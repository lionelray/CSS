#ifndef LOGINSERVER_H
#define LOGINSERVER_H

#include <QObject>

class LoginServer : public QObject
{
    Q_OBJECT
    QString username;
    QString password;
    int waringflag;
public:
    explicit LoginServer(QObject *parent = 0);
    int verify(QString name, QString pwd);
    void verifystr(QString name, QString pwd);
    QString logingWaring();
signals:

public slots:

};

#endif // LOGINSERVER_H
