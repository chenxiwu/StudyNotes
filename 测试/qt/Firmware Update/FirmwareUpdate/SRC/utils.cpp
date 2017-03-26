#include "utils.h"
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include "crc16.h"
#include <QHostInfo>

quint16 htons(quint16 n)
{
    return ((n & 0xff) << 8) | ((n & 0xff00) >> 8);
}

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    (void)context;

    QString text;

//    QDateTime time = QDateTime::currentDateTime();
//    QString timeStr = time.toString("yyyy-MM-dd hh:mm:ss");

    switch (type) {
    //调试信息提示
    case QtDebugMsg:
          text = QString("[DEBUG] %1").arg(msg);
          break;

    //一般的warning提示
    case QtWarningMsg:
          text = QString("[WARNING] %1").arg(msg);
    break;
    //严重错误提示
    case QtCriticalMsg:
          text = QString("[CRITICAL] %1").arg(msg);
    break;
    //致命错误提示
    case QtFatalMsg:
          text = QString("[FATAL] %1").arg(msg);
          abort();
    default:
    break;
    }

    QFile outFile(LOG_NAME);
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream out(&outFile);
    out << text << endl;
}

void CMD_SystemUpdate(QByteArray &cmd, bool isUpdate)
{
    UDP_PROTECOL_HEAD_TypeDef head;
    head.start = 0x1B;
    head.addr = 0;
    head.index = 0x21;
    head.rsv1 = 0;
    head.size = sizeof(CMD_UPDATE_TypeDef);
    head.rsv2 = 0;
    head.token = 0x0E;
    cmd.append((const char *)&head, sizeof(head));

    CMD_UPDATE_TypeDef body;
    body.cmd = 0x0011;
    body.update = isUpdate;
    cmd.append((const char *)&body, sizeof(body));

    UDP_PROTECOL_TAIL_TypeDef tail;
    tail.crc = CRC16::get(0, (quint8 *)cmd.data(), cmd.size());
    tail.end = 0x16;
    cmd.append((const char *)&tail, sizeof(tail));
}

void getLocalIP(QVector<QHostAddress> &localIP)
{
    QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName());
    foreach(QHostAddress address, info.addresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol) {
            localIP.append(address);
        }
    }
}

bool isInSubnet(QString ip1, QString subnetMask1,
                       QString ip2, QString subnetMask2)
{
    QStringList ip_list1 = ip1.split('.');
    QStringList mask_list1 = subnetMask1.split('.');
    QStringList ip_list2 = ip2.split('.');
    QStringList mask_list2 = subnetMask2.split('.');

    if (ip_list1.count() != ip_list2.count()) {
        return false;
    }

    for (int i=0; i<ip_list1.count(); ++i) {
        int num1 = ip_list1.at(i).toInt() & mask_list1.at(i).toInt();
        int num2 = ip_list2.at(i).toInt() & mask_list2.at(i).toInt();
        if (num1 != num2) {
            return false;
        }
    }

    return true;
}
