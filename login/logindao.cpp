#include "logindao.h"
#include "db.h"
#include <QtSql/QSqlDatabase>
extern QString identify;

LoginDao::LoginDao(QObject *parent) :
    QObject(parent)
{
}

int LoginDao::verify(QString name, QString pwd)
{
    QSqlDatabase db = Db::getConnection();
    QSqlQuery query(db);
    bool dbOpen = db.open();
    if(dbOpen ==false)
    {
        return 3;
    }
    else
    {
        QString s = QString("select password,identify from guest where gname = '%1'").arg(name);
        query.exec(s);
        bool flag = query.next();
        if(!flag)
        {
            return 2;//查无此人
        }
        else
        {
            QString dbpwd = query.value(0).toString();
            if(pwd == dbpwd)
            {
                identify = query.value(1).toString();
                return 0;//验证通过
            }
            else return 1;//密码错误
        }
    }
}
