#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "sign/signdetail.h"
#include "sign/signdao.h"

extern QString Error;
extern QString identify;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);//当前tab页
    ui->pushButtonChooseitem->setVisible(false);
    stu = new StuDao;
    guest = new GuestDao;
    loadsign();
    loadstu();
    if(identify != "系统管理员")
    {
        ui->pushButtonAddgst->setEnabled(false);
        ui->pushButtonDelgst->setEnabled(false);
        ui->groupBoxSearchgst->setEnabled(false);
        ui->pushButtonResetPwd->setEnabled(false);
    }
    else
    {
        loadguest();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*-----------------------
#
#    识别签到模块
#
#------------------------*/
//新建签到项目
void MainWindow::on_pushButtonCreateItem_clicked()
{
    CreateItem *createitem = new CreateItem(this);
    createitem->exec();
}

//选择签到项目
void MainWindow::on_pushButtonSwitchItem_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
    ui->pushButtonChooseitem->setVisible(true);
}


/*-----------------------
#
#    签到管理模块
#
#------------------------*/
//载入签到项目
void MainWindow::loadsign()
{
    SignDao *showall = new SignDao();
    model = showall->showallSign();
    ui->tableViewSigninfo->setModel(model);
    ui->tableViewSigninfo->resizeColumnsToContents();
    delete showall;
}

//添加签到项目
void MainWindow::on_pushButtonAddSignitem_clicked()
{
    on_pushButtonCreateItem_clicked();
}

//删除签到项目
void MainWindow::on_pushButtonDelSignitem_clicked()
{
    int row = ui->tableViewSigninfo->currentIndex().row();
    if(row!=-1)
    {
        switch(QMessageBox::question(this,"删除项目",tr("您确定要删除该项目吗？该操作不可恢复！"),
                                     QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok))
        {
        case QMessageBox::Ok:
        {
            SignDao *delsign = new SignDao();
            QModelIndex index = ui->tableViewSigninfo->currentIndex();
            int sid = index.sibling(row,0).data().toInt();
            bool flag = delsign->delsign(sid);
            if(flag)
            {
                loadsign();
                QMessageBox message(QMessageBox::NoIcon, "通知", "删除成功！");
                message.exec();
            }
            else
            {
                QMessageBox message(QMessageBox::NoIcon, "通知", "删除失败！");
                message.exec();
            }
            break;
        }
        case QMessageBox::Cancel:
            break;
        default:
            break;
        }
    }
    else
    {
        QMessageBox::warning(this,"告警！","未选中行！");
    }
}

//显示所有签到项目
void MainWindow::on_pushButtonShowallSign_clicked()
{
    loadsign();
}

//选中签到项目转到tab0
void MainWindow::on_pushButtonChooseitem_clicked()
{
    int row = ui->tableViewSigninfo->currentIndex().row();
    if(row!=-1)
    {
        ui->pushButtonChooseitem->setVisible(false);
        ui->tabWidget->setCurrentIndex(0);
        QModelIndex index = ui->tableViewSigninfo->currentIndex();
        QStringList sign;
        for(int i=0; i<6; i++)
        {
            sign<<index.sibling(row,i).data().toString();
        }
        ui->lineEditSignid->setText(sign.at(0));
        ui->lineEditSignName->setText(sign.at(1));
        ui->lineEditSignloc->setText(sign.at(2));
        ui->lineEditSignTime->setText(sign.at(3));
        ui->lineEditCharge->setText(sign.at(4));
        ui->textBrowser->setText(sign.at(5));
    }
    else
    {
        QMessageBox::warning(this,"告警！","未选中行！");
    }
}
//查看某个签到项目明细
void MainWindow::on_tableViewSigninfo_doubleClicked(const QModelIndex &index)
{
    int row = ui->tableViewSigninfo->currentIndex().row();
    int sid = index.sibling(row,0).data().toInt();
    SignDetail *signdetail = new SignDetail();
    signdetail->setSID(sid);
    signdetail->exec();
}

//查询签到项
void MainWindow::on_pushButtonSearchSign_clicked()
{
    if(!ui->lineEditSearchSign->text().isEmpty())
    {
        QString info = ui->lineEditSearchSign->text();
        QString meth;
        if(ui->radioButtonSignId->isChecked())
        {
            meth = "a.aid";
        }
        else if(ui->radioButtonSignName->isChecked())
        {
            meth = "a.aname";
        }
        else if(ui->radioButtonSignloc->isChecked())
        {
            meth = "a.aloc";
        }
        else if(ui->radioButtonSigntime->isChecked())
        {
            meth = "a.atime";
        }
        else if(ui->radioButtonSignRange->isChecked())
        {
            meth = "a.arange";
        }
        SearchsignDao *searchsign = new SearchsignDao();
        model = searchsign->searchsign(info,meth);
        ui->tableViewSigninfo->setModel(model);
        ui->tableViewSigninfo->resizeColumnsToContents();
        delete searchsign;
    }
    else
    {
        QMessageBox message(QMessageBox::NoIcon,"警告","未输入查询内容！");
        message.exec();
    }
}

/*-----------------------
#
#    学生管理模块
#
#------------------------*/
//载入学生
void MainWindow::loadstu()
{
    model = stu->showall();
    ui->tableViewStu->setModel(model);
    ui->tableViewStu->resizeColumnsToContents();
}

//添加学生
void MainWindow::on_pushButtonAddstu_clicked()
{
    Addstu *addstu = new Addstu(this);
    addstu->exec();
}

