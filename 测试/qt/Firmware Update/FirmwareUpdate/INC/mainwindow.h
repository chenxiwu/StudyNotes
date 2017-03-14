#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QLabel>
#include <QtNetwork>

enum CONNECT_PRM_STATUS {
    PRM_DISCONNECT = 0,
    PRM_AGREE,
    PRM_REJECT,
};

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
    bool isIP_SegmentEqual(QString ip1, QString subnetMask1, QString ip2, QString subnetMask2);
    bool checkInput();
    bool checkPRMConnect();
    void initSocket();

private slots:
    void on_pushButton_Open_clicked();
    void on_pushButton_Update_clicked();

    void on_tabWidget_currentChanged(int index);
    void on_lineEdit_returnPressed();
    void readPendingDatagrams();

private:
    Ui::MainWindow *ui;
    QProgressBar *progressBar;
    QLabel *statusLabel;
    int curPage;
    QUdpSocket *udpSocket;
    CONNECT_PRM_STATUS connectStatus;
};

#endif // MAINWINDOW_H
