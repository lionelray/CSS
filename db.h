#ifndef DB_H
#define DB_H

#include <QObject>
#include <QtSql>
extern QString Error;
class Db : public QObject
{
    Q_OBJECT
    static QSqlDatabase db;
    static bool flag;
public:
    explicit Db(QObject *parent = 0);
    static QSqlDatabase getConnection();
signals:

public slots:

};

#endif // DB_H
