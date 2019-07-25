/****************************************************************************
** Meta object code from reading C++ file 'ForwardAndInverseProcess.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ForwardAndInverseProcess.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ForwardAndInverseProcess.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_IP__ForwardAndInverseProcess_t {
    QByteArrayData data[18];
    char stringdata0[288];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IP__ForwardAndInverseProcess_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IP__ForwardAndInverseProcess_t qt_meta_stringdata_IP__ForwardAndInverseProcess = {
    {
QT_MOC_LITERAL(0, 0, 28), // "IP::ForwardAndInverseProcess"
QT_MOC_LITERAL(1, 29, 13), // "reselectCount"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 17), // "onInvertCompleted"
QT_MOC_LITERAL(4, 62, 14), // "long double***"
QT_MOC_LITERAL(5, 77, 5), // "vData"
QT_MOC_LITERAL(6, 83, 5), // "vZLen"
QT_MOC_LITERAL(7, 89, 5), // "vYLen"
QT_MOC_LITERAL(8, 95, 5), // "vXLen"
QT_MOC_LITERAL(9, 101, 29), // "osg::ref_ptr<osg::Vec4dArray>"
QT_MOC_LITERAL(10, 131, 11), // "vPointArray"
QT_MOC_LITERAL(11, 143, 16), // "setProgressValue"
QT_MOC_LITERAL(12, 160, 18), // "creatForwardResult"
QT_MOC_LITERAL(13, 179, 20), // "creatInversionResult"
QT_MOC_LITERAL(14, 200, 22), // "creatSimuForwardResult"
QT_MOC_LITERAL(15, 223, 29), // "autoGenForwardProcessFinished"
QT_MOC_LITERAL(16, 253, 6), // "result"
QT_MOC_LITERAL(17, 260, 27) // "inducedPolariAutoGenProcess"

    },
    "IP::ForwardAndInverseProcess\0reselectCount\0"
    "\0onInvertCompleted\0long double***\0"
    "vData\0vZLen\0vYLen\0vXLen\0"
    "osg::ref_ptr<osg::Vec4dArray>\0vPointArray\0"
    "setProgressValue\0creatForwardResult\0"
    "creatInversionResult\0creatSimuForwardResult\0"
    "autoGenForwardProcessFinished\0result\0"
    "inducedPolariAutoGenProcess"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IP__ForwardAndInverseProcess[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    4,   65,    2, 0x06 /* Public */,
       3,    4,   74,    2, 0x06 /* Public */,
      11,    1,   83,    2, 0x06 /* Public */,
      12,    0,   86,    2, 0x06 /* Public */,
      13,    0,   87,    2, 0x06 /* Public */,
      14,    0,   88,    2, 0x06 /* Public */,
      15,    1,   89,    2, 0x06 /* Public */,
       3,    0,   92,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    0,   93,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt,    5,    6,    7,    8,
    QMetaType::Void, 0x80000000 | 9, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt,   10,    6,    7,    8,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void IP::ForwardAndInverseProcess::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ForwardAndInverseProcess *_t = static_cast<ForwardAndInverseProcess *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->reselectCount(); break;
        case 1: _t->onInvertCompleted((*reinterpret_cast< long double***(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4]))); break;
        case 2: _t->onInvertCompleted((*reinterpret_cast< osg::ref_ptr<osg::Vec4dArray>(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4]))); break;
        case 3: _t->setProgressValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->creatForwardResult(); break;
        case 5: _t->creatInversionResult(); break;
        case 6: _t->creatSimuForwardResult(); break;
        case 7: _t->autoGenForwardProcessFinished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->onInvertCompleted(); break;
        case 9: _t->inducedPolariAutoGenProcess(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ForwardAndInverseProcess::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ForwardAndInverseProcess::reselectCount)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ForwardAndInverseProcess::*_t)(long double * * * , unsigned int , unsigned int , unsigned int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ForwardAndInverseProcess::onInvertCompleted)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ForwardAndInverseProcess::*_t)(osg::ref_ptr<osg::Vec4dArray> , unsigned int , unsigned int , unsigned int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ForwardAndInverseProcess::onInvertCompleted)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ForwardAndInverseProcess::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ForwardAndInverseProcess::setProgressValue)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (ForwardAndInverseProcess::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ForwardAndInverseProcess::creatForwardResult)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (ForwardAndInverseProcess::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ForwardAndInverseProcess::creatInversionResult)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (ForwardAndInverseProcess::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ForwardAndInverseProcess::creatSimuForwardResult)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (ForwardAndInverseProcess::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ForwardAndInverseProcess::autoGenForwardProcessFinished)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (ForwardAndInverseProcess::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ForwardAndInverseProcess::onInvertCompleted)) {
                *result = 8;
                return;
            }
        }
    }
}

const QMetaObject IP::ForwardAndInverseProcess::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_IP__ForwardAndInverseProcess.data,
      qt_meta_data_IP__ForwardAndInverseProcess,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *IP::ForwardAndInverseProcess::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IP::ForwardAndInverseProcess::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IP__ForwardAndInverseProcess.stringdata0))
        return static_cast<void*>(const_cast< ForwardAndInverseProcess*>(this));
    return QThread::qt_metacast(_clname);
}

int IP::ForwardAndInverseProcess::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void IP::ForwardAndInverseProcess::reselectCount()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void IP::ForwardAndInverseProcess::onInvertCompleted(long double * * * _t1, unsigned int _t2, unsigned int _t3, unsigned int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void IP::ForwardAndInverseProcess::onInvertCompleted(osg::ref_ptr<osg::Vec4dArray> _t1, unsigned int _t2, unsigned int _t3, unsigned int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void IP::ForwardAndInverseProcess::setProgressValue(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void IP::ForwardAndInverseProcess::creatForwardResult()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void IP::ForwardAndInverseProcess::creatInversionResult()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void IP::ForwardAndInverseProcess::creatSimuForwardResult()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void IP::ForwardAndInverseProcess::autoGenForwardProcessFinished(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void IP::ForwardAndInverseProcess::onInvertCompleted()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
