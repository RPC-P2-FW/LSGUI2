#ifndef MYTHREAD_CB_UPDATE_H
#define MYTHREAD_CB_UPDATE_H

#include <QObject>
#include <QtCore>
#include "YasinLanLib.h"
#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QString>


const INT Cmd_CB_1V = 0 ;
const INT Cmd_CB_1V8_Aux = 1 ;
const INT Cmd_CB_1V_MGTAVCC = 2 ;
const INT Cmd_CB_1V_MGTAVTT = 3 ;
const INT Cmd_CB_1V_MGTVCCAUX = 4 ;
const INT Cmd_CB_1V5 = 5 ;
const INT Cmd_CB_1V8 = 6 ;
const INT Cmd_CB_2V5 = 7 ;
const INT Cmd_CB_3V3 = 8 ;
const INT Cmd_CB_3V3VDD = 9 ;
const INT Cmd_CB_CS1_Vout = 10 ;
const INT Cmd_CB_CS2_Vout = 11 ;
const INT Cmd_CB_CS3_Vout = 12 ;


const INT Cmd_CB_Temp_Sensor1 = 13 ;
const INT Cmd_CB_Temp_Sensor2 = 14 ;
const INT Cmd_CB_Temp_Sensor3 = 15 ;
const INT Cmd_CB_ADC_TEMP = 16 ;
const INT Cmd_CB_ADC_AVDD_2 = 17 ;
const INT Cmd_CB_ADC_GND = 18 ;
const INT Cmd_CB_FPGA_VCORE = 19 ;
const INT Cmd_CB_FPGA_VCCBRAM = 20 ;
const INT Cmd_CB_FPGA_VCCAUX = 21 ;
const INT Cmd_CB_FPGA_Temp = 22 ;
const INT Cmd_CB_ID_Number = 23 ;
const INT Cmd_CB_SEM_Counter = 24 ;

const INT Cmd_CB_FEB1_DAC1_Ch1_Set_Vth1 = 25 ;
const INT Cmd_CB_FEB1_DAC1_Ch2_Set_Vth2 = 26  ;
const INT Cmd_CB_FEB1_DAC1_Ch3_Set_Vmon1 = 27 ;
const INT Cmd_CB_FEB1_DAC1_Ch3_Set_Vmon2 = 28 ;
const INT Cmd_CB_FEB1_DAC1_ON = 29 ;
const INT Cmd_CB_FEB1_ADC1_Read_Temp = 30 ;
const INT Cmd_CB_FEB1_ADC1_Read_Ch1_Vth1 = 31 ;
const INT Cmd_CB_FEB1_ADC1_Read_Ch2_Vth2 = 32 ;
const INT Cmd_CB_FEB1_ADC1_Read_Ch3_VMon1 = 33 ;
const INT Cmd_CB_FEB1_ADC1_Read_Ch4_VMon2 = 34 ;
const INT Cmd_CB_FEB1_DAC2_Ch1_Set_Vth1 = 35 ;
const INT Cmd_CB_FEB1_DAC2_Ch2_Set_Vth2 = 36 ;
const INT Cmd_CB_FEB1_DAC2_Ch3_Set_Vmon1 = 37 ;
const INT Cmd_CB_FEB1_DAC2_Ch4_Set_Vmon2 = 38 ;
const INT Cmd_CB_FEB1_DAC2_ON = 39 ;
const INT Cmd_CB_FEB1_ADC2_Read_Temp = 40 ;
const INT Cmd_CB_FEB1_ADC2_Read_Ch1_Vth1 = 41 ;
const INT Cmd_CB_FEB1_ADC2_Read_Ch2_Vth2 = 42 ;
const INT Cmd_CB_FEB1_ADC2_Read_Ch3_VMon1 = 43 ;
const INT Cmd_CB_FEB1_ADC2_Read_Ch4_VMon2 = 44 ;

