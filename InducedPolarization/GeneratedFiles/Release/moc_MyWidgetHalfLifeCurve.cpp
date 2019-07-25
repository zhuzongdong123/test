/****************************************************************************
** Meta object code from reading C++ file 'MyWidgetHalfLifeCurve.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MyWidgetHalfLifeCurve.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyWidgetHalfLifeCurve.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyWidgetHalfLifeCurve_t {
    QByteArrayData data[11];
    char stringdata0[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyWidgetHalfLifeCurve_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyWidgetHalfLifeCurve_t qt_meta_stringdata_MyWidgetHalfLifeCurve = {
    {
QT_MOC_LITERAL(0, 0, 21), // "MyWidgetHalfLifeCurve"
QT_MOC_LITERAL(1, 22, 23), // "setHalfDeclineAreaValue"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 4), // "text"
QT_MOC_LITERAL(4, 52, 6), // "reDraw"
QT_MOC_LITERAL(5, 59, 8), // "minValue"
QT_MOC_LITERAL(6, 68, 8), // "maxValue"
QT_MOC_LITERAL(7, 77, 4), // "name"
QT_MOC_LITERAL(8, 82, 21), // "redrawCoordinateVText"
QT_MOC_LITERAL(9, 104, 13), // "begChannelDis"
QT_MOC_LITERAL(10, 118, 13) // "endChannelDis"

    },
    "MyWidgetHalfLifeCurve\0setHalfDeclineAreaValue\0"
    "\0text\0reDraw\0minValue\0maxValue\0name\0"
    "redrawCoordinateVText\0begChannelDis\0"
    "endChannelDis"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyWidgetHalfLifeCurve[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    3,   32,    2, 0x06 /* Public */,
       8,    3,   39,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::QString,    5,    6,    7,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::QString,    9,   10,    7,

       0        // eod
};

void MyWidgetHalfLifeCurve::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyWidgetHalfLifeCurve *_t = static_cast<MyWidgetHalfLifeCurve *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setHalfDeclineAreaValue((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->reDraw((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 2: _t->redrawCoordinateVText((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MyWidgetHalfLifeCurve::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyWidgetHalfLifeCurve::setHalfDeclineAreaValue)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MyWidgetHalfLifeCurve::*_t)(double , double , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyWidgetHalfLifeCurve::reDraw)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MyWidgetHalfLifeCurve::*_t)(float , float , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyWidgetHalfLifeCurve::redrawCoordinateVText)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject MyWidgetHalfLifeCurve::staticMetaObject = {
    { &ViewerWidget::staticMetaObject, qt_meta_stringdata_MyWidgetHalfLifeCurve.data,
      qt_meta_data_MyWidgetHalfLifeCurve,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MyWidgetHalfLifeCurve::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyWidgetHalfLifeCurve::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyWidgetHalfLifeCurve.stringdata0))
        return static_cast<void*>(const_cast< MyWidgetHalfLifeCurve*>(this));
    return ViewerWidget::qt_metacast(_clname);
}

int MyWidgetHalfLifeCurve::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ViewerWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void MyWidgetHalfLifeCurve::setHalfDeclineAreaValue(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyWidgetHalfLifeCurve::reDraw(double _t1, double _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MyWidgetHalfLifeCurve::redrawCoordinateVText(float _t1, float _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
