#ifndef DEBUGTHREAD_H
#define DEBUGTHREAD_H

#include <QThread>

class DebugThread : public QThread
{
    Q_OBJECT
public:
    DebugThread();

signals:
    void Load_UI();
    void refresh();

public slots:

protected:
    void run();
};

#endif // DEBUGTHREAD_H
