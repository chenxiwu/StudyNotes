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
    connectStatus = PRM_DISCONNECT;

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
    statusLabel->setText(QStringLiteral("欢迎使用固件升级系统！"));
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

    debugOpen = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateLocalIP()
{
    ui->comboBox_LocalIP->clear();

    QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName());
    foreach(QHostAddress address, info.addresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol) {
            qDebug() << "本地IP：" + address.toString();

            ui->comboBox_LocalIP->addItem(address.toString());
        }
    }
}

bool MainWindow::isIP_SegmentEqual(QString ip1, QString subnetMask1,
                                   QString ip2, QString subnetMask2)
{
    QStringList ip_list1 = ip1.split('.');
    QStringList mask_list1 = subnetMask1.split('.');
    QStringList ip_list2 = ip2.split('.');
    QStringList mask_list2 = subnetMask2.split('.');

    if (ip_list1.count() != ip_list2.count()) {
        return false;
    }

    for (int i=0; i<ip_list1.count(); ++i) {
        int num1 = ip_list1.at(i).toInt() & mask_list1.at(i).toInt();
        int num2 = ip_list2.at(i).toInt() & mask_list2.at(i).toInt();
        if (num1 != num2) {
            return false;
        }
    }

    return true;
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

        QString ip1 = ui->comboBox_LocalIP->currentText();
        QString ip2 = ui->comboBox_AutoControllerIP->currentText();
        if (isIP_SegmentEqual(ip1, "255.255.255.0", ip2, "255.255.255.0") == false) {
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

bool MainWindow::CMD_SystemUpdate(bool isUpdate)
{
    QByteArray updateCmd;
    UDP_PROTECOL_HEAD_TypeDef head;
    head.start = 0x1B;
    head.addr = 0;
    head.index = 0x21;
    head.rsv1 = 0;
    head.size = sizeof(CMD_UPDATE_TypeDef);
    head.rsv2 = 0;
    head.token = 0x0E;
    updateCmd.append((const char *)&head, sizeof(head));

    CMD_UPDATE_TypeDef body;
    body.cmd = 0x0011;
    body.update = isUpdate;
    updateCmd.append((const char *)&body, sizeof(body));

    UDP_PROTECOL_TAIL_TypeDef tail;
    tail.crc = CRC16::get(0, (quint8 *)updateCmd.data(), updateCmd.size());
    tail.end = 0x16;
    updateCmd.append((const char *)&tail, sizeof(tail));

    QString port = ui->lineEdit_AutoControllerPort->text();
    qDebug() << "控制器端口：" << port;
    udpSocket->writeDatagram(updateCmd.data(), updateCmd.size(),
                         QHostAddress::Broadcast, port.toInt());

    qDebug() << "> 发送系统更新命令！";

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

        QString remoteIP = remoteAddress.toString();
        QRegExp exp("[A-Za-z:]");
        remoteIP = remoteIP.remove(exp);

        UDP_PROTECOL_HEAD_TypeDef *head = (UDP_PROTECOL_HEAD_TypeDef *)datagram.data();
        UDP_PROTECOL_TAIL_TypeDef *tail = (UDP_PROTECOL_TAIL_TypeDef *)(datagram.data() +
                                                                        sizeof(UDP_PROTECOL_HEAD_TypeDef)
                                                                        + head->size);
        quint16 crc = CRC16::get(0, (quint8 *)datagram.data(),
                                 sizeof(UDP_PROTECOL_HEAD_TypeDef) + head->size);
        if (tail->crc != crc) {
            continue;
        }

        CMD_UPDATE_REPLY_TypeDef *body = (CMD_UPDATE_REPLY_TypeDef *)head->data;
        const quint8 STATUS_REPLY_OK = 0;

        switch (connectStatus) {
        case PRM_DISCONNECT:
            if (body->status == STATUS_REPLY_OK) {              
                ui->comboBox_AutoControllerIP->addItem(remoteIP);
            }
            break;
        case PRM_AGREE:

            break;
        case PRM_REJECT:

            break;
        default:
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
        if (isIP_SegmentEqual(ui->comboBox_LocalIP->itemText(i) , "255.255.255.0",
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

void MainWindow::UpdateFirmWare_Handler()
{
    connectStatus = PRM_DISCONNECT;
    CMD_SystemUpdate(true);
    QThread::msleep(1000);

    TFTP tftp(ui->comboBox_AutoControllerIP->currentText());
    QString filePath = ui->lineEdit_Firmware->text();
    QFileInfo info(filePath);

    quint32 cnt = 0;
    while (1) {
        if (cnt % 1000 == 0) {
            tftp.writeReq(info.fileName());
        }
        cnt++;
        QThread::msleep(1);

        TFTP_WR_STATUS status = tftp.getStatus();
        if (status == TFTP_STATUS_SENDING) {
            break;
        } else if (cnt >= 5000) {
            QMessageBox::information(this, QStringLiteral("提示信息"),
                                     QStringLiteral("接收控制器命令超时！"),
                                     QMessageBox::Ok);
            return;
        }
    }

    tftp.writeFile(filePath);

    int timeoutCount = 0;
    const int TIMEOUT = 1000;
    while ((connectStatus == PRM_DISCONNECT) &&
           (timeoutCount < TIMEOUT)) {
        QThread::msleep(20);
        timeoutCount += 20;
    }
    switch (connectStatus) {
    case PRM_DISCONNECT:
        QMessageBox::information(this, QStringLiteral("提示信息"),
                                 QStringLiteral("连接控制器失败！"),
                                 QMessageBox::Ok);
        break;
    case PRM_REJECT:
        QMessageBox::information(this, QStringLiteral("提示信息"),
                                 QStringLiteral("控制器正在忙！"),
                                 QMessageBox::Ok);
        break;
    case PRM_AGREE:
        ui->pushButton_Update->setText(QStringLiteral("升级中..."));
        repaint();

        //等待控制器进入BootLoader
        QThread::msleep(1000);


        break;
    default:
        break;
    }

}

void MainWindow::on_pushButton_Update_clicked()
{
    qDebug() << "按下[升级]按钮！";

    if (checkInput() == false) {
        return;
    }

    QString updatePuttonText = ui->pushButton_Update->text();
    ui->pushButton_Update->setText(QStringLiteral("正在连接..."));
    ui->pushButton_Update->setDisabled(true);
    repaint();

    UpdateFirmWare_Handler();

    ui->pushButton_Update->setText(updatePuttonText);
    ui->pushButton_Update->setEnabled(true);
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

    ui->pushButton_Update_aotoGet->setDisabled(true);
    repaint();

    ui->comboBox_AutoControllerIP->clear();

    connectStatus = PRM_DISCONNECT;
    CMD_SystemUpdate(false);

    ui->pushButton_Update_aotoGet->setEnabled(true);
}

void MainWindow::on_action_Debug_triggered()
{
    if (debugOpen == true) {
        return;
    }


}


