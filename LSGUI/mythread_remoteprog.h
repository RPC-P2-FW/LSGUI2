#ifndef MYTHREAD_CB_REMOTEPROG_H
#define MYTHREAD_CB_REMOTEPROG_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtCore>
#include "YasinLanLib.h"
#include <QMutex>
#include <QThread>
#include <QWaitCondition>

class Mythread_RemoteProg : public QThread
{
    Q_OBJECT
public:
    explicit Mythread_RemoteProg(QObject *parent = nullptr);
    ~Mythread_RemoteProg();

    void RP_transaction(void);//, int waitTimeout, const QString &request);
    void RP_WriteConfig(UCHAR rp_address, UINT rp_value);


    UINT32 packet_size = 270 ;
    unsigned char *rp_sendBuf = NULL;
    char *rp_sendmem = NULL;

    char rp_flashbuf = 0 ;

    UINT32 rp_Addr_Ptr = 0 ;

    UINT32 rp_itrloop;
    UINT32 rp_packCnt;

    bool rp_prog_full= false ;
    bool rp_buf_empty = false ;
    bool rp_buf_ready = false ;

    char rp_load_state = 0;
    bool rp_quit = false;



    QString rp_text;
    UINT64  rp_fileLength;
    UINT64  rp_sentSize;
    UINT64  rp_remainLength;
    UINT64  rp_cnt = 0 ;
    unsigned int const cmdOverhrad = 0 ;

signals:
    void RemoteProgRespondSend(const UINT32 RP_address_Counter) ;// ,const boolean Buffer_full );

private:

    void run() override;

    QMutex rp_mutex;
    QWaitCondition rp_cond;

    bool rp_retVal;





};

#endif // MYTHREAD_CB_REMOTEPROG_H
