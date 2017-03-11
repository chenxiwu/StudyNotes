#ifndef MYSQL_H
#define MYSQL_H

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMessageBox>

static bool mysql_Connect(const QString &dbName) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("Sunyu520");
    db.setDatabaseName(dbName);

    if (db.open() == false) {
        QMessageBox::critical(0, "Cannot Open MySQL", "Connect MySQL Error!", QMessageBox::Close);

        return false;
    }

    return true;
}

static void mysql_InsertData() {
    QSqlQuery query;

    query.exec("create table info (id int primary key, name varchar(32))");
    query.exec("insert into info values(0, 'first')");
    query.exec("insert into info values(1, 'second')");
    query.exec("insert into info values(2, 'third')");
    query.exec("insert into info values(3, 'fourth')");
    query.exec("insert into info values(4, 'five')");
}

#endif // MYSQL_H
