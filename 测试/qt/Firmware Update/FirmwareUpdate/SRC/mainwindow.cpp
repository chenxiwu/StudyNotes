#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTabWidget>
#include <QFileDialog>
#include <QDialog>
#include <QMessageBox>
#include "tftp.h"
#include "crc16.h"
#include "utils.h"
#include "dialogdebug.h"
#include <QThread>
#include "dialogabout.h"

enum  PAGE_INDEX_ENUM{
    PAGE_AUTO = 0,
    PAGE_MANUAL,
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile::remove(LOG_NAME);
    curPage = PAGE_AUTO;
    setWindowTitle(QStringLiteral("控制器固件升级"));
    setFixedSize(this->width(), this->height());

    updateLocalIP();
    initSocket();

    connect(ui->tabWidget, SIGNAL(currentChanged(int)),
            this, SLOT(on_tabWidget_currentChanged(int)));
    ui->tabWidget->setCurrentIndex(0);

    ui->lineEdit_AutoControllerPort->setText("9999");

    ui->lineEdit_ManualControllerIP->setText
            (QStringLiteral("192.168.0.111"));
    ui->lineEdit_ManualControllerIP->setDisabled(true);
    ui->lineEdit_ManualControllerPort->setText
            (QStringLiteral("69"));
    ui->lineEdit_ManualControllerPort->setDisabled(true);

    statusLabel = new QLabel();
    statusLabel->setMinimumSize(150, 24);
    statusLabel->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);
    statusLabel->setText(QStringLiteral("欢迎使用固件升级助手！"));
    ui->statusBar->addWidget(statusLabel);

    progressBar = new QProgressBar();
    progressBar->setMaximumSize(100, 16);
    ui->statusBar->addWidget(progressBar);
    progressBar->hide();

    QLabel *label = new QLabel(this);
    label->setFrameStyle(QFrame::Box | QFrame::Sunken);
    label->setText(QStringLiteral("<a href=\"http://www.hzxingao.com\">杭州鑫高</a>"));
    label->setTextFormat(Qt::RichText);
    label->setOpenExternalLinks(true);
    ui->statusBar->addPermanentWidget(label);

    updateStatus = STATUS_DISCONNECT;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateLocalIP()
{
    ui->comboBox_LocalIP->clear();

    QVector<QHostAddress> hostAddress;
    getLocalIP(hostAddress);

    for (int i=0; i<hostAddress.count(); ++i) {
        QHostAddress address = hostAddress.at(i);

        qDebug() << "本地IP：" + address.toString();
        ui->comboBox_LocalIP->addItem(address.toString());
    }
}

bool MainWindow::checkInput()
{
    if (ui->lineEdit_Firmware->text().isEmpty() == true) {
        qDebug() << "未选择固件！";
        QMessageBox::information(this, QStringLiteral("提示信息"),
                                 QStringLiteral("请先选择固件！"),
                                 QMessageBox::Ok);

        return false;
    }

    if (curPage == PAGE_AUTO) {
        if (ui->comboBox_AutoControllerIP->count() == 0) {
            qDebug() << "控制器IP为空！";
            QMessageBox::information(this, QStringLiteral("提示信息"),
                                     QStringLiteral("控制器IP不能为空，请点击【自动获取】按钮！"),
                                     QMessageBox::Ok);

            return false;
        }

        QString localIP = ui->comboBox_LocalIP->currentText();
        QString remoteIP = ui->comboBox_AutoControllerIP->currentText();
        if (isInSubnet(localIP, "255.255.255.0", remoteIP, "255.255.255.0") == false) {
            qDebug() << "本地IP与控制器IP不在同一网段！";
            QMessageBox::information(this, QStringLiteral("提示信息"),
                                     QStringLiteral("本地IP与控制器IP不在同一个网段！"),
                                     QMessageBox::Ok);

            return false;
        }

        if (ui->lineEdit_AutoControllerPort->text().isEmpty() == true) {
            qDebug() << "控制器端口为空！";
            QMessageBox::information(this, QStringLiteral("提示信息"),
                                     QStringLiteral("控制器端口不能为空！"),
                                     QMessageBox::Ok);

            return false;
        }
    }

    return true;
}

void MainWindow::initSocket()
{
    udpSocket = new QUdpSocket(this);

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
}

