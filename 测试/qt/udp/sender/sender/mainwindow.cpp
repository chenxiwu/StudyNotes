
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sender = new QUdpSocket(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QByteArray datagram = "Hello World!";
    sender->writeDatagram(datagram.data(), datagram.size(),
                          QHostAddress::Broadcast, 55445);
    qDebug() << "Send Data";
}