const INT Cmd_CB_FEB2_DAC1_Ch1_Set_Vth1 = 45 ;
const INT Cmd_CB_FEB2_DAC1_Ch2_Set_Vth2 = 46 ;
const INT Cmd_CB_FEB2_DAC1_Ch3_Set_Vmon1 = 47 ;
const INT Cmd_CB_FEB2_DAC1_Ch3_Set_Vmon2 = 48 ;
const INT Cmd_CB_FEB2_DAC1_ON = 49 ;
const INT Cmd_CB_FEB2_ADC1_Read_Temp = 50 ;
const INT Cmd_CB_FEB2_ADC1_Read_Ch1_Vth1 = 51 ;
const INT Cmd_CB_FEB2_ADC1_Read_Ch2_Vth2 = 52 ;
const INT Cmd_CB_FEB2_ADC1_Read_Ch3_VMon1 = 53 ;
const INT Cmd_CB_FEB2_ADC1_Read_Ch4_VMon2 = 54 ;
const INT Cmd_CB_FEB2_DAC2_Ch1_Set_Vth1 = 55 ;
const INT Cmd_CB_FEB2_DAC2_Ch2_Set_Vth2 = 56 ;
const INT Cmd_CB_FEB2_DAC2_Ch3_Set_Vmon1 = 57 ;
const INT Cmd_CB_FEB2_DAC2_Ch4_Set_Vmon2 = 58 ;
const INT Cmd_CB_FEB2_DAC2_ON = 59 ;
const INT Cmd_CB_FEB2_ADC2_Read_Temp = 60 ;
const INT Cmd_CB_FEB2_ADC2_Read_Ch1_Vth1 = 61 ;
const INT Cmd_CB_FEB2_ADC2_Read_Ch2_Vth2 = 62 ;
const INT Cmd_CB_FEB2_ADC2_Read_Ch3_VMon1 = 63 ;
const INT Cmd_CB_FEB2_ADC2_Read_Ch4_VMon2 = 64 ;

const INT Cmd_CB_FEB3_DAC1_Ch1_Set_Vth1 = 65 ;
const INT Cmd_CB_FEB3_DAC1_Ch2_Set_Vth2 = 66 ;
const INT Cmd_CB_FEB3_DAC1_Ch3_Set_Vmon1 = 67 ;
const INT Cmd_CB_FEB3_DAC1_Ch3_Set_Vmon2 = 68 ;
const INT Cmd_CB_FEB3_DAC1_ON = 69 ;
const INT Cmd_CB_FEB3_ADC1_Read_Temp = 70 ;
const INT Cmd_CB_FEB3_ADC1_Read_Ch1_Vth1 = 71 ;
const INT Cmd_CB_FEB3_ADC1_Read_Ch2_Vth2 = 72 ;
const INT Cmd_CB_FEB3_ADC1_Read_Ch3_VMon1 = 73 ;
const INT Cmd_CB_FEB3_ADC1_Read_Ch4_VMon2 = 74 ;
const INT Cmd_CB_FEB3_DAC2_Ch1_Set_Vth1 = 75 ;
const INT Cmd_CB_FEB3_DAC2_Ch2_Set_Vth2 = 76 ;
const INT Cmd_CB_FEB3_DAC2_Ch3_Set_Vmon1 = 77 ;
const INT Cmd_CB_FEB3_DAC2_Ch4_Set_Vmon2 = 78 ;
const INT Cmd_CB_FEB3_DAC2_ON = 79 ;
const INT Cmd_CB_FEB3_ADC2_Read_Temp = 80 ;
const INT Cmd_CB_FEB3_ADC2_Read_Ch1_Vth1 = 81 ;
const INT Cmd_CB_FEB3_ADC2_Read_Ch2_Vth2 = 82 ;
const INT Cmd_CB_FEB3_ADC2_Read_Ch3_VMon1 = 83 ;
const INT Cmd_CB_FEB3_ADC2_Read_Ch4_VMon2 = 84 ;

const INT Cmd_CB_Turn_ON_LinkBoard = 85 ;


const INT Cmd_CB_MAX_CMD_NUMs     = 85 + 1 ;


class Mythread_CB_Update : public QThread
{
    Q_OBJECT
public:
    explicit Mythread_CB_Update(QObject *parent = nullptr);

    ~Mythread_CB_Update();

     void CB_transaction(void);//, int waitTimeout, const QString &request);
     void CB_WriteConfig(UCHAR cb_address, UINT cb_value);
     void Read_Current_Frame (void);

     bool cb_retVal ;

     bool ChBx_CB_1V = false;
     bool ChBx_CB_1V8_Aux = false ;
     bool ChBx_CB_1V_MGTAVCC = false;
     bool ChBx_CB_1V_MGTAVTT = false;
     bool ChBx_CB_1V_MGTVCCAUX = false;
     bool ChBx_CB_1V5 = false;
     bool ChBx_CB_1V8 = false;
     bool ChBx_CB_2V5 = false;
     bool ChBx_CB_3V3 = false;
     bool ChBx_CB_3V3VDD = false;
     bool ChBx_CB_CS1_Vout = false;
     bool ChBx_CB_CS2_Vout = false;
     bool ChBx_CB_CS3_Vout = false;

     bool ChBx_CB_Temp_Sensor1 = false;
     bool ChBx_CB_Temp_Sensor2 = false;
     bool ChBx_CB_Temp_Sensor3 = false;
     bool ChBx_CB_ADC_TEMP = false;
     bool ChBx_CB_ADC_AVDD_2 = false;
     bool ChBx_CB_ADC_GND = false;
     bool ChBx_CB_FPGA_VCORE = false;
     bool ChBx_CB_FPGA_VCCBRAM = false;
     bool ChBx_CB_FPGA_VCCAUX = false;
     bool ChBx_CB_FPGA_Temp = false;
     bool ChBx_CB_ID_Number = false;
     bool ChBx_CB_SEM_Counter = false;


