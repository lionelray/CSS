#include "signdetail.h"
#include "ui_signdetail.h"
#include "stusign.h"
#include <QMessageBox>
SignDetail::SignDetail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignDetail)
{
    ui->setupUi(this);
}

SignDetail::~SignDetail()
{
    delete ui;
}

void SignDetail::setSID(int aid)
{
    this->aid = aid;
    loadSign(aid);
}

void SignDetail::loadSign(int aid)
{
    SignDao *sign = new SignDao();

    model = sign->showall(aid);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    delete sign;
    //delete model;
}

void SignDetail::on_pushButtonChangeStat_clicked()
{
    int row = ui->tableView->currentIndex().row();
    if(row != -1)
    {
        QModelIndex index = ui->tableView->currentIndex();
        int sid = index.sibling(row,0).data().toInt();
        StuSign *changestat = new StuSign();
        changestat->setID(sid,aid);
        changestat->exec();
    }
    else
    {
        QMessageBox::warning(this,"告警！","未选中行！");
    }
}
//导表--签到详细
void SignDetail::on_pushButtonOutXls_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(NULL,"Save File",".","Excel File (*.xls)");
    fileName.replace("/","\\");
    ExcelEngine excel(fileName);
    excel.Open();
    excel.SaveDataFrTable(ui->tableView); //导出报表
    excel.Close();
}
