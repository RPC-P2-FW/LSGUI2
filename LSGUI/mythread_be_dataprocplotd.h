#ifndef MYTHREAD_BE_DATAPROCPLOTD_H
#define MYTHREAD_BE_DATAPROCPLOTD_H

#include <QObject>
#include <QWidget>

#include <QMutex>
#include <QThread>
#include <QWaitCondition>

#include "backendemu2.h"

class Mythread_BE_DataProcPlotD : public QThread
{
Q_OBJECT
    public:
        explicit Mythread_BE_DataProcPlotD(QObject *parent = nullptr);
        ~Mythread_BE_DataProcPlotD();

        void BE_dataProcessPlotD_transaction(void);//, int waitTimeout, const QString &request);

        unsigned int packet_cnt_PlotD = 0 ;

        unsigned int Rec_Reply_PlotD [300][300];

        //unsigned int RPCHist[100]; // Plot C
        //unsigned int RPCStripHit[200][200]; // Plot A - [strip][BX]
        //unsigned int RPCHitSubBx[16][100]; //Plot B - [Sub-BX][Strip]
        unsigned int RPCHitTimingPrf_PlotD[4000]; // Plot D


    signals:
        void BE_dpsPlotD_response(unsigned int) ;// ,const boolean Buffer_full );


    private:
        void run() override;

        QMutex be_dpcPlotD_mutex;
        QWaitCondition be_dpcPlotD_cond;
        bool be_dpcPlotD_quit = false;

        unsigned int const maxBX = 3564; //3564



        unsigned int findex = 0 ;
        unsigned int Field1 = 0 ;
        unsigned int Field2 = 0 ;
        unsigned int Field3 = 0 ;

        unsigned int frameCnt = 0 ;

        unsigned int hit1_stripNum[120] ;
        unsigned int hit1_subBX [120][10] ;

        unsigned int hit2_stripNum [120] ;
        unsigned int hit2_subBX [120][10] ;

        unsigned int hit3_stripNum [120] ;
        unsigned int hit3_subBX [120][10] ;

        unsigned int hit4_stripNum [120] ;
        unsigned int hit4_subBX [120][10] ;

        unsigned int hit5_stripNum [120] ;
        unsigned int hit5_subBX [120][10] ;

        unsigned int hit6_stripNum [120] ;
        unsigned int hit6_subBX [120][10] ;

        unsigned int bunchCrossing [120] ;
        unsigned int orbitNumber [120][10] ;

        unsigned int ArrayPnt1 = 0 ;
        unsigned int ArrayPnt2 = 0 ;


};

#endif // MYTHREAD_BE_DATAPROCPLOTD_H
