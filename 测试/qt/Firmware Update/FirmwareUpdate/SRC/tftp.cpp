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
    qDebug() << "File Name：" << info.fileName();
    qDebug() << "File Size：" << info.size();

    udpSocket = new QUdpSocket(this);
    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()),
            Qt::DirectConnection);
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

    qDebug() << "Remote IP：" << remoteIP;
    qDebug() << "Remote Port："<< remotePort;
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
    QFileInfo info(filePath);
    quint64 curFileSize = 0;
    quint64 totalFileSize = info.size();

    const quint32 ONCE_SEND_SIZE = 512;
    QByteArray datagram;

    quint32 curProgress = 0;
    quint32 totalProgress = 100;
    emit sendProgress(curProgress);

    char buff[ONCE_SEND_SIZE];
    block = 0;
    quint16 nextBlock = block;
    bool sendDone = false;
    while (sendDone == false) {
        struct TFTP_DATA writeData;
        writeData.opCode = htons(TFTP_CODE_DATA);
        nextBlock++;
        writeData.block = htons(nextBlock);
        datagram.append((const char *)&writeData, sizeof(writeData));

        quint32 rdLenth = in.readRawData(buff, ONCE_SEND_SIZE);
        if (rdLenth < ONCE_SEND_SIZE) {
            sendDone = true;
        }
        datagram.append(buff, rdLenth);
        udpSocket->writeDatagram(datagram.data(), datagram.size(),
                                 QHostAddress(remoteIP), remotePort);
        curFileSize += rdLenth;
        curProgress = (float)curFileSize / totalFileSize * totalProgress;
        emit sendProgress(curProgress);

        datagram.clear();

        //等待服务器回复数据
        quint32 cnt = 0;
        while (block != nextBlock) {
            QThread::msleep(10);
            QCoreApplication::processEvents();

            cnt++;
            if (cnt >= 1000) {
                file.close();

                return ERROR_TIMEOUT;
            }
        }
    }

    file.close();

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

//        qDebug() << "> 收到数据！";

        struct TFTP_ACK *reply = (struct TFTP_ACK *)datagram.data();     
        if (reply->opCode == htons(TFTP_CODE_ACK)) {
            if (reply->block == 0) {
                //确定状态，防止收到服务器的重发包，将端口改变
                if (wrStatus == TFTP_STATUS_WRQ) {
                    wrStatus = TFTP_STATUS_SENDING;
                    qDebug() << "> 收到写请求回复！";
                    qDebug() << "远程端口：" << remotePort;

                    //根据TFTP协议：服务器使用新的端口发送回复数据
                    this->remotePort = remotePort;
                } else {
                    qDebug() << "收到重发包！";
                }
            } else if (wrStatus == TFTP_STATUS_SENDING) {
                block = htons(reply->block);
                qDebug() << "Block：" << block;
            }
        }
    }
}
