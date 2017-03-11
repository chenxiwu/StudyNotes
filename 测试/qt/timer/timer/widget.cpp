#include "widget.h"
#include "ui_widget.h"
#include "QTime"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    id1 = startTimer(1000);
    id2 = startTimer(2000);
    id3 = startTimer(10000);
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == id1) {
        //ui->label->setText(QString("%1").arg(qrand()%10));
        ui->label->move(qrand()%300, qrand()%300);
    } else if (event->timerId() == id2) {
        ui->label_2->setText(QString("Hello World!"));
    } else {
        qApp->quit();
    }
}
