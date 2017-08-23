#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QWidget>
#include <QDebug>
#include <QListWidget>
#include <QListWidgetItem>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QShortcut>
#include "mylistitem.h"

extern "C"
{
#include "../list.h"
}

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void setInfo(QTreeWidgetItem* item, int num);
    void modifyInfo(QListWidgetItem* item);
    void on_actionInsert_organization_triggered();
    void on_deleteButton_clicked();
    void on_insertButton_clicked();
    void accept();
    void reject();
    void on_searchButton_clicked();

    void on_childList_doubleClicked(const QModelIndex &index);

private:
    QTreeWidgetItem* cur_item;
    QDialog* insertDialog;
    org_node* cur_org;
    achi_node* cur_achi;
    org_node* pre_org;
    achi_node* pre_achi;
    contr_node* pre_contr;
    org_node* this_org;
    achi_node* this_achi;
    contr_node* this_contr;
    Ui::MainWindow *ui;
    QListWidget* infolist;
    QListWidget* childlist;
    void initTree();
    // void addMyItem(QListWidget* list, QString key, QString val);
};

#endif // MAINWINDOW_H