void MainWindow::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        QHostAddress remoteAddress;
        quint16 remotePort;

        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(), &remoteAddress, &remotePort);

        qDebug() << "远程服务器信息：" << remoteAddress.toString();
        //移除子网掩码
        QString remoteIP = remoteAddress.toString();
        QRegExp exp(":");
        quint8 index = remoteIP.lastIndexOf(exp);
        remoteIP = remoteIP.remove(0, index+1);

        UDP_PROTECOL_HEAD_TypeDef *head = (UDP_PROTECOL_HEAD_TypeDef *)datagram.data();
        UDP_PROTECOL_TAIL_TypeDef *tail = (UDP_PROTECOL_TAIL_TypeDef *)(datagram.data() +
                                                                        sizeof(UDP_PROTECOL_HEAD_TypeDef)
                                                                        + head->size);
        quint16 crc = CRC16::get(0, (quint8 *)datagram.data(),
                                 sizeof(UDP_PROTECOL_HEAD_TypeDef) + head->size);
        if (tail->crc != crc) {
            qDebug() << "CRC校验错误！";
            continue;
        }

        CMD_UPDATE_REPLY_TypeDef *body = (CMD_UPDATE_REPLY_TypeDef *)head->data;
        const quint8 STATUS_REPLY_OK = 0;

        switch (updateStatus) {
        case STATUS_DISCONNECT:
            if (body->status == STATUS_REPLY_OK) {
                qDebug() << "[状态] 发现设备！";
                updateStatus = STATUS_CONNECT;
                ui->comboBox_AutoControllerIP->addItem(remoteIP);

    //            updateLocalIpByControllerIp(ui->comboBox_AutoControllerIP->currentText());
            }
            break;
        case STATUS_CONNECT:
            if (body->status == STATUS_REPLY_OK) {
                qDebug() << "[状态] 控制器同意升级！";
                updateStatus = STATUS_AGREE;

                //开启TFTP线程
                tftpThread = new TftpThread();
                connect(tftpThread, SIGNAL(sendMsg(quint32)),
                        this, SLOT(on_tftpReceiveMsg(quint32)));
                connect(tftpThread, SIGNAL(sendProgress(quint32)),
                        this, SLOT(on_tftpUpdateProgress(quint32)));
                connect(tftpThread, &TftpThread::finished,
                        tftpThread, &QObject::deleteLater);
                tftpThread->remoteIP = ui->comboBox_AutoControllerIP->currentText();
                tftpThread->filePath = ui->lineEdit_Firmware->text();
                tftpThread->start();
            } else {
                qDebug() << "[状态] 控制器忙！";
                updateStatus = STATUS_BUSY;
            }
            break;
        default:
             qDebug() << "[状态] 未知状态！";
            break;
        }
    }
}

void MainWindow::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                            QStringLiteral("选择升级文件"));
    if (filePath.isEmpty() == false) {
        ui->lineEdit_Firmware->setText(filePath);
    }

    qDebug() << "打开文件！";
}

void MainWindow::updateLocalIpByControllerIp(const QString &controllerIp)
{
    for (int i=0; i<ui->comboBox_LocalIP->count(); ++i) {
        if (isInSubnet(ui->comboBox_LocalIP->itemText(i), "255.255.255.0",
                       controllerIp, "255.255.255.0") == true) {
            //自动更新下拉列表数据
            ui->comboBox_LocalIP->setCurrentIndex(i);
            break;
        }
    }
}

void MainWindow::on_pushButton_Open_clicked()
{
    openFile();
}

/*
 * TFTP升级线程执行体
 */
void TftpThread::run()
{
    TFTP tftp(remoteIP, filePath);
    connect(&tftp, SIGNAL(sendProgress(quint32)),
            this, SLOT(on_receiveProgress(quint32)));

    int count = 0;
    int repeatCount = 0;

    emit sendMsg(MSG_WRQ_START);
    tftp.writeReq();

    while(1) {
        QThread::msleep(10);
        QCoreApplication::processEvents();
        count++;

        if (tftp.getStatus() == TFTP_STATUS_SENDING) {
            tftp.sendMsg(MSG_WRQ_SUCCESS);
            break;
        } else if (count % 100 == 0) {
            repeatCount++;
            if (repeatCount > 10) {
                emit sendMsg(MSG_WRQ_TIMEOUT);
                return;
            }

            tftp.writeReq();
            emit sendMsg(MSG_WRQ_REPEAT);
        }
    }

    emit sendMsg(MSG_WR_DATA_START);
    TFTP_ERROR_ENUM ret = tftp.writeFile();
    switch (ret) {
    case ERROR_NONE:
        emit sendMsg(MSG_WR_DATA_SUCCESS);
        break;
    case ERROR_INSIDE:
    case ERROR_FILE:
        emit sendMsg(MSG_WR_DATA_UNKNOWN);
        break;
    case ERROR_TIMEOUT:
        emit sendMsg(MSG_WR_DATA_TIMEOUT);
        break;
    default:
        emit sendMsg(MSG_WR_DATA_UNKNOWN);
        break;
    }

    exit();
    qDebug() << "线程结束！";
}

void MainWindow::on_receiveProgress(quint32 progress)
{
    emit sendProgress(progress);
}

