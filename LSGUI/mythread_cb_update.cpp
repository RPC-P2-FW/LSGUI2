
#include "mythread_cb_update.h"
#include"mainwindow.h"
#include "mythread.h"
#include "YasinLanLib.h"
#include "sendframe.h"

#include <QMainWindow>
#include <QtCore>
#include <QDebug>
#include <QTime>
#include <QMutex>
#include <QThread>
#include <QWaitCondition>

#include <QStringView>


#include <QAbstractItemView>
#include <QApplication>
#include <QAbstractItemModel>
#include <QVarLengthArray>
#include <QCompleter>
#include <QDebug>
#include <QDir>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QFrame>
#include <QFont>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QKeyEvent>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QMetaEnum>
#include <QModelIndex>
#include <QTableWidgetItem>
#include <QtWidgets>
#include <QtNetwork>
#include <QtCore>
#include <QtDebug>
#include <QScreen>
#include <QScrollBar>
#include <qstring.h>
//==========================================================================
//          Function :
//
//==========================================================================

Mythread_CB_Update::Mythread_CB_Update(QObject *parent) : QThread(parent)
{

}
//==========================================================================
//          Function :
//
//==========================================================================


Mythread_CB_Update::~Mythread_CB_Update(){

    cb_mutex.lock();
    cb_quit = true;
    cb_mutex.unlock();
    wait();
}

//==========================================================================
//          Function :
//
//==========================================================================

void Mythread_CB_Update::CB_transaction(void){

    const QMutexLocker locker(&cb_mutex);

    if (!isRunning())
    {
        start(QThread::NormalPriority);
        cb_quit = false;

        //qDebug() << "\n\n\n >> 1- Thread: Start" ;
    }
    else
    {
        cb_cond.wakeOne();
        //qDebug() << "\n\n\n >> 2- Thread: is ongoing" ;
    }

}
//==========================================================================
//          Function :
//
//==========================================================================
void Mythread_CB_Update::run(){




    //==================================
    Read_Current_Frame();
    //==================================
    if ( (ChBx_checked)&&(!cb_prog_full) ){

        cb_fileLength = 16; // 10
        //--------------------------------------------------------
        cb_sendBuf = (char*)malloc(cb_fileLength); // char *sendBuf;
        memset(cb_sendBuf, 0, cb_fileLength);
        //--------------------------------------------------------


        unsigned char test_char;

        for (int i = 0 , j=0 ; i < 4 ; i++ )
        {
            cb_sendBuf[j]   = Out_frame_arr[i] >> 24;
            //test_char = cb_sendBuf[j] ;
            //qDebug() << " J = " << j << " cb_sendBuf[j] = " << QString("0x%1").arg(test_char, 0, 16) ;

            cb_sendBuf[j+1] = Out_frame_arr[i] >> 16;
            //test_char = cb_sendBuf[j+1] ;
            //qDebug() << " J = " << j+1 << " cb_sendBuf[j] = " << QString("0x%1").arg(test_char, 0, 16) ;

            cb_sendBuf[j+2] = Out_frame_arr[i] >> 8;
            //test_char = cb_sendBuf[j+2] ;
            //qDebug() << " J = " << j+2 << " cb_sendBuf[j] = " << QString("0x%1").arg(test_char, 0, 16) ;

            cb_sendBuf[j+3] = Out_frame_arr[i];
            //test_char = cb_sendBuf[j+3] ;
            //qDebug() << " J = " << j+3 << " cb_sendBuf[j] = " << QString("0x%1").arg(test_char, 0, 16) ;

            j+=4;
        }

        //qDebug() << "---------------------------------------------" ;

        //---------------------------------------------------------
        CB_WriteConfig(0x00, 0x01u);   // Prepare Ethernt for Send packets
        //---------------------------------------------------------

        //---------------------------------------------------------
        cb_retVal = YE_TCP_SendMem(cb_sendBuf, cb_fileLength);

        if (!cb_retVal)
        {
            if (cb_sendBuf != NULL)
                free(cb_sendBuf);
            return;
        }
        else
        {
            //cb_sentSize += cb_fileLength;
        }


        //qDebug() << "          ";
        //qDebug() << "SW -> HD: cb_YE_TCP_SendMem--------- =";
        delay(100);

    }

    //--------------------------------------------------------
    emit CB_respond_send(Parameter_Counter);

}

//==========================================================================
//          Function : Delay
//
//==========================================================================

void Mythread_CB_Update::delay (int miliseconds){

    QEventLoop loop ;
    QTimer t ;
    t.connect(&t,&QTimer::timeout, &loop,&QEventLoop::quit);
    t.start(miliseconds);
    loop.exec();
}

