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
    explicit MainWindow(QWidget *parent = 0); // 构造函数
    ~MainWindow(); // 析构函数

private slots:
    void closeEvent(QCloseEvent *event); // 重写closeEvent
    void setInfo(QTreeWidgetItem* item); // 展示信息
    void modifyInfo(QListWidgetItem* item); // 修改信息
    void on_actionInsert_organization_triggered(); // 插入单位
    void on_deleteButton_clicked(); // 删除结点
    void on_insertButton_clicked(); // 插入子项
    void accept(); // 封装mydialog的accept
    void reject(); // 封装mydialog的reject
    void on_searchButton_clicked(); // 搜索指定项
    void on_childList_doubleClicked(const QModelIndex &index); // 通过右侧子结点表选定单位
    void on_actionSort_organizations_triggered(); // 在界面层面根据成果数对单位进行排序
    void on_actionSearch_among_contributors_triggered(); // 展示指定年龄段完成人信息
    void on_actionsearch_among_MVC_triggered(); // 展示指定年龄段第一完成人信息
    void on_actionHelp_document_triggered(); // 展开操作帮助文档（当前目录的README.md）
    void on_actionAbout_us_triggered(); // 通过浏览器打开程序github页面
    void on_actionOpen_triggered(); // 文件打开
    void on_actionSave_triggered(); // 文件保存
    void on_actionClose_triggered(); // 文件关闭

private:
    QTreeWidgetItem* cur_item; // 存储左侧树状结构中当前item
    QDialog* myDialog; // 常用对话框
    org_node* cur_org; // 当前单元为成果时存储其所在单位
    achi_node* cur_achi; // 当前单元为完成人时存储其所在成果
    org_node* pre_org; // 当前单元为单位时存储前一个单位
    achi_node* pre_achi; // 当前单元为成果时存储前一个成果
    contr_node* pre_contr; // 当前单元为完成人时存储前一个完成人
    org_node* this_org; // 当前单元为单位时存储当前结点
    achi_node* this_achi; // 当前单元为成果时存储当前结点
    contr_node* this_contr; // 当前单元为完成人时存储当前完成人
    Ui::MainWindow *ui; // 由ui文件生成的对象
    QListWidget* infolist; // 存储中间信息展示区list部件
    QListWidget* childlist; // 存储右侧子节点站上去list部件
    QString dir = ""; // 存储当前打开的文件名
    bool ischanged = 0; // 上次保存后文件是否被修改
    void initTree(); // 构建左侧总览区的树状结构
    void resetInfo(); // 更新信息展示区信息
};

#endif // MAINWINDOW_H
