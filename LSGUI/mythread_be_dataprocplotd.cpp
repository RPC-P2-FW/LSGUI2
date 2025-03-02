#include "mythread_be_dataprocplotd.h"

#include"mainwindow.h"
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



Mythread_BE_DataProcPlotD::Mythread_BE_DataProcPlotD(QObject *parent) : QThread (parent)
{

}




//==========================================================================
//          Function :
//
//==========================================================================
Mythread_BE_DataProcPlotD::~Mythread_BE_DataProcPlotD(){

    be_dpcPlotD_mutex.lock();
    be_dpcPlotD_quit = true;
    be_dpcPlotD_mutex.unlock();
    wait();
}


//==========================================================================
//          Function :
//
//==========================================================================

void Mythread_BE_DataProcPlotD::BE_dataProcessPlotD_transaction(void){

    const QMutexLocker locker(&be_dpcPlotD_mutex);

    if (!isRunning())
    {
        start(QThread::HighPriority);
        be_dpcPlotD_quit = false;

        //qDebug() << "\n\n\n >> 1- BE Data Processing Thread: Start" ;
    }
    else
    {
        be_dpcPlotD_cond.wakeOne();
        //qDebug() << "\n\n\n >> 2- BE Data Processing Thread: is ongoing" ;
    }

}



//==========================================================================
//          Function :
//
//==========================================================================

