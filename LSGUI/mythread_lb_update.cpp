#include "mythread_lb_update.h"


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

Mythread_LB_Update::Mythread_LB_Update(QObject *parent)  :  QThread(parent)
{

}



//==========================================================================
//          Function :
//
//==========================================================================


Mythread_LB_Update::~Mythread_LB_Update(){

    lb_mutex.lock();
    lb_quit = true;
    lb_mutex.unlock();
    wait();
}


//==========================================================================
//          Function :
//
//==========================================================================

void Mythread_LB_Update::LB_transaction(void){

    const QMutexLocker locker(&lb_mutex);

    if (!isRunning())
    {
        start(QThread::NormalPriority);
        lb_quit = false;

        qDebug() << "\n\n\n >> 1- LB Thread: Start" ;
    }
    else
    {
        lb_cond.wakeOne();
        qDebug() << "\n\n\n >> 2- LB Thread: is ongoing" ;
    }

}


//==========================================================================
//          Function :
//
//==========================================================================
void Mythread_LB_Update::run(){

    //==================================
    Read_Current_Frame();
    //==================================

    if ( (ChBx_checked)&&(!lb_prog_full) ){

        lb_fileLength = 16; // 10
        //--------------------------------------------------------
        lb_sendBuf = (char*)malloc(lb_fileLength); // char *sendBuf;
        memset(lb_sendBuf, 0, lb_fileLength);
        //--------------------------------------------------------

        unsigned char test_char;

        for (int i = 0 , j=0 ; i < 4 ; i++ )
        {
            lb_sendBuf[j]   = Out_frame_arr[i] >> 24;
            //test_char = lb_sendBuf[j] ;
            //qDebug() << " J = " << j << " lb_sendBuf[j] = " << QString("0x%1").arg(test_char, 0, 16) ;

            lb_sendBuf[j+1] = Out_frame_arr[i] >> 16;
            //test_char = lb_sendBuf[j+1] ;
            //qDebug() << " J = " << j+1 << " lb_sendBuf[j] = " << QString("0x%1").arg(test_char, 0, 16) ;

            lb_sendBuf[j+2] = Out_frame_arr[i] >> 8;
            //test_char = lb_sendBuf[j+2] ;
            //qDebug() << " J = " << j+2 << " lb_sendBuf[j] = " << QString("0x%1").arg(test_char, 0, 16) ;

            lb_sendBuf[j+3] = Out_frame_arr[i];
            //test_char = lb_sendBuf[j+3] ;
            //qDebug() << " J = " << j+3 << " lb_sendBuf[j] = " << QString("0x%1").arg(test_char, 0, 16) ;

            j+=4;
        }

        //qDebug() << "---------------------------------------------" ;

        //---------------------------------------------------------
        LB_WriteConfig(0x00, 0x01u);   // Prepare Ethernt for Send packets
        //---------------------------------------------------------

        //---------------------------------------------------------
        lb_retVal = YE_TCP_SendMem(lb_sendBuf, lb_fileLength);

        if (!lb_retVal)
        {
            if (lb_sendBuf != NULL)
            free(lb_sendBuf);
            return;
        }
        else
        {
            //lb_sentSize += lb_fileLength;
        }
        //---------------------------------------------------------
    }

//--------------------------------------------------------
qDebug() << "12- lb_readRegFBCommand--------- =" << readRegFBCommand;
emit LB_respond_send(Parameter_Counter);

}

//==========================================================================
//          Function :
//
//==========================================================================
void Mythread_LB_Update::LB_WriteConfig(UCHAR lb_address, UINT lb_value){


    lb_retVal = YE_TCP_WriteConfig(lb_address, lb_value);

    if (!lb_retVal)
    {
        //str += QString("%1 %2\n").arg("Error in Write Config").arg(GetLastWSAError());
        //ui->textEdit->append(str);
    }


}





