#include <QTreeWidgetItem>
#include "mainwindow.h"
#include "ui_mainwindow.h"

// 构造函数
// 功能：初始化主窗口。
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setWindowTitle("Achievement Manager");
    ui->setupUi(this);
    initTree();
    infolist = ui->infoList;
    childlist = ui->childList;
    connect(infolist, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(modifyInfo(QListWidgetItem*)));
    connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(setInfo(QTreeWidgetItem*)));
    ui->deleteButton->setDisabled(1);
    ui->insertButton->setDisabled(1);
    QShortcut *shortcut = new QShortcut(QKeySequence("Return"), this);
    QObject::connect(shortcut, SIGNAL(activated()), this, SLOT(on_searchButton_clicked()));
}

// 析构函数
// 功能：进行空间释放
MainWindow::~MainWindow()
{
    delete ui;
}

// 功能：读取链表，初始化树状结构。
void MainWindow::initTree()
{
    QTreeWidgetItem* org;
    QTreeWidgetItem* achi;
    QTreeWidgetItem* contr;
    ui->treeWidget->clear();
    org_node* it_org_ptr = org_list_head;
    for (; it_org_ptr; it_org_ptr = it_org_ptr->next) { // 遍历链表, 为树结构添加结点
        org = new QTreeWidgetItem(ui->treeWidget);
        org->setText(0, it_org_ptr->info.org_name);
        achi_node* it_achi_ptr = it_org_ptr->achievements;
        for (; it_achi_ptr; it_achi_ptr = it_achi_ptr->next) {
            achi = new QTreeWidgetItem(org);
            qDebug() << it_achi_ptr << " " << achi;
            achi->setText(0, it_achi_ptr->info.result_name);
            contr_node* it_contr_ptr = it_achi_ptr->contributors;
            for (; it_contr_ptr; it_contr_ptr = it_contr_ptr->next) {
                contr = new QTreeWidgetItem(achi);
                contr->setText(0, it_contr_ptr->info.name);
            }
        }
    }
}

// 功能：更新当前单元的信息；
void MainWindow::resetInfo()
{
    if (cur_item->parent())
    {
        if (cur_item->parent()->parent())
        {
            infolist->clear();
            QString gender;
            if (this_contr->info.gender == 'w') gender = "woman";
            else gender = "man";
            infolist->addItem(QString("name: ") + QString(this_contr->info.name));
            infolist->addItem(QString("id: ") + QString(this_contr->info.id_num));
            infolist->addItem(QString("org: ") + QString(this_contr->info.org));
            infolist->addItem(QString("one achievement: ") + QString(this_contr->info.result_name));
            infolist->addItem(QString("gender: ") + gender);
            infolist->addItem(QString("age: ") + QString::number(this_contr->info.age));
            infolist->addItem(QString("job title: ") + QString(this_contr->info.job_title));
            infolist->addItem(QString("achievement ranking: ") + QString::number(this_contr->info.ranking));
        }
        else
        {
            infolist->clear();
            infolist->addItem(QString("id: ") + QString(this_achi->info.result_id));
            infolist->addItem(QString("name: ") + QString(this_achi->info.result_name));
            infolist->addItem(QString("field: ") + QString(this_achi->info.field));
            infolist->addItem(QString("organization: ") + QString(this_achi->info.org));
            infolist->addItem(QString("most valuable contributor: ") + QString(this_achi->info.mvp));
            infolist->addItem(QString("price name: ") + QString(this_achi->info.price_name));
            infolist->addItem(QString("price class: ") + QString(this_achi->info.price_class));
            infolist->addItem(QString("price ranking: ") + QString::number(this_achi->info.price_ranking));
            infolist->addItem(QString("contributors number: ") + QString::number(this_achi->info.contr_num));
        }
    }
    else
    {
        infolist->clear();
        infolist->addItem(QString("id: ") + QString(this_org->info.org_id));
        infolist->addItem(QString("name: ") + QString(this_org->info.org_name));
        infolist->addItem(QString("chairman: ") + QString(this_org->info.chairman));
        infolist->addItem(QString("phone: ") + QString(this_org->info.phone_num));
        infolist->addItem(QString("achievements number: ") + QString::number(this_org->info.achi_num));
        infolist->addItem(QString("national achievements number: ") + QString::number(this_org->info.national_achi_num));
        infolist->addItem(QString("provincial achievements number: ") + QString::number(this_org->info.provincial_achi_num));
        infolist->addItem(QString("municipal achievements number: ") + QString::number(this_org->info.municipal_achi_num));
    }
}

