#ifndef UTILS_H
#define UTILS_H

#include <QMainWindow>
#include <QHostAddress>

const QString LOG_NAME = "log.txt";

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

quint16 htons(quint16 n);
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);
void CMD_SystemUpdate(QByteArray &cmd, bool isUpdate);
void getLocalIP(QVector<QHostAddress> &localIP);
bool isInSubnet(QString ip1, QString subnetMask1,
                       QString ip2, QString subnetMask2);

#endif // UTILS_H
