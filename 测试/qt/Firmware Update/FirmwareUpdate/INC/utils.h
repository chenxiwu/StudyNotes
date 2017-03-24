#ifndef UTILS_H
#define UTILS_H

#include <QMainWindow>

const QString LOG_NAME = "log.txt";

quint16 htons(quint16 n);
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

#endif // UTILS_H
