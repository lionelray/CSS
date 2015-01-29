#ifndef ADDSTU_H
#define ADDSTU_H

#include <QDialog>
#include "studao.h"
namespace Ui {
class Addstu;
}

class Addstu : public QDialog
{
    Q_OBJECT
    StuDao *studao;
public:
    explicit Addstu(QWidget *parent = 0);
    ~Addstu();

private slots:
    void on_pushButtonBack_clicked();

    void on_pushButtonSave_clicked();

    void on_comboBoxDept_currentTextChanged(const QString &arg1);

    void on_lineEditGrade_textChanged(const QString &arg1);

private:
    Ui::Addstu *ui;
};

#endif // ADDSTU_H
