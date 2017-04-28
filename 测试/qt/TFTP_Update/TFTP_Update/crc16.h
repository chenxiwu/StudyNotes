#ifndef CRC16_H
#define CRC16_H

#include <QObject>

class CRC16 : public QObject
{
    Q_OBJECT
public:
    explicit CRC16(QObject *parent = 0);
    static quint16 get(quint16 initValue, quint8 *data, quint16 lenth);
signals:

public slots:
};

#endif // CRC16_H
