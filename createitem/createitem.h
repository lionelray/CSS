#ifndef CREATEITEM_H
#define CREATEITEM_H

#include <QDialog>

namespace Ui {
class CreateItem;
}

class CreateItem : public QDialog
{
    Q_OBJECT

public:
    explicit CreateItem(QWidget *parent = 0);
    ~CreateItem();

private slots:
    void on_pushButtonBack_clicked();

    void on_pushButtonSave_clicked();

    void on_comboBoxDept_currentTextChanged(const QString &arg1);

    void on_radioButton_clicked();

    void on_radioButtonMajor_clicked();

    void on_radioButtonClass_clicked();

private:
    Ui::CreateItem *ui;

};

#endif // CREATEITEM_H
