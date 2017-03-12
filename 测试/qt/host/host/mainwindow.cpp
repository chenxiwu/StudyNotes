#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtNetwork>

static QString getIP() {
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol) {
            qDebug() << address.toString();
        }
    }

    return NULL;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QString localHostName = QHostInfo::localHostName();
//    QHostInfo info = QHostInfo::fromName(localHostName);
//    qDebug() << localHostName;

//    foreach (QHostAddress address, info.addresses()) {
//        if (address.protocol() == QAbstractSocket::IPv4Protocol) {
//            qDebug() << address.toString();
//        }
//    }
//    setWindowTitle(localHostName);

//    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
//    foreach (QNetworkInterface interface, list) {

//        QList<QNetworkAddressEntry> list = interface.addressEntries();
//        foreach (QNetworkAddressEntry entry, list) {
//            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol) {
//                qDebug() << "IP: " + entry.ip().toString()
//                         << "SubMask: " + entry.netmask().toString()
//                         << "GetWay: " + entry.broadcast().toString();
//            }
//        }
//    }

    getIP();
}

MainWindow::~MainWindow()
{
    delete ui;
}
