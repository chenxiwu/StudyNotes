#include "tftp.h"
#include <QDebug>
#include <QDataStream>
#include <QMessageBox>

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
    writeReq.opCode = TFTP_CODE_WRQ;

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

    struct TFTP_DATA writedata;
    writedata.opCode = TFTP_CODE_DATA;
    QByteArray datagram;

    const quint32 ONCE_SEND_SIZE = 512;
    char buff[ONCE_SEND_SIZE];

    block = 0;
    quint16 nextBlock = block;
    while (true) {
        quint32 rdLenth = in.readRawData(buff, ONCE_SEND_SIZE);       

        nextBlock++;
        writedata.block = nextBlock;
        datagram.append((const char *)&writedata, sizeof(writedata));
        datagram.append(buff, rdLenth);

        udpSocket->writeDatagram(datagram.data(), datagram.size(),
                                 QHostAddress(remoteIP), remotePort);
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
                qDebug() << "Block" << reply->block;
                block = reply->block;
            }
        }
    }
}
