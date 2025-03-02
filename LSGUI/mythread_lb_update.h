#ifndef MYTHREAD_LB_UPDATE_H
#define MYTHREAD_LB_UPDATE_H

#include <QObject>
#include <QtCore>
#include "YasinLanLib.h"
#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QString>

const INT Cmd_LB1               = 100 ;
const INT Cmd_LB2               = 200 ;
const INT Cmd_LB3               = 300 ;
const INT Cmd_LB4               = 400 ;
const INT Cmd_LB5               = 500 ;
const INT Cmd_LB6               = 600 ;
const INT Cmd_LB7               = 700 ;
const INT Cmd_LB8               = 800 ;
const INT Cmd_LB9               = 900 ;

const INT Cmd_LB1_1V             = Cmd_LB1 + 0 ;
const INT Cmd_LB1_1V8_Aux        = Cmd_LB1 + 1 ;
const INT Cmd_LB1_1V_MGTAVCC     = Cmd_LB1 + 2 ;
const INT Cmd_LB1_1V_MGTAVTT     = Cmd_LB1 + 3 ;
const INT Cmd_LB1_1V_MGTVCCAUX   = Cmd_LB1 + 4 ;
const INT Cmd_LB1_1V5            = Cmd_LB1 + 5 ;
const INT Cmd_LB1_1V8            = Cmd_LB1 + 6 ;
const INT Cmd_LB1_2V5            = Cmd_LB1 + 7 ;
const INT Cmd_LB1_3V3            = Cmd_LB1 + 8 ;
const INT Cmd_LB1_3V3VDD         = Cmd_LB1 + 9 ;
const INT Cmd_LB1_CS1_Vout       = Cmd_LB1 + 10 ;
const INT Cmd_LB1_CS2_Vout       = Cmd_LB1 + 11 ;
const INT Cmd_LB1_CS3_Vout       = Cmd_LB1 + 12 ;


const INT Cmd_LB1_Temp_Sensor1   = Cmd_LB1 + 13 ;
const INT Cmd_LB1_Temp_Sensor2   = Cmd_LB1 + 14 ;
const INT Cmd_LB1_Temp_Sensor3   = Cmd_LB1 + 15 ;
const INT Cmd_LB1_ADC_TEMP       = Cmd_LB1 + 16 ;
const INT Cmd_LB1_ADC_AVDD_2     = Cmd_LB1 + 17 ;
const INT Cmd_LB1_ADC_GND        = Cmd_LB1 + 18 ;
const INT Cmd_LB1_FPGA_VCORE     = Cmd_LB1 + 19 ;
const INT Cmd_LB1_FPGA_VCCBRAM   = Cmd_LB1 + 20 ;
const INT Cmd_LB1_FPGA_VCCAUX    = Cmd_LB1 + 21 ;
const INT Cmd_LB1_FPGA_Temp      = Cmd_LB1 + 22 ;
const INT Cmd_LB1_ID_Number      = Cmd_LB1 + 23 ;
const INT Cmd_LB1_SEM_Counter    = Cmd_LB1 + 24 ;

const INT Cmd_LB1_ReadMultiChCnts= Cmd_LB1 + 25 ;
const INT Cmd_LB1_TimingProfile  = Cmd_LB1 + 26 ;
const INT Cmd_LB1_RpcRowData     = Cmd_LB1 + 27 ;


const INT Cmd_LB1_SelectTestSig  = Cmd_LB1 + 28 ;
const INT Cmd_LB1_ClockDeskew    = Cmd_LB1 + 29 ;
const INT Cmd_LB1_FullWin        = Cmd_LB1 + 30 ;
const INT Cmd_LB1_AdjWin         = Cmd_LB1 + 31 ;

const INT Cmd_LB_MAX_CMD_NUMs     = 31 + 1 ;

class Mythread_LB_Update : public QThread
{
    Q_OBJECT
public:
    explicit Mythread_LB_Update(QObject *parent = nullptr);

    ~Mythread_LB_Update();

    void LB_transaction(void);//, int waitTimeout, const QString &request);
    void LB_WriteConfig(UCHAR lb_address, UINT lb_value);
    void Read_Current_Frame (void);

    bool lb_retVal ;

    bool ChBx_LB1_1V               = false ;
    bool ChBx_LB1_1V8_Aux          = false ;
    bool ChBx_LB1_1V_MGTAVCC       = false ;
    bool ChBx_LB1_1V_MGTAVTT       = false ;
    bool ChBx_LB1_1V_MGTVCCAUX     = false ;
    bool ChBx_LB1_1V5              = false ;
    bool ChBx_LB1_1V8              = false ;
    bool ChBx_LB1_2V5              = false ;
    bool ChBx_LB1_3V3              = false ;
    bool ChBx_LB1_3V3VDD           = false ;
    bool ChBx_LB1_CS1_Vout         = false ;
    bool ChBx_LB1_CS2_Vout         = false ;
    bool ChBx_LB1_CS3_Vout         = false ;

