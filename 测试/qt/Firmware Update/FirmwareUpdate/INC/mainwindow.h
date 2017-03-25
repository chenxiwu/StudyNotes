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

#pragma pack(push,1)

typedef struct {
    quint8 start;
    quint8 addr;
    quint8 index;
    quint8 rsv1;
    quint16 size;
    quint8 rsv2;
    quint8 token;
    quint8 data[0];
}UDP_PROTECOL_HEAD_TypeDef;

typedef struct {
    quint16 cmd;
    quint8 update;
}CMD_UPDATE_TypeDef;

typedef struct {
    quint16 cmd;
    quint8 status;
}CMD_UPDATE_REPLY_TypeDef;

typedef struct {
    quint16 crc;
    quint8 end;
}UDP_PROTECOL_TAIL_TypeDef;

#pragma pack(pop)

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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateLocalIP();
    bool isIP_SegmentEqual(QString ip1, QString subnetMask1, QString ip2, QString subnetMask2);
    bool checkInput();
    bool CMD_SystemUpdate(bool isUpdate);
    void initSocket();
    void openFile();
    void updateLocalIpByControllerIp(const QString &controllerIp);
    void UpdateFirmWare_Handler();

private slots:
    void on_pushButton_Open_clicked();
    void on_pushButton_Update_clicked();
    void on_tabWidget_currentChanged(int index);
    void readPendingDatagrams();
    void on_action_O_triggered();
    void on_pushButton_Update_aotoGet_clicked();
    void on_action_Debug_triggered();
    void on_receiveMsg(quint32 msg);

private:
    Ui::MainWindow *ui;
    QProgressBar *progressBar;
    QLabel *statusLabel;
    int curPage;
    QUdpSocket *udpSocket;
    TftpThread tftpThread;

};

#endif // MAINWINDOW_H
