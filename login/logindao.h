#ifndef LOGINDAO_H
#define LOGINDAO_H

#include <QObject>

class LoginDao : public QObject
{
    Q_OBJECT
public:
    explicit LoginDao(QObject *parent = 0);
    int verify(QString name, QString pwd);
signals:

public slots:

};

#endif // LOGINDAO_H