    bool ChBx_LB1_Temp_Sensor1     = false ;
    bool ChBx_LB1_Temp_Sensor2     = false ;
    bool ChBx_LB1_Temp_Sensor3     = false ;
    bool ChBx_LB1_ADC_TEMP         = false ;
    bool ChBx_LB1_ADC_AVDD_2       = false ;
    bool ChBx_LB1_ADC_GND          = false ;
    bool ChBx_LB1_FPGA_VCORE       = false ;
    bool ChBx_LB1_FPGA_VCCBRAM     = false ;
    bool ChBx_LB1_FPGA_VCCAUX      = false ;
    bool ChBx_LB1_FPGA_Temp        = false ;
    bool ChBx_LB1_ID_Number        = false ;
    bool ChBx_LB1_SEM_Counter      = false ;

    bool ChBx_LB1_ReadMultiChCnts  = false ;
    bool ChBx_LB1_TimingProfile    = false ;
    bool ChBx_LB1_RpcRowData       = false ;

    bool ChBx_LB1_SelectTestSig    = false ;
    bool ChBx_LB1_ClockDeskew      = false ;
    bool ChBx_LB1_FullWin          = false ;
    bool ChBx_LB1_AdjWin           = false ;

    //==============================================
    bool ChBx_LB2_1V               = false ;
    bool ChBx_LB2_1V8_Aux          = false ;
    bool ChBx_LB2_1V_MGTAVCC       = false ;
    bool ChBx_LB2_1V_MGTAVTT       = false ;
    bool ChBx_LB2_1V_MGTVCCAUX     = false ;
    bool ChBx_LB2_1V5              = false ;
    bool ChBx_LB2_1V8              = false ;
    bool ChBx_LB2_2V5              = false ;
    bool ChBx_LB2_3V3              = false ;
    bool ChBx_LB2_3V3VDD           = false ;
    bool ChBx_LB2_CS1_Vout         = false ;
    bool ChBx_LB2_CS2_Vout         = false ;
    bool ChBx_LB2_CS3_Vout         = false ;

    bool ChBx_LB2_Temp_Sensor1     = false ;
    bool ChBx_LB2_Temp_Sensor2     = false ;
    bool ChBx_LB2_Temp_Sensor3     = false ;
    bool ChBx_LB2_ADC_TEMP         = false ;
    bool ChBx_LB2_ADC_AVDD_2       = false ;
    bool ChBx_LB2_ADC_GND          = false ;
    bool ChBx_LB2_FPGA_VCORE       = false ;
    bool ChBx_LB2_FPGA_VCCBRAM     = false ;
    bool ChBx_LB2_FPGA_VCCAUX      = false ;
    bool ChBx_LB2_FPGA_Temp        = false ;
    bool ChBx_LB2_ID_Number        = false ;
    bool ChBx_LB2_SEM_Counter      = false ;

    bool ChBx_LB2_ReadMultiChCnts  = false ;
    bool ChBx_LB2_TimingProfile    = false ;
    bool ChBx_LB2_RpcRowData       = false ;

    bool ChBx_LB2_SelectTestSig    = false ;
    bool ChBx_LB2_ClockDeskew      = false ;
    bool ChBx_LB2_FullWin          = false ;
    bool ChBx_LB2_AdjWin           = false ;
    //=========================================

    //==============================================
    bool ChBx_LB3_1V               = false ;
    bool ChBx_LB3_1V8_Aux          = false ;
    bool ChBx_LB3_1V_MGTAVCC       = false ;
    bool ChBx_LB3_1V_MGTAVTT       = false ;
    bool ChBx_LB3_1V_MGTVCCAUX     = false ;
    bool ChBx_LB3_1V5              = false ;
    bool ChBx_LB3_1V8              = false ;
    bool ChBx_LB3_2V5              = false ;
    bool ChBx_LB3_3V3              = false ;
    bool ChBx_LB3_3V3VDD           = false ;
    bool ChBx_LB3_CS1_Vout         = false ;
    bool ChBx_LB3_CS2_Vout         = false ;
    bool ChBx_LB3_CS3_Vout         = false ;

    bool ChBx_LB3_Temp_Sensor1     = false ;
    bool ChBx_LB3_Temp_Sensor2     = false ;
    bool ChBx_LB3_Temp_Sensor3     = false ;
    bool ChBx_LB3_ADC_TEMP         = false ;
    bool ChBx_LB3_ADC_AVDD_2       = false ;
    bool ChBx_LB3_ADC_GND          = false ;
    bool ChBx_LB3_FPGA_VCORE       = false ;
    bool ChBx_LB3_FPGA_VCCBRAM     = false ;
    bool ChBx_LB3_FPGA_VCCAUX      = false ;
    bool ChBx_LB3_FPGA_Temp        = false ;
    bool ChBx_LB3_ID_Number        = false ;
    bool ChBx_LB3_SEM_Counter      = false ;

