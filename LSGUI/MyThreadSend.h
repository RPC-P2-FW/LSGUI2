#ifndef MYTHREADSEND_H
#define MYTHREADSEND_H

#include <QtCore>
#include "YasinLanLib.h"
#include <QMutex>
#include <QThread>
#include <QWaitCondition>


class MyThreadSend : public QThread
{
    Q_OBJECT

public:
    explicit MyThreadSend(QObject *parent = nullptr);

    ~MyThreadSend();

    void transaction_send(USHORT &IPaddress);//, int waitTimeout, const QString &request);

    UINT t_value;
    UINT t_address ;
    UINT t_receivedSize = 0;
    UINT t_safe_receivedSize = 0;
    UINT t_receivedBuf = 0;
    UINT t_receiveBufSize = 0;
    UINT t_receiveBufIndex = 0;

    char *t_receiveBuf = NULL;
    boolean t_bSave = false ;

    boolean t_buffer_full = 0;
    //void run_YE_TCP_RecvPacket();
    QString t_text;
    UINT64  t_fileLength;
    UINT64  t_sentSize;
    boolean t_repeatSend = false ;
    boolean t_OpenSendFile = false ;

    char *t_sendBuf = NULL;

signals:
    void response_send(const UINT64 totalSentSize ) ;// ,const boolean Buffer_full );
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

    UINT packetCount = 0;

    QString sResult , sTemp , sData ;

    char    buffer[RECV_PACKET_SIZE];
    UCHAR   command=0;
    USHORT  address=0 ;
    UINT    value=0;
    USHORT  length=0 ;
    UCHAR   packetCounter=0;
    QString msg ;
    bool   t_retVal = false;

};
#endif // MYTHREADSEND_H

