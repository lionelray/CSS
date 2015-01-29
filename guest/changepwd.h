#ifndef CHANGEPWD_H
#define CHANGEPWD_H

#include <QDialog>

namespace Ui {
class ChangePwd;
}

class ChangePwd : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePwd(QWidget *parent = 0);
    ~ChangePwd();
    void getoldpwd();
private slots:
    void on_pushButtonBack_clicked();

    void on_pushButtonSave_clicked();

    void on_lineEditConfirPwd_textChanged(const QString &arg1);

    void on_lineEditPwd_textChanged(const QString &arg1);

    void on_lineEditOldPwd_textChanged(const QString &arg1);

private:
    Ui::ChangePwd *ui;
    QString oldpwd;
};

#endif // CHANGEPWD_H
