/****************************************************************************
** Meta object code from reading C++ file 'LogSystem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LogSystem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LogSystem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LogSystem_t {
    QByteArrayData data[5];
    char stringdata0[47];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LogSystem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LogSystem_t qt_meta_stringdata_LogSystem = {
    {
QT_MOC_LITERAL(0, 0, 9), // "LogSystem"
QT_MOC_LITERAL(1, 10, 13), // "writeToDialog"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 15), // "onWriteToDialog"
QT_MOC_LITERAL(4, 41, 5) // "value"

    },
    "LogSystem\0writeToDialog\0\0onWriteToDialog\0"
    "value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LogSystem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    4,

       0        // eod
};

void LogSystem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LogSystem *_t = static_cast<LogSystem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->writeToDialog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->onWriteToDialog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (LogSystem::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LogSystem::writeToDialog)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject LogSystem::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_LogSystem.data,
      qt_meta_data_LogSystem,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *LogSystem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LogSystem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LogSystem.stringdata0))
        return static_cast<void*>(const_cast< LogSystem*>(this));
    return QThread::qt_metacast(_clname);
}

int LogSystem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void LogSystem::writeToDialog(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