// 功能：将选中结点的信息展示出来，单击树状结构item调用；
// 输入参数：树状结构单元的指针；
void MainWindow::setInfo(QTreeWidgetItem* item) // 设置中间信息栏以及右侧次级结点栏内容
{
    cur_item = item;
    ui->treeWidget->expandItem(item);
    if (item->parent()) {
        if (item->parent()->parent()) { // contributor
            qDebug() << "contributor item clicked";
            ui->childClass->setText("");
            ui->deleteButton->setText("Delete this contributor");
            ui->insertButton->setText("insert");
            ui->insertButton->setDisabled(1);
            ui->deleteButton->setDisabled(0);
            this_contr = get_contr_by_name(item->parent()->parent()->text(0).toLatin1().data(),
                                        item->parent()->text(0).toLatin1().data(), item->text(0).toLatin1().data(), &pre_contr, &cur_achi);
            if (!this_contr)
            {
                qDebug() << "ERROR: No contributor named " << item->text(0);
                return;
            }
            infolist->clear();
            childlist->clear();
            QString gender;
            if (this_contr->info.gender == 'w') gender = "woman";
            else gender = "man";
            infolist->addItem(QString("name: ") + QString(this_contr->info.name));
            infolist->addItem(QString("id: ") + QString(this_contr->info.id_num));
            infolist->addItem(QString("org: ") + QString(this_contr->info.org));
            infolist->addItem(QString("one achievement: ") + QString(this_contr->info.result_name));
            infolist->addItem(QString("gender: ") + gender);
            infolist->addItem(QString("age: ") + QString::number(this_contr->info.age));
            infolist->addItem(QString("job title: ") + QString(this_contr->info.job_title));
            infolist->addItem(QString("achievement ranking: ") + QString::number(this_contr->info.ranking));
        }
        else { // achievement
            qDebug() << "achievement item clicked";
            ui->childClass->setText("Contributors");
            ui->deleteButton->setText("Delete this achievement");
            ui->insertButton->setText("Insert new contributor");
            ui->insertButton->setDisabled(0);
            ui->deleteButton->setDisabled(0);
            this_achi = get_achi_by_name(item->parent()->text(0).toLatin1().data(),
                                        item->text(0).toLatin1().data(), &pre_achi, &cur_org);
            if (!this_achi)
            {
                qDebug() << "ERROR: No achievement named " << item->text(0);
                return;
            }
            infolist->clear();
            childlist->clear();
            infolist->addItem(QString("id: ") + QString(this_achi->info.result_id));
            infolist->addItem(QString("name: ") + QString(this_achi->info.result_name));
            infolist->addItem(QString("field: ") + QString(this_achi->info.field));
            infolist->addItem(QString("organization: ") + QString(this_achi->info.org));
            infolist->addItem(QString("most valuable contributor: ") + QString(this_achi->info.mvp));
            infolist->addItem(QString("price name: ") + QString(this_achi->info.price_name));
            infolist->addItem(QString("price class: ") + QString(this_achi->info.price_class));
            infolist->addItem(QString("price ranking: ") + QString::number(this_achi->info.price_ranking));
            infolist->addItem(QString("contributors number: ") + QString::number(this_achi->info.contr_num));
            for (contr_node* it = this_achi->contributors; it; it = it->next) {
                childlist->addItem(QString(it->info.name));
            }
        }
    }
    else { // organization
        qDebug() << "organization item clicked";
        ui->childClass->setText("Achievements");
        ui->deleteButton->setText("Delete this organization");
        ui->insertButton->setText("Insert new achievement");
        ui->insertButton->setDisabled(0);
        ui->deleteButton->setDisabled(0);
        this_org = get_org_by_name(item->text(0).toLatin1().data(), &pre_org);
        if (!this_org)
        {
            qDebug() << "ERROR: No organization named " << item->text(0);
            return;
        }
        infolist->clear();
        childlist->clear();
        infolist->addItem(QString("id: ") + QString(this_org->info.org_id));
        infolist->addItem(QString("name: ") + QString(this_org->info.org_name));
        infolist->addItem(QString("chairman: ") + QString(this_org->info.chairman));
        infolist->addItem(QString("phone: ") + QString(this_org->info.phone_num));
        infolist->addItem(QString("achievements number: ") + QString::number(this_org->info.achi_num));
        infolist->addItem(QString("national achievements number: ") + QString::number(this_org->info.national_achi_num));
        infolist->addItem(QString("provincial achievements number: ") + QString::number(this_org->info.provincial_achi_num));
        infolist->addItem(QString("municipal achievements number: ") + QString::number(this_org->info.municipal_achi_num));
        for (achi_node* it = this_org->achievements; it; it = it->next) {
            childlist->addItem(QString(it->info.result_name));
        }
    }
}

