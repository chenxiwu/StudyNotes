#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QSqlQuery"
#include "QSqlRecord"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QSqlQuery query;

    //query.exec("select id, name from info");
    /*
    while (query.next()) {
        qDebug() << query.value(0).toInt()
                 << query.value(1).toString();
    }
    */

    /*
    if (query.next()) {
        int rowNums = query.at();
        qDebug() << rowNums;

        //查询列数
        int columnNums = query.record().count();
        qDebug() << columnNums;

        //获取属性所在的列号
        int fieldName = query.record().indexOf("name");
        qDebug() << query.value(fieldName).toString();
    }

    qDebug() << "seek(2):";
    if (query.seek(3)) {
        qDebug() << query.at()
                 << query.value(0).toInt()
                 << query.value(1).toString();

    }

    qDebug() << "last()";
    if (query.last()) {
        qDebug() << query.value(0).toInt()
                 << query.value(1).toString();
    }
    */

    int id = ui->spinBox->text().toInt();
    query.exec(QString("select name from info where id =%1").arg(id));
    if (query.next()) {
        QString name = query.value(0).toString();
        qDebug() << name;
    }
}
