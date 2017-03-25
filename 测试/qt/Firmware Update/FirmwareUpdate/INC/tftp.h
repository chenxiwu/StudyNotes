#ifndef TFTP_H
#define TFTP_H

#include <QMainWindow>
#include <QtNetwork>
#include <QThread>


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

typedef enum {
    MSG_WRQ_OK = 0,
    MSG_WRQ_TIMEOUT,
    MSG_WRQ_REPEAT,

    MSG_WR_DATA_OK,
    MSG_WR_DATA_TIMEOUT,
    MSG_WR_DATA_REPEAT,
}TFTP_MSG_TypeDef;

class TFTP : public QThread {
    Q_OBJECT

public:
    explicit TFTP();
    ~TFTP();

    void writeReq(const QString &fileName);
    bool writeFile(const QString &filePath);
    TFTP_WR_STATUS getStatus();
    void setRemoteIP(const QString &remoteIP);
    void setFilePath(const QString &filePath);

signals:
    void sendMsg(quint32);

protected:
    void run();

private slots:
    void readPendingDatagrams();

private:
    QUdpSocket *udpSocket;
    TFTP_WR_STATUS wrStatus;
    quint16 block;
    QString remoteIP;
    quint16 remotePort;
    QString filePath;
    QString fileName;
};

#endif // TFTP_H