// 功能：对可以修改的信息项，获取修改信息并修改，双击信息调用；
// 输入参数：被双击的listitem指针；
void MainWindow::modifyInfo(QListWidgetItem* item)
{
    QStringList pieces = item->text().split( ": " );
    QString key = pieces.value(0); // key
    QString val = pieces.value(1); // value
    QString newval;
    bool dialogResult;
    char rightmodify = 0;
    char* newname = 0;
    int index = infolist->row(item); // 根据在表中的位置获取需要修改的信息
    ischanged = 1;
    if (cur_item->parent())
    {
        if (cur_item->parent()->parent())
        {
            switch (index)
            {
            case 2: return; // 不可修改, 下同
            case 3: return;
            case 4: // 性别修改
            {
                myDialog = new QDialog;
                QPushButton okbtn("ok");
                QPushButton cancelbtn("cancel");
                connect(&okbtn, SIGNAL(clicked()), this, SLOT(accept()));
                connect(&cancelbtn, SIGNAL(clicked()), this, SLOT(reject()));
                QGridLayout modifylayout;
                myDialog->setWindowTitle("modify gender");
                QComboBox genderline;
                genderline.addItem("man");
                genderline.addItem("woman");
                QLabel genderlabel("gender:");
                modifylayout.addWidget(&genderlabel, 0, 0);
                modifylayout.addWidget(&genderline, 0, 1);
                modifylayout.addWidget(&okbtn, 1, 0);
                modifylayout.addWidget(&cancelbtn, 1, 1);
                myDialog->setLayout(&modifylayout);
                dialogResult = (myDialog->exec() == QDialog::Accepted);
                newval = genderline.currentText();
                break;
            }
            default: // 其他修改
            {
                QInputDialog* modifyDialog = new QInputDialog();
                newval = modifyDialog->getText(0, "modify", "New " + key, QLineEdit::Normal,
                                                       val, &dialogResult);
                delete modifyDialog;
            }
            }
            if (newval.length() > 0 && dialogResult) // 修改有效
            {
                if (index == 0) // 如果修改了名称, 检查重名
                {
                    for (contr_node* it = cur_achi->contributors; it; it = it->next)
                    {
                        if (!strcmp(newval.toLatin1().data(), it->info.name))
                        {
                            QMessageBox::critical(0, "Error", newval + " has existed !");
                            return;
                        }
                    }
                    cur_item->setText(0, newval);
                    newname = this_contr->info.name;
                }
                rightmodify = modify_contr(this_contr, index, newval.toLatin1().data(), newval.toInt());
            }
        }
        else
        {
            switch (index)
            {
            case 3: return;
            case 8: return;
            case 6: // 等级修改
            {
                myDialog = new QDialog;
                QPushButton okbtn("ok");
                QPushButton cancelbtn("cancel");
                connect(&okbtn, SIGNAL(clicked()), this, SLOT(accept()));
                connect(&cancelbtn, SIGNAL(clicked()), this, SLOT(reject()));
                QGridLayout modifylayout;
                myDialog->setWindowTitle("modify price class");
                QComboBox priceclassline;
                priceclassline.addItem("National");
                priceclassline.addItem("Provincial");
                priceclassline.addItem("Municipal");
                priceclassline.addItem("School");
                QLabel priceclasslabel("price class:");
                modifylayout.addWidget(&priceclasslabel, 0, 0);
                modifylayout.addWidget(&priceclassline, 0, 1);
                modifylayout.addWidget(&okbtn, 1, 0);
                modifylayout.addWidget(&cancelbtn, 1, 1);
                myDialog->setLayout(&modifylayout);
                dialogResult = (myDialog->exec() == QDialog::Accepted);
                newval = priceclassline.currentText();
                if (dialogResult) // 维护各等级结点数
                {
                    if (val[0] == 'N') --cur_org->info.national_achi_num;
                    else if (val[0] == 'P') --cur_org->info.provincial_achi_num;
                    else if (val[0] == 'M') --cur_org->info.municipal_achi_num;
                    if (newval[0] == 'N') ++cur_org->info.national_achi_num;
                    else if (newval[0] == 'P') ++cur_org->info.provincial_achi_num;
                    else if (newval[0] == 'M') ++cur_org->info.municipal_achi_num;
                }
                break;
            }
            default: // 其他修改
            {
                QInputDialog* modifyDialog = new QInputDialog();
                newval = modifyDialog->getText(0, "modify", "New " + key, QLineEdit::Normal,
                                                       val, &dialogResult);
                delete modifyDialog;
            }
            }
            if (newval.length() > 0 && dialogResult) // 修改有效
            {
                if (index == 1) { // 修改名称, 检查重名
                    for (achi_node* it = cur_org->achievements; it; it = it->next)
                    {
                        if (!strcmp(newval.toLatin1().data(), it->info.result_name))
                        {
                            QMessageBox::critical(0, "Error", newval + " has existed !");
                            return;
                        }
                    }
                    cur_item->setText(0, newval);
                    newname = this_achi->info.result_name;
                }
                rightmodify = modify_achi(this_achi, index, newval.toLatin1().data(), newval.toInt());
            }
        }
    }
    else
    {
        if (index == 4 || index == 5 || index == 6 || index == 7) return;
        QInputDialog* modifyDialog = new QInputDialog();
        newval = modifyDialog->getText(0, "modify", "New " + key, QLineEdit::Normal,
                                               val, &dialogResult);
        if (dialogResult) // 修改有效
        {
            if (index == 1) { // 修改名称, 检查重名
                for (org_node* it = org_list_head; it; it = it->next)
                {
                    if (!strcmp(newval.toLatin1().data(), it->info.org_name))
                    {
                        QMessageBox::critical(0, "Error", newval + " has existed !");
                        delete modifyDialog;
                        return;
                    }
                }
                cur_item->setText(0, newval);
                newname = this_org->info.org_name;
            }
            rightmodify = modify_org(this_org, index, newval.toLatin1().data());
        }
        delete modifyDialog;
    }
    if (rightmodify == 1) item->setText(key + QString(": " + newval));
    else if (rightmodify == 2) item->setText(key + QString(": " + QString::number(newval.toInt())));
    if (newname) cur_item->setText(0, newname);
}

