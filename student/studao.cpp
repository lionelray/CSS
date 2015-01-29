#include "studao.h"
#include "db.h"
StuDao::StuDao(QObject *parent) :
    QObject(parent)
{
}
//查询所有学院
QStringList StuDao::dept()
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

//查询某学院的所有专业
QStringList StuDao::major(QString dname)
{
    QSqlDatabase db = Db::getConnection();
    db.open();
    QSqlQuery query(db);
    query.exec("select mname from major m,dept d where m.deptno=d.deptno and d.deptname='"
               + dname +"'");
    QStringList major;
    while(query.next())
    {
        major<<query.value(0).toString();
    }
    db.close();
    return major;
}

bool StuDao::addstu(QStringList stuinfo)
{
    QSqlDatabase db = Db::getConnection();
    db.open();
    QSqlQuery query(db);
    query.exec(QString("select mid from major where mname = '%1'").arg(stuinfo.at(2)));
    query.next();
    int sid = stuinfo.at(0).toInt();
    int major = query.value(0).toInt();
    int grade = stuinfo.at(3).toInt();
    int cls = stuinfo.at(4).toInt();

    QString s = QString("insert into student values(%1,'%2',%3,%4,%5,'%6','%7','%8')"
                        ).arg(sid).arg(stuinfo.at(1)).arg(major).arg(grade).arg(cls).arg(stuinfo.at(5)).arg(stuinfo.at(6)).arg(stuinfo.at(7));
    bool flag = query.exec(s);
    if(!flag)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool StuDao::delstu(int sid)
{
    QSqlDatabase db = Db::getConnection();
    QSqlQuery query(db);
    QString sSQL = QString("delete from student where sid = %1").arg(sid);
    bool flag = query.exec(sSQL);

    if (query.lastError().isValid())
    {
        Error = "Error:" + QString::number(query.lastError().number());
        Error += "\n" + query.lastError().text();
    }

    return flag;
}
//自动生成学号
QString StuDao::autosid(int grade)
{
    QString sid = QString::number(grade)+"1001";
    QSqlDatabase db = Db::getConnection();
    QSqlQuery query(db);
    QString s = QString(
                "select sid from student where grade=%1 order by sid desc limit 1"
                ).arg(grade);
    query.exec(s);
    if(query.next())
    {
        sid = QString::number(query.value(0).toInt()+1);
    }
    return sid;
}

QSqlQueryModel *StuDao::search(QString info, QString meth)
{
    QSqlDatabase db = Db::getConnection();
    db.open();
    if(model == NULL)
    {
        model = new QSqlQueryModel;
    }
    QString s = QString(
                "select s.sid,s.sname,d.deptname,m.mname,s.grade,s.class,s.mark"
                " from student s,major m,dept d where m.deptno=d.deptno and s.mid=m.mid and %1 like '%%2%'"
                ).arg(meth).arg(info);

    model->setQuery(s,db);
    model->setHeaderData(0,Qt::Horizontal,"学号");
    model->setHeaderData(1,Qt::Horizontal,"姓名");
    model->setHeaderData(2,Qt::Horizontal,"学院");
    model->setHeaderData(3,Qt::Horizontal,"专业");
    model->setHeaderData(4,Qt::Horizontal,"年级");
    model->setHeaderData(5,Qt::Horizontal,"班级");
    model->setHeaderData(6,Qt::Horizontal,"备注");
    db.close();
    return model;
}

QSqlQueryModel *StuDao::showall()
{
    QSqlDatabase db = Db::getConnection();
    db.open();
    if(model == NULL)
    {
        model = new QSqlQueryModel;
    }
    QString s = QString(
                "select s.sid,s.sname,d.deptname,m.mname,s.grade,s.class,"
                "s.mark from student s,major m,dept d where m.deptno=d.deptno and s.mid=m.mid");
    model->setQuery(s,db);
    model->setHeaderData(0,Qt::Horizontal,"学号");
    model->setHeaderData(1,Qt::Horizontal,"姓名");
    model->setHeaderData(2,Qt::Horizontal,"学院");
    model->setHeaderData(3,Qt::Horizontal,"专业");
    model->setHeaderData(4,Qt::Horizontal,"年级");
    model->setHeaderData(5,Qt::Horizontal,"班级");
    model->setHeaderData(6,Qt::Horizontal,"备注");
    db.close();
    return model;
}
