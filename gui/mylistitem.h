#ifndef MYLISTITEM_H
#define MYLISTITEM_H

#include <QWidget>

namespace Ui {
class MyListItem;
}

class MyListItem : public QWidget
{
    Q_OBJECT

public:
    explicit MyListItem(QString newkey, QString newval, QWidget *parent = 0);
    ~MyListItem();

private:
    Ui::MyListItem *ui;
};

#endif // MYLISTITEM_H