    bool ChBx_LB3_SelectTestSig    = false ;
    bool ChBx_LB3_ClockDeskew      = false ;
    bool ChBx_LB3_FullWin          = false ;
    bool ChBx_LB3_AdjWin           = false ;

    //=========================================


    //==============================================
    bool ChBx_LB4_1V               = false ;
    bool ChBx_LB4_1V8_Aux          = false ;
    bool ChBx_LB4_1V_MGTAVCC       = false ;
    bool ChBx_LB4_1V_MGTAVTT       = false ;
    bool ChBx_LB4_1V_MGTVCCAUX     = false ;
    bool ChBx_LB4_1V5              = false ;
    bool ChBx_LB4_1V8              = false ;
    bool ChBx_LB4_2V5              = false ;
    bool ChBx_LB4_3V3              = false ;
    bool ChBx_LB4_3V3VDD           = false ;
    bool ChBx_LB4_CS1_Vout         = false ;
    bool ChBx_LB4_CS2_Vout         = false ;
    bool ChBx_LB4_CS3_Vout         = false ;

    bool ChBx_LB4_Temp_Sensor1     = false ;
    bool ChBx_LB4_Temp_Sensor2     = false ;
    bool ChBx_LB4_Temp_Sensor3     = false ;
    bool ChBx_LB4_ADC_TEMP         = false ;
    bool ChBx_LB4_ADC_AVDD_2       = false ;
    bool ChBx_LB4_ADC_GND          = false ;
    bool ChBx_LB4_FPGA_VCORE       = false ;
    bool ChBx_LB4_FPGA_VCCBRAM     = false ;
    bool ChBx_LB4_FPGA_VCCAUX      = false ;
    bool ChBx_LB4_FPGA_Temp        = false ;
    bool ChBx_LB4_ID_Number        = false ;
    bool ChBx_LB4_SEM_Counter      = false ;

    bool ChBx_LB4_SelectTestSig    = false ;
    bool ChBx_LB4_ClockDeskew      = false ;
    bool ChBx_LB4_FullWin          = false ;
    bool ChBx_LB4_AdjWin           = false ;

    //=========================================



    //==============================================
    bool ChBx_LB5_1V               = false ;
    bool ChBx_LB5_1V8_Aux          = false ;
    bool ChBx_LB5_1V_MGTAVCC       = false ;
    bool ChBx_LB5_1V_MGTAVTT       = false ;
    bool ChBx_LB5_1V_MGTVCCAUX     = false ;
    bool ChBx_LB5_1V5              = false ;
    bool ChBx_LB5_1V8              = false ;
    bool ChBx_LB5_2V5              = false ;
    bool ChBx_LB5_3V3              = false ;
    bool ChBx_LB5_3V3VDD           = false ;
    bool ChBx_LB5_CS1_Vout         = false ;
    bool ChBx_LB5_CS2_Vout         = false ;
    bool ChBx_LB5_CS3_Vout         = false ;

    bool ChBx_LB5_Temp_Sensor1     = false ;
    bool ChBx_LB5_Temp_Sensor2     = false ;
    bool ChBx_LB5_Temp_Sensor3     = false ;
    bool ChBx_LB5_ADC_TEMP         = false ;
    bool ChBx_LB5_ADC_AVDD_2       = false ;
    bool ChBx_LB5_ADC_GND          = false ;
    bool ChBx_LB5_FPGA_VCORE       = false ;
    bool ChBx_LB5_FPGA_VCCBRAM     = false ;
    bool ChBx_LB5_FPGA_VCCAUX      = false ;
    bool ChBx_LB5_FPGA_Temp        = false ;
    bool ChBx_LB5_ID_Number        = false ;
    bool ChBx_LB5_SEM_Counter      = false ;

    bool ChBx_LB5_SelectTestSig    = false ;
    bool ChBx_LB5_ClockDeskew      = false ;
    bool ChBx_LB5_FullWin          = false ;
    bool ChBx_LB5_AdjWin           = false ;

    //=========================================


    //==============================================
    bool ChBx_LB6_1V               = false ;
    bool ChBx_LB6_1V8_Aux          = false ;
    bool ChBx_LB6_1V_MGTAVCC       = false ;
    bool ChBx_LB6_1V_MGTAVTT       = false ;
    bool ChBx_LB6_1V_MGTVCCAUX     = false ;
    bool ChBx_LB6_1V5              = false ;
    bool ChBx_LB6_1V8              = false ;
    bool ChBx_LB6_2V5              = false ;
    bool ChBx_LB6_3V3              = false ;
    bool ChBx_LB6_3V3VDD           = false ;
    bool ChBx_LB6_CS1_Vout         = false ;
    bool ChBx_LB6_CS2_Vout         = false ;
    bool ChBx_LB6_CS3_Vout         = false ;

