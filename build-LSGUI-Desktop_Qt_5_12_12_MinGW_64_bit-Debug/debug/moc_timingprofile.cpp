/****************************************************************************
** Meta object code from reading C++ file 'timingprofile.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LSGUI/timingprofile.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'timingprofile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_timingprofile_t {
    QByteArrayData data[9];
    char stringdata0[104];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_timingprofile_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_timingprofile_t qt_meta_stringdata_timingprofile = {
    {
QT_MOC_LITERAL(0, 0, 13), // "timingprofile"
QT_MOC_LITERAL(1, 14, 20), // "horzScrollBarChanged"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 5), // "value"
QT_MOC_LITERAL(4, 42, 20), // "vertScrollBarChanged"
QT_MOC_LITERAL(5, 63, 12), // "xAxisChanged"
QT_MOC_LITERAL(6, 76, 8), // "QCPRange"
QT_MOC_LITERAL(7, 85, 5), // "range"
QT_MOC_LITERAL(8, 91, 12) // "yAxisChanged"

    },
    "timingprofile\0horzScrollBarChanged\0\0"
    "value\0vertScrollBarChanged\0xAxisChanged\0"
    "QCPRange\0range\0yAxisChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_timingprofile[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x08 /* Private */,
       4,    1,   37,    2, 0x08 /* Private */,
       5,    1,   40,    2, 0x08 /* Private */,
       8,    1,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void timingprofile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<timingprofile *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->horzScrollBarChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->vertScrollBarChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->xAxisChanged((*reinterpret_cast< QCPRange(*)>(_a[1]))); break;
        case 3: _t->yAxisChanged((*reinterpret_cast< QCPRange(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject timingprofile::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_timingprofile.data,
    qt_meta_data_timingprofile,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *timingprofile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *timingprofile::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_timingprofile.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int timingprofile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
