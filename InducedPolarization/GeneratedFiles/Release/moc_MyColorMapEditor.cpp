/****************************************************************************
** Meta object code from reading C++ file 'MyColorMapEditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MyColorMapEditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyColorMapEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_myColorMapEditor_t {
    QByteArrayData data[11];
    char stringdata0[104];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myColorMapEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myColorMapEditor_t qt_meta_stringdata_myColorMapEditor = {
    {
QT_MOC_LITERAL(0, 0, 16), // "myColorMapEditor"
QT_MOC_LITERAL(1, 17, 11), // "changeColor"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 18), // "changeTransparency"
QT_MOC_LITERAL(4, 49, 5), // "value"
QT_MOC_LITERAL(5, 55, 14), // "getChangedText"
QT_MOC_LITERAL(6, 70, 4), // "text"
QT_MOC_LITERAL(7, 75, 13), // "setColorValue"
QT_MOC_LITERAL(8, 89, 3), // "red"
QT_MOC_LITERAL(9, 93, 5), // "green"
QT_MOC_LITERAL(10, 99, 4) // "blue"

    },
    "myColorMapEditor\0changeColor\0\0"
    "changeTransparency\0value\0getChangedText\0"
    "text\0setColorValue\0red\0green\0blue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myColorMapEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    1,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   43,    2, 0x0a /* Public */,
       7,    3,   46,    2, 0x0a /* Public */,
       3,    1,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    8,    9,   10,
    QMetaType::Void, QMetaType::QString,    4,

       0        // eod
};

void myColorMapEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        myColorMapEditor *_t = static_cast<myColorMapEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeColor(); break;
        case 1: _t->changeTransparency((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->getChangedText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->setColorValue((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->changeTransparency((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (myColorMapEditor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myColorMapEditor::changeColor)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (myColorMapEditor::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myColorMapEditor::changeTransparency)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject myColorMapEditor::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_myColorMapEditor.data,
      qt_meta_data_myColorMapEditor,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *myColorMapEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myColorMapEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_myColorMapEditor.stringdata0))
        return static_cast<void*>(const_cast< myColorMapEditor*>(this));
    return QDialog::qt_metacast(_clname);
}

int myColorMapEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void myColorMapEditor::changeColor()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void myColorMapEditor::changeTransparency(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
