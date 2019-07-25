/****************************************************************************
** Meta object code from reading C++ file 'DialogModeling.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DialogModeling.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DialogModeling.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DialogModeling_t {
    QByteArrayData data[10];
    char stringdata0[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialogModeling_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialogModeling_t qt_meta_stringdata_DialogModeling = {
    {
QT_MOC_LITERAL(0, 0, 14), // "DialogModeling"
QT_MOC_LITERAL(1, 15, 14), // "creatModelData"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 9), // "is_folder"
QT_MOC_LITERAL(4, 41, 10), // "is_level_2"
QT_MOC_LITERAL(5, 52, 9), // "item_name"
QT_MOC_LITERAL(6, 62, 8), // "editData"
QT_MOC_LITERAL(7, 71, 10), // "updateData"
QT_MOC_LITERAL(8, 82, 23), // "invertBeginZTextChanged"
QT_MOC_LITERAL(9, 106, 4) // "text"

    },
    "DialogModeling\0creatModelData\0\0is_folder\0"
    "is_level_2\0item_name\0editData\0updateData\0"
    "invertBeginZTextChanged\0text"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialogModeling[] = {

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
       1,    3,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   41,    2, 0x0a /* Public */,
       7,    0,   42,    2, 0x0a /* Public */,
       8,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool, QMetaType::QString,    3,    4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,

       0        // eod
};

void DialogModeling::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DialogModeling *_t = static_cast<DialogModeling *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->creatModelData((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->editData(); break;
        case 2: _t->updateData(); break;
        case 3: _t->invertBeginZTextChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DialogModeling::*_t)(bool , bool , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DialogModeling::creatModelData)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject DialogModeling::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogModeling.data,
      qt_meta_data_DialogModeling,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DialogModeling::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogModeling::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DialogModeling.stringdata0))
        return static_cast<void*>(const_cast< DialogModeling*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogModeling::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void DialogModeling::creatModelData(bool _t1, bool _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
