#include "mainwindow.h"
#include <QApplication>
#include <QtXml>
#include <QDebug>


bool readXML(const QString name) {
    QDomDocument doc;
    QFile file(name);

    if (file.open(QIODevice::ReadOnly) == false) {
        qDebug() << "Open File Error!";
        return false;
    }

    if (doc.setContent(&file) == false) {
        qDebug() << "Set Content Error!";
        file.close();

        return false;
    }
    file.close();

    /* XML说明 */
    QDomNode node = doc.firstChild();
    qDebug() << node.nodeName() << node.nodeValue();

    qDebug() << "==========";

    /* 根节点 */
    QDomElement docElem = doc.documentElement();
    node = docElem.firstChild();

    while (node.isNull() == false) {
        if (node.isElement() == true) {
            QDomElement e = node.toElement();
            qDebug() << qPrintable(e.tagName())
                     << qPrintable(e.attribute("id"));
        }
        node = node.nextSibling();
    }

    qDebug() << "==========";

    /* 子节点内容 */
    docElem = doc.documentElement();
    node = docElem.firstChild();

    while (node.isNull() == false) {
        if (node.isElement() == true) {
            QDomElement e = node.toElement();
            QDomNodeList list = e.childNodes();

            for (int i=0; i<list.count(); i++) {
                QDomNode n = list.at(i);
                if (n.isElement() == true) {
                    qDebug() << n.toElement().tagName()
                             << n.toElement().text();

                }
            }
        }

        node = node.nextSibling();
    }

    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    if (readXML("test.xml") == false) {
        qDebug() << "Cannot Find File!";
    }

    return a.exec();
}
