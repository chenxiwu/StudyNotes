#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "QMessageBox"
#include "QFileDialog"
#include "QFile"
#include "QTextStream"
#include "QLineEdit"
#include "QPushButton"
#include "QLabel"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isUntitled = true;
    curFile = QStringLiteral("未命名.txt");
    setWindowTitle(curFile);

    findDlg = new QDialog(this);
    findDlg->setWindowTitle(QStringLiteral("查找"));
    findLineEdit = new QLineEdit();
    QPushButton *button = new QPushButton(QStringLiteral("查找下一个"), this);
    QVBoxLayout *layout = new QVBoxLayout(findDlg);
    layout->addWidget(findLineEdit);
    layout->addWidget(button);
    connect(button, SIGNAL(clicked()), this, SLOT(showFindText()));

    //提示信息
    statusLabel = new QLabel();
    statusLabel->setMinimumSize(150, 24);
    statusLabel->setFrameShape(QFrame::WinPanel);
    statusLabel->setFrameShadow(QFrame::Sunken);
    statusLabel->setText(QStringLiteral("欢迎来到QT！"));
    ui->statusBar->addWidget(statusLabel);

    QLabel *permannent = new QLabel(this);
    permannent->setFrameStyle(QFrame::Box | QFrame::Sunken);
    permannent->setText(QStringLiteral("<a href=\"http://www.baidu.com\">百度</a>"));
    permannent->setTextFormat(Qt::RichText);
    permannent->setOpenExternalLinks(true);
    ui->statusBar->addPermanentWidget(permannent);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile()
{
    if (maybeSave() == true)
    {
        isUntitled = true;
        curFile = QStringLiteral("未保存.txt");
        setWindowTitle(curFile);
        ui->textEdit->clear();
        ui->textEdit->setVisible(true);
    }
}

bool MainWindow::maybeSave()
{
    if (ui->textEdit->document()->isModified() == true)
    {
        QMessageBox m;
        m.setText(curFile + QStringLiteral(" 尚未保存，是否保存？"));
        QPushButton *yesBtn = m.addButton(QStringLiteral("是（&Y）"), QMessageBox::YesRole);
        m.addButton(QStringLiteral("否（&N）"), QMessageBox::NoRole);
        QPushButton *cancelBtn = m.addButton(QStringLiteral("取消"), QMessageBox::RejectRole);
        m.exec();

        if ((QPushButton *)m.clickedButton() == yesBtn) {
            return save();
        } else if ((QPushButton *)m.clickedButton() == cancelBtn) {
            return false;
        }
    }

    return true;
}

bool MainWindow::save()
{
    if (isUntitled == true) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, QStringLiteral("另存为"), curFile);

    return saveFile(fileName);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);

    if (file.open(QFile::WriteOnly | QFile::Text) == false) {
        QMessageBox::warning(this, QStringLiteral("多文档编辑器"), QStringLiteral("无法写入文件 %1：\n %2")
                             .arg(fileName).arg(file.errorString()));
        return false;
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);

    QTextStream out(&file);
    out << ui->textEdit->toPlainText();

    QApplication::restoreOverrideCursor();

    isUntitled = false;
    curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);

    return true;
}


void MainWindow::on_action_N_triggered()
{
    newFile();
}

void MainWindow::on_action_S_triggered()
{
    save();
}

void MainWindow::on_action_A_triggered()
{
    saveAs();
}

void MainWindow::showFindText()
{
    QString str = findLineEdit->text();
    if (ui->textEdit->find(str, QTextDocument::FindBackward) == false) {
        QMessageBox::warning(this, QStringLiteral("查找"), QStringLiteral("找不到%1").arg(str));
    }
}

void MainWindow::on_action_F_triggered()
{
    findDlg->exec();

}
