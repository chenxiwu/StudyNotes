#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTabWidget>
#include <QFileDialog>
#include <QtNetwork>
#include <QDialog>
#include <QMessageBox>

enum  PAGE_INDEX_ENUM{
    PAGE_AUTO = 0,
    PAGE_MANUAL,
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    curPage = PAGE_AUTO;

    setWindowTitle(QStringLiteral("控制器固件升级"));
    setFixedSize(this->width(), this->height());

    updateLocalIP();

    connect(ui->tabWidget, SIGNAL(currentChanged(int)),
            this, SLOT(tabWidgetCurrentChanged(int)));
    ui->tabWidget->setCurrentIndex(0);

    ui->lineEdit_AutoControllerIP->setText("192.168.0.234");
    ui->lineEdit_AutoControllerPort->setText("9999");

    ui->lineEdit_ManualControllerIP->setText
            (QStringLiteral("192.168.0.111"));
    ui->lineEdit_ManualControllerIP->setDisabled(true);
    ui->lineEdit_ManualControllerPort->setText
            (QStringLiteral("69"));
    ui->lineEdit_ManualControllerPort->setDisabled(true);

    ui->pushButton_Update->

    statusLabel = new QLabel();
    statusLabel->setMinimumSize(150, 24);
    statusLabel->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);
    statusLabel->setText(QStringLiteral("欢迎使用固件升级软件！"));
    ui->statusBar->addWidget(statusLabel);

    progressBar = new QProgressBar();
    progressBar->setMaximumSize(100, 16);
    ui->statusBar->addWidget(progressBar);
    progressBar->hide();

    QLabel *label = new QLabel(this);
    label->setFrameStyle(QFrame::Box | QFrame::Sunken);
    label->setText(QStringLiteral("<a href=\"http://www.hzxingao.com\">杭州鑫高</a>"));
    label->setTextFormat(Qt::RichText);
    label->setOpenExternalLinks(true);
    ui->statusBar->addPermanentWidget(label);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateLocalIP()
{
    ui->comboBox_LocalIP->clear();

    QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName());
    foreach(QHostAddress address, info.addresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol) {
            qDebug() << address.toString();

            ui->comboBox_LocalIP->addItem(address.toString());
        }
    }
}

bool MainWindow::isIP_SegmentEqual(QString ip1, QString subnetMask1,
                                   QString ip2, QString subnetMask2)
{
    QStringList ip_list1 = ip1.split('.');
    QStringList mask_list1 = subnetMask1.split('.');
    QStringList ip_list2 = ip2.split('.');
    QStringList mask_list2 = subnetMask2.split('.');

    if (ip_list1.count() != ip_list2.count()) {
        return false;
    }

    for (int i=0; i<ip_list1.count(); ++i) {
        int num1 = ip_list1.at(i).toInt() & mask_list1.at(i).toInt();
        int num2 = ip_list2.at(i).toInt() & mask_list2.at(i).toInt();
        if (num1 != num2) {
            return false;
        }
    }

    return true;
}

bool MainWindow::checkInput()
{
    if (ui->lineEdit_Firmware->text().isEmpty() == true) {
        QMessageBox::information(this, QStringLiteral("提示信息"),
                                 QStringLiteral("请先选择固件！"),
                                 QMessageBox::Ok);

        return false;
    }

    if (curPage == PAGE_AUTO) {
        if (ui->lineEdit_AutoControllerIP->text().isEmpty() == true) {
            QMessageBox::information(this, QStringLiteral("提示信息"),
                                     QStringLiteral("控制器IP不能为空！"),
                                     QMessageBox::Ok);

            return false;
        }

        QString ip1 = ui->comboBox_LocalIP->currentText();
        QString ip2 = ui->lineEdit_AutoControllerIP->text();
        if (isIP_SegmentEqual(ip1, "255.255.255.0", ip2, "255.255.255.0") == false) {
            QMessageBox::information(this, QStringLiteral("提示信息"),
                                     QStringLiteral("本地IP与控制器IP不在同一个网段！"),
                                     QMessageBox::Ok);

            return false;
        }

        if (ui->lineEdit_AutoControllerPort->text().isEmpty() == true) {
            QMessageBox::information(this, QStringLiteral("提示信息"),
                                     QStringLiteral("控制器端口不能为空！"),
                                     QMessageBox::Ok);

            return false;
        }
    }

    return true;
}


void MainWindow::on_pushButton_Open_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                       QStringLiteral("选择升级文件"));
    if (filePath.isEmpty() == false) {
        ui->lineEdit_Firmware->setText(filePath);
    }
}

void MainWindow::on_pushButton_Update_clicked()
{
    if (checkInput() == false) {
        return;
    }
}

void MainWindow::tabWidgetCurrentChanged(int index)
{
    curPage = index;
}
