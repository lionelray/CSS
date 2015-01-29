#include "login.h"
#include "ui_login.h"
#include "loginserver.h"
#include <QMessageBox>
extern QString main_username;
Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->lineEdit_username->setFocus();
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_Login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    LoginServer *logins = new LoginServer(); //创建一个登陆控制类对象
    int login = logins->verify(username,password);//**调用控制类的检查函数
    if(login == 0)
    {
        main_username = username;
        accept();
    }
    else
    {
        QString waringstr = logins->logingWaring();
        QMessageBox::warning(this,"告警！",waringstr);
    }
    delete (logins);
}

void Login::on_pushButton_Exit_clicked()
{
    reject();
}
