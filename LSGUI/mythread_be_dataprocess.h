#ifndef MYTHREAD_BE_DATAPROCESS_H
#define MYTHREAD_BE_DATAPROCESS_H

#include <QObject>
#include <QWidget>

#include <QMutex>
#include <QThread>
#include <QWaitCondition>

#include "backendemu2.h"


class Mythread_BE_DataProcess : public QThread
{
    Q_OBJECT

public:
    explicit Mythread_BE_DataProcess(QObject *parent = nullptr);
    ~Mythread_BE_DataProcess();

    void BE_dataProcess_transaction(void);//, int waitTimeout, const QString &request);

    unsigned int packet_cnt = 0 ;
    unsigned int Rec_Reply [300][300];

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




signals:
    void BE_dps_response(unsigned int) ;// ,const boolean Buffer_full );


private:
    void run() override;

    QMutex be_dpc_mutex;
    QWaitCondition be_dpc_cond;
    bool be_dpc_quit = false;
};

#endif // MYTHREAD_BE_DATAPROCESS_H
