#include "debugthread.h"
#include "dialogdebug.h"
#include <QDebug>

void DebugThread::run()
{
    emit Load_UI();

    while (1) {
        emit refresh();
        msleep(1000);
    }
}
