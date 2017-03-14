#ifndef TFTP_H
#define TFTP_H

#include <QtNetwork>


enum TFTP_OPERATION_CODE {
    TFTP_CODE_RRQ = 1,
    TFTP_CODE_WRQ,
    TFTP_CODE_DATA,
    TFTP_CODE_ACK,
    TFTP_CODE_ERROR,
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

class TFTP : public QObject {
public:
    void tftp_Init(QString fileName);
    bool tftp_WriteDatagram();

private:
    QUdpSocket *udpSocket;

private slots:
    void readPendingDatagrams();
};

#endif // TFTP_H