//删除学生
void MainWindow::on_pushButtonDelstu_clicked()
{
    int row = ui->tableViewStu->currentIndex().row();
    if(row!=-1)
    {
        QModelIndex index = ui->tableViewStu->currentIndex();
        int sid = index.sibling(row,0).data().toInt();
        bool flag = stu->delstu(sid);
        if(flag)
        {
            loadstu();
            QMessageBox message(QMessageBox::NoIcon, "通知", "删除成功！");
            message.exec();
        }
        else
        {
            QMessageBox message(QMessageBox::NoIcon, "通知", "删除失败！\n" + Error);
            message.exec();
        }
    }
    else
    {
        QMessageBox::warning(this,"告警！","未选中行！");
    }
}

//查询学生
void MainWindow::on_pushButtonSearchstu_clicked()
{
    QString info = ui->lineEditSearchstu->text();
    QString meth;
    if(!ui->lineEditSearchstu->text().isEmpty())
    {
        if(ui->radioButtonSId->isChecked())
        {
            meth = "s.sid";
        }
        else if(ui->radioButtonSName->isChecked())
        {
            meth = "s.sname";
        }
        else if(ui->radioButtonSDept->isChecked())
        {
            meth = "d.deptname";
        }
        else if(ui->radioButtonSMajor->isChecked())
        {
            meth = "m.mname";
        }
        else if(ui->radioButtonGrade->isChecked())
        {
            meth = "s.grade";
        }
        else if(ui->radioButtonClass->isChecked())
        {
            meth = "s.class";
        }
        model = stu->search(info,meth);
        ui->tableViewGuest->clearMask();
        ui->tableViewGuest->setModel(model);
        ui->tableViewGuest->resizeColumnsToContents();
    }
    else
    {
        QMessageBox message(QMessageBox::NoIcon, "通知", "未输入查询内容！");
        message.exec();
    }
}

/*-----------------------
#
#    用户管理模块
#
#------------------------*/
//载入用户
void MainWindow::loadguest()
{
    model = guest->showall();
    ui->tableViewGuest->setModel(model);
    ui->tableViewGuest->resizeColumnsToContents();
}

//添加用户
void MainWindow::on_pushButtonAddgst_clicked()
{
    Addgst *addgst = new Addgst();
    addgst->exec();
    loadguest();
}

//删除用户
void MainWindow::on_pushButtonDelgst_clicked()
{
    int row = ui->tableViewGuest->currentIndex().row();
    if(row!=-1)
    {
        QModelIndex index = ui->tableViewGuest->currentIndex();
        QString gname = index.sibling(row,0).data().toString();
        bool flag = guest->delguest(gname);
        if(flag)
        {
            loadguest();
            QMessageBox message(QMessageBox::NoIcon, "通知", "删除成功！");
            message.exec();
        }
        else
        {
            QMessageBox message(QMessageBox::NoIcon, "通知", "删除失败！\n" + Error);
            message.exec();
        }
    }
    else
    {
        QMessageBox::warning(this,"告警！","未选中行！");
    }
}

//查询用户
void MainWindow::on_pushButtonSearchgst_clicked()
{
    QString info = ui->lineEditSearchgst->text();
    QString meth;
    if(!ui->lineEditSearchgst->text().isEmpty())
    {
        if(ui->radioButtonGname->isChecked())
        {
            meth = "g.gname";
        }
        else if(ui->radioButtonIdentify->isChecked())
        {
            meth = "g.identify";
        }
        else if(ui->radioButtonGDept->isChecked())
        {
            meth = "d.deptname";
        }
        model = guest->search(info,meth);
        ui->tableViewGuest->clearMask();
        ui->tableViewGuest->setModel(model);
        ui->tableViewGuest->resizeColumnsToContents();
    }
    else
    {
        QMessageBox message(QMessageBox::NoIcon, "通知", "未输入查询内容！");
        message.exec();
    }
}

//显示所有用户
void MainWindow::on_pushButtonGShowAll_clicked()
{
    loadguest();
}

//重置密码
void MainWindow::on_pushButtonResetPwd_clicked()
{
    int row = ui->tableViewGuest->currentIndex().row();

    if(row!=-1)
    {
        QModelIndex index = ui->tableViewGuest->currentIndex();
        QString gname = index.sibling(row,0).data().toString();
        bool flag = guest->resetpwd(gname,"123456");
        if(flag)
        {
            loadguest();
            QMessageBox message(QMessageBox::NoIcon, "通知", "用户："+gname+"密码重置为“123456”！");
            message.exec();
        }
        else
        {
            QMessageBox message(QMessageBox::NoIcon, "通知", "重置密码失败！");
            message.exec();
        }
    }
    else
    {
        QMessageBox::warning(this,"告警！","未选中行！");
    }
}

//修改当前用户密码
void MainWindow::on_pushButtonChangePwd_clicked()
{
    ChangePwd *changepwd = new ChangePwd(this);
    changepwd->show();
}

//导表--签到项目
void MainWindow::on_pushButtonOutitem_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(NULL,"Save File",".","Excel File (*.xls)");
    fileName.replace("/","\\");
    ExcelEngine excel(fileName);
    excel.Open();
    excel.SaveDataFrTable(ui->tableViewSigninfo); //导出报表
    excel.Close();
}

//导表--学生
void MainWindow::on_pushButtonOutstu_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(NULL,"Save File",".","Excel File (*.xls)");
    fileName.replace("/","\\");
    ExcelEngine excel(fileName);
    excel.Open();
    excel.SaveDataFrTable(ui->tableViewStu); //导出报表
    excel.Close();
}

//导表--用户
void MainWindow::on_pushButtonOutGuest_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(NULL,"Save File",".","Excel File (*.xls)");
    fileName.replace("/","\\");
    ExcelEngine excel(fileName);
    excel.Open();
    excel.SaveDataFrTable(ui->tableViewGuest); //导出报表
    excel.Close();
}
