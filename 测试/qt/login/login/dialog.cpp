#include "dialog.h"
#include "ui_dialog.h"
#include "QMessageBox"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_loginButton_clicked()
{
    //忽略空白字符、忽略大小写
    if ((ui->userLineEdit->text().trimmed().compare(tr("SY"), Qt::CaseInsensitive) == 0) &&
        (ui->pwdLineEdit->text() == tr("123")))
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this, tr("warning"),
                             tr("User Name Or Password Error!"),
                             QMessageBox::Ok);
        ui->userLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->userLineEdit->setFocus();

    }
}