     bool  ChBx_CB_FEB1_DAC1_Ch1_Set_Vth1 = false;
     bool  ChBx_CB_FEB1_DAC1_Ch2_Set_Vth2 = false;
     bool  ChBx_CB_FEB1_DAC1_Ch3_Set_Vmon1 = false;
     bool  ChBx_CB_FEB1_DAC1_Ch4_Set_Vmon2= false;
     bool  ChBx_CB_FEB1_DAC1_ON = false;

     bool  ChBx_CB_FEB1_DAC2_Ch1_Set_Vth1 = false;
     bool  ChBx_CB_FEB1_DAC2_Ch2_Set_Vth2= false;
     bool  ChBx_CB_FEB1_DAC2_Ch3_Set_Vmon1= false;
     bool  ChBx_CB_FEB1_DAC2_Ch4_Set_Vmon2= false;
     bool  ChBx_CB_FEB1_DAC2_ON= false;

     bool  ChBx_CB_FEB1_ADC1_Read_Temp = false;
     bool  ChBx_CB_FEB1_ADC1_Read_Ch1_Vth1= false;
     bool  ChBx_CB_FEB1_ADC1_Read_Ch2_Vth2= false;
     bool  ChBx_CB_FEB1_ADC1_Read_Ch3_VMon1= false;
     bool  ChBx_CB_FEB1_ADC1_Read_Ch4_VMon2= false;

     bool  ChBx_CB_FEB1_ADC2_Read_Temp= false;
     bool  ChBx_CB_FEB1_ADC2_Read_Ch1_Vth1= false;
     bool  ChBx_CB_FEB1_ADC2_Read_Ch2_Vth2= false;
     bool  ChBx_CB_FEB1_ADC2_Read_Ch3_VMon1= false;
     bool  ChBx_CB_FEB1_ADC2_Read_Ch4_VMon2= false;



     bool  ChBx_CB_FEB2_DAC1_Ch1_Set_Vth1 = false;
     bool  ChBx_CB_FEB2_DAC1_Ch2_Set_Vth2 = false;
     bool  ChBx_CB_FEB2_DAC1_Ch3_Set_Vmon1 = false;
     bool  ChBx_CB_FEB2_DAC1_Ch4_Set_Vmon2= false;
     bool  ChBx_CB_FEB2_DAC1_ON = false;

     bool  ChBx_CB_FEB2_DAC2_Ch1_Set_Vth1 = false;
     bool  ChBx_CB_FEB2_DAC2_Ch2_Set_Vth2= false;
     bool  ChBx_CB_FEB2_DAC2_Ch3_Set_Vmon1= false;
     bool  ChBx_CB_FEB2_DAC2_Ch4_Set_Vmon2= false;
     bool  ChBx_CB_FEB2_DAC2_ON= false;

     bool  ChBx_CB_FEB2_ADC1_Read_Temp = false;
     bool  ChBx_CB_FEB2_ADC1_Read_Ch1_Vth1= false;
     bool  ChBx_CB_FEB2_ADC1_Read_Ch2_Vth2= false;
     bool  ChBx_CB_FEB2_ADC1_Read_Ch3_VMon1= false;
     bool  ChBx_CB_FEB2_ADC1_Read_Ch4_VMon2= false;

     bool  ChBx_CB_FEB2_ADC2_Read_Temp= false;
     bool  ChBx_CB_FEB2_ADC2_Read_Ch1_Vth1= false;
     bool  ChBx_CB_FEB2_ADC2_Read_Ch2_Vth2= false;
     bool  ChBx_CB_FEB2_ADC2_Read_Ch3_VMon1= false;
     bool  ChBx_CB_FEB2_ADC2_Read_Ch4_VMon2= false;



     bool  ChBx_CB_FEB3_DAC1_Ch1_Set_Vth1 = false;
     bool  ChBx_CB_FEB3_DAC1_Ch2_Set_Vth2 = false;
     bool  ChBx_CB_FEB3_DAC1_Ch3_Set_Vmon1 = false;
     bool  ChBx_CB_FEB3_DAC1_Ch4_Set_Vmon2= false;
     bool  ChBx_CB_FEB3_DAC1_ON = false;

     bool  ChBx_CB_FEB3_DAC2_Ch1_Set_Vth1 = false;
     bool  ChBx_CB_FEB3_DAC2_Ch2_Set_Vth2= false;
     bool  ChBx_CB_FEB3_DAC2_Ch3_Set_Vmon1= false;
     bool  ChBx_CB_FEB3_DAC2_Ch4_Set_Vmon2= false;
     bool  ChBx_CB_FEB3_DAC2_ON= false;

