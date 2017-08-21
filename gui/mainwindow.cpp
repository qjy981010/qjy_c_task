#include <QTreeWidgetItem>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(setInfo(QTreeWidgetItem*,int)));
    initTree();
    infolist = ui->infoList;
    childlist = ui->childList;
    connect(infolist, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(modifyInfo(QListWidgetItem*)));
    ui->deleteButton->setDisabled(1);
    ui->insertButton->setDisabled(1);
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

//void MainWindow::addMyItem(QListWidget* list, QString key, QString val)
//{
//    QListWidgetItem* newitem = new QListWidgetItem(infolist);
//    infolist->addItem(newitem);
//    QWidget* myitem = new QWidget;
//    QHBoxLayout* hbl = new QHBoxLayout(myitem);
//    QLabel* key_lab = new QLabel(key);
//    QLabel* val_lab = new QLabel(val);
//    QPushButton* modifyButton = new QPushButton("modify");

//    hbl->addWidget(key_lab);
//    hbl->addWidget(val_lab);
//    hbl->addWidget(modifyButton);
//    hbl->setSizeConstraint( QLayout::SetFixedSize );
//    myitem->setLayout(hbl);
//    newitem->setSizeHint(myitem->sizeHint());
//    infolist->setItemWidget(newitem, myitem);
//    qDebug() << "add info";
//}

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
            infolist->clear();
            childlist->clear();
            infolist->addItem(QString("id: ") + QString(this_achi->info.result_id));
            infolist->addItem(QString("name: ") + QString(this_achi->info.result_name));
            infolist->addItem(QString("field: ") + QString(this_achi->info.field));
            infolist->addItem(QString("organization: ") + QString(this_achi->info.org));
            infolist->addItem(QString("mvp: ") + QString(this_achi->info.mvp));
            infolist->addItem(QString("price name: ") + QString(this_achi->info.price_name));
            infolist->addItem(QString("price class: ") + QString(this_achi->info.price_class));
            infolist->addItem(QString("price ranking: ") + QString::number(this_achi->info.price_ranking));
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
        infolist->clear();
        childlist->clear();
        infolist->addItem(QString("id: ") + QString(this_org->info.org_id));
        infolist->addItem(QString("name: ") + QString(this_org->info.org_name));
        infolist->addItem(QString("chairman: ") + QString(this_org->info.chairman));
        infolist->addItem(QString("phone: ") + QString(this_org->info.phone_num));
        for (achi_node* it = this_org->achievements; it; it = it->next) {
            childlist->addItem(QString(it->info.result_name));
        }
    }
}

void MainWindow::modifyInfo(QListWidgetItem* item) // 需要字长限制
{
    QStringList pieces = item->text().split( ": " );
    QString key = pieces.value(0);
    QString val = pieces.value(1);
    QInputDialog* modifyDialog = new QInputDialog();
    bool dialogResult;
    QString newval = modifyDialog->getText(0, "modify", "New " + key, QLineEdit::Normal,
                                           val, &dialogResult);
    if (newval.length() > 0 && dialogResult)
    {
        item->setText(key + QString(": " + newval));
        if (cur_item->parent())
        {
            if (cur_item->parent()->parent())
            {
                modify_contr(this_contr, infolist->row(item), newval.toLatin1().data(), newval.toInt());
            }
            else {
                modify_achi(this_achi, infolist->row(item), newval.toLatin1().data(), newval.toInt());
            }
        }
        else {
            modify_org(this_org, infolist->row(item), newval.toLatin1().data());
        }
    }
    delete modifyDialog;
}

