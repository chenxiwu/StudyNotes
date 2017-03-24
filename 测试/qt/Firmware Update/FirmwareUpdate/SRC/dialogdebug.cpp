#include "dialogdebug.h"
#include "ui_dialogdebug.h"
#include "QFile"
#include <QDebug>
#include "utils.h"
#include <QString>

DialogDebug::DialogDebug(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDebug)
{
    ui->setupUi(this);

    connect(ui->textBrowser, SIGNAL(cursorPositionChanged()),
            this, SLOT(autoScroll()));

    QFile file(LOG_NAME);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      return;

    QTextStream in(&file);
    ui->textBrowser->setText(in.readAll());
}

DialogDebug::~DialogDebug()
{
    delete ui;
}

void DialogDebug::autoScroll()
{
    QTextCursor cursor =  ui->textBrowser->textCursor();

    cursor.movePosition(QTextCursor::End);

    ui->textBrowser->setTextCursor(cursor);
}

void DialogDebug::on_pushButton_Clear_clicked()
{
    QFile::remove(LOG_NAME);
    ui->textBrowser->clear();
}
