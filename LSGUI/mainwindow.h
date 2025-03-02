#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "secdialog.h"
#include "histogram.h"
#include "realtime.h"
#include "realtimev2.h"
#include "timingprofile.h"
#include "backendemu2.h"
#include "backendhitplot.h"
#include "backendstripprf.h"
#include "backendtimingprf.h"

#include "mythread_be_dataprocess.h"
#include "mythread_be_dataprocplotd.h"
#include "mythread_be_dataprocplotc.h"

#include "febdialog.h"
#include "mythread.h"
#include "MyThreadSend.h"
#include "mythread_cb_update.h"
#include "mythread_lb_update.h"
#include "mythread_remoteprog.h"
#include "mythread_be_update.h"

#include <QMainWindow>
#include <QDialog>
#include <QString>
#include <QVector>
#include <QTimer>

unsigned int const mccs_read_PacketSize   = 0 ;
unsigned int const mccs_read_BunchCounter = 1 ;
unsigned int const mccs_read_FullWin      = 2 ;
unsigned int const mccs_read_AdjWin       = 3 ;


unsigned int const timingHst_read_PacketSize      = 0 ;
unsigned int const timingHst_read_BunchCounter    = 1 ;
unsigned int const timingHst_read_BunchData       = 2 ;


unsigned int const dataLog_read_PacketSize      = 0 ;
unsigned int const dataLog_read_BunchCounter    = 1 ;
unsigned int const dataLog_read_Channels       = 2 ;

unsigned int const LB1 = 1 ;
unsigned int const LB2 = 2 ;
unsigned int const LB3 = 3 ;
unsigned int const LB4 = 4 ;
unsigned int const LB5 = 5 ;
unsigned int const LB6 = 6 ;
unsigned int const LB7 = 7 ;
unsigned int const LB8 = 8 ;
unsigned int const LB9 = 9 ;

const unsigned int t_histogram = 1 ;
const unsigned int t_timing = 2 ;
const unsigned int t_dataLog = 3 ;








QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
    /*
    unsigned int const LB1 = 1 ;
    unsigned int const LB2 = 2 ;
    unsigned int const LB3 = 3 ;
    unsigned int const LB4 = 4 ;
    unsigned int const LB5 = 5 ;
    unsigned int const LB6 = 6 ;
    unsigned int const LB7 = 7 ;
    unsigned int const LB8 = 8 ;
    unsigned int const LB9 = 9 ;
    */

    USHORT P_value ;
    USHORT P_address ;
    bool exitRecvThread;
    INT mBuffer_size = 0;
    bool bSave = false;
    char *receiveBuf = NULL;
    UINT receiveBufSize = 0;
    UINT receiveBufIndex = 0;
    char *sendBuf;
    unsigned char *UsendBuf;
    QFile file ;

    char *flashBuf;

    unsigned int fileLength = 0;
    unsigned int sent_char[4] = {0,0,0,0};
    unsigned int STAMP ;
    bool load_complete = false;

    UINT packet_cnt = 0 ;
    unsigned int Rec_Reply [300][300];
    QString str;
    unsigned int cb_lb = 0 ;
    unsigned int instruction_code = 0 ;
    unsigned int ADC_channel = 0 ;
    unsigned int ADG_MUX_selector = 0 ;
    unsigned int data_1 = 0 ;
    unsigned int data_2 = 0 ;
    unsigned int data = 0 ;
    float adc_value = 0 ;

    unsigned int feb_instruction_code = 0 ;
    unsigned int feb_distribution_board = 0 ;
    unsigned int feb_distribution_board_port = 0 ;
    unsigned int feb_number = 0 ;
    unsigned int feb_chip = 0 ;
    unsigned int feb_chip_channel = 0 ;
    unsigned int acc , bcc = 0 ;
    unsigned int feb_dac_value = 0 ;
    unsigned int feb_adc_value = 0 ;

    unsigned int rw0 , rw1 , rw2 , rw3 ,rw4 , rw5 = 0;
    unsigned int lb_number = 0 ;
    unsigned int diagnostic_instruction_code = 0 ;
    unsigned int test_sig_number = 0 ;
    unsigned int test_sig_on_off = 0 ;
    unsigned int open_window_value = 0 ;
    unsigned int close_window_value = 0 ;
    unsigned int tdc_number_to_turn_off = 0 ;
    unsigned int bunch_counter_value = 0 ;
    unsigned int mccs_pack_cnt = 0 ;
    unsigned int mcc, mcc1 , mcc2 = 0 ;
    unsigned int icc = 0 ;
    unsigned int histogram_value = 0 ;
    unsigned int bxx = 0 ;
    unsigned int sub_bx = 0 ;
    unsigned int logging_valid = 0 ;
    unsigned int logging_value1 , logging_value2 = 0 ;

    unsigned int mccs_status = mccs_read_PacketSize ;
    unsigned int mccs_total_pack_size = 0 ;
    unsigned int FullWinChannel[255];
    unsigned int AdjWinChannel[255];
    UINT8  FW_Cnter = 0 ;
    UINT8  AdW_Cnter = 0 ;

    unsigned int timingHst_pack_cnt = 0 ;
    unsigned int timingHst_status = mccs_read_PacketSize ;
    unsigned int timingHst_total_pack_size = 0 ;
    unsigned int BunchCrossData[255];
    UINT8  BxCnt = 0 ;

    unsigned int dataLog_pack_cnt = 0 ;
    unsigned int dataLog_status = mccs_read_PacketSize ;
    unsigned int dataLog_total_pack_size = 0 ;

    unsigned int dataLog[96][130]; // [strip][sub-bx]

    UINT8  subBxCnt = 0 ; //1-129  dataLogCnt
    UINT8  stripCnt = 0 ; //1-96
    UINT8  LineCnt = 0 ; //1-16 partitionCnt

    unsigned int LBN = 0 ;
    void ProgressBarUpdate(unsigned int l_histType, unsigned int l_LBN , float l_currentPackNum , float l_maxPackNum);
    unsigned int maxPackNum = 0 ;
    unsigned int currentPackNum = 0 ;

    unsigned int SEM_Reply [500];
    QString strSEU ;
    unsigned int SemCnt = 0 ;
    unsigned int SenCmdcnt = 0 ;

    QString SemCmdText ;
    unsigned int SEMCmdArray [500];
    QString TempText;

    QString str3 ;

    unsigned int const maxBX = 3564; //3564

    unsigned int RPCHist[100]; // Plot C
    unsigned int RPCStripHit[200][200]; // Plot A - [strip][BX]
    unsigned int RPCHitSubBx[16][100]; //Plot B - [Sub-BX][Strip]
    unsigned int RPCHitTimingPrf[4000];

    unsigned int findex = 0 ;
    unsigned int Field1 = 0 ;
    unsigned int Field2 = 0 ;
    unsigned int Field3 = 0 ;

    unsigned int frameCnt = 0 ;

    unsigned int hit1_stripNum[120][10] ;
    unsigned int hit1_subBX [120][10] ;

    unsigned int hit2_stripNum [120][10] ;
    unsigned int hit2_subBX [120][10] ;

    unsigned int hit3_stripNum [120][10] ;
    unsigned int hit3_subBX [120][10] ;

    unsigned int hit4_stripNum [120][10] ;
    unsigned int hit4_subBX [120][10] ;

    unsigned int hit5_stripNum [120][10] ;
    unsigned int hit5_subBX [120][10] ;

    unsigned int hit6_stripNum [120][10] ;
    unsigned int hit6_subBX [120][10] ;

    unsigned int bunchCrossing [120][10] ;
    unsigned int orbitNumber [120][10] ;

    unsigned int ArrayPnt1 = 0 ;
    unsigned int ArrayPnt2 = 0 ;

    bool freeRunLog = false;

    unsigned char conv_ascii_to_hex(unsigned char );

    unsigned int feb1_dac1_vth1_value_int = 0 ;
    unsigned int feb1_dac1_vth2_value_int = 0 ;
    unsigned int feb1_dac1_vmon1_value_int = 0 ;
    unsigned int feb1_dac1_vmon2_value_int = 0 ;

    unsigned int feb1_dac2_vth1_value_int = 0 ;
    unsigned int feb1_dac2_vth2_value_int = 0 ;
    unsigned int feb1_dac2_vmon1_value_int = 0 ;
    unsigned int feb1_dac2_vmon2_value_int = 0 ;


    unsigned int feb2_dac1_vth1_value_int = 0 ;
    unsigned int feb2_dac1_vth2_value_int = 0 ;
    unsigned int feb2_dac1_vmon1_value_int = 0 ;
    unsigned int feb2_dac1_vmon2_value_int = 0 ;

    unsigned int feb2_dac2_vth1_value_int = 0 ;
    unsigned int feb2_dac2_vth2_value_int = 0 ;
    unsigned int feb2_dac2_vmon1_value_int = 0 ;
    unsigned int feb2_dac2_vmon2_value_int = 0 ;


    unsigned int feb3_dac1_vth1_value_int = 0 ;
    unsigned int feb3_dac1_vth2_value_int = 0 ;
    unsigned int feb3_dac1_vmon1_value_int = 0 ;
    unsigned int feb3_dac1_vmon2_value_int = 0 ;

    unsigned int feb3_dac2_vth1_value_int = 0 ;
    unsigned int feb3_dac2_vth2_value_int = 0 ;
    unsigned int feb3_dac2_vmon1_value_int = 0 ;
    unsigned int feb3_dac2_vmon2_value_int = 0 ;

    unsigned int db_port = 0 ;

