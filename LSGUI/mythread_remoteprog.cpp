
#include "mythread_remoteprog.h"
#include "mainwindow.h"
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

Mythread_RemoteProg::Mythread_RemoteProg(QObject *parent)
    : QThread(parent)
{

}
//==========================================================================
//          Function :
//
//==========================================================================


Mythread_RemoteProg::~Mythread_RemoteProg(){

    rp_mutex.lock();
    rp_quit = true;
    rp_mutex.unlock();
    wait();
}

//==========================================================================
//          Function :
//
//==========================================================================

void Mythread_RemoteProg::RP_transaction(void){

    const QMutexLocker locker(&rp_mutex);
    if (!isRunning()){

        start(QThread::HighPriority);
    }
    else
    {
        rp_cond.wakeOne();
    }

}
//==========================================================================
//          Function :
//
//==========================================================================
void Mythread_RemoteProg::run(){


/*
    rp_mutex.lock();
    if (rp_buf_ready){
        rp_remainLength = rp_fileLength - rp_packCnt ;
        //qDebug() << "0- rp_remainLength=" << rp_remainLength ;

        if (rp_remainLength < packet_size-7){
            packet_size = rp_remainLength+7;
        }


        rp_sendmem[0] = 0x0d;
        rp_sendmem[1] = 0x0d;
        rp_sendmem[2] = 0x0d;
        rp_sendmem[3] = 0x0d;
        rp_sendmem[4] = 0x0d;
        rp_sendmem[5] = 0x0d;
        rp_sendmem[6] = 0x04; // Remote Programmig Code

        for (UINT32 i = 0 ; i < packet_size-7 ; i++)
        {



            rp_sendmem[i+7] = rp_sendBuf [i + rp_packCnt];

            //rp_sendmem[i] = rp_sendBuf [i + rp_packCnt];

            //qDebug() << "3- i =" << i;
            //qDebug() << "4- rp_packCnt =" << rp_packCnt;
            //qDebug() << "5- rp_sendBuf [i + rp_packCnt]; =" << rp_sendBuf [i + rp_packCnt];
            //qDebug() << "6- rp_sendmem[i] =" << rp_sendmem[i] ;
            //qDebug() << "7- Char =" << ++rp_cnt;
            //qDebug() << "-------------------------------" ;


        }

        //---------------------------------------------------------
        RP_WriteConfig(0x00, 0x01u);   // Prepare Ethernt for Send packets
        //---------------------------------------------------------

        //---------------------------------------------------------
        YE_TCP_SendMem(rp_sendmem, packet_size);
        //---------------------------------------------------------
        rp_packCnt = rp_packCnt +  packet_size - 7 ;
        //rp_cnt++;
        rp_remainLength = rp_fileLength - rp_packCnt ;

    }rp_mutex.unlock();
    emit RemoteProgRespondSend(rp_packCnt);
    */




//unsigned int const cmdOverhrad = 7 ;

rp_mutex.lock();
if (rp_buf_ready){
    rp_remainLength = rp_fileLength - rp_packCnt ;
    //qDebug() << "0- rp_remainLength=" << rp_remainLength ;

    if (rp_remainLength < packet_size - cmdOverhrad){
        packet_size = rp_remainLength + cmdOverhrad;
    }


    //rp_sendmem[0] = 0x0d;
    //rp_sendmem[1] = 0x0d;
    //rp_sendmem[2] = 0x0d;
    //rp_sendmem[3] = 0x0d;
    //rp_sendmem[4] = 0x0d;
    //rp_sendmem[5] = 0x0d;
    //rp_sendmem[6] = 0x04; // Remote Programmig Code

    for (UINT32 i = 0 ; i < packet_size-cmdOverhrad ; i++)
    {



        rp_sendmem[i+cmdOverhrad] = rp_sendBuf [i + rp_packCnt];

        //rp_sendmem[i] = rp_sendBuf [i + rp_packCnt];

        //qDebug() << "3- i =" << i;
        //qDebug() << "4- rp_packCnt =" << rp_packCnt;
        //qDebug() << "5- rp_sendBuf [i + rp_packCnt]; =" << rp_sendBuf [i + rp_packCnt];
        //qDebug() << "6- rp_sendmem[i] =" << rp_sendmem[i] ;
        //qDebug() << "7- Char =" << ++rp_cnt;
        //qDebug() << "-------------------------------" ;


    }

    //---------------------------------------------------------
    RP_WriteConfig(0x00, 0x01u);   // Prepare Ethernt for Send packets
    //---------------------------------------------------------

    //---------------------------------------------------------
    YE_TCP_SendMem(rp_sendmem, packet_size);
    //---------------------------------------------------------
    rp_packCnt = rp_packCnt +  packet_size - cmdOverhrad ;
    //rp_cnt++;
    rp_remainLength = rp_fileLength - rp_packCnt ;

}rp_mutex.unlock();
emit RemoteProgRespondSend(rp_packCnt);


}

//==========================================================================
//          Function :
//
//==========================================================================
void Mythread_RemoteProg::RP_WriteConfig(UCHAR rp_address, UINT rp_value){

    rp_retVal = YE_TCP_WriteConfig(rp_address, rp_value);

    if (!rp_retVal)
    {
        //str += QString("%1 %2\n").arg("Error in Write Config").arg(GetLastWSAError());
        //ui->textEdit->append(str);
    }


}
