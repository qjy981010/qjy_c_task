/********************************************************************************
** Form generated from reading UI file 'mylistitem.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYLISTITEM_H
#define UI_MYLISTITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyListItem
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *key;
    QLabel *val;
    QPushButton *modifyButton;

    void setupUi(QWidget *MyListItem)
    {
        if (MyListItem->objectName().isEmpty())
            MyListItem->setObjectName(QStringLiteral("MyListItem"));
        MyListItem->resize(322, 36);
        widget = new QWidget(MyListItem);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 321, 36));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        key = new QLabel(widget);
        key->setObjectName(QStringLiteral("key"));

        horizontalLayout->addWidget(key);

        val = new QLabel(widget);
        val->setObjectName(QStringLiteral("val"));

        horizontalLayout->addWidget(val);

        modifyButton = new QPushButton(widget);
        modifyButton->setObjectName(QStringLiteral("modifyButton"));

        horizontalLayout->addWidget(modifyButton);


        retranslateUi(MyListItem);

        QMetaObject::connectSlotsByName(MyListItem);
    } // setupUi

    void retranslateUi(QWidget *MyListItem)
    {
        MyListItem->setWindowTitle(QApplication::translate("MyListItem", "Form", Q_NULLPTR));
        key->setText(QApplication::translate("MyListItem", "TextLabel", Q_NULLPTR));
        val->setText(QApplication::translate("MyListItem", "TextLabel", Q_NULLPTR));
        modifyButton->setText(QApplication::translate("MyListItem", "modify", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MyListItem: public Ui_MyListItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYLISTITEM_H