    bool ChBx_LB6_Temp_Sensor1     = false ;
    bool ChBx_LB6_Temp_Sensor2     = false ;
    bool ChBx_LB6_Temp_Sensor3     = false ;
    bool ChBx_LB6_ADC_TEMP         = false ;
    bool ChBx_LB6_ADC_AVDD_2       = false ;
    bool ChBx_LB6_ADC_GND          = false ;
    bool ChBx_LB6_FPGA_VCORE       = false ;
    bool ChBx_LB6_FPGA_VCCBRAM     = false ;
    bool ChBx_LB6_FPGA_VCCAUX      = false ;
    bool ChBx_LB6_FPGA_Temp        = false ;
    bool ChBx_LB6_ID_Number        = false ;
    bool ChBx_LB6_SEM_Counter      = false ;

    bool ChBx_LB6_SelectTestSig    = false ;
    bool ChBx_LB6_ClockDeskew      = false ;
    bool ChBx_LB6_FullWin          = false ;
    bool ChBx_LB6_AdjWin           = false ;

    //=========================================


    //==============================================
    bool ChBx_LB7_1V               = false ;
    bool ChBx_LB7_1V8_Aux          = false ;
    bool ChBx_LB7_1V_MGTAVCC       = false ;
    bool ChBx_LB7_1V_MGTAVTT       = false ;
    bool ChBx_LB7_1V_MGTVCCAUX     = false ;
    bool ChBx_LB7_1V5              = false ;
    bool ChBx_LB7_1V8              = false ;
    bool ChBx_LB7_2V5              = false ;
    bool ChBx_LB7_3V3              = false ;
    bool ChBx_LB7_3V3VDD           = false ;
    bool ChBx_LB7_CS1_Vout         = false ;
    bool ChBx_LB7_CS2_Vout         = false ;
    bool ChBx_LB7_CS3_Vout         = false ;

    bool ChBx_LB7_Temp_Sensor1     = false ;
    bool ChBx_LB7_Temp_Sensor2     = false ;
    bool ChBx_LB7_Temp_Sensor3     = false ;
    bool ChBx_LB7_ADC_TEMP         = false ;
    bool ChBx_LB7_ADC_AVDD_2       = false ;
    bool ChBx_LB7_ADC_GND          = false ;
    bool ChBx_LB7_FPGA_VCORE       = false ;
    bool ChBx_LB7_FPGA_VCCBRAM     = false ;
    bool ChBx_LB7_FPGA_VCCAUX      = false ;
    bool ChBx_LB7_FPGA_Temp        = false ;
    bool ChBx_LB7_ID_Number        = false ;
    bool ChBx_LB7_SEM_Counter      = false ;

    bool ChBx_LB7_SelectTestSig    = false ;
    bool ChBx_LB7_ClockDeskew      = false ;
    bool ChBx_LB7_FullWin          = false ;
    bool ChBx_LB7_AdjWin           = false ;
    //=========================================


    //==============================================
    bool ChBx_LB8_1V               = false ;
    bool ChBx_LB8_1V8_Aux          = false ;
    bool ChBx_LB8_1V_MGTAVCC       = false ;
    bool ChBx_LB8_1V_MGTAVTT       = false ;
    bool ChBx_LB8_1V_MGTVCCAUX     = false ;
    bool ChBx_LB8_1V5              = false ;
    bool ChBx_LB8_1V8              = false ;
    bool ChBx_LB8_2V5              = false ;
    bool ChBx_LB8_3V3              = false ;
    bool ChBx_LB8_3V3VDD           = false ;
    bool ChBx_LB8_CS1_Vout         = false ;
    bool ChBx_LB8_CS2_Vout         = false ;
    bool ChBx_LB8_CS3_Vout         = false ;

    bool ChBx_LB8_Temp_Sensor1     = false ;
    bool ChBx_LB8_Temp_Sensor2     = false ;
    bool ChBx_LB8_Temp_Sensor3     = false ;
    bool ChBx_LB8_ADC_TEMP         = false ;
    bool ChBx_LB8_ADC_AVDD_2       = false ;
    bool ChBx_LB8_ADC_GND          = false ;
    bool ChBx_LB8_FPGA_VCORE       = false ;
    bool ChBx_LB8_FPGA_VCCBRAM     = false ;
    bool ChBx_LB8_FPGA_VCCAUX      = false ;
    bool ChBx_LB8_FPGA_Temp        = false ;
    bool ChBx_LB8_ID_Number        = false ;
    bool ChBx_LB8_SEM_Counter      = false ;

    bool ChBx_LB8_SelectTestSig    = false ;
    bool ChBx_LB8_ClockDeskew      = false ;
    bool ChBx_LB8_FullWin          = false ;
    bool ChBx_LB8_AdjWin           = false ;
    //=========================================


