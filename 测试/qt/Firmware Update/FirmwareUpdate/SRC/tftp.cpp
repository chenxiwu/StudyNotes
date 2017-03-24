#include "tftp.h"
#include <QDebug>
#include <QDataStream>
#include <QMessageBox>
#include <QtEndian>
#include "utils.h"


TFTP::TFTP(const QString remoteIP)
{
    this->remoteIP = remoteIP;
    this->remotePort = 69;

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

void TFTP::writeReq(const QString &fileName)
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

bool TFTP::writeFile(const QString &filePath)
{
    /*
        2 bytes     2 bytes      n bytes
        ----------------------------------
        | Opcode |   Block #  |   Data     |
        ----------------------------------
    */
    if (wrStatus != TFTP_STATUS_SENDING) {
        QMessageBox::information(this, QStringLiteral("提示信息"),
                                 QStringLiteral("内部状态错误！"),
                                 QMessageBox::Ok);

        return false;
    }

    QFile file(filePath);
    if (file.open(QFile::ReadOnly) == false) {
        QMessageBox::information(this, QStringLiteral("提示信息"),
                                 QStringLiteral("文件打开错误！"),
                                 QMessageBox::Ok);

        return false;
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
            QThread::msleep(1);
            cnt++;
            if (cnt >= 3000) {
                QMessageBox::information(this, QStringLiteral("提示信息"),
                                        QStringLiteral("发送超时！"),
                                        QMessageBox::Ok);
                return false;
            }
        }

        if (rdLenth == 0) {
            break;
        }
    }

    return true;
}

TFTP_WR_STATUS TFTP::getStatus()
{
    return wrStatus;
}

void TFTP::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        QHostAddress remoteAddress;
        quint16 remotePort;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(), &remoteAddress, &remotePort);

        struct TFTP_ACK *reply = (struct TFTP_ACK *)datagram.data();
        if (reply->opCode == TFTP_CODE_ACK) {
            if (wrStatus == TFTP_STATUS_WRQ) {
                if (reply->block == 0) {
                    wrStatus = TFTP_STATUS_SENDING;
                    qDebug() << "Start Send...";

                    //根据TFTP协议：服务器使用新的端口发送回复数据
                    this->remotePort = remotePort;
                }
            } else if (wrStatus == TFTP_STATUS_SENDING) {
                qDebug() << "Block：" << reply->block;
                block = reply->block;
            }
        }
    }
}
