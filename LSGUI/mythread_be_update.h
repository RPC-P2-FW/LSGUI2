#ifndef MYTHREAD_BE_UPDATE_H
#define MYTHREAD_BE_UPDATE_H

#include <QObject>
#include <QtCore>
#include "YasinLanLib.h"
#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QString>

class mythread_be_update : public QThread
{
    Q_OBJECT
public:
    explicit mythread_be_update(QObject *parent = nullptr);

    ~mythread_be_update();

    void BE_transaction(void);//, int waitTimeout, const QString &request);
    void BE_WriteConfig(UCHAR cb_address, UINT cb_value);
    void Read_Current_Frame (void);

    bool be_retVal ;

    unsigned int Current_Frame [4] = {} ; /*"11010000110100001101000011010000110100001101000000000001000000000000000000000000000000000100000000000000000000000000000000000100";*/

    UINT Parameter_Counter = 0 ;
    UINT be_value=0;
    UINT be_value2 =0;
    bool be_prog_full = false;

    unsigned int Out_frame_arr[4];



signals:

    void BE_respond_send(const UINT BE_Parameter_Counter) ;// ,const boolean Buffer_full );


private:
    void run() override;

    QMutex be_mutex;
    QWaitCondition be_cond;
    bool be_quit = false;
    bool ChBx_checked = false;

    UINT64 be_fileLength = 16;
    char *be_sendBuf;

    char    be_buffer[RECV_PACKET_SIZE];
    UCHAR   be_command=0;
    USHORT  be_address=0 ;

    USHORT  be_length=0 ;
    UCHAR   be_packetCounter=0;

    bool    be_disp_once = true;
    UINT64  be_counter = 0;



};

#endif // MYTHREAD_BE_UPDATE_H