    //==============================================
    bool ChBx_LB9_1V               = false ;
    bool ChBx_LB9_1V8_Aux          = false ;
    bool ChBx_LB9_1V_MGTAVCC       = false ;
    bool ChBx_LB9_1V_MGTAVTT       = false ;
    bool ChBx_LB9_1V_MGTVCCAUX     = false ;
    bool ChBx_LB9_1V5              = false ;
    bool ChBx_LB9_1V8              = false ;
    bool ChBx_LB9_2V5              = false ;
    bool ChBx_LB9_3V3              = false ;
    bool ChBx_LB9_3V3VDD           = false ;
    bool ChBx_LB9_CS1_Vout         = false ;
    bool ChBx_LB9_CS2_Vout         = false ;
    bool ChBx_LB9_CS3_Vout         = false ;

    bool ChBx_LB9_Temp_Sensor1     = false ;
    bool ChBx_LB9_Temp_Sensor2     = false ;
    bool ChBx_LB9_Temp_Sensor3     = false ;
    bool ChBx_LB9_ADC_TEMP         = false ;
    bool ChBx_LB9_ADC_AVDD_2       = false ;
    bool ChBx_LB9_ADC_GND          = false ;
    bool ChBx_LB9_FPGA_VCORE       = false ;
    bool ChBx_LB9_FPGA_VCCBRAM     = false ;
    bool ChBx_LB9_FPGA_VCCAUX      = false ;
    bool ChBx_LB9_FPGA_Temp        = false ;
    bool ChBx_LB9_ID_Number        = false ;
    bool ChBx_LB9_SEM_Counter      = false ;

    bool ChBx_LB9_SelectTestSig    = false ;
    bool ChBx_LB9_ClockDeskew      = false ;
    bool ChBx_LB9_FullWin          = false ;
    bool ChBx_LB9_AdjWin           = false ;
    //=====================================================



    //=====================================================
    //CB:  D0 D0 D0 D0 D0 D0 01 00 00 00 00 40 00 00 00 04
    //LB:  D0 D0 D0 D0 D0 D0 21 00 00 00 00 40 00 00 00 04
    unsigned int Val_LB_1V [4]     = {0xD0D0D0D0,
                                      0xD0D02100,
                                      0x00000040,
                                      0x00000004};
                                     /*   "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "00100001" //21
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "01000000" //40
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000100";//04
                                            */
    //=====================================================
    //CB:   D0 D0 D0 D0 D0 D0 01 00 00 00 02 40 00 00 00 04
    //LB:   D0 D0 D0 D0 D0 D0 21 00 00 00 02 40 00 00 00 04
    unsigned int Val_LB_1V8_Aux  [4]  = {0xD0D0D0D0 ,
                                         0xD0D02100 ,
                                         0x00000240 ,
                                         0x00000004} ;
                                        /*"11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "00100001" //21
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000010" //02
                                         "01000000" //40
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000100";//04 */

    //=====================================================
    //CB:   D0 D0 D0 D0 D0 D0 01 00 00 00 04 40 00 00 00 04
    //LB:   D0 D0 D0 D0 D0 D0 21 00 00 00 04 40 00 00 00 04
    unsigned int Val_LB_1V_MGTAVCC [4]   = {0xD0D0D0D0 ,
                                            0xD0D02100 ,
                                            0x00000440 ,
                                            0x00000004};
                                        /*"11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "00100001" //21
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000100" //04
                                         "01000000" //40
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000100";//04 */

    //=====================================================
    //D0 D0 D0 D0 D0 D0 01 00 00 00 06 40 00 00 00 04
    //D0 D0 D0 D0 D0 D0 21 00 00 00 06 40 00 00 00 04
    unsigned int  Val_LB_1V_MGTAVTT [4]   = {0xD0D0D0D0,
                                             0xD0D02100,
                                             0x00000640,
                                             0x00000004 };
                                        /*
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "00100001" //21
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000110" //06
                                         "01000000" //40
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000100";//04
                                         */

    //=====================================================
    //D0 D0 D0 D0 D0 D0 01 00 00 00 08 40 00 00 00 04
    //D0 D0 D0 D0 D0 D0 21 00 00 00 08 40 00 00 00 04
    unsigned int  Val_LB_1V_MGTVCCAUX [4] = {0xD0D0D0D0 ,
                                             0xD0D02100 ,
                                             0x00000840 ,
                                             0x00000004};

                                       /*"11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "00100001" //21
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00001000" //08
                                         "01000000" //40
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000100";//04 */


    //=====================================================
    //D0 D0 D0 D0 D0 D0 01 00 00 00 0C 40 00 00 00 04
    //D0 D0 D0 D0 D0 D0 21 00 00 00 0C 40 00 00 00 04
    unsigned int  Val_LB_1V5  [4]    = {0xD0D0D0D0 ,
                                        0xD0D02100 ,
                                        0x00000C40 ,
                                        0x00000004};
                                         /*"11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "00100001" //21
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00001100" //0C
                                         "01000000" //40
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000100";//04 */

