#include "dialogdebug.h"
#include "ui_dialogdebug.h"
#include "QFile"
#include <QDebug>
#include "utils.h"
#include <QString>
#include <QTimer>


DialogDebug::DialogDebug(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDebug)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
            this, SLOT(timeoutNotify()));
    timer->start(1000);

    connect(ui->textBrowser, SIGNAL(cursorPositionChanged()),
            this, SLOT(autoScroll()));
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

void DialogDebug::timeoutNotify()
{
    QFile file(LOG_NAME);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      return;

    QTextStream in(&file);
    QString source = ui->textBrowser->toPlainText();
    QString newText = in.readAll();

    if (source != newText) {
        ui->textBrowser->clear();
        ui->textBrowser->setText(newText);
    }
}
