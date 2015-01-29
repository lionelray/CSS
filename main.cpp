#include "mainwindow.h"
#include <QApplication>
#include "login/login.h"
QString Error;
QString main_username;
QString identify;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login log;
    int flag=log.exec();
    MainWindow w;
    if(flag == Login::Accepted)
    {
        w.setWindowTitle("用户 "+main_username+" ，欢迎登陆校园班级签到系统！您的身份是："+identify);
        w.show();
    }
    else
    {
        return 0;
    }

    return a.exec();
}
