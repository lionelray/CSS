#include "addgst.h"
#include "ui_addgst.h"
#include <QMessageBox>
#include "mainwindow.h"

Addgst::Addgst(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Addgst)
{
    ui->setupUi(this);
    guest = new GuestDao;
    ui->comboBoxDept->addItems(guest->dept());
}

Addgst::~Addgst()
{
    delete ui;
}

//保存用户
void Addgst::on_pushButtonSave_clicked()
{
    QStringList guestl;
    guestl<<ui->lineEditGname->text()<<ui->lineEditPwd->text()<<ui->comboBoxIdentify->currentText()<<ui->comboBoxDept->currentText()<<ui->plainTextEdit->toPlainText();
    bool flag = guest->insert(guestl);
    if(flag)
    {
//        loadguest();
        QMessageBox message(QMessageBox::NoIcon, "通知", "保存成功！");
        message.exec();
        this->close();
    }
    else
    {
        QMessageBox message(QMessageBox::NoIcon, "通知", "保存失败！\n" + Error);
        message.exec();
    }
}

//返回
void Addgst::on_pushButtonBack_clicked()
{
    this->close();
}
