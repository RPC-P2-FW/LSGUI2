#include "mythread_be_update.h"
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
mythread_be_update::mythread_be_update(QObject *parent) : QThread(parent)
{

}

//==========================================================================
//          Function :
//
//==========================================================================
mythread_be_update::~mythread_be_update(){

    be_mutex.lock();
    be_quit = true;
    be_mutex.unlock();
    wait();
}


//==========================================================================
//          Function :
//
//==========================================================================

void mythread_be_update::BE_transaction(void){

    const QMutexLocker locker(&be_mutex);

    if (!isRunning())
    {
        start(QThread::NormalPriority);
        be_quit = false;

        qDebug() << "\n\n\n >> 1- BE Thread: Start" ;
    }
    else
    {
        be_cond.wakeOne();
        qDebug() << "\n\n\n >> 2- BE Thread: is ongoing" ;
    }

}

//==========================================================================
//          Function :
//
//==========================================================================
void mythread_be_update::run(){

    //==================================
    //Read_Current_Frame();
    //==================================

    if ( (ChBx_checked)&&(!be_prog_full) ){

        be_fileLength = 16; // 10
        //--------------------------------------------------------
        be_sendBuf = (char*)malloc(be_fileLength); // char *sendBuf;
        memset(be_sendBuf, 0, be_fileLength);
        //--------------------------------------------------------

        unsigned char test_char;

        for (int i = 0 , j=0 ; i < 4 ; i++ )
        {
            be_sendBuf[j]   = Out_frame_arr[i] >> 24;
            //test_char = lb_sendBuf[j] ;
            //qDebug() << " J = " << j << " lb_sendBuf[j] = " << QString("0x%1").arg(test_char, 0, 16) ;

            be_sendBuf[j+1] = Out_frame_arr[i] >> 16;
            //test_char = lb_sendBuf[j+1] ;
            //qDebug() << " J = " << j+1 << " lb_sendBuf[j] = " << QString("0x%1").arg(test_char, 0, 16) ;

            be_sendBuf[j+2] = Out_frame_arr[i] >> 8;
            //test_char = lb_sendBuf[j+2] ;
            //qDebug() << " J = " << j+2 << " lb_sendBuf[j] = " << QString("0x%1").arg(test_char, 0, 16) ;

            be_sendBuf[j+3] = Out_frame_arr[i];
            //test_char = lb_sendBuf[j+3] ;
            //qDebug() << " J = " << j+3 << " lb_sendBuf[j] = " << QString("0x%1").arg(test_char, 0, 16) ;

            j+=4;
        }

        //qDebug() << "---------------------------------------------" ;

        //---------------------------------------------------------
        BE_WriteConfig(0x00, 0x01u);   // Prepare Ethernt for Send packets
        //---------------------------------------------------------

        //---------------------------------------------------------
        be_retVal = YE_TCP_SendMem(be_sendBuf, be_fileLength);

        if (!be_retVal)
        {
            if (be_sendBuf != NULL)
            free(be_sendBuf);
            return;
        }
        else
        {
            //lb_sentSize += lb_fileLength;
        }
        //---------------------------------------------------------
    }

//--------------------------------------------------------
qDebug() << "12- BE_readRegFBCommand--------- =" << readRegFBCommand;
emit BE_respond_send(Parameter_Counter);

}

//==========================================================================
//          Function :
//
//==========================================================================
void mythread_be_update::BE_WriteConfig(UCHAR be_address, UINT be_value){

    be_retVal = YE_TCP_WriteConfig(be_address, be_value);

    if (!be_retVal)
    {
        //str += QString("%1 %2\n").arg("Error in Write Config").arg(GetLastWSAError());
        //ui->textEdit->append(str);
    }
}
