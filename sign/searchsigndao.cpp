#include "searchsigndao.h"

SearchsignDao::SearchsignDao(QObject *parent) :
    QObject(parent)
{
}

QSqlQueryModel *SearchsignDao::searchsign(QString info, QString meth)
{
    QSqlDatabase db = Db::getConnection();
    QSqlQueryModel *model;
    db.open();
    if(model == NULL)
    {
        model = new QSqlQueryModel;
    }
    QString s;
    s = QString("select a.* from attend a where %1 like '%%2%'").arg(meth).arg(info);
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
    delete model;
}
