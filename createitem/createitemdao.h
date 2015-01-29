#ifndef CREATEITEMDAO_H
#define CREATEITEMDAO_H

#include <QObject>
#include "db.h"
class CreateitemDao : public QObject
{
    Q_OBJECT
public:
    explicit CreateitemDao(QObject *parent = 0);
    bool additem(QStringList list);
    bool addcheck(QString sel,QString signid);
    QString autoaid();
signals:

public slots:

};

#endif // CREATEITEMDAO_H
