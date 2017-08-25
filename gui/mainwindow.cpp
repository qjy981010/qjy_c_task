#include <QTreeWidgetItem>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setWindowTitle("Achievement Manager");
    ui->setupUi(this);
    connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(setInfo(QTreeWidgetItem*,int)));
    initTree();
    // ui->treeWidget->setSortingEnabled(true);
    // ui->treeWidget->sortByColumn(0);
    // ui->treeWidget->sortItems(0, Qt::DescendingOrder);
    infolist = ui->infoList;
    childlist = ui->childList;
    connect(infolist, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(modifyInfo(QListWidgetItem*)));
    ui->deleteButton->setDisabled(1);
    ui->insertButton->setDisabled(1);
    QShortcut *shortcut = new QShortcut(QKeySequence("Return"), this);
    QObject::connect(shortcut, SIGNAL(activated()), this, SLOT(on_searchButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTree()
{
    QTreeWidgetItem* org;
    QTreeWidgetItem* achi;
    QTreeWidgetItem* contr;
    ui->treeWidget->clear();
    org_node* it_org_ptr = org_list_head;
    for (; it_org_ptr; it_org_ptr = it_org_ptr->next) {
        org = new QTreeWidgetItem(ui->treeWidget);
        org->setText(0, it_org_ptr->info.org_name);
        achi_node* it_achi_ptr = it_org_ptr->achievements;
        for (; it_achi_ptr; it_achi_ptr = it_achi_ptr->next) {
            achi = new QTreeWidgetItem(org);
            achi->setText(0, it_achi_ptr->info.result_name);
            contr_node* it_contr_ptr = it_achi_ptr->contributors;
            for (; it_contr_ptr; it_contr_ptr = it_contr_ptr->next) {
                contr = new QTreeWidgetItem(achi);
                contr->setText(0, it_contr_ptr->info.name);
            }
        }
    }
}

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

void MainWindow::setInfo(QTreeWidgetItem* item, int num)
{
    cur_item = item;
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

void MainWindow::modifyInfo(QListWidgetItem* item)
{
    QStringList pieces = item->text().split( ": " );
    QString key = pieces.value(0);
    QString val = pieces.value(1);
    QString newval;
    bool dialogResult;
    char rightmodify = 0;
    int index = infolist->row(item);
    if (cur_item->parent())
    {
        if (cur_item->parent()->parent())
        {
            switch (index)
            {
            case 2: return;
            case 3: return;
            case 4:
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
            default:
            {
                QInputDialog* modifyDialog = new QInputDialog();
                newval = modifyDialog->getText(0, "modify", "New " + key, QLineEdit::Normal,
                                                       val, &dialogResult);
                delete modifyDialog;
            }
            }
            if (newval.length() > 0 && dialogResult)
            {
                if (index == 0)
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
            case 6:
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
                if (dialogResult)
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
            default:
            {
                QInputDialog* modifyDialog = new QInputDialog();
                newval = modifyDialog->getText(0, "modify", "New " + key, QLineEdit::Normal,
                                                       val, &dialogResult);
                delete modifyDialog;
            }
            }
            if (newval.length() > 0 && dialogResult)
            {
                if (index == 1) {
                    for (achi_node* it = cur_org->achievements; it; it = it->next)
                    {
                        if (!strcmp(newval.toLatin1().data(), it->info.result_name))
                        {
                            QMessageBox::critical(0, "Error", newval + " has existed !");
                            return;
                        }
                    }
                    cur_item->setText(0, newval);
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
        if (dialogResult)
        {
            if (index == 1) {
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
            }
            rightmodify = modify_org(this_org, index, newval.toLatin1().data());
        }
        delete modifyDialog;
    }
    if (rightmodify == 1) item->setText(key + QString(": " + newval));
    else if (rightmodify == 2) item->setText(key + QString(": " + QString::number(newval.toInt())));
}

void MainWindow::on_actionInsert_organization_triggered()
{
    qDebug() << "insert org";
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
    if (result == QDialog::Accepted && !nameline.text().isEmpty())
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
    }
}

void MainWindow::on_deleteButton_clicked()
{
    qDebug() << "delete button clicked";
    if (QMessageBox::Yes == QMessageBox::warning(NULL, "warning", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
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

void MainWindow::accept()
{
    myDialog->accept();
}

void MainWindow::reject()
{
    myDialog->reject();
}

void MainWindow::on_insertButton_clicked()
{
    qDebug() << "insert button clicked";
    myDialog = new QDialog;
    QPushButton okbtn("ok");
    QPushButton cancelbtn("cancel");
    connect(&okbtn, SIGNAL(clicked()), this, SLOT(accept()));
    connect(&cancelbtn, SIGNAL(clicked()), this, SLOT(reject()));
    QGridLayout insertlayout;
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
        if (result == QDialog::Accepted && !nameline.text().isEmpty())
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
        if (result == QDialog::Accepted && !nameline.text().isEmpty()) {
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
        }
    }
    resetInfo();
}

void MainWindow::on_searchButton_clicked()
{
    char searchstr[40];
    strcpy(searchstr, ui->searchLine->text().toLatin1().data());
    int min = INT_MAX, dis;
    QTreeWidgetItem* rightItem = 0;
    if (strlen(searchstr) > 0)
    {
        QTreeWidgetItemIterator it(ui->treeWidget);
        while (*it)
        {
            dis = dl_distance((*it)->text(0).toLatin1().data(), searchstr);
            qDebug() << (*it)->text(0) << "  distance: " << dis;
            if (dis < min)
            {
                min = dis;
                rightItem = *it;
                if (dis == 0) break;
            }
            ++it;
        }
        if (!rightItem) return;
        ui->treeWidget->itemClicked(rightItem, 0);
        if (rightItem->parent())
        {
            if (rightItem->parent()->parent())
                ui->treeWidget->expandItem(rightItem->parent()->parent());
            ui->treeWidget->expandItem(rightItem->parent());
        }
    }
}

void MainWindow::on_childList_doubleClicked(const QModelIndex &index)
{
    QString curstr = childlist->currentItem()->text();
    for (int i = 0; i < cur_item->childCount(); ++i)
    {
        if (cur_item->child(i)->text(0) == curstr)
        {
            ui->treeWidget->expandItem(cur_item);
            ui->treeWidget->itemClicked(cur_item->child(i), 0);
        }
    }
}

void MainWindow::on_actionSort_organizations_triggered()
{
    initTree();
}

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
        if (!head)
        {
            QMessageBox::information(this, "no result", "no contributor aged from " + fromline.text() + " to " + toline.text());
        }
        QString info = "";
        for (contr_node* it = head; it; it = it->next)
        {
            info += QString("name: %1\nid: %2\norganization: %3\nachievement: %4\ngender: %5\nage: %6\njob title: %7\nachievement ranking: %8\n\n").arg(
                        it->info.name, it->info.id_num, it->info.org, it->info.result_name, &(it->info.gender), QString::number(it->info.age), it->info.job_title, QString::number(it->info.ranking));
        }
        myDialog = new QDialog;
        myDialog->setWindowTitle("Filter by age from " + fromline.text() + " to " + toline.text());
        QTextEdit textedit;
        textedit.setText(info);
        filterlayout.addWidget(&textedit, 0, 0, 1, 4);
        myDialog->setLayout(&filterlayout);
        myDialog->exec();
        delete_contr_list(head);
    }
}

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
        if (!head)
        {
            QMessageBox::information(this, "no result", "no MVC aged from " + fromline.text() + " to " + toline.text());
        }
        QString info = "";
        for (contr_node* it = head; it; it = it->next)
        {
            info += QString("name: %1\nid: %2\norganization: %3\nachievement: %4\ngender: %5\nage: %6\njob title: %7\nachievement ranking: %8\n\n").arg(
                        it->info.name, it->info.id_num, it->info.org, it->info.result_name, &(it->info.gender), QString::number(it->info.age), it->info.job_title, QString::number(it->info.ranking));
        }
        myDialog = new QDialog;
        myDialog->setWindowTitle("Filter by age from " + fromline.text() + " to " + toline.text());
        QTextEdit textedit;
        textedit.setText(info);
        filterlayout.addWidget(&textedit, 0, 0, 1, 4);
        myDialog->setLayout(&filterlayout);
        myDialog->exec();
        delete_contr_list(head);
    }
}
