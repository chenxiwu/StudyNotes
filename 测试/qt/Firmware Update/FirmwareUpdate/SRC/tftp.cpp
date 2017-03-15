#include "tftp.h"

void TFTP::tftp_Init()
{
    udpSocket = new QUdpSocket(this);

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));

}

void TFTP::tftp_WriteReq(QString fileName)
{
    const QString NODE = "octet";

    auto wReq = QByteArray();
    wReq.append("0" + QString::number(TFTP_CODE_WRQ, 10));
    wReq.append(fileName + "0");
    wReq.append(NODE + "0");

    udpSocket->writeDatagram(wReq.data(), wReq.size(),
                             QHostAddress::Broadcast, 69);
}

bool TFTP::tftp_WriteDatagram(QByteArray datagram)
{
    ;
}

void TFTP::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());

        struct TFTP_ACK *reply = (struct TFTP_ACK *)datagram.data();
        if (reply->opCode == TFTP_CODE_ACK) {
            qDebug() << "Reply Block:" + reply->block;
        }
    }
}
