#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    receiver = new QUdpSocket(this);
    receiver->bind(55445, QUdpSocket::ShareAddress);
    connect(receiver, SIGNAL(readyRead()),
            this, SLOT(DataReadyRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DataReadyRead()
{
    qDebug() <<"receive Data";

    while (receiver->hasPendingDatagrams() == true) {
        QByteArray datagram;
        datagram.resize(receiver->pendingDatagramSize());
        receiver->readDatagram(datagram.data(), datagram.size());
        ui->label->setText(datagram);
    }

}
