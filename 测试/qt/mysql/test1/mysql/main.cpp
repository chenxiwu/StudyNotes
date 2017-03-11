#include <QCoreApplication>
#include <QDebug>
#include <QSqlDatabase>

class Test {
public:
    Test(){};
    ~Test(){};
    bool isSQL_Connect();

};

bool Test::isSQL_Connect()
{
   QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
   db.setHostName("localhost");
   db.setDatabaseName("mysql");
   db.setUserName("root");
   db.setPassword("123");

   if (db.open() == true) {
      qDebug() << "Database is establish!";

      return true;
   } else {
      qDebug() << "Database is error!";

       return false;
   }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Test t;
    t.isSQL_Connect();

    return a.exec();
}
