#ifndef DEBUGTHREAD_H
#define DEBUGTHREAD_H

#include <QObject>
#include <QThread>

class DebugThread : public QObject, QThread
{
    Q_OBJECT
public:
    explicit DebugThread(QObject *parent = 0);

signals:

public slots:

protected:
    void run();
};

#endif // DEBUGTHREAD_H
