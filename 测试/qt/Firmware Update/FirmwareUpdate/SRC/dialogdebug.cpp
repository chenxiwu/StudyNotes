#include "dialogdebug.h"
#include "ui_dialogdebug.h"

DialogDebug::DialogDebug(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDebug)
{
    ui->setupUi(this);
}

DialogDebug::~DialogDebug()
{
    delete ui;
}
