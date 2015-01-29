#include "guestdao.h"
#include "db.h"
GuestDao::GuestDao(QObject *parent) :
    QObject(parent)
{
    model = NULL;
}

//显示所有用户
QSqlQueryModel *GuestDao::showall()
{
    QSqlDatabase db = Db::getConnection();
    db.open();
    if(model == NULL)
    {
        model = new QSqlQueryModel;
    }

    model->setQuery(QString(
                    "select g.gname,g.identify,d.deptname,g.mark from guest g "
                    "inner join dept d on g.deptno=d.deptno"),db);

    model->setHeaderData(0,Qt::Horizontal,"用户名");
    model->setHeaderData(1,Qt::Horizontal,"身份");
    model->setHeaderData(2,Qt::Horizontal,"部门");
    model->setHeaderData(3,Qt::Horizontal,"备注");

    db.close();

    return model;
}

QSqlQueryModel *GuestDao::search(QString info, QString meth)
{
    QSqlDatabase db = Db::getConnection();
    if(model == NULL)
    {
        model = new QSqlQueryModel;
    }
    model->setQuery(QString(
                        "select g.gname,g.identify,d.deptname,g.mark from guest g"
                        " inner join dept d on g.deptno=d.deptno where %1 like '%%2%'"
                        ).arg(meth).arg(info),db);

    model->setHeaderData(0,Qt::Horizontal,"用户名");
    model->setHeaderData(1,Qt::Horizontal,"身份");
    model->setHeaderData(2,Qt::Horizontal,"部门");
    model->setHeaderData(3,Qt::Horizontal,"备注");

    return model;
}

bool GuestDao::delguest(QString gname)
{
    QSqlDatabase db = Db::getConnection();
    QSqlQuery query(db);
    bool flag = query.exec(QString("delete from guest where gname = '%1'").arg(gname));

    if (query.lastError().isValid())
    {
        Error = "Error:" + QString::number(query.lastError().number());
        Error += "\n" + query.lastError().text();
    }

    return flag;
}

bool GuestDao::insert(QStringList list)
{
    QSqlDatabase db = Db::getConnection();
    db.open();
    QSqlQuery query(db);
    query.exec(QString("select deptno from dept where deptname='%1'").arg(list.at(3)));
    query.next();
    int dept = query.value(0).toInt();
    QString s = QString("insert into guest values('%1','%2','%3','%4','%5')"
                        ).arg(list.at(0)).arg(list.at(1)).arg(list.at(2)).arg(dept).arg(list.at(4));
    bool flag = query.exec(s);

    if (query.lastError().isValid())
    {
        Error = "Error:" + QString::number(query.lastError().number());
        Error += "\n" + query.lastError().text();
    }

    db.close();
    return flag;
}

bool GuestDao::resetpwd(QString gname,QString pwd)
{
    QSqlDatabase db = Db::getConnection();
    db.open();
    QSqlQuery query(db);
    bool flag = query.exec(QString(
                               "update guest set password='%1' where gname='%2'"
                               ).arg(pwd).arg(gname));
    return flag;
}

QStringList GuestDao::dept()
{
    QSqlDatabase db = Db::getConnection();
    db.open();
    QSqlQuery query(db);
    query.exec("select deptname from dept");
    QStringList dept;
    while(query.next())
    {
        dept<<query.value(0).toString();
    }
    db.close();
    return dept;
}

QString GuestDao::getoldpwd(QString gname)
{
    QSqlDatabase db = Db::getConnection();
    db.open();
    QSqlQuery query(db);
    query.exec("select password from guest where gname='"+ gname +"'");
    query.next();
    QString pwd = query.value(0).toString();
    db.close();
    return pwd;
}
