/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LSGUI/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[70];
    char stringdata0[1434];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 11), // "transaction"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 23), // "ThreadSlot_showResponse"
QT_MOC_LITERAL(4, 48, 4), // "UINT"
QT_MOC_LITERAL(5, 53, 12), // "rec_complete"
QT_MOC_LITERAL(6, 66, 27), // "ThreadSlot_showResponseSend"
QT_MOC_LITERAL(7, 94, 6), // "UINT64"
QT_MOC_LITERAL(8, 101, 13), // "totalSentSize"
QT_MOC_LITERAL(9, 115, 29), // "ThreadSlot_rp_status_register"
QT_MOC_LITERAL(10, 145, 12), // "RP_Param_Cnt"
QT_MOC_LITERAL(11, 158, 35), // "ThreadSlot_Check_cb_status_re..."
QT_MOC_LITERAL(12, 194, 12), // "CB_Param_Cnt"
QT_MOC_LITERAL(13, 207, 35), // "ThreadSlot_Check_lb_status_re..."
QT_MOC_LITERAL(14, 243, 12), // "LB_Param_Cnt"
QT_MOC_LITERAL(15, 256, 35), // "ThreadSlot_Check_be_status_re..."
QT_MOC_LITERAL(16, 292, 12), // "BE_Param_Cnt"
QT_MOC_LITERAL(17, 305, 23), // "ThreadSlot_be_dpc_plotD"
QT_MOC_LITERAL(18, 329, 8), // "frameCnt"
QT_MOC_LITERAL(19, 338, 23), // "ThreadSlot_be_dpc_plotC"
QT_MOC_LITERAL(20, 362, 12), // "processError"
QT_MOC_LITERAL(21, 375, 1), // "s"
QT_MOC_LITERAL(22, 377, 14), // "processTimeout"
QT_MOC_LITERAL(23, 392, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(24, 414, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(25, 438, 22), // "on_actionFEB_triggered"
QT_MOC_LITERAL(26, 461, 23), // "on_actionFEBs_triggered"
QT_MOC_LITERAL(27, 485, 23), // "on_actionExit_triggered"
QT_MOC_LITERAL(28, 509, 30), // "on_actionEthernet_1G_triggered"
QT_MOC_LITERAL(29, 540, 26), // "on_actionPCIe_8G_triggered"
QT_MOC_LITERAL(30, 567, 23), // "on_actionUART_triggered"
QT_MOC_LITERAL(31, 591, 18), // "on_Connect_clicked"
QT_MOC_LITERAL(32, 610, 15), // "on_ping_clicked"
QT_MOC_LITERAL(33, 626, 29), // "on_actionTlbConnect_triggered"
QT_MOC_LITERAL(34, 656, 26), // "on_actionTlbPing_triggered"
QT_MOC_LITERAL(35, 683, 18), // "on_ReadReg_clicked"
QT_MOC_LITERAL(36, 702, 19), // "on_WriteReg_clicked"
QT_MOC_LITERAL(37, 722, 21), // "on_ReadConfig_clicked"
QT_MOC_LITERAL(38, 744, 24), // "on_ReceiveBuffer_clicked"
QT_MOC_LITERAL(39, 769, 26), // "on_checkBox_2_stateChanged"
QT_MOC_LITERAL(40, 796, 4), // "arg1"
QT_MOC_LITERAL(41, 801, 21), // "on_SendBuffer_clicked"
QT_MOC_LITERAL(42, 823, 25), // "on_send_one_frame_clicked"
QT_MOC_LITERAL(43, 849, 27), // "on_clear_pushBotton_clicked"
QT_MOC_LITERAL(44, 877, 20), // "on_CB_Update_clicked"
QT_MOC_LITERAL(45, 898, 10), // "on_timeout"
QT_MOC_LITERAL(46, 909, 11), // "on_timeout2"
QT_MOC_LITERAL(47, 921, 11), // "on_timeout3"
QT_MOC_LITERAL(48, 933, 21), // "on_CB_RP_Load_clicked"
QT_MOC_LITERAL(49, 955, 23), // "on_CB_RP_Verify_clicked"
QT_MOC_LITERAL(50, 979, 22), // "on_WriteConfig_clicked"
QT_MOC_LITERAL(51, 1002, 29), // "on_clear_pushBotton_2_clicked"
QT_MOC_LITERAL(52, 1032, 18), // "on_CB_Stop_clicked"
QT_MOC_LITERAL(53, 1051, 21), // "on_monitorSem_clicked"
QT_MOC_LITERAL(54, 1073, 20), // "on_SemStatus_clicked"
QT_MOC_LITERAL(55, 1094, 19), // "on_SemReset_clicked"
QT_MOC_LITERAL(56, 1114, 20), // "on_IdleState_clicked"
QT_MOC_LITERAL(57, 1135, 22), // "on_Observation_clicked"
QT_MOC_LITERAL(58, 1158, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(59, 1182, 23), // "on_pushButton_8_clicked"
QT_MOC_LITERAL(60, 1206, 19), // "on_Reserved_clicked"
QT_MOC_LITERAL(61, 1226, 22), // "on_systemClock_timeout"
QT_MOC_LITERAL(62, 1249, 18), // "on_CB_Plot_clicked"
QT_MOC_LITERAL(63, 1268, 19), // "on_CB_Clear_clicked"
QT_MOC_LITERAL(64, 1288, 19), // "on_CB_Close_clicked"
QT_MOC_LITERAL(65, 1308, 23), // "on_pushButton_destroyed"
QT_MOC_LITERAL(66, 1332, 24), // "on_Plot_ScaleTop_clicked"
QT_MOC_LITERAL(67, 1357, 27), // "on_Plot_ScaleWindow_clicked"
QT_MOC_LITERAL(68, 1385, 21), // "on_CB_RP_Prog_clicked"
QT_MOC_LITERAL(69, 1407, 26) // "on_checkBox_4_stateChanged"

    },
    "MainWindow\0transaction\0\0ThreadSlot_showResponse\0"
    "UINT\0rec_complete\0ThreadSlot_showResponseSend\0"
    "UINT64\0totalSentSize\0ThreadSlot_rp_status_register\0"
    "RP_Param_Cnt\0ThreadSlot_Check_cb_status_register\0"
    "CB_Param_Cnt\0ThreadSlot_Check_lb_status_register\0"
    "LB_Param_Cnt\0ThreadSlot_Check_be_status_register\0"
    "BE_Param_Cnt\0ThreadSlot_be_dpc_plotD\0"
    "frameCnt\0ThreadSlot_be_dpc_plotC\0"
    "processError\0s\0processTimeout\0"
    "on_pushButton_clicked\0on_pushButton_2_clicked\0"
    "on_actionFEB_triggered\0on_actionFEBs_triggered\0"
    "on_actionExit_triggered\0"
    "on_actionEthernet_1G_triggered\0"
    "on_actionPCIe_8G_triggered\0"
    "on_actionUART_triggered\0on_Connect_clicked\0"
    "on_ping_clicked\0on_actionTlbConnect_triggered\0"
    "on_actionTlbPing_triggered\0"
    "on_ReadReg_clicked\0on_WriteReg_clicked\0"
    "on_ReadConfig_clicked\0on_ReceiveBuffer_clicked\0"
    "on_checkBox_2_stateChanged\0arg1\0"
    "on_SendBuffer_clicked\0on_send_one_frame_clicked\0"
    "on_clear_pushBotton_clicked\0"
    "on_CB_Update_clicked\0on_timeout\0"
    "on_timeout2\0on_timeout3\0on_CB_RP_Load_clicked\0"
    "on_CB_RP_Verify_clicked\0on_WriteConfig_clicked\0"
    "on_clear_pushBotton_2_clicked\0"
    "on_CB_Stop_clicked\0on_monitorSem_clicked\0"
    "on_SemStatus_clicked\0on_SemReset_clicked\0"
    "on_IdleState_clicked\0on_Observation_clicked\0"
    "on_pushButton_3_clicked\0on_pushButton_8_clicked\0"
    "on_Reserved_clicked\0on_systemClock_timeout\0"
    "on_CB_Plot_clicked\0on_CB_Clear_clicked\0"
    "on_CB_Close_clicked\0on_pushButton_destroyed\0"
    "on_Plot_ScaleTop_clicked\0"
    "on_Plot_ScaleWindow_clicked\0"
    "on_CB_RP_Prog_clicked\0on_checkBox_4_stateChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      57,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  299,    2, 0x08 /* Private */,
       3,    1,  300,    2, 0x08 /* Private */,
       6,    1,  303,    2, 0x08 /* Private */,
       9,    1,  306,    2, 0x08 /* Private */,
      11,    1,  309,    2, 0x08 /* Private */,
      13,    1,  312,    2, 0x08 /* Private */,
      15,    1,  315,    2, 0x08 /* Private */,
      17,    1,  318,    2, 0x08 /* Private */,
      19,    1,  321,    2, 0x08 /* Private */,
      20,    1,  324,    2, 0x08 /* Private */,
      22,    1,  327,    2, 0x08 /* Private */,
      23,    0,  330,    2, 0x08 /* Private */,
      24,    0,  331,    2, 0x08 /* Private */,
      25,    0,  332,    2, 0x08 /* Private */,
      26,    0,  333,    2, 0x08 /* Private */,
      27,    0,  334,    2, 0x08 /* Private */,
      28,    0,  335,    2, 0x08 /* Private */,
      29,    0,  336,    2, 0x08 /* Private */,
      30,    0,  337,    2, 0x08 /* Private */,
      31,    0,  338,    2, 0x08 /* Private */,
      32,    0,  339,    2, 0x08 /* Private */,
      33,    0,  340,    2, 0x08 /* Private */,
      34,    0,  341,    2, 0x08 /* Private */,
      35,    0,  342,    2, 0x08 /* Private */,
      36,    0,  343,    2, 0x08 /* Private */,
      37,    0,  344,    2, 0x08 /* Private */,
      38,    0,  345,    2, 0x08 /* Private */,
      39,    1,  346,    2, 0x08 /* Private */,
      41,    0,  349,    2, 0x08 /* Private */,
      42,    0,  350,    2, 0x08 /* Private */,
      43,    0,  351,    2, 0x08 /* Private */,
      44,    0,  352,    2, 0x08 /* Private */,
      45,    0,  353,    2, 0x08 /* Private */,
      46,    0,  354,    2, 0x08 /* Private */,
      47,    0,  355,    2, 0x08 /* Private */,
      48,    0,  356,    2, 0x08 /* Private */,
      49,    0,  357,    2, 0x08 /* Private */,
      50,    0,  358,    2, 0x08 /* Private */,
      51,    0,  359,    2, 0x08 /* Private */,
      52,    0,  360,    2, 0x08 /* Private */,
      53,    0,  361,    2, 0x08 /* Private */,
      54,    0,  362,    2, 0x08 /* Private */,
      55,    0,  363,    2, 0x08 /* Private */,
      56,    0,  364,    2, 0x08 /* Private */,
      57,    0,  365,    2, 0x08 /* Private */,
      58,    0,  366,    2, 0x08 /* Private */,
      59,    0,  367,    2, 0x08 /* Private */,
      60,    0,  368,    2, 0x08 /* Private */,
      61,    0,  369,    2, 0x08 /* Private */,
      62,    0,  370,    2, 0x08 /* Private */,
      63,    0,  371,    2, 0x08 /* Private */,
      64,    0,  372,    2, 0x08 /* Private */,
      65,    1,  373,    2, 0x08 /* Private */,
      66,    0,  376,    2, 0x08 /* Private */,
      67,    0,  377,    2, 0x08 /* Private */,
      68,    0,  378,    2, 0x08 /* Private */,
      69,    1,  379,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::UInt,   10,
    QMetaType::Void, 0x80000000 | 4,   12,
    QMetaType::Void, 0x80000000 | 4,   14,
    QMetaType::Void, 0x80000000 | 4,   16,
    QMetaType::Void, QMetaType::UInt,   18,
    QMetaType::Void, QMetaType::UInt,   18,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::QString,   21,
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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   40,
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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QObjectStar,   40,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   40,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->transaction(); break;
        case 1: _t->ThreadSlot_showResponse((*reinterpret_cast< const UINT(*)>(_a[1]))); break;
        case 2: _t->ThreadSlot_showResponseSend((*reinterpret_cast< const UINT64(*)>(_a[1]))); break;
        case 3: _t->ThreadSlot_rp_status_register((*reinterpret_cast< const uint(*)>(_a[1]))); break;
        case 4: _t->ThreadSlot_Check_cb_status_register((*reinterpret_cast< const UINT(*)>(_a[1]))); break;
        case 5: _t->ThreadSlot_Check_lb_status_register((*reinterpret_cast< const UINT(*)>(_a[1]))); break;
        case 6: _t->ThreadSlot_Check_be_status_register((*reinterpret_cast< const UINT(*)>(_a[1]))); break;
        case 7: _t->ThreadSlot_be_dpc_plotD((*reinterpret_cast< const uint(*)>(_a[1]))); break;
        case 8: _t->ThreadSlot_be_dpc_plotC((*reinterpret_cast< const uint(*)>(_a[1]))); break;
        case 9: _t->processError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->processTimeout((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->on_pushButton_clicked(); break;
        case 12: _t->on_pushButton_2_clicked(); break;
        case 13: _t->on_actionFEB_triggered(); break;
        case 14: _t->on_actionFEBs_triggered(); break;
        case 15: _t->on_actionExit_triggered(); break;
        case 16: _t->on_actionEthernet_1G_triggered(); break;
        case 17: _t->on_actionPCIe_8G_triggered(); break;
        case 18: _t->on_actionUART_triggered(); break;
        case 19: _t->on_Connect_clicked(); break;
        case 20: _t->on_ping_clicked(); break;
        case 21: _t->on_actionTlbConnect_triggered(); break;
        case 22: _t->on_actionTlbPing_triggered(); break;
        case 23: _t->on_ReadReg_clicked(); break;
        case 24: _t->on_WriteReg_clicked(); break;
        case 25: _t->on_ReadConfig_clicked(); break;
        case 26: _t->on_ReceiveBuffer_clicked(); break;
        case 27: _t->on_checkBox_2_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: _t->on_SendBuffer_clicked(); break;
        case 29: _t->on_send_one_frame_clicked(); break;
        case 30: _t->on_clear_pushBotton_clicked(); break;
        case 31: _t->on_CB_Update_clicked(); break;
        case 32: _t->on_timeout(); break;
        case 33: _t->on_timeout2(); break;
        case 34: _t->on_timeout3(); break;
        case 35: _t->on_CB_RP_Load_clicked(); break;
        case 36: _t->on_CB_RP_Verify_clicked(); break;
        case 37: _t->on_WriteConfig_clicked(); break;
        case 38: _t->on_clear_pushBotton_2_clicked(); break;
        case 39: _t->on_CB_Stop_clicked(); break;
        case 40: _t->on_monitorSem_clicked(); break;
        case 41: _t->on_SemStatus_clicked(); break;
        case 42: _t->on_SemReset_clicked(); break;
        case 43: _t->on_IdleState_clicked(); break;
        case 44: _t->on_Observation_clicked(); break;
        case 45: _t->on_pushButton_3_clicked(); break;
        case 46: _t->on_pushButton_8_clicked(); break;
        case 47: _t->on_Reserved_clicked(); break;
        case 48: _t->on_systemClock_timeout(); break;
        case 49: _t->on_CB_Plot_clicked(); break;
        case 50: _t->on_CB_Clear_clicked(); break;
        case 51: _t->on_CB_Close_clicked(); break;
        case 52: _t->on_pushButton_destroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 53: _t->on_Plot_ScaleTop_clicked(); break;
        case 54: _t->on_Plot_ScaleWindow_clicked(); break;
        case 55: _t->on_CB_RP_Prog_clicked(); break;
        case 56: _t->on_checkBox_4_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 57)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 57;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 57)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 57;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
