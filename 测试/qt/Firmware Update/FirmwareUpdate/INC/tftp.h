#ifndef TFTP_H
#define TFTP_H

#include <QMainWindow>
#include <QtNetwork>


enum TFTP_OPERATION_CODE {
    TFTP_CODE_RRQ = 1,
    TFTP_CODE_WRQ,
    TFTP_CODE_DATA,
    TFTP_CODE_ACK,
    TFTP_CODE_ERROR,
};

enum TFTP_WR_STATUS {
    TFTP_STATUS_WRQ = 0,
    TFTP_STATUS_SENDING,
    TFTP_STATUS_DONE,
};

#pragma pack(push,1)

struct TFTP_WRQ {
    quint16 opCode;
    QString fileName;
    QString mode;
};

struct TFTP_DATA {
    quint16 opCode;
    quint16 block;
    quint8 data[0];
};

struct TFTP_ACK {
    quint16 opCode;
    quint16 block;
};

struct TFTP_ERROR {
    quint16 opCode;
    quint16 errorCode;
    QString errMsg;
};


#pragma pack(pop)

class TFTP : public QMainWindow {
    Q_OBJECT

public:
    explicit TFTP(const QString remoteIP);
    ~TFTP();

    void writeReq(const QString &fileName);
    bool writeFile(const QString &filePath);

private slots:
    void readPendingDatagrams();

private:
    QUdpSocket *udpSocket;
    TFTP_WR_STATUS wrStatus;
    quint16 block;
    QString remoteIP;
    quint16 remotePort;
};

#endif // TFTP_H
