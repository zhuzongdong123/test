/****************************************************************************
** Meta object code from reading C++ file 'DialogContourLevels.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DialogContourLevels.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DialogContourLevels.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DialogContourLevels_t {
    QByteArrayData data[9];
    char stringdata0[164];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialogContourLevels_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialogContourLevels_t qt_meta_stringdata_DialogContourLevels = {
    {
QT_MOC_LITERAL(0, 0, 19), // "DialogContourLevels"
QT_MOC_LITERAL(1, 20, 18), // "onClickExactLevels"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 24), // "onClickApproximateLevels"
QT_MOC_LITERAL(4, 65, 25), // "onClickRangeDistribution0"
QT_MOC_LITERAL(5, 91, 25), // "onClickRangeDistribution1"
QT_MOC_LITERAL(6, 117, 25), // "onClickRangeDistribution2"
QT_MOC_LITERAL(7, 143, 10), // "resetRange"
QT_MOC_LITERAL(8, 154, 9) // "onClickOK"

    },
    "DialogContourLevels\0onClickExactLevels\0"
    "\0onClickApproximateLevels\0"
    "onClickRangeDistribution0\0"
    "onClickRangeDistribution1\0"
    "onClickRangeDistribution2\0resetRange\0"
    "onClickOK"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialogContourLevels[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x0a /* Public */,
       8,    0,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DialogContourLevels::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DialogContourLevels *_t = static_cast<DialogContourLevels *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onClickExactLevels(); break;
        case 1: _t->onClickApproximateLevels(); break;
        case 2: _t->onClickRangeDistribution0(); break;
        case 3: _t->onClickRangeDistribution1(); break;
        case 4: _t->onClickRangeDistribution2(); break;
        case 5: _t->resetRange(); break;
        case 6: _t->onClickOK(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject DialogContourLevels::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogContourLevels.data,
      qt_meta_data_DialogContourLevels,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DialogContourLevels::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogContourLevels::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DialogContourLevels.stringdata0))
        return static_cast<void*>(const_cast< DialogContourLevels*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogContourLevels::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
