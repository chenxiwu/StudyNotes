#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtXml>
#include <QFile>
#include <QDebug>
#include <QDomDocument>

bool MainWindow::create_XML(const QString fileName) {
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate) == false) {
        return false;
    }

    QDomDocument doc;
    QDomProcessingInstruction instruction =
            doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);

    //添加根节点
    QDomElement root = doc.createElement(QStringLiteral("书库"));
    doc.appendChild(root);

    //添加子节点1
    QDomElement book = doc.createElement(QStringLiteral("图书"));
    QDomAttr id = doc.createAttribute(QStringLiteral("编号"));
    id.setValue("1");
    book.setAttributeNode(id);

    QDomElement bookName = doc.createElement(QStringLiteral("书名"));
    bookName.appendChild(doc.createTextNode(QStringLiteral("Linux")));
    book.appendChild(bookName);

    QDomElement author = doc.createElement(QStringLiteral("作者"));
    author.appendChild(doc.createTextNode(QStringLiteral("Linus Torvalds")));
    book.appendChild(author);

    root.appendChild(book);

    //添加子节点2
    book = doc.createElement(QStringLiteral("图书"));
    id = doc.createAttribute(QStringLiteral("编号"));
    id.setValue("2");
    book.setAttributeNode(id);

    bookName = doc.createElement(QStringLiteral("书名"));
    bookName.appendChild(doc.createTextNode(QStringLiteral("Windows")));
    book.appendChild(bookName);

    author = doc.createElement(QStringLiteral("作者"));
    author.appendChild(doc.createTextNode(QStringLiteral("比尔·盖茨")));
    book.appendChild(author);

    root.appendChild(book);

    //使用流保存文件
    QTextStream outStream(&file);
    doc.save(outStream, 4);
    file.close();

    return true;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    create_XML(QStringLiteral("my.xml"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::read_XML(const QString fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly) == false) {
        return false;
    }
    QDomDocument doc;
    if (doc.setContent(&file) == false) {
        file.close();
        return false;
    }
    file.close();

    //根元素
    QDomElement docElem = doc.documentElement();
    QDomNode node = docElem.firstChild();
    while (node.isNull() == false) {
        if (node.isElement() == true) {
            QDomElement e = node.toElement();
            ui->listWidget->addItem(e.tagName() + e.attribute(QStringLiteral("编号")));

            QDomNodeList list = e.childNodes();
            for (int i=0; i<list.count(); ++i) {
                QDomNode node = list.at(i);
                if (node.isElement() == true) {
                    ui->listWidget->addItem("    " + node.toElement().tagName()
                                            + ":" + node.toElement().text());
                }
            }
        }

        node = node.nextSibling();
    }

    return true;
}

void MainWindow::do_XML(const QString fileName, const QString operate)
{
    ui->listWidget->clear();
    ui->listWidget->addItem(QStringLiteral("未发现相关内容！"));

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly) == false) {
        return;
    }

    QDomDocument doc;
    if (doc.setContent(&file) == false) {
        file.close();
        return;
    }
    file.close();

    QDomNodeList list = doc.elementsByTagName(QStringLiteral("图书"));
    for (int i=0; i<list.count(); ++i) {
        QDomElement e = list.at(i).toElement();
        if (e.attribute(QStringLiteral("编号")) == ui->lineEdit_id->text()) {
            if (operate == "delete") {
                QDomElement rootNode = doc.documentElement();
                rootNode.removeChild(list.at(i));

                QFile file(fileName);
                if (file.open(QIODevice::WriteOnly | QIODevice::Truncate) == false) {
                    return;
                }
                QTextStream outStream(&file);
                doc.save(outStream, 4);
                file.close();
                ui->listWidget->clear();
                ui->listWidget->addItem(QStringLiteral("删除成功！"));
            } else if (operate == "update") {
                if (ui->lineEdit_author->text() == NULL) {
                    return;
                } else if (ui->lineEdit_bookName->text() == NULL) {
                    return;
                }

                QDomNodeList list = e.childNodes();
                list.at(0).toElement().firstChild().setNodeValue(ui->lineEdit_bookName->text());
                list.at(1).toElement().firstChild().setNodeValue(ui->lineEdit_author->text());

                QFile file(fileName);
                if (file.open(QIODevice::WriteOnly | QIODevice::Truncate) == false) {
                    return;
                }
                QTextStream outStream(&file);
                doc.save(outStream, 4);
                file.close();
                ui->listWidget->clear();
                ui->listWidget->addItem(QStringLiteral("更新成功！"));
            } else if (operate == "find") {
                ui->listWidget->clear();
                ui->listWidget->addItem(e.tagName() + e.attribute(QStringLiteral("编号")));
                QDomNodeList list = e.childNodes();
                for (int i=0; i<list.count(); ++i) {
                    QDomNode node = list.at(i);
                    if (node.isElement() == true) {
                        ui->listWidget->addItem("    " + node.toElement().tagName() + ":" +
                                            node.toElement().text());
                    }
                }

            }
        }
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->listWidget->clear();
    read_XML("my.xml");
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->listWidget->clear();
    ui->listWidget->addItem(QStringLiteral("无法添加！"));

    QFile file("my.xml");
    if (file.open(QIODevice::ReadOnly) == false) {
        return;
    }
    QDomDocument doc;
    if (doc.setContent(&file) == false) {
        file.close();

        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    QString lastNum = root.lastChildElement(QStringLiteral("图书")).attribute(QStringLiteral("编号"));
    int newNum = lastNum.toInt() + 1;

    QDomElement book = doc.createElement(QStringLiteral("图书"));
    QDomAttr id = doc.createAttribute(QStringLiteral("编号"));
    id.setValue(QString::number(newNum));
    book.setAttributeNode(id);

    QDomElement bookName = doc.createElement(QStringLiteral("书名"));
    QString bookNameText = ui->lineEdit_bookName->text();
    if (bookNameText == NULL) {
        return;
    }
    bookName.appendChild(doc.createTextNode((bookNameText)));
    book.appendChild(bookName);

    QDomElement author = doc.createElement(QStringLiteral("作者"));
    QString authorText = ui->lineEdit_author->text();
    if (authorText == NULL) {
        return;
    }
    author.appendChild(doc.createTextNode(authorText));
    book.appendChild(author);

    root.appendChild(book);

    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate) == false) {
        return;
    }
    QTextStream outStream(&file);
    doc.save(outStream, 4);
    file.close();

    ui->listWidget->clear();
    ui->listWidget->addItem(QStringLiteral("添加成功！"));
    ui->lineEdit_bookName->clear();
    ui->lineEdit_author->clear();
}

void MainWindow::on_pushButton_2_clicked()
{
    do_XML("my.xml", "delete");
}

void MainWindow::on_pushButton_3_clicked()
{
    do_XML("my.xml", "update");
}

void MainWindow::on_pushButton_clicked()
{
    do_XML("my.xml", "find");
}
