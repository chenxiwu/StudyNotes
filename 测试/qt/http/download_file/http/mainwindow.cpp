
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);
    ui->progressBar->hide();
    file = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startRequest(QUrl url)
{
    reply = manager->get(QNetworkRequest(url));
    connect(reply, SIGNAL(readyRead()),
            this, SLOT(http_ReadyRead()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(updateDataReadProgress(qint64,qint64)));
    connect(reply, SIGNAL(finished()),
            this, SLOT(http_Finished()));
}


void MainWindow::on_pushButton_clicked()
{
    url = ui->lineEdit->text();

    QFileInfo info(url.path());
    QString fileName(info.fileName());
    if (fileName.isEmpty() == true) {
        fileName = "index.html";
    }

    file = new QFile(fileName);
    if (file->open(QIODevice::WriteOnly | QIODevice::Truncate) == false) {
        delete file;
        file = NULL;

        return;
    }

    startRequest(url);
    ui->progressBar->setValue(0);
    ui->progressBar->show();
    ui->pushButton->setText(QStringLiteral("下载中..."));
}

void MainWindow::http_ReadyRead()
{
    if (file != NULL) {
        file->write(reply->readAll());
        file->flush();
    }
}

void MainWindow::updateDataReadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    ui->progressBar->setMaximum(bytesTotal);
    ui->progressBar->setValue(bytesReceived);
}

void MainWindow::http_Finished()
{
    ui->progressBar->hide();
    ui->pushButton->setText(QStringLiteral("下载"));
    file->close();
    delete file;
    file = NULL;

    reply->deleteLater();
    reply = NULL;
}