void MainWindow::on_actionInsert_organization_triggered()
{
    qDebug() << "insert org";
    insertDialog = new QDialog;
    QPushButton* okbtn = new QPushButton("ok");
    QPushButton* cancelbtn = new QPushButton("cancel");
    connect(okbtn, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelbtn, SIGNAL(clicked()), this, SLOT(reject()));
    QVBoxLayout* insertlayout = new QVBoxLayout;
    insertDialog->setWindowTitle("insert new organization");
    QLineEdit* nameline = new QLineEdit;
    QLineEdit* idline = new QLineEdit;
    QLineEdit* chairmanline = new QLineEdit;
    QLineEdit* phoneline = new QLineEdit;
    QLabel* namelabel = new QLabel("name:");
    QLabel* idlabel = new QLabel("id:");
    QLabel* chairmanlabel = new QLabel("chair man:");
    QLabel* phonelabel = new QLabel("phone number:");
    insertlayout->addWidget(namelabel);
    insertlayout->addWidget(nameline);
    insertlayout->addWidget(idlabel);
    insertlayout->addWidget(idline);
    insertlayout->addWidget(chairmanlabel);
    insertlayout->addWidget(chairmanline);
    insertlayout->addWidget(phonelabel);
    insertlayout->addWidget(phoneline);
    insertlayout->addWidget(okbtn);
    insertlayout->addWidget(cancelbtn);
    insertDialog->setLayout(insertlayout);
    int result = insertDialog->exec();
    if (result == QDialog::Accepted && !nameline->text().isEmpty())
    {
        if (!insert_org(idline->text().toLatin1().data(), nameline->text().toLatin1().data(),
                        chairmanline->text().toLatin1().data(), phoneline->text().toLatin1().data()))
        {
            qDebug() << "name " << nameline->text();
            qDebug() << "id " << idline->text();
            qDebug() << "chairman " << chairmanline->text();
            qDebug() << "phone " << phoneline->text();
            QTreeWidgetItem* org = new QTreeWidgetItem(ui->treeWidget);
            org->setText(0, nameline->text());
        }
    }
    delete nameline;
    delete idline;
    delete chairmanline;
    delete phoneline;
    delete namelabel;
    delete idlabel;
    delete chairmanlabel;
    delete phonelabel;
    delete insertlayout;
    delete okbtn;
    delete cancelbtn;
    delete insertDialog;
}

