#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "function.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Function function;

    int value = function.add(3, 5);
    qDebug() << value;
}

MainWindow::~MainWindow()
{
    delete ui;
}