//==========================================================================
//          Function :
//
//==========================================================================
void Mythread_CB_Update::CB_WriteConfig(UCHAR cb_address, UINT cb_value){


    cb_retVal = YE_TCP_WriteConfig(cb_address, cb_value);

    if (!cb_retVal)
    {
        //str += QString("%1 %2\n").arg("Error in Write Config").arg(GetLastWSAError());
        //ui->textEdit->append(str);
        qDebug() << "Error in Write Config"<<GetLastWSAError();
    }


}

//==========================================================================
//          Function :
//
//==========================================================================
void Mythread_CB_Update::Read_Current_Frame (void){

    QString Out_frame = "11010000"
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
                        "00000000"
                        "00000000"
                        "00000000"
                        "00000000"
                        "00000100";



    //=========================================================


    ChBx_checked = false;

    switch (Parameter_Counter){
        //-------------------------------------
        case Cmd_CB_1V :
            if (ChBx_CB_1V){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_1V[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }


              ChBx_checked = true;
             }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();
            break;
        //-------------------------------------
        case Cmd_CB_1V8_Aux :
            if (ChBx_CB_1V8_Aux){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_1V8_Aux[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }

              ChBx_checked = true;
              }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();
            break;
        //-------------------------------------
        case Cmd_CB_1V_MGTAVCC :
            if (ChBx_CB_1V_MGTAVCC){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_1V_MGTAVCC[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }


              ChBx_checked = true;
            }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();
            break;
        //-------------------------------------
        case Cmd_CB_1V_MGTAVTT :
            if (ChBx_CB_1V_MGTAVTT){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_1V_MGTAVTT[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }


              ChBx_checked = true;
            }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();
            break;
        //-------------------------------------
        case Cmd_CB_1V_MGTVCCAUX :
            if (ChBx_CB_1V_MGTVCCAUX){


                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_1V_MGTVCCAUX[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }


              ChBx_checked = true;
            }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();
            break;
        //-------------------------------------
        case Cmd_CB_1V5 :
            if (ChBx_CB_1V5){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_1V5[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }


              ChBx_checked = true;
            }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();
            break;
        //-------------------------------------
        case Cmd_CB_1V8 :
            if (ChBx_CB_1V8){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_1V8[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }


              ChBx_checked = true;
            }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();
            break;
        //-------------------------------------
        case Cmd_CB_2V5 :
            if (ChBx_CB_2V5){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_2V5[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }



              ChBx_checked = true;
            }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();
            break;
        //-------------------------------------
        case Cmd_CB_3V3 :
            if (ChBx_CB_3V3){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_3V3[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }



              ChBx_checked = true;
            }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();
            break;
        //-------------------------------------
        case Cmd_CB_3V3VDD :
            if (ChBx_CB_3V3VDD){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_3V3VDD[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }



              ChBx_checked = true;
            }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();

            break;
        //-------------------------------------
        case Cmd_CB_CS1_Vout :
            if (ChBx_CB_CS1_Vout){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_CS1_Vout[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }


              ChBx_checked = true;
            }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();
            break;
        //-------------------------------------
        case Cmd_CB_CS2_Vout :
            if (ChBx_CB_CS2_Vout){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_CS2_Vout[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }

              ChBx_checked = true;
            }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();

            break;
        //-------------------------------------
        case Cmd_CB_CS3_Vout :
            if (ChBx_CB_CS3_Vout){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_CS3_Vout[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }



              ChBx_checked = true;
            }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();

            break;
        //-------------------------------------



        //-------------------------------------

        //-------------------------------------
        case Cmd_CB_Temp_Sensor1 :
            if (ChBx_CB_Temp_Sensor1){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_Temp_Sensor1[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }



              ChBx_checked = true;
            }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();

            break;
        //-------------------------------------

        case Cmd_CB_Temp_Sensor2 :
            if (ChBx_CB_Temp_Sensor2){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_Temp_Sensor2[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }



              ChBx_checked = true;
            }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();

            break;
        //-------------------------------------
        case Cmd_CB_Temp_Sensor3 :
            if (ChBx_CB_Temp_Sensor3){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_Temp_Sensor4[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }



              ChBx_checked = true;
            }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();

            break;
        //-------------------------------------
        case Cmd_CB_ADC_TEMP :
            if (ChBx_CB_ADC_TEMP){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_ADC_TEMP[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }



              ChBx_checked = true;
            }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();

            break;
        //-------------------------------------
        case Cmd_CB_ADC_AVDD_2 :
            if (ChBx_CB_ADC_AVDD_2){


                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_ADC_AVDD_2[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }


              ChBx_checked = true;
            }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();

            break;
        //-------------------------------------
        case Cmd_CB_ADC_GND :
            if (ChBx_CB_ADC_GND){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_ADC_GND[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }


              ChBx_checked = true;
            }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();

            break;
        //-------------------------------------
        case Cmd_CB_FPGA_VCORE :
            if (ChBx_CB_FPGA_VCORE){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_FPGA_VCORE[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }

              ChBx_checked = true;
            }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();

            break;
        //-------------------------------------
        case Cmd_CB_FPGA_VCCBRAM :
            if (ChBx_CB_FPGA_VCCBRAM){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_FPGA_VCCBRAM[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }


              ChBx_checked = true;
            }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();

            break;
        //-------------------------------------
        case Cmd_CB_FPGA_VCCAUX :
            if (ChBx_CB_FPGA_VCCAUX){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_FPGA_VCCAUX[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }

              ChBx_checked = true;
            }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();

            break;
        //-------------------------------------
        case Cmd_CB_FPGA_Temp :
            if (ChBx_CB_FPGA_Temp){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_FPGA_Temp[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }


              ChBx_checked = true;
            }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();

            break;
        //-------------------------------------
        case Cmd_CB_ID_Number :
            if (ChBx_CB_ID_Number){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_ID_Number[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }

              ChBx_checked = true;
            }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();

            break;
        //-------------------------------------
        case Cmd_CB_SEM_Counter :
            if (ChBx_CB_SEM_Counter){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_CB_SEM_Counter[j];
                }

                if (CB_Select){
                    CB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                }


              ChBx_checked = true;
            }
            cb_mutex.lock();
              Parameter_Counter++;
            cb_mutex.unlock();

            break;
        //-------------------------------------



        //-------------------------------------
            case Cmd_CB_FEB1_DAC1_Ch1_Set_Vth1 :
                if (ChBx_CB_FEB1_DAC1_Ch1_Set_Vth1){



                    //w[0]=  0xD0D0D0D0; << please note to the index of the array!
                    //w[1]=  0xD0D00000,
                    //w[2]=  0x00000000,
                    //w[3]=  0x00000000;

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB1_DAC1_Ch1_Set_Vth1[j];

                    }

                    aw = 0 ;
                    tw = 0 ;

                    aw = feb1_dac1_vth1_value_int << 26 ;
                    tw = feb1_dac1_vth1_value_int >> 6 ;

                    Out_frame_arr[3] |= aw;
                    Out_frame_arr[2] |= tw;
                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                    for (int j=0;j<4;j++){

                        qDebug() << QString("Out_frame_arr[%1]=  0x%2").arg(j).arg(Out_frame_arr[j], 8, 16, QChar('0'));
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB1_DAC1_Ch2_Set_Vth2 :
                if (ChBx_CB_FEB1_DAC1_Ch2_Set_Vth2){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB1_DAC1_Ch2_Set_Vth2[j];
                    }

                    aw = 0 ;
                    tw = 0 ;

                    aw = feb1_dac1_vth2_value_int << 26 ;
                    tw = feb1_dac1_vth2_value_int >> 6 ;

                    Out_frame_arr[3] |= aw;
                    Out_frame_arr[2] |= tw;

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }

                    for (int j=0;j<4;j++){

                        qDebug() << QString("Out_frame_arr[%1]=  0x%2").arg(j).arg(Out_frame_arr[j], 8, 16, QChar('0'));
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB1_DAC1_Ch3_Set_Vmon1 :
                if (ChBx_CB_FEB1_DAC1_Ch3_Set_Vmon1){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB1_DAC1_Ch3_Set_Vmon1[j];
                    }

                    aw = 0 ;
                    tw = 0 ;

                    aw = feb1_dac1_vmon1_value_int << 26 ;
                    tw = feb1_dac1_vmon1_value_int >> 6 ;

                    Out_frame_arr[3] |= aw;
                    Out_frame_arr[2] |= tw;

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }

                    for (int j=0;j<4;j++){

                        qDebug() << QString("Out_frame_arr[%1]=  0x%2").arg(j).arg(Out_frame_arr[j], 8, 16, QChar('0'));
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB1_DAC1_Ch3_Set_Vmon2 :
                if (ChBx_CB_FEB1_DAC1_Ch4_Set_Vmon2){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB1_DAC1_Ch4_Set_Vmon2[j];
                    }

                    aw = 0 ;
                    tw = 0 ;

                    aw = feb1_dac1_vmon2_value_int << 26 ;
                    tw = feb1_dac1_vmon2_value_int >> 6 ;

                    Out_frame_arr[3] |= aw;
                    Out_frame_arr[2] |= tw;

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }

                    for (int j=0;j<4;j++){

                        qDebug() << QString("Out_frame_arr[%1]=  0x%2").arg(j).arg(Out_frame_arr[j], 8, 16, QChar('0'));
                    }

                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB1_DAC1_ON :
                if (ChBx_CB_FEB1_DAC1_ON){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB1_DAC1_ON[j];
                    }


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }

                    for (int j=0;j<4;j++){

                        qDebug() << QString("Out_frame_arr[%1]=  0x%2").arg(j).arg(Out_frame_arr[j], 8, 16, QChar('0'));
                    }

                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;

        //-------------------------------------
            case Cmd_CB_FEB1_DAC2_Ch1_Set_Vth1 :
                if (ChBx_CB_FEB1_DAC2_Ch1_Set_Vth1){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB1_DAC2_Ch1_Set_Vth1[j];
                    }

                    aw = 0 ;
                    tw = 0 ;

                    aw = feb1_dac2_vth1_value_int << 26 ;
                    tw = feb1_dac2_vth1_value_int >> 6 ;

                    Out_frame_arr[3] |= aw;
                    Out_frame_arr[2] |= tw;

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }

                    for (int j=0;j<4;j++){

                        qDebug() << QString("Out_frame_arr[%1]=  0x%2").arg(j).arg(Out_frame_arr[j], 8, 16, QChar('0'));
                    }

                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB1_DAC2_Ch2_Set_Vth2 :
                if (ChBx_CB_FEB1_DAC2_Ch2_Set_Vth2){


                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB1_DAC2_Ch2_Set_Vth2[j];
                    }

                    aw = 0 ;
                    tw = 0 ;

                    aw = feb1_dac2_vth2_value_int << 26 ;
                    tw = feb1_dac2_vth2_value_int >> 6 ;

                    Out_frame_arr[3] |= aw;
                    Out_frame_arr[2] |= tw;


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }

                    for (int j=0;j<4;j++){

                        qDebug() << QString("Out_frame_arr[%1]=  0x%2").arg(j).arg(Out_frame_arr[j], 8, 16, QChar('0'));
                    }

                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB1_DAC2_Ch3_Set_Vmon1 :
                if (ChBx_CB_FEB1_DAC2_Ch3_Set_Vmon1){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB1_DAC2_Ch3_Set_Vmon1[j];
                    }

                    aw = 0 ;
                    tw = 0 ;

                    aw = feb1_dac2_vmon1_value_int << 26 ;
                    tw = feb1_dac2_vmon1_value_int >> 6 ;

                    Out_frame_arr[3] |= aw;
                    Out_frame_arr[2] |= tw;


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }



                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB1_DAC2_Ch4_Set_Vmon2 :
                if (ChBx_CB_FEB1_DAC2_Ch4_Set_Vmon2){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB1_DAC2_Ch4_Set_Vmon2[j];
                    }

                    aw = 0 ;
                    tw = 0 ;

                    aw = feb1_dac2_vmon2_value_int << 26 ;
                    tw = feb1_dac2_vmon2_value_int >> 6 ;

                    Out_frame_arr[3] |= aw;
                    Out_frame_arr[2] |= tw;

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                    ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB1_DAC2_ON :
                if (ChBx_CB_FEB1_DAC2_ON){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB1_DAC2_ON[j];
                    }


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }



                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;

        //-------------------------------------
            case Cmd_CB_FEB1_ADC1_Read_Temp :
                if (ChBx_CB_FEB1_ADC1_Read_Temp){


                    qDebug()<<"Read FEB ADC temperture";

                    unsigned int temp [4]   = {0xD0D0D0D0,
                                               0xD0D00200,
                                               0x00000000,
                                               0x00000004};

                    for (int j=0;j<4;j++){

                       //Out_frame_arr[j] =  Val_CB_FEB1_ADC1_Read_Temp[j];
                        Out_frame_arr[j] =  temp[j];
                    }


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }



                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB1_ADC1_Read_Ch1_Vth1 :
                if (ChBx_CB_FEB1_ADC1_Read_Ch1_Vth1){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB1_ADC1_Read_Ch1_Vth1[j];
                    }


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }



                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB1_ADC1_Read_Ch2_Vth2 :
                if (ChBx_CB_FEB1_ADC1_Read_Ch2_Vth2){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB1_ADC1_Read_Ch2_Vth2[j];
                    }

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }



                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB1_ADC1_Read_Ch3_VMon1 :
                if (ChBx_CB_FEB1_ADC1_Read_Ch3_VMon1){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB1_ADC1_Read_Ch3_VMon1[j];
                    }


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }



                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB1_ADC1_Read_Ch4_VMon2 :
                if (ChBx_CB_FEB1_ADC1_Read_Ch4_VMon2){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB1_ADC1_Read_Ch4_VMon2[j];
                    }

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }



                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;

        //-------------------------------------
            case Cmd_CB_FEB1_ADC2_Read_Temp :
                if (ChBx_CB_FEB1_ADC2_Read_Temp){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB1_ADC2_Read_Temp[j];
                    }

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }



                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB1_ADC2_Read_Ch1_Vth1 :
                if (ChBx_CB_FEB1_ADC2_Read_Ch1_Vth1){


                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB1_ADC2_Read_Ch1_Vth1[j];
                    }


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB1_ADC2_Read_Ch2_Vth2 :
                if (ChBx_CB_FEB1_ADC2_Read_Ch2_Vth2){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB1_ADC2_Read_Ch2_Vth2[j];
                    }


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB1_ADC2_Read_Ch3_VMon1 :
                if (ChBx_CB_FEB1_ADC2_Read_Ch3_VMon1){


                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB1_ADC2_Read_Ch3_VMon1[j];
                    }

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }

                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------

            case Cmd_CB_FEB1_ADC2_Read_Ch4_VMon2 :
                if (ChBx_CB_FEB1_ADC2_Read_Ch4_VMon2){


                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB1_ADC2_Read_Ch4_VMon2[j];
                    }

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------

        //-------------------------------------


        //-------------------------------------
            case Cmd_CB_FEB2_DAC1_Ch1_Set_Vth1 :
                if (ChBx_CB_FEB2_DAC1_Ch1_Set_Vth1){


                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB2_DAC1_Ch1_Set_Vth1[j];
                    }

                    aw = 0 ;
                    tw = 0 ;

                    aw = feb2_dac1_vth1_value_int << 26 ;
                    tw = feb2_dac1_vth1_value_int >> 6 ;

                    Out_frame_arr[3] |= aw;
                    Out_frame_arr[2] |= tw;
                    qDebug()<< "feb2_dac1_vth1_value_int= " << feb2_dac1_vth1_value_int;


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                    for (int j=0;j<4;j++){

                        qDebug() << QString("Out_frame_arr[%1]=  0x%2").arg(j).arg(Out_frame_arr[j], 8, 16, QChar('0'));
                    }

                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB2_DAC1_Ch2_Set_Vth2 :
                if (ChBx_CB_FEB2_DAC1_Ch2_Set_Vth2){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB2_DAC1_Ch2_Set_Vth2[j];
                    }

                    aw = 0 ;
                    tw = 0 ;

                    aw = feb2_dac1_vth2_value_int << 26 ;
                    tw = feb2_dac1_vth2_value_int >> 6 ;

                    Out_frame_arr[3] |= aw;
                    Out_frame_arr[2] |= tw;

                    qDebug()<< "feb2_dac1_vth2_value_int= " << feb2_dac1_vth2_value_int;

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }

                    for (int j=0;j<4;j++){

                        qDebug() << QString("Out_frame_arr[%1]=  0x%2").arg(j).arg(Out_frame_arr[j], 8, 16, QChar('0'));
                    }
                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB2_DAC1_Ch3_Set_Vmon1 :
                if (ChBx_CB_FEB2_DAC1_Ch3_Set_Vmon1){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB2_DAC1_Ch3_Set_Vmon1[j];
                    }

                    aw = 0 ;
                    tw = 0 ;

                    aw = feb2_dac1_vmon1_value_int << 26 ;
                    tw = feb2_dac1_vmon1_value_int >> 6 ;

                    Out_frame_arr[3] |= aw;
                    Out_frame_arr[2] |= tw;

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }

                    for (int j=0;j<4;j++){

                        qDebug() << QString("Out_frame_arr[%1]=  0x%2").arg(j).arg(Out_frame_arr[j], 8, 16, QChar('0'));
                    }

                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB2_DAC1_Ch3_Set_Vmon2 :
                if (ChBx_CB_FEB2_DAC1_Ch4_Set_Vmon2){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB2_DAC1_Ch4_Set_Vmon2[j];
                    }

                    aw = 0 ;
                    tw = 0 ;

                    aw = feb2_dac1_vmon2_value_int << 26 ;
                    tw = feb2_dac1_vmon2_value_int >> 6 ;

                    Out_frame_arr[3] |= aw;
                    Out_frame_arr[2] |= tw;


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }

                    for (int j=0;j<4;j++){

                        qDebug() << QString("Out_frame_arr[%1]=  0x%2").arg(j).arg(Out_frame_arr[j], 8, 16, QChar('0'));
                    }

                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB2_DAC1_ON :
                if (ChBx_CB_FEB2_DAC1_ON){


                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB2_DAC1_ON[j];
                    }

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;

        //-------------------------------------
            case Cmd_CB_FEB2_DAC2_Ch1_Set_Vth1 :
                if (ChBx_CB_FEB2_DAC2_Ch1_Set_Vth1){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB2_DAC2_Ch1_Set_Vth1[j];
                    }

                    aw = 0 ;
                    tw = 0 ;

                    aw = feb2_dac2_vth1_value_int << 26 ;
                    tw = feb2_dac2_vth1_value_int >> 6 ;

                    Out_frame_arr[3] |= aw;
                    Out_frame_arr[2] |= tw;


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }

                    for (int j=0;j<4;j++){

                        qDebug() << QString("Out_frame_arr[%1]=  0x%2").arg(j).arg(Out_frame_arr[j], 8, 16, QChar('0'));
                    }

                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB2_DAC2_Ch2_Set_Vth2 :
                if (ChBx_CB_FEB2_DAC2_Ch2_Set_Vth2){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB2_DAC2_Ch2_Set_Vth2[j];
                    }

                    aw = 0 ;
                    tw = 0 ;

                    aw = feb2_dac2_vth2_value_int << 26 ;
                    tw = feb2_dac2_vth2_value_int >> 6 ;

                    Out_frame_arr[3] |= aw;
                    Out_frame_arr[2] |= tw;

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }

                    for (int j=0;j<4;j++){

                        qDebug() << QString("Out_frame_arr[%1]=  0x%2").arg(j).arg(Out_frame_arr[j], 8, 16, QChar('0'));
                    }

                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB2_DAC2_Ch3_Set_Vmon1 :
                if (ChBx_CB_FEB2_DAC2_Ch3_Set_Vmon1){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB2_DAC2_Ch3_Set_Vmon1[j];
                    }

                    aw = 0 ;
                    tw = 0 ;

                    aw = feb2_dac2_vmon1_value_int << 26 ;
                    tw = feb2_dac2_vmon1_value_int >> 6 ;

                    Out_frame_arr[3] |= aw;
                    Out_frame_arr[2] |= tw;

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB2_DAC2_Ch4_Set_Vmon2 :
                if (ChBx_CB_FEB2_DAC2_Ch4_Set_Vmon2){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB2_DAC2_Ch4_Set_Vmon2[j];
                    }

                    aw = 0 ;
                    tw = 0 ;

                    aw = feb2_dac2_vmon2_value_int << 26 ;
                    tw = feb2_dac2_vmon2_value_int >> 6 ;

                    Out_frame_arr[3] |= aw;
                    Out_frame_arr[2] |= tw;

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB2_DAC2_ON :
                if (ChBx_CB_FEB2_DAC2_ON){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB2_DAC2_ON[j];
                    }

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;

        //-------------------------------------
            case Cmd_CB_FEB2_ADC1_Read_Temp :
                if (ChBx_CB_FEB2_ADC1_Read_Temp){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB2_ADC1_Read_Temp[j];
                    }


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB2_ADC1_Read_Ch1_Vth1 :
                if (ChBx_CB_FEB2_ADC1_Read_Ch1_Vth1){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB2_ADC1_Read_Ch1_Vth1[j];
                    }


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB2_ADC1_Read_Ch2_Vth2 :
                if (ChBx_CB_FEB2_ADC1_Read_Ch2_Vth2){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB2_ADC1_Read_Ch2_Vth2[j];
                    }


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }



                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB2_ADC1_Read_Ch3_VMon1 :
                if (ChBx_CB_FEB2_ADC1_Read_Ch3_VMon1){


                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB2_ADC1_Read_Ch3_VMon1[j];
                    }


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }



                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB2_ADC1_Read_Ch4_VMon2 :
                if (ChBx_CB_FEB2_ADC1_Read_Ch4_VMon2){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB2_ADC1_Read_Ch4_VMon2[j];
                    }

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;

        //-------------------------------------
            case Cmd_CB_FEB2_ADC2_Read_Temp :
                if (ChBx_CB_FEB2_ADC2_Read_Temp){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB2_ADC2_Read_Temp[j];
                    }

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB2_ADC2_Read_Ch1_Vth1 :
                if (ChBx_CB_FEB2_ADC2_Read_Ch1_Vth1){


                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB2_ADC2_Read_Ch1_Vth1[j];
                    }


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }



                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB2_ADC2_Read_Ch2_Vth2 :
                if (ChBx_CB_FEB2_ADC2_Read_Ch2_Vth2){


                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB2_ADC2_Read_Ch2_Vth2[j];
                    }


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }



                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB2_ADC2_Read_Ch3_VMon1 :
                if (ChBx_CB_FEB2_ADC2_Read_Ch3_VMon1){


                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB2_ADC2_Read_Ch3_VMon1[j];
                    }

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------

            case Cmd_CB_FEB2_ADC2_Read_Ch4_VMon2 :
                if (ChBx_CB_FEB2_ADC2_Read_Ch4_VMon2){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB2_ADC2_Read_Ch4_VMon2[j];
                    }


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------



        //-------------------------------------
            case Cmd_CB_FEB3_DAC1_Ch1_Set_Vth1 :
                if (ChBx_CB_FEB3_DAC1_Ch1_Set_Vth1){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB3_DAC1_Ch1_Set_Vth1[j];
                    }


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB3_DAC1_Ch2_Set_Vth2 :
                if (ChBx_CB_FEB3_DAC1_Ch2_Set_Vth2){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB3_DAC1_Ch2_Set_Vth2[j];
                    }


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB3_DAC1_Ch3_Set_Vmon1 :
                if (ChBx_CB_FEB3_DAC1_Ch3_Set_Vmon1){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB3_DAC1_Ch3_Set_Vmon1[j];
                    }


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB3_DAC1_Ch3_Set_Vmon2 :
                if (ChBx_CB_FEB3_DAC1_Ch4_Set_Vmon2){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB3_DAC1_Ch4_Set_Vmon2[j];
                    }


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB3_DAC1_ON :
                if (ChBx_CB_FEB3_DAC1_ON){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB3_DAC1_ON[j];
                    }

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;

        //-------------------------------------
            case Cmd_CB_FEB3_DAC2_Ch1_Set_Vth1 :
                if (ChBx_CB_FEB3_DAC2_Ch1_Set_Vth1){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB3_DAC2_Ch1_Set_Vth1[j];
                    }


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB3_DAC2_Ch2_Set_Vth2 :
                if (ChBx_CB_FEB3_DAC2_Ch2_Set_Vth2){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB3_DAC2_Ch2_Set_Vth2[j];
                    }

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB3_DAC2_Ch3_Set_Vmon1 :
                if (ChBx_CB_FEB3_DAC2_Ch3_Set_Vmon1){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB3_DAC2_Ch3_Set_Vmon1[j];
                    }


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB3_DAC2_Ch4_Set_Vmon2 :
                if (ChBx_CB_FEB3_DAC2_Ch4_Set_Vmon2){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB3_DAC2_Ch4_Set_Vmon2[j];
                    }


                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB3_DAC2_ON :
                if (ChBx_CB_FEB3_DAC2_ON){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB3_DAC2_ON[j];
                    }

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;

        //-------------------------------------
            case Cmd_CB_FEB3_ADC1_Read_Temp :
                if (ChBx_CB_FEB3_ADC1_Read_Temp){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB3_ADC1_Read_Temp[j];
                    }

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB3_ADC1_Read_Ch1_Vth1 :
                if (ChBx_CB_FEB3_ADC1_Read_Ch1_Vth1){


                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB3_ADC1_Read_Ch1_Vth1[j];
                    }

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB3_ADC1_Read_Ch2_Vth2 :
                if (ChBx_CB_FEB3_ADC1_Read_Ch2_Vth2){
                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB3_ADC1_Read_Ch2_Vth2[j];
                    }

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB3_ADC1_Read_Ch3_VMon1 :
                if (ChBx_CB_FEB3_ADC1_Read_Ch3_VMon1){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB3_ADC1_Read_Ch3_VMon1[j];
                    }

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB3_ADC1_Read_Ch4_VMon2 :
                if (ChBx_CB_FEB3_ADC1_Read_Ch4_VMon2){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB3_ADC1_Read_Ch4_VMon2[j];
                    }

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;

        //-------------------------------------
            case Cmd_CB_FEB3_ADC2_Read_Temp :
                if (ChBx_CB_FEB3_ADC2_Read_Temp){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB3_ADC2_Read_Temp[j];
                    }

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB3_ADC2_Read_Ch1_Vth1 :
                if (ChBx_CB_FEB3_ADC2_Read_Ch1_Vth1){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB3_ADC2_Read_Ch1_Vth1[j];
                    }

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB3_ADC2_Read_Ch2_Vth2 :
                if (ChBx_CB_FEB3_ADC2_Read_Ch2_Vth2){


                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB3_ADC2_Read_Ch2_Vth2[j];
                    }

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }


                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------
            case Cmd_CB_FEB3_ADC2_Read_Ch3_VMon1 :
                if (ChBx_CB_FEB3_ADC2_Read_Ch3_VMon1){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB3_ADC2_Read_Ch3_VMon1[j];
                    }

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }



                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;
        //-------------------------------------

            case Cmd_CB_FEB3_ADC2_Read_Ch4_VMon2 :
                if (ChBx_CB_FEB3_ADC2_Read_Ch4_VMon2){

                    for (int j=0;j<4;j++){

                       Out_frame_arr[j] =  Val_CB_FEB3_ADC2_Read_Ch4_VMon2[j];
                    }

                    //--------------------------------
                    bw = 0 ;
                    bw = db_port << 10;
                    Out_frame_arr[2] |= bw;
                    //--------------------------------

                    if (CB_Select){
                        CB_Number = 1;
                        //Link board number is 4-bit field in a frame
                        //Selective 4-bit Masking needs 0b00001111 (0x0F)
                        Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                        //Selective 4-bit LB_Number Insertion
                        Out_frame_arr[2] |= (CB_Number << 13);  // "0b11111111111111100011111111111111"
                    }

                  ChBx_checked = true;
                }
                cb_mutex.lock();
                  Parameter_Counter++;
                cb_mutex.unlock();

                break;


                //-------------------------------------

            case Cmd_CB_Turn_ON_LinkBoard :

               if (ChBx_CB_Cmd_Turn_ON_LBBX){

                    for (int j=0;j<4;j++){

                        Out_frame_arr[j] =  Val_CB_Turn_ON_LB[j];
                    }

                    //w[0]=  0xD0D0D0D0; << please note to the index of the array!
                    //w[1]=  0xD0D00000,
                    //w[2]=  0x00000000,
                    //w[3]=  0x00000000;
                    //--------------------------------
                    aw = 0 ;
                    bw = 0 ;

                    if (ChBx_CB_Cmd_Turn_ON_LB1 == true){

                        aw = 1 ;
                        bw |= aw << 5 ;

                    }else{
                        aw = ~(0x01<<5) ;
                        bw &= aw ;
                    }

                    if (ChBx_CB_Cmd_Turn_ON_LB2 == true){

                        aw = 1 ;
                        bw |= aw << 6 ;

                    }else{
                        aw = ~(0x01<<6) ;
                        bw &= aw ;
                    }

                    if (ChBx_CB_Cmd_Turn_ON_LB3 == true){

                        aw = 1 ;
                        bw |= aw << 7 ;

                    }else{
                        aw = ~(0x01<<7) ;
                        bw &= aw ;
                    }


                    if (ChBx_CB_Cmd_Turn_ON_LB4 == true){

                        aw = 1 ;
                        bw |= aw << 8 ;

                    }else{
                        aw = ~(0x01<<8) ;
                        bw &= aw ;
                    }


                    if (ChBx_CB_Cmd_Turn_ON_LB5 == true){

                        aw = 1 ;
                        bw |= aw << 9 ;

                    }else{
                        aw = ~(0x01<<9) ;
                        bw &= aw ;
                    }

                    if (ChBx_CB_Cmd_Turn_ON_LB6 == true){

                        aw = 1 ;
                        bw |= aw << 10 ;

                    }else{
                        aw = ~(0x01<<10) ;
                        bw &= aw ;
                    }


                    if (ChBx_CB_Cmd_Turn_ON_LB7 == true){

                        aw = 1 ;
                        bw |= aw << 11 ;

                    }else{
                        aw = ~(0x01<<11) ;
                        bw &= aw ;
                    }

                    if (ChBx_CB_Cmd_Turn_ON_LB8 == true){

                        aw = 1 ;
                        bw |= aw << 12 ;

                    }else{
                        aw = ~(0x01<<12) ;
                        bw &= aw ;
                    }


                    if (ChBx_CB_Cmd_Turn_ON_LB9 == true){

                        aw = 1 ;
                        bw |= aw << 13 ;

                    }else{
                        aw = ~(0x01<<13) ;
                        bw &= aw ;
                    }

                    Out_frame_arr[3] |= bw;

                    qDebug() <<  "g-bw =" << QString("bw = 0x%1").arg(bw, 0, 2) ;
                    //--------------------------------


                    ChBx_checked = true;
               }

                cb_mutex.lock();
                Parameter_Counter++;
                cb_mutex.unlock();

                break;

        //-------------------------------------

        //-------------------------------------


        default:
        //l_quit = true;
        cb_quit = true; //<----- Notice
        ChBx_checked = true;
        break;
        }

}
