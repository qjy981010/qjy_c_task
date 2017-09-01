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
#include <QtWidgets/QLineEdit>
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
    QAction *actionInsert_organization;
    QAction *actionSort_organizations;
    QAction *actionsearch_among_MVC;
    QAction *actionSearch_among_contributors;
    QAction *actionHelp_document;
    QAction *actionAbout_us;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionClose;
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *searchLine;
    QPushButton *searchButton;
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
    QMenu *menuInsert;
    QMenu *menuStatistics;
    QMenu *menu_filter_by_age;
    QMenu *menuhelp;
    QMenu *menuFile;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1070, 640);
        actionInsert_organization = new QAction(MainWindow);
        actionInsert_organization->setObjectName(QStringLiteral("actionInsert_organization"));
        actionSort_organizations = new QAction(MainWindow);
        actionSort_organizations->setObjectName(QStringLiteral("actionSort_organizations"));
        actionsearch_among_MVC = new QAction(MainWindow);
        actionsearch_among_MVC->setObjectName(QStringLiteral("actionsearch_among_MVC"));
        actionSearch_among_contributors = new QAction(MainWindow);
        actionSearch_among_contributors->setObjectName(QStringLiteral("actionSearch_among_contributors"));
        actionHelp_document = new QAction(MainWindow);
        actionHelp_document->setObjectName(QStringLiteral("actionHelp_document"));
        actionAbout_us = new QAction(MainWindow);
        actionAbout_us->setObjectName(QStringLiteral("actionAbout_us"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 1051, 591));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));

        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        searchLine = new QLineEdit(layoutWidget);
        searchLine->setObjectName(QStringLiteral("searchLine"));

        horizontalLayout_2->addWidget(searchLine);

        searchButton = new QPushButton(layoutWidget);
        searchButton->setObjectName(QStringLiteral("searchButton"));
        searchButton->setAutoDefault(false);

        horizontalLayout_2->addWidget(searchButton);


        verticalLayout_4->addLayout(horizontalLayout_2);

        treeWidget = new QTreeWidget(layoutWidget);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setSortingEnabled(false);

        verticalLayout_4->addWidget(treeWidget);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        info_label = new QLabel(layoutWidget);
        info_label->setObjectName(QStringLiteral("info_label"));

        verticalLayout_2->addWidget(info_label);

        infoList = new QListWidget(layoutWidget);
        infoList->setObjectName(QStringLiteral("infoList"));

        verticalLayout_2->addWidget(infoList);

        deleteButton = new QPushButton(layoutWidget);
        deleteButton->setObjectName(QStringLiteral("deleteButton"));

        verticalLayout_2->addWidget(deleteButton);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        childClass = new QLabel(layoutWidget);
        childClass->setObjectName(QStringLiteral("childClass"));

        verticalLayout->addWidget(childClass);

        childList = new QListWidget(layoutWidget);
        childList->setObjectName(QStringLiteral("childList"));

        verticalLayout->addWidget(childList);

        insertButton = new QPushButton(layoutWidget);
        insertButton->setObjectName(QStringLiteral("insertButton"));

        verticalLayout->addWidget(insertButton);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1070, 30));
        menuInsert = new QMenu(menuBar);
        menuInsert->setObjectName(QStringLiteral("menuInsert"));
        menuStatistics = new QMenu(menuBar);
        menuStatistics->setObjectName(QStringLiteral("menuStatistics"));
        menu_filter_by_age = new QMenu(menuStatistics);
        menu_filter_by_age->setObjectName(QStringLiteral("menu_filter_by_age"));
        menuhelp = new QMenu(menuBar);
        menuhelp->setObjectName(QStringLiteral("menuhelp"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuInsert->menuAction());
        menuBar->addAction(menuStatistics->menuAction());
        menuBar->addAction(menuhelp->menuAction());
        menuInsert->addAction(actionInsert_organization);
        menuInsert->addAction(actionSort_organizations);
        menuStatistics->addAction(menu_filter_by_age->menuAction());
        menu_filter_by_age->addAction(actionsearch_among_MVC);
        menu_filter_by_age->addAction(actionSearch_among_contributors);
        menuhelp->addAction(actionHelp_document);
        menuhelp->addAction(actionAbout_us);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionClose);

        retranslateUi(MainWindow);

        searchButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionInsert_organization->setText(QApplication::translate("MainWindow", "&New organization", Q_NULLPTR));
        actionSort_organizations->setText(QApplication::translate("MainWindow", "&Sort organizations", Q_NULLPTR));
        actionsearch_among_MVC->setText(QApplication::translate("MainWindow", "&Search among MVC", Q_NULLPTR));
        actionSearch_among_contributors->setText(QApplication::translate("MainWindow", "Search among &contributors", Q_NULLPTR));
        actionHelp_document->setText(QApplication::translate("MainWindow", "&Help document", Q_NULLPTR));
        actionAbout_us->setText(QApplication::translate("MainWindow", "&About us", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("MainWindow", "Open file", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionSave->setText(QApplication::translate("MainWindow", "Save file", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionClose->setText(QApplication::translate("MainWindow", "Close file", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionClose->setShortcut(QApplication::translate("MainWindow", "Ctrl+W", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        searchButton->setText(QApplication::translate("MainWindow", "search", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        searchButton->setShortcut(QApplication::translate("MainWindow", "Enter, Return", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "organizations", Q_NULLPTR));
        info_label->setText(QApplication::translate("MainWindow", "Information", Q_NULLPTR));
        deleteButton->setText(QApplication::translate("MainWindow", "delete", Q_NULLPTR));
        childClass->setText(QApplication::translate("MainWindow", "Achievements or Contributors", Q_NULLPTR));
        insertButton->setText(QApplication::translate("MainWindow", "insert", Q_NULLPTR));
        menuInsert->setTitle(QApplication::translate("MainWindow", "&Manage", Q_NULLPTR));
        menuStatistics->setTitle(QApplication::translate("MainWindow", "Statistics", Q_NULLPTR));
        menu_filter_by_age->setTitle(QApplication::translate("MainWindow", "&filter by age", Q_NULLPTR));
        menuhelp->setTitle(QApplication::translate("MainWindow", "he&lp", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