// 封装mydialog的accept
void MainWindow::accept()
{
    myDialog->accept();
}

// 封装mydialog的reject
void MainWindow::reject()
{
    myDialog->reject();
}

// 功能：调用内部删除函数，删除当前选中的结点，由“delete”按钮调用；
void MainWindow::on_deleteButton_clicked()
{
    qDebug() << "delete button clicked";
    ischanged = 1;
    // 提示, 防止误删
    if (QMessageBox::Yes == QMessageBox::warning(NULL, "warning", "Do you really want to delete "+cur_item->text(0)+"?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
    {
        if (cur_item->parent())
        {
            if (cur_item->parent()->parent())
            {
                delete_contr(this_contr, pre_contr, cur_achi);
                delete this_contr;
            }
            else
            {
                delete_achi(this_achi, pre_achi, cur_org);
                sort_orgs_if_needed(cur_org->next, cur_org);
            }
        }
        else
        {
            delete_org(this_org, pre_org);
        }
        infolist->clear();
        childlist->clear();
        delete cur_item;
        ui->insertButton->setDisabled(1);
        ui->deleteButton->setDisabled(1);
    }
}

// 功能：信息获取，并调用内部插入单位的函数插入新单位，由菜单栏manage->New organization调用；
void MainWindow::on_actionInsert_organization_triggered()
{
    qDebug() << "insert org";
    ischanged = 1;
    myDialog = new QDialog;
    QPushButton okbtn("ok");
    QPushButton cancelbtn("cancel");
    connect(&okbtn, SIGNAL(clicked()), this, SLOT(accept()));
    connect(&cancelbtn, SIGNAL(clicked()), this, SLOT(reject()));
    QGridLayout insertlayout;
    myDialog->setWindowTitle("insert new organization");
    QLineEdit nameline;
    QLineEdit idline;
    QLineEdit chairmanline;
    QLineEdit phoneline;
    QLabel namelabel("name:");
    QLabel idlabel("id:");
    QLabel chairmanlabel("chair man:");
    QLabel phonelabel("phone number:");
    insertlayout.addWidget(&namelabel, 0, 0);
    insertlayout.addWidget(&nameline, 0, 1);
    insertlayout.addWidget(&idlabel, 1, 0);
    insertlayout.addWidget(&idline, 1, 1);
    insertlayout.addWidget(&chairmanlabel, 2, 0);
    insertlayout.addWidget(&chairmanline, 2, 1);
    insertlayout.addWidget(&phonelabel, 3, 0);
    insertlayout.addWidget(&phoneline, 3, 1);
    insertlayout.addWidget(&okbtn, 4, 0);
    insertlayout.addWidget(&cancelbtn, 4, 1);
    myDialog->setLayout(&insertlayout);
    int result = myDialog->exec();
    org_node* neworg;
    if (result == QDialog::Accepted && !nameline.text().isEmpty()) // 信息有效
    {
        if (neworg = insert_org(idline.text().toLatin1().data(), nameline.text().toLatin1().data(),
                        chairmanline.text().toLatin1().data(), phoneline.text().toLatin1().data()))
        {
            qDebug() << "name " << nameline.text();
            qDebug() << "id " << idline.text();
            qDebug() << "chairman " << chairmanline.text();
            qDebug() << "phone " << phoneline.text();
            QTreeWidgetItem* org = new QTreeWidgetItem(ui->treeWidget);
            org->setText(0, neworg->info.org_name);
        }
        else // 重名
        {
            QMessageBox::warning(this, "Name has been used", "Name "+nameline.text()+" has been used before!");
        }
    }
}

// 功能：信息获取，并调用内部插入函数插入成果、完成人，由“insert”按钮调用。
void MainWindow::on_insertButton_clicked()
{
    qDebug() << "insert button clicked";
    myDialog = new QDialog;
    QPushButton okbtn("ok");
    QPushButton cancelbtn("cancel");
    connect(&okbtn, SIGNAL(clicked()), this, SLOT(accept()));
    connect(&cancelbtn, SIGNAL(clicked()), this, SLOT(reject()));
    QGridLayout insertlayout;
    ischanged = 1;
    if (cur_item->parent()) { // insert contributor
        qDebug() << "insert contributor";
        myDialog->setWindowTitle("insert new contributor");
        QLineEdit nameline;
        QLineEdit idline;
        QComboBox genderline;
        QLineEdit ageline;
        QLineEdit titleline;
        QLineEdit rankingline;
        genderline.addItem("man");
        genderline.addItem("woman");
        QLabel namelabel("name:");
        QLabel idlabel("id:");
        QLabel genderlabel("gender:");
        QLabel agelabel("age:");
        QLabel titlelabel("job title:");
        QLabel rankinglabel("achievement ranking:");
        insertlayout.addWidget(&namelabel, 0, 0);
        insertlayout.addWidget(&nameline, 0, 1);
        insertlayout.addWidget(&idlabel, 1, 0);
        insertlayout.addWidget(&idline, 1, 1);
        insertlayout.addWidget(&genderlabel, 2, 0);
        insertlayout.addWidget(&genderline, 2, 1);
        insertlayout.addWidget(&agelabel, 3, 0);
        insertlayout.addWidget(&ageline, 3, 1);
        insertlayout.addWidget(&titlelabel, 4, 0);
        insertlayout.addWidget(&titleline, 4, 1);
        insertlayout.addWidget(&rankinglabel, 5, 0);
        insertlayout.addWidget(&rankingline, 5, 1);
        insertlayout.addWidget(&okbtn, 6, 0);
        insertlayout.addWidget(&cancelbtn, 6, 1);
        myDialog->setLayout(&insertlayout);
        int result = myDialog->exec();
        contr_node* newcontr;
        if (result == QDialog::Accepted && !nameline.text().isEmpty()) // 信息有效
        {
            if (newcontr = insert_contr(this_achi, nameline.text().toLatin1().data(), idline.text().toLatin1().data(),
                              cur_item->parent()->text(0).toLatin1().data(), cur_item->text(0).toLatin1().data(),
                              genderline.currentText()[0].toLatin1(), ageline.text().toInt(),
                              titleline.text().toLatin1().data(), rankingline.text().toInt()))
            {
                qDebug() << "name " << nameline.text();
                qDebug() << "id " << idline.text();
                qDebug() << "gender " << genderline.currentText();
                qDebug() << "age " << ageline.text();
                qDebug() << "title " << titleline.text();
                qDebug() << "ranking " << rankingline.text();
                childlist->addItem(nameline.text());
                QTreeWidgetItem* contr = new QTreeWidgetItem(cur_item);
                contr->setText(0, newcontr->info.name);
            }
            else // 重名
            {
                QMessageBox::warning(this, "Name has been used", "Name "+nameline.text()+" has been used before!");
            }
        }
    }
    else { // insert achievement
        qDebug() << "insert achievement";
        myDialog->setWindowTitle("insert new achievement");
        QLineEdit nameline;
        QLineEdit idline;
        QLineEdit fieldline;
        QLineEdit mvpline;
        QLineEdit pricenameline;
        QComboBox priceclassline;
        QLineEdit pricerankingline;
        priceclassline.addItem("National");
        priceclassline.addItem("Provincial");
        priceclassline.addItem("Municipal");
        priceclassline.addItem("School");
        QLabel namelabel("name:");
        QLabel idlabel("id:");
        QLabel fieldlabel("field:");
        QLabel mvplabel("most valuable contributor:");
        QLabel pricenamelabel("price name:");
        QLabel priceclasslabel("price class:");
        QLabel pricerankinglabel("price ranking:");
        insertlayout.addWidget(&idlabel, 0 ,0);
        insertlayout.addWidget(&idline, 0, 1);
        insertlayout.addWidget(&namelabel, 1, 0);
        insertlayout.addWidget(&nameline, 1, 1);
        insertlayout.addWidget(&fieldlabel, 2, 0);
        insertlayout.addWidget(&fieldline, 2, 1);
        insertlayout.addWidget(&mvplabel, 3, 0);
        insertlayout.addWidget(&mvpline, 3, 1);
        insertlayout.addWidget(&pricenamelabel, 4, 0);
        insertlayout.addWidget(&pricenameline, 4, 1);
        insertlayout.addWidget(&priceclasslabel, 5, 0);
        insertlayout.addWidget(&priceclassline, 5, 1);
        insertlayout.addWidget(&pricerankinglabel, 6, 0);
        insertlayout.addWidget(&pricerankingline, 6, 1);
        insertlayout.addWidget(&okbtn, 7, 0);
        insertlayout.addWidget(&cancelbtn, 7, 1);
        myDialog->setLayout(&insertlayout);
        int result = myDialog->exec();
        achi_node* newachi;
        if (result == QDialog::Accepted && !nameline.text().isEmpty()) { // 信息有效
            if (newachi = insert_achi(this_org, idline.text().toLatin1().data(), nameline.text().toLatin1().data(),
                            fieldline.text().toLatin1().data(), cur_item->text(0).toLatin1().data(),
                            mvpline.text().toLatin1().data(), pricenameline.text().toLatin1().data(),
                            priceclassline.currentText().toLatin1().data(), pricerankingline.text().toInt()))
            {
                qDebug() << "name " << nameline.text().toLatin1().data();
                qDebug() << "id " << idline.text().toLatin1().data();
                qDebug() << "field " << fieldline.text().toLatin1().data();
                qDebug() << "mvp " << mvpline.text().toLatin1().data();
                qDebug() << "price name " << pricenameline.text().toLatin1().data();
                qDebug() << "price class " << priceclassline.currentText().toLatin1().data();
                qDebug() << "price ranking " << pricerankingline.text().toLatin1().data();
                childlist->addItem(nameline.text());
                QTreeWidgetItem* achi = new QTreeWidgetItem(cur_item);
                achi->setText(0, newachi->info.result_name);
                sort_orgs_if_needed(this_org, pre_org);
            }
            else // 重名
            {
                QMessageBox::warning(this, "Name has been used", "Name "+nameline.text()+" has been used before!");
            }
        }
    }
    resetInfo();
    ui->treeWidget->expandItem(cur_item);
}

// 功能：获取搜索栏字符串搜索相似度最高的单元并展示此项信息；由"search"按钮调用
void MainWindow::on_searchButton_clicked()
{
    char searchstr[40];
    strcpy(searchstr, ui->searchLine->text().toLatin1().data());
    int min = INT_MAX, dis;
    QTreeWidgetItem* rightItem = 0;
    if (cur_item) cur_item->setSelected(false);
    if (strlen(searchstr) > 0) // 搜索内容不为空
    {
        QTreeWidgetItemIterator it(ui->treeWidget); // 遍历, 找到相似度最高的
        while (*it)
        {
            dis = dl_distance((*it)->text(0).toLatin1().data(), searchstr);
            qDebug() << (*it)->text(0) << "  distance: " << dis;
            if (dis < min)
            {
                min = dis;
                rightItem = *it;
                if (dis == 0) break; // 如果完全相等, 跳出
            }
            ++it;
        }
        if (!rightItem) return;
        ui->treeWidget->itemClicked(rightItem, 0); // 选中此项
        rightItem->setSelected(true);
        if (rightItem->parent()) // 展开父级树
        {
            if (rightItem->parent()->parent())
                ui->treeWidget->expandItem(rightItem->parent()->parent());
            ui->treeWidget->expandItem(rightItem->parent());
        }
    }
}

// 功能：在当前结点的子链表搜索指定孩子信息并展示，双击右侧表项调用；
// 输入参数：被双击项的索引值。
void MainWindow::on_childList_doubleClicked(const QModelIndex &index)
{
    QString curstr = childlist->currentItem()->text();
    for (int i = 0; i < cur_item->childCount(); ++i) // 遍历子链表, 找到此项
    {
        if (cur_item->child(i)->text(0) == curstr)
        {
            cur_item->setSelected(false);
            cur_item->child(i)->setSelected(true);
            ui->treeWidget->itemClicked(cur_item->child(i), 0);
        }
    }
}

// 功能：实现对科研单位在界面层上的排序；由Manage->Sort Organization调用
void MainWindow::on_actionSort_organizations_triggered()
{
    // 实际上内部的链表排序, 在插入删除时已完成, 但界面上未更新, 此为重新构建树状结构
    initTree();
}

// 功能：获取年龄段并调用内部函数，最后展示符合要求的完成人信息；
void MainWindow::on_actionSearch_among_contributors_triggered()
{
    qDebug() << "filter by age";
    myDialog = new QDialog;
    QPushButton okbtn("ok");
    QPushButton cancelbtn("cancel");
    connect(&okbtn, SIGNAL(clicked()), this, SLOT(accept()));
    connect(&cancelbtn, SIGNAL(clicked()), this, SLOT(reject()));
    QGridLayout filterlayout;
    myDialog->setWindowTitle("Filter by age");
    QLabel fromlabel("age from");
    QLabel tolabel("to");
    QLineEdit fromline("0");
    QLineEdit toline("60");
    filterlayout.addWidget(&fromlabel, 0, 0);
    filterlayout.addWidget(&fromline, 0, 1);
    filterlayout.addWidget(&tolabel, 0, 2);
    filterlayout.addWidget(&toline, 0, 3);
    filterlayout.addWidget(&okbtn, 1, 0, 1, 2);
    filterlayout.addWidget(&cancelbtn, 1, 2, 1, 2);
    myDialog->setLayout(&filterlayout);
    int result = myDialog->exec();
    if (result == QDialog::Accepted) {
        contr_node* head = filter_by_age(fromline.text().toInt(), toline.text().toInt());
        if (!head) // 未找到
        {
            QMessageBox::information(this, "no result", "No contributor aged from " + fromline.text() + " to " + toline.text());
        }
        QString info = "";
        for (contr_node* it = head; it; it = it->next) // 获取信息
        {
            info += QString("name: %1\nid: %2\norganization: %3\nachievement: %4\ngender: %5\nage: %6\njob title: %7\nachievement ranking: %8\n\n").arg(
                        it->info.name, it->info.id_num, it->info.org, it->info.result_name, QString(it->info.gender), QString::number(it->info.age), it->info.job_title, QString::number(it->info.ranking));
        }
        myDialog = new QDialog; // 展示结果
        myDialog->setWindowTitle("Filter by age from " + fromline.text() + " to " + toline.text());
        QTextEdit textedit;
        textedit.setText(info);
        filterlayout.addWidget(&textedit, 0, 0, 1, 4);
        myDialog->setLayout(&filterlayout);
        myDialog->exec();
        delete_contr_list(head);
    }
}

// 功能：获取年龄段并调用内部函数，最后展示符合要求的完成人信息；
void MainWindow::on_actionsearch_among_MVC_triggered()
{
    qDebug() << "filter by age";
    myDialog = new QDialog;
    QPushButton okbtn("ok");
    QPushButton cancelbtn("cancel");
    connect(&okbtn, SIGNAL(clicked()), this, SLOT(accept()));
    connect(&cancelbtn, SIGNAL(clicked()), this, SLOT(reject()));
    QGridLayout filterlayout;
    myDialog->setWindowTitle("Filter by age among MVC");
    QLabel fromlabel("age from");
    QLabel tolabel("to");
    QLineEdit fromline("0");
    QLineEdit toline("60");
    filterlayout.addWidget(&fromlabel, 0, 0);
    filterlayout.addWidget(&fromline, 0, 1);
    filterlayout.addWidget(&tolabel, 0, 2);
    filterlayout.addWidget(&toline, 0, 3);
    filterlayout.addWidget(&okbtn, 1, 0, 1, 2);
    filterlayout.addWidget(&cancelbtn, 1, 2, 1, 2);
    myDialog->setLayout(&filterlayout);
    int result = myDialog->exec();
    if (result == QDialog::Accepted) {
        contr_node* head = filter_by_age_MVC(fromline.text().toInt(), toline.text().toInt());
        if (!head) // 未找到
        {
            QMessageBox::information(this, "no result", "no MVC aged from " + fromline.text() + " to " + toline.text());
        }
        QString info = "";
        for (contr_node* it = head; it; it = it->next) // 获取信息
        {
            info += QString("name: %1\nid: %2\norganization: %3\nachievement: %4\ngender: %5\nage: %6\njob title: %7\nachievement ranking: %8\n\n").arg(
                        it->info.name, it->info.id_num, it->info.org, it->info.result_name, QString(it->info.gender), QString::number(it->info.age), it->info.job_title, QString::number(it->info.ranking));
        }
        myDialog = new QDialog; // 展示结果
        myDialog->setWindowTitle("Filter by age from " + fromline.text() + " to " + toline.text());
        QTextEdit textedit;
        textedit.setText(info);
        textedit.setReadOnly(true);
        filterlayout.addWidget(&textedit, 0, 0, 1, 4);
        myDialog->setLayout(&filterlayout);
        myDialog->exec();
        delete_contr_list(head);
    }
}

// 功能：获取并展示当前文件夹下的帮助文档（./README.md）；无此文件时弹出错误框
void MainWindow::on_actionHelp_document_triggered()
{
    QFile documentfile("./README.md");
    if (documentfile.open(QFile::ReadOnly)) {
        QTextStream in(&documentfile);
        QString document = in.readAll();
        myDialog = new QDialog;
        QGridLayout documentlayout;
        QPushButton okbtn("ok");
        QPushButton cancelbtn("cancel");
        connect(&okbtn, SIGNAL(clicked()), this, SLOT(accept()));
        connect(&cancelbtn, SIGNAL(clicked()), this, SLOT(reject()));
        myDialog->setWindowTitle("Help document");
        QTextEdit textedit;
        textedit.setText(document);
        textedit.setReadOnly(true);
        documentlayout.addWidget(&textedit, 0, 0, 1, 4);
        documentlayout.addWidget(&okbtn, 1, 0, 1, 2);
        documentlayout.addWidget(&cancelbtn, 1, 2, 1, 2);
        myDialog->setLayout(&documentlayout);
        myDialog->resize(700, 500);
        myDialog->exec();
    }
    else // 未找到readme文件
    {
        QMessageBox::critical(this, "No document found", "No help document found!");
    }
}

// 功能：在默认浏览器打开此项目的github页面；
void MainWindow::on_actionAbout_us_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/qjy981010/qjy_c_task"));
}

// 功能：如果此时有文件打开则调用先判断是否保存后关闭当前文件，然后选择数据文件所在文件夹，调用load_data读取；
void MainWindow::on_actionOpen_triggered()
{
    ui->actionClose->triggered(); // 调用close, 关闭当前文件
    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), // 获取要打开的目录
                                            "",
                                            QFileDialog::ShowDirsOnly
                                            | QFileDialog::DontResolveSymlinks);
    if (dir == "") return;
    if (dir[dir.length()-1] != '/') dir += '/';
    if (load_data((dir+"org.dat").toLatin1().data(), (dir+"achi.dat").toLatin1().data(), (dir+"contr.dat").toLatin1().data()))
    {
        qDebug() << dir+"org.dat"; // 打开失败
        QMessageBox::critical(this, "Open error", "Fail to load data in "+dir);
        return;
    }
    initTree();
}

