#include "createitem.h"
#include "ui_createitem.h"
#include "student/studao.h"
#include "createitemdao.h"
#include <QMessageBox>
extern QString main_username;
CreateItem::CreateItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateItem)
{
    ui->setupUi(this);
    CreateitemDao * item = new CreateitemDao();
    QString sid = item->autoaid();
    ui->lineEditSignid->setText(sid);

    QRegExp re("[0-9]{2}");
    QRegExpValidator *pReva = new QRegExpValidator(re,this);
    ui->lineEditClass->setValidator(pReva);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->comboBoxMajor->setEnabled(false);
    ui->lineEditClass->setEnabled(false);
    ui->lineEditCharge->setText(main_username);
    StuDao *studao = new StuDao();
    ui->comboBoxDept->addItems(studao->dept());
    delete studao;
}

CreateItem::~CreateItem()
{
    delete ui;
}

//返回
void CreateItem::on_pushButtonBack_clicked()
{
    this->close();
}

//保存
void CreateItem::on_pushButtonSave_clicked()
{
    CreateitemDao * item = new CreateitemDao();
    QString signid = ui->lineEditSignid->text();
    QString sel;
    QStringList list;
    QString range = ui->comboBoxDept->currentText();
    list<<ui->lineEditSignid->text()<<ui->lineEditSignName->text()<<ui->lineEditSignloc->text()<<ui->dateTimeEdit->text()<<ui->lineEditCharge->text();
    if(ui->radioButton->isChecked())
    {
          sel = "d.deptname='"+ range +"'";
    }
    else if(ui->radioButtonMajor->isChecked())
    {
        sel = "d.deptname='"+ ui->comboBoxDept->currentText() +"' and m.mname='"+ ui->comboBoxMajor->currentText()+"'";
        range += ui->comboBoxMajor->currentText();
    }
    else
    {
        sel = "d.deptname='"+ ui->comboBoxDept->currentText() +"' and m.mname='"+ ui->comboBoxMajor->currentText()+"' and s.class='"+ ui->lineEditClass->text()+"'";
        range = ui->comboBoxMajor->currentText() + ui->lineEditClass->text();
    }
    list<<range<<ui->plainTextEdit->toPlainText();
    bool additem = item->additem(list);
    bool addcheck = item->addcheck(sel,signid);
    delete item;
    if(additem && addcheck)
    {
        QMessageBox message(QMessageBox::NoIcon, "通知", "添加成功！");
        message.exec();
    }
    else
    {
        QMessageBox message(QMessageBox::NoIcon, "通知", "添加失败！");
        message.exec();
    }
}

void CreateItem::on_comboBoxDept_currentTextChanged(const QString &arg1)
{
    StuDao *studao = new StuDao();
    ui->comboBoxMajor->clear();
    ui->comboBoxMajor->addItems(studao->major(arg1));
    delete studao;
}

void CreateItem::on_radioButton_clicked()
{
    ui->comboBoxMajor->setEnabled(false);
    ui->lineEditClass->setEnabled(false);
}

void CreateItem::on_radioButtonMajor_clicked()
{
    ui->comboBoxMajor->setEnabled(true);
    ui->lineEditClass->setEnabled(false);
}

void CreateItem::on_radioButtonClass_clicked()
{
    ui->comboBoxMajor->setEnabled(true);
    ui->lineEditClass->setEnabled(true);
}
