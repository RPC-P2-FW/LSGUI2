/****************************************************************************
** Meta object code from reading C++ file 'mythread_remoteprog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LSGUI/mythread_remoteprog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mythread_remoteprog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Mythread_RemoteProg_t {
    QByteArrayData data[5];
    char stringdata0[69];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Mythread_RemoteProg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Mythread_RemoteProg_t qt_meta_stringdata_Mythread_RemoteProg = {
    {
QT_MOC_LITERAL(0, 0, 19), // "Mythread_RemoteProg"
QT_MOC_LITERAL(1, 20, 21), // "RemoteProgRespondSend"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 6), // "UINT32"
QT_MOC_LITERAL(4, 50, 18) // "RP_address_Counter"

    },
    "Mythread_RemoteProg\0RemoteProgRespondSend\0"
    "\0UINT32\0RP_address_Counter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Mythread_RemoteProg[] = {

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
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void Mythread_RemoteProg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Mythread_RemoteProg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->RemoteProgRespondSend((*reinterpret_cast< const UINT32(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Mythread_RemoteProg::*)(const UINT32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Mythread_RemoteProg::RemoteProgRespondSend)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Mythread_RemoteProg::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_Mythread_RemoteProg.data,
    qt_meta_data_Mythread_RemoteProg,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Mythread_RemoteProg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Mythread_RemoteProg::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Mythread_RemoteProg.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int Mythread_RemoteProg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Mythread_RemoteProg::RemoteProgRespondSend(const UINT32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
