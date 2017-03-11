#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>

static bool streamReader_XML(const QString &fileName) {
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly) == false) {
        qDebug() << "Cnnot Find File!";
        return false;
    }

    QXmlStreamReader reader;
    reader.setDevice(&file);
    while (reader.atEnd() == false) {
        QXmlStreamReader::TokenType type = reader.readNext();
        if (type == QXmlStreamReader::StartDocument) {
            qDebug() << reader.documentVersion()
                     << reader.documentEncoding();
        } else if (type == QXmlStreamReader::StartElement) {
            qDebug() << "<" + reader.name() + ">";
            if (reader.attributes().hasAttribute(QStringLiteral("编号")) == true) {
                qDebug() << reader.attributes().value(QStringLiteral("编号"));
            }
        } else if (type == QXmlStreamReader::EndDocument) {
            qDebug() << "<" << reader.name() << ">";
        } else if ((type == QXmlStreamReader::Characters) &&
                   (reader.isWhitespace() == false)) {
            qDebug() << reader.text();
        }
    }

    if (reader.hasError() == true) {
        qDebug() << "error: " << reader.errorString();
    }

    file.close();

    return true;
}

static bool streamWriter_XML(const QString &fileName) {
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate) == false) {
        qDebug() << "Open File Error!";

        return false;
    }

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement(QStringLiteral("bookmark"));
    writer.writeAttribute("href", "www.baidu.com");
    writer.writeTextElement("title", QStringLiteral("百度"));
    writer.writeEndElement();
    writer.writeEndDocument();

    file.close();

    qDebug() << "Write Over!";

    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    streamWriter_XML("../xmlStream/test.xml");
    streamReader_XML("../xmlStream/test.xml");

    return a.exec();
}
