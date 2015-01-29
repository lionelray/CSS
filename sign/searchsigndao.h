#ifndef SEARCHSIGNDAO_H
#define SEARCHSIGNDAO_H

#include <QObject>
#include <QtSql>
#include "db.h"
class SearchsignDao : public QObject
{
    Q_OBJECT
public:
    explicit SearchsignDao(QObject *parent = 0);
    QSqlQueryModel *searchsign(QString info, QString meth);
signals:

public slots:

};

#endif // SEARCHSIGNDAO_H
