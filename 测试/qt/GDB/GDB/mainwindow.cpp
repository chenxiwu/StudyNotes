#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.h"
#include <QVector>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    const QString SOFT_VERSION = "(V1.00)";

    ui->setupUi(this);

    setWindowTitle(QStringLiteral("以太网调试助手GDB") + " " + SOFT_VERSION);

    updateLocalIP();
    ui->lineEdit_localPort->setText("5555");
    udpConnect = false;
    initSocket(); 
    connect(ui->textBrowser_receive, SIGNAL(cursorPositionChanged()),
            this, SLOT(autoScroll()));

    ui->lineEdit_remoteIP->setDisabled(true);
    ui->lineEdit_remotePort->setDisabled(true);
    ui->pushButton_send->setDisabled(true);

    QPalette pal;
    pal.setColor(QPalette::ButtonText, Qt::blue);
    ui->pushButton_clear->setPalette(pal);

    QLabel *statusLabel = new QLabel();
    statusLabel->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);
    statusLabel->setText(QStringLiteral("By <SY>"));
    ui->statusBar->addWidget(statusLabel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateLocalIP()
{
    ui->comboBox_localIP->clear();

    QVector<QHostAddress> hostAddress;
    getLocalIP(hostAddress);

    for (int i=0; i<hostAddress.count(); ++i) {
        QHostAddress address = hostAddress.at(i);

        qDebug() << "本地IP：" + address.toString();
        ui->comboBox_localIP->addItem(address.toString());
    }
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
        udpSocket->readDatagram(datagram.data(), datagram.size(),
                                &remoteAddress, &remotePort);

        qDebug() << "远程服务器信息：" << remoteAddress.toString();
        QString remoteIP = remoteAddress.toString();

        if (ui->lineEdit_remoteIP->text().isEmpty() == true) {
            ui->lineEdit_remoteIP->setText(remoteIP);
        }
        if (ui->lineEdit_remotePort->text().isEmpty() == true) {
            ui->lineEdit_remotePort->setText(QString::number(remotePort));
        }

        ui->textBrowser_receive->append(QString::fromLocal8Bit(datagram.data()));
    }
}

void MainWindow::on_pushButton_connect_clicked()
{
    quint16 port = 0;

    udpSocket->close();

    udpConnect = !udpConnect;

    if (udpConnect == true) {
        QString localIP = ui->comboBox_localIP->currentText();
        QHostAddress host(localIP);
        port = ui->lineEdit_localPort->text().toUInt();
        if (udpSocket->bind(host, port,
                        QAbstractSocket::ShareAddress |
                        QUdpSocket::ReuseAddressHint)== true) {
            QPalette pal;
            pal.setColor(QPalette::ButtonText, Qt::red);
            ui->pushButton_connect->setPalette(pal);
            ui->pushButton_connect->setText("断开连接");
        } else {
            QMessageBox::warning(this, "警告", "绑定端口失败！");
        }
    } else {
        QPalette pal;
        pal.setColor(QPalette::ButtonText, Qt::black);
        ui->pushButton_connect->setPalette(pal);
        ui->pushButton_connect->setText("连  接");
    }

    ui->comboBox_localIP->setDisabled(udpConnect);
    ui->lineEdit_localPort->setDisabled(udpConnect);
    ui->lineEdit_remoteIP->setEnabled(udpConnect);
    ui->lineEdit_remotePort->setEnabled(udpConnect);
    ui->pushButton_send->setEnabled(udpConnect);
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->textBrowser_receive->clear();
}

void MainWindow::autoScroll()
{
    QTextCursor cursor =  ui->textBrowser_receive->textCursor();

    cursor.movePosition(QTextCursor::End);

    ui->textBrowser_receive->setTextCursor(cursor);
}

void MainWindow::on_pushButton_send_clicked()
{
    if (ui->lineEdit_remoteIP->text().isEmpty() == true) {
        QMessageBox::warning(this, "警告", "远程IP地址不能为空！");
        return;
    }
    if (ui->lineEdit_remotePort->text().isEmpty() == true) {
        QMessageBox::warning(this, "警告", "远程端口不能为空！");
        return;
    }
    if (ui->textEdit_sender->document()->isEmpty() == true) {
        QMessageBox::warning(this, "警告", "发送内容不能为空！");
        return;
    }

    QByteArray datagram;
    datagram.append(ui->textEdit_sender->document()->toPlainText());
    QHostAddress hostAddress = QHostAddress(ui->lineEdit_remoteIP->text());
    quint16 remotePort = ui->lineEdit_remotePort->text().toUInt();
    if (udpSocket->writeDatagram(datagram, hostAddress, remotePort) < 0) {
        QMessageBox::warning(this, "警告", "发送数据包失败！");
    }
}
