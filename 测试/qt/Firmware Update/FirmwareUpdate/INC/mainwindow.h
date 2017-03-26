#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QLabel>
#include <QtNetwork>
#include "dialogdebug.h"
#include "tftp.h"

namespace Ui {
class MainWindow;
}

class TftpThread :public QThread {
    Q_OBJECT

protected:
    void run();

signals:
    void sendMsg(quint32);

public:
    QString remotePort;
    QString filePath;
};

typedef enum {
    STATUS_DISCONNECT = 0,
    STATUS_CONNECT,
    STATUS_AGREE,
    STATUS_BUSY,
}UPDATE_STATUS_TypeDef;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateLocalIP();    
    bool checkInput();
    void initSocket();
    void openFile();
    void updateLocalIpByControllerIp(const QString &controllerIp);
    void UpdateFirmWare_Handler();
    void updateAfterDispose();

private slots:
    void on_pushButton_Open_clicked();
    void on_pushButton_Update_clicked();
    void on_tabWidget_currentChanged(int index);
    void readPendingDatagrams();
    void on_action_O_triggered();
    void on_pushButton_Update_aotoGet_clicked();
    void on_action_Debug_triggered();
    void on_tftpReceiveMsg(quint32 msg);
    void on_timer1Timeout();
    void on_action_A_triggered();
    void on_action_Log_triggered();

private:
    Ui::MainWindow *ui;
    QProgressBar *progressBar;
    QLabel *statusLabel;
    int curPage;
    QUdpSocket *udpSocket;
    TftpThread tftpThread;
    UPDATE_STATUS_TypeDef updateStatus;
};

#endif // MAINWINDOW_H
