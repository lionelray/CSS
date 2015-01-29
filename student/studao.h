#ifndef STUDAO_H
#define STUDAO_H

#include <QObject>
#include <QtSql>
class StuDao : public QObject
{
    Q_OBJECT
    QSqlQueryModel *model;
public:
    explicit StuDao(QObject *parent = 0);
    QStringList dept();
    QStringList major(QString dname);
    bool addstu(QStringList stuinfo);
    bool delstu(int sid);
    QString autosid(int grade);
    QSqlQueryModel *search(QString info, QString meth);
    QSqlQueryModel *showall();
signals:

public slots:

};

#endif // STUDAO_H