    //=====================================================
    //D0 D0 D0 D0 D0 D0 01 00 00 00 0A 40 00 00 00 04
    //D0 D0 D0 D0 D0 D0 21 00 00 00 0A 40 00 00 00 04
    unsigned int  Val_LB_1V8 [4]     = {0xD0D0D0D0,
                                        0xD0D02100,
                                        0x00000A40,
                                        0x00000004};

                                       /*  "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "00100001" //21
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00001010" //0A
                                         "01000000" //40
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000100";//04 */

    //=====================================================
    //D0 D0 D0 D0 D0 D0 01 00 00 00 10 40 00 00 00 04
    //D0 D0 D0 D0 D0 D0 21 00 00 00 10 40 00 00 00 04
    unsigned int  Val_LB_2V5 [4]  = {0xD0D0D0D0 ,
                                     0xD0D02100 ,
                                     0x00001040 ,
                                     0x00000004};
                                      /*  "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "00100001" //21
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00010000" //10
                                         "01000000" //40
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000100";//04 */

    //=====================================================
    //D0 D0 D0 D0 D0 D0 01 00 00 00 0E 40 00 00 00 04
    //D0 D0 D0 D0 D0 D0 21 00 00 00 0E 40 00 00 00 04
    unsigned int  Val_LB_3V3  [4]     = {0xD0D0D0D0 ,
                                         0xD0D02100 ,
                                         0x00000E40 ,
                                         0x00000004 };

                                        /*"11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "00100001" //21
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00001110" //0E
                                         "01000000" //40
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000100";//04 */

    //=====================================================
    //D0 D0 D0 D0 D0 D0 01 00 00 00 12 40 00 00 00 04
    //D0 D0 D0 D0 D0 D0 21 00 00 00 12 40 00 00 00 04
    unsigned int  Val_LB_3V3VDD [4]  =  {0xD0D0D0D0,
                                         0xD0D02100,
                                         0x00001240,
                                         0x00000004} ;

                                       /*  "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "00100001" //21
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00010010" //12
                                         "01000000" //40
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000100";//04
                                          */

    //=====================================================
    //D0 D0 D0 D0 D0 D0 01 00 00 00 1A 40 00 00 00 04
    //D0 D0 D0 D0 D0 D0 21 00 00 00 1A 40 00 00 00 04
    unsigned int  Val_LB_CS1_Vout [4]  = {0xD0D0D0D0 ,
                                          0xD0D02100,
                                          0x00001A40,
                                          0x00000004};

                                     /* "11010000"
                                        "11010000"
                                        "11010000"
                                        "11010000"
                                        "11010000"
                                        "11010000"
                                        "00100001" //21
                                        "00000000" //00
                                        "00000000" //00
                                        "00000000" //00
                                        "00011010" //1A
                                        "01000000" //40
                                        "00000000" //00
                                        "00000000" //00
                                        "00000000" //00
                                        "00000100";//04 */

    //=====================================================
    //D0 D0 D0 D0 D0 D0 01 00 00 00 1C 40 00 00 00 04
    //D0 D0 D0 D0 D0 D0 21 00 00 00 1C 40 00 00 00 04
    unsigned int  Val_LB_CS2_Vout [4]  = {0xD0D0D0D0,
                                          0xD0D02100,
                                          0x00001C40,
                                          0x00000004};
                                        /*"11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "00100001" //21
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00011100" //1C
                                         "01000000" //40
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000100";//04*/

    //=====================================================
    //D0 D0 D0 D0 D0 D0 01 00 00 00 1E 40 00 00 00 04
    //D0 D0 D0 D0 D0 D0 21 00 00 00 1E 40 00 00 00 04
    unsigned int  Val_LB_CS3_Vout [4]  = {0xD0D0D0D0,
                                          0xD0D02100,
                                          0x00001E40,
                                          0x00000004};
                                      /*   "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "00100001" //21
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00011110" //1E
                                         "01000000" //40
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000100";//04*/

    //=====================================================
    //D0 D0 D0 D0 D0 D0 01 00 00 00 14 40 00 00 00 04
    //D0 D0 D0 D0 D0 D0 21 00 00 00 14 40 00 00 00 04
    unsigned int  Val_LB_Temp_Sensor1 [4] = {0xD0D0D0D0,
                                             0xD0D02100,
                                             0x00001440,
                                             0x00000004};

                                      /*  "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "00100001" //21
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00010100" //14
                                         "01000000" //40
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000100";//04 */

