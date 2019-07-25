/****************************************************************************
** Meta object code from reading C++ file 'MyColorButton.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MyColorButton.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyColorButton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyColorButton_t {
    QByteArrayData data[9];
    char stringdata0[89];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyColorButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyColorButton_t qt_meta_stringdata_MyColorButton = {
    {
QT_MOC_LITERAL(0, 0, 13), // "MyColorButton"
QT_MOC_LITERAL(1, 14, 12), // "colorChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 12), // "setTextRange"
QT_MOC_LITERAL(4, 41, 8), // "minValue"
QT_MOC_LITERAL(5, 50, 8), // "maxValue"
QT_MOC_LITERAL(6, 59, 6), // "number"
QT_MOC_LITERAL(7, 66, 17), // "setColorGroupName"
QT_MOC_LITERAL(8, 84, 4) // "name"

    },
    "MyColorButton\0colorChanged\0\0setTextRange\0"
    "minValue\0maxValue\0number\0setColorGroupName\0"
    "name"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyColorButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    3,   35,    2, 0x08 /* Private */,
       3,    2,   42,    2, 0x08 /* Private */,
       7,    1,   47,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Int,    4,    5,    6,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,    4,    5,
    QMetaType::Void, QMetaType::QString,    8,

       0        // eod
};

void MyColorButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyColorButton *_t = static_cast<MyColorButton *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->colorChanged(); break;
        case 1: _t->setTextRange((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->setTextRange((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 3: _t->setColorGroupName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MyColorButton::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyColorButton::colorChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MyColorButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_MyColorButton.data,
      qt_meta_data_MyColorButton,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MyColorButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyColorButton::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyColorButton.stringdata0))
        return static_cast<void*>(const_cast< MyColorButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int MyColorButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MyColorButton::colorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
