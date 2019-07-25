/****************************************************************************
** Meta object code from reading C++ file 'DialogSimuForward.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DialogSimuForward.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DialogSimuForward.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DialogSimuForward_t {
    QByteArrayData data[9];
    char stringdata0[199];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialogSimuForward_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialogSimuForward_t qt_meta_stringdata_DialogSimuForward = {
    {
QT_MOC_LITERAL(0, 0, 17), // "DialogSimuForward"
QT_MOC_LITERAL(1, 18, 11), // "textChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 27), // "onActualLocationXMaxChanged"
QT_MOC_LITERAL(4, 59, 27), // "onActualLocationYMaxChanged"
QT_MOC_LITERAL(5, 87, 27), // "onActualLocationZMaxChanged"
QT_MOC_LITERAL(6, 115, 27), // "onActualLocationXMinChanged"
QT_MOC_LITERAL(7, 143, 27), // "onActualLocationYMinChanged"
QT_MOC_LITERAL(8, 171, 27) // "onActualLocationZMinChanged"

    },
    "DialogSimuForward\0textChanged\0\0"
    "onActualLocationXMaxChanged\0"
    "onActualLocationYMaxChanged\0"
    "onActualLocationZMaxChanged\0"
    "onActualLocationXMinChanged\0"
    "onActualLocationYMinChanged\0"
    "onActualLocationZMinChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialogSimuForward[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x0a /* Public */,
       8,    0,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DialogSimuForward::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DialogSimuForward *_t = static_cast<DialogSimuForward *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->textChanged(); break;
        case 1: _t->onActualLocationXMaxChanged(); break;
        case 2: _t->onActualLocationYMaxChanged(); break;
        case 3: _t->onActualLocationZMaxChanged(); break;
        case 4: _t->onActualLocationXMinChanged(); break;
        case 5: _t->onActualLocationYMinChanged(); break;
        case 6: _t->onActualLocationZMinChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DialogSimuForward::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DialogSimuForward::textChanged)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject DialogSimuForward::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogSimuForward.data,
      qt_meta_data_DialogSimuForward,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DialogSimuForward::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogSimuForward::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DialogSimuForward.stringdata0))
        return static_cast<void*>(const_cast< DialogSimuForward*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogSimuForward::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void DialogSimuForward::textChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
