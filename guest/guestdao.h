#ifndef GUESTDAO_H
#define GUESTDAO_H

#include <QObject>
#include <QtSql>
class GuestDao : public QObject
{
    Q_OBJECT
    QSqlQueryModel *model;
public:
    explicit GuestDao(QObject *parent = 0);
    QSqlQueryModel *showall();
    QSqlQueryModel *search(QString info,QString meth);
    bool delguest(QString gname);
    bool insert(QStringList list);
    bool resetpwd(QString gname, QString pwd);
    QStringList dept();
    QString getoldpwd(QString gname);
signals:

public slots:

};

#endif // GUESTDAO_H
