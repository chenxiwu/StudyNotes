#include "mainwindow.h"
#include <QApplication>
#include "mysql.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    if (mysql_Connect("student") == true) {
        mysql_InsertData();


    }

    return a.exec();
}
