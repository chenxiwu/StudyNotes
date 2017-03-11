#include "widget.h"
#include "ui_widget.h"
#include <QMouseEvent>
#include <QKeyEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    ui->pushButton->setText(QStringLiteral("(%1,%2)").arg(event->x()).arg(event->y()));
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    int x = ui->pushButton->x();
    int y = ui->pushButton->y();

    switch (event->key())
    {
    case Qt::Key_W:
        ui->pushButton->move(x, y-10);
        break;
    case Qt::Key_S:
        ui->pushButton->move(x, y+10);
        break;
    case Qt::Key_A:
        ui->pushButton->move(x-10, y);
        break;
    case Qt::Key_D:
        ui->pushButton->move(x+10, y);
        break;

    }
}
