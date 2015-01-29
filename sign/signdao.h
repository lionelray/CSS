#ifndef SIGNDAO_H
#define SIGNDAO_H

#include <QObject>
#include <QSql>
#include "db.h"
class SignDao : public QObject
{
    Q_OBJECT

public:
    explicit SignDao(QObject *parent = 0);
    QSqlQueryModel *showall(int aid);
    QSqlQueryModel *showallSign();
    bool changeStat(int sid, int aid, QString stat);
    bool delsign(int sid);
    QStringList showStuSign(int sid,int aid);
signals:

public slots:

};

#endif // SIGNDAO_H