     bool  ChBx_CB_FEB3_ADC1_Read_Temp = false;
     bool  ChBx_CB_FEB3_ADC1_Read_Ch1_Vth1= false;
     bool  ChBx_CB_FEB3_ADC1_Read_Ch2_Vth2= false;
     bool  ChBx_CB_FEB3_ADC1_Read_Ch3_VMon1= false;
     bool  ChBx_CB_FEB3_ADC1_Read_Ch4_VMon2= false;  

     bool  ChBx_CB_FEB3_ADC2_Read_Temp= false;
     bool  ChBx_CB_FEB3_ADC2_Read_Ch1_Vth1= false;
     bool  ChBx_CB_FEB3_ADC2_Read_Ch2_Vth2= false;
     bool  ChBx_CB_FEB3_ADC2_Read_Ch3_VMon1= false;
     bool  ChBx_CB_FEB3_ADC2_Read_Ch4_VMon2= false;

     bool  ChBx_CB_Cmd_Turn_ON_LBBX= false;
     bool  ChBx_CB_Cmd_Turn_ON_LB1= false;
     bool  ChBx_CB_Cmd_Turn_ON_LB2= false;
     bool  ChBx_CB_Cmd_Turn_ON_LB3= false;
     bool  ChBx_CB_Cmd_Turn_ON_LB4= false;
     bool  ChBx_CB_Cmd_Turn_ON_LB5= false;
     bool  ChBx_CB_Cmd_Turn_ON_LB6= false;
     bool  ChBx_CB_Cmd_Turn_ON_LB7= false;
     bool  ChBx_CB_Cmd_Turn_ON_LB8= false;
     bool  ChBx_CB_Cmd_Turn_ON_LB9= false;

     //=====================================================
     //D0 D0 D0 D0 D0 D0 01 00 00 00 00 40 00 00 00 04
     unsigned int  Val_CB_1V [4]   = {0xD0D0D0D0,
                                      0xD0D00100,
                                      0x00000040,
                                      0x00000004};
                                       /* "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "00000001" //01
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "01000000" //40
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000100";//04 */

     //=====================================================
     //D0 D0 D0 D0 D0 D0 01 00 00 00 02 40 00 00 00 04
     unsigned int Val_CB_1V8_Aux  [4]   = { 0xD0D0D0D0,
                                            0xD0D00100,
                                            0x00000240,
                                            0x00000004};
                                       /* "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "00000001" //01
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
     //D0 D0 D0 D0 D0 D0 01 00 00 00 04 40 00 00 00 04
     unsigned int Val_CB_1V_MGTAVCC  [4]  = {0xD0D0D0D0,
                                             0xD0D00100,
                                             0x00000440,
                                             0x00000004};
                                      /*  "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "00000001" //01
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
     unsigned int Val_CB_1V_MGTAVTT  [4]  = {0xD0D0D0D0,
                                             0xD0D00100,
                                             0x00000640,
                                             0x00000004};

                                        /*  "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "00000001" //01
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000110" //06
                                          "01000000" //40
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000100";//04 */

     //=====================================================
     //D0 D0 D0 D0 D0 D0 01 00 00 00 08 40 00 00 00 04
     unsigned int Val_CB_1V_MGTVCCAUX [4] = {0xD0D0D0D0,
                                             0xD0D00100,
                                             0x00000840,
                                             0x00000004};

                                       /*   "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "00000001" //01
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
     unsigned int Val_CB_1V5     [4]   = {0xD0D0D0D0,
                                          0xD0D00100,
                                          0x00000C40,
                                          0x00000004};

                                       /* "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "00000001" //01
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
     unsigned int Val_CB_1V8        [4]   = {0xD0D0D0D0,
                                             0xD0D00100,
                                             0x00000A40,
                                             0x00000004};

                                      /*  "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "00000001" //01
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
     //D0D0D0D0D0D0 01 00 00 00 10 40 00 00 00 04
     unsigned int Val_CB_2V5         [4]  = {0xD0D0D0D0,
                                             0xD0D00100,
                                             0x00001040,
                                             0x00000004};

                                      /*  "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "00000001" //01
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
     unsigned int Val_CB_3V3        [4]   = {0xD0D0D0D0,
                                             0xD0D00100,
                                             0x00000E40,
                                             0x00000004};
                                       /* "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "00000001" //01
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
     unsigned int Val_CB_3V3VDD      [4]  = {0xD0D0D0D0,
                                             0xD0D00100,
                                             0x00001240,
                                             0x00000004};

                                       /* "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "00000001" //01
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00010010" //12
                                          "01000000" //40
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000100";//04 */

