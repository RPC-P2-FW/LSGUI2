#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QtCore>
#include "YasinLanLib.h"
#include <QMutex>
#include <QThread>
#include <QWaitCondition>


class MyThread : public QThread
{
    Q_OBJECT

public:
    explicit MyThread(QObject *parent = nullptr);

    ~MyThread();

    void transaction(USHORT &IPaddress);//, int waitTimeout, const QString &request);

    UINT t_value;
    UINT t_address ;
    UINT t_receivedSize = 0;
    UINT t_safe_receivedSize = 0;
    UINT t_receivedBuf = 0;
    UINT t_receiveBufSize = 0;
    UINT t_receiveBufIndex = 0;
    unsigned int RECEIVE_COUNTER = 0;

    unsigned char t_receiveBuf[500][500] ; //    char *t_receiveBuf = NULL;
    boolean t_bSave = false ;

    boolean t_buffer_full = 0;
    //void run_YE_TCP_RecvPacket();
    boolean on_receive = false;
    unsigned int packetCount = 0;

signals:
    void response(const UINT rec_complete) ;// ,const boolean Buffer_full );
    //void response(const QString &s);
    //void error(const QString &s);
    //void timeout(const QString &s);

private:
    void run() override;

    QMutex m_mutex;
    QWaitCondition m_cond;
    bool m_quit = false;

    UINT m_IPaddress;
    QString m_request;
    UINT m_waitTimeout = 0;



    QString sResult , sTemp , sData ;

    char    buffer[RECV_PACKET_SIZE];
    UCHAR   command=0;
    USHORT  address=0 ;
    UINT    value=0;
    USHORT  length=0 ;
    UCHAR   packetCounter=0;
    QString msg ;


};

#endif // MYTHREAD_H
