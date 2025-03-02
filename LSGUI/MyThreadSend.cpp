#include <QMainWindow>
#include"mainwindow.h"
#include "mythread.h"
#include "MyThreadSend.h"
#include "YasinLanLib.h"

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


//================================================================
//
//================================================================
MyThreadSend::MyThreadSend(QObject *parent) :
        QThread(parent)
{

}

//================================================================
//
//================================================================
MyThreadSend::~MyThreadSend(){

    m_mutex.lock();
    m_quit = true;
    m_mutex.unlock();
    wait();
}

//================================================================
//
//================================================================
void MyThreadSend::transaction_send(USHORT &IPaddress)//, int waitTimeout, const QString &request)
{

    const QMutexLocker locker(&m_mutex);


    if (!isRunning())
    {
        start(QThread::NormalPriority);
        m_quit = false;
        t_sentSize = 0 ;
    }
    else
    {
        m_cond.wakeOne();
    }
}

//================================================================
//
//================================================================
void MyThreadSend::run()
{


    //char *t_sendBuf = (char*)malloc(t_fileLength);
    //memset(t_sendBuf, 0, t_fileLength);
    //memcpy(&t_sendBuf, MainWindow::sendBuf , t_fileLength);

    do
    {
        t_retVal = YE_TCP_SendMem(t_sendBuf, t_fileLength);

        if (!t_retVal)
        {
            if (t_sendBuf != NULL)
                free(t_sendBuf);
            return;
        }
        else
        {
            t_sentSize += t_fileLength;

        }
    }
    while (t_repeatSend);

    emit response_send(t_sentSize);
}

