#include "mainwindow.h"
#include <QApplication>
#include "utils.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qInstallMessageHandler(myMessageOutput);

    MainWindow w;
    w.show();

    return a.exec();
}
