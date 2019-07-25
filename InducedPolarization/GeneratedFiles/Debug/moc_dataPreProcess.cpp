/****************************************************************************
** Meta object code from reading C++ file 'dataPreProcess.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/3ddisplay/dataPreProcess/dataPreProcess.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dataPreProcess.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DataPreprocess_t {
    QByteArrayData data[3];
    char stringdata0[23];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataPreprocess_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataPreprocess_t qt_meta_stringdata_DataPreprocess = {
    {
QT_MOC_LITERAL(0, 0, 14), // "DataPreprocess"
QT_MOC_LITERAL(1, 15, 6), // "reDraw"
QT_MOC_LITERAL(2, 22, 0) // ""

    },
    "DataPreprocess\0reDraw\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataPreprocess[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void DataPreprocess::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DataPreprocess *_t = static_cast<DataPreprocess *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->reDraw(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DataPreprocess::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataPreprocess::reDraw)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject DataPreprocess::staticMetaObject = {
    { &ViewerWidget::staticMetaObject, qt_meta_stringdata_DataPreprocess.data,
      qt_meta_data_DataPreprocess,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DataPreprocess::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataPreprocess::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DataPreprocess.stringdata0))
        return static_cast<void*>(const_cast< DataPreprocess*>(this));
    return ViewerWidget::qt_metacast(_clname);
}

int DataPreprocess::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ViewerWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void DataPreprocess::reDraw()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
