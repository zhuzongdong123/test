/****************************************************************************
** Meta object code from reading C++ file 'MyPushButtonH.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MyPushButtonH.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyPushButtonH.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyPushButtonH_t {
    QByteArrayData data[10];
    char stringdata0[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyPushButtonH_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyPushButtonH_t qt_meta_stringdata_MyPushButtonH = {
    {
QT_MOC_LITERAL(0, 0, 13), // "MyPushButtonH"
QT_MOC_LITERAL(1, 14, 21), // "redrawCoordinateVText"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 13), // "begChannelDis"
QT_MOC_LITERAL(4, 51, 13), // "endChannelDis"
QT_MOC_LITERAL(5, 65, 4), // "name"
QT_MOC_LITERAL(6, 70, 9), // "isChanged"
QT_MOC_LITERAL(7, 80, 15), // "begChannelIndex"
QT_MOC_LITERAL(8, 96, 15), // "endChannelIndex"
QT_MOC_LITERAL(9, 112, 10) // "waveNumber"

    },
    "MyPushButtonH\0redrawCoordinateVText\0"
    "\0begChannelDis\0endChannelDis\0name\0"
    "isChanged\0begChannelIndex\0endChannelIndex\0"
    "waveNumber"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyPushButtonH[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x0a /* Public */,
       1,    4,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::QString,    3,    4,    5,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int, QMetaType::Int, QMetaType::Int,    6,    7,    8,    9,

       0        // eod
};

void MyPushButtonH::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyPushButtonH *_t = static_cast<MyPushButtonH *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->redrawCoordinateVText((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->redrawCoordinateVText((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        default: ;
        }
    }
}

const QMetaObject MyPushButtonH::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_MyPushButtonH.data,
      qt_meta_data_MyPushButtonH,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MyPushButtonH::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyPushButtonH::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyPushButtonH.stringdata0))
        return static_cast<void*>(const_cast< MyPushButtonH*>(this));
    return QPushButton::qt_metacast(_clname);
}

int MyPushButtonH::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
