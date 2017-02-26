/****************************************************************************
** Meta object code from reading C++ file 'mysortfilterproxymodel.h'
**
** Created: Sat Oct 25 20:39:13 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mysortfilterproxymodel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mysortfilterproxymodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MySortFilterProxyModel[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_MySortFilterProxyModel[] = {
    "MySortFilterProxyModel\0"
};

const QMetaObject MySortFilterProxyModel::staticMetaObject = {
    { &QSortFilterProxyModel::staticMetaObject, qt_meta_stringdata_MySortFilterProxyModel,
      qt_meta_data_MySortFilterProxyModel, 0 }
};

const QMetaObject *MySortFilterProxyModel::metaObject() const
{
    return &staticMetaObject;
}

void *MySortFilterProxyModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MySortFilterProxyModel))
        return static_cast<void*>(const_cast< MySortFilterProxyModel*>(this));
    return QSortFilterProxyModel::qt_metacast(_clname);
}

int MySortFilterProxyModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSortFilterProxyModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