void MainWindow::UpdateFirmWare_Handler()
{
    qDebug() << "> 准备升级...";

    QByteArray cmd;
    CMD_SystemUpdate(cmd, true);

    QString remoteIP = ui->comboBox_AutoControllerIP->currentText();
    qDebug() << "控制器IP：" << remoteIP;
    QString remotePort = ui->lineEdit_AutoControllerPort->text();
    qDebug() << "控制器端口：" << remotePort;
    udpSocket->writeDatagram(cmd.data(), cmd.size(),
                         QHostAddress(remoteIP), remotePort.toInt());

    QTimer::singleShot(3000, this, SLOT(on_timer1Timeout()));
}

void MainWindow::on_pushButton_Update_clicked()
{
    qDebug() << "按下[升级]按钮！";

    if (checkInput() == false) {
        return;
    }

    ui->pushButton_Update->setDisabled(true);
    repaint();
    UpdateFirmWare_Handler();   
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    curPage = index;
}

void MainWindow::on_action_O_triggered()
{
    openFile();
}

void MainWindow::on_pushButton_Update_aotoGet_clicked()
{
    qDebug() << "按下 [自动获取] 按钮！";
    updateStatus = STATUS_DISCONNECT;
    qDebug() << "[状态] 未连接！";

    ui->comboBox_AutoControllerIP->clear();   
    QByteArray cmd;
    CMD_SystemUpdate(cmd, false);
    qDebug() << "控制器IP：" << "广播";
    QString remotePort = ui->lineEdit_AutoControllerPort->text();
    qDebug() << "控制器端口：" << remotePort;
    udpSocket->writeDatagram(cmd.data(), cmd.size(),
                         QHostAddress::Broadcast, remotePort.toInt());
}

void MainWindow::on_action_Debug_triggered()
{
    DialogDebug *dlgDebug = new DialogDebug();
    dlgDebug->setWindowTitle(QStringLiteral("调试输出"));
    dlgDebug->setWindowFlags(Qt::WindowCloseButtonHint);
    dlgDebug->show();
}

void MainWindow::on_tftpReceiveMsg(quint32 msg)
{
    switch (msg) {
    case MSG_WRQ_START:
        qDebug() << "[TFTP] 写请求开始！";
        break;
    case MSG_WRQ_SUCCESS:
        qDebug() << "[TFTP] 写请求成功！";
        break;
    case MSG_WRQ_TIMEOUT:
        qDebug() << "[TFTP] 写请求超时！";
        updateAfterDispose();
        break;
    case MSG_WRQ_REPEAT:
        qDebug() << "[TFTP] 写请求重发！";
        break;
    case MSG_WR_DATA_START:
        qDebug() << "[TFTP] 写数据开始！";
        break;
    case MSG_WR_DATA_SUCCESS:
        qDebug() << "[TFTP] 写数据包成功！";
        qDebug() << "升级完成！";
        updateStatus = STATUS_CONNECT;
        updateAfterDispose();
        QMessageBox::information(this, QStringLiteral("提示信息"),
                                 QStringLiteral("升级成功！"),
                                 QMessageBox::Ok);
        break;
    case MSG_WR_DATA_TIMEOUT:
        qDebug() << "[TFTP] 写数据包超时！";
        updateAfterDispose();
        break;
    case MSG_WR_DATA_UNKNOWN:
        qDebug() << "[TFTP] 写数据包未知错误！";
        updateAfterDispose();
        break;
    default:
        qDebug() << "[TFTP] TFTP其他状态！";
        updateAfterDispose();
        break;
    }
}

void MainWindow::on_tftpUpdateProgress(quint32 progress)
{
    if (progress == 0) {
        progressBar->show();
    }
    progressBar->setValue(progress);
}

void MainWindow::updateAfterDispose()
{
    ui->pushButton_Update->setEnabled(true);
    progressBar->hide();
}

void MainWindow::on_timer1Timeout()
{
    switch (updateStatus) {
    case STATUS_DISCONNECT:
        QMessageBox::information(this, QStringLiteral("提示信息"),
                                 QStringLiteral("找不到控制器！"),
                                 QMessageBox::Ok);
        break;
    case STATUS_CONNECT:
        QMessageBox::information(this, QStringLiteral("提示信息"),
                                 QStringLiteral("控制器未响应！"),
                                 QMessageBox::Ok);
        break;
    case STATUS_BUSY:
        QMessageBox::information(this, QStringLiteral("提示信息"),
                                 QStringLiteral("控制器正在忙！"),
                                 QMessageBox::Ok);
        break;
    case STATUS_AGREE:
        return;
    default:
        break;
    }

    updateAfterDispose();
}

void MainWindow::on_action_A_triggered()
{
    DialogAbout dlg;
    dlg.setWindowTitle(QStringLiteral("关于"));
    dlg.setWindowFlags(Qt::WindowCloseButtonHint);
    dlg.exec();
}

void MainWindow::on_action_Log_triggered()
{
    on_action_Debug_triggered();
}
