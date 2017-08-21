#include "mylistitem.h"
#include "ui_mylistitem.h"

MyListItem::MyListItem(QString newkey, QString newval, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyListItem)
{
    ui->setupUi(this);
    ui->key->setText(newkey);
    ui->val->setText(newval);
    ui->horizontalLayout->setSizeConstraint( QLayout::SetFixedSize );
}

MyListItem::~MyListItem()
{
    delete ui;
}
