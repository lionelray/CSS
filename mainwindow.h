#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "excelengine.h"
#include "createitem/createitem.h"
#include "student/addstu.h"
#include "student/delstu.h"
#include "student/searchstu.h"
#include "guest/changepwd.h"
#include "guest/guestdao.h"
#include "guest/addgst.h"
#include "student/studao.h"
#include "sign/searchsigndao.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void loadguest();
    void loadstu();
    void loadsign();
private slots:
    void on_pushButtonCreateItem_clicked();

    void on_pushButtonAddstu_clicked();

    void on_pushButtonDelstu_clicked();

    void on_pushButtonSearchstu_clicked();

    void on_pushButtonChangePwd_clicked();

    void on_pushButtonAddgst_clicked();

    void on_pushButtonSearchgst_clicked();

    void on_pushButtonGShowAll_clicked();

    void on_pushButtonResetPwd_clicked();

    void on_pushButtonDelgst_clicked();

    void on_pushButtonSwitchItem_clicked();

    void on_pushButtonChooseitem_clicked();

    void on_pushButtonSearchSign_clicked();

    void on_tableViewSigninfo_doubleClicked(const QModelIndex &index);

    void on_pushButtonShowallSign_clicked();

    void on_pushButtonDelSignitem_clicked();

    void on_pushButtonAddSignitem_clicked();

    void on_pushButtonOutitem_clicked();

    void on_pushButtonOutstu_clicked();

    void on_pushButtonOutGuest_clicked();

private:
    Ui::MainWindow *ui;
    ChangePwd changepwd;
    QSqlQueryModel *model;
    GuestDao *guest;
    StuDao *stu;
};

#endif // MAINWINDOW_H
