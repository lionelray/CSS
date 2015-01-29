#include "createitemdao.h"

CreateitemDao::CreateitemDao(QObject *parent) :
    QObject(parent)
{
}

bool CreateitemDao::additem(QStringList list)
{
    QString s;
    s = QString("insert into attend values(%1,'%2','%3','%4','%5','%6','%7')").arg(list.at(0).toInt()).arg(list.at(1)).arg(list.at(2)).arg(list.at(3)).arg(list.at(4)).arg(list.at(5)).arg(list.at(6));
    QSqlDatabase db = Db::getConnection();
    db.open();
    QSqlQuery query(db);
    bool flag = query.exec(s);
    if(!flag)
    {
        qDebug()<<query.lastError();
        return false;
    }
    else
    {
        return true;
    }
    db.close();
}

bool CreateitemDao::addcheck(QString sel, QString signid)
{
    QString s;
    s = "select s.sid from student s,dept d,major m where d.deptno=m.deptno and m.mid=s.mid and "+sel;
    QSqlDatabase db = Db::getConnection();
    db.open();
    QSqlQuery query(db);
    QSqlQuery insert(db);
    bool flag = query.exec(s);
    bool iflag;
    while(query.next())
    {
        s=QString("insert into sign(sid,aid) values(%1,%2)").arg(query.value(0).toInt()).arg(signid.toInt());
        iflag = insert.exec(s);
    }
    db.close();
    if(!flag && !iflag)
    {
        qDebug()<<query.lastError()<<"/n"<<insert.lastError();
        return false;
    }
    else
    {
        return true;
    }
}
//自动生成id
QString CreateitemDao::autoaid()
{
    QString aid = "10000001";
    QSqlDatabase db = Db::getConnection();
    db.open();
    QSqlQuery query(db);
    query.exec("select aid from attend order by aid desc limit 1");
    if(query.next())
    {
        aid = QString::number(query.value(0).toInt() +1);
        return aid;
    }
    else
    {
        return aid;
    }
}
