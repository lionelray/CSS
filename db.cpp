#include "db.h"

QSqlDatabase Db::db = QSqlDatabase::addDatabase("QMYSQL","mysql");
bool Db::flag = false;
Db::Db(QObject *parent) :
    QObject(parent)
{
}

QSqlDatabase Db::getConnection()
{
    if(flag == false)
    {
        db.setHostName("127.0.0.1");
        db.setPort(3306);
        db.setDatabaseName("css");
        db.setUserName("root");
        db.setPassword("mysql");
        flag = true;
    }
    else
    {
        db=QSqlDatabase::database("mysql");
    }
    return db;
}
