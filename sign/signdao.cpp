#include "signdao.h"

SignDao::SignDao(QObject *parent) :
    QObject(parent)
{
}

QSqlQueryModel *SignDao::showall(int aid)
{
    QSqlDatabase db = Db::getConnection();
    QSqlQueryModel *model;
    db.open();
    if(model == NULL)
    {
        model = new QSqlQueryModel;
    }
    QString s = QString("select s.sid,s.sname,d.deptname,m.mname,s.grade,s.class,c.cstat from student s,major m,dept d,sign c where m.deptno=d.deptno and s.mid=m.mid and c.sid=s.sid and c.aid=%1").arg(aid);
    model->setQuery(s,db);
    model->setHeaderData(0,Qt::Horizontal,"学号");
    model->setHeaderData(1,Qt::Horizontal,"姓名");
    model->setHeaderData(2,Qt::Horizontal,"学院");
    model->setHeaderData(3,Qt::Horizontal,"专业");
    model->setHeaderData(4,Qt::Horizontal,"年级");
    model->setHeaderData(5,Qt::Horizontal,"班级");
    model->setHeaderData(6,Qt::Horizontal,"签到状态");
    db.close();
    return model;
}

QSqlQueryModel *SignDao::showallSign()
{
    QSqlDatabase db = Db::getConnection();
    QSqlQueryModel *model;
    db.open();
    if(model == NULL)
    {
        model = new QSqlQueryModel;
    }
    QString s = QString("select a.* from attend a");
    model->setQuery(s,db);
    model->setHeaderData(0,Qt::Horizontal,"编号");
    model->setHeaderData(1,Qt::Horizontal,"名称");
    model->setHeaderData(2,Qt::Horizontal,"地点");
    model->setHeaderData(3,Qt::Horizontal,"时间");
    model->setHeaderData(4,Qt::Horizontal,"负责人");
    model->setHeaderData(5,Qt::Horizontal,"签到范围");
    model->setHeaderData(6,Qt::Horizontal,"备注");
    db.close();
    return model;

}

bool SignDao::changeStat(int sid, int aid, QString stat)
{
    QSqlDatabase db = Db::getConnection();
    QSqlQuery query(db);
    bool flag = query.exec(QString("update sign set cstat='%1' where sid = %2 and aid=%3").arg(stat).arg(sid).arg(aid));
    return flag;
}

bool SignDao::delsign(int aid)
{
    QSqlDatabase db = Db::getConnection();
    QSqlQuery query(db);
    bool flag = query.exec(QString("delete from attend where aid = %1").arg(aid));
    return flag;
}

QStringList SignDao::showStuSign(int sid, int aid)
{
    QSqlDatabase db = Db::getConnection();
    QSqlQuery query(db);
    QString s = QString("select s.sid,s.sname,d.deptname,m.mname,s.grade,s.class,c.cstat from student s,major m,dept d,sign c where m.deptno=d.deptno and s.mid=m.mid and c.sid=s.sid and c.sid=%1 and c.aid=%2").arg(sid).arg(aid);
    query.exec(s);
    QStringList stu;
    if(query.next())
    {
        for(int i=0; i<7; i++)
            stu<<query.value(i).toString();
    }qDebug()<<stu<<s;
    return stu;
}