     //=====================================================
     //D0 D0 D0 D0 D0 D0 01 00 00 00 1A 40 00 00 00 04
     unsigned int Val_CB_CS1_Vout    [4]  = {0xD0D0D0D0,
                                             0xD0D00100,
                                             0x00001A40,
                                             0x00000004};
                                        /*"11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "11010000"
                                         "00000001" //01
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
     unsigned int Val_CB_CS2_Vout     [4] = {0xD0D0D0D0,
                                             0xD0D00100,
                                             0x00001C40,
                                             0x00000004};
                                       /* "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "00000001" //01
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00011100" //1C
                                          "01000000" //40
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000100";//04 */

     //=====================================================
     //D0 D0 D0 D0 D0 D0 01 00 00 00 1E 40 00 00 00 04
     unsigned int Val_CB_CS3_Vout    [4]  = {0xD0D0D0D0,
                                             0xD0D00100,
                                             0x00001E40,
                                             0x00000004};
                                    /*    "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "00000001" //01
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00011110" //1E
                                          "01000000" //40
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000100";//04 */

     //=====================================================
     //D0 D0 D0 D0 D0 D0 01 00 00 00 14 40 00 00 00 04
     unsigned int Val_CB_Temp_Sensor1  [4] = {0xD0D0D0D0,
                                              0xD0D00100,
                                              0x00001440,
                                              0x00000004};
                                         /*"11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "00000001" //01
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
     unsigned int Val_CB_Temp_Sensor2  [4] = {0xD0D0D0D0,
                                              0xD0D00100,
                                              0x00001640,
                                              0x00000004};
                                       /* "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "00000001" //01
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
     unsigned int Val_CB_Temp_Sensor3 [4] = {0xD0D0D0D0,
                                             0xD0D00100,
                                             0x00001840,
                                             0x00000004};

                                       /*   "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "00000001" //01
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00011000" //18
                                          "01000000" //40
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000100";//04  */

     //=====================================================
     //D0 D0 D0 D0 D0 D0 01 00 00 00 00 80 00 00 00 04
     unsigned int Val_CB_Temp_Sensor4  [4] = {0xD0D0D0D0,
                                              0xD0D00100,
                                              0x00000080,
                                              0x00000004};

                                       /*"11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "00000001" //01
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
     unsigned int Val_CB_ADC_TEMP     [4] = {0xD0D0D0D0,
                                             0xD0D00100,
                                             0x00000000,
                                             0x00000004};
                                        /*"11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "00000001" //01
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000100";//04 */

     //=====================================================
     //D0 D0 D0 D0 D0 D0 01 00 00 00 00 C0 00 00 00 04
     unsigned int Val_CB_ADC_AVDD_2   [4] = {0xD0D0D0D0,
                                             0xD0D00100,
                                             0x000000C0,
                                             0x00000004};
                                        /*"11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "00000001" //01
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "11000000" //C0
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000100";//04 */

     //=====================================================
    //D0 D0 D0 D0 D0 D0 01 00 00 00 01 00 00 00 00 04
    //D0 D0 D0 D0 D0 D0 01 00 00 00 01 00 00 00 00 04
     unsigned int Val_CB_ADC_GND     [4]  = {0xD0D0D0D0,
                                             0xD0D00100,
                                             0x00000100,
                                             0x00000004};
                                        /*"11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "00000001" //01
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000001" //01
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000100";//04 */


     //=====================================================
     unsigned int Val_CB_FPGA_VCORE   [4]  = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/
     unsigned int Val_CB_FPGA_VCCBRAM [4] = {};/*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/
     unsigned int Val_CB_FPGA_VCCAUX  [4] = {};/*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/
     unsigned int Val_CB_FPGA_Temp    [4] = {};/*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     //=====================================================
     //D0 D0 D0 D0 D0 D0 03 00 00 00 00 00 00 00 00 04
     unsigned int Val_CB_ID_Number    [4] =  {0xD0D0D0D0,
                                              0xD0D00300,
                                              0x00000000,
                                              0x00000004};
                                        /*"11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "11010000"
                                          "00000011" //03
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000000" //00
                                          "00000100";//04 */

