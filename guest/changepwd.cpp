#include "changepwd.h"
#include "ui_changepwd.h"
#include "guestdao.h"
#include <QMessageBox>
extern QString main_username;
ChangePwd::ChangePwd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePwd)
{
    ui->setupUi(this);
    ui->labelG1->setVisible(false);
    ui->labelG2->setVisible(false);
    ui->labelPwdConfirm->setVisible(false);
    ui->labelG1_2->setVisible(false);
    ui->labelOldPwd->setVisible(false);
    QRegExp re("^[A-Za-z0-9]+${16}");
    QRegExpValidator *pReva = new QRegExpValidator(re,this);
    ui->lineEditPwd->setValidator(pReva);
    ui->lineEditConfirPwd->setValidator(pReva);
    getoldpwd();
}

ChangePwd::~ChangePwd()
{
    delete ui;
}

void ChangePwd::getoldpwd()
{
    GuestDao *guest = new GuestDao();
    oldpwd = guest->getoldpwd(main_username);
}

//返回
void ChangePwd::on_pushButtonBack_clicked()
{
    this->close();
}

//保存密码
void ChangePwd::on_pushButtonSave_clicked()
{
    if(ui->lineEditOldPwd->text() != oldpwd)
    {
        QMessageBox message(QMessageBox::NoIcon,"通知","原密码错误！");
        message.exec();
    }
    else if(ui->lineEditPwd->text() == ui->lineEditConfirPwd->text())
    {
        QString pwd = ui->lineEditPwd->text();
        GuestDao *guest = new GuestDao();
        bool flag = guest->resetpwd(main_username,pwd);
        if(flag)
        {
            QMessageBox message(QMessageBox::NoIcon,"通知","密码修改成功！");
            message.exec();
            this->close();
        }
        else
        {
            QMessageBox message(QMessageBox::NoIcon,"通知","密码修改失败！");
            message.exec();
        }
    }

    else
    {
        QMessageBox message(QMessageBox::NoIcon,"通知","密码不一致，请重新输入！");
        message.exec();
    }
}
//检查密码规范性
void ChangePwd::on_lineEditPwd_textChanged(const QString &arg1)
{
    if(ui->lineEditPwd->text().length()>5)
    {
        ui->labelPwdCheck->setVisible(false);
        ui->labelG1->setVisible(true);
    }
    else
    {
        ui->labelPwdCheck->setVisible(true);
        ui->labelG1->setVisible(false);
    }
}
//检查密码一致性
void ChangePwd::on_lineEditConfirPwd_textChanged(const QString &arg1)
{
    if(ui->lineEditPwd->text() != ui->lineEditConfirPwd->text())
    {
        ui->labelPwdConfirm->setVisible(true);
        ui->labelG2->setVisible(false);
    }
    else
    {
        ui->labelPwdConfirm->setVisible(false);
        ui->labelG2->setVisible(true);
    }
}
//检查原密码
void ChangePwd::on_lineEditOldPwd_textChanged(const QString &arg1)
{
    if(ui->lineEditOldPwd->text() != oldpwd)
    {
        ui->labelOldPwd->setVisible(true);
        ui->labelG1_2->setVisible(false);
    }
    else
    {
        ui->labelOldPwd->setVisible(false);
        ui->labelG1_2->setVisible(true);
    }
}
