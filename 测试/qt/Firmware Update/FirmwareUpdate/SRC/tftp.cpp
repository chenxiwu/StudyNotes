#include "tftp.h"

void TFTP::tftp_Init(QString fileName)
{
    udpSocket = new QUdpSocket(this);

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));

    /* 发送写请求 */
    auto wReq = QByteArray();
    wReq.append("0");
    wReq.append(QString::number(TFTP_CODE_WRQ, 10));
    wReq.append(fileName);
    wReq.append("0");
    wReq.append("octet");
    wReq.append("0");

    udpSocket->writeDatagram(wReq.data(), wReq.size(),
                             QHostAddress::Broadcast, 69);
}

void TFTP::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());


    }
}