     //=====================================================
     unsigned int Val_CB_SEM_Counter  [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001"; */



     //=====================================================
     //D0 D0 D0 D0      D0 D0 02 00      00 00 40 10     F0 00 00 04
     //D0 D0 D0 D0      D0 D0 02 00      00 00 40 10     3C 00 00 00
     unsigned int Val_CB_FEB1_DAC1_Ch1_Set_Vth1 [4]   = {0xD0D0D0D0,
                                                         0xD0D00200,
                                                         0x00004010,
                                                         0x00000004};

                                                    /*"11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "00000010" //02
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "01000000" //40
                                                      "00010000" //10
                                                      "11110000" //F0
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000100";//04*/

     //=====================================================
     //D0 D0 D0 D0 D0 D0 02 00 00 00 40 20 F0 00 00 04
     unsigned int Val_CB_FEB1_DAC1_Ch2_Set_Vth2   [4] = {0xD0D0D0D0,
                                                         0xD0D00200,
                                                         0x00004020,
                                                         0x00000004};
                                                    /*"11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "00000010" //02
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "01000000" //40
                                                      "00100000" //20
                                                      "11110000" //F0
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000100";//04*/

     //=====================================================
     //D0 D0 D0 D0 D0 D0 02 00 00 00 40 30 F0 00 00 04
     unsigned int Val_CB_FEB1_DAC1_Ch3_Set_Vmon1  [4] = {0xD0D0D0D0,
                                                         0xD0D00200,
                                                         0x00004030,
                                                         0x00000004};
                                                   /* "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "00000010" //02
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "01000000" //40
                                                      "00110000" //30
                                                      "11110000" //F0
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000100";//04 */


     //=====================================================
     //D0 D0 D0 D0 D0 D0 02 00 00 00 40 40 F0 00 00 04
     unsigned int Val_CB_FEB1_DAC1_Ch4_Set_Vmon2  [4] = {0xD0D0D0D0,
                                                         0xD0D00200,
                                                         0x00004040,
                                                         0x00000004};

                                                    /*"11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "00000010" //02
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "01000000" //40
                                                      "01000000" //40
                                                      "11110000" //F0
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000100";//04*/


     //=====================================================
     unsigned int Val_CB_FEB1_DAC1_ON     [4]  = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     //=====================================================
     unsigned int Val_CB_FEB1_DAC2_Ch1_Set_Vth1   [4]  = {  0xd0d0d0d0,
                                                            0xd0d00200,
                                                            0x00004090,
                                                            0x00000004};/*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/
     //=====================================================

     unsigned int Val_CB_FEB1_DAC2_Ch2_Set_Vth2   [4]  = {  0xd0d0d0d0,
                                                            0xd0d00200,
                                                            0x000040a0,
                                                            0x00000004};/*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     //=====================================================
     unsigned int Val_CB_FEB1_DAC2_Ch3_Set_Vmon1  [4]  = {  0xd0d0d0d0,
                                                            0xd0d00200,
                                                            0x000040b0,
                                                            0x00000004};/*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     //=====================================================
     unsigned int Val_CB_FEB1_DAC2_Ch4_Set_Vmon2  [4]  = {  0xd0d0d0d0,
                                                            0xd0d00200,
                                                            0x000040c0,
                                                            0x00000004};/*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/


     //=====================================================
     unsigned int Val_CB_FEB1_DAC2_ON             [4]  = {};/*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     //=====================================================
     //D0 D0 D0 D0 D0 D0 02 00 00 00 00 00 00 00 00 04
     unsigned int Val_CB_FEB1_ADC1_Read_Temp      [4] = {0xD0D0D0D0,
                                                         0xD0D00200,
                                                         0x00000000,
                                                         0x00000004};
                                                    /*"11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "00000010" //02
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000100";//04*/

     //=====================================================
     //D0 D0 D0 D0 D0 D0 02 00 00 00 00 10 00 00 00 04
     unsigned int Val_CB_FEB1_ADC1_Read_Ch1_Vth1  [4] = {0xD0D0D0D0,
                                                         0xD0D00200,
                                                         0x00000010,
                                                         0x00000004};

                                                    /*"11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "00000010" //02
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00010000" //10
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000100";//04 */

     //=====================================================
     //D0 D0 D0 D0 D0 D0 02 00 00 00 00 20 00 00 00 04
     unsigned int Val_CB_FEB1_ADC1_Read_Ch2_Vth2  [4] = {0xD0D0D0D0,
                                                         0xD0D00200,
                                                         0x00000020,
                                                         0x00000004};

                                                    /*"11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "00000010" //02
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00100000" //20
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000100";//04 */

     //=====================================================
     //D0 D0 D0 D0 D0 D0 02 00 00 00 00 30 00 00 00 04
     unsigned int Val_CB_FEB1_ADC1_Read_Ch3_VMon1 [4] = {0xD0D0D0D0,
                                                         0xD0D00200,
                                                         0x00000030,
                                                         0x00000004};

                                                    /*"11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "00000010" //02
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00110000" //30
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000100";//04*/


     //=====================================================
     //D0 D0 D0 D0 D0 D0 02 00 00 00 00 40 00 00 00 04
     unsigned int Val_CB_FEB1_ADC1_Read_Ch4_VMon2 [4] = {0xD0D0D0D0,
                                                         0xD0D00200,
                                                         0x00000040,
                                                         0x00000004};

                                                    /*"11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "11010000"
                                                      "00000010" //02
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "01000000" //40
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000000" //00
                                                      "00000100";//04 */

//=====================================================
     unsigned int Val_CB_FEB1_ADC2_Read_Temp      [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     unsigned int Val_CB_FEB1_ADC2_Read_Ch1_Vth1  [4] = {   0xd0d0d0d0,
                                                            0xd0d00200,
                                                            0x00000090,
                                                            0x00000004}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     unsigned int Val_CB_FEB1_ADC2_Read_Ch2_Vth2  [4] = {   0xd0d0d0d0,
                                                            0xd0d00200,
                                                            0x000000a0,
                                                            0x00000004}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     unsigned int Val_CB_FEB1_ADC2_Read_Ch3_VMon1 [4] = {   0xd0d0d0d0,
                                                            0xd0d00200,
                                                            0x000000b0,
                                                            0x00000004}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     unsigned int Val_CB_FEB1_ADC2_Read_Ch4_VMon2 [4] = {   0xd0d0d0d0,
                                                            0xd0d00200,
                                                            0x000000c0,
                                                            0x00000004}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     //----------------------------------------------------------------------
     //     FEB2 - DAC1
     //----------------------------------------------------------------------
     unsigned int Val_CB_FEB2_DAC1_Ch1_Set_Vth1   [4] = {   0xd0d0d0d0,
                                                            0xd0d00200,
                                                            0x00004410,
                                                            0x00000004}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     unsigned int Val_CB_FEB2_DAC1_Ch2_Set_Vth2   [4] = {   0xd0d0d0d0,
                                                            0xd0d00200,
                                                            0x00004420,
                                                            0x00000004}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     unsigned int Val_CB_FEB2_DAC1_Ch3_Set_Vmon1  [4] = {   0xd0d0d0d0,
                                                            0xd0d00200,
                                                            0x00004430,
                                                            0x00000004}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     unsigned int Val_CB_FEB2_DAC1_Ch4_Set_Vmon2   [4]= {   0xd0d0d0d0,
                                                            0xd0d00200,
                                                            0x00004440,
                                                            0x00000004}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     unsigned int Val_CB_FEB2_DAC1_ON             [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     //----------------------------------------------------------------------
     //     FEB2 - DAC2
     //----------------------------------------------------------------------
     unsigned int Val_CB_FEB2_DAC2_Ch1_Set_Vth1   [4] = {   0xd0d0d0d0,
                                                            0xd0d00200,
                                                            0x00004490,
                                                            0x00000004}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     unsigned int Val_CB_FEB2_DAC2_Ch2_Set_Vth2   [4] = {   0xd0d0d0d0,
                                                            0xd0d00200,
                                                            0x000044a0,
                                                            0x00000004}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     unsigned int Val_CB_FEB2_DAC2_Ch3_Set_Vmon1  [4] = {   0xd0d0d0d0,
                                                            0xd0d00200,
                                                            0x000044b0,
                                                            0x00000004}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     unsigned int Val_CB_FEB2_DAC2_Ch4_Set_Vmon2  [4] = {   0xd0d0d0d0,
                                                            0xd0d00200,
                                                            0x000044c0,
                                                            0x00000004}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     unsigned int Val_CB_FEB2_DAC2_ON             [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     //----------------------------------------------------------------------
     //     FEB2 - ADC1
     //----------------------------------------------------------------------
     unsigned int Val_CB_FEB2_ADC1_Read_Temp      [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/


     unsigned int Val_CB_FEB2_ADC1_Read_Ch1_Vth1  [4] = {   0xd0d0d0d0,
                                                            0xd0d00200,
                                                            0x00000410,
                                                            0x00000004}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     unsigned int Val_CB_FEB2_ADC1_Read_Ch2_Vth2  [4] = {   0xd0d0d0d0,
                                                            0xd0d00200,
                                                            0x00000420,
                                                            0x00000004}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     unsigned int Val_CB_FEB2_ADC1_Read_Ch3_VMon1 [4] = {   0xd0d0d0d0,
                                                            0xd0d00200,
                                                            0x00000430,
                                                            0x00000004}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     unsigned int Val_CB_FEB2_ADC1_Read_Ch4_VMon2 [4] = {   0xd0d0d0d0,
                                                            0xd0d00200,
                                                            0x00000440,
                                                            0x00000004}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     unsigned int Val_CB_FEB2_ADC2_Read_Temp      [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     unsigned int Val_CB_FEB2_ADC2_Read_Ch1_Vth1  [4] = {   0xd0d0d0d0,
                                                            0xd0d00200,
                                                            0x00000490,
                                                            0x00000004}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     unsigned int Val_CB_FEB2_ADC2_Read_Ch2_Vth2  [4] = {   0xd0d0d0d0,
                                                            0xd0d00200,
                                                            0x000004a0,
                                                            0x00000004}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     unsigned int Val_CB_FEB2_ADC2_Read_Ch3_VMon1 [4] = {   0xd0d0d0d0,
                                                            0xd0d00200,
                                                            0x000004b0,
                                                            0x00000004}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     unsigned int Val_CB_FEB2_ADC2_Read_Ch4_VMon2 [4] = {   0xd0d0d0d0,
                                                            0xd0d00200,
                                                            0x000004c0,
                                                            0x00000004}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/


     unsigned int Val_CB_FEB3_DAC1_Ch1_Set_Vth1   [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/
     unsigned int Val_CB_FEB3_DAC1_Ch2_Set_Vth2   [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/
     unsigned int Val_CB_FEB3_DAC1_Ch3_Set_Vmon1  [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/
     unsigned int Val_CB_FEB3_DAC1_Ch4_Set_Vmon2  [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/
     unsigned int Val_CB_FEB3_DAC1_ON             [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/
     unsigned int Val_CB_FEB3_DAC2_Ch1_Set_Vth1   [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/
     unsigned int Val_CB_FEB3_DAC2_Ch2_Set_Vth2   [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/
     unsigned int Val_CB_FEB3_DAC2_Ch3_Set_Vmon1  [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/
     unsigned int Val_CB_FEB3_DAC2_Ch4_Set_Vmon2  [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/
     unsigned int Val_CB_FEB3_DAC2_ON             [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/

     unsigned int Val_CB_FEB3_ADC1_Read_Temp      [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/
     unsigned int Val_CB_FEB3_ADC1_Read_Ch1_Vth1  [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/
     unsigned int Val_CB_FEB3_ADC1_Read_Ch2_Vth2  [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/
     unsigned int Val_CB_FEB3_ADC1_Read_Ch3_VMon1 [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/
     unsigned int Val_CB_FEB3_ADC1_Read_Ch4_VMon2 [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/
     unsigned int Val_CB_FEB3_ADC2_Read_Temp      [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/
     unsigned int Val_CB_FEB3_ADC2_Read_Ch1_Vth1  [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/
     unsigned int Val_CB_FEB3_ADC2_Read_Ch2_Vth2  [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/
     unsigned int Val_CB_FEB3_ADC2_Read_Ch3_VMon1 [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/
     unsigned int Val_CB_FEB3_ADC2_Read_Ch4_VMon2 [4] = {}; /*"10101010100110011000100001110111011001100101010101000100001100110010001000010001";*/


     //D0 D0 D0 D0 D0 D0 03 00 00 00 00 00 00 00 00 04
     unsigned int Val_CB_Turn_ON_LB [4] =  {0xD0D0D0D0,
                                            0xD0D00600,
                                            0x00000000,
                                            0x00000004};
                                            /*"11010000"
                                            "11010000"
                                            "11010000"
                                            "11010000"
                                            "11010000"
                                            "11010000"
                                            "00000011" //03
                                            "00000000" //00
                                            "00000000" //00
                                            "00000000" //00
                                            "00000000" //00
                                            "00000000" //00
                                            "00000000" //00
                                             "00000000" //00
                                            "00000000" //00
                                            "00000100";//04 */


     //=====================================================

     unsigned int ChBx_CB_FEB1_DAC1_Ch1_Vth1_Value = 0 ;

    //=====================================================
     unsigned int Current_Frame [4] = {} ; /*"11010000110100001101000011010000110100001101000000000001000000000000000000000000000000000100000000000000000000000000000000000100";*/


     UINT  Parameter_Counter = 0 ;
     UINT cb_value=0;
     UINT cb_value2 =0;
     bool cb_prog_full = false;

     unsigned int Out_frame_arr[4];
     unsigned int CB_Number = 0 ;

     bool CB_Select = false;
     unsigned int temp = 0 ;
     unsigned int CB_TestSig_Number = 0 ;

     unsigned int aw, bw, cw, dw , tw ;
     unsigned int w[4] = {};
     unsigned char i = 0 ;


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

signals:
      void CB_respond_send(const UINT CB_Parameter_Counter) ;// ,const boolean Buffer_full );

private:
    void run() override;

    QMutex cb_mutex;
    QWaitCondition cb_cond;
    bool cb_quit = false;
    bool ChBx_checked = false;

    UINT64 cb_fileLength = 16;
    char *cb_sendBuf;

    char    cb_buffer[RECV_PACKET_SIZE];
    UCHAR   cb_command=0;
    USHORT  cb_address=0 ;

    USHORT  cb_length=0 ;
    UCHAR   cb_packetCounter=0;

    bool    cb_disp_once = true;
    UINT64  cb_counter = 0;

    void delay (int miliseconds);


};

#endif // MYTHREAD_CB_UPDATE_H
