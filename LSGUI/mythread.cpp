

#include <QMainWindow>
#include"mainwindow.h"
#include "mythread.h"
#include "YasinLanLib.h"
#include <QtCore>
#include <QDebug>
#include <QTime>
#include <QMutex>
#include <QThread>
#include <QWaitCondition>

MyThread::MyThread(QObject *parent) :
        QThread(parent)
{

}

MyThread::~MyThread(){

    m_mutex.lock();
    m_quit = true;
    m_mutex.unlock();
    wait();

}

void MyThread::transaction(USHORT &IPaddress)//, int waitTimeout, const QString &request)
{

    const QMutexLocker locker(&m_mutex);
    m_IPaddress = IPaddress;

    //m_waitTimeout = waitTimeout;
    //m_request = request;

    if (!isRunning())
    {
        start(QThread::HighPriority);
        m_quit = false;
    }
    else
    {
        m_cond.wakeOne();
    }
    qDebug() << " >> IPAddress inside Thread:"<<m_IPaddress;
    qDebug() << "Ethernet Receiver " ;
}


void MyThread::run()
{

   while  (!m_quit)
   {
    //------------------------------------
    m_mutex.lock();
       t_safe_receivedSize = t_receivedSize;
    m_mutex.unlock();


     YE_TCP_RecvPacket(&command, &address, &value, buffer, &length, &packetCounter);



    if (command == readRegFBCommand)
    {
         //qDebug() << "SW <- HD:  readRegFBCommand--------- =" << readRegFBCommand;
         //m_mutex.lock();
            t_value = value;
            t_address= address;
        //m_mutex.unlock();

    }
    else if(command == writeRegAckCommand)
    {
        //qDebug() << "SW <- HD:  writeRegAckCommand--------- =" << writeRegAckCommand;
        m_mutex.lock();
            t_value = value;
            t_address= address;
        m_mutex.unlock();
    }

    else if(command == readCfgFBCommand)
    {
        m_mutex.lock();
            //qDebug() << "SW <- HD:  readCfgFBCommand--------- =" << readCfgFBCommand;
            t_value = value;
            t_address= address;
        m_mutex.unlock();
    }
    else if(command == writeCfgAckCommand)
    {
        m_mutex.lock();
            //qDebug() << "SW <- HD:  writeCfgAckCommand--------- =" << writeCfgAckCommand;
            t_value = value;
            t_address= address;
        m_mutex.unlock();
    }
    else if(command == readMemFBCommand)
    {

        //qDebug() << "SW <- HD:  readMemFBCommand--------- =" << readMemFBCommand;

        //qDebug() << "packetCount =" << packetCount;
        //qDebug() << "on_receive = " << on_receive ;

        if (on_receive == true)
        {

            m_mutex.lock();//-------------------

            // RECV_PACKET_SIZE   512 //maximum length in each Receive
            // SEND_PACKET_SIZE   536 //maximum length in each Send
            // PACKET_HEADER_SIZE 8

            if (length > RECV_PACKET_SIZE-PACKET_HEADER_SIZE) //512-8 = 504
            {
                length = RECV_PACKET_SIZE-PACKET_HEADER_SIZE; //504
            }
            /*
            qDebug() << "S2) ======================================================";
            qDebug() << "S2) t_receiveBufSize =" << t_receiveBufSize ;
            qDebug() << "S2) Length =" << length ;
            qDebug() << "S2) t_receiveBufIndex =" << t_receiveBufIndex ;
            qDebug() << "S2) Received Thread End." ;
            qDebug() << "S2) ======================================================";
            */

            for (unsigned int i=0 ; i<length ;i++){
              t_receiveBuf[i][packetCount] = buffer [i];
            }


            t_buffer_full = 1;
            //on_receive = false;

            //emit response(length);


            t_buffer_full = 0 ;
            t_receivedBuf = 0 ;

        }

        //========================
        packetCount++;
        if (packetCount == 499){packetCount=0;}        
        //========================

        emit response(length);

        m_mutex.unlock();
        //----------------------------------------

    }
    else if(command == writeMemAckCommand)
    {
        //qDebug() << "SW <- HD:  writeMemAckCommand--------- =" << writeMemAckCommand;
        m_mutex.lock();
            t_value = value;
            t_address= address;
        m_mutex.unlock();
    }
  }

}