// 功能：将链表中数据保存在数据文件中，若无文件打开则需先选择所要保存的文件夹；
void MainWindow::on_actionSave_triggered()
{
    qDebug() << "save";
    if (!ischanged) return; // 未改动则返回
    if (!dir.length()) // 无文件打开时, 选择要保存的位置
    {
        dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
        if (dir == "") return;
        if (dir[dir.length()-1] != '/') dir += '/';
    }
    // 写入数据
    if (write_data((dir+"org.dat").toLatin1().data(), (dir+"achi.dat").toLatin1().data(), (dir+"contr.dat").toLatin1().data()))
    {
        QMessageBox::critical(this, "Save error", "Fail to save data to "+dir);
        return;
    }
    ischanged = 0; // 未更改
}

// 功能：若文件有更改则提示是否保存，然后关闭文件。
void MainWindow::on_actionClose_triggered()
{
    qDebug() << "close";
    // 是否保存
    if (ischanged && QMessageBox::Yes == QMessageBox::question(this, "Save or not", "Do you want to save the files before close?"))
    {
        // 保存
        on_actionSave_triggered();
    }
    ui->treeWidget->clear();
    childlist->clear();
    infolist->clear();
    ui->deleteButton->setDisabled(1);
    ui->insertButton->setDisabled(1);
    delall();
    dir = "";
    ischanged = 0;
}

// 功能：Override Qt的退出事件退出前提示保存。
void MainWindow::closeEvent(QCloseEvent *event)
{
    // 退出前
    if (!ischanged) return; // 未修改, 直接退出
    // 有修改, 提示保存
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Achievement Manager",
                                                                tr("Do you want to save the files before close?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn == QMessageBox::Cancel) // 取消, 不退出
    {
        event->ignore();
    }
    else if (resBtn == QMessageBox::No) // 不保存
    {
        event->accept();
    }
    else // 保存
    {
        on_actionSave_triggered();
        event->accept();
    }
}