//==========================================================================
//          Function :
//
//==========================================================================
void Mythread_LB_Update::Read_Current_Frame (void){

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
        case Cmd_LB1_1V :
            if (ChBx_LB1_1V){
                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_1V[j];
                }

                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"
                }

              ChBx_checked = true;
             }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();
            break;
        //-------------------------------------
        case Cmd_LB1_1V8_Aux :
            if (ChBx_LB1_1V8_Aux){
                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_1V8_Aux[j];
                }

                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }

              ChBx_checked = true;
              }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();
            break;
        //-------------------------------------
        case Cmd_LB1_1V_MGTAVCC :
            if (ChBx_LB1_1V_MGTAVCC){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_1V_MGTAVCC[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }

              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();
            break;
        //-------------------------------------
        case Cmd_LB1_1V_MGTAVTT :
            if (ChBx_LB1_1V_MGTAVTT){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_1V_MGTAVTT[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }


              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();
            break;
        //-------------------------------------
        case Cmd_LB1_1V_MGTVCCAUX :
            if (ChBx_LB1_1V_MGTVCCAUX){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_1V_MGTVCCAUX[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }


              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();
            break;
        //-------------------------------------
        case Cmd_LB1_1V5 :
            if (ChBx_LB1_1V5){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_1V5[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }


              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();
            break;
        //-------------------------------------
        case Cmd_LB1_1V8 :
            if (ChBx_LB1_1V8){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_1V8[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }

              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();
            break;
        //-------------------------------------
        case Cmd_LB1_2V5 :
            if (ChBx_LB1_2V5){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_2V5[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }

              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();
            break;
        //-------------------------------------
        case Cmd_LB1_3V3 :
            if (ChBx_LB1_3V3){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_3V3[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }

              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();
            break;
        //-------------------------------------
        case Cmd_LB1_3V3VDD :
            if (ChBx_LB1_3V3VDD){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_3V3VDD[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }


              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();

            break;
        //-------------------------------------
        case Cmd_LB1_CS1_Vout :
            if (ChBx_LB1_CS1_Vout){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_CS1_Vout[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }

              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();
            break;
        //-------------------------------------
        case Cmd_LB1_CS2_Vout :
            if (ChBx_LB1_CS2_Vout){
                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_CS2_Vout[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }


              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();

            break;
        //-------------------------------------
        case Cmd_LB1_CS3_Vout :
            if (ChBx_LB1_CS3_Vout){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_CS3_Vout[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }

              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();

            break;
        //-------------------------------------



        //-------------------------------------

        //-------------------------------------
        case Cmd_LB1_Temp_Sensor1 :
            if (ChBx_LB1_Temp_Sensor1){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_Temp_Sensor1[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }


              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();

            break;
        //-------------------------------------

        case Cmd_LB1_Temp_Sensor2 :
            if (ChBx_LB1_Temp_Sensor2){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_Temp_Sensor2[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }

              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();

            break;
        //-------------------------------------
        case Cmd_LB1_Temp_Sensor3 :
            if (ChBx_LB1_Temp_Sensor3){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_Temp_Sensor3[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }

              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();

            break;
        //-------------------------------------
        case Cmd_LB1_ADC_TEMP :
            if (ChBx_LB1_ADC_TEMP){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_ADC_TEMP[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }

              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();

            break;
        //-------------------------------------
        case Cmd_LB1_ADC_AVDD_2 :
            if (ChBx_LB1_ADC_AVDD_2){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_ADC_AVDD_2[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }

              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();

            break;
        //-------------------------------------
        case Cmd_LB1_ADC_GND :
            if (ChBx_LB1_ADC_GND){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_ADC_GND[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }



              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();

            break;
        //-------------------------------------
        case Cmd_LB1_FPGA_VCORE :
            if (ChBx_LB1_FPGA_VCORE){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_FPGA_VCORE[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }


              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();

            break;
        //-------------------------------------
        case Cmd_LB1_FPGA_VCCBRAM :
            if (ChBx_LB1_FPGA_VCCBRAM){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_FPGA_VCCBRAM[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }

              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();

            break;
        //-------------------------------------
        case Cmd_LB1_FPGA_VCCAUX :
            if (ChBx_LB1_FPGA_VCCAUX){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_FPGA_VCCAUX[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }


              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();

            break;
        //-------------------------------------
        case Cmd_LB1_FPGA_Temp :
            if (ChBx_LB1_FPGA_Temp){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_FPGA_Temp[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }


              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();

            break;
        //-------------------------------------
        case Cmd_LB1_ID_Number :
            if (ChBx_LB1_ID_Number){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_ID_Number[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }


              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();

            break;
        //-------------------------------------
        case Cmd_LB1_SEM_Counter :
            if (ChBx_LB1_SEM_Counter){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_SEM_Counter[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }


              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();

            break;
        //-------------------------------------

        //-------------------------------------
        case Cmd_LB1_ReadMultiChCnts :
            if (ChBx_LB1_ReadMultiChCnts){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_ReadMultiChCnts[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                }

              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();

            break;
        //-------------------------------------

        //-------------------------------------
        case Cmd_LB1_TimingProfile :
            if (ChBx_LB1_TimingProfile){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_TimingProfile[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 3-bit field in a frame
                    //Selective 3-bit Masking needs 0b00000111 (0x07)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111110001111111111111"
                    //Selective 3-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111110011111111111111"

                }

              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();

            break;
        //-------------------------------------

        //-------------------------------------
        case Cmd_LB1_RpcRowData :
            if (ChBx_LB1_RpcRowData){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_RpcRowData[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 3-bit field in a frame
                    //Selective 3-bit Masking needs 0b00000111 (0x07)
                    Out_frame_arr[2] &= ~(0x07 << 13);      // "0b11111111111111110001111111111111"
                    //Selective 3-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111110011111111111111"

                }
              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();

            break;
        //-------------------------------------


        //-------------------------------------
        case Cmd_LB1_SelectTestSig :
            if (ChBx_LB1_SelectTestSig){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_SelectTestSig[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x0F << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                    Out_frame_arr[2] &= ~(0x0F << 4);
                    Out_frame_arr[2] |= (LB1_TestSig_Number << 4);

                }

              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();

            break;
        //-------------------------------------

        //-------------------------------------
        case Cmd_LB1_ClockDeskew :
            if (ChBx_LB1_ClockDeskew){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_ClockDeskew[j];
                }
                if (LB1_Select){
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x0F << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"

                    Out_frame_arr[2] &= ~(0x3FF << 2);  // 10-bit number Shoud be check
                    Out_frame_arr[2] |= (LB1_ClockDeskew_Value << 2);

                }

              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();

            break;
        //-------------------------------------

        //-------------------------------------
        case Cmd_LB1_FullWin :
            if (ChBx_LB1_FullWin){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_FullWin[j];
                }
                if (LB1_Select){
                    //---------------------------------
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x0F << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"
                    //---------------------------------
                    LB_DiagInstCode = 3 ;
                    Out_frame_arr[2] |= (LB_DiagInstCode << 9);
                    //---------------------------------
                    LB1_FullWin_value &= 0x0F; // Full Window = 0 - 15 (4-bit)

                    Out_frame_arr[2] &= ~(0xF << 5);
                    Out_frame_arr[2] |= (LB1_FullWin_value << 5);
                    //----------------------------------
                    if (ChBx_LB1_AdjWin){
                        LB1_AdjWin_value &= 0x0F; // Full Window = 0 - 15 (4-bit)

                        Out_frame_arr[2] &= ~(0x0F << 1);
                        Out_frame_arr[2] |= (LB1_AdjWin_value << 1);
                    }
                    //----------------------------------
                }

              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();

            break;
        //-------------------------------------


        //-------------------------------------
        case Cmd_LB1_AdjWin :
            if (ChBx_LB1_AdjWin){

                for (int j=0;j<4;j++){

                   Out_frame_arr[j] =  Val_LB_AdjWin[j];
                }
                if (LB1_Select){
                    //---------------------------------
                    LB_Number = 1;
                    //Link board number is 4-bit field in a frame
                    //Selective 4-bit Masking needs 0b00001111 (0x0F)
                    Out_frame_arr[2] &= ~(0x0F << 13);      // "0b11111111111111100001111111111111"
                    //Selective 4-bit LB_Number Insertion
                    Out_frame_arr[2] |= (LB_Number << 13);  // "0b11111111111111100011111111111111"
                    //---------------------------------
                    LB_DiagInstCode = 3 ;
                    Out_frame_arr[2] |= (LB_DiagInstCode << 9);
                    //---------------------------------
                    LB1_AdjWin_value &= 0x0F; // Full Window = 0 - 15 (4-bit)

                    Out_frame_arr[2] &= ~(0x0F << 1);
                    Out_frame_arr[2] |= (LB1_AdjWin_value << 1);
                    //---------------------------------
                    if (ChBx_LB1_FullWin){
                        LB1_FullWin_value &= 0x0F; // Full Window = 0 - 15 (4-bit)

                        Out_frame_arr[2] &= ~(0xF << 5);
                        Out_frame_arr[2] |= (LB1_FullWin_value << 5);
                    }
                    //----------------------------------

                }

              ChBx_checked = true;
            }
            lb_mutex.lock();
              Parameter_Counter++;
            lb_mutex.unlock();

            break;
        //-------------------------------------


        //====================================================================

            default:
            //l_quit = true;
            lb_quit = true; //<----- Notice
            ChBx_checked = true;
            break;
            }
        //return Out_frame_arr;
    }
