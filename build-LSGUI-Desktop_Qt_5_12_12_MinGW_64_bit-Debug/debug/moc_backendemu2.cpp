/****************************************************************************
** Meta object code from reading C++ file 'backendemu2.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LSGUI/backendemu2.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'backendemu2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BackendEmu2_t {
    QByteArrayData data[12];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BackendEmu2_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BackendEmu2_t qt_meta_stringdata_BackendEmu2 = {
    {
QT_MOC_LITERAL(0, 0, 11), // "BackendEmu2"
QT_MOC_LITERAL(1, 12, 20), // "horzScrollBarChanged"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 5), // "value"
QT_MOC_LITERAL(4, 40, 20), // "vertScrollBarChanged"
QT_MOC_LITERAL(5, 61, 12), // "xAxisChanged"
QT_MOC_LITERAL(6, 74, 8), // "QCPRange"
QT_MOC_LITERAL(7, 83, 5), // "range"
QT_MOC_LITERAL(8, 89, 12), // "yAxisChanged"
QT_MOC_LITERAL(9, 102, 10), // "mousePress"
QT_MOC_LITERAL(10, 113, 10), // "mouseWheel"
QT_MOC_LITERAL(11, 124, 12) // "QWheelEvent*"

    },
    "BackendEmu2\0horzScrollBarChanged\0\0"
    "value\0vertScrollBarChanged\0xAxisChanged\0"
    "QCPRange\0range\0yAxisChanged\0mousePress\0"
    "mouseWheel\0QWheelEvent*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BackendEmu2[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x08 /* Private */,
       4,    1,   47,    2, 0x08 /* Private */,
       5,    1,   50,    2, 0x08 /* Private */,
       8,    1,   53,    2, 0x08 /* Private */,
       9,    0,   56,    2, 0x08 /* Private */,
      10,    1,   57,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,    2,

       0        // eod
};

void BackendEmu2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BackendEmu2 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->horzScrollBarChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->vertScrollBarChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->xAxisChanged((*reinterpret_cast< QCPRange(*)>(_a[1]))); break;
        case 3: _t->yAxisChanged((*reinterpret_cast< QCPRange(*)>(_a[1]))); break;
        case 4: _t->mousePress(); break;
        case 5: _t->mouseWheel((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BackendEmu2::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_BackendEmu2.data,
    qt_meta_data_BackendEmu2,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BackendEmu2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BackendEmu2::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BackendEmu2.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int BackendEmu2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
