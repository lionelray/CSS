#ifndef SIGNDETAIL_H
#define SIGNDETAIL_H

#include <QDialog>
#include <QSql>
#include <QFileDialog>
#include "signdao.h"
#include "excelengine.h"
namespace Ui {
class SignDetail;
}

class SignDetail : public QDialog
{
    Q_OBJECT
    int aid;
    QSqlQueryModel *model;
public:
    explicit SignDetail(QWidget *parent = 0);
    ~SignDetail();
    void setSID(int aid);
    void loadSign(int aid);
private slots:
    void on_pushButtonChangeStat_clicked();

    void on_pushButtonOutXls_clicked();

private:
    Ui::SignDetail *ui;
};

#endif // SIGNDETAIL_H
