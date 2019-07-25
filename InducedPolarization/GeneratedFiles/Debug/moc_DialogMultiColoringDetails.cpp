/****************************************************************************
** Meta object code from reading C++ file 'DialogMultiColoringDetails.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DialogMultiColoringDetails.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DialogMultiColoringDetails.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DialogMultiColoringDetails_t {
    QByteArrayData data[11];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialogMultiColoringDetails_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialogMultiColoringDetails_t qt_meta_stringdata_DialogMultiColoringDetails = {
    {
QT_MOC_LITERAL(0, 0, 26), // "DialogMultiColoringDetails"
QT_MOC_LITERAL(1, 27, 12), // "setTextRange"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 8), // "minLevel"
QT_MOC_LITERAL(4, 50, 8), // "maxLevel"
QT_MOC_LITERAL(5, 59, 13), // "numberOfLevel"
QT_MOC_LITERAL(6, 73, 17), // "setColorGroupName"
QT_MOC_LITERAL(7, 91, 4), // "name"
QT_MOC_LITERAL(8, 96, 13), // "enterNewLevel"
QT_MOC_LITERAL(9, 110, 17), // "colorGroupChanged"
QT_MOC_LITERAL(10, 128, 4) // "text"

    },
    "DialogMultiColoringDetails\0setTextRange\0"
    "\0minLevel\0maxLevel\0numberOfLevel\0"
    "setColorGroupName\0name\0enterNewLevel\0"
    "colorGroupChanged\0text"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialogMultiColoringDetails[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   34,    2, 0x06 /* Public */,
       6,    1,   41,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   44,    2, 0x0a /* Public */,
       9,    1,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Int,    3,    4,    5,
    QMetaType::Void, QMetaType::QString,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,

       0        // eod
};

void DialogMultiColoringDetails::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DialogMultiColoringDetails *_t = static_cast<DialogMultiColoringDetails *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setTextRange((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->setColorGroupName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->enterNewLevel(); break;
        case 3: _t->colorGroupChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DialogMultiColoringDetails::*_t)(float , float , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DialogMultiColoringDetails::setTextRange)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DialogMultiColoringDetails::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DialogMultiColoringDetails::setColorGroupName)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject DialogMultiColoringDetails::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogMultiColoringDetails.data,
      qt_meta_data_DialogMultiColoringDetails,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DialogMultiColoringDetails::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogMultiColoringDetails::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DialogMultiColoringDetails.stringdata0))
        return static_cast<void*>(const_cast< DialogMultiColoringDetails*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogMultiColoringDetails::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void DialogMultiColoringDetails::setTextRange(float _t1, float _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DialogMultiColoringDetails::setColorGroupName(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
