#include "loginserver.h"
#include "logindao.h"
LoginServer::LoginServer(QObject *parent) :
    QObject(parent)
{
    this->username="";
    this->password="";
    /*this->right="";*/
    this->waringflag=0;
}

int LoginServer::verify(QString name, QString pwd)
{
    verifystr(name,pwd);
    if(waringflag==0)
    {
        LoginDao logindao;
        int verifyreturn=logindao.verify(username,password);
        if(verifyreturn==0)
        {
            return 0;
        }
        else if(verifyreturn == 1)
        {
            waringflag=4;
            return 1;
        }
        else if(verifyreturn == 2)
        {
            waringflag=6;
            return 2;
        }
        else if(verifyreturn == 3)
        {
            waringflag=3;
            return 3;
        }
    }
}

void LoginServer::verifystr(QString name, QString pwd)
{
    if(name == ""){waringflag=1;}
    else if(pwd == ""){waringflag=2;}
    this->username=name;
    this->password=pwd;
}

QString LoginServer::logingWaring()
{
    QString waringstr="空";
    if(waringflag==1){waringstr="请输入你的用户名";}
    if(waringflag==2){waringstr="请输入你的登陆密码";}    
    if(waringflag==3){waringstr="数据库未连接！";}
    if(waringflag==4){waringstr="密码错误！";}
    if(waringflag==6){waringstr="系统不存在该用户！";}
    return waringstr;
}
