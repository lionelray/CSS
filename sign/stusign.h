#ifndef STUSIGN_H
#define STUSIGN_H

#include <QDialog>

namespace Ui {
class StuSign;
}

class StuSign : public QDialog
{
    Q_OBJECT
    int sid,aid;
public:
    explicit StuSign(QWidget *parent = 0);
    ~StuSign();
    void load(int sid, int aid);
    void setID(int sid,int aid);
private slots:
    void on_pushButtonBack_clicked();

    void on_pushButtonSave_clicked();

private:
    Ui::StuSign *ui;
};

#endif // STUSIGN_H