/*
    bool  ChBx_CB_Cmd_Turn_ON_LB1= false;
    bool  ChBx_CB_Cmd_Turn_ON_LB2= false;
    bool  ChBx_CB_Cmd_Turn_ON_LB3= false;
    bool  ChBx_CB_Cmd_Turn_ON_LB4= false;
    bool  ChBx_CB_Cmd_Turn_ON_LB5= false;
    bool  ChBx_CB_Cmd_Turn_ON_LB6= false;
    bool  ChBx_CB_Cmd_Turn_ON_LB7= false;
    bool  ChBx_CB_Cmd_Turn_ON_LB8= false;
    bool  ChBx_CB_Cmd_Turn_ON_LB9= false;
*/
unsigned int aw , bw ;


private slots:

    void transaction();

    void ThreadSlot_showResponse( const UINT rec_complete);
    void ThreadSlot_showResponseSend( const UINT64 totalSentSize);
    void ThreadSlot_rp_status_register (const unsigned int RP_Param_Cnt);
    void ThreadSlot_Check_cb_status_register (const UINT CB_Param_Cnt);
    void ThreadSlot_Check_lb_status_register (const UINT LB_Param_Cnt);
    void ThreadSlot_Check_be_status_register (const UINT BE_Param_Cnt);
    //void ThreadSlot_be_dpc_plot(const unsigned int frameCnt);
    void ThreadSlot_be_dpc_plotD(const unsigned int frameCnt);
    void ThreadSlot_be_dpc_plotC(const unsigned int frameCnt);


    void processError(const QString &s);
    void processTimeout(const QString &s);

    void on_pushButton_clicked();            
    void on_pushButton_2_clicked();
    void on_actionFEB_triggered();
    void on_actionFEBs_triggered();
    void on_actionExit_triggered();
    void on_actionEthernet_1G_triggered();
    void on_actionPCIe_8G_triggered();
    void on_actionUART_triggered();
    void on_Connect_clicked();
    void on_ping_clicked();
    void on_actionTlbConnect_triggered();
    void on_actionTlbPing_triggered();
    void on_ReadReg_clicked();
    void on_WriteReg_clicked();
    void on_ReadConfig_clicked();
    void on_ReceiveBuffer_clicked();

    void on_checkBox_2_stateChanged(int arg1);
    void on_SendBuffer_clicked();
    void on_send_one_frame_clicked();
    void on_clear_pushBotton_clicked();
    void on_CB_Update_clicked();

    void on_timeout();
    void on_timeout2();
    void on_timeout3();

    void on_CB_RP_Load_clicked();
    void on_CB_RP_Verify_clicked();
    void on_WriteConfig_clicked();
    void on_clear_pushBotton_2_clicked();
    void on_CB_Stop_clicked();



    void on_monitorSem_clicked();
    void on_SemStatus_clicked();
    void on_SemReset_clicked();
    void on_IdleState_clicked();
    void on_Observation_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_8_clicked();
    void on_Reserved_clicked();
    void on_systemClock_timeout();
    void on_CB_Plot_clicked();
    void on_CB_Clear_clicked();
    void on_CB_Close_clicked();

    void on_pushButton_destroyed(QObject *arg1);

    void on_Plot_ScaleTop_clicked();

    void on_Plot_ScaleWindow_clicked();

    void on_CB_RP_Prog_clicked();

    void on_checkBox_4_stateChanged(int arg1);