    //=====================================================
    //D0 D0 D0 D0 D0 D0 01 00 00 00 16 40 00 00 00 04
    //D0 D0 D0 D0 D0 D0 21 00 00 00 16 40 00 00 00 04
    unsigned int  Val_LB_Temp_Sensor2 [4] = {0xD0D0D0D0,
                                             0xD0D02100,
                                             0x00001640,
                                             0x00000004};

                                       /*  "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "00100001" //21
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00010110" //16
                                         "01000000" //40
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000100";//04 */

    //=====================================================
    //D0 D0 D0 D0 D0 D0 01 00 00 00 18 40 00 00 00 04
    //D0 D0 D0 D0 D0 D0 21 00 00 00 18 40 00 00 00 04
    unsigned int  Val_LB_Temp_Sensor3 [4] = {0xD0D0D0D0,
                                             0xD0D02100,
                                             0x00001840,
                                             0x00000004};

                                       /*  "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "00100001" //21
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00011000" //18
                                         "01000000" //40
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000100";//04 */

    //=====================================================
    //D0 D0 D0 D0 D0 D0 01 00 00 00 00 80 00 00 00 04
    //D0 D0 D0 D0 D0 D0 21 00 00 00 00 80 00 00 00 04
    unsigned int  Val_LB_Temp_Sensor4 [4] = {0xD0D0D0D0,
                                             0xD0D02100,
                                             0x00000080,
                                             0x00000004};

                                      /*   "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "00100001" //21
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "10000000" //80
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000100";//04 */

    //=====================================================
    //D0 D0 D0 D0 D0 D0 01 00 00 00 00 00 00 00 00 04
    //D0 D0 D0 D0 D0 D0 21 00 00 00 20 00 00 00 00 04
    unsigned int  Val_LB_ADC_TEMP [4]  = {0xD0D0D0D0 ,
                                          0xD0D02100 ,
                                          0x00002000 ,
                                          0x00000004};
                                        /*"11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "00100001" //21
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00100000" //20
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000100";//04
                                            */

    //=====================================================
    //D0 D0 D0 D0 D0 D0 01 00 00 00 00 C0 00 00 00 04
    //D0 D0 D0 D0 D0 D0 21 00 00 00 00 C0 00 00 00 04
    unsigned int Val_LB_ADC_AVDD_2 [4]   = {0xD0D0D0D0,
                                            0xD0D02100,
                                            0x000000C0,
                                            0x00000004};
                                      /* "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "00100001" //21
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "11000000" //C0
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000100";//04
                                            */

   //=====================================================
    //D0 D0 D0 D0 D0 D0 01 00 00 00 01 00 00 00 00 04
   //D0 D0 D0 D0 D0 D0 21 00 00 00 01 00 00 00 00 04
    unsigned int Val_LB_ADC_GND [4]    = {0xD0D0D0D0 ,
                                          0xD0D02100 ,
                                          0x00000100 ,
                                          0x00000004 };
                                         /*
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "00100001" //21
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000001" //01
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000100";//04
                                         */

    unsigned int Val_LB_FPGA_VCORE   [4] = {};// "10101010100110011000100001110111011001100101010101000100001100110010001000010001";
    unsigned int Val_LB_FPGA_VCCBRAM [4] = {};// "10101010100110011000100001110111011001100101010101000100001100110010001000010001";
    unsigned int Val_LB_FPGA_VCCAUX  [4] = {};// "10101010100110011000100001110111011001100101010101000100001100110010001000010001";
    unsigned int Val_LB_FPGA_Temp    [4] = {};// "10101010100110011000100001110111011001100101010101000100001100110010001000010001";

    //=====================================================
    //D0 D0 D0 D0 D0 D0 03 00 00 00 00 00 00 00 00 04
    //D0 D0 D0 D0 D0 D0 23 00 00 00 20 00 00 00 00 04
    unsigned int Val_LB_ID_Number [4] = {0xD0D0D0D0 ,
                                         0xD0D02300 ,
                                         0x00002000 ,
                                         0x00000004 };
                                        /*"11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "00100011"  //23
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00100000"  //20
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000000" //00
                                         "00000100"; //04*/


    //=====================================================
    unsigned int Val_LB_SEM_Counter [4]   = {} ;



    //=====================================================
    //D0D0D0D0 D0D02200 00003800 00000004
    unsigned int Val_LB_ReadMultiChCnts [4] = {0xD0D0D0D0 ,
                                               0xD0D02200 ,
                                               0x00003800 ,
                                               0x00000004 };

    //=====================================================
    //D0D0D0D0 D0D02200 00003A00 00000004
    unsigned int Val_LB_TimingProfile [4]  =   { 0xD0D0D0D0 ,
                                                 0xD0D02200 ,
                                                 0x00003A00 ,
                                                 0x00000004 };

    //=====================================================
    //D0D0D0D0 D0D02200 00003C00 00000004
    unsigned int Val_LB_RpcRowData [4]      = { 0xD0D0D0D0 ,
                                                0xD0D02200 ,
                                                0x00003C00 ,
                                                0x00000004 };

