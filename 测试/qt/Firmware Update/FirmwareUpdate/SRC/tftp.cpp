#include "tftp.h"
#include <QDebug>
#include <QDataStream>
#include <QMessageBox>
#include <QtEndian>
#include "utils.h"


TFTP::TFTP(const QString &remoteIP, const QString &filePath)
{
    this->remotePort = 69;   
    this->remoteIP = remoteIP;
    this->filePath = filePath;
    QFileInfo info(filePath);
    this->fileName = info.fileName();

    udpSocket = new QUdpSocket(this);
    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
}

TFTP::~TFTP()
{
    if (udpSocket != NULL) {
        delete udpSocket;
    }
    udpSocket = NULL;
}

void TFTP::writeReq()
{
    wrStatus = TFTP_STATUS_WRQ;

    /*
        2 bytes     string    1 byte     string   1 byte
       ------------------------------------------------
      | Opcode |  Filename  |   0  |    Mode    |   0  |
       ------------------------------------------------
    */
    struct TFTP_WRQ writeReq;
    writeReq.opCode = htons(TFTP_CODE_WRQ);

    QByteArray datagram;
    datagram.append((const char *)&writeReq, sizeof(writeReq.opCode));
    datagram.append(fileName);
    datagram.append('\0');
    datagram.append("octet");
    datagram.append('\0');

    udpSocket->writeDatagram(datagram.data(), datagram.size(),
                             QHostAddress(remoteIP), remotePort);   
}

TFTP_ERROR_ENUM TFTP::writeFile()
{
    /*
        2 bytes     2 bytes      n bytes
        ----------------------------------
        | Opcode |   Block #  |   Data     |
        ----------------------------------
    */
    if (wrStatus != TFTP_STATUS_SENDING) {
        return ERROR_INSIDE;
    }

    QFile file(filePath);
    if (file.open(QFile::ReadOnly) == false) {
        return ERROR_FILE;
    }
    QDataStream in(&file);
    file.close();

    const quint32 ONCE_SEND_SIZE = 512;
    QByteArray datagram;

    char buff[ONCE_SEND_SIZE];
    block = 0;
    quint16 nextBlock = block;
    while (true) {
        struct TFTP_DATA writeData;
        writeData.opCode = htons(TFTP_CODE_DATA);
        nextBlock++;
        writeData.block = htons(nextBlock);
        datagram.append((const char *)&writeData, sizeof(writeData));

        quint32 rdLenth = in.readRawData(buff, ONCE_SEND_SIZE);
        datagram.append(buff, rdLenth);

        udpSocket->writeDatagram(datagram.data(), datagram.size(),
                                 QHostAddress(remoteIP), remotePort);
        datagram.clear();

        //等待服务器回复数据
        quint32 cnt = 0;
        while (block != nextBlock) {
            QThread::msleep(10);
            cnt++;
            if (cnt >= 300) {
                return ERROR_TIMEOUT;
            }
        }

        if (rdLenth == 0) {
            break;
        }
    }

    return ERROR_NONE;
}

TFTP_WR_STATUS TFTP::getStatus()
{
    return wrStatus;
}

void TFTP::setRemoteIP(const QString &remoteIP)
{
    this->remoteIP = remoteIP;
}

void TFTP::setFilePath(const QString &filePath)
{
    this->filePath = filePath;
    QFileInfo info(filePath);
    this->fileName = info.fileName();
}

void TFTP::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        QHostAddress remoteAddress;
        quint16 remotePort;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(), &remoteAddress, &remotePort);

        qDebug() << "> 收到数据！";

        struct TFTP_ACK *reply = (struct TFTP_ACK *)datagram.data();     
        if (reply->opCode == htons(TFTP_CODE_ACK)) {
            if (reply->block == 0) {
                wrStatus = TFTP_STATUS_SENDING;
                qDebug() << "> 收到写请求回复！";
                qDebug() << "远程端口：" << remotePort;

                //根据TFTP协议：服务器使用新的端口发送回复数据
                this->remotePort = remotePort;
            } else if (wrStatus == TFTP_STATUS_SENDING) {
                qDebug() << "Block：" << reply->block;
                block = reply->block;
            }
        }
    }
}
