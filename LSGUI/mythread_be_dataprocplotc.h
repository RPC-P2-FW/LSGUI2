#ifndef MYTHREAD_BE_DATAPROCPLOTC_H
#define MYTHREAD_BE_DATAPROCPLOTC_H

#include <QObject>
#include <QWidget>

#include <QMutex>
#include <QThread>
#include <QWaitCondition>


class Mythread_BE_DataProcPlotC : public QThread
{
Q_OBJECT
        public:
            explicit Mythread_BE_DataProcPlotC(QObject *parent = nullptr);
            ~Mythread_BE_DataProcPlotC();
            void BE_dataProcessPlotC_transaction(void);//, int waitTimeout, const QString &request);

            unsigned int packet_cnt_PlotC = 0 ;

            unsigned int Rec_Reply_PlotC [300][300];

            unsigned int RPCHist_PlotC[100]; // Plot C
            //unsigned int RPCStripHit[200][200]; // Plot A - [strip][BX]
            //unsigned int RPCHitSubBx[16][100]; //Plot B - [Sub-BX][Strip]
            //unsigned int RPCHitTimingPrf_PlotD[4000]; // Plot D

        signals:
            void BE_dpsPlotC_response(unsigned int) ;// ,const boolean Buffer_full );


        private:
            void run() override;

            QMutex be_dpcPlotC_mutex;
            QWaitCondition be_dpcPlotC_cond;
            bool be_dpcPlotC_quit = false;

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

#endif // MYTHREAD_BE_DATAPROCPLOTC_H
