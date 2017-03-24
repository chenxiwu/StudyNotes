#include "utils.h"
#include <QDateTime>
#include <QFile>
#include <QTextStream>

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
