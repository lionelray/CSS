#include "addstu.h"
#include "ui_addstu.h"
#include <QMessageBox>
#include <QDebug>
#include "mainwindow.h"
Addstu::Addstu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Addstu)
{
    ui->setupUi(this);
    studao = new StuDao;
    ui->comboBoxDept->addItems(studao->dept());

    QString year = QDateTime::currentDateTime().toString("yyyy");
    ui->lineEditGrade->setText(year);

    QRegExp reG("[0-9]{4}");
    QRegExpValidator *pRevaG = new QRegExpValidator(reG,this);
    ui->lineEditGrade->setValidator(pRevaG);
    QRegExp reC("[0-9]{2}");
    QRegExpValidator *pRevaC = new QRegExpValidator(reC,this);
    ui->lineEditClass->setValidator(pRevaC);
}

Addstu::~Addstu()
{
    delete ui;
}

//返回
void Addstu::on_pushButtonBack_clicked()
{
    this->close();
}

//保存
void Addstu::on_pushButtonSave_clicked()
{
    QStringList stuinfo;
    stuinfo<<ui->lineEditStuid->text()<<ui->lineEditStuName->text()<<ui->comboBoxMajor->currentText()<<ui->lineEditGrade->text()<<ui->lineEditClass->text()<<ui->lineEditFace->text()<<ui->lineEditFinger->text()<<ui->plainTextEdit->toPlainText();
    bool flag = studao->addstu(stuinfo);
    if(flag)
    {
        QMessageBox message(QMessageBox::NoIcon, "通知", "保存成功！");
        MainWindow *mainwindow = (MainWindow*)parentWidget();
        mainwindow->loadstu();
        message.exec();
        this->close();
    }
    else
    {
        QMessageBox message(QMessageBox::NoIcon, "通知", "保存失败！");
        message.exec();
    }
}

void Addstu::on_comboBoxDept_currentTextChanged(const QString &arg1)
{
    ui->comboBoxMajor->clear();
    ui->comboBoxMajor->addItems(studao->major(arg1));
}
//自动生成学号
void Addstu::on_lineEditGrade_textChanged(const QString &arg1)
{
    if(ui->lineEditGrade->text().length()>3)
    {
        ui->lineEditStuid->setText(studao->autosid(ui->lineEditGrade->text().toInt()));
    }
    return;
}