private:

    void setControlsEnabled(bool enable);
    void WriteConfig(UCHAR address, UINT value);
    void WriteReg(USHORT address, UINT value);
    void Set_ch_thread_ChBx();
    void Get_ch_thread_ChBx_Values();
    void delay (int miliseconds);

    void cmd_process(unsigned int cmd_counter , unsigned int rec_buf );
    void lb_cmd_process(unsigned int frame_index , unsigned int packet_cnt  );
    void cb_cmd_process(unsigned int cmd_counter );
    void realTimePlot(unsigned int LBN , unsigned int bunch_counter_value );
    void timingProfilePlot (unsigned int LBN , unsigned int bunch_counter_value );
    void sendSemCmd (unsigned int fileLength, char sendBuf[], unsigned int receiveBufSize, unsigned int cmdType, QString cmdText, unsigned int SemCnt);
    void BackendProcess(UINT32 frame_index , UINT32 packet_cnt);
    void makeBackendPlot(void);

    Ui::MainWindow *ui;
    secDialog *secDialog1;
    histogram *histogram1;
    febDialog *febdialog;
    realTime *realTime1;
    realtimev2 *REALtimev2;
    timingprofile *TimingProfile1;
    BackendEmu2 *backendbmu2;
    BackendHitPlot *backendhitplot;
    BackendStripPrf *backendstripprf;
    BackendTimingPrf *backendtimingprf;

    QTimer *qtimer;
    QTimer *qtimer2;
    QTimer *qtimer3;
    QTimer *systemClock;
    QTime SystemTime ;
    QTime SystemDate ;

    MyThread m_thread;
    MyThreadSend s_thread;
    Mythread_CB_Update cb_thread;
    Mythread_LB_Update lb_thread;
    Mythread_RemoteProg rp_thread;
    mythread_be_update be_thread;
    //Mythread_BE_DataProcess be_dpc_thread;
    Mythread_BE_DataProcPlotD be_dpcPlotD_thread;
    Mythread_BE_DataProcPlotC be_dpcPlotC_thread;

    bool LanStatus = false;
    UINT oldReceivedSize;
    DWORD rStartTickCount;
    INT64 mReceived_Buffer=0;
    boolean mBuffer_full=false;

    UINT Prog_Full = 0 ;
    UINT Buf_empty = 0 ;

    USHORT address ;
    QString str1;
    QString str2;
    bool ReadReg_status;
    float progress, p1, p2 , p3;

    bool check_ready = false ;
    bool Histogram_exist = false;
    bool REALTimev2_exist = false;
    bool TimingProfile_exist = false;

    UINT retrig_interval = 0;

    QString TimeText;





};
#endif // MAINWINDOW_H
