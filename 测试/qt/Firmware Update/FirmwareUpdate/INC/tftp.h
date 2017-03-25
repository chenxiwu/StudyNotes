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
    MSG_WRQ_START = 0,
    MSG_WRQ_SUCCESS,
    MSG_WRQ_TIMEOUT,
    MSG_WRQ_REPEAT,

    MSG_WR_DATA_START,
    MSG_WR_DATA_SUCCESS,
    MSG_WR_DATA_TIMEOUT,
    MSG_WR_DATA_UNKNOWN,
}TFTP_MSG_ENUM;

typedef enum {
    ERROR_NONE = 0,
    ERROR_INSIDE,
    ERROR_FILE,
    ERROR_TIMEOUT,
}TFTP_ERROR_ENUM;

class TFTP : public QObject {
    Q_OBJECT

public:
    explicit TFTP(const QString &remoteIP, const QString &filePath);
    ~TFTP();

    void writeReq();
    TFTP_ERROR_ENUM writeFile();
    TFTP_WR_STATUS getStatus();
    void setRemoteIP(const QString &remoteIP);
    void setFilePath(const QString &filePath);

signals:
    void sendMsg(quint32);

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
