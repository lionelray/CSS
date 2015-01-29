#include "stusign.h"
#include "ui_stusign.h"
#include "signdao.h"
#include <QMessageBox>
StuSign::StuSign(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StuSign)
{
    ui->setupUi(this);
}

StuSign::~StuSign()
{
    delete ui;
}

void StuSign::load(int sid, int aid)
{
    SignDao *stusign = new SignDao();
    QStringList stu = stusign->showStuSign(sid,aid);
    ui->lineEditStuid->setText(stu.at(0));
    ui->lineEditStuName->setText(stu.at(1));
    ui->lineEditStuDept->setText(stu.at(2));
    ui->lineEditStuMajor->setText(stu.at(3));
    ui->lineEditGrade->setText(stu.at(4));
    ui->lineEditClass->setText(stu.at(5));
    ui->comboBox->setCurrentText(stu.at(6));
    delete stusign;
}

void StuSign::setID(int sid, int aid)
{
    this->sid = sid;
    this->aid = aid;
    load(sid,aid);
}

void StuSign::on_pushButtonBack_clicked()
{
    this->close();
}

void StuSign::on_pushButtonSave_clicked()
{
    SignDao *changestat = new SignDao();
    QString cstat = ui->comboBox->currentText();
    bool flag = changestat->changeStat(sid,aid,cstat);
    if(flag)
    {
        QMessageBox message(QMessageBox::NoIcon, "通知", "保存成功！");
        message.exec();
        this->close();
    }
    else
    {
        QMessageBox message(QMessageBox::NoIcon, "通知", "保存失败！");
        message.exec();
    }
}
