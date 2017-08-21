/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionModify_organization;
    QAction *actionModify_achievement;
    QAction *actionModify_contributor;
    QAction *actionDelete_organization;
    QAction *actionDelete_achievement;
    QAction *actionDelete_contributor;
    QAction *actionInsert_organization;
    QAction *actionInsert_achievement;
    QAction *actionInsert_contributor;
    QWidget *centralWidget;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QTreeWidget *treeWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *info_label;
    QListWidget *infoList;
    QPushButton *deleteButton;
    QVBoxLayout *verticalLayout;
    QLabel *childClass;
    QListWidget *childList;
    QPushButton *insertButton;
    QMenuBar *menuBar;
    QMenu *menuModify;
    QMenu *menuDelete;
    QMenu *menuInsert;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1070, 640);
        actionModify_organization = new QAction(MainWindow);
        actionModify_organization->setObjectName(QStringLiteral("actionModify_organization"));
        actionModify_achievement = new QAction(MainWindow);
        actionModify_achievement->setObjectName(QStringLiteral("actionModify_achievement"));
        actionModify_contributor = new QAction(MainWindow);
        actionModify_contributor->setObjectName(QStringLiteral("actionModify_contributor"));
        actionDelete_organization = new QAction(MainWindow);
        actionDelete_organization->setObjectName(QStringLiteral("actionDelete_organization"));
        actionDelete_achievement = new QAction(MainWindow);
        actionDelete_achievement->setObjectName(QStringLiteral("actionDelete_achievement"));
        actionDelete_contributor = new QAction(MainWindow);
        actionDelete_contributor->setObjectName(QStringLiteral("actionDelete_contributor"));
        actionInsert_organization = new QAction(MainWindow);
        actionInsert_organization->setObjectName(QStringLiteral("actionInsert_organization"));
        actionInsert_achievement = new QAction(MainWindow);
        actionInsert_achievement->setObjectName(QStringLiteral("actionInsert_achievement"));
        actionInsert_contributor = new QAction(MainWindow);
        actionInsert_contributor->setObjectName(QStringLiteral("actionInsert_contributor"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 0, 1051, 591));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        treeWidget = new QTreeWidget(widget);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        horizontalLayout->addWidget(treeWidget);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        info_label = new QLabel(widget);
        info_label->setObjectName(QStringLiteral("info_label"));

        verticalLayout_2->addWidget(info_label);

        infoList = new QListWidget(widget);
        infoList->setObjectName(QStringLiteral("infoList"));

        verticalLayout_2->addWidget(infoList);

        deleteButton = new QPushButton(widget);
        deleteButton->setObjectName(QStringLiteral("deleteButton"));

        verticalLayout_2->addWidget(deleteButton);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        childClass = new QLabel(widget);
        childClass->setObjectName(QStringLiteral("childClass"));

        verticalLayout->addWidget(childClass);

        childList = new QListWidget(widget);
        childList->setObjectName(QStringLiteral("childList"));

        verticalLayout->addWidget(childList);

        insertButton = new QPushButton(widget);
        insertButton->setObjectName(QStringLiteral("insertButton"));

        verticalLayout->addWidget(insertButton);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1070, 30));
        menuModify = new QMenu(menuBar);
        menuModify->setObjectName(QStringLiteral("menuModify"));
        menuDelete = new QMenu(menuBar);
        menuDelete->setObjectName(QStringLiteral("menuDelete"));
        menuInsert = new QMenu(menuBar);
        menuInsert->setObjectName(QStringLiteral("menuInsert"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuInsert->menuAction());
        menuBar->addAction(menuModify->menuAction());
        menuBar->addAction(menuDelete->menuAction());
        menuModify->addAction(actionModify_organization);
        menuModify->addAction(actionModify_achievement);
        menuModify->addAction(actionModify_contributor);
        menuDelete->addAction(actionDelete_organization);
        menuDelete->addAction(actionDelete_achievement);
        menuDelete->addAction(actionDelete_contributor);
        menuInsert->addAction(actionInsert_organization);
        menuInsert->addAction(actionInsert_achievement);
        menuInsert->addAction(actionInsert_contributor);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionModify_organization->setText(QApplication::translate("MainWindow", "&Modify organization", Q_NULLPTR));
        actionModify_achievement->setText(QApplication::translate("MainWindow", "M&odify achievement", Q_NULLPTR));
        actionModify_contributor->setText(QApplication::translate("MainWindow", "Modify &contributor", Q_NULLPTR));
        actionDelete_organization->setText(QApplication::translate("MainWindow", "&Delete organization", Q_NULLPTR));
        actionDelete_achievement->setText(QApplication::translate("MainWindow", "D&elete achievement", Q_NULLPTR));
        actionDelete_contributor->setText(QApplication::translate("MainWindow", "Delete &contributor", Q_NULLPTR));
        actionInsert_organization->setText(QApplication::translate("MainWindow", "&Insert organization", Q_NULLPTR));
        actionInsert_achievement->setText(QApplication::translate("MainWindow", "I&nsert achievement", Q_NULLPTR));
        actionInsert_contributor->setText(QApplication::translate("MainWindow", "Insert &contributor", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "organizations", Q_NULLPTR));
        info_label->setText(QApplication::translate("MainWindow", "Information", Q_NULLPTR));
        deleteButton->setText(QApplication::translate("MainWindow", "delete", Q_NULLPTR));
        childClass->setText(QApplication::translate("MainWindow", "Achievements or Contributors", Q_NULLPTR));
        insertButton->setText(QApplication::translate("MainWindow", "insert", Q_NULLPTR));
        menuModify->setTitle(QApplication::translate("MainWindow", "&Modify", Q_NULLPTR));
        menuDelete->setTitle(QApplication::translate("MainWindow", "De&lete", Q_NULLPTR));
        menuInsert->setTitle(QApplication::translate("MainWindow", "I&nsert", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
