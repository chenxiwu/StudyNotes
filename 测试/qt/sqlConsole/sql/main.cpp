#include <QCoreApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QStringList>
#include <QSqlQuery>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //打印当前支持的数据库
    /*
    qDebug() << "Avail Driver:";
    QStringList drivers = QSqlDatabase::drivers();
    foreach (QString driver, drivers) {
        qDebug() << driver;
    }
    */
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //:memory:表示数据库建立在内存中，只在程序运行期间有效
    db.setDatabaseName(":memory:");
    if (db.open() == false) {
        return false;
    }

    QSqlQuery query;

    //创建表
    query.exec("create table student(id int primary key, name varchar)");

    //插入记录
    query.exec("insert into student values(1, 'zhang san')");
    query.exec("insert into student values(2, 'li shi')");
    query.exec("insert into student values(3, 'wang wu')");

    //查找记录
    query.exec("select id,name from student where id >= 2");

    //显示记录
    while (query.next()) {
        int value0 = query.value(0).toInt();
        QString value1 = query.value(1).toString();

        qDebug() << value0 << value1;
    }

    return a.exec();
}
