/****************************************************************************
** Meta object code from reading C++ file 'mythread_be_dataprocess.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LSGUI/mythread_be_dataprocess.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mythread_be_dataprocess.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Mythread_BE_DataProcess_t {
    QByteArrayData data[3];
    char stringdata0[41];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Mythread_BE_DataProcess_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Mythread_BE_DataProcess_t qt_meta_stringdata_Mythread_BE_DataProcess = {
    {
QT_MOC_LITERAL(0, 0, 23), // "Mythread_BE_DataProcess"
QT_MOC_LITERAL(1, 24, 15), // "BE_dps_response"
QT_MOC_LITERAL(2, 40, 0) // ""

    },
    "Mythread_BE_DataProcess\0BE_dps_response\0"
    ""
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Mythread_BE_DataProcess[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt,    2,

       0        // eod
};

void Mythread_BE_DataProcess::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Mythread_BE_DataProcess *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->BE_dps_response((*reinterpret_cast< uint(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Mythread_BE_DataProcess::*)(unsigned int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Mythread_BE_DataProcess::BE_dps_response)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Mythread_BE_DataProcess::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_Mythread_BE_DataProcess.data,
    qt_meta_data_Mythread_BE_DataProcess,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Mythread_BE_DataProcess::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Mythread_BE_DataProcess::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Mythread_BE_DataProcess.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int Mythread_BE_DataProcess::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void Mythread_BE_DataProcess::BE_dps_response(unsigned int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
