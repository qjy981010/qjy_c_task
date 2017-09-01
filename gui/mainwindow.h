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
#include <QComboBox>
#include <QTextEdit>
#include <QDesktopServices>
#include <QUrl>
#include <QFile>
#include <QFileDialog>
#include <QCloseEvent>
#include <fstream>
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
    void closeEvent(QCloseEvent *event);
    void setInfo(QTreeWidgetItem* item);
    void modifyInfo(QListWidgetItem* item);
    void on_actionInsert_organization_triggered();
    void on_deleteButton_clicked();
    void on_insertButton_clicked();
    void accept();
    void reject();
    void on_searchButton_clicked();

    void on_childList_doubleClicked(const QModelIndex &index);

    void on_actionSort_organizations_triggered();

    void on_actionSearch_among_contributors_triggered();

    void on_actionsearch_among_MVC_triggered();

    void on_actionHelp_document_triggered();

    void on_actionAbout_us_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionClose_triggered();

private:
    QTreeWidgetItem* cur_item;
    QDialog* myDialog;
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
    QString dir = "";
    bool ischanged = 0;
    void initTree();
    void resetInfo();
    // void addMyItem(QListWidget* list, QString key, QString val);
};

#endif // MAINWINDOW_H
