/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gui/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[351];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 7), // "setInfo"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(4, 37, 4), // "item"
QT_MOC_LITERAL(5, 42, 3), // "num"
QT_MOC_LITERAL(6, 46, 10), // "modifyInfo"
QT_MOC_LITERAL(7, 57, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(8, 74, 38), // "on_actionInsert_organization_..."
QT_MOC_LITERAL(9, 113, 23), // "on_deleteButton_clicked"
QT_MOC_LITERAL(10, 137, 23), // "on_insertButton_clicked"
QT_MOC_LITERAL(11, 161, 6), // "accept"
QT_MOC_LITERAL(12, 168, 6), // "reject"
QT_MOC_LITERAL(13, 175, 23), // "on_searchButton_clicked"
QT_MOC_LITERAL(14, 199, 26), // "on_childList_doubleClicked"
QT_MOC_LITERAL(15, 226, 5), // "index"
QT_MOC_LITERAL(16, 232, 37), // "on_actionSort_organizations_t..."
QT_MOC_LITERAL(17, 270, 44), // "on_actionSearch_among_contrib..."
QT_MOC_LITERAL(18, 315, 35) // "on_actionsearch_among_MVC_tri..."

    },
    "MainWindow\0setInfo\0\0QTreeWidgetItem*\0"
    "item\0num\0modifyInfo\0QListWidgetItem*\0"
    "on_actionInsert_organization_triggered\0"
    "on_deleteButton_clicked\0on_insertButton_clicked\0"
    "accept\0reject\0on_searchButton_clicked\0"
    "on_childList_doubleClicked\0index\0"
    "on_actionSort_organizations_triggered\0"
    "on_actionSearch_among_contributors_triggered\0"
    "on_actionsearch_among_MVC_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x08 /* Private */,
       6,    1,   79,    2, 0x08 /* Private */,
       8,    0,   82,    2, 0x08 /* Private */,
       9,    0,   83,    2, 0x08 /* Private */,
      10,    0,   84,    2, 0x08 /* Private */,
      11,    0,   85,    2, 0x08 /* Private */,
      12,    0,   86,    2, 0x08 /* Private */,
      13,    0,   87,    2, 0x08 /* Private */,
      14,    1,   88,    2, 0x08 /* Private */,
      16,    0,   91,    2, 0x08 /* Private */,
      17,    0,   92,    2, 0x08 /* Private */,
      18,    0,   93,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setInfo((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->modifyInfo((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->on_actionInsert_organization_triggered(); break;
        case 3: _t->on_deleteButton_clicked(); break;
        case 4: _t->on_insertButton_clicked(); break;
        case 5: _t->accept(); break;
        case 6: _t->reject(); break;
        case 7: _t->on_searchButton_clicked(); break;
        case 8: _t->on_childList_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 9: _t->on_actionSort_organizations_triggered(); break;
        case 10: _t->on_actionSearch_among_contributors_triggered(); break;
        case 11: _t->on_actionsearch_among_MVC_triggered(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