void MainWindow::on_deleteButton_clicked()
{
    qDebug() << "delete button clicked";
    if (QMessageBox::Yes == QMessageBox::warning(NULL, "warning", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
    {
        if (cur_item->parent()) {
            qDebug() << "delete begin";
            if (cur_item->parent()->parent()) {qDebug() << "delete contr " << this_contr << pre_contr << cur_achi; delete_contr(this_contr, pre_contr, cur_achi);delete this_contr;}
            else {qDebug() << "delete achi"; delete_achi(this_achi, pre_achi, cur_org);}
            qDebug() << "delete over";
        }
        else {
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
    insertDialog->accept();
}

void MainWindow::reject()
{
    insertDialog->reject();
}

void MainWindow::on_insertButton_clicked()
{
    qDebug() << "insert button clicked";
    insertDialog = new QDialog;
    QPushButton* okbtn = new QPushButton("ok");
    QPushButton* cancelbtn = new QPushButton("cancel");
    connect(okbtn, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelbtn, SIGNAL(clicked()), this, SLOT(reject()));
    QVBoxLayout* insertlayout = new QVBoxLayout;
    if (cur_item->parent()) { // insert contributor
        qDebug() << "insert contributor";
        insertDialog->setWindowTitle("insert new contributor");
        QLineEdit* nameline = new QLineEdit;
        QLineEdit* idline = new QLineEdit;
        QLineEdit* genderline = new QLineEdit;
        QLineEdit* ageline = new QLineEdit;
        QLineEdit* titleline = new QLineEdit;
        QLineEdit* rankingline = new QLineEdit;
        QLabel* namelabel = new QLabel("name:");
        QLabel* idlabel = new QLabel("id:");
        QLabel* genderlabel = new QLabel("gender:");
        QLabel* agelabel = new QLabel("age:");
        QLabel* titlelabel = new QLabel("title:");
        QLabel* rankinglabel = new QLabel("ranking:");
        insertlayout->addWidget(namelabel);
        insertlayout->addWidget(nameline);
        insertlayout->addWidget(idlabel);
        insertlayout->addWidget(idline);
        insertlayout->addWidget(genderlabel);
        insertlayout->addWidget(genderline);
        insertlayout->addWidget(agelabel);
        insertlayout->addWidget(ageline);
        insertlayout->addWidget(titlelabel);
        insertlayout->addWidget(titleline);
        insertlayout->addWidget(rankinglabel);
        insertlayout->addWidget(rankingline);
        insertlayout->addWidget(okbtn);
        insertlayout->addWidget(cancelbtn);
        insertDialog->setLayout(insertlayout);
        int result = insertDialog->exec();
        if (result == QDialog::Accepted && !nameline->text().isEmpty())
        {
            if (!insert_contr(this_achi, nameline->text().toLatin1().data(), idline->text().toLatin1().data(),
                              cur_item->parent()->text(0).toLatin1().data(), cur_item->text(0).toLatin1().data(),
                              genderline->text().toStdString()[0], ageline->text().toInt(),
                              titleline->text().toLatin1().data(), rankingline->text().toInt()))
            {
                qDebug() << "name " << nameline->text();
                qDebug() << "id " << idline->text();
                qDebug() << "gender " << genderline->text();
                qDebug() << "age " << ageline->text();
                qDebug() << "title " << titleline->text();
                qDebug() << "ranking " << rankingline->text();
                childlist->addItem(nameline->text());
                QTreeWidgetItem* contr = new QTreeWidgetItem(cur_item);
                contr->setText(0, nameline->text());
            }
        }
        delete nameline;
        delete idline;
        delete genderline;
        delete ageline;
        delete titleline;
        delete rankingline;
        delete namelabel;
        delete idlabel;
        delete genderlabel;
        delete agelabel;
        delete titlelabel;
        delete rankinglabel;
        delete insertlayout;
    }
    else { // insert achievement
        qDebug() << "insert achievement";
        insertDialog->setWindowTitle("insert new achievement");
        QLineEdit* nameline = new QLineEdit;
        QLineEdit* idline = new QLineEdit;
        QLineEdit* fieldline = new QLineEdit;
        QLineEdit* mvpline = new QLineEdit;
        QLineEdit* pricenameline = new QLineEdit;
        QLineEdit* priceclassline = new QLineEdit;
        QLineEdit* pricerankingline = new QLineEdit;
        QLabel* namelabel = new QLabel("name:");
        QLabel* idlabel = new QLabel("id:");
        QLabel* fieldlabel = new QLabel("field:");
        QLabel* mvplabel = new QLabel("mvp:");
        QLabel* pricenamelabel = new QLabel("price name:");
        QLabel* priceclasslabel = new QLabel("price class:");
        QLabel* pricerankinglabel = new QLabel("price ranking:");
        insertlayout->addWidget(idlabel);
        insertlayout->addWidget(idline);
        insertlayout->addWidget(namelabel);
        insertlayout->addWidget(nameline);
        insertlayout->addWidget(fieldlabel);
        insertlayout->addWidget(fieldline);
        insertlayout->addWidget(mvplabel);
        insertlayout->addWidget(mvpline);
        insertlayout->addWidget(pricenamelabel);
        insertlayout->addWidget(pricenameline);
        insertlayout->addWidget(priceclasslabel);
        insertlayout->addWidget(priceclassline);
        insertlayout->addWidget(pricerankinglabel);
        insertlayout->addWidget(pricerankingline);
        insertlayout->addWidget(okbtn);
        insertlayout->addWidget(cancelbtn);
        insertDialog->setLayout(insertlayout);
        int result = insertDialog->exec();
        if (result == QDialog::Accepted && !nameline->text().isEmpty()) {
            if (insert_achi(this_org, idline->text().toLatin1().data(), nameline->text().toLatin1().data(),
                            fieldline->text().toLatin1().data(), cur_item->text(0).toLatin1().data(),
                            mvpline->text().toLatin1().data(), pricenameline->text().toLatin1().data(),
                            priceclassline->text().toLatin1().data(), pricerankingline->text().toInt()))
            qDebug() << "name " << nameline->text().toLatin1().data();
            qDebug() << "id " << idline->text().toLatin1().data();
            qDebug() << "field " << fieldline->text().toLatin1().data();
            qDebug() << "mvp " << mvpline->text().toLatin1().data();
            qDebug() << "price name " << pricenameline->text().toLatin1().data();
            qDebug() << "price class " << priceclassline->text().toLatin1().data();
            qDebug() << "price ranking " << pricerankingline->text().toLatin1().data();
            childlist->addItem(nameline->text());
            QTreeWidgetItem* achi = new QTreeWidgetItem(cur_item);
            achi->setText(0, nameline->text());
        }
        delete nameline;
        delete idline;
        delete fieldline;
        delete mvpline;
        delete pricenameline;
        delete priceclassline;
        delete pricerankingline;
        delete namelabel;
        delete idlabel;
        delete fieldlabel;
        delete mvplabel;
        delete pricenamelabel;
        delete priceclasslabel;
        delete pricerankinglabel;
        delete insertlayout;
    }
    delete okbtn;
    delete cancelbtn;
    delete insertDialog;
}
