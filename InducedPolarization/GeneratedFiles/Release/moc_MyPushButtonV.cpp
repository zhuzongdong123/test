/****************************************************************************
** Meta object code from reading C++ file 'MyPushButtonV.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MyPushButtonV.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyPushButtonV.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyPushButtonV_t {
    QByteArrayData data[6];
    char stringdata0[45];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyPushButtonV_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyPushButtonV_t qt_meta_stringdata_MyPushButtonV = {
    {
QT_MOC_LITERAL(0, 0, 13), // "MyPushButtonV"
QT_MOC_LITERAL(1, 14, 6), // "reDraw"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 8), // "minValue"
QT_MOC_LITERAL(4, 31, 8), // "maxValue"
QT_MOC_LITERAL(5, 40, 4) // "name"

    },
    "MyPushButtonV\0reDraw\0\0minValue\0maxValue\0"
    "name"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyPushButtonV[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::QString,    3,    4,    5,

       0        // eod
};

void MyPushButtonV::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyPushButtonV *_t = static_cast<MyPushButtonV *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->reDraw((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject MyPushButtonV::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_MyPushButtonV.data,
      qt_meta_data_MyPushButtonV,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MyPushButtonV::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyPushButtonV::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyPushButtonV.stringdata0))
        return static_cast<void*>(const_cast< MyPushButtonV*>(this));
    return QPushButton::qt_metacast(_clname);
}

int MyPushButtonV::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
