#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void updateLocalIP();
    void initSocket();

private slots:
    void readPendingDatagrams();
    void on_pushButton_connect_clicked();
    void on_pushButton_clear_clicked();
    void autoScroll();

    void on_pushButton_send_clicked();

private:
    Ui::MainWindow *ui;
    QUdpSocket *udpSocket;
    bool udpConnect;
};

#endif // MAINWINDOW_H