void Mythread_BE_DataProcPlotD::run(){




    findex = 0 ;
    frameCnt = 0 ;
    //unsigned int  packet_cnt_PlotD2 = 0;

    for (findex = 0 ; findex<=117 ; findex=findex+3){

        //qDebug() << "1- findex : " << QString("%1").arg(findex, 0, 10);
        //qDebug() << "2- frameCnt : " << QString("%1").arg(frameCnt, 0, 10);
        //qDebug() << "3- packet_cnt_PlotD : " << QString("%1").arg(packet_cnt_PlotD, 0, 10);

        //------------------------------------------------------------------------------
        //Field1 =   Rec_Reply_PlotD[findex+0][packet_cnt_PlotD];
        //qDebug() << "4- 32-bit BE code(1) : " << QString("0x%1").arg(Field1, 0, 16);
        //------------------------------------------------------------------------------
        Field1 =   Rec_Reply_PlotD[findex+0][packet_cnt_PlotD];
        Field1 = Field1 >> 26 ;
        //qDebug() << "4- CommadType : " << QString("0x%1").arg(Field1, 0, 16);
        //------------------------------------------------------------------------------
        if (Field1 == 15){

            Field1 =   Rec_Reply_PlotD[findex+0][packet_cnt_PlotD];
            Field1 = Field1 << 6 ;
            hit1_stripNum[frameCnt] = Field1 >> 25 ;
            //qDebug() << "1- Hit-1 Strip No : " << QString("%1").arg(hit1_stripNum[frameCnt][packet_cnt_PlotD], 0, 10);
            ////qDebug() << "5- Hit-1 Strip No : " << hit1_stripNum[frameCnt][packet_cnt_PlotD];

            //Field1 =   Rec_Reply_PlotD[findex+0][packet_cnt_PlotD];
            //Field1 = Field1 << 13 ;
            //hit1_subBX[frameCnt][packet_cnt_PlotD2] = Field1 >> 28 ;
            //qDebug() << "2- Hit-1 Sub-BX : " << QString("%1").arg(hit1_subBX[frameCnt][packet_cnt_PlotD], 0, 10);
            //------------------------------------------------------------------------------
            Field1 =   Rec_Reply_PlotD[findex+0][packet_cnt_PlotD];
            Field1 = Field1 << 17 ;
            hit2_stripNum[frameCnt] = Field1 >> 25 ;
            //qDebug() << "3- Hit-2 Strip No : " << QString("%1").arg(hit2_stripNum[frameCnt][packet_cnt_PlotD], 0, 10);

            //Field1 =   Rec_Reply_PlotD[findex+0][packet_cnt_PlotD];
            //Field1 = Field1 << 24 ;
            //hit2_subBX[frameCnt][packet_cnt_PlotD2] = Field1 >> 28 ;
            //qDebug() << "4- Hit-2 Sub-BX : " << QString("%1").arg(hit2_subBX[frameCnt][packet_cnt_PlotD], 0, 10);
            //qDebug() << "" ;
            //------------------------------------------------------------------------------
            //Field1 =   Rec_Reply_PlotD[findex+0][packet_cnt_PlotD];
            //qDebug() << "5- Field(1) : " << QString("0x%1").arg(Field1, 0, 16);
            //Field2 =   Rec_Reply_PlotD[findex+1][packet_cnt_PlotD];
            //qDebug() << "6- Field(2) : " << QString("0x%1").arg(Field2, 0, 16);
            //------------------------------------------------------------------------------
            Field1 =   Rec_Reply_PlotD[findex+0][packet_cnt_PlotD];
            Field1 = Field1 << 28 ;
            hit3_stripNum[frameCnt] = Field1 >> 25 ;
            //qDebug() << "7- Hit-3 Strip No (4-bit): " << QString("%1").arg(hit3_stripNum[frameCnt][packet_cnt_PlotD], 0, 10);

            Field2 =   Rec_Reply_PlotD[findex+1][packet_cnt_PlotD];
            //qDebug() << "6- Field(2) : " << QString("0x%1").arg(Field2, 0, 16);
            Field2 = Field2 >> 29 ;
            hit3_stripNum[frameCnt] = hit3_stripNum[frameCnt] | Field2 ;
            //qDebug() << "8- Hit-3 Strip No (7-bit): " << QString("%1").arg(hit3_stripNum[frameCnt][packet_cnt_PlotD], 0, 10);
            //------------------------------------------------------------------------------
            //Field2 =   Rec_Reply_PlotD[findex+1][packet_cnt_PlotD];
            //Field2 = Field2 << 3 ;
            //hit3_subBX[frameCnt][packet_cnt_PlotD2] = Field2 >> 28 ;
            //qDebug() << "9- Hit-3 Sub-BX : " << QString("%1").arg(hit3_subBX[frameCnt][packet_cnt_PlotD], 0, 10);
            //qDebug() << "" ;
            //------------------------------------------------------------------------------
            //Field1 =   Rec_Reply_PlotD[findex+0][packet_cnt_PlotD];
            //qDebug() << "10- Field(1) : " << QString("0x%1").arg(Field1, 0, 16);
            //Field2 =   Rec_Reply_PlotD[findex+1][packet_cnt_PlotD];
            //qDebug() << "11- Field(2) : " << QString("0x%1").arg(Field2, 0, 16);
            //------------------------------------------------------------------------------
            Field2 =   Rec_Reply_PlotD[findex+1][packet_cnt_PlotD];
            Field2 = Field2 << 7 ;
            hit4_stripNum [frameCnt]= Field2 >> 25 ;
            //qDebug() << "12- Hit-4 Strip No : " << QString("%1").arg(hit4_stripNum[frameCnt][packet_cnt_PlotD], 0, 10);
            //------------------------------------------------------------------------------
            //Field2 =   Rec_Reply_PlotD[findex+1][packet_cnt_PlotD];
            //Field2 = Field2 << 14 ;
            //hit4_subBX [frameCnt][packet_cnt_PlotD2]= Field2 >> 28 ;
            //qDebug() << "13- Hit-4 Sub-BX : " << QString("%1").arg(hit4_subBX[frameCnt][packet_cnt_PlotD], 0, 10);
            //qDebug() << "" ;
            //------------------------------------------------------------------------------
            Field2 =   Rec_Reply_PlotD[findex+1][packet_cnt_PlotD];
            Field2 = Field2 << 18 ;
            hit5_stripNum[frameCnt] = Field2 >> 25 ;
            //qDebug() << "14- Hit-5 Strip No : " << QString("%1").arg(hit5_stripNum[frameCnt][packet_cnt_PlotD], 0, 10);
            //------------------------------------------------------------------------------
            //Field2 =   Rec_Reply_PlotD[findex+1][packet_cnt_PlotD];
            //Field2 = Field2 << 25 ;
            //hit5_subBX[frameCnt][packet_cnt_PlotD2] = Field2 >> 28 ;
            //qDebug() << "15- Hit-5 Sub-BX : " << QString("%1").arg(hit5_subBX[frameCnt][packet_cnt_PlotD], 0, 10);
            //qDebug() << "" ;
            //------------------------------------------------------------------------------
            //Field2 =   Rec_Reply_PlotD[findex+1][packet_cnt_PlotD];
            //qDebug() << "16- Field(2) : " << QString("0x%1").arg(Field2, 0, 16);
            //Field3 =   Rec_Reply_PlotD[findex+2][packet_cnt_PlotD];
            //qDebug() << "17- Field(3) : " << QString("0x%1").arg(Field3, 0, 16);
            //------------------------------------------------------------------------------
            Field2 =   Rec_Reply_PlotD[findex+1][packet_cnt_PlotD];
            Field2 = Field2 << 29 ;
            hit6_stripNum[frameCnt] = Field2 >> 25 ;
            //qDebug() << "18- Hit-3 Strip No (3-bit): " << QString("%1").arg(hit6_stripNum[frameCnt][packet_cnt_PlotD], 0, 10);

            Field3 =   Rec_Reply_PlotD[findex+2][packet_cnt_PlotD];
            //qDebug() << "17- Field(3) : " << QString("0x%1").arg(Field3, 0, 16);
            Field3 = Field3 >> 28 ;
            hit6_stripNum[frameCnt] = hit6_stripNum[frameCnt] | Field3 ;
            //qDebug() << "19- Hit-3 Strip No (7-bit): " << QString("%1").arg(hit6_stripNum[frameCnt][packet_cnt_PlotD], 0, 10);
            //------------------------------------------------------------------------------
            //Field3 =   Rec_Reply_PlotD[findex+2][packet_cnt_PlotD];
            //Field3 = Field3 << 4 ;
            //hit6_subBX[frameCnt][packet_cnt_PlotD2] = Field3 >> 28 ;
            //qDebug() << "20- Hit-3 Sub-BX : " << QString("%1").arg(hit6_subBX[frameCnt][packet_cnt_PlotD], 0, 10);
            //qDebug() << "" ;
            //------------------------------------------------------------------------------
            Field3 =   Rec_Reply_PlotD[findex+2][packet_cnt_PlotD];
            //qDebug() << "21- Field(3) : " << QString("0x%1").arg(Field3, 0, 16);

            Field3 = Field3 << 8 ;
            bunchCrossing[frameCnt] = Field3 >> 20 ;
            //qDebug() << "22- Bunch Crossing : " << QString("%1").arg(bunchCrossing[frameCnt][packet_cnt_PlotD], 0, 10);
            //------------------------------------------------------------------------------

            //------------------------------------------------------------------------------
            //Field3 =   Rec_Reply_PlotD[findex+2][packet_cnt_PlotD];
            //Field3 = Field3 << 20 ;
            //orbitNumber[frameCnt][packet_cnt_PlotD2] = Field3 >> 20 ;
            //qDebug() << "23- Orbit Number : " << QString("%1").arg(orbitNumber[frameCnt][packet_cnt_PlotD], 0, 10);
            //qDebug() << "" ;

            /*
            //------------------------------------------------------------------------------
            //  RPC hit time stamping - Plot A
            //------------------------------------------------------------------------------
            if ((hit1_stripNum[frameCnt][packet_cnt_PlotD2]<=96)&&(hit1_subBX[frameCnt][packet_cnt_PlotD2]<=16)&&(bunchCrossing[frameCnt][packet_cnt_PlotD2]<=maxBX)){

            ArrayPnt1 = hit1_stripNum[frameCnt][packet_cnt_PlotD2] ;
            ArrayPnt2 = bunchCrossing[frameCnt][packet_cnt_PlotD2] ;

            RPCStripHit[ArrayPnt1][ArrayPnt2] = hit1_subBX[frameCnt][packet_cnt_PlotD2] ;
            //backendbmu2->BePlotter(RPCStripHit, hit1_stripNum[frameCnt][packet_cnt_PlotD]);
            //qDebug() << "1- Bunch Crossing : " << QString("%1").arg(bunchCrossing[frameCnt][packet_cnt_PlotD], 0, 10);
            //qDebug() << "2- Hit-1 Strip No : " << QString("%1").arg(hit1_stripNum[frameCnt][packet_cnt_PlotD], 0, 10);
            //qDebug() << "3- Hit-1 Sub-BX : " << QString("%1").arg(hit1_subBX[frameCnt][packet_cnt_PlotD], 0, 10);
        }


        if ((hit2_stripNum[frameCnt][packet_cnt_PlotD2]<=96)&&(hit2_subBX[frameCnt][packet_cnt_PlotD2]<=16)&&(bunchCrossing[frameCnt][packet_cnt_PlotD2]<=maxBX)){

            //RPCStripHit[hit2_stripNum][bunchCrossing] = hit2_subBX ;
            ArrayPnt1 = hit2_stripNum[frameCnt][packet_cnt_PlotD2] ;
            ArrayPnt2 = bunchCrossing[frameCnt][packet_cnt_PlotD2] ;
            RPCStripHit[ArrayPnt1][ArrayPnt2] = hit2_subBX[frameCnt][packet_cnt_PlotD2] ;
            //backendbmu2->BePlotter(RPCStripHit, hit2_stripNum[frameCnt][packet_cnt_PlotD]);
            //qDebug() << "4- Hit-2 Strip No : " << QString("%1").arg(hit2_stripNum[frameCnt][packet_cnt_PlotD], 0, 10);
            //qDebug() << "5- Hit-2 Sub-BX : " << QString("%1").arg(hit2_subBX[frameCnt][packet_cnt_PlotD], 0, 10);

        }

        if ((hit3_stripNum[frameCnt][packet_cnt_PlotD2]<=96)&&(hit3_subBX[frameCnt][packet_cnt_PlotD2]<=16)&&(bunchCrossing[frameCnt][packet_cnt_PlotD2]<=maxBX)){

            ArrayPnt1 = hit3_stripNum[frameCnt][packet_cnt_PlotD2] ;
            ArrayPnt2 = bunchCrossing[frameCnt][packet_cnt_PlotD2] ;
            RPCStripHit[ArrayPnt1][ArrayPnt2] = hit3_subBX[frameCnt][packet_cnt_PlotD2] ;
            //backendbmu2->BePlotter(RPCStripHit, hit3_stripNum[frameCnt][packet_cnt_PlotD]);
            //qDebug() << "6- Hit-3 Strip No : " << QString("%1").arg(hit3_stripNum[frameCnt][packet_cnt_PlotD], 0, 10);
            //qDebug() << "7- Hit-3 Sub-BX : " << QString("%1").arg(hit3_subBX[frameCnt][packet_cnt_PlotD], 0, 10);
        }

        if ((hit4_stripNum[frameCnt][packet_cnt_PlotD2]<=96)&&(hit4_subBX[frameCnt][packet_cnt_PlotD2]<=16)&&(bunchCrossing[frameCnt][packet_cnt_PlotD2]<=maxBX)){

            ArrayPnt1 = hit4_stripNum[frameCnt][packet_cnt_PlotD2] ;
            ArrayPnt2 = bunchCrossing[frameCnt][packet_cnt_PlotD2] ;
            RPCStripHit[ArrayPnt1][ArrayPnt2] = hit4_subBX[frameCnt][packet_cnt_PlotD2] ;
            //backendbmu2->BePlotter(RPCStripHit, hit4_stripNum[frameCnt][packet_cnt_PlotD]);
            //qDebug() << "8- Hit-4 Strip No : " << QString("%1").arg(hit4_stripNum[frameCnt][packet_cnt_PlotD], 0, 10);
            //qDebug() << "9- Hit-4 Sub-BX : " << QString("%1").arg(hit4_subBX[frameCnt][packet_cnt_PlotD], 0, 10);
        }

        if ((hit5_stripNum[frameCnt][packet_cnt_PlotD2]<=96)&&(hit5_subBX[frameCnt][packet_cnt_PlotD2]<=16)&&(bunchCrossing[frameCnt][packet_cnt_PlotD2]<=maxBX)){

            ArrayPnt1 = hit5_stripNum[frameCnt][packet_cnt_PlotD2] ;
            ArrayPnt2 = bunchCrossing[frameCnt][packet_cnt_PlotD2] ;
            RPCStripHit[ArrayPnt1][ArrayPnt2] = hit5_subBX[frameCnt][packet_cnt_PlotD2] ;
            //backendbmu2->BePlotter(RPCStripHit, hit5_stripNum[frameCnt][packet_cnt_PlotD]);
            //qDebug() << "10- Hit-5 Strip No : " << QString("%1").arg(hit5_stripNum[frameCnt][packet_cnt_PlotD], 0, 10);
            //qDebug() << "11 Hit-5 Sub-BX : " << QString("%1").arg(hit5_subBX[frameCnt][packet_cnt_PlotD], 0, 10);
        }

        if ((hit6_stripNum[frameCnt][packet_cnt_PlotD2]<=96)&&(hit6_subBX[frameCnt][packet_cnt_PlotD2]<=16)&&(bunchCrossing[frameCnt][packet_cnt_PlotD2]<=maxBX)){

            ArrayPnt1 = hit6_stripNum[frameCnt][packet_cnt_PlotD2] ;
            ArrayPnt2 = bunchCrossing[frameCnt][packet_cnt_PlotD2] ;
            RPCStripHit[ArrayPnt1][ArrayPnt2] = hit6_subBX[frameCnt][packet_cnt_PlotD2] ;
            //backendbmu2->BePlotter(RPCStripHit, hit6_stripNum[frameCnt][packet_cnt_PlotD]);
            //qDebug() << "12- Hit-6 Strip No : " << QString("%1").arg(hit6_stripNum[frameCnt][packet_cnt_PlotD], 0, 10);
            //qDebug() << "13- Hit-6 Sub-BX : " << QString("%1").arg(hit6_subBX[frameCnt][packet_cnt_PlotD], 0, 10);
        }


        //------------------------------------------------------------------------------
        //  RPC hit timeStamping - Plot B
        //------------------------------------------------------------------------------
        if ((hit1_subBX[frameCnt][packet_cnt_PlotD2]<=16)&&(hit1_stripNum[frameCnt][packet_cnt_PlotD2]<=96)){

            ArrayPnt1 = hit1_subBX[frameCnt][packet_cnt_PlotD2] ;
            ArrayPnt2 = hit1_stripNum[frameCnt][packet_cnt_PlotD2] ;

            RPCHitSubBx[ArrayPnt1][ArrayPnt2] = RPCHitSubBx[ArrayPnt1][ArrayPnt2] + 1 ;
            //backendstripprf->BeStripPrfPlotter(RPCHitSubBx, hit1_stripNum[frameCnt][packet_cnt_PlotD]);
            //qDebug() << "14- Hit-1 Strip No : " << QString("%1").arg(hit1_stripNum[frameCnt][packet_cnt_PlotD], 0, 10);
            //qDebug() << "15- Hit-1 Sub-BX : " << QString("%1").arg(hit1_subBX[frameCnt][packet_cnt_PlotD], 0, 10);
        }

        if ((hit2_subBX[frameCnt][packet_cnt_PlotD2]<=16)&&(hit2_stripNum[frameCnt][packet_cnt_PlotD2]<=96)){

            ArrayPnt1 = hit2_subBX[frameCnt][packet_cnt_PlotD2] ;
            ArrayPnt2 = hit2_stripNum[frameCnt][packet_cnt_PlotD2] ;
            //RPCHitSubBx[hit2_subBX][hit2_stripNum] = RPCHitSubBx[hit2_subBX][hit2_stripNum] + 1 ;
            RPCHitSubBx[ArrayPnt1][ArrayPnt2] = RPCHitSubBx[ArrayPnt1][ArrayPnt2] + 1 ;
            //backendstripprf->BeStripPrfPlotter(RPCHitSubBx, hit2_stripNum[frameCnt][packet_cnt_PlotD]);
        }

        if ((hit3_subBX[frameCnt][packet_cnt_PlotD2]<=16)&&(hit3_stripNum[frameCnt][packet_cnt_PlotD2]<=96)){

            ArrayPnt1 = hit3_subBX[frameCnt][packet_cnt_PlotD2] ;
            ArrayPnt2 = hit3_stripNum[frameCnt][packet_cnt_PlotD2] ;

            RPCHitSubBx[ArrayPnt1][ArrayPnt2] = RPCHitSubBx[ArrayPnt1][ArrayPnt2] + 1 ;
            //backendstripprf->BeStripPrfPlotter(RPCHitSubBx, hit3_stripNum[frameCnt][packet_cnt_PlotD]);
        }

        if ((hit4_subBX[frameCnt][packet_cnt_PlotD2]<=16)&&(hit4_stripNum[frameCnt][packet_cnt_PlotD2]<=96)){

            ArrayPnt1 = hit4_subBX[frameCnt][packet_cnt_PlotD2] ;
            ArrayPnt2 = hit4_stripNum[frameCnt][packet_cnt_PlotD2] ;

            RPCHitSubBx[ArrayPnt1][ArrayPnt2] = RPCHitSubBx[ArrayPnt1][ArrayPnt2] + 1 ;
            //backendstripprf->BeStripPrfPlotter(RPCHitSubBx, hit4_stripNum[frameCnt][packet_cnt_PlotD]);
        }

        if ((hit5_subBX[frameCnt][packet_cnt_PlotD2]<=16)&&(hit5_stripNum[frameCnt][packet_cnt_PlotD2]<=96)){
            ArrayPnt1 = hit5_subBX[frameCnt][packet_cnt_PlotD2] ;
            ArrayPnt2 = hit5_stripNum[frameCnt][packet_cnt_PlotD2] ;

            RPCHitSubBx[ArrayPnt1][ArrayPnt2] = RPCHitSubBx[ArrayPnt1][ArrayPnt2] + 1 ;
            //backendstripprf->BeStripPrfPlotter(RPCHitSubBx, hit5_stripNum[frameCnt][packet_cnt_PlotD]);
        }

        if ((hit6_subBX[frameCnt][packet_cnt_PlotD2]<=16)&&(hit6_stripNum[frameCnt][packet_cnt_PlotD2]<=96)){
            ArrayPnt1 = hit6_subBX[frameCnt][packet_cnt_PlotD2] ;
            ArrayPnt2 = hit6_stripNum[frameCnt][packet_cnt_PlotD2] ;

            RPCHitSubBx[ArrayPnt1][ArrayPnt2] = RPCHitSubBx[ArrayPnt1][ArrayPnt2] + 1 ;
            //backendstripprf->BeStripPrfPlotter(RPCHitSubBx, hit6_stripNum[frameCnt][packet_cnt_PlotD]);
        }


        //------------------------------------------------------------------------------
        //  Histogram - Plot C
        //------------------------------------------------------------------------------

        if ((hit1_stripNum[frameCnt][packet_cnt_PlotD2]<=96)&&(hit1_stripNum[frameCnt][packet_cnt_PlotD2]!=127)){
            ArrayPnt1 = hit1_stripNum[frameCnt][packet_cnt_PlotD2] ;
            RPCHist[ArrayPnt1] = RPCHist[ArrayPnt1] + 1 ;
        }

        if ((hit2_stripNum[frameCnt][packet_cnt_PlotD2]<=96)&&(hit2_stripNum[frameCnt][packet_cnt_PlotD2]!=127)){
            ArrayPnt1 = hit2_stripNum[frameCnt][packet_cnt_PlotD2] ;
            RPCHist[ArrayPnt1] = RPCHist[ArrayPnt1] + 1 ;
        }

        if ((hit3_stripNum[frameCnt][packet_cnt_PlotD2]<=96)&&(hit3_stripNum[frameCnt][packet_cnt_PlotD2]!=127)){
            ArrayPnt1 = hit3_stripNum[frameCnt][packet_cnt_PlotD2] ;
            RPCHist[ArrayPnt1] = RPCHist[ArrayPnt1] + 1 ;
        }

        if ((hit4_stripNum[frameCnt][packet_cnt_PlotD2]<=96)&&(hit4_stripNum[frameCnt][packet_cnt_PlotD2]!=127)){
            ArrayPnt1 = hit4_stripNum[frameCnt][packet_cnt_PlotD2] ;
            RPCHist[ArrayPnt1] = RPCHist[ArrayPnt1] + 1 ;
        }

        if ((hit5_stripNum[frameCnt][packet_cnt_PlotD2]<=96)&&(hit5_stripNum[frameCnt][packet_cnt_PlotD2]!=127)){
            ArrayPnt1 = hit5_stripNum[frameCnt][packet_cnt_PlotD2] ;
            RPCHist[ArrayPnt1] = RPCHist[ArrayPnt1] + 1 ;
        }

        if ((hit6_stripNum[frameCnt][packet_cnt_PlotD2]<=96)&&(hit6_stripNum[frameCnt][packet_cnt_PlotD2]!=127)){
            ArrayPnt1 = hit6_stripNum[frameCnt][packet_cnt_PlotD2] ;
            RPCHist[ArrayPnt1] = RPCHist[ArrayPnt1] + 1 ;
        }
        */

            //backendhitplot->BeHistPlotter(RPCHist);

            //backendhitplot->repaint();
            //backendhitplot->show();
            //-------------------------------------



            //------------------------------------------------------------------------------
            //  RPC hit timing Profile - Plot D
            //------------------------------------------------------------------------------
            //be_dpc_mutex.lock();
            ArrayPnt1 = bunchCrossing[frameCnt] ;

        if ((hit1_stripNum[frameCnt]<=96)/*&&(hit1_stripNum[frameCnt][packet_cnt_PlotD2]!=127)*/){

            RPCHitTimingPrf_PlotD[ArrayPnt1] =  RPCHitTimingPrf_PlotD[ArrayPnt1] +  1 ;
        }

        if ((hit2_stripNum[frameCnt]<=96)/*&&(hit2_stripNum[frameCnt][packet_cnt_PlotD2]!=127)*/){

            RPCHitTimingPrf_PlotD[ArrayPnt1] =  RPCHitTimingPrf_PlotD[ArrayPnt1] +  1 ;
        }

        if ((hit3_stripNum[frameCnt]<=96)/*&&(hit3_stripNum[frameCnt][packet_cnt_PlotD2]!=127)*/){
            RPCHitTimingPrf_PlotD[ArrayPnt1] =  RPCHitTimingPrf_PlotD[ArrayPnt1] +  1 ;
        }

        if ((hit4_stripNum[frameCnt]<=96)/*&&(hit4_stripNum[frameCnt][packet_cnt_PlotD2]!=127)*/){
            RPCHitTimingPrf_PlotD[ArrayPnt1] =  RPCHitTimingPrf_PlotD[ArrayPnt1] +  1 ;
        }

        if ((hit5_stripNum[frameCnt]<=96)/*&&(hit5_stripNum[frameCnt][packet_cnt_PlotD2]!=127)*/){
            RPCHitTimingPrf_PlotD[ArrayPnt1] =  RPCHitTimingPrf_PlotD[ArrayPnt1] +  1 ;
        }

        if ((hit6_stripNum[frameCnt]<=96)/*&&(hit6_stripNum[frameCnt][packet_cnt_PlotD2]!=127)*/){
            RPCHitTimingPrf_PlotD[ArrayPnt1] =  RPCHitTimingPrf_PlotD[ArrayPnt1] +  1 ;
        }
        //backendtimingprf->BeTimingPrfPlotter(RPCHitTimingPrf_PlotD);
        //backendtimingprf->show();

        //be_dpc_mutex.unlock();

    }
    else if(Field1 == 58){

    }

    frameCnt++;
}
//===========================================
//
//===========================================



emit BE_dpsPlotD_response(frameCnt);
}