    //=====================================================
    //Cmd_LB1_SelectTestSig   -OK
    //D0 D0 D0 D0 D0 D0 22 00 00 00 22 00 00 00 00 04
    //D0 D0 D0 D0 D0 D0 22 00 00 00 22 00 00 00 00 04
    unsigned int Val_LB_SelectTestSig[4]  =   { 0xD0D0D0D0,
                                                0xD0D02200,
                                                0x00002200,
                                                0x00000004} ;


    //=====================================================
    unsigned int Val_LB_ClockDeskew[4]  =   {   0xD0D0D0D0,
                                                0xD0D02500,
                                                0x00000000,
                                                0x00000004} ;

    //=====================================================
    unsigned int Val_LB_FullWin[4]  =  { 0xD0D0D0D0,
                                         0xD0D02200,
                                         0x00000000,
                                         0x00000004 } ;

    //=====================================================
    unsigned int Val_LB_AdjWin[4]  =   {0xD0D0D0D0,
                                        0xD0D02200,
                                        0x00000000,
                                        0x00000004} ;

    //=====================================================
    QString Current_Frame= "11010000"
                           "11010000"
                           "11010000"
                           "11010000"
                           "11010000"
                           "11010000"
                           "00000001"
                           "00000000"
                           "00000000"
                           "00000000"
                           "00000000"
                           "01000000"
                           "00000000"
                           "00000000"
                           "00000000"
                           "00000100";
    //=====================================================

    UINT Parameter_Counter = 0 ;
    UINT lb_value=0;
    UINT lb_value2 =0;
    bool lb_prog_full = false;

    unsigned int Out_frame_arr[4];
    unsigned int LB_Number = 0 ;
    bool LB1_Select = false;
    unsigned int temp = 0 ;
    unsigned int LB_DiagInstCode = 0 ;

    unsigned int LB1_TestSig_Number    = 0 ;
    unsigned int LB1_ClockDeskew_Value = 0 ;
    unsigned int LB1_FullWin_value     = 0 ;
    unsigned int LB1_AdjWin_value      = 0 ;

    unsigned int LB2_TestSig_Number    = 0 ;
    unsigned int LB2_ClockDeskew_Value = 0 ;
    unsigned int LB2_FullWin_value     = 0 ;
    unsigned int LB2_AdjWin_value      = 0 ;

    unsigned int LB3_TestSig_Number    = 0 ;
    unsigned int LB3_ClockDeskew_Value = 0 ;
    unsigned int LB3_FullWin_value     = 0 ;
    unsigned int LB3_AdjWin_value      = 0 ;

    unsigned int LB4_TestSig_Number    = 0 ;
    unsigned int LB4_ClockDeskew_Value = 0 ;
    unsigned int LB4_FullWin_value     = 0 ;
    unsigned int LB4_AdjWin_value      = 0 ;

    unsigned int LB5_TestSig_Number    = 0 ;
    unsigned int LB5_ClockDeskew_Value = 0 ;
    unsigned int LB5_FullWin_value     = 0 ;
    unsigned int LB5_AdjWin_value      = 0 ;

    unsigned int LB6_TestSig_Number    = 0 ;
    unsigned int LB6_ClockDeskew_Value = 0 ;
    unsigned int LB6_FullWin_value     = 0 ;
    unsigned int LB6_AdjWin_value      = 0 ;

    unsigned int LB7_TestSig_Number    = 0 ;
    unsigned int LB7_ClockDeskew_Value = 0 ;
    unsigned int LB7_FullWin_value     = 0 ;
    unsigned int LB7_AdjWin_value      = 0 ;

    unsigned int LB8_TestSig_Number    = 0 ;
    unsigned int LB8_ClockDeskew_Value = 0 ;
    unsigned int LB8_FullWin_value     = 0 ;
    unsigned int LB8_AdjWin_value      = 0 ;

    unsigned int LB9_TestSig_Number    = 0 ;
    unsigned int LB9_ClockDeskew_Value = 0 ;
    unsigned int LB9_FullWin_value     = 0 ;
    unsigned int LB9_AdjWin_value      = 0 ;

signals:
    void LB_respond_send(const UINT LB_Parameter_Counter) ;// ,const boolean Buffer_full );

private:
    void run() override;

    QMutex lb_mutex;
    QWaitCondition lb_cond;
    bool lb_quit = false;
    bool ChBx_checked = false;

    UINT64 lb_fileLength = 16;
    char *lb_sendBuf;

    char    lb_buffer[RECV_PACKET_SIZE];
    UCHAR   lb_command=0;
    USHORT  lb_address=0 ;

    USHORT  lb_length=0 ;
    UCHAR   lb_packetCounter=0;

    bool    lb_disp_once = true;
    UINT64  lb_counter = 0;





};

#endif // MYTHREAD_LB_UPDATE_H
