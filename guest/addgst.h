#ifndef ADDGST_H
#define ADDGST_H

#include <QDialog>

#include "guestdao.h"
namespace Ui {
class Addgst;
}

class Addgst : public QDialog
{
    Q_OBJECT
    GuestDao *guest;
    QSqlQueryModel *model;
public:
    explicit Addgst(QWidget *parent = 0);
    ~Addgst();

private slots:
    void on_pushButtonSave_clicked();

    void on_pushButtonBack_clicked();

private:
    Ui::Addgst *ui;
};

#endif // ADDGST_H
