/****************************************************************************
** Meta object code from reading C++ file 'DialogObservationDeviceSettings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DialogObservationDeviceSettings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DialogObservationDeviceSettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DialogObservationDeviceSettings_t {
    QByteArrayData data[19];
    char stringdata0[361];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialogObservationDeviceSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialogObservationDeviceSettings_t qt_meta_stringdata_DialogObservationDeviceSettings = {
    {
QT_MOC_LITERAL(0, 0, 31), // "DialogObservationDeviceSettings"
QT_MOC_LITERAL(1, 32, 15), // "setAutoModeling"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 14), // "isAutoModeling"
QT_MOC_LITERAL(4, 64, 27), // "onMileageNumberEditFinished"
QT_MOC_LITERAL(5, 92, 19), // "onTunnelParamUpdate"
QT_MOC_LITERAL(6, 112, 17), // "onSupplyEditClick"
QT_MOC_LITERAL(7, 130, 20), // "onMeasuringEditClick"
QT_MOC_LITERAL(8, 151, 19), // "onSupplyUpdateClick"
QT_MOC_LITERAL(9, 171, 23), // "onMesasuringUpdateClick"
QT_MOC_LITERAL(10, 195, 23), // "onFaceWidthEditFinished"
QT_MOC_LITERAL(11, 219, 24), // "onFaceHeightEditFinished"
QT_MOC_LITERAL(12, 244, 19), // "onFaceXEditFinished"
QT_MOC_LITERAL(13, 264, 19), // "onFaceYEditFinished"
QT_MOC_LITERAL(14, 284, 19), // "onFaceZEditFinished"
QT_MOC_LITERAL(15, 304, 17), // "onComboBoxChanged"
QT_MOC_LITERAL(16, 322, 3), // "pos"
QT_MOC_LITERAL(17, 326, 22), // "onExcavationDirChanged"
QT_MOC_LITERAL(18, 349, 11) // "textChanged"

    },
    "DialogObservationDeviceSettings\0"
    "setAutoModeling\0\0isAutoModeling\0"
    "onMileageNumberEditFinished\0"
    "onTunnelParamUpdate\0onSupplyEditClick\0"
    "onMeasuringEditClick\0onSupplyUpdateClick\0"
    "onMesasuringUpdateClick\0onFaceWidthEditFinished\0"
    "onFaceHeightEditFinished\0onFaceXEditFinished\0"
    "onFaceYEditFinished\0onFaceZEditFinished\0"
    "onComboBoxChanged\0pos\0onExcavationDirChanged\0"
    "textChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialogObservationDeviceSettings[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   92,    2, 0x0a /* Public */,
       5,    0,   93,    2, 0x0a /* Public */,
       6,    0,   94,    2, 0x0a /* Public */,
       7,    0,   95,    2, 0x0a /* Public */,
       8,    0,   96,    2, 0x0a /* Public */,
       9,    0,   97,    2, 0x0a /* Public */,
      10,    0,   98,    2, 0x0a /* Public */,
      11,    0,   99,    2, 0x0a /* Public */,
      12,    0,  100,    2, 0x0a /* Public */,
      13,    0,  101,    2, 0x0a /* Public */,
      14,    0,  102,    2, 0x0a /* Public */,
      15,    1,  103,    2, 0x0a /* Public */,
      17,    1,  106,    2, 0x0a /* Public */,
      18,    0,  109,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,

       0        // eod
};

void DialogObservationDeviceSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DialogObservationDeviceSettings *_t = static_cast<DialogObservationDeviceSettings *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setAutoModeling((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->onMileageNumberEditFinished(); break;
        case 2: _t->onTunnelParamUpdate(); break;
        case 3: _t->onSupplyEditClick(); break;
        case 4: _t->onMeasuringEditClick(); break;
        case 5: _t->onSupplyUpdateClick(); break;
        case 6: _t->onMesasuringUpdateClick(); break;
        case 7: _t->onFaceWidthEditFinished(); break;
        case 8: _t->onFaceHeightEditFinished(); break;
        case 9: _t->onFaceXEditFinished(); break;
        case 10: _t->onFaceYEditFinished(); break;
        case 11: _t->onFaceZEditFinished(); break;
        case 12: _t->onComboBoxChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->onExcavationDirChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->textChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DialogObservationDeviceSettings::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DialogObservationDeviceSettings::setAutoModeling)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject DialogObservationDeviceSettings::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogObservationDeviceSettings.data,
      qt_meta_data_DialogObservationDeviceSettings,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DialogObservationDeviceSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogObservationDeviceSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DialogObservationDeviceSettings.stringdata0))
        return static_cast<void*>(const_cast< DialogObservationDeviceSettings*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogObservationDeviceSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void DialogObservationDeviceSettings::setAutoModeling(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
