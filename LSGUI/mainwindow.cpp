#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "YasinLanLib.h"
#include "mythread.h"
#include "MyThreadSend.h"
#include "sendframe.h"
#include "realtime.h"
#include "realtimev2.h"
#include "mythread_cb_update.h"
#include "mythread_lb_update.h"
#include "backendemu2.h"
#include "backendhitplot.h"
#include "backendstripprf.h"
#include "backendtimingprf.h"
#include "mythread_be_dataprocess.h"

#include <QAbstractItemView>
#include <QApplication>
#include <QAbstractItemModel>
#include <QVarLengthArray>
#include <QCompleter>
#include <qdatastream.h>
#include <qdatetime.h>
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
#include <QtMath>
#include <QMessageBox>
#include <QMetaEnum>
#include <QModelIndex>
#include <QTableWidgetItem>
#include <QtWidgets>
#include <QtNetwork>
#include <QtCore>
#include <QtDebug>
#include <QStringRef>
#include <QScreen>
#include <QScrollBar>
#include <qstring.h>

#include <stdio.h>
#include <QApplication>
#include <QDebug>
#include <QThread>
#include <QProcess>
#include <QFile>
#include <QDir>


#include <stdio.h>
#include <string.h>


bool retVal = false;
bool onReceive = false;
bool onSend = false;
UINT receivedSize = 0;
unsigned int lastCounter = 0;
unsigned int errorCount = 0;
UINT receiveBufSize = 0 ;

bool repeatSend = false;

QString filename = "logfile"; // Make a file in the current directory
QFile f(filename+".txt");
QTextStream out(&f);

// new line to check the gitlab

//==========================================================================
//  MainWindow Function
//==========================================================================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    //online modification
    
    unsigned long int apple = 20 ;
    printf("address of Apple : 0x%x \n" , &apple);
    printf("Value of Apple : %d \n" , apple);

    unsigned long int *pntr ;
    pntr = &apple;

    //printf("pntr : 0x%x \n" , pntr );
    //printf("pntr : %d \n" , *pntr );

    qDebug() << "Address pntr :" << pntr;
    qDebug() << "Value pntr :" << *pntr;

    ui->setupUi(this);
    ui->lineEdit->setText("172.30.1.1");
    ui->lineEdit_3->setText("0");
    ui->lineEdit_4->setText("0");
    ui->lineEdit_5->setText("0");
    ui->lineEdit_6->setText("0");
    ui->lineEdit_7->setText("536");
    ui->lineEdit_8->setText("512");
    ui->lineEdit_25->setText("1500");
    //ui->framelineEdit->setText("10101010100110011000100001110111011001100101010101000100001100110010001000010001");
    ui->framelineEdit->setText("11010000"
                               "11010000"
                               "11010000"
                               "11010000"
                               "11010000"
                               "11010000"
                               "00000001"
                               "00000000"
                               "00000000"
                               "00000000"
                               "00000000"
                               "00000000"
                               "00000000"
                               "00000000"
                               "00000000"
                               "00000100");


    ui->ping ->setDisabled(1);
    ui->ReadReg->setDisabled(1);
    ui->WriteReg->setDisabled(1);
    ui->ReadConfig->setDisabled(1);
    ui->WriteConfig->setDisabled(1);
    ui->ReceiveBuffer->setDisabled(1);
    ui->SendBuffer->setDisabled(1);
    ui->ReceiveBuffer->setDisabled(1);


    ui->radioButton_CB_ST0->setChecked(1);
    ui->radioButton_Load_Speed3->setChecked(1);

    ui->ChBX_freeRunLog->setChecked(0);
    ui->ChBx_BS_BEB->setChecked(0);
    ui->ChBx_BS_CB->setChecked(1);

    packet_cnt = 0 ; // is used on the ThreadSlot_showRespond()

    ui->RB_CB_DB_Barrel->setChecked(0);
    ui->RB_CB_DB_Endcap->setChecked(1);


    ui->RB_CB_DB_No1->setChecked(1);
    ui->RB_CB_DB_No2->setChecked(0);
    ui->RB_CB_DB_No3->setChecked(0);

    ui->RB_CB_DB_Port1->setChecked(1);
    ui->RB_CB_DB_Port2->setChecked(0);


    ui->ChBx_CB_FPGA_VCORE  ->setDisabled(1);
    ui->ChBx_CB_FPGA_VCCBRAM->setDisabled(1);
    ui->ChBx_CB_FPGA_VCCAUX ->setDisabled(1);
    ui->ChBx_CB_FPGA_Temp   ->setDisabled(1);
    ui->ChBx_CB_SEM_Counter ->setDisabled(1);



    //str = "";
    //str += QString("%1%2\n").arg("LB IP Address : ").arg(ui->lineEdit->text());
    //ui->textEdit->setText(str);

    qRegisterMetaType<INT64>();
    connect(&m_thread  , &MyThread::response, this,&MainWindow::ThreadSlot_showResponse,Qt::QueuedConnection);
    connect(&s_thread  , &MyThreadSend::response_send, this,&MainWindow::ThreadSlot_showResponseSend,Qt::QueuedConnection);
    connect(&cb_thread , &Mythread_CB_Update::CB_respond_send, this , &MainWindow::ThreadSlot_Check_cb_status_register,Qt::QueuedConnection);
    connect(&lb_thread , &Mythread_LB_Update::LB_respond_send, this , &MainWindow::ThreadSlot_Check_lb_status_register,Qt::QueuedConnection);
    connect(&rp_thread , &Mythread_RemoteProg::RemoteProgRespondSend, this, &MainWindow::ThreadSlot_rp_status_register,Qt::QueuedConnection );
    connect(&be_thread , &mythread_be_update::BE_respond_send, this , &MainWindow::ThreadSlot_Check_be_status_register,Qt::QueuedConnection);

    //connect(&be_dpc_thread, &Mythread_BE_DataProcess::BE_dps_response,this,&MainWindow::ThreadSlot_be_dpc_plot, Qt::QueuedConnection );
    connect(&be_dpcPlotD_thread, &Mythread_BE_DataProcPlotD::BE_dpsPlotD_response,this,&MainWindow::ThreadSlot_be_dpc_plotD, Qt::QueuedConnection );
    connect(&be_dpcPlotC_thread, &Mythread_BE_DataProcPlotC::BE_dpsPlotC_response,this,&MainWindow::ThreadSlot_be_dpc_plotC, Qt::QueuedConnection );

    QPushButton *quitButton = new QPushButton("Quit");
    connect(quitButton, &QPushButton::clicked, this, &QCoreApplication::quit, Qt::QueuedConnection);


    qtimer = new QTimer (this);
    connect(qtimer,SIGNAL(timeout()), this,SLOT(on_timeout()));

    qtimer2 = new QTimer (this);
    connect(qtimer2,SIGNAL(timeout()), this,SLOT(on_timeout2()));

    qtimer3 = new QTimer (this);
    connect(qtimer3,SIGNAL(timeout()), this,SLOT(on_timeout3()));

    systemClock = new QTimer (this);
    connect(systemClock,SIGNAL(timeout()), this,SLOT(on_systemClock_timeout()));
    systemClock->start(1000);
    //connect(m_thread, SIGNAL(response()), m_thread, SLOT(deleteLater()));

    //Qt::BlockingQueuedConnection
    //Qt::QueuedConnection
    //Qt::DirectConnection
    //Qt::AutoConnection



   //-------------------------------------
    QTableWidgetItem *item;
    //item = new QTableWidgetItem;
    int rowTable ;
    int columnTable ;

    rowTable = 0 ;
    columnTable = 1 ;

    freeRunLog = false;

    for(int i=0 ; i<rowTable+7; i++){
     item = new QTableWidgetItem;
     item->setText("Ok-*-*");
     item->setTextAlignment(-20);
     ui->tableWidget->setItem(i,columnTable, item);
    }
    //====================================================

    //ui->tabWidget->setCurrentIndex(ui->tableWidget->count());

    ui->tabWidget_FEB->setCurrentIndex(ui->tabWidget_FEB->count());

    backendbmu2 = new BackendEmu2();
    backendbmu2 ->setWindowTitle(" PLOT-A) RPC Strip Hit Time Stamping");
    backendbmu2 ->BeSetupPlot();


    backendstripprf = new BackendStripPrf();
    backendstripprf ->setWindowTitle("PLOT-B) RPC Strip Hit Rate VS Sub-BX");
    backendstripprf ->BeStripPrfSetupPlot();


    backendhitplot = new BackendHitPlot();
    backendhitplot ->setWindowTitle(" PLOT-C) RPC Hit Rate Histogram");
    backendhitplot ->BeHistSetupPlot();


    backendtimingprf = new BackendTimingPrf();
    backendtimingprf ->setWindowTitle("PLOT-D) RPC Hits Timing Profile (Hit rate VS Bunch Crossing)");
    backendtimingprf ->BeTimingPrfSetupPlot();


    //Disabling the Qt Close Button
    setWindowFlags(Qt::Window
                   | Qt::WindowMinimizeButtonHint
                   | Qt::WindowMaximizeButtonHint );
                   //| Qt::WindowCloseButtonHint);


    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) return;









/*

    QString FileName;
    QString FlashText;
    QString str;

    char file_data;
    QString string;
    UINT64 file_counter=0;

    rp_thread.rp_remainLength = 0 ;
    rp_thread.rp_fileLength = 0 ;
    rp_thread.rp_packCnt = 0 ;
    rp_thread.packet_size = 480 ; //270

    QString filter = "Text File (*.txt) ;; MCS File (*.mcs) ;; All File (*.*) ";
    //FileName = QFileDialog::getOpenFileName(this,"Open a File", "C:\\M:\temp/QT/Sample1/LinkSystemGUI2/LSGUI/LSGUI/",filter);
    FileName = QFileDialog::getOpenFileName(this,"Open a File", QDir::toNativeSeparators(QDir::currentPath()),filter);

    QFile file(FileName);


    //--------------------------------------------------------
    if (!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(this,"Open File    ", "Error");
    }
    else
    {


        QTextStream in(&file);
        FlashText = in.readAll() ;
        fileLength = FlashText.size();
        qDebug() << "Flash File Length =" << fileLength ;
        file.close();

        //--------------------------------------------------------
        UsendBuf = (unsigned char*)malloc(fileLength); // char *flashBuf;
        memset(UsendBuf, 0, fileLength);
        //--------------------------------------------------------

        //--- Step 2 ----
        //  Load content of the flash buffet from configuration file
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this,"Open File    ", "Error");
        }
        else
        {
            while (!file.atEnd()){
                file.read(&file_data,sizeof(quint8));
                quint8  U_file_data = file_data;
                UsendBuf[file_counter] = conv_ascii_to_hex(U_file_data);
                qDebug() << "1- U_file_data =" << U_file_data << " UsendBuf[file_counter]" << QString("%1").arg(UsendBuf[file_counter],0,16) ;
                qDebug() << " " ;

                file_counter++;

            }
            qDebug() << "Total number of Characters =" << file_counter ;
            file.close();


            //QString fileContent =  file.readAll();
            //QByteArray HexVal = QByteArray::fromHex(fileContent.toUtf8());
            //qDebug() << "HexVal = " <<HexVal ;


            //--- Step 3 ----
            //---------------------------------------------------------
            // push sendBuf buffer to the buffer of the Send Thread (rp_thread.t_sendBuf)
            //---------------------------------------------------------
            rp_thread.rp_fileLength = fileLength;

            rp_thread.rp_sendBuf = (unsigned char*)malloc(fileLength); // Create a buffer, char *sendBuf;
            memset(rp_thread.rp_sendBuf, 0, fileLength);      // Set all element to zero

            memcpy(rp_thread.rp_sendBuf,UsendBuf,fileLength);  // Copy current buffer to the thread buffer
            //---------------------------------------------------------
            rp_thread.rp_sendmem = (char*)malloc(rp_thread.packet_size); // Create a buffer, char *sendBuf;
            memset(rp_thread.rp_sendmem, 0, rp_thread.packet_size);
            //---------------------------------------------------------

            str = QString("%1").arg(fileLength);
            ui->lineEdit_fileSize->setText(str);
        }   
    }
*/

/*
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        in.setCodec("UTF-8");
        QString line = in.readLine();

        qDebug() << line;

        QString result;
        for(int i = 0; i < line.size(); ++i) {
            const ushort code = line.at(i).unicode();
            if (code < 0x0080)
                result += line.at(i);
            else
                result += QString("\\u%1").arg(code, 4, 16, QChar('0'));
        }

        qDebug() << result;
    }*/

    /*
    if (file.open(QIODevice::ReadOnly)) {

        QTextStream in(&file);
        in.setCodec("UTF-8");
        QString line = in.readAll();

        //qDebug() << "line = " << line;


        QVector<uint> utf8 = line.toUcs4();

        unsigned char value;

        for( unsigned int i = 0; i < fileLength; ++i )
        {
            char code = utf8.at(i);
            qDebug() << "1- ASCII code = " << code;


            value = conv_ascii_to_hex(code);
            qDebug() << "2- ASCII code = " << QString("%1").arg(value,0,16);

            qDebug() << " " ;

        }
    }

*/





    /*
    QString filename = "logfile";
    QFile f(filename+".txt");

    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out(&f);
    out << QString("cd \"%1\"\n").arg(QDir::toNativeSeparators(QDir::currentPath()));
    */

    /*
    QString filename = "file";

    auto preparescript = [](QString cmd, QString filename) {
        QFile f(filename+".bat");
        if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) return;
        QTextStream out(&f);

        out << QString("cd \"%1\"\n").arg(QDir::toNativeSeparators(QDir::currentPath()));
        out << cmd;
    };



    auto name  = "Ethernet";
    auto ip  = "192.168.1.7";
    auto mask  = "255.255.255.0";
    auto gateway  = "192.168.1.1";
    QString cmd = QString("netsh interface ip set address name=\"%1\" static %2 %3\n").arg(name,


    preparescript(cmd, filename);

    QProcess p;
    p.start("cmd.exe", {"/C", QString("Powershell Start %1 -Verb Runas").arg(filename+".bat")});
    */


    /*
    QString commandLine;
    char* ipset = "172.30.1.2";
        //localhostIP = "172.30.1.2";;

    commandLine.sprintf(" sudo ifconfig eth0 %s netmask 255.255.255.0 up", ipset);

    QProcess* myPro = new QProcess();
    myPro->start( commandLine );
    myPro-> waitForFinished();


    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
            qDebug() << address.toString();
    }

    QList<QHostAddress> list = QNetworkInterface::allAddresses();

    for(int nIter=0; nIter<list.count(); nIter++)

    {
        if(!list[nIter].isLoopback())
            if (list[nIter].protocol() == QAbstractSocket::IPv4Protocol )
                qDebug() << list[nIter].toString();

    }


    QString localhostname =  QHostInfo::localHostName();
    QString localhostIP;
    QList<QHostAddress> hostList = QHostInfo::fromName(localhostname).addresses();
    foreach (const QHostAddress& address, hostList) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address.isLoopback() == false) {
            localhostIP = address.toString();
        }
    }
    QString localMacAddress;
    QString localNetmask;
    foreach (const QNetworkInterface& networkInterface, QNetworkInterface::allInterfaces()) {
        foreach (const QNetworkAddressEntry& entry, networkInterface.addressEntries()) {
            if (entry.ip().toString() == localhostIP) {
                localMacAddress = networkInterface.hardwareAddress();
                localNetmask = entry.netmask().toString();
                break;
            }
        }
    }
    qDebug() << "Localhost name: " << localhostname;
    qDebug() << "IP = " << localhostIP;
    qDebug() << "MAC = " << localMacAddress;
    qDebug() << "Netmask = " << localNetmask;



    QString setbuff;
    char* ip_buff = "172.30.1.2";
    setbuff.sprintf("ifconfig eth0 %s netmask 255.255.255.0 up",ip_buff);
    qDebug() << setbuff;

    QProcess *qProc = new QProcess(this);

    qProc->start(setbuff);
    qDebug() << setbuff;
    qProc->waitForFinished();
    QString tmp = qProc->readAll();

    QString ip = "172.30.1.2";
    QString cmd = QString("ifconfig eth0 %1 netmask 255.255.255.0 up").arg(ip);


    for(int nIter=0; nIter<list.count(); nIter++)

    {
        if(!list[nIter].isLoopback())
            if (list[nIter].protocol() == QAbstractSocket::IPv4Protocol )
                qDebug() << list[nIter].toString();

    }
    */

    //=======================================================
    // Plot Histogram
    //=======================================================

    // if (Histogram_exist != true){ // Retriggering Mode

        histogram1 = new histogram();
        histogram1->setWindowTitle("Histograms");

        Histogram_exist = false;

        for (int j=0 ; j<95;j++){
            histogram1->y0CB_FullWinChannel[j] = 0;
            histogram1->y0CB_AdjWinChannel[j] = 0;
            histogram1->x0CB_stripFulW[j] = j;
            histogram1->x0CB_stripAdjW[j] = j;

            histogram1->y0LB1_FullWinChannel[j] = 0;
            histogram1->y0LB1_AdjWinChannel[j] = 0;
            histogram1->x0LB1_stripFulW[j] = j;
            histogram1->x0LB1_stripAdjW[j] = j;

            histogram1->y0LB2_FullWinChannel[j] = 0;
            histogram1->y0LB2_AdjWinChannel[j] = 0;
            histogram1->x0LB2_stripFulW[j] = j;
            histogram1->x0LB2_stripAdjW[j] = j;

            histogram1->y0LB3_FullWinChannel[j] = 0;
            histogram1->y0LB3_AdjWinChannel[j] = 0;
            histogram1->x0LB3_stripFulW[j] = j;
            histogram1->x0LB3_stripAdjW[j] = j;

            histogram1->y0LB4_FullWinChannel[j] = 0;
            histogram1->y0LB4_AdjWinChannel[j] = 0;
            histogram1->x0LB4_stripFulW[j] = j;
            histogram1->x0LB4_stripAdjW[j] = j;

            histogram1->y0LB5_FullWinChannel[j] = 0;
            histogram1->y0LB5_AdjWinChannel[j] = 0;
            histogram1->x0LB5_stripFulW[j] = j;
            histogram1->x0LB5_stripAdjW[j] = j;

            histogram1->y0LB6_FullWinChannel[j] = 0;
            histogram1->y0LB6_AdjWinChannel[j] = 0;
            histogram1->x0LB6_stripFulW[j] = j;
            histogram1->x0LB6_stripAdjW[j] = j;

            histogram1->y0LB7_FullWinChannel[j] = 0;
            histogram1->y0LB7_AdjWinChannel[j] = 0;
            histogram1->x0LB7_stripFulW[j] = j;
            histogram1->x0LB7_stripAdjW[j] = j;

            histogram1->y0LB8_FullWinChannel[j] = 0;
            histogram1->y0LB8_AdjWinChannel[j] = 0;
            histogram1->x0LB8_stripFulW[j] = j;
            histogram1->x0LB8_stripAdjW[j] = j;

            histogram1->y0LB9_FullWinChannel[j] = 0;
            histogram1->y0LB9_AdjWinChannel[j] = 0;
            histogram1->x0LB9_stripFulW[j] = j;
            histogram1->x0LB9_stripAdjW[j] = j;

        }

        //histogram1->setupPlot_CB();

        //histogram1->setupPlot_LB(LB1);
        //histogram1->setupPlot_LB(LB2);
        //histogram1->setupPlot_LB(LB3);
        //histogram1->setupPlot_LB(LB4);
        //histogram1->setupPlot_LB(LB5);
        //histogram1->setupPlot_LB(LB6);
        //histogram1->setupPlot_LB(LB7);
        //histogram1->setupPlot_LB(LB8);
        //histogram1->setupPlot_LB(LB9);

        //histogram1->show();
        //Histogram_exist = true;

    //}



    //=======================================================
    // Plot Full window and Adjustable Histogram
    //=======================================================
    //if (REALTimev2_exist != true){ // Retriggering Mode
        //realTime1 = new realTime(this);

        REALtimev2 = new realtimev2 ();

        REALtimev2->setWindowTitle("RealTime RPC Strip Signals");

        REALTimev2_exist = false ;

        for (int j=0 ; j<95;j++){
            REALtimev2->y0CB_FullWinChannel[j] = 0;
            REALtimev2->y0CB_AdjWinChannel[j] = 0;
            REALtimev2->x0CB_stripFulW[j] = j;
            REALtimev2->x0CB_stripAdjW[j] = j;

            REALtimev2->y0LB1_FullWinChannel[j] = 0;
            REALtimev2->y0LB1_AdjWinChannel[j] = 0;
            REALtimev2->x0LB1_stripFulW[j] = j;
            REALtimev2->x0LB1_stripAdjW[j] = j;

            REALtimev2->y0LB2_FullWinChannel[j] = 0;
            REALtimev2->y0LB2_AdjWinChannel[j] = 0;
            REALtimev2->x0LB2_stripFulW[j] = j;
            REALtimev2->x0LB2_stripAdjW[j] = j;

            REALtimev2->y0LB3_FullWinChannel[j] = 0;
            REALtimev2->y0LB3_AdjWinChannel[j] = 0;
            REALtimev2->x0LB3_stripFulW[j] = j;
            REALtimev2->x0LB3_stripAdjW[j] = j;

            REALtimev2->y0LB4_FullWinChannel[j] = 0;
            REALtimev2->y0LB4_AdjWinChannel[j] = 0;
            REALtimev2->x0LB4_stripFulW[j] = j;
            REALtimev2->x0LB4_stripAdjW[j] = j;

            REALtimev2->y0LB5_FullWinChannel[j] = 0;
            REALtimev2->y0LB5_AdjWinChannel[j] = 0;
            REALtimev2->x0LB5_stripFulW[j] = j;
            REALtimev2->x0LB5_stripAdjW[j] = j;

            REALtimev2->y0LB6_FullWinChannel[j] = 0;
            REALtimev2->y0LB6_AdjWinChannel[j] = 0;
            REALtimev2->x0LB6_stripFulW[j] = j;
            REALtimev2->x0LB6_stripAdjW[j] = j;

            REALtimev2->y0LB7_FullWinChannel[j] = 0;
            REALtimev2->y0LB7_AdjWinChannel[j] = 0;
            REALtimev2->x0LB7_stripFulW[j] = j;
            REALtimev2->x0LB7_stripAdjW[j] = j;

            REALtimev2->y0LB8_FullWinChannel[j] = 0;
            REALtimev2->y0LB8_AdjWinChannel[j] = 0;
            REALtimev2->x0LB8_stripFulW[j] = j;
            REALtimev2->x0LB8_stripAdjW[j] = j;

            REALtimev2->y0LB9_FullWinChannel[j] = 0;
            REALtimev2->y0LB9_AdjWinChannel[j] = 0;
            REALtimev2->x0LB9_stripFulW[j] = j;
            REALtimev2->x0LB9_stripAdjW[j] = j;

        }
        //REALtimev2->setupPlot_CB();

        //REALtimev2->setupPlot_LB(LB1);
        //REALtimev2->setupPlot_LB(LB2);
        //REALtimev2->setupPlot_LB(LB3);
        //REALtimev2->setupPlot_LB(LB4);
        //REALtimev2->setupPlot_LB(LB5);
        //REALtimev2->setupPlot_LB(LB6);
        //REALtimev2->setupPlot_LB(LB7);
        //REALtimev2->setupPlot_LB(LB8);
        //REALtimev2->setupPlot_LB(LB9);

        //REALtimev2->show();
        //REALTimev2_exist = true;
    //}



    //=======================================================
    // Plot Timing Profile (timing Histogram)
    //=======================================================

    //if (TimingProfile_exist != true){ // Retriggering Mode
        //realTime1 = new realTime(this);

        TimingProfile1 = new timingprofile();

        TimingProfile1->setWindowTitle("Timing Profile");

        TimingProfile_exist = false;

        for (int j=0 ; j<129;j++){

            TimingProfile1->y0CB_timingHist[j] = 0;
            TimingProfile1->x0CB_BxNum[j] = j;

            TimingProfile1->y0LB1_timingHist[j] = 0;
            TimingProfile1->x0LB1_BxNum[j] = j;

            TimingProfile1->y0LB2_timingHist[j] = 0;
            TimingProfile1->x0LB2_BxNum[j] = j;

            TimingProfile1->y0LB3_timingHist[j] = 0;
            TimingProfile1->x0LB3_BxNum[j] = j;

            TimingProfile1->y0LB4_timingHist[j] = 0;
            TimingProfile1->x0LB4_BxNum[j] = j;

            TimingProfile1->y0LB5_timingHist[j] = 0;
            TimingProfile1->x0LB5_BxNum[j] = j;

            TimingProfile1->y0LB6_timingHist[j] = 0;
            TimingProfile1->x0LB6_BxNum[j] = j;

            TimingProfile1->y0LB7_timingHist[j] = 0;
            TimingProfile1->x0LB7_BxNum[j] = j;

            TimingProfile1->y0LB8_timingHist[j] = 0;
            TimingProfile1->x0LB8_BxNum[j] = j;

            TimingProfile1->y0LB9_timingHist[j] = 0;
            TimingProfile1->x0LB9_BxNum[j] = j;

        }
        //TimingProfile1->setupPlot_CB();

        //TimingProfile1->setupPlot_LB(LB1);
        //TimingProfile1->setupPlot_LB(LB2);
        //TimingProfile1->setupPlot_LB(LB3);
        //TimingProfile1->setupPlot_LB(LB4);
        //TimingProfile1->setupPlot_LB(LB5);
        //TimingProfile1->setupPlot_LB(LB6);
        //TimingProfile1->setupPlot_LB(LB7);
        //TimingProfile1->setupPlot_LB(LB8);
        //TimingProfile1->setupPlot_LB(LB9);

        //TimingProfile1->show();

    //}


    //-------------------------------------
    /*
    unsigned int test_data [4] = {0xD0D0D0D0,
                                  0x44332211,
                                  0xFFFFFFFF,
                                  0x00000004
                                  };
    unsigned char test_char;

    test_char = test_data[1] >>8;

    qDebug() << "1) test_data : " <<  QString("0x%1").arg(test_data[1], 0, 16) ;
    qDebug() << "2) test_char : " <<  QString("0x%1").arg(test_char, 0, 16) ;

    test_char = test_data[1] >>16;
    qDebug() << "1) test_data : " <<  QString("0x%1").arg(test_data[1], 0, 16) ;
    qDebug() << "3) test_char : " <<  QString("0x%1").arg(test_char, 0, 16) ;

    test_char = test_data[1] >>24;
    qDebug() << "1) test_data : " <<  QString("0x%1").arg(test_data[1], 0, 16) ;
    qDebug() << "4) test_char : " <<  QString("0x%1").arg(test_char, 0, 16) ;


    unsigned int board_num = 6;


    test_data[2] &= ~(0x0F << 13);      // "0b11111111111111100001111111111111"
    qDebug() << "5) test_data : " <<  QString("0b%1").arg(test_data[2], 0, 2) ;

    test_data[2] |= (board_num << 13);  //"0b11111111111111100011111111111111"
    qDebug() << "6) test_data : " <<  QString("0b%1").arg(test_data[2], 0, 2) ;

    */

    /*
    // Working with Word, Byte and Logic AND, OR, and  SHIFT instructions

    unsigned int Rec_Reply_t [4] = {0xD0D0D0D0,
                                    0xD0D022F1,
                                    0xAECEFFFF,
                                    0x00000004
                                  };


    unsigned int rw0 , rw1 , rw2 = 0;

    rw0 = Rec_Reply_t [1] ;
    rw0 &= ~(0xffffffc0);

    qDebug() << "1) rw0 : " <<  QString("0x%1").arg(rw0, 0, 16) ;

    rw0 <<= 15 ;
    qDebug() << "2) rw0 : " <<  QString("0x%1").arg(rw0, 0, 16) ;

    rw1 = Rec_Reply_t [2] ;
    rw1 >>= 17 ;

    qDebug() << "3) rw1 : " <<  QString("0x%1").arg(rw1, 0, 16) ;

    rw2 = (rw0) | (rw1);

    qDebug() << "4) rw2 : " <<  QString("0x%1").arg(rw2, 0, 16) ;
    */

}

//==========================================================================
//          Destroy MainWindow
//==========================================================================
MainWindow::~MainWindow()
{
    LanStatus = false;
    m_thread.quit();
    s_thread.quit();
    cb_thread.quit();
    lb_thread.quit();
    rp_thread.quit();
    be_thread.quit();
    be_dpcPlotD_thread.quit();
    be_dpcPlotC_thread.quit();


    YE_TCP_StopSend();
    qDebug() << "10-GetLastWSAError: "<< GetLastWSAError();
    //-----------------------------------------------------------------
    YE_TCP_Disconnect();
    qDebug() << "11-GetLastWSAError: "<< GetLastWSAError();
    //-----------------------------------------------------------------
    qDebug() << "12-Lan Cleanup    : "<< YE_LanCleanup ();
    qDebug() << "======================================================";

    delete ui;
    QApplication::quit();
   // void QCoreApplication::quit() [static slot];

}
//==========================================================================
//          Connect Button
//==========================================================================
void MainWindow::on_Connect_clicked()
{



    //-----------------------------------------------------------------
    YE_LanStartup ();

    //-----------------------------------------------------------------
    QString csIpAddress = ui->lineEdit->text();
    //QString strA(csIpAddress);
    PCSTR pNodeName = csIpAddress.toUtf8();
    //-----------------------------------------------------------------
    LanStatus = YE_TCP_Connect(pNodeName);


    if (LanStatus){

        ui->lineEdit_2->setText(csIpAddress);

        ui->Connect->setDisabled(1);

        ui->ping ->setEnabled(1);
        ui->ReadReg->setEnabled(1);
        ui->WriteReg->setEnabled(1);
        ui->ReadConfig->setEnabled(1);
        ui->WriteConfig->setEnabled(1);
        ui->ReceiveBuffer->setEnabled(1);
        ui->SendBuffer->setEnabled(1);

        this->transaction(); // Run m_thread.transaction(address)
                             // MyThread : Ethernet Receiver

        str += QString("%1\n").arg("=========================");
        str += QString("%1%2\n").arg("1- Ethernet is Connected : ").arg(csIpAddress);
        str += QString("%1\n").arg("=========================");
        ui->textEdit->append(str);

    }
    else
    {
        qDebug() << "======================================================";
        qDebug() << "1- LanSatus       : " << LanStatus;
        qDebug() << "2- GetLastWSAError: " << GetLastWSAError();
        qDebug() << "======================================================";
        str += QString("%1\n").arg("==========================");
        str += QString("%1\n").arg("1- Link Board/Ethernet is not connected");
        str += QString("%1\n").arg("==========================");
        ui->textEdit->append(str);

        QMessageBox::information(this,"Ethernet Status","Link Board or Ethernet is not connected\n Please Check Connection or PC Ethernet Setting");

    }

 }


//==========================================================================
//          Function : transaction()
//==========================================================================

void MainWindow::transaction(){

    //MyThread mThread;
    qDebug() << "======================================================";
    qDebug() << " >> Call Thread";
    USHORT address ;
    address = ui->lineEdit_3->text().toUShort();

    setControlsEnabled(false);
    m_thread.transaction(address);

}

//==========================================================================
//          Ping Button
//==========================================================================

void MainWindow::on_ping_clicked()
{
    DWORD numOfEchoReply;
    char address[16];
    ULONG status;
    ULONG roundTripTime;
    USHORT dataSize;

    QString csIpAddress = ui->lineEdit->text();
    PCSTR pNodeName = csIpAddress.toUtf8() ;

    bool pinStaus = YE_Ping(pNodeName, &numOfEchoReply, address, &status, &roundTripTime, &dataSize);

    str += QString("%1\n").arg("=========================");
    str += QString("%1%2\n").arg("4- Ping status     : ").arg(pinStaus);
    str += QString("%1%2\n").arg("5- NumOfEchoReply  : ").arg(numOfEchoReply);
    str += QString("%1%2\n").arg("6- Address         : ").arg(address);
    str += QString("%1%2\n").arg("7- Status          : ").arg(status);
    str += QString("%1%2\n").arg("8- RoundTripTime   : ").arg(roundTripTime);
    str += QString("%1%2\n").arg("9- DataSize        : ").arg(dataSize);
    str += QString("%1\n").arg("=========================");
    ui->textEdit->append(str);
}



//==========================================================================
//          Exit Button
//==========================================================================
void MainWindow::on_pushButton_clicked()
{

  m_thread.quit();
  s_thread.quit();
  YE_TCP_Disconnect ();
  YE_LanCleanup();
  QApplication::quit();
}


//==========================================================================
//          Opne Second Window
//==========================================================================
void MainWindow::on_pushButton_2_clicked()
{
    //hide();
    //secDialog1 = new secDialog(this);
    //secDialog1 -> show();


    //secDialog secDialog;
    //secDialog.setModal(true);
    //secDialog.exec();

    backendhitplot->BeHistPlotter(RPCHist);
    backendhitplot->show();
    backendhitplot->update();


}

//==========================================================================
//          Function : Read Ethernet Register
//==========================================================================
void MainWindow::on_ReadReg_clicked()
{
    unsigned int regValue , regAdr;

    qDebug() << "======================================================";
    qDebug() << " >> Read Register";
    qDebug() << " >> LAN status = "<<LanStatus ;
    USHORT address ;
    address = ui->lineEdit_3->text().toUShort();

    bool ReadReg_status = YE_TCP_ReadReg(address);

    if (LanStatus){
        //this->transaction();

        if (!ReadReg_status)
        {
          str += QString("%1\n").arg("=========================");
          str += QString("%1\n").arg(">> Read Reg ERROR");
          str += QString("%1\n").arg("=========================");
        }
        else
        {

           str += QString("%1\n").arg("=========================");
           str += QString("%1\n").arg(">> Read Reg OK");

           regAdr = m_thread.t_address;
           regValue = m_thread.t_value;

           str += QString("15-Register at Address (%1) = %2\n").arg(regAdr).arg(regValue);
           str += QString("%1\n").arg("=========================");

           ui->textEdit->append(str);


           str1 = QString("%1").arg(m_thread.t_value);
           ui->lineEdit_4->setText(str1);
           qDebug()<<  "m_thread.t_value" << m_thread.t_value;
        }
    }
}

//==========================================================================
//          Function : Write to the Ethernt Register
//==========================================================================
void MainWindow::on_WriteReg_clicked()
{
    qDebug() << "======================================================";
    qDebug() << " >> Write Register";
    qDebug() << " >> LAN status = "<<LanStatus ;

    USHORT address ;
    address = ui->lineEdit_3->text().toUShort();

    USHORT value ;
    value = ui->lineEdit_4->text().toUShort();

    if (LanStatus){
        bool WriteReg_status = YE_TCP_WriteReg(address, value);
        //this->transaction();

        if (!WriteReg_status)
        {
          str += QString("%1\n").arg("=========================");
          str += QString("%1\n").arg(">> Write Reg ERROR");
          str += QString("%1\n").arg("=========================");
        }
        else
        {

           str += QString("%1\n").arg("=========================");
           str += QString("%1\n").arg(">> Write Reg OK");

           str += QString("15-Register at Address (%1) = %2\n").arg(m_thread.t_address).arg(m_thread.t_value);
           str += QString("%1\n").arg("=========================");
           ui->textEdit->append(str);

           str1 = QString("%1").arg(m_thread.t_value);
           ui->lineEdit_4->setText(str1);
        }
    }
}

//==========================================================================
//          Function : Read Configuration Register
//==========================================================================

void MainWindow::on_ReadConfig_clicked()
{
    qDebug() << "======================================================";
    qDebug() << " >> Read Configuration Register";
    qDebug() << " >> LAN status = "<<LanStatus ;
    USHORT address ;
    address = ui->lineEdit_5->text().toUShort();

    bool retVal = YE_TCP_ReadConfig(address);

    if (LanStatus){
        //this->transaction();

        if (!retVal)
        {
          str += QString("%1\n").arg("=========================");
          str += QString("%1\n").arg(">> Read Configuration Reg ERROR");
          str += QString("%1\n").arg("=========================");
        }
        else
        {

           str += QString("%1\n").arg("=========================");
           str += QString("%1\n").arg(">> Read Configuration Reg OK");

           str += QString("15-Register at Address (%1) = %2\n").arg(m_thread.t_address).arg(m_thread.t_value);
           str += QString("%1\n").arg("=========================");
           ui->textEdit->append(str);

           str1 = QString("%1").arg(m_thread.t_value);
           ui->lineEdit_6->setText(str1);
        }
    }
}

//==========================================================================
//          Function : Error Callback of Received Thread
//==========================================================================

void MainWindow::processError(const QString &s)
{

}

//==========================================================================
//          Function : Timeout Callback of Received Thread
//==========================================================================

void MainWindow::processTimeout(const QString &s)
{

}

//==========================================================================
//          Function :
//==========================================================================

void MainWindow::setControlsEnabled(bool enable)
{
    enable =true ;
    //m_runButton->setEnabled(enable);
    //m_serialPortComboBox->setEnabled(enable);
    //m_waitResponseSpinBox->setEnabled(enable);
    //m_requestLineEdit->setEnabled(enable);
}

//==========================================================================
//
//==========================================================================
void MainWindow::WriteConfig(UCHAR address, UINT value)
{

    retVal = YE_TCP_WriteConfig(address, value);

    if (!retVal)
    {
        str += QString("%1 %2\n").arg("Error in Write Config").arg(GetLastWSAError());
        ui->textEdit->append(str);
    }

    //return retVal;
}
//==========================================================================
//          Function : Write into the Ethernet Register
//==========================================================================

void MainWindow::WriteReg(USHORT address, UINT value)
{

    retVal = YE_TCP_WriteReg(address, value);

    if (!retVal)
    {
        str += QString("%1 %2\n").arg("Error in Write Register").arg(GetLastWSAError());
        ui->textEdit->append(str);
    }
    //return retVal;
}


//==========================================================================
//          Function : Received Burst of Packet from Ethernet
//==========================================================================

void MainWindow::on_ReceiveBuffer_clicked()
{

    //ui->ReceiveBuffer->setDisabled(1);

    UINT iAsRateControl = 0x00u;

    receiveBufSize = ui->lineEdit_8->text().toUInt(); // Get the received buffer size

    //m_thread.t_receiveBuf = (unsigned char*) malloc(receiveBufSize); // Set the thread received buffer size

    memset(m_thread.t_receiveBuf, 0, receiveBufSize); // Set thread received buffers with 0s

    m_thread.t_receiveBufSize = receiveBufSize;
    m_thread.t_receiveBufIndex = 0 ;
    m_thread.t_buffer_full = 0 ;
    m_thread.t_receivedBuf = 0 ;


    qDebug() << "======================================================";
    qDebug() << "   RECEIVE BUFFER--";
    qDebug() << "   SET RECEIVE BUFFER SIZE TO = " << receiveBufSize ;
    qDebug() << "======================================================";

    m_thread.on_receive = true ;

    WriteReg(0x01, iAsRateControl); // (Address , Value) Request to Link Board for sending the BURST data
    WriteConfig(0x00, 0x02u);       // (Address , Value) AutoSend pin enable


    unsigned int address = 4 ;
    UINT value = receiveBufSize * 65536 ; // set the length of send packet ;
    WriteConfig(address, value); // write


}

//==========================================================================
//          Function : Send Burst of Packet to Ethernet
//==========================================================================
void MainWindow::on_SendBuffer_clicked()
{
    USHORT address ;
    QString text;
    QByteArray text_qba;

    QString file_name;
    //QFile file ;

    address = ui->lineEdit_3->text().toUShort();

    if (ui->checkBox_1->isChecked())  // Locate file from windows browser
    {
        QString filter = "MCS File (*.mcs) ;; Text File (*.txt) ;; All File (*.*) ";
        file_name = QFileDialog::getOpenFileName(this,"Open a File", "C:\\",filter);
        QFile file(file_name);
        //--------------------------------------------------------
        if (!file.open(QFile::ReadOnly| QFile::Text)){
            QMessageBox::information(this,"title", "file not open");
        }
        else
        {
            QTextStream in(&file);
            text = in.readAll() ;
            fileLength = text.size();
            qDebug() << "fileLength =" << fileLength ;
            file.close();
        }
        //--------------------------------------------------------
        sendBuf = (char*)malloc(fileLength); // char *sendBuf;
        memset(sendBuf, 0, fileLength);
        //--------------------------------------------------------

        if (!file.open(QFile::ReadOnly| QFile::Text))
        {
            QMessageBox::information(this,"title", "file not open");
        }
        else
        {
            char file_data;
            QString string;
            uint64_t file_counter=0;

            while (!file.atEnd()){
                file.read(&file_data,sizeof(char));
                string.append(file_data);
                sendBuf[file_counter] = file_data;
                //qDebug() << "file_data" << file_data ;
                file_counter++;
            }
            qDebug() << "Total number of Characters =" << file_counter ;
            file.close();

        }
        //---------------------------------------------------------
        // push sendBuf buffer to the buffer of the Send Thread (s_thread.t_sendBuf)
        //---------------------------------------------------------

        s_thread.t_sendBuf = (char*)malloc(fileLength); // Create a buffer, char *sendBuf;
        memset(s_thread.t_sendBuf, 0, fileLength);      // Set all element to zero

        memcpy(s_thread.t_sendBuf,sendBuf,fileLength);  // Copy current buffer to the thread buffer
        //---------------------------------------------------------
        s_thread.t_text = text;
        s_thread.t_fileLength = fileLength;            // Send size of buffer to the thread
        //---------------------------------------------------------
        /*
        for (long long j=0; j<fileLength ;j++ )
        {
          qDebug() << " sendBuf " << j << "="<< sendBuf[j] << "s_thread.t_sendBuf " << j << "="<< s_thread.t_sendBuf[j];
        }*/
        //---------------------------------------------------------

    }
    else // Send default counter value to the Ethernet as a test file
    {
        fileLength = ui->lineEdit_7->text().toUInt(); // Get the received buffer size
        //fileLength = 10;

        //--------------------------------------------------------
        sendBuf = (char*)malloc(fileLength); // char *sendBuf;
        memset(sendBuf, 0, fileLength);
        //--------------------------------------------------------

        for (UINT64 i=0 ; i <fileLength ; i++)
        {
           sendBuf[i] = i;
        }

        //---------------------------------------------------------
        // push sendBuf buffer to the buffer of the Send Thread (s_thread.t_sendBuf)
        //---------------------------------------------------------

        s_thread.t_sendBuf = (char*)malloc(fileLength); // Create a buffer, char *sendBuf;
        memset(s_thread.t_sendBuf, 0, fileLength);      // Set all element to zero

        memcpy(s_thread.t_sendBuf,sendBuf,fileLength);  // Copy current buffer to the thread buffer
        //---------------------------------------------------------
        s_thread.t_text = text;
        s_thread.t_fileLength = fileLength;             // Send size of buffer to the thread
        //---------------------------------------------------------

        /*
        for (long long j=0; j<fileLength ;j++ )
        {
          qDebug() << " sendBuf " << j << "="<< sendBuf[j] << "s_thread.t_sendBuf " << j << "="<< s_thread.t_sendBuf[j];

        }*/
    }

    //---------------------------------------------------------
    //if (ui->checkBox_4->isChecked()) // check if copy check box is checked
    //ui->plainTextEdit->setPlainText(text); // Copy content of file to the PlainText box

    qDebug() << "File Size =" << fileLength;
    str += QString("%1\n").arg("=========================");
    str += QString("1-File Characters = %1\n").arg(fileLength); // Number of File lines
    str += QString("2-File Lines = %1\n").arg(fileLength/9);    // Number of Characters
    str += QString("%1\n").arg("=========================");
    ui->textEdit->append(str);
    //---------------------------------------------------------
    if (ui->checkBox_3->isChecked()) // check if repeat check box is checked
    {
        s_thread.t_repeatSend = true;
    }
    else
    {
        s_thread.t_repeatSend = false;
    }
    //---------------------------------------------------------
    WriteConfig(0x00, 0x01u);   // Prepare Ethernt for Send packets

    s_thread.transaction_send(address); // Call Transaction funtion of the Thread

}


//==========================================================================
//          Function : Acknowledge function of the Receive Thread
//==========================================================================
void MainWindow::ThreadSlot_showResponse( UINT rec_complete )//, boolean Buffer_full )
{

    qDebug() << "         " ;
    qDebug() << "ThreadSlot_showResponse()" ;

    uint i , j , stringCnt ;

    if (packet_cnt == 499){packet_cnt=0;}

    packet_cnt++;

    m_thread.on_receive = true ;

    stringCnt++;

    if (stringCnt >= 5){
        //====================
        str = QString("");
        str.clear();
        ui->textEdit->clear();
        //====================
        stringCnt = 0 ;
    }


    //qDebug() << "  ReceBufferSizeY =" << rec_complete;
    //qDebug() << "  receiveBufSize =" << receiveBufSize;

    //=============================================================
    if (rec_complete == receiveBufSize){
            for ( i=0,j=0  ; i<rec_complete;){

                Rec_Reply[j][packet_cnt-1] = ((m_thread.t_receiveBuf[i][packet_cnt-1])<<24)|
                                               ((m_thread.t_receiveBuf[i+1][packet_cnt-1])<<16)|
                                               ((m_thread.t_receiveBuf[i+2][packet_cnt-1])<<8)|
                                               ((m_thread.t_receiveBuf[i+3][packet_cnt-1]));
                //out << QString("Word [%1][%2]= 0x%3\n").arg(j).arg(packet_cnt-1).arg(Rec_Reply[j][packet_cnt-1],0,16, QLatin1Char(' '));

                //qDebug() << "Word [%1][%2]= 0x%3 " << ii << "packet_cnt = " << packet_cnt<< " w2 =" << QString("0x%1").arg(w2, 0, 16);
                //qDebug() << "Word[" << j <<  "][" << packet_cnt-1 <<"] = " <<  QString("0x%1").arg(Rec_Reply[j][packet_cnt-1], 0, 16) ;
                i = i + 4;
                j++;
            }

            //----------------------------------------------
            // Run cmd process
            //----------------------------------------------
            if (ui->ChBX_freeRunLog->isChecked()== false){ // Normal run
                cmd_process (packet_cnt-1 , rec_complete/4); // n = packet_cnt
                //qDebug() << "ui->ch_Sem_En->isChecked()= false" ;
                //qDebug() << "NORMAL RUN" ;
            }
        }
    //=============================================================

    /*
    if (rec_complete == receiveBufSize)
    {

        ui->textEdit->clear();
        //str += QString("ReceBufferSizeX = %1\n").arg(rec_complete);

        if (ui->checkBox_2->isChecked()) // Save file
        {
            QString filter = "All File (*.*) ;; Text File (*.txt) ;; CSV File (*.csv)";
            QString file_name = QFileDialog::getOpenFileName(this,"Open a File", "C:\\",filter);
            QFile file(file_name);
            if (!file.open(QFile::WriteOnly| QFile::Text)){
                QMessageBox::information(this,"title", "file not open");
            }
            QTextStream out(&file);
            QString text ;
            for (uint i=0;i<rec_complete;i++){
                out << "Char "<< i << " ="<< m_thread.t_receiveBuf[i]<<"\n";
                str += QString("Char [%1]= %2\n").arg(i).arg(m_thread.t_receiveBuf[i][packet_cnt-1]);
                ui->textEdit->append(str); //<< Display
            }
            file.flush();
            file.close();
         }
         else // don't save file
         {
            //------------------------------------------------------------------
            if (ui->ChBx_LogString->isChecked()){
                str += QString("\n%1\n").arg("=========================");
                str += QString("Received Packet=%1    Number of Byte=%2\n").arg(packet_cnt).arg(rec_complete);
                str += QString("%1").arg("=========================");

                for ( i=0;i<rec_complete;i++){
                   str += QString("\nChar [%1]= 0x%2").arg(i).arg(m_thread.t_receiveBuf[i][packet_cnt-1],0,16, QLatin1Char(' ')) ;
                   //SEM_Reply [i] = m_thread.t_receiveBuf[i][packet_cnt-1];
                   }
                //------------------------------------------------------------------
                str += QString("\n");
                //------------------------------------------------------------------
            }
            //------------------------------------------------------------------

            for ( i=0,j=0  ; i<rec_complete;){

                Rec_Reply[j][packet_cnt-1] = ((m_thread.t_receiveBuf[i][packet_cnt-1])<<24)|
                                             ((m_thread.t_receiveBuf[i+1][packet_cnt-1])<<16)|
                                             ((m_thread.t_receiveBuf[i+2][packet_cnt-1])<<8)|
                                             ((m_thread.t_receiveBuf[i+3][packet_cnt-1]));
                    if (ui->ChBx_LogString->isChecked()){
                        str += QString("Word [%1][%2]= 0x%3\n").arg(j).arg(packet_cnt-1).arg(Rec_Reply[j][packet_cnt-1],0,16, QLatin1Char(' ')) ;
                    }

                    if (ui->ChBX_freeRunLog->isChecked()){
                        out << QString("Word [%1][%2]= 0x%3\n").arg(j).arg(packet_cnt-1).arg(Rec_Reply[j][packet_cnt-1],0,16, QLatin1Char(' '));
                    }
                i = i + 4;
                j++;
            }
            */
            //------------------------------------------------------------------



            //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            //  Check the SEM enable check box
            //  If not, run Normal Routine otherwise run the SEM routine
            //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            /*
            if (ui->ChBX_freeRunLog->isChecked()== false){ // Normal run
                     (packet_cnt-1 , rec_complete/4); // n = packet_cnt
                    qDebug() << "ui->ch_Sem_En->isChecked()= false" ;
                    qDebug() << "NORMAL RUN" ;
            }*/



        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        //  Check the SEM enable check box
        //  If yes, run the SEM routine
        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        if (ui->ch_Sem_En->isChecked()== true){ // SEM run

            SemCnt++;
            str3 = "" ;
            //------------------------------------------------
            str3 += QString("\n %1").arg("=========================");
            str3 += QString("\n %1%2%3").arg("No.").arg(SemCnt).arg(" - Clock :");
            str3+= TimeText;
            str3 += QString("\n %1").arg(" SEM REPORT ");
            str3 += QString("\n ");
            //------------------------------------------------
            for ( i=0;i<rec_complete;i++){
               //str2 += QString("\n SEM Byte[%1]= 0x%2").arg(i).arg(m_thread.t_receiveBuf[i][packet_cnt-1],0,16, QLatin1Char(' ')) ;
               SEM_Reply [i] = m_thread.t_receiveBuf[i][packet_cnt-1];
               //SemCmdText += QString("\n %1").arg(toascii (SEM_Reply[i])) ;
               str3 += toascii (SEM_Reply[i]) ;
               }

            //------------------------------------------------------
            // First - Read Content of the File
            //------------------------------------------------------

            QFile file ("C:\\LinkSystemSEM.txt");
            if (!file.open(QFile::ReadOnly |QFile::Text)){
                str3 += QString("\n %1").arg("=========================");
                str3 += QString("\n %1").arg("FAIL IN READ FILE - FILE NOT OPEN");
                str3 += QString("\n %1").arg("=========================");
            }
            QTextStream in(&file);

            //QString tempText1 = in.readAll(); // NOTE, TempText earas first and fills with new data
                                     // Because += does not use here

            QString tempText1 = in.readAll();

            file.flush();
            file.close();

            //------------------------------------------------------
            // Second - Write log data to the the File
            //------------------------------------------------------

            QFile file2 ("C:\\LinkSystemSEM.txt");
            if (!file2.open(QFile::WriteOnly |QFile::Text)){
                str3 += QString("\n %1").arg("=========================");
                str3 += QString("\n %1").arg("FAIL IN WRITE FILE - FILE NOT OPEN");
                str3 += QString("\n %1").arg("=========================");
            }
            QTextStream out(&file2);


            tempText1 += str3;
            out << tempText1 ;

            //str2 += tempText1;
            ui->plainTextEdit->clear();
            ui->plainTextEdit->appendPlainText(tempText1);

            file2.flush();
            file2.close();
            //-------------------------------------------------------
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

            packet_cnt = 0 ;
            m_thread.packetCount = 0 ;
            qDebug() << "ui->ch_Sem_En->isChecked()= true" ;
        }
        //=======================================================================


    //qDebug() << "Received Packet = " << packet_cnt ;
    //ui->textEdit->append(str); //<< Display

}

//==========================================================================
//          Function : Respond to the commands
//                     In a normal routine after receiving a new data, this function is callbacked.
//==========================================================================
void MainWindow::cmd_process(UINT32 packet_cnt , UINT32 rec_word_buf ){

    unsigned int ii = 0 ;
    unsigned int w1 , w2 , w3, w4;



    if (ui->ChBx_BS_BEB->isChecked() == true){
        qDebug() << "BackendProcess " ;
        BackendProcess( rec_word_buf , packet_cnt);

    }

    for (ii=0 ; ii <rec_word_buf ; ){

        qDebug() << "cmd_process () " ;
        qDebug() << "packet_cnt = " << packet_cnt ;
        qDebug() << "rec_word_buf = " << rec_word_buf ;

        w1 = Rec_Reply[ii+0][packet_cnt] ;
        w2 = Rec_Reply[ii+1][packet_cnt] ;
        w3 = Rec_Reply[ii+2][packet_cnt] ;
        w4 = Rec_Reply[ii+3][packet_cnt] ;

        if (w1 == 0xD0D0D0D0){
            qDebug() << "ii = " << ii << "packet_cnt =" << packet_cnt;
            qDebug() << " w1 =" << QString("0x%1").arg(w1, 0, 16);
            qDebug() << " w2 =" << QString("0x%1").arg(w2, 0, 16);
            qDebug() << " w3 =" << QString("0x%1").arg(w3, 0, 16);
            qDebug() << " w4 =" << QString("0x%1").arg(w4, 0, 16);


            cb_lb = Rec_Reply[ii+1][packet_cnt]; // check if input frame is for link board
            cb_lb = cb_lb << 18;
            cb_lb = cb_lb >> 31;

            if (cb_lb == 0 ) {
                cb_cmd_process (packet_cnt);
            }
            else {
                lb_cmd_process (ii , packet_cnt);
            }
        }
        else{
            qDebug() << "Frame Header Wrong " ;
        }

        cb_lb = Rec_Reply[ii+1][packet_cnt]; // check if input frame is for link board
        cb_lb = cb_lb << 18;
        cb_lb = cb_lb >> 31;



        //------------------------------------------------------------------
        if (ui->ChBx_LogString->isChecked()){
            if (cb_lb == 0 ) {str += QString("\n -= CB Command =- \n");}
            else {str += QString("\n -= LB Command =- \n");}
            str += QString("%1\n").arg("=========================");
        }
        //------------------------------------------------------------------

        ii+=4 ;
        //---------------------------------
    }
}










//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



//==========================================================================
//          Function : Respond to the commands
//==========================================================================
void MainWindow::lb_cmd_process(UINT32 frame_index , UINT32 packet_cnt  ){


    //qDebug() << "LB Received Packet No. =: " << packet_cnt << "Frame No. =: " << frame_index ;


    lb_number = Rec_Reply[frame_index+2][packet_cnt]; // find link board number in input frame
    lb_number = lb_number << 15;
    lb_number = lb_number >> 28;
    qDebug() << "Link Board No. : " << lb_number;

    instruction_code = Rec_Reply[frame_index+1][packet_cnt]; // find out instruction
    instruction_code = instruction_code << 19;
    instruction_code = instruction_code >> 27;
    qDebug() << "instruction_code =  " << instruction_code;

    //#################################################################
    if (instruction_code == 1) // if instruction is : get LB parameters
    {
        ADC_channel = Rec_Reply[frame_index+2][packet_cnt];
        ADC_channel = ADC_channel << 23;
        ADC_channel = ADC_channel >> 29;

        ADG_MUX_selector = Rec_Reply[frame_index+2][packet_cnt];
        ADG_MUX_selector = ADG_MUX_selector << 19;
        ADG_MUX_selector = ADG_MUX_selector >> 28;

        data_1 = Rec_Reply[frame_index+2][packet_cnt];
        data_1 = data_1 << 26;
        data_1 = data_1 >> 22;

        data_2 = Rec_Reply[frame_index+3][packet_cnt]; //receive_buffer[i + 3];
        data_2 = data_2 >> 28;

        data = data_1 + data_2;



        if (ADC_channel == 0)
        {
            adc_value = data * 0.25;

            QString str_LB1_Temp_ADC = QString("%1  'C").arg(adc_value);
            ui->lineEdit_LB1_Temp_ADC->setText(str_LB1_Temp_ADC);

            //printf(" ADC Temperature is: %.3f C\n", adc_value);
            qDebug() << "LB1 ADC Temperature is: " << adc_value << "C";
        }
        if (ADC_channel == 2)
        {
            adc_value = data * 2.44;
            adc_value = adc_value - 500;
            adc_value = adc_value / 10;

            QString str_LB1_Temp_Sensor4 = QString("%1  'C").arg(adc_value);
            //ui->lineEdit_LB1_Temp_Sensor4->setText(str_LB1_Temp_Sensor4);

            //printf(" Temperature sensor 4 is: %.3f C\n", adc_value);
            qDebug() << "Temperature sensor No.4 : " << adc_value << "C";

        }
        if (ADC_channel == 3)
        {
            adc_value = data * 2.44;

            QString str_LB1_ADC_AVDD_2 = QString("%1  mV").arg(adc_value);
            ui->lineEdit_LB1_ADC_AVDD_2->setText(str_LB1_ADC_AVDD_2);

            qDebug() <<  "LB1 AVDD / 2 : " << adc_value << " mV" ; //printf(" AVDD / 2 is: %.3f mV\n", adc_value);
        }
        if (ADC_channel == 4)
        {
            //printf(" ground voltage is: %d\n", data);
            adc_value = data * 2.44;

            QString str_LB1_ADC_GND = QString("%1  mV").arg(adc_value);
            ui->lineEdit_LB1_ADC_GND->setText(str_LB1_ADC_GND);

            //printf(" ground voltage is: %.3f mV\n", adc_value);
            qDebug() <<  "LB1 Ground Voltage : " << adc_value << " mV" ;
        }
        if (ADC_channel == 1)
        {
            if (ADG_MUX_selector == 0)
            {
                adc_value = data * 2.44;
                //printf(" +1.0 volt VDD is: %.3f mV\n", adc_value);

                QString str_LB1_1V = QString("%1  mV").arg(adc_value);
                ui->lineEdit_LB1_1V->setText(str_LB1_1V);

                qDebug() << "+1.0 volt VDD is: " << adc_value << " mV" ;

            }
            if (ADG_MUX_selector == 1)
            {
                adc_value = data * 2.44;
                //printf(" +1.8 volt AUX is: %.3f mV\n", adc_value);
                QString str_LB1_1V8_Aux = QString("%1  mV").arg(adc_value);
                ui->lineEdit_LB1_1V8_Aux->setText(str_LB1_1V8_Aux);

                qDebug() <<  " +1.8 volt AUX : " << adc_value << " mV" ;
            }
            if (ADG_MUX_selector == 2)
            {
                adc_value = data * 2.44;

                QString str_LB1_1V_MGTAVCC = QString("%1  mV").arg(adc_value);
                ui->lineEdit_LB1_1V_MGTAVCC->setText(str_LB1_1V_MGTAVCC);

                //printf(" +1.0 volt MGTAVCC is: %.3f mV\n", adc_value);
                qDebug() <<  " +1.0 volt MGTAVCC : " << adc_value << " mV" ;
            }
            if (ADG_MUX_selector == 3)
            {
                adc_value = data * 2.44;

                QString str_LB1_1V_MGTAVTT = QString("%1  mV").arg(adc_value);
                ui->lineEdit_LB1_1V_MGTAVTT->setText(str_LB1_1V_MGTAVTT);

                //printf(" +1.0 volt MGTAVTT is: %.3f mV\n", adc_value);
                qDebug() <<  " +1.0 volt MGTAVTT : " << adc_value << " mV" ;
            }
            if (ADG_MUX_selector == 4)
            {
                adc_value = data * 2.44;

                QString str_LB1_1V8_MGTVCCAUX = QString("%1  mV").arg(adc_value);
                ui->lineEdit_LB1_1V8_MGTVCCAUX->setText(str_LB1_1V8_MGTVCCAUX);

                //printf(" +1.8 volt MGTVCCAUX is: %.3f mV\n", adc_value);
                qDebug() <<  " +1.8 volt MGTVCCAUX : " << adc_value << " mV" ;
            }
            if (ADG_MUX_selector == 5)
            {
                adc_value = data * 2.44;

                QString str_LB1_1V8 = QString("%1  mV").arg(adc_value);
                ui->lineEdit_LB1_1V8->setText(str_LB1_1V8);

                //printf(" +1.8 volt is: %.3f mV\n", adc_value);
                qDebug() <<  " +1.8 volt : " << adc_value << " mV" ;
            }
            if (ADG_MUX_selector == 6)
            {
                adc_value = data * 2.44;

                QString str_LB1_1V5 = QString("%1  mV").arg(adc_value);
                ui->lineEdit_LB1_1V5->setText(str_LB1_1V5);

                //printf(" +1.5 volt is: %.3f mV\n", adc_value);
                qDebug() <<  " +1.5 volt : " << adc_value << " mV" ;
            }
            if (ADG_MUX_selector == 7)
            {
                adc_value = data * 2.44;

                QString str_LB1_3V3 = QString("%1  mV").arg(adc_value);
                ui->lineEdit_LB1_3V3->setText(str_LB1_3V3);

                //printf(" +3.3 volt is: %.3f mV\n", adc_value);
                qDebug() <<  " +3.3 volt : " << adc_value << " mV" ;
            }
            if (ADG_MUX_selector == 8)
            {
                adc_value = data * 2.44;

                QString str_LB1_2V5 = QString("%1  mV").arg(adc_value);
                ui->lineEdit_LB1_2V5->setText(str_LB1_2V5);

                //printf(" +2.5 volt is: %.3f mV\n", adc_value);
                qDebug() <<  " +2.5 volt : " << adc_value << " mV" ;
            }
            if (ADG_MUX_selector == 9)
            {
                adc_value = data * 2.44;

                QString str_LB1_3V3VDD = QString("%1  mV").arg(adc_value);
                ui->lineEdit_LB1_3V3VDD->setText(str_LB1_3V3VDD);

                //printf(" +3.3 volt VDD is: %.3f mV\n", adc_value);
                qDebug() <<  " +3.3 VDD : " << adc_value << " mV" ;
            }
            if (ADG_MUX_selector == 10)
            {
                adc_value = data * 2.44;
                adc_value = adc_value - 500;
                adc_value = adc_value / 10;

                QString str_LB1_Temp_Sensor1 = QString("%1  'C").arg(adc_value);
                ui->lineEdit_LB1_Temp_Sensor1->setText(str_LB1_Temp_Sensor1);

                //printf(" Temperature sensor 1 is: %.3f C\n", adc_value);
                qDebug() << "Temperature sensor No.1 : " << adc_value << "C";
            }
            if (ADG_MUX_selector == 11)
            {
                adc_value = data * 2.44;
                adc_value = adc_value - 500;
                adc_value = adc_value / 10;

                QString str_LB1_Temp_Sensor2 = QString("%1  'C").arg(adc_value);
                ui->lineEdit_LB1_Temp_Sensor2->setText(str_LB1_Temp_Sensor2);

                //printf(" Temperature sensor 2 is: %.3f C\n", adc_value);
                qDebug() << "Temperature sensor No.2 : " << adc_value << "C";
            }
            if (ADG_MUX_selector == 12)
            {
                adc_value = data * 2.44;
                adc_value = adc_value - 500;
                adc_value = adc_value / 10;

                QString str_LB1_Temp_Sensor3 = QString("%1  'C").arg(adc_value);
                ui->lineEdit_LB1_Temp_Sensor3->setText(str_LB1_Temp_Sensor3);

                //printf(" Temperature sensor 3 is: %.3f C\n", adc_value);
                qDebug() << "Temperature sensor No.3 : " << adc_value << "C";
            }
            if (ADG_MUX_selector == 13)
            {
                adc_value = data * 2.44;

                QString str_LB1_CS1_Vout = QString("%1  mV").arg(adc_value);
                ui->lineEdit_LB1_CS1_Vout->setText(str_LB1_CS1_Vout);

                //printf(" CS1 VOUT is: %.3f mV\n", adc_value);
                qDebug() << "LB1 CS1 VOUT : " << adc_value << "mV";
            }
            if (ADG_MUX_selector == 14)
            {
                adc_value = data * 2.44;

                QString str_LB1_CS2_Vout = QString("%1  mV").arg(adc_value);
                ui->lineEdit_LB1_CS2_Vout->setText(str_LB1_CS2_Vout);

                //printf(" CS2 VOUT is: %.3f mV\n", adc_value);
                qDebug() << "LB1 CS2 VOUT : " << adc_value << "mV";
            }
            if (ADG_MUX_selector == 15)
            {
                adc_value = data * 2.44;

                QString str_LB1_CS3_Vout = QString("%1  mV").arg(adc_value);
                ui->lineEdit_LB1_CS3_Vout->setText(str_LB1_CS3_Vout);

                //printf(" CS3 VOUT is: %.3f mV\n", adc_value);
                qDebug() << "LB1 CS3 VOUT : " << adc_value << "mV";
            }
        }
        //                      printf("\n");
    }

    //#################################################################
    else if (instruction_code == 2) // if instruction is : get LB diagnastic
    {
        diagnostic_instruction_code = Rec_Reply[frame_index+2][packet_cnt]; //receive_buffer[i + 2];
        diagnostic_instruction_code = diagnostic_instruction_code << 19;
        diagnostic_instruction_code = diagnostic_instruction_code >> 28;
        //printf(" diagnostic_instruction_code = (%d)" , diagnostic_instruction_code);
        qDebug() << " diagnostic_instruction_code = " << diagnostic_instruction_code;

        if (diagnostic_instruction_code == 1) // select test signal
        {
            test_sig_number = Rec_Reply[frame_index+2][packet_cnt] ; //receive_buffer[i + 2];
            test_sig_number = test_sig_number << 23;
            test_sig_number = test_sig_number >> 27;

            QString str_LB1_TestSig = QString("Test Pattern Signal %1 of 23").arg(test_sig_number);
            ui->lineEdit_LB1_TestSig->setText(str_LB1_TestSig);

            //printf(" Test signal number (%d) has been chosen\n", test_sig_number);
            qDebug() << "Test signal number " << test_sig_number << " has been chosen\n";

        }
        if (diagnostic_instruction_code == 2) // turn on or off test pattern generator
        {
            test_sig_on_off = Rec_Reply[frame_index+2][packet_cnt] ; //receive_buffer[i + 2];
            test_sig_on_off = test_sig_on_off << 23;
            test_sig_on_off = test_sig_on_off >> 31;
            if (test_sig_on_off == 1)
            {
                printf(" Test pattern generator turned On\n");
            }
            if (test_sig_on_off == 0)
            {
                printf(" Test pattern generator turned Off\n");
            }
        }

        if (diagnostic_instruction_code == 3) // set open window and close window
        {

            if(ui->ChBx_LB1_FullWin->isChecked()) {

                open_window_value = Rec_Reply[frame_index+2][packet_cnt] ; //receive_buffer[i + 2];
                open_window_value = open_window_value << 23;
                open_window_value = open_window_value >> 28;

                QString str_LB1_FullWin = QString(" %1").arg(open_window_value);
                ui->lineEdit_LB1_FullWin->setText(str_LB1_FullWin);
                qDebug() << " Full window = " << open_window_value ;
            }

            if(ui->ChBx_LB1_AdjWin->isChecked()) {

                close_window_value = Rec_Reply[frame_index+2][packet_cnt] ; //receive_buffer[i + 2];
                close_window_value = close_window_value << 27;
                close_window_value = close_window_value >> 28;

                QString str_LB1_AdjlWin = QString(" %1").arg(close_window_value);
                ui->lineEdit_LB1_AdjWin->setText(str_LB1_AdjlWin);
                qDebug() << " Adjustable window = " << close_window_value ;
            }
        }

        if (diagnostic_instruction_code == 8) // disable one TDC
        {
            tdc_number_to_turn_off = Rec_Reply[frame_index+2][packet_cnt] ; //receive_buffer[i + 2];
            tdc_number_to_turn_off = tdc_number_to_turn_off << 23;
            tdc_number_to_turn_off = tdc_number_to_turn_off >> 25;
            printf(" TDC number %d is disabled\n", tdc_number_to_turn_off);
        }


        if (diagnostic_instruction_code == 12) // read mccs
        {

            switch (mccs_status){

                case mccs_read_PacketSize :

                    rw0 = Rec_Reply [frame_index+1][packet_cnt] ;
                    rw0 &= ~(0xffffffc0);
                    rw0 <<= 15 ;

                    rw1 = Rec_Reply [frame_index+2][packet_cnt] ;
                    rw1 >>= 17 ;

                    rw2 = (rw0) | (rw1);

                    mccs_pack_cnt = rw2 ;
                    qDebug() << "max mccs packet counter = " << mccs_pack_cnt;

                    mccs_total_pack_size = mccs_pack_cnt ;
                    if (mccs_total_pack_size!= 0){
                        mccs_status = mccs_read_BunchCounter ; // Go to the next state

                        LBN = 1 ;
                        currentPackNum = 0 ;
                        ProgressBarUpdate (t_histogram , LBN ,currentPackNum , mccs_total_pack_size );

                    }
                    else{
                        mccs_status = mccs_read_PacketSize ;
                    }


                break;

                case mccs_read_BunchCounter :
                    //------------------------------------------------
                    //  Get Packet Number
                    //------------------------------------------------
                    rw0 = Rec_Reply [frame_index+1][packet_cnt] ;
                    rw0 &= ~(0xffffffc0);
                    rw0 <<= 15 ;

                    rw1 = Rec_Reply [frame_index+2][packet_cnt] ;
                    rw1 >>= 17 ;

                    rw2 = (rw0) | (rw1);
                    mccs_pack_cnt = rw2 ;
                    qDebug() << "mccs packet counter = " << mccs_pack_cnt;
                    ProgressBarUpdate (t_histogram , LBN ,mccs_pack_cnt , mccs_total_pack_size );
                    //------------------------------------------------

                    //------------------------------------------------
                    //  Get Bunch Counter Number
                    //------------------------------------------------
                    rw3 = 0 ;
                    rw3 = Rec_Reply [frame_index+3][packet_cnt] ;
                    rw3 >>= 5 ;

                    rw2 = 0 ;
                    rw2 = Rec_Reply [frame_index+2][packet_cnt] ;
                    rw2 <<=27 ;

                    rw0 = 0 ;
                    rw0 = (rw2) | (rw3);
                    bunch_counter_value = rw0 ;
                    qDebug() << "BUNCH COUNTER = " << bunch_counter_value;


                    //------------------------------------------------
                    FW_Cnter = 0 ;
                    AdW_Cnter = 0 ;
                    //------------------------------------------------
                    mccs_status = mccs_read_FullWin ; // Go to the next state
                break;


                case mccs_read_FullWin :
                    //------------------------------------------------
                    //  Get Packet Number
                    //------------------------------------------------
                    rw0 = 0 ;
                    rw1 = 0 ;
                    rw2 = 0 ;

                    rw0 = Rec_Reply [frame_index+1][packet_cnt] ;
                    rw0 &= ~(0xffffffc0);
                    rw0 <<= 15 ;

                    rw1 = Rec_Reply [frame_index+2][packet_cnt] ;
                    rw1 >>= 17 ;

                    rw2 = (rw0) | (rw1);
                    mccs_pack_cnt = rw2 ;

                    qDebug() << "mccs packet counter = " << mccs_pack_cnt;
                    ProgressBarUpdate (t_histogram , LBN ,mccs_pack_cnt , mccs_total_pack_size );
                    //------------------------------------------------


                    //------------------------------------------------
                    //  Get 96 full-window Multi-Channel-Counters
                    //------------------------------------------------
                    rw3 = 0 ;
                    rw3 = Rec_Reply [frame_index+3][packet_cnt] ;
                    rw3 >>= 5 ;

                    rw2 = 0 ;
                    rw2 = Rec_Reply [frame_index+2][packet_cnt] ;
                    rw2 <<=27 ;

                    rw0 = 0 ;
                    rw0 = (rw2) | (rw3);

                    FullWinChannel[FW_Cnter] = rw0 ;
                    qDebug() << QString ("FullWinChannel[%1] = %2") .arg(FW_Cnter).arg(FullWinChannel[FW_Cnter]);
                    //------------------------------------------------

                    if (FW_Cnter < 95) {
                        histogram1-> x0LB1_stripFulW[FW_Cnter] = (unsigned int)FW_Cnter ;
                        histogram1-> y0LB1_FullWinChannel[FW_Cnter] = (unsigned int)FullWinChannel[FW_Cnter] ;

                        histogram1->setupPlot_LB(LB1); // PLOT HISTOGRAM - FULL WINDOW
                        FW_Cnter++ ;
                    }
                    else{

                       FW_Cnter = 0 ;
                       AdW_Cnter = 0 ;
                       mccs_status = mccs_read_AdjWin ; // Go to the next state
                    }

                    //------------------------------------------------

                break;

                case mccs_read_AdjWin :

                    //------------------------------------------------
                    //  Get Packet Number
                    //------------------------------------------------
                    rw0 = 0 ;
                    rw1 = 0 ;
                    rw2 = 0 ;

                    rw0 = Rec_Reply [frame_index+1][packet_cnt] ;
                    rw0 &= ~(0xffffffc0);
                    rw0 <<= 15 ;

                    rw1 = Rec_Reply [frame_index+2][packet_cnt] ;
                    rw1 >>= 17 ;

                    rw2 = (rw0) | (rw1);
                    mccs_pack_cnt = rw2 ;
                    qDebug() << "mccs packet counter = " << mccs_pack_cnt;
                    ProgressBarUpdate (t_histogram , LBN ,mccs_pack_cnt , mccs_total_pack_size );
                    //------------------------------------------------

                    //------------------------------------------------
                    //  Get 96 Adj-window Multi-Channel-Counters
                    //------------------------------------------------
                    rw3 = 0 ;
                    rw3 = Rec_Reply [frame_index+3][packet_cnt] ;
                    rw3 >>= 5 ;

                    rw2 = 0 ;
                    rw2 = Rec_Reply [frame_index+2][packet_cnt] ;
                    rw2 <<=27 ;

                    rw0 = 0 ;
                    rw0 = (rw2) | (rw3);

                    AdjWinChannel[AdW_Cnter] = rw0 ;
                    qDebug() << QString ("AdjWinChannel[%1] = %2") .arg(AdW_Cnter).arg(AdjWinChannel[AdW_Cnter]);
                    //------------------------------------------------

                    if (AdW_Cnter < 95) {

                      histogram1-> x0LB1_stripAdjW[AdW_Cnter] =  (unsigned int)AdW_Cnter ;
                      histogram1-> y0LB1_AdjWinChannel[AdW_Cnter] =  (unsigned int)AdjWinChannel[AdW_Cnter] ;
                      histogram1->setupPlot_LB(LB1); // PLOT HISTOGRAM - ADJUSTABLE WINDOW

                      AdW_Cnter++ ;
                    }
                    else{

                       mccs_pack_cnt-- ;
                       ProgressBarUpdate (t_histogram , LBN ,mccs_pack_cnt , mccs_total_pack_size );

                       if (Histogram_exist != true){
                           histogram1->show();
                           Histogram_exist = true;
                       }

                       FW_Cnter = 0 ;
                       AdW_Cnter = 0 ;
                       mccs_status = mccs_read_PacketSize ; // Go to the next state
                    }

                break;

                default:

                break;
            }

        }
        if (diagnostic_instruction_code == 13) // read timming histogram
        {


            switch (timingHst_status){

                case timingHst_read_PacketSize :

                    rw0 = Rec_Reply [frame_index+1][packet_cnt] ;
                    rw0 &= ~(0xffffffc0);
                    rw0 <<= 15 ;

                    rw1 = Rec_Reply [frame_index+2][packet_cnt] ;
                    rw1 >>= 17 ;

                    rw2 = (rw0) | (rw1);

                    timingHst_pack_cnt = rw2 ;

                    qDebug() << "1) timingHst packet counter = " << timingHst_pack_cnt;


                    timingHst_total_pack_size = timingHst_pack_cnt ;
                    if (timingHst_total_pack_size!= 1){

                        LBN = 1 ;
                        ProgressBarUpdate (t_timing , LBN ,timingHst_pack_cnt , timingHst_total_pack_size );

                        timingHst_status = timingHst_read_BunchCounter ; // Go to the next state
                        BxCnt = 0 ;
                    }
                    else{
                        timingHst_status = timingHst_read_PacketSize ;
                    }


                break;

                case timingHst_read_BunchCounter :
                    //------------------------------------------------
                    //  Get Packet Number
                    //------------------------------------------------
                    rw0 = Rec_Reply [frame_index+1][packet_cnt] ;
                    rw0 &= ~(0xffffffc0);
                    rw0 <<= 15 ;

                    rw1 = Rec_Reply [frame_index+2][packet_cnt] ;
                    rw1 >>= 17 ;

                    rw2 = (rw0) | (rw1);
                    timingHst_pack_cnt = rw2 ;
                    qDebug() << "2) timingHst packet counter = " << timingHst_pack_cnt;
                    ProgressBarUpdate (t_timing , LBN ,timingHst_pack_cnt , timingHst_total_pack_size );

                    //------------------------------------------------

                    //------------------------------------------------
                    //  Get Bunch Counter Number
                    //------------------------------------------------
                    rw3 = 0 ;
                    rw3 = Rec_Reply [frame_index+3][packet_cnt] ;
                    rw3 >>= 5 ;

                    rw2 = 0 ;
                    rw2 = Rec_Reply [frame_index+2][packet_cnt] ;
                    rw2 <<=27 ;

                    rw0 = 0 ;
                    rw0 = (rw2) | (rw3);
                    bunch_counter_value = rw0 ;
                    qDebug() << "BUNCH COUNTER = " << bunch_counter_value;
                    //------------------------------------------------
                    FW_Cnter = 0 ;
                    AdW_Cnter = 0 ;
                    //------------------------------------------------
                    timingHst_status = timingHst_read_BunchData ; // Go to the next state
                break;


                case timingHst_read_BunchData :
                    //------------------------------------------------
                    //  Get Packet Number
                    //------------------------------------------------
                    rw0 = 0 ;
                    rw1 = 0 ;
                    rw2 = 0 ;

                    rw0 = Rec_Reply [frame_index+1][packet_cnt] ;
                    rw0 &= ~(0xffffffc0);
                    rw0 <<= 15 ;

                    rw1 = Rec_Reply [frame_index+2][packet_cnt] ;
                    rw1 >>= 17 ;

                    rw2 = (rw0) | (rw1);
                    timingHst_pack_cnt = rw2 ;
                    qDebug() << "3) timingHst packet counter = " << timingHst_pack_cnt;
                    ProgressBarUpdate (t_timing , LBN ,timingHst_pack_cnt , timingHst_total_pack_size );

                    //------------------------------------------------


                    //------------------------------------------------
                    //  Get 128 Bunchs of Bunch Crossing Data
                    //------------------------------------------------
                    rw3 = 0 ;
                    rw3 = Rec_Reply [frame_index+3][packet_cnt] ;
                    rw3 >>= 5 ;

                    rw2 = 0 ;
                    rw2 = Rec_Reply [frame_index+2][packet_cnt] ;
                    rw2 <<=27 ;

                    rw0 = 0 ;
                    rw0 = (rw2) | (rw3);

                    BunchCrossData[BxCnt] = rw0 ;
                    qDebug() << QString ("  BunchCrosse[%1 + %2] = %3").arg(bunch_counter_value).arg(BxCnt).arg(BunchCrossData[BxCnt]);
                    //------------------------------------------------

                    if (BxCnt < 127) {
                      BxCnt++ ;
                    }
                    else{

                        LBN = 1 ;
                        timingProfilePlot(LBN ,bunch_counter_value );// Plot

                       mccs_status = timingHst_read_PacketSize ; // Go to the next state
                    }

                    //------------------------------------------------

                break;

                default:

                break;
            }

        }
        if (diagnostic_instruction_code == 14) // read loging fifo
        {

            switch (dataLog_status){

                case dataLog_read_PacketSize :

                    rw0 = Rec_Reply [frame_index+1][packet_cnt] ;
                    rw0 &= ~(0xffffffc0);
                    rw0 <<= 15 ;

                    rw1 = Rec_Reply [frame_index+2][packet_cnt] ;
                    rw1 >>= 17 ;

                    rw2 = (rw0) | (rw1);

                    dataLog_pack_cnt = rw2 ;
                    qDebug() << "1 ) dataLog packet counter = " << dataLog_pack_cnt;

                    dataLog_total_pack_size = dataLog_pack_cnt ;
                    if (dataLog_total_pack_size!= 0){
                        dataLog_status = dataLog_read_BunchCounter ; // Go to the next state

                        LBN = 1 ;
                        dataLog_pack_cnt = 0 ;
                        ProgressBarUpdate (t_dataLog , LBN ,dataLog_pack_cnt , dataLog_total_pack_size );

                    }
                    else{
                        dataLog_status = dataLog_read_PacketSize ;
                    }


                break;

                case dataLog_read_BunchCounter :
                    //------------------------------------------------
                    //  Get Packet Number
                    //------------------------------------------------
                    rw0 = Rec_Reply [frame_index+1][packet_cnt] ;
                    rw0 &= ~(0xffffffc0);
                    rw0 <<= 15 ;

                    rw1 = Rec_Reply [frame_index+2][packet_cnt] ;
                    rw1 >>= 17 ;

                    rw2 = (rw0) | (rw1);
                    mccs_pack_cnt = rw2 ;
                    qDebug() << "dataLog packet counter = " << dataLog_pack_cnt;
                    ProgressBarUpdate (t_dataLog , LBN ,dataLog_pack_cnt , dataLog_total_pack_size );

                    //------------------------------------------------

                    //dataLog[96][130]; // [strip][sub-bx]

                    stripCnt = 0 ;  // 1-96
                    subBxCnt = 0 ; // 1 - 129
                    LineCnt = 0 ; // 1 - 16
                    //------------------------------------------------
                    //  Get Bunch Counter Number
                    //------------------------------------------------
                    rw3 = 0 ;
                    rw3 = Rec_Reply [frame_index+3][packet_cnt] ;
                    rw3 >>= 5 ;

                    rw2 = 0 ;
                    rw2 = Rec_Reply [frame_index+2][packet_cnt] ;
                    rw2 <<=27 ;

                    rw0 = 0 ;
                    rw0 = (rw2) | (rw3);
                    bunch_counter_value = rw0 ;
                    qDebug() << "BUNCH COUNTER = " << bunch_counter_value;
                    //realtimev2 -> BxCntVal = bunch_counter_value;
                    //------------------------------------------------

                    //------------------------------------------------
                    dataLog_status = dataLog_read_Channels ; // Go to the next state
                break;


                case dataLog_read_Channels :
                    //------------------------------------------------
                    //  Get Packet Number
                    //------------------------------------------------
                    rw0 = 0 ;
                    rw1 = 0 ;
                    rw2 = 0 ;

                    rw0 = Rec_Reply [frame_index+1][packet_cnt] ;
                    rw0 &= ~(0xffffffc0);
                    rw0 <<= 15 ;

                    rw1 = Rec_Reply [frame_index+2][packet_cnt] ;
                    rw1 >>= 17 ;

                    rw2 = (rw0) | (rw1);
                    dataLog_pack_cnt = rw2 ;
                    //qDebug() << "A - dataLog packet counter = " << dataLog_pack_cnt;
                    ProgressBarUpdate (t_dataLog , LBN ,dataLog_pack_cnt , dataLog_total_pack_size );

                    //------------------------------------------------


                    //------------------------------------------------
                    //  Get 96 full-window Multi-Channel-Counters
                    //------------------------------------------------
                    rw0 = 0 ;
                    rw1 = 0 ;

                    rw0 = Rec_Reply[frame_index+2][packet_cnt] ; // Sub-bx0
                    rw0 >>= 3 ;
                    rw1 = rw0 ;
                    rw1 &= 0x0f; // Data 4-bit

                    rw0 >>= 4 ;
                    rw0 &= 0x01; // Valid  1-bit

                    //dataLog[96][130]; // [strip][sub-bx]
                    dataLog [stripCnt+0][subBxCnt]  = rw1 ;
                    //qDebug() << QString ("A - dataLog [%1] [%2] = %3  , Valid = %4").arg(stripCnt).arg(subBxCnt).arg(rw1).arg(rw0);
                    //------------------------------------------------


                    rw0 = 0 ;
                    rw1 = 0 ;

                    rw0 = Rec_Reply [frame_index+3][packet_cnt] ; // Sub-bx1
                    rw0 >>= 29 ;

                    rw1 = Rec_Reply [frame_index+2][packet_cnt] ; // Sub-bx1
                    rw1 &= 0x07 ;
                    rw1 <<= 3 ;
                    rw1 = rw1 | rw0 ; // Data is ready   <0/valid/sub-bx>

                    rw0 = rw1 ;
                    rw0 >>= 4 ;
                    rw0 &= 0x01;  //valid

                    rw1 &= 0x0f;  // sub-bx1

                    //dataLog[96][130]; // [strip][sub-bx]
                    dataLog [stripCnt+1][subBxCnt]  = rw1 ;
                    //qDebug() << QString ("A - dataLog [%1] [%2] = %3  , Valid = %4").arg(stripCnt+1).arg(subBxCnt).arg(rw1).arg(rw0);

                    //------------------------------------------------
                    rw0 = 0 ;
                    rw1 = 0 ;

                    rw0 = Rec_Reply [frame_index+3][packet_cnt] ; // Sub-bx2
                    rw0 >>= 23 ;
                    rw1 = rw0 ;

                    rw1 &= 0x0f; // Data 4-bit (sub-bx2)

                    rw0 >>= 4 ;
                    rw0 &= 0x01; // Valid  1-bit

                    //dataLog[96][130]; // [strip][sub-bx]
                    dataLog [stripCnt+2][subBxCnt]  = rw1 ;
                    //qDebug() << QString ("A - dataLog [%1] [%2] = %3  , Valid = %4").arg(stripCnt+2).arg(subBxCnt).arg(rw1).arg(rw0);

                    //------------------------------------------------

                    rw0 = 0 ;
                    rw1 = 0 ;

                    rw0 = Rec_Reply [frame_index+3][packet_cnt] ; // Sub-bx3
                    rw0 >>= 17 ;
                    rw1 = rw0 ;

                    rw1 &= 0x0f; // Data 4-bit (sub-bx3)

                    rw0 >>= 4 ;
                    rw0 &= 0x01; // Valid  1-bit

                    //dataLog[96][130]; // [strip][sub-bx]
                    dataLog [stripCnt+3][subBxCnt]  = rw1 ;
                    //qDebug() << QString ("A - dataLog [%1] [%2] = %3  , Valid = %4").arg(stripCnt+3).arg(subBxCnt).arg(rw1).arg(rw0);

                    //------------------------------------------------


                    rw0 = 0 ;
                    rw1 = 0 ;

                    rw0 = Rec_Reply [frame_index+3][packet_cnt] ; // Sub-bx4
                    rw0 >>= 11 ;
                    rw1 = rw0 ;

                    rw1 &= 0x0f; // Data 4-bit (sub-bx4)

                    rw0 >>= 4 ;
                    rw0 &= 0x01; // Valid  1-bit

                    //dataLog[96][130]; // [strip][sub-bx]
                    dataLog [stripCnt+4][subBxCnt]  = rw1 ;
                    //qDebug() << QString ("A - dataLog [%1] [%2] = %3  , Valid = %4").arg(stripCnt+4).arg(subBxCnt).arg(rw1).arg(rw0);

                    //------------------------------------------------
                    rw0 = 0 ;
                    rw1 = 0 ;

                    rw0 = Rec_Reply [frame_index+3][packet_cnt] ; // Sub-bx5
                    rw0 >>= 5 ;
                    rw1 = rw0 ;

                    rw1 &= 0x0f; // Data 4-bit (sub-bx5)

                    rw0 >>= 4 ;
                    rw0 &= 0x01; // Valid  1-bit

                    //dataLog[96][130]; // [strip][sub-bx]
                    dataLog [stripCnt+5][subBxCnt]  = rw1 ;
                    //qDebug() << QString ("A - dataLog [%1] [%2] = %3  , Valid = %4").arg(stripCnt+5).arg(subBxCnt).arg(rw1).arg(rw0);

                    //------------------------------------------------

                    LineCnt = LineCnt + 1 ;
                    //qDebug() << QString ("A - LineCnt = %1").arg(LineCnt);

                    if (LineCnt < 16) {
                       stripCnt += 6;
                    }else{
                            LineCnt = 0 ;
                            stripCnt = 0 ;

                        if (subBxCnt <128){
                            subBxCnt++ ;
                            dataLog_status = dataLog_read_Channels ; // Go to the next state
                        }
                        else{

                            LineCnt = 0 ;
                            stripCnt = 0 ;
                            subBxCnt = 0 ;

                            dataLog_status = dataLog_read_PacketSize ; // Go to the next state
                            LBN = 1 ;
                            realTimePlot(LBN ,bunch_counter_value );// Plot
                        }
                    }

                    /*
                    if (subBxCnt < 129) {
                      subBxCnt++ ;
                    }
                    else{
                       subBxCnt = 0 ;
                       stripCnt = stripCnt + 6;


                       //qDebug() << QString ("subBxCnt = [%1], stripCnt = [%2], LineCnt = [%3]").arg(subBxCnt).arg(stripCnt).arg(LineCnt);

                       if (LineCnt <16){
                        dataLog_status = dataLog_read_Channels ; // Go to the next state
                       }else{
                          dataLog_status = dataLog_read_PacketSize ; // Go to the next state
                          realTimePlot(LBN);// Plot
                       }

                    }*/

                    //------------------------------------------------

                break;

                default:

                break;
            }


        }
    }

    //#################################################################
    else if (instruction_code == 3) // if instruction is : get LB firmware ID
    {
        qDebug() << " Firmware ID is: " ;

        data_1 = Rec_Reply[2][packet_cnt] ;  //receive_buffer[i + 2];
        data_2 = Rec_Reply[3][packet_cnt] ;  //receive_buffer[i + 3];
        data_1 = data_1 << 30;
        data_2 = data_2 >> 2;
        data = data_1 + data_2;
        //printf("%08X \n", data);

        QString str_LB1_ID_Number = QString(" %1").arg(data);
        ui->lineEdit_LB1_ID_Number->setText(str_LB1_ID_Number);


        qDebug() << "Link Board No.1 Firmware ID: " << data ;


    }
    //#################################################################

    //#################################################################
    else if (instruction_code == 5) // if instruction is 5 : get LB Clock Deskew
    {
        data_1 = Rec_Reply[2][packet_cnt] ;  //receive_buffer[i + 2];
        data_1 &= (0xFFC);
        data_1 >>= 2 ;

        QString str_LB1_ClkDeskew = QString(" %1").arg(data_1);
        ui->lineEdit_LB1_ClkDesk->setText(str_LB1_ClkDeskew);

        qDebug() << "Link Board No.1 Clock Deskew =  " << data_1 ;

    }

}
//==============================================================================
//
//==============================================================================

void MainWindow ::ProgressBarUpdate(unsigned int l_histType, unsigned int l_LBN , float l_currentPackNum , float l_maxPackNum){

    float l_percent;
    l_percent = ((l_maxPackNum - l_currentPackNum) / l_maxPackNum) * 100 ;

    if (l_histType == t_histogram) {
    switch (l_LBN){

        case LB1:
            ui->LB1_ProgBarHist->setValue(l_percent);
        break;

        case LB2:
            ui->LB2_ProgBarHist->setValue(l_percent);
        break;

        case LB3:
            ui->LB3_ProgBarHist->setValue(l_percent);
        break;

        case LB4:
            ui->LB4_ProgBarHist->setValue(l_percent);
        break;


        case LB5:
            ui->LB5_ProgBarHist->setValue(l_percent);
        break;

        case LB6:
            ui->LB6_ProgBarHist->setValue(l_percent);
        break;

        case LB7:
            ui->LB7_ProgBarHist->setValue(l_percent);
        break;

        case LB8:
            ui->LB8_ProgBarHist->setValue(l_percent);
        break;

        case LB9:
            ui->LB9_ProgBarHist_2->setValue(l_percent);
        break;
        }
    }else if (l_histType == t_timing) {

        switch (LBN){

            case LB1:
                ui->LB1_ProgTim->setValue(l_percent);
            break;

            case LB2:
                ui->LB2_ProgTim->setValue(l_percent);
            break;

            case LB3:
                ui->LB3_ProgTim->setValue(l_percent);
            break;

            case LB4:
                ui->LB4_ProgTim->setValue(l_percent);
            break;


            case LB5:
                ui->LB5_ProgTim->setValue(l_percent);
            break;

            case LB6:
                ui->LB6_ProgTim->setValue(l_percent);
            break;

            case LB7:
                ui->LB7_ProgTim->setValue(l_percent);
            break;

            case LB8:
                ui->LB8_ProgTim->setValue(l_percent);
            break;

            case LB9:
                ui->LB9_ProgTim->setValue(l_percent);
            break;
            }

    }else if (l_histType == t_dataLog) {

        switch (LBN){

            case LB1:
                ui->LB1_ProgDataLog->setValue(l_percent);

            break;

            case LB2:
                ui->LB2_ProgDataLog->setValue(l_percent);
            break;

            case LB3:
                ui->LB3_ProgDataLog->setValue(l_percent);
            break;

            case LB4:
                ui->LB4_ProgDataLog->setValue(l_percent);
            break;


            case LB5:
                ui->LB5_ProgDataLog->setValue(l_percent);
            break;

            case LB6:
                ui->LB6_ProgDataLog->setValue(l_percent);
            break;

            case LB7:
                ui->LB7_ProgDataLog->setValue(l_percent);
            break;

            case LB8:
                ui->LB8_ProgDataLog->setValue(l_percent);
            break;

            case LB9:
                ui->LB9_ProgDataLog->setValue(l_percent);
            break;
            }
    }

}






//==============================================================================
//
//==============================================================================
void MainWindow::realTimePlot(unsigned int LBN , unsigned int bunch_counter_value){


    switch (LBN){

    case LB1:
        //----------------------------------------------------------
        for (int j=0 ; j<129;j++){

            for (int i=0 ; i<96 ; i++) {
                //REALtimev2-> y0CB_StripData [i][j] = dataLog [i][j] ;
                REALtimev2-> y0LB1_StripData [i][j] = dataLog [i][j] ;
             }
        }

        REALtimev2-> BxCntVal = bunch_counter_value;
        REALtimev2->setupPlot_LB(LB1);

        if (REALTimev2_exist != true){
            REALtimev2->show();
            REALTimev2_exist = true;
        }
        //----------------------------------------------------------
    break;

    case LB2:
        //----------------------------------------------------------
        for (int j=0 ; j<129;j++){

            for (int i=0 ; i<96 ; i++) {
                REALtimev2-> y0LB2_StripData [i][j] = dataLog [i][j] ;
             }
        }

        REALtimev2-> BxCntVal = bunch_counter_value;
        REALtimev2->setupPlot_LB(LB2);

        if (REALTimev2_exist!= true){
            REALtimev2->show();
            REALTimev2_exist = true;
        }
        //----------------------------------------------------------
    break;

    case LB3:
        //----------------------------------------------------------
        for (int j=0 ; j<129;j++){

            for (int i=0 ; i<96 ; i++) {
                REALtimev2-> y0LB3_StripData [i][j] = dataLog [i][j] ;
             }
        }

        REALtimev2-> BxCntVal = bunch_counter_value;
        REALtimev2->setupPlot_LB(LB3);

        if (REALTimev2_exist!= true){
            REALtimev2->show();
            REALTimev2_exist = true;
        }

        //----------------------------------------------------------
    break;

    case LB4:
        //----------------------------------------------------------
        for (int j=0 ; j<129;j++){

            for (int i=0 ; i<96 ; i++) {
                REALtimev2-> y0LB4_StripData [i][j] = dataLog [i][j] ;
             }
        }

        REALtimev2-> BxCntVal = bunch_counter_value;
        REALtimev2->setupPlot_LB(LB4);

        if (REALTimev2_exist!= true){
            REALtimev2->show();
            REALTimev2_exist = true;
        }

        //----------------------------------------------------------
    break;

    case LB5:
        //----------------------------------------------------------
        for (int j=0 ; j<129;j++){

            for (int i=0 ; i<96 ; i++) {
                REALtimev2-> y0LB5_StripData [i][j] = dataLog [i][j] ;
             }
        }

        REALtimev2-> BxCntVal = bunch_counter_value;
        REALtimev2->setupPlot_LB(LB5);

        if (REALTimev2_exist!= true){
            REALtimev2->show();
            REALTimev2_exist = true;
        }

        //----------------------------------------------------------
    break;

    case LB6:
        //----------------------------------------------------------
        for (int j=0 ; j<129;j++){

            for (int i=0 ; i<96 ; i++) {
                REALtimev2-> y0LB6_StripData [i][j] = dataLog [i][j] ;
             }
        }

        REALtimev2-> BxCntVal = bunch_counter_value;
        REALtimev2->setupPlot_LB(LB6);

        if (REALTimev2_exist!= true){
            REALtimev2->show();
            REALTimev2_exist = true;
        }

        //----------------------------------------------------------
    break;

    case LB7:
        //----------------------------------------------------------
        for (int j=0 ; j<129;j++){

            for (int i=0 ; i<96 ; i++) {
                REALtimev2-> y0LB7_StripData [i][j] = dataLog [i][j] ;
             }
        }

        REALtimev2-> BxCntVal = bunch_counter_value;
        REALtimev2->setupPlot_LB(LB7);

        if (REALTimev2_exist!= true){
            REALtimev2->show();
            REALTimev2_exist = true;
        }

        //----------------------------------------------------------
    break;

    case LB8:
        //----------------------------------------------------------
        for (int j=0 ; j<129;j++){

            for (int i=0 ; i<96 ; i++) {
                REALtimev2-> y0LB8_StripData [i][j] = dataLog [i][j] ;
             }
        }

        REALtimev2-> BxCntVal = bunch_counter_value;
        REALtimev2->setupPlot_LB(LB8);

        if (REALTimev2_exist!= true){
            REALtimev2->show();
            REALTimev2_exist = true;
        }

        //----------------------------------------------------------
    break;

    case LB9:
        //----------------------------------------------------------
        for (int j=0 ; j<129;j++){

            for (int i=0 ; i<96 ; i++) {
                REALtimev2-> y0LB9_StripData [i][j] = dataLog [i][j] ;
             }
        }

        REALtimev2-> BxCntVal = bunch_counter_value;
        REALtimev2->setupPlot_LB(LB9);

        if (REALTimev2_exist!= true){
            REALtimev2->show();
            REALTimev2_exist = true;
        }

        //----------------------------------------------------------
    break;

    }

}



//==========================================================================
//          Function : plot timing profile
//          inputs : 1) Link Board Number
//                   2) Current Bunch Crossing Number
//==========================================================================

void MainWindow::timingProfilePlot (unsigned int LBN , unsigned int bunch_counter_value )
{

    switch (LBN){

    case LB1:
        //---------------------------------------------------------------
        for (int j=0 ; j<129;j++){

            TimingProfile1 -> y0LB1_timingHist[j] = BunchCrossData[j];
        }

        TimingProfile1-> BxCntVal = bunch_counter_value;
        TimingProfile1->setupPlot_LB(LB1);

        if (TimingProfile_exist!= true){

            TimingProfile1->show();
          TimingProfile_exist = true ;
        }

        //---------------------------------------------------------------
    break;

    case LB2:
        //---------------------------------------------------------------
        for (int j=0 ; j<129;j++){

            TimingProfile1 -> y0LB2_timingHist[j] = BunchCrossData[j];
        }

        TimingProfile1-> BxCntVal = bunch_counter_value;
        TimingProfile1->setupPlot_LB(LB2);

        if (TimingProfile_exist!= true){
          TimingProfile1->show();
          TimingProfile_exist = true ;
        }

        //---------------------------------------------------------------
    break;

    case LB3:
        //---------------------------------------------------------------
        for (int j=0 ; j<129;j++){

            TimingProfile1 -> y0LB3_timingHist[j] = BunchCrossData[j];
        }

        TimingProfile1-> BxCntVal = bunch_counter_value;
        TimingProfile1->setupPlot_LB(LB3);

        if (TimingProfile_exist!= true){
          TimingProfile1->show();
          TimingProfile_exist = true ;
        }

        //---------------------------------------------------------------

    break;

    case LB4:
        //---------------------------------------------------------------
        for (int j=0 ; j<129;j++){

            TimingProfile1 -> y0LB4_timingHist[j] = BunchCrossData[j];
        }

        TimingProfile1-> BxCntVal = bunch_counter_value;
        TimingProfile1->setupPlot_LB(LB4);

        if (TimingProfile_exist!= true){
          TimingProfile1->show();
          TimingProfile_exist = true ;
        }

        //---------------------------------------------------------------
    break;

    case LB5:
        //---------------------------------------------------------------
        for (int j=0 ; j<129;j++){

            TimingProfile1 -> y0LB5_timingHist[j] = BunchCrossData[j];
        }

        TimingProfile1-> BxCntVal = bunch_counter_value;
        TimingProfile1->setupPlot_LB(LB5);

        if (TimingProfile_exist!= true){
          TimingProfile1->show();
          TimingProfile_exist = true ;
        }

        //---------------------------------------------------------------
    break;

    case LB6:
        //---------------------------------------------------------------
        for (int j=0 ; j<129;j++){

            TimingProfile1 -> y0LB6_timingHist[j] = BunchCrossData[j];
        }

        TimingProfile1-> BxCntVal = bunch_counter_value;
        TimingProfile1->setupPlot_LB(LB6);

        if (TimingProfile_exist!= true){
          TimingProfile1->show();
          TimingProfile_exist = true ;
        }

        //---------------------------------------------------------------
    break;

    case LB7:
        //---------------------------------------------------------------
        for (int j=0 ; j<129;j++){

            TimingProfile1 -> y0LB7_timingHist[j] = BunchCrossData[j];
        }

        TimingProfile1-> BxCntVal = bunch_counter_value;
        TimingProfile1->setupPlot_LB(LB7);

        if (TimingProfile_exist!= true){
          TimingProfile1->show();
          TimingProfile_exist = true ;
        }

        //---------------------------------------------------------------
    break;

    case LB8:
        //---------------------------------------------------------------
        for (int j=0 ; j<129;j++){

            TimingProfile1 -> y0LB8_timingHist[j] = BunchCrossData[j];
        }

        TimingProfile1-> BxCntVal = bunch_counter_value;
        TimingProfile1->setupPlot_LB(LB8);

        if (TimingProfile_exist!= true){
          TimingProfile1->show();
          TimingProfile_exist = true ;
        }

        //---------------------------------------------------------------
    break;

    case LB9:
        //---------------------------------------------------------------
        for (int j=0 ; j<129;j++){

            TimingProfile1 -> y0LB9_timingHist[j] = BunchCrossData[j];
        }

        TimingProfile1-> BxCntVal = bunch_counter_value;
        TimingProfile1->setupPlot_LB(LB9);

        if (TimingProfile_exist!= true){
          TimingProfile1->show();
          TimingProfile_exist = true ;
        }

        //---------------------------------------------------------------
    break;

    }

}

//==========================================================================
//          Function : Respond to the commands
//==========================================================================
void MainWindow::cb_cmd_process(UINT32 packet_cnt ){


    instruction_code = Rec_Reply[1][packet_cnt]; // find out instruction
    instruction_code = instruction_code << 19;
    instruction_code = instruction_code >> 27;
    qDebug() << "         " ;
    qDebug() << "cb_cmd_process() " ;
    qDebug() << "packet_cnt = " << packet_cnt ;
    //#################################################################
    if (instruction_code == 1) // if instruction is : get CB parameters
    {
        qDebug() << "Control Board CMD = " << packet_cnt ;

        ADC_channel = Rec_Reply[2][packet_cnt];
        ADC_channel = ADC_channel << 23;
        ADC_channel = ADC_channel >> 29;
        qDebug() << "ADC_channel = " << ADC_channel ;

        ADG_MUX_selector = Rec_Reply[2][packet_cnt];
        ADG_MUX_selector = ADG_MUX_selector << 19;
        ADG_MUX_selector = ADG_MUX_selector >> 28;
        qDebug() << "ADG_MUX_selector = " << ADG_MUX_selector ;

        data_1 = Rec_Reply[2][packet_cnt];
        data_1 = data_1 << 26;
        data_1 = data_1 >> 22;
        data_2 = Rec_Reply[3][packet_cnt];
        data_2 = data_2 >> 28;
        data = data_1 + data_2;

        ///data = data * 2 ;

        qDebug() << "DATA = " << data ;


        if (ADC_channel == 0)
        {
            //printf(" ADC Temperature is: %d\n", data);
            adc_value = data * 0.25;

            QString str_CB_Temp_ADC = QString("%1  'C").arg(adc_value);
            ui->lineEdit_CB_Temp_ADC->setText(str_CB_Temp_ADC);

            //printf(" ADC Temperature is: %.3f C\n", adc_value);
            qDebug() << "CB ADC Temperature is: " << adc_value << " C" ;
        }

        if (ADC_channel == 2)
        {
            //CB_V1_R0 : printf(" Temperature sensor 4 is: %d\n", data);
            //CB_V1_R1 : printf(" Temperature sensor 3 is: %d\n", data);


            adc_value = data * 2.44;

            adc_value = adc_value - 500;
            adc_value = adc_value / 10;
            QString str_CB_Temp_Sensor3 = QString("%1  'C").arg(adc_value);
            ui->lineEdit_CB_Temp_Sensor3->setText(str_CB_Temp_Sensor3);
            qDebug()<<"str_CB_Temp_Sensor3 =" <<QString("%1  'C").arg(adc_value);

        }
        if (ADC_channel == 3)
        {
            //printf(" AVDD / 2 is: %d\n", data);
            adc_value = data * 2.44;
            adc_value = adc_value * 2 ;//CB_V1_R1

            QString str_CB_ADC_AVDD_2 = QString("%1  mV").arg(adc_value);
            ui->lineEdit_CB_ADC_AVDD_2->setText(str_CB_ADC_AVDD_2);
            printf(" AVDD is: %.3f mV\n", adc_value);
        }
        if (ADC_channel == 4)
        {
            //printf(" ground voltage is: %d\n", data);
            adc_value = data * 2.44;
            QString str_CB_ADC_GND = QString("%1  mV").arg(adc_value);
            ui->lineEdit_CB_ADC_GND->setText(str_CB_ADC_GND);
            printf(" ground voltage is: %.3f mV\n", adc_value);
        }
        if (ADC_channel == 1)
        {
            if (ADG_MUX_selector == 0)
            {
                //printf(" +1.0 volt VDD is: %d\n", data);
                adc_value = data * 2.44;
                adc_value = adc_value * 2 ;//CB_V1_R1
                //printf(" +1.0 volt VDD is: %.3f mV\n", adc_value);

                QString str_CB_1V = QString("%1  mV").arg(adc_value);
                ui->lineEdit_CB_1V->setText(str_CB_1V);

                qDebug() << "+1.0 volt VDD is: " << adc_value << " mV" ;
            }

            if (ADG_MUX_selector == 1)
            {
                //printf(" +1.8 volt AUX is: %d\n", data);
                adc_value = data * 2.44;
                adc_value = adc_value * 2 ;//CB_V1_R1

                QString str_CB_1V8_Aux = QString("%1  mV").arg(adc_value);
                ui->lineEdit_CB_1V8_Aux->setText(str_CB_1V8_Aux);
                //printf(" +1.8 volt AUX is: %.3f mV\n", adc_value);
            }

            if (ADG_MUX_selector == 2)
            {
                //printf(" +1.0 volt MGTAVCC is: %d\n", data);
                adc_value = data * 2.44;
                adc_value = adc_value * 2 ;//CB_V1_R1

                QString str_CB_1V_MGTAVCC = QString("%1  mV").arg(adc_value);
                ui->lineEdit_CB_1V_MGTAVCC->setText(str_CB_1V_MGTAVCC);
                //printf(" +1.0 volt MGTAVCC is: %.3f mV\n", adc_value);
            }

            if (ADG_MUX_selector == 3)
            {
                //printf(" +1.0 volt MGTAVTT is: %d\n", data);
                adc_value = data * 2.44;
                adc_value = adc_value * 2 ;//CB_V1_R1

                QString str_CB_1V_MGTAVTT = QString("%1  mV").arg(adc_value);
                ui->lineEdit_CB_1V_MGTAVTT->setText(str_CB_1V_MGTAVTT);
                //printf(" +1.0 volt MGTAVTT is: %.3f mV\n", adc_value);
            }

            if (ADG_MUX_selector == 4)
            {
                //printf(" +1.8 volt MGTVCCAUX is: %d\n", data);
                adc_value = data * 2.44;
                adc_value = adc_value * 2 ;//CB_V1_R1

                QString str_CB_1V_MGTVCCAUX = QString("%1  mV").arg(adc_value);
                ui->lineEdit_CB_1V_MGTVCCAUX->setText(str_CB_1V_MGTVCCAUX);
                //printf(" +1.8 volt MGTVCCAUX is: %.3f mV\n", adc_value);
            }

            if (ADG_MUX_selector == 5)
            {
                //printf(" +1.8 volt is: %d\n", data);
                adc_value = data * 2.44;
                adc_value = adc_value * 2 ;//CB_V1_R1

                QString str_CB_1V8 = QString("%1  mV").arg(adc_value);
                ui->lineEdit_CB_1V8->setText(str_CB_1V8);
                //printf(" +1.8 volt is: %.3f mV\n", adc_value);
            }

            if (ADG_MUX_selector == 6)
            {
                //printf(" +1.5 volt is: %d\n", data);
                adc_value = data * 2.44;
                adc_value = adc_value * 2 ;//CB_V1_R1

                QString str_CB_1V5 = QString("%1  mV").arg(adc_value);
                ui->lineEdit_CB_1V5->setText(str_CB_1V5);
                //printf(" +1.5 volt is: %.3f mV\n", adc_value);
            }

            if (ADG_MUX_selector == 7)
            {
                //printf(" +3.3 volt is: %d\n", data);
                adc_value = data * 2.44;
                adc_value = adc_value * 2 ;//CB_V1_R1

                QString str_CB_3V3 = QString("%1  mV").arg(adc_value);
                ui->lineEdit_CB_3V3->setText(str_CB_3V3);
                //printf(" +3.3 volt is: %.3f mV\n", adc_value);
            }

            if (ADG_MUX_selector == 8)
            {
                //printf(" +2.5 volt is: %d\n", data);
                adc_value = data * 2.44;
                adc_value = adc_value * 2 ;//CB_V1_R1

                QString str_CB_2V5 = QString("%1  mV").arg(adc_value);
                ui->lineEdit_CB_2V5->setText(str_CB_2V5);
                //printf(" +2.5 volt is: %.3f mV\n", adc_value);
            }

            if (ADG_MUX_selector == 9)
            {
                //printf(" +3.3 volt VDD is: %d\n", data);
                adc_value = data * 2.44;
                adc_value = adc_value * 2 ;//CB_V1_R1

                QString str_CB_3V3VDD = QString("%1  mV").arg(adc_value);
                ui->lineEdit_CB_3V3VDD->setText(str_CB_3V3VDD);
                //printf(" +3.3 volt VDD is: %.3f mV\n", adc_value);
            }

            if (ADG_MUX_selector == 10)
            {
                //printf(" Temperature sensor 1 is: %d\n", data);
                adc_value = data * 2.44;
                adc_value = adc_value * 2 ;//CB_V1_R1

                //adc_value = adc_value - 500;
                //adc_value = adc_value / 10;
                QString str_CB_Temp_Sensor1 = QString("%1  mV").arg(adc_value);
                ui->lineEdit_CB_Temp_Sensor1->setText(str_CB_Temp_Sensor1);
                //printf(" Temperature sensor 1 is: %.3f 'C\n", adc_value);
            }

            if (ADG_MUX_selector == 11)
            {
                //CB_V1_R0: Temperature sensor 2
                //CB_V1_R1: Temperature sensor 1
                adc_value = data * 2.44;
                adc_value = adc_value * 2 ;//CB_V1_R1

                adc_value = adc_value - 500;
                adc_value = adc_value / 10;
                QString str_CB_Temp_Sensor2 = QString("%1  'C").arg(adc_value);
                ui->lineEdit_CB_Temp_Sensor2->setText(str_CB_Temp_Sensor2);
                //printf(" Temperature sensor 2 is: %.3f 'C\n", adc_value);
            }

            if (ADG_MUX_selector == 12)
            {
                //CB_V1_R0: Temperature sensor 3
                //CB_V1_R1: Not used

                /*
                adc_value = data * 2.44;
                adc_value = adc_value * 2 ;//CB_V1_R1

                adc_value = adc_value - 500;
                adc_value = adc_value / 10;
                QString str_CB_Temp_Sensor3 = QString("%1  'C").arg(adc_value);
                ui->lineEdit_CB_Temp_Sensor3->setText(str_CB_Temp_Sensor3);
                //printf(" Temperature sensor 3 is: %.3f 'C\n", adc_value);
                */
            }

            if (ADG_MUX_selector == 13)
            {
                //printf(" CS1 VOUT is: %d\n", data);
                adc_value = data * 2.44;
                adc_value = adc_value * 2 ;//CB_V1_R1

                QString str_CB_CS1_Vout = QString("%1  mV").arg(adc_value);
                ui->lineEdit_CB_CS1_Vout->setText(str_CB_CS1_Vout);
                //printf(" CS1 VOUT is: %.3f mV\n", adc_value);
            }

            if (ADG_MUX_selector == 14)
            {
                //printf(" CS2 VOUT is: %d\n", data);
                adc_value = data * 2.44;
                adc_value = adc_value * 2 ;//CB_V1_R1

                QString str_CB_CS2_Vout = QString("%1  mV").arg(adc_value);
                ui->lineEdit_CB_CS2_Vout->setText(str_CB_CS2_Vout);
                //printf(" CS2 VOUT is: %.3f mV\n", adc_value);
            }

            if (ADG_MUX_selector == 15)
            {
                //printf(" CS3 VOUT is: %d\n", data);
                adc_value = data * 2.44;
                adc_value = adc_value * 2 ;//CB_V1_R1

                QString str_CB_CS3_Vout = QString("%1  mV").arg(adc_value);
                ui->lineEdit_CB_CS3_Vout->setText(str_CB_CS3_Vout);
                //printf(" CS3 VOUT is: %.3f mV\n", adc_value);
            }
        }
    }

    //#################################################################
    if (instruction_code == 2) // if instruction is : get FEB parameters
    {

        qDebug() << "FEB CMD = " << packet_cnt ;

        feb_instruction_code = Rec_Reply[2][packet_cnt];
        feb_instruction_code = feb_instruction_code << 15;
        feb_instruction_code = feb_instruction_code >> 29;

        feb_distribution_board = Rec_Reply[2][packet_cnt];
        feb_distribution_board = feb_distribution_board << 18;
        feb_distribution_board = feb_distribution_board >> 29;

        feb_distribution_board_port = Rec_Reply[2][packet_cnt];
        feb_distribution_board_port = feb_distribution_board_port << 21;
        feb_distribution_board_port = feb_distribution_board_port >> 31;

        feb_number = Rec_Reply[2][packet_cnt];
        feb_number = feb_number << 22;
        feb_number = feb_number >> 30;


        feb_chip = Rec_Reply[2][packet_cnt];
        feb_chip = feb_chip << 24;
        feb_chip = feb_chip >> 31;

        feb_chip_channel = Rec_Reply[2][packet_cnt];
        feb_chip_channel = feb_chip_channel << 25;
        feb_chip_channel = feb_chip_channel >> 29;

        if (feb_instruction_code == 1)
        {
            acc = Rec_Reply[2][packet_cnt];
            qDebug() << "acc = " <<  QString("0x%1").arg(acc, 0, 16);
            acc = acc << 28;
            qDebug() << "acc = " << QString("0x%1").arg(acc, 0, 16);
            acc = acc >> 22;
            qDebug() << "acc = " << QString("0x%1").arg(acc, 0, 16);

            bcc = Rec_Reply[3][packet_cnt]; //receive_buffer[i + 3];
            qDebug() << "bcc = " <<  QString("0x%1").arg(bcc, 0, 16);
            bcc = bcc >> 26;
            qDebug() << "bcc = " <<  QString("0x%1").arg(bcc, 0, 16);
            feb_dac_value = acc + bcc;
            feb_dac_value = feb_dac_value * 5;

            qDebug() << " ===Set  DAC Value of ===================";
            qDebug() << " 1) Distribution Board No. (DB):"  << feb_distribution_board ;         //printf("DAC value of DB: %d, ", feb_distribution_board);
            qDebug() << " 2) DB port:   "    << feb_distribution_board_port ;    //printf("DB port: %d, ", feb_distribution_board_port);
            qDebug() << " 3) FEB number:"    << feb_number;                      //printf("FEB number: %d, ", feb_number);
            qDebug() << " 4) Chip:      "    << feb_chip;                        //printf("Chip: %d, ", feb_chip);
            qDebug() << " 5) Channel:   "    << feb_chip_channel ;               //printf("Channel: %d, ", feb_chip_channel);
            qDebug() << " 6) Value:     "    << feb_dac_value << "mV";           //printf("is: %d mV\n", feb_dac_value);


            str += QString("\n  Set DAC Value of \n");
            str += QString(" 1) Distribution Board No. (DB): %1 \n").arg(feb_distribution_board);
            str += QString(" 2) DB port: %1\n").arg(feb_distribution_board_port);
            str += QString(" 3) FEB number: %1\n").arg(feb_number);
            str += QString(" 4) Chip: %1\n").arg(feb_chip);
            str += QString(" 5) Channel: %1\n").arg(feb_chip_channel);
            str += QString(" 6) Value: %1 mV\n").arg(feb_dac_value);

            if (feb_chip== 0){ // DAC1
                if (feb_chip_channel==1){
                    QString str_FEB1_DAC1_Ch1_Set_Vth1 = QString("%1  mV").arg(feb_dac_value);
                    ui->lineEdit_FEB1_DAC1_Ch1_Set_Vth1->setText(str_FEB1_DAC1_Ch1_Set_Vth1);
                }
                else if(feb_chip_channel==2){
                    QString str_FEB1_DAC1_Ch2_Set_Vth2 = QString("%1  mV").arg(feb_dac_value);
                    ui->lineEdit_FEB1_DAC1_Ch2_Set_Vth2->setText(str_FEB1_DAC1_Ch2_Set_Vth2);
                }
                else if(feb_chip_channel==3){
                    QString str_FEB1_DAC1_Ch3_Set_Vmon1 = QString("%1  mV").arg(feb_dac_value);
                    ui->lineEdit_FEB1_DAC1_Ch3_Set_Vmon1->setText(str_FEB1_DAC1_Ch3_Set_Vmon1);
                }
                else if(feb_chip_channel==4){
                    QString str_FEB1_DAC1_Ch4_Set_Vmon2 = QString("%1  mV").arg(feb_dac_value);
                    ui->lineEdit_FEB1_DAC1_Ch4_Set_Vmon2->setText(str_FEB1_DAC1_Ch4_Set_Vmon2);
                }
            }

            if (feb_chip== 1){ // DAC2
                if (feb_chip_channel==1){
                    QString str_FEB1_DAC2_Ch1_Set_Vth1 = QString("%1  mV").arg(feb_dac_value);
                    ui->lineEdit_FEB1_DAC2_Ch1_Set_Vth1_2->setText(str_FEB1_DAC2_Ch1_Set_Vth1);
                }
                else if(feb_chip_channel==2){
                    QString str_FEB1_DAC2_Ch2_Set_Vth2 = QString("%1  mV").arg(feb_dac_value);
                    ui->lineEdit_FEB1_DAC2_Ch2_Set_Vth2->setText(str_FEB1_DAC2_Ch2_Set_Vth2);
                }
                else if(feb_chip_channel==3){
                    QString str_FEB1_DAC2_Ch3_Set_Vmon1 = QString("%1  mV").arg(feb_dac_value);
                    ui->lineEdit_FEB1_DAC2_Ch3_Set_Vmon1->setText(str_FEB1_DAC2_Ch3_Set_Vmon1);
                }
                else if(feb_chip_channel==4){
                    QString str_FEB1_DAC2_Ch4_Set_Vmon2 = QString("%1  mV").arg(feb_dac_value);
                    ui->lineEdit_FEB1_DAC2_Ch4_Set_Vmon2->setText(str_FEB1_DAC2_Ch4_Set_Vmon2);
                }
            }



            //------------------------------------------
            //ui->textEdit->append(str); //<< Display
            //------------------------------------------

        }
        if (feb_instruction_code == 0)
        {
            acc = Rec_Reply[2][packet_cnt];
            acc = acc << 28;
            acc = acc >> 22;
            bcc = Rec_Reply[3][packet_cnt]; //receive_buffer[i + 3];
            bcc = bcc >> 26;
            feb_adc_value = acc + bcc;

            qDebug() << " ===Read ADC Value of ===================";
            qDebug() << " 1) Distribution Board No. (DB): "  << feb_distribution_board ;    //printf("\nADC value of \nDB:%d, ", feb_distribution_board);
            qDebug() << " 2) DB port:       "   << feb_distribution_board_port; //printf("DB port:%d, ", feb_distribution_board_port);
            qDebug() << " 3) FEB number:    "   << feb_number;                 //printf("FEB number:%d, ", feb_number);
            qDebug() << " 4) Chip:          "   << feb_chip;                   // printf("Chip:%d, ", feb_chip);
            qDebug() << " 5) Channel:       "   << feb_chip_channel ;          //printf("Channel:%d, ", feb_chip_channel);


            str += QString("\n  Read ADC Value of \n");
            str += QString(" 1) Distribution Board No. (DB): %1 \n").arg(feb_distribution_board);
            str += QString(" 2) DB port: %1\n").arg(feb_distribution_board_port);
            str += QString(" 3) FEB number: %1\n").arg(feb_number);
            str += QString(" 4) Chip: %1\n").arg(feb_chip);
            str += QString(" 5) Channel: %1\n").arg(feb_chip_channel);
            str += QString(" 6) Raw Value: %1 \n").arg(feb_adc_value);



            if (feb_chip_channel==0)
            {
                feb_adc_value = feb_adc_value * 0.25;
                str += QString(" 7) Temperature: %1 'C\n").arg(feb_adc_value);
                qDebug() << " 7) Temperature: " << feb_adc_value <<" 'C";                  //printf("is: %.3f C\n", feb_adc_value);

                QString str_FEB1_ADC1_Read_Temp = QString("%1  'C").arg(feb_adc_value);
                ui->lineEdit_FEB1_ADC1_Read_Temp->setText(str_FEB1_ADC1_Read_Temp);
            }
            else
            {
                feb_adc_value = feb_adc_value * 2.44;
                str += QString(" 7) ADC Value: %1 mV\n").arg(feb_adc_value);
                qDebug() << " 7) ADC Value: " << feb_adc_value << " mV";  //printf("is: %.3f mV\n", feb_adc_value);
                if (feb_chip==0){ // ADC1

                    if (feb_chip_channel==1){
                        QString str_FEB1_ADC1_Read_Ch1_Vth1 = QString("%1  mV").arg(feb_adc_value);
                        ui->lineEdit_FEB1_ADC1_Read_Ch1_Vth1->setText(str_FEB1_ADC1_Read_Ch1_Vth1);
                    }
                    else if (feb_chip_channel==2){
                        QString str_FEB1_ADC1_Read_Ch2_Vth2 = QString("%1  mV").arg(feb_adc_value);
                        ui->lineEdit_FEB1_ADC1_Read_Ch2_Vth2->setText(str_FEB1_ADC1_Read_Ch2_Vth2);
                    }
                    else if (feb_chip_channel==3){
                        feb_adc_value = feb_adc_value * 2 ;

                        QString str_FEB1_ADC1_Read_Ch3_Vmon1 = QString("%1  mV").arg(feb_adc_value);
                        ui->lineEdit_FEB1_ADC1_Read_Ch3_Vmon1->setText(str_FEB1_ADC1_Read_Ch3_Vmon1);
                    }
                    else if (feb_chip_channel==4){
                        feb_adc_value = feb_adc_value * 2 ;

                        QString str_FEB1_ADC1_Read_Ch4_Vmon2 = QString("%1  mV").arg(feb_adc_value);
                        ui->lineEdit_FEB1_ADC1_Read_Ch4_Vmon2->setText(str_FEB1_ADC1_Read_Ch4_Vmon2);
                    }
                }

                    if (feb_chip==1){ // ADC2

                        if (feb_chip_channel==1){
                            QString str_FEB1_ADC2_Read_Ch1_Vth1 = QString("%1  mV").arg(feb_adc_value);
                            ui->lineEdit_FEB1_ADC2_Read_Ch1_Vth1->setText(str_FEB1_ADC2_Read_Ch1_Vth1);
                        }
                        else if (feb_chip_channel==2){
                            QString str_FEB1_ADC2_Read_Ch2_Vth2 = QString("%1  mV").arg(feb_adc_value);
                            ui->lineEdit_FEB1_ADC2_Read_Ch2_Vth2->setText(str_FEB1_ADC2_Read_Ch2_Vth2);
                        }
                        else if (feb_chip_channel==3){
                            feb_adc_value = feb_adc_value * 2 ;

                            QString str_FEB1_ADC2_Read_Ch3_Vmon1 = QString("%1  mV").arg(feb_adc_value);
                            ui->lineEdit_FEB1_ADC2_Read_Ch3_Vmon1->setText(str_FEB1_ADC2_Read_Ch3_Vmon1);
                        }
                        else if (feb_chip_channel==4){
                            feb_adc_value = feb_adc_value * 2 ;

                            QString str_FEB1_ADC2_Read_Ch4_Vmon2 = QString("%1  mV").arg(feb_adc_value);
                            ui->lineEdit_FEB1_ADC2_Read_Ch4_Vmon2->setText(str_FEB1_ADC2_Read_Ch4_Vmon2);
                        }
                }
            }

        }
        qDebug() << "===================================="; //printf("\n");
    }
    //#################################################################
    if (instruction_code == 3) // if instruction is : get CB firmware ID
    {
        data_1 = Rec_Reply[2][packet_cnt]; //receive_buffer[i + 2];
        data_2 = Rec_Reply[3][packet_cnt]; //receive_buffer[i + 3];
        data_1 = data_1 << 30;
        data_2 = data_2 >> 2;
        data = data_1 + data_2;
        QString str_CB_ID_Number = QString(" %1").arg(data);
        ui->lineEdit_CB_ID_Number->setText(str_CB_ID_Number);


        qDebug() << "Control Board Firmware ID: " << data ; // printf("%08X \n", data);

    }

}


//==========================================================================
//          Function : Check the Save checkBox, uses for saving
//                     the Send file from LB' Ethernet
//==========================================================================
void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if (ui->checkBox_2->isChecked())
    {
        m_thread.t_bSave = 1;
        qDebug()<< "Checked =" << m_thread.t_bSave;
    }
    else
    {
        m_thread.t_bSave = 0;
        qDebug()<< "UnChecked ="<< m_thread.t_bSave;
    }

}

//==========================================================================
//          Function : Acknowledge function of the Send Thread
//==========================================================================

void MainWindow::ThreadSlot_showResponseSend( const UINT64 totalSentSize)// , const boolean Buffer_full );
{
         qDebug() << "SentBufferSize(char) =" << totalSentSize;
         qDebug() << "SentBufferSize(Line) =" << totalSentSize/9;

         str += QString("%1\n").arg("=========================");
         str += QString("3-SentBufferSize(char) = %1\n").arg(totalSentSize);
         str += QString("4-SentBufferSize(Line) = %1\n").arg(totalSentSize/9);
         str += QString("%1\n").arg("=========================");
         ui->textEdit->append(str);

}


//==========================================================================
//          Function : Menue item, FEB
//==========================================================================

void MainWindow::on_actionFEB_triggered()
{
    QMessageBox::information(this,"Title","Read-Back FEB Setting");
}


//==========================================================================
//          Function : Menue item, FEBs
//==========================================================================
void MainWindow::on_actionFEBs_triggered()
{
    //QMessageBox::information(this,"Title","FEB Command Setting");
    febdialog = new febDialog(this);
    febdialog -> show();
}
//==========================================================================
//          Function : Menue item, Exit
//==========================================================================
void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
//==========================================================================
//          Function : Menue item, Ethernet_1G
//==========================================================================
void MainWindow::on_actionEthernet_1G_triggered()
{

    bool lanStartup = YE_LanStartup ();
    QString csIpAddress = ui->lineEdit->text();
    ui->lineEdit_2->setText(csIpAddress);
    QString strA(csIpAddress);
    PCSTR pNodeName = csIpAddress.toUtf8();

    LanStatus = YE_TCP_Connect(pNodeName);

    if (LanStatus &lanStartup){
       QMessageBox::information(this,"Title","Ethernet is Connected");
    }

}
//==========================================================================
//          Function : Menue item, PCIe_8G
//==========================================================================
void MainWindow::on_actionPCIe_8G_triggered()
{
    QMessageBox::information(this,"Title","PCIe-8G Selected");
}
//==========================================================================
//          Function : Menue item, UART
//==========================================================================
void MainWindow::on_actionUART_triggered()
{
    QMessageBox::information(this,"Title","UART Selected");
}

//==========================================================================
//          Function : Menue item, Connect
//==========================================================================
void MainWindow::on_actionTlbConnect_triggered()
{
    bool lanStartup = YE_LanStartup ();
    QString csIpAddress = ui->lineEdit->text();
    ui->lineEdit_2->setText(csIpAddress);
    QString strA(csIpAddress);
    PCSTR pNodeName = csIpAddress.toUtf8();

    LanStatus = YE_TCP_Connect(pNodeName);

    if (LanStatus &lanStartup){
       QMessageBox::information(this,"Title","Ethernet is Connected");
  }
}
//==========================================================================
//          Function : Menue item, Ping
//==========================================================================
void MainWindow::on_actionTlbPing_triggered()
{


}

//==========================================================================
//          Function : After clicked the "send frame" button, follwong
//                     funtion sends 10 bytes to the ethernet
//==========================================================================
void MainWindow::on_send_one_frame_clicked()
{
    USHORT address ;
    QString text;
    QByteArray text_qba;
    int64_t fileLength = 8;
    QString file_name;

        address = ui->lineEdit_3->text().toUShort();


        //--------------------------------------------------------
        sendBuf = (char*)malloc(fileLength); // char *sendBuf;
        memset(sendBuf, 0, fileLength);
        //--------------------------------------------------------

        SendFrame myFrame;
        /*
        myFrame.frame = ui->framelineEdit->text(); // Read string of 80-bits
        myFrame.config_buffer(); // Write 80-bit string to the 10-Bytes "char_array[i]"
        */

        /*
        qDebug() << "frame value is :" << myFrame.frame;


        for (int i = 0 ; i < 16 ; i++)
        {
             sendBuf[i] = myFrame.char_array[i]; // Copy 10-byte of the char_array[i] to sendBuf
        }*/


        sendBuf[0] = 0XD0;

        sendBuf[1] = 0XD0;

        sendBuf[2] = 0XD0;
        sendBuf[3] = 0XD0;

        sendBuf[4] = 0XD0;
        sendBuf[5] = 0XD0;
        sendBuf[6] = 0X01;
        sendBuf[7] = 0X00;
        /*
        sendBuf[8] = 0X00;
        sendBuf[9] = 0X00;
        sendBuf[10] = 0X00;
        sendBuf[11] = 0X00;
        sendBuf[12] = 0X00;
        sendBuf[13] = 0X00;
        sendBuf[14] = 0X00;
        sendBuf[15] = 0X04; */

        //---------------------------------------------------------
        // push sendBuf buffer to the buffer of the Send Thread (s_thread.t_sendBuf)
        //---------------------------------------------------------

        s_thread.t_sendBuf = (char*)malloc(fileLength); // Create a buffer, char *sendBuf;
        memset(s_thread.t_sendBuf, 0, fileLength);      // Set all element to zero

        memcpy(s_thread.t_sendBuf,sendBuf,fileLength);  // Copy current buffer to the thread buffer
        //---------------------------------------------------------
        //s_thread.t_text = text;
        s_thread.t_fileLength = fileLength;             // Send size of buffer to the thread
        //---------------------------------------------------------


        //---------------------------------------------------------
        //if (ui->checkBox_4->isChecked()) // check if copy check box is checked
        //ui->plainTextEdit->setPlainText(text); // Copy content of file to the PlainText box

        qDebug() << "File Size =" << fileLength;
        str += QString("%1\n").arg("=========================");
        str += QString("1-File Characters = %1\n").arg(fileLength); // Number of File lines
        str += QString("2-File Lines = %1\n").arg(fileLength/9);    // Number of Characters
        str += QString("%1\n").arg("=========================");
        ui->textEdit->append(str);
        str.clear();
        //---------------------------------------------------------
        if (ui->checkBox_3->isChecked()) // check if repeat check box is checked
        {
            s_thread.t_repeatSend = true;
        }
        else
        {
            s_thread.t_repeatSend = false;
        }
        //---------------------------------------------------------
        WriteConfig(0x00, 0x01u);   // Prepare Ethernt for Send packets

        s_thread.transaction_send(address); // Call Transaction funtion of the Thread




        //++++++++++++++++++++++++++++++++++++++++++++++++++++
        UINT iAsRateControl = 0x00u;

        receiveBufSize = 2; // Get the received buffer size

        //m_thread.t_receiveBuf = (unsigned char*) malloc(receiveBufSize); // Set the thread received buffer size

        memset(m_thread.t_receiveBuf, 0, receiveBufSize); // Set thread received buffers with 0s

        m_thread.t_receiveBufSize = receiveBufSize;
        m_thread.t_receiveBufIndex = 0 ;
        m_thread.t_buffer_full = 0 ;
        m_thread.t_receivedBuf = 0 ;


        qDebug() << "======================================================";
        qDebug() << "   Receive BUFFER--";
        qDebug() << "   Receive Buffer Size = " << receiveBufSize ;
        qDebug() << "======================================================";

        m_thread.on_receive = true ;

        WriteReg(0x01, iAsRateControl); // (Address , Value) Request to Link Board for sending the BURST data
        WriteConfig(0x00, 0x02u);       // (Address , Value) AutoSend pin enable


        unsigned int uint_address = 4 ;
        UINT value = receiveBufSize * 65536 ; // set the length of send packet ;
        WriteConfig(uint_address, value); // write

        //------------------------------------------------


}


//==========================================================================
//          Function : Erase Receive Text Box and
//                     Reset content of Ethernet Receive Buffer
//==========================================================================
void MainWindow::on_clear_pushBotton_clicked()
{

    UINT iAsRateControl = 0x00u;

    str.clear();
    ui->textEdit->clear();

    receiveBufSize = ui->lineEdit_8->text().toUInt(); // Read size of Received buffer

    //m_thread.t_receiveBuf = (unsigned char*) malloc(receiveBufSize); // Set size of thread received buffer

    memset(m_thread.t_receiveBuf, 0, receiveBufSize); // Clear thread received buffer

    m_thread.t_receiveBufSize = receiveBufSize;
    m_thread.t_receiveBufIndex = 0 ;
    m_thread.t_buffer_full = 0 ;
    m_thread.t_receivedBuf = 0 ;


    qDebug() << "======================================================";
    qDebug() << "   Receive BUFFER--";
    qDebug() << "   Receive Buffer Size = " << receiveBufSize ;
    qDebug() << "======================================================";

    m_thread.on_receive = true ;

    WriteReg(0x01, iAsRateControl); // Request to Link Board for sending the BURST data
    WriteConfig(0x00, 0x02u);       // (Address , Value) AutoSend pin enable
}

//==========================================================================
//          Function : A) Erase Receive Text Box,
//                     B) Reset content of Ethernet Receive Buffer,
//                     C) Determine which one of the LB, CB or BE is selected.
//                     D) Run a thread for selected device.
//==========================================================================
void MainWindow::on_CB_Update_clicked()
{


    if (ui->radioButton_CB_ST1->isChecked()){ //ST0 = One shot -- ST1 = Auto Trigger
        //secDialog1 -> show();

        qDebug() << "START Timer-3 for Update retriggering " ;
        retrig_interval = ui->lineEdit_25->text().toUInt();
        qtimer3->start(retrig_interval);
    }

    //==============================

    //histogram1->secDialog();
    /*
        for (int j=0 ; j<95;j++){
            histogram1->y0CB_FullWinChannel[j] = j;
            histogram1->y0CB_AdjWinChannel[j] = j;
            histogram1->x0CB_stripFulW[j] = j;
            histogram1->x0CB_stripAdjW[j] = j;

            histogram1->y0LB1_FullWinChannel[j] = 0;
            histogram1->y0LB1_AdjWinChannel[j] = 0;
            histogram1->x0LB1_stripFulW[j] = j;
            histogram1->x0LB1_stripAdjW[j] = j;

            histogram1->y0LB2_FullWinChannel[j] = 0;
            histogram1->y0LB2_AdjWinChannel[j] = 0;
            histogram1->x0LB2_stripFulW[j] = j;
            histogram1->x0LB2_stripAdjW[j] = j;

            histogram1->y0LB3_FullWinChannel[j] = 0;
            histogram1->y0LB3_AdjWinChannel[j] = 0;
            histogram1->x0LB3_stripFulW[j] = j;
            histogram1->x0LB3_stripAdjW[j] = j;

            histogram1->y0LB4_FullWinChannel[j] = 0;
            histogram1->y0LB4_AdjWinChannel[j] = 0;
            histogram1->x0LB4_stripFulW[j] = j;
            histogram1->x0LB4_stripAdjW[j] = j;

            histogram1->y0LB5_FullWinChannel[j] = 0;
            histogram1->y0LB5_AdjWinChannel[j] = 0;
            histogram1->x0LB5_stripFulW[j] = j;
            histogram1->x0LB5_stripAdjW[j] = j;

            histogram1->y0LB6_FullWinChannel[j] = 0;
            histogram1->y0LB6_AdjWinChannel[j] = 0;
            histogram1->x0LB6_stripFulW[j] = j;
            histogram1->x0LB6_stripAdjW[j] = j;

            histogram1->y0LB7_FullWinChannel[j] = 0;
            histogram1->y0LB7_AdjWinChannel[j] = 0;
            histogram1->x0LB7_stripFulW[j] = j;
            histogram1->x0LB7_stripAdjW[j] = j;

            histogram1->y0LB8_FullWinChannel[j] = 0;
            histogram1->y0LB8_AdjWinChannel[j] = 0;
            histogram1->x0LB8_stripFulW[j] = j;
            histogram1->x0LB8_stripAdjW[j] = j;

            histogram1->y0LB9_FullWinChannel[j] = 0;
            histogram1->y0LB9_AdjWinChannel[j] = 0;
            histogram1->x0LB9_stripFulW[j] = j;
            histogram1->x0LB9_stripAdjW[j] = j;
    }

    histogram1->setupPlot_CB();
    for (int i=1 ; i<=9 ; i++){
      histogram1->setupPlot_LB(i);
    } */


    //histogram1->show();
    //==============================



    str = QString("");
    str.clear();
    ui->textEdit->clear();
    packet_cnt = 0;
    m_thread.packetCount = 0 ;     //MyThread m_thread;
    m_thread.RECEIVE_COUNTER = 0 ;
    m_thread.t_receiveBufIndex = 0 ;

    Set_ch_thread_ChBx(); // Disable all commands in CB and LB1 .. LB9
    Get_ch_thread_ChBx_Values(); // Check which command in CB and LB1 & LB2 need to be run
                                 // List of commands for LB3 .. LB9 should be included.
    //-------------------------------------------------------------------------------
    // FEB 1 - DAC1
    //-------------------------------------------------------------------------------
    feb1_dac1_vth1_value_int = ui->lineEdit_FEB1_DAC1_Ch1_Set_Vth1->text().toUInt();
    cb_thread.feb1_dac1_vth1_value_int = feb1_dac1_vth1_value_int ;


    feb1_dac1_vth2_value_int = ui->lineEdit_FEB1_DAC1_Ch2_Set_Vth2->text().toUInt();
    cb_thread.feb1_dac1_vth2_value_int = feb1_dac1_vth2_value_int ;


    feb1_dac1_vmon1_value_int = ui->lineEdit_FEB1_DAC1_Ch3_Set_Vmon1->text().toUInt();
    cb_thread.feb1_dac1_vmon1_value_int = feb1_dac1_vmon1_value_int ;

    feb1_dac1_vmon2_value_int = ui->lineEdit_FEB1_DAC1_Ch4_Set_Vmon2->text().toUInt();
    cb_thread.feb1_dac1_vmon2_value_int = feb1_dac1_vmon2_value_int ;

    //-------------------------------------------------------------------------------
    // FEB 1 - DAC2
    //-------------------------------------------------------------------------------
    feb1_dac2_vth1_value_int = ui->lineEdit_FEB1_DAC2_Ch1_Set_Vth1_2->text().toUInt();
    cb_thread.feb1_dac2_vth1_value_int = feb1_dac2_vth1_value_int ;


    feb1_dac2_vth2_value_int = ui->lineEdit_FEB1_DAC2_Ch2_Set_Vth2->text().toUInt();
    cb_thread.feb1_dac2_vth2_value_int = feb1_dac2_vth2_value_int ;


    feb1_dac2_vmon1_value_int = ui->lineEdit_FEB1_DAC2_Ch3_Set_Vmon1->text().toUInt();
    cb_thread.feb1_dac2_vmon1_value_int = feb1_dac2_vmon1_value_int ;

    feb1_dac2_vmon2_value_int = ui->lineEdit_FEB1_DAC2_Ch4_Set_Vmon2->text().toUInt();
    cb_thread.feb1_dac2_vmon2_value_int = feb1_dac2_vmon2_value_int ;

    //-------------------------------------------------------------------------------
    // FEB 2 - DAC1
    //-------------------------------------------------------------------------------
    feb2_dac1_vth1_value_int = ui->lineEdit_FEB2_DAC1_Ch1_Set_Vth1->text().toUInt();
    cb_thread.feb2_dac1_vth1_value_int = feb2_dac1_vth1_value_int ;

    qDebug() << "feb2_dac1_vth1_value_int" << feb2_dac1_vth1_value_int ;
    qDebug() << "cb_thread.feb2_dac1_vth1_value_int" << cb_thread.feb2_dac1_vth1_value_int ;

    feb2_dac1_vth2_value_int = ui->lineEdit_FEB2_DAC1_Ch2_Set_Vth2->text().toUInt();
    cb_thread.feb2_dac1_vth2_value_int = feb2_dac1_vth2_value_int ;
    qDebug() << "feb2_dac1_vth2_value_int" << feb2_dac1_vth2_value_int ;

    feb2_dac1_vmon1_value_int = ui->lineEdit_FEB2_DAC1_Ch3_Set_Vmon1->text().toUInt();
    cb_thread.feb2_dac1_vmon1_value_int = feb2_dac1_vmon1_value_int ;

    feb2_dac1_vmon2_value_int = ui->lineEdit_FEB2_DAC1_Ch4_Set_Vmon2->text().toUInt();
    cb_thread.feb2_dac1_vmon2_value_int = feb2_dac1_vmon2_value_int ;

    //-------------------------------------------------------------------------------
    // FEB 2 - DAC2
    //-------------------------------------------------------------------------------
    feb2_dac2_vth1_value_int = ui->lineEdit_FEB2_DAC2_Ch1_Set_Vth1->text().toUInt();
    cb_thread.feb2_dac2_vth1_value_int = feb1_dac2_vth1_value_int ;


    feb2_dac2_vth2_value_int = ui->lineEdit_FEB2_DAC2_Ch2_Set_Vth2->text().toUInt();
    cb_thread.feb2_dac2_vth2_value_int = feb2_dac2_vth2_value_int ;


    feb2_dac2_vmon1_value_int = ui->lineEdit_FEB2_DAC2_Ch3_Set_Vmon1->text().toUInt();
    cb_thread.feb2_dac1_vmon1_value_int = feb2_dac1_vmon1_value_int ;

    feb2_dac2_vmon2_value_int = ui->lineEdit_FEB2_DAC2_Ch4_Set_Vmon2->text().toUInt();
    cb_thread.feb2_dac2_vmon2_value_int = feb2_dac2_vmon2_value_int ;


    //-------------------------------------------------------------------------------
    // FEB 3 - DAC1
    //-------------------------------------------------------------------------------
    feb3_dac1_vth1_value_int = ui->lineEdit_FEB3_DAC1_Ch1_Set_Vth1->text().toUInt();
    cb_thread.feb3_dac2_vth1_value_int = feb3_dac2_vth1_value_int ;


    feb3_dac1_vth2_value_int = ui->lineEdit_FEB3_DAC1_Ch2_Set_Vth2->text().toUInt();
    cb_thread.feb3_dac1_vth2_value_int = feb3_dac1_vth2_value_int ;


    feb3_dac1_vmon1_value_int = ui->lineEdit_FEB3_DAC1_Ch3_Set_Vmon1->text().toUInt();
    cb_thread.feb3_dac1_vmon1_value_int = feb3_dac1_vmon1_value_int ;

    feb3_dac1_vmon2_value_int = ui->lineEdit_FEB3_DAC1_Ch4_Set_Vmon2->text().toUInt();
    cb_thread.feb3_dac1_vmon2_value_int = feb3_dac1_vmon2_value_int ;

    //-------------------------------------------------------------------------------
    // FEB 3 - DAC2
    //-------------------------------------------------------------------------------
    feb3_dac2_vth1_value_int = ui->lineEdit_FEB3_DAC2_Ch1_Set_Vth1->text().toUInt();
    cb_thread.feb3_dac2_vth1_value_int = feb3_dac2_vth1_value_int ;


    feb3_dac2_vth2_value_int = ui->lineEdit_FEB3_DAC2_Ch2_Set_Vth2->text().toUInt();
    cb_thread.feb3_dac2_vth2_value_int = feb3_dac2_vth2_value_int ;


    feb3_dac2_vmon1_value_int = ui->lineEdit_FEB3_DAC2_Ch3_Set_Vmon1->text().toUInt();
    cb_thread.feb3_dac1_vmon1_value_int = feb3_dac1_vmon1_value_int ;

    feb3_dac2_vmon2_value_int = ui->lineEdit_FEB3_DAC2_Ch4_Set_Vmon2->text().toUInt();
    cb_thread.feb3_dac2_vmon2_value_int = feb3_dac2_vmon2_value_int ;


    if (ui->RB_CB_DB_Port1->isChecked()){
        db_port = 0 ;
        cb_thread.db_port = 0 ;
    }else if (ui->RB_CB_DB_Port2->isChecked()){
        db_port = 1 ;
        cb_thread.db_port = 1 ;
    }
    qDebug() << "db_port ="<< db_port;


    qDebug() <<"------------------------------------------------" ;
    qDebug() <<"on_CB_Update_clicked()" ;

    if (ui->ChBx_BS_CB->isChecked()){ // if CB is selected
        //----------------------------------------------------------
        cb_thread.Parameter_Counter = 0 ;
        cb_thread.cb_value = 0 ;
        cb_thread.cb_value2 = 0 ;
        cb_thread.cb_prog_full = false;
        //----------------------------------------------------------
        cb_thread.CB_transaction();
        //----------------------------------------------------------
    }

    if (ui->ChBx_BS_LB1->isChecked()){// if LB1 is selected
        //----------------------------------------------------------
        lb_thread.Parameter_Counter = Cmd_LB1 ;
        lb_thread.lb_value = 0 ;
        lb_thread.lb_value2 = 0 ;
        lb_thread.lb_prog_full = false;
        //----------------------------------------------------------
        lb_thread.LB_transaction();
        //----------------------------------------------------------
    }

    if (ui->ChBx_BS_BEB->isChecked()){// if Backend is selected

        makeBackendPlot();
        //----------------------------------------------------------
        be_thread.Parameter_Counter = 0 ;
        be_thread.be_value = 0 ;
        be_thread.be_value2 = 0 ;
        be_thread.be_prog_full = false;
        //----------------------------------------------------------
        be_thread.BE_transaction();
        //----------------------------------------------------------
    }

    //qtimer->stop();

}

//==========================================================================
//          Function :  Respond Thread of the Control Board
//
//==========================================================================

void MainWindow::ThreadSlot_Check_cb_status_register ( UINT CB_Param_Cnt){

    UINT iAsRateControl = 0x00u;

    receiveBufSize = 16; // Get the received buffer size

    //m_thread.t_receiveBuf = (unsigned char*) malloc(receiveBufSize); // Set the thread received buffer size

    memset(m_thread.t_receiveBuf, 0, receiveBufSize); // Set thread received buffers with 0s

    m_thread.t_receiveBufSize = receiveBufSize;  //MyThread m_thread;
    m_thread.t_receiveBufIndex = 0 ;
    m_thread.t_buffer_full = 0 ;
    m_thread.t_receivedBuf = 0 ;


    //qDebug() << "======================================================";
    //qDebug() << "   Receive BUFFER--";
    //qDebug() << "   Receive Buffer Size = " << receiveBufSize ;
    //qDebug() << "======================================================";

    m_thread.on_receive = true ;

    WriteReg(0x01, iAsRateControl); // (Address , Value) Request to Link Board for sending the BURST data
    WriteConfig(0x00, 0x02u);       // (Address , Value) AutoSend pin enable


    unsigned int address = 4 ;
    UINT value = receiveBufSize * 65536 ; // set the length of send packet ;
                                          // As receiveBufSize was adjusted to 16, the length of send
                                          // Packet become 16 byte. This value set on the Byte-3 and Byte-4
                                          //  of the ethernet config register at address 0x04.
                                          // Please refer to the ethernet doc; YE_LAN_UM_r1.0.6.pdf, page 19.
    WriteConfig(address, value); // write

    //------------------------------------------------

   if (cb_thread.Parameter_Counter < 86){

           //qDebug() <<"R3- cb_thread.Parameter_Counter ="<<cb_thread.Parameter_Counter ;
           //qDebug() <<"R4- CB_Param_Cnt ="<<CB_Param_Cnt ;
           cb_thread.cb_prog_full = false;
           cb_thread.CB_transaction();

       }
       else{
           cb_thread.Parameter_Counter--;
           //qDebug() <<"R5- cb_thread.Parameter_Counter(--) ="<<cb_thread.Parameter_Counter ;
           //qDebug() <<"R6- CB_Param_Cnt ="<<CB_Param_Cnt ;
           cb_thread.cb_prog_full = true;
           //cb_thread.Parameter_Counter = 0;
           //cb_thread.CB_transaction();

       }

}

//==========================================================================
//          Function :  Respond Thread of the Link Board
//
//==========================================================================

void MainWindow::ThreadSlot_Check_lb_status_register ( UINT LB_Param_Cnt){


    UINT iAsRateControl = 0x00u;

    receiveBufSize = 480; // Get the received buffer size 500

    //m_thread.t_receiveBuf = (unsigned char*) malloc(receiveBufSize); // Set the thread received buffer size

    //memset(m_thread.t_receiveBuf, 0, receiveBufSize); // Set thread received buffers with 0s

    m_thread.t_receiveBufSize = receiveBufSize;
    m_thread.t_receiveBufIndex = 0 ;
    m_thread.t_buffer_full = 0 ;
    m_thread.t_receivedBuf = 0 ;


    qDebug() << "======================================================";
    qDebug() << "   LB Receive BUFFER--";
    qDebug() << "   LB Receive Buffer Size = " << receiveBufSize ;
    qDebug() << "======================================================";

    m_thread.on_receive = true ;

    WriteReg(0x01, iAsRateControl); // (Address , Value) Request to Link Board for sending the BURST data
    WriteConfig(0x00, 0x02u);       // (Address , Value) AutoSend pin enable


    unsigned int address = 4 ;
    UINT value = receiveBufSize * 65536 ;   // set the length of send packet ;
                                            // As receiveBufSize was adjusted to 480, the length of send
                                            // Packet become 480 byte. This value set on the Byte-3 and Byte-4
                                            //  of the ethernet config register at address 0x04.
                                            // Please refer to the ethernet doc; YE_LAN_UM_r1.0.6.pdf, page 19.
    WriteConfig(address, value); // write

    //------------------------------------------------

    if (lb_thread.Parameter_Counter < (Cmd_LB1 +Cmd_LB_MAX_CMD_NUMs)){ //  100 + 27 + 1

        qDebug() <<"R3- lb_thread.Parameter_Counter ="<<lb_thread.Parameter_Counter ;
        qDebug() <<"R4- LB_Param_Cnt ="<<LB_Param_Cnt ;
        lb_thread.lb_prog_full = false;
        lb_thread.LB_transaction();

    }
    else{
        lb_thread.Parameter_Counter--;
        qDebug() <<"R5- lb_thread.Parameter_Counter(--) ="<<lb_thread.Parameter_Counter ;
        qDebug() <<"R6- LB_Param_Cnt ="<<LB_Param_Cnt ;
        lb_thread.lb_prog_full = true;
        //cb_thread.CB_transaction();
    }

}


//==========================================================================
//          Function :  Respond Thread of the Link Board
//
//==========================================================================

void MainWindow::ThreadSlot_Check_be_status_register ( UINT BE_Param_Cnt){


    UINT iAsRateControl = 0x00u;

    receiveBufSize = 480; // Get the received buffer size 500

    //m_thread.t_receiveBuf = (unsigned char*) malloc(receiveBufSize); // Set the thread received buffer size

    //memset(m_thread.t_receiveBuf, 0, receiveBufSize); // Set thread received buffers with 0s

    m_thread.t_receiveBufSize = receiveBufSize;
    m_thread.t_receiveBufIndex = 0 ;
    m_thread.t_buffer_full = 0 ;
    m_thread.t_receivedBuf = 0 ;


    qDebug() << "======================================================";
    qDebug() << "   BE Receive BUFFER--";
    qDebug() << "   BE Receive Buffer Size = " << receiveBufSize ;
    qDebug() << "======================================================";

    m_thread.on_receive = true ;

    WriteReg(0x01, iAsRateControl); // (Address , Value) Request to Link Board for sending the BURST data
    WriteConfig(0x00, 0x02u);       // (Address , Value) AutoSend pin enable


    unsigned int address = 4 ;
    UINT value = receiveBufSize * 65536 ;   // set the length of send packet ;
                                            // As receiveBufSize was adjusted to 16, the length of send
                                            // Packet become 16 byte. This value set on the Byte-3 and Byte-4
                                            //  of the ethernet config register at address 0x04.
                                            // Please refer to the ethernet doc; YE_LAN_UM_r1.0.6.pdf, page 19.
    WriteConfig(address, value); // write

    //------------------------------------------------
    /*
    if (be_thread.Parameter_Counter < (Cmd_LB1 +Cmd_LB_MAX_CMD_NUMs)){ //  100 + 27 + 1

        qDebug() <<"R3- be_thread.Parameter_Counter ="<<be_thread.Parameter_Counter ;
        qDebug() <<"R4- BE_Param_Cnt ="<<BE_Param_Cnt ;
        be_thread.be_prog_full = false;
        be_thread.BE_transaction();

    }
    else{
        be_thread.Parameter_Counter--;
        qDebug() <<"R5- BE_thread.Parameter_Counter(--) ="<<be_thread.Parameter_Counter ;
        qDebug() <<"R6- BE_Param_Cnt ="<<BE_Param_Cnt ;
        be_thread.be_prog_full = true;
        //cb_thread.CB_transaction();
    }
    */

}


//==========================================================================
//          Function :
//
//==========================================================================
void MainWindow::Set_ch_thread_ChBx(){

    cb_thread.ChBx_CB_1V = false;
    cb_thread.ChBx_CB_1V8_Aux = false ;
    cb_thread.ChBx_CB_1V_MGTAVCC = false;
    cb_thread.ChBx_CB_1V_MGTAVTT = false;
    cb_thread.ChBx_CB_1V_MGTVCCAUX = false;
    cb_thread.ChBx_CB_1V5 = false;
    cb_thread.ChBx_CB_1V8 = false;
    cb_thread.ChBx_CB_2V5 = false;
    cb_thread.ChBx_CB_3V3 = false;
    cb_thread.ChBx_CB_3V3VDD = false;
    cb_thread.ChBx_CB_CS1_Vout = false;
    cb_thread.ChBx_CB_CS2_Vout = false;
    cb_thread.ChBx_CB_CS3_Vout = false;

    cb_thread.ChBx_CB_Temp_Sensor1 = false;
    cb_thread.ChBx_CB_Temp_Sensor2 = false;
    cb_thread.ChBx_CB_Temp_Sensor3 = false;
    cb_thread.ChBx_CB_ADC_TEMP = false;
    cb_thread.ChBx_CB_ADC_AVDD_2 = false;
    cb_thread.ChBx_CB_ADC_GND = false;
    cb_thread.ChBx_CB_FPGA_VCORE = false;
    cb_thread.ChBx_CB_FPGA_VCCBRAM = false;
    cb_thread.ChBx_CB_FPGA_VCCAUX = false;
    cb_thread.ChBx_CB_FPGA_Temp = false;
    cb_thread.ChBx_CB_ID_Number = false;
    cb_thread.ChBx_CB_SEM_Counter = false;


    cb_thread.ChBx_CB_FEB1_DAC1_Ch1_Set_Vth1  = false;
    cb_thread.ChBx_CB_FEB1_DAC1_Ch2_Set_Vth2  = false;
    cb_thread.ChBx_CB_FEB1_DAC1_Ch3_Set_Vmon1  = false;
    cb_thread.ChBx_CB_FEB1_DAC1_Ch4_Set_Vmon2  = false;
    cb_thread.ChBx_CB_FEB1_DAC1_ON  = false;
    cb_thread.ChBx_CB_FEB1_DAC2_Ch1_Set_Vth1  = false;
    cb_thread.ChBx_CB_FEB1_DAC2_Ch2_Set_Vth2  = false;
    cb_thread.ChBx_CB_FEB1_DAC2_Ch3_Set_Vmon1  = false;
    cb_thread.ChBx_CB_FEB1_DAC2_Ch4_Set_Vmon2  = false;
    cb_thread.ChBx_CB_FEB1_DAC2_ON  = false;

    cb_thread.ChBx_CB_FEB1_ADC1_Read_Temp  = false;
    cb_thread.ChBx_CB_FEB1_ADC1_Read_Ch1_Vth1  = false;
    cb_thread.ChBx_CB_FEB1_ADC1_Read_Ch2_Vth2  = false;
    cb_thread.ChBx_CB_FEB1_ADC1_Read_Ch3_VMon1  = false;
    cb_thread.ChBx_CB_FEB1_ADC1_Read_Ch4_VMon2  = false;
    cb_thread.ChBx_CB_FEB1_ADC2_Read_Temp  = false;
    cb_thread.ChBx_CB_FEB1_ADC2_Read_Ch1_Vth1  = false;
    cb_thread.ChBx_CB_FEB1_ADC2_Read_Ch2_Vth2  = false;
    cb_thread.ChBx_CB_FEB1_ADC2_Read_Ch3_VMon1  = false;
    cb_thread.ChBx_CB_FEB1_ADC2_Read_Ch4_VMon2  = false;


    cb_thread.ChBx_CB_FEB2_DAC1_Ch1_Set_Vth1  = false;
    cb_thread.ChBx_CB_FEB2_DAC1_Ch2_Set_Vth2  = false;
    cb_thread.ChBx_CB_FEB2_DAC1_Ch3_Set_Vmon1  = false;
    cb_thread.ChBx_CB_FEB2_DAC1_Ch4_Set_Vmon2  = false;
    cb_thread.ChBx_CB_FEB2_DAC1_ON  = false;
    cb_thread.ChBx_CB_FEB2_DAC2_Ch1_Set_Vth1  = false;
    cb_thread.ChBx_CB_FEB2_DAC2_Ch2_Set_Vth2  = false;
    cb_thread.ChBx_CB_FEB2_DAC2_Ch3_Set_Vmon1  = false;
    cb_thread.ChBx_CB_FEB2_DAC2_Ch4_Set_Vmon2  = false;
    cb_thread.ChBx_CB_FEB2_DAC2_ON  = false;

    cb_thread.ChBx_CB_FEB2_ADC1_Read_Temp  = false;
    cb_thread.ChBx_CB_FEB2_ADC1_Read_Ch1_Vth1  = false;
    cb_thread.ChBx_CB_FEB2_ADC1_Read_Ch2_Vth2  = false;
    cb_thread.ChBx_CB_FEB2_ADC1_Read_Ch3_VMon1  = false;
    cb_thread.ChBx_CB_FEB2_ADC1_Read_Ch4_VMon2  = false;
    cb_thread.ChBx_CB_FEB2_ADC2_Read_Temp  = false;
    cb_thread.ChBx_CB_FEB2_ADC2_Read_Ch1_Vth1  = false;
    cb_thread.ChBx_CB_FEB2_ADC2_Read_Ch2_Vth2  = false;
    cb_thread.ChBx_CB_FEB2_ADC2_Read_Ch3_VMon1  = false;
    cb_thread.ChBx_CB_FEB2_ADC2_Read_Ch4_VMon2  = false;


    cb_thread.ChBx_CB_FEB3_DAC1_Ch1_Set_Vth1  = false;
    cb_thread.ChBx_CB_FEB3_DAC1_Ch2_Set_Vth2  = false;
    cb_thread.ChBx_CB_FEB3_DAC1_Ch3_Set_Vmon1  = false;
    cb_thread.ChBx_CB_FEB3_DAC1_Ch4_Set_Vmon2  = false;
    cb_thread.ChBx_CB_FEB3_DAC1_ON  = false;
    cb_thread.ChBx_CB_FEB3_DAC2_Ch1_Set_Vth1  = false;
    cb_thread.ChBx_CB_FEB3_DAC2_Ch2_Set_Vth2  = false;
    cb_thread.ChBx_CB_FEB3_DAC2_Ch3_Set_Vmon1  = false;
    cb_thread.ChBx_CB_FEB3_DAC2_Ch4_Set_Vmon2  = false;
    cb_thread.ChBx_CB_FEB3_DAC2_ON  = false;


    cb_thread.ChBx_CB_FEB3_ADC1_Read_Temp  = false;
    cb_thread.ChBx_CB_FEB3_ADC1_Read_Ch1_Vth1  = false;
    cb_thread.ChBx_CB_FEB3_ADC1_Read_Ch2_Vth2  = false;
    cb_thread.ChBx_CB_FEB3_ADC1_Read_Ch3_VMon1  = false;
    cb_thread.ChBx_CB_FEB3_ADC1_Read_Ch4_VMon2  = false;
    cb_thread.ChBx_CB_FEB3_ADC2_Read_Temp  = false;
    cb_thread.ChBx_CB_FEB3_ADC2_Read_Ch1_Vth1  = false;
    cb_thread.ChBx_CB_FEB3_ADC2_Read_Ch2_Vth2  = false;
    cb_thread.ChBx_CB_FEB3_ADC2_Read_Ch3_VMon1  = false;
    cb_thread.ChBx_CB_FEB3_ADC2_Read_Ch4_VMon2  = false;

    cb_thread.ChBx_CB_Cmd_Turn_ON_LBBX= false;
    cb_thread.ChBx_CB_Cmd_Turn_ON_LB1= false;
    cb_thread.ChBx_CB_Cmd_Turn_ON_LB2= false;
    cb_thread.ChBx_CB_Cmd_Turn_ON_LB3= false;
    cb_thread.ChBx_CB_Cmd_Turn_ON_LB4= false;
    cb_thread.ChBx_CB_Cmd_Turn_ON_LB5= false;
    cb_thread.ChBx_CB_Cmd_Turn_ON_LB6= false;
    cb_thread.ChBx_CB_Cmd_Turn_ON_LB7= false;
    cb_thread.ChBx_CB_Cmd_Turn_ON_LB8= false;
    cb_thread.ChBx_CB_Cmd_Turn_ON_LB9= false;


    lb_thread.ChBx_LB1_1V = false;
    lb_thread.ChBx_LB1_1V8_Aux = false ;
    lb_thread.ChBx_LB1_1V_MGTAVCC = false;
    lb_thread.ChBx_LB1_1V_MGTAVTT = false;
    lb_thread.ChBx_LB1_1V_MGTVCCAUX = false;
    lb_thread.ChBx_LB1_1V5 = false;
    lb_thread.ChBx_LB1_1V8 = false;
    lb_thread.ChBx_LB1_2V5 = false;
    lb_thread.ChBx_LB1_3V3 = false;
    lb_thread.ChBx_LB1_3V3VDD = false;
    lb_thread.ChBx_LB1_CS1_Vout = false;
    lb_thread.ChBx_LB1_CS2_Vout = false;
    lb_thread.ChBx_LB1_CS3_Vout = false;

    lb_thread.ChBx_LB1_Temp_Sensor1 = false;
    lb_thread.ChBx_LB1_Temp_Sensor2 = false;
    lb_thread.ChBx_LB1_Temp_Sensor3 = false;
    lb_thread.ChBx_LB1_ADC_TEMP = false;
    lb_thread.ChBx_LB1_ADC_AVDD_2 = false;
    lb_thread.ChBx_LB1_ADC_GND = false;
    lb_thread.ChBx_LB1_FPGA_VCORE = false;
    lb_thread.ChBx_LB1_FPGA_VCCBRAM = false;
    lb_thread.ChBx_LB1_FPGA_VCCAUX = false;
    lb_thread.ChBx_LB1_FPGA_Temp = false;
    lb_thread.ChBx_LB1_ID_Number = false;
    lb_thread.ChBx_LB1_SEM_Counter = false;

    lb_thread.ChBx_LB1_ReadMultiChCnts = false;
    lb_thread.ChBx_LB1_TimingProfile = false;
    lb_thread.ChBx_LB1_RpcRowData = false;

    lb_thread.ChBx_LB1_SelectTestSig = false;
    lb_thread.ChBx_LB1_ClockDeskew   = false;
    lb_thread.ChBx_LB1_FullWin       = false;
    lb_thread.ChBx_LB1_AdjWin        = false;

    //===================================================

    lb_thread.ChBx_LB2_1V = false;
    lb_thread.ChBx_LB2_1V8_Aux = false ;
    lb_thread.ChBx_LB2_1V_MGTAVCC = false;
    lb_thread.ChBx_LB2_1V_MGTAVTT = false;
    lb_thread.ChBx_LB2_1V_MGTVCCAUX = false;
    lb_thread.ChBx_LB2_1V5 = false;
    lb_thread.ChBx_LB2_1V8 = false;
    lb_thread.ChBx_LB2_2V5 = false;
    lb_thread.ChBx_LB2_3V3 = false;
    lb_thread.ChBx_LB2_3V3VDD = false;
    lb_thread.ChBx_LB2_CS1_Vout = false;
    lb_thread.ChBx_LB2_CS2_Vout = false;
    lb_thread.ChBx_LB2_CS3_Vout = false;

    lb_thread.ChBx_LB2_Temp_Sensor1 = false;
    lb_thread.ChBx_LB2_Temp_Sensor2 = false;
    lb_thread.ChBx_LB2_Temp_Sensor3 = false;
    lb_thread.ChBx_LB2_ADC_TEMP = false;
    lb_thread.ChBx_LB2_ADC_AVDD_2 = false;
    lb_thread.ChBx_LB2_ADC_GND = false;
    lb_thread.ChBx_LB2_FPGA_VCORE = false;
    lb_thread.ChBx_LB2_FPGA_VCCBRAM = false;
    lb_thread.ChBx_LB2_FPGA_VCCAUX = false;
    lb_thread.ChBx_LB2_FPGA_Temp = false;
    lb_thread.ChBx_LB2_ID_Number = false;
    lb_thread.ChBx_LB2_SEM_Counter = false;

    //======================================================

    //===================================================

    lb_thread.ChBx_LB3_1V = false;
    lb_thread.ChBx_LB3_1V8_Aux = false ;
    lb_thread.ChBx_LB3_1V_MGTAVCC = false;
    lb_thread.ChBx_LB3_1V_MGTAVTT = false;
    lb_thread.ChBx_LB3_1V_MGTVCCAUX = false;
    lb_thread.ChBx_LB3_1V5 = false;
    lb_thread.ChBx_LB3_1V8 = false;
    lb_thread.ChBx_LB3_2V5 = false;
    lb_thread.ChBx_LB3_3V3 = false;
    lb_thread.ChBx_LB3_3V3VDD = false;
    lb_thread.ChBx_LB3_CS1_Vout = false;
    lb_thread.ChBx_LB3_CS2_Vout = false;
    lb_thread.ChBx_LB3_CS3_Vout = false;

    lb_thread.ChBx_LB3_Temp_Sensor1 = false;
    lb_thread.ChBx_LB3_Temp_Sensor2 = false;
    lb_thread.ChBx_LB3_Temp_Sensor3 = false;
    lb_thread.ChBx_LB3_ADC_TEMP = false;
    lb_thread.ChBx_LB3_ADC_AVDD_2 = false;
    lb_thread.ChBx_LB3_ADC_GND = false;
    lb_thread.ChBx_LB3_FPGA_VCORE = false;
    lb_thread.ChBx_LB3_FPGA_VCCBRAM = false;
    lb_thread.ChBx_LB3_FPGA_VCCAUX = false;
    lb_thread.ChBx_LB3_FPGA_Temp = false;
    lb_thread.ChBx_LB3_ID_Number = false;
    lb_thread.ChBx_LB3_SEM_Counter = false;

    //======================================================

    //===================================================

    lb_thread.ChBx_LB4_1V = false;
    lb_thread.ChBx_LB4_1V8_Aux = false ;
    lb_thread.ChBx_LB4_1V_MGTAVCC = false;
    lb_thread.ChBx_LB4_1V_MGTAVTT = false;
    lb_thread.ChBx_LB4_1V_MGTVCCAUX = false;
    lb_thread.ChBx_LB4_1V5 = false;
    lb_thread.ChBx_LB4_1V8 = false;
    lb_thread.ChBx_LB4_2V5 = false;
    lb_thread.ChBx_LB4_3V3 = false;
    lb_thread.ChBx_LB4_3V3VDD = false;
    lb_thread.ChBx_LB4_CS1_Vout = false;
    lb_thread.ChBx_LB4_CS2_Vout = false;
    lb_thread.ChBx_LB4_CS3_Vout = false;

    lb_thread.ChBx_LB4_Temp_Sensor1 = false;
    lb_thread.ChBx_LB4_Temp_Sensor2 = false;
    lb_thread.ChBx_LB4_Temp_Sensor3 = false;
    lb_thread.ChBx_LB4_ADC_TEMP = false;
    lb_thread.ChBx_LB4_ADC_AVDD_2 = false;
    lb_thread.ChBx_LB4_ADC_GND = false;
    lb_thread.ChBx_LB4_FPGA_VCORE = false;
    lb_thread.ChBx_LB4_FPGA_VCCBRAM = false;
    lb_thread.ChBx_LB4_FPGA_VCCAUX = false;
    lb_thread.ChBx_LB4_FPGA_Temp = false;
    lb_thread.ChBx_LB4_ID_Number = false;
    lb_thread.ChBx_LB4_SEM_Counter = false;

    //======================================================

    //===================================================

    lb_thread.ChBx_LB5_1V = false;
    lb_thread.ChBx_LB5_1V8_Aux = false ;
    lb_thread.ChBx_LB5_1V_MGTAVCC = false;
    lb_thread.ChBx_LB5_1V_MGTAVTT = false;
    lb_thread.ChBx_LB5_1V_MGTVCCAUX = false;
    lb_thread.ChBx_LB5_1V5 = false;
    lb_thread.ChBx_LB5_1V8 = false;
    lb_thread.ChBx_LB5_2V5 = false;
    lb_thread.ChBx_LB5_3V3 = false;
    lb_thread.ChBx_LB5_3V3VDD = false;
    lb_thread.ChBx_LB5_CS1_Vout = false;
    lb_thread.ChBx_LB5_CS2_Vout = false;
    lb_thread.ChBx_LB5_CS3_Vout = false;

    lb_thread.ChBx_LB5_Temp_Sensor1 = false;
    lb_thread.ChBx_LB5_Temp_Sensor2 = false;
    lb_thread.ChBx_LB5_Temp_Sensor3 = false;
    lb_thread.ChBx_LB5_ADC_TEMP = false;
    lb_thread.ChBx_LB5_ADC_AVDD_2 = false;
    lb_thread.ChBx_LB5_ADC_GND = false;
    lb_thread.ChBx_LB5_FPGA_VCORE = false;
    lb_thread.ChBx_LB5_FPGA_VCCBRAM = false;
    lb_thread.ChBx_LB5_FPGA_VCCAUX = false;
    lb_thread.ChBx_LB5_FPGA_Temp = false;
    lb_thread.ChBx_LB5_ID_Number = false;
    lb_thread.ChBx_LB5_SEM_Counter = false;

    //======================================================

    //===================================================

    lb_thread.ChBx_LB6_1V = false;
    lb_thread.ChBx_LB6_1V8_Aux = false ;
    lb_thread.ChBx_LB6_1V_MGTAVCC = false;
    lb_thread.ChBx_LB6_1V_MGTAVTT = false;
    lb_thread.ChBx_LB6_1V_MGTVCCAUX = false;
    lb_thread.ChBx_LB6_1V5 = false;
    lb_thread.ChBx_LB6_1V8 = false;
    lb_thread.ChBx_LB6_2V5 = false;
    lb_thread.ChBx_LB6_3V3 = false;
    lb_thread.ChBx_LB6_3V3VDD = false;
    lb_thread.ChBx_LB6_CS1_Vout = false;
    lb_thread.ChBx_LB6_CS2_Vout = false;
    lb_thread.ChBx_LB6_CS3_Vout = false;

    lb_thread.ChBx_LB6_Temp_Sensor1 = false;
    lb_thread.ChBx_LB6_Temp_Sensor2 = false;
    lb_thread.ChBx_LB6_Temp_Sensor3 = false;
    lb_thread.ChBx_LB6_ADC_TEMP = false;
    lb_thread.ChBx_LB6_ADC_AVDD_2 = false;
    lb_thread.ChBx_LB6_ADC_GND = false;
    lb_thread.ChBx_LB6_FPGA_VCORE = false;
    lb_thread.ChBx_LB6_FPGA_VCCBRAM = false;
    lb_thread.ChBx_LB6_FPGA_VCCAUX = false;
    lb_thread.ChBx_LB6_FPGA_Temp = false;
    lb_thread.ChBx_LB6_ID_Number = false;
    lb_thread.ChBx_LB6_SEM_Counter = false;

    //======================================================

    //===================================================

    lb_thread.ChBx_LB7_1V = false;
    lb_thread.ChBx_LB7_1V8_Aux = false ;
    lb_thread.ChBx_LB7_1V_MGTAVCC = false;
    lb_thread.ChBx_LB7_1V_MGTAVTT = false;
    lb_thread.ChBx_LB7_1V_MGTVCCAUX = false;
    lb_thread.ChBx_LB7_1V5 = false;
    lb_thread.ChBx_LB7_1V8 = false;
    lb_thread.ChBx_LB7_2V5 = false;
    lb_thread.ChBx_LB7_3V3 = false;
    lb_thread.ChBx_LB7_3V3VDD = false;
    lb_thread.ChBx_LB7_CS1_Vout = false;
    lb_thread.ChBx_LB7_CS2_Vout = false;
    lb_thread.ChBx_LB7_CS3_Vout = false;

    lb_thread.ChBx_LB7_Temp_Sensor1 = false;
    lb_thread.ChBx_LB7_Temp_Sensor2 = false;
    lb_thread.ChBx_LB7_Temp_Sensor3 = false;
    lb_thread.ChBx_LB7_ADC_TEMP = false;
    lb_thread.ChBx_LB7_ADC_AVDD_2 = false;
    lb_thread.ChBx_LB7_ADC_GND = false;
    lb_thread.ChBx_LB7_FPGA_VCORE = false;
    lb_thread.ChBx_LB7_FPGA_VCCBRAM = false;
    lb_thread.ChBx_LB7_FPGA_VCCAUX = false;
    lb_thread.ChBx_LB7_FPGA_Temp = false;
    lb_thread.ChBx_LB7_ID_Number = false;
    lb_thread.ChBx_LB7_SEM_Counter = false;

    //======================================================

    //===================================================

    lb_thread.ChBx_LB8_1V = false;
    lb_thread.ChBx_LB8_1V8_Aux = false ;
    lb_thread.ChBx_LB8_1V_MGTAVCC = false;
    lb_thread.ChBx_LB8_1V_MGTAVTT = false;
    lb_thread.ChBx_LB8_1V_MGTVCCAUX = false;
    lb_thread.ChBx_LB8_1V5 = false;
    lb_thread.ChBx_LB8_1V8 = false;
    lb_thread.ChBx_LB8_2V5 = false;
    lb_thread.ChBx_LB8_3V3 = false;
    lb_thread.ChBx_LB8_3V3VDD = false;
    lb_thread.ChBx_LB8_CS1_Vout = false;
    lb_thread.ChBx_LB8_CS2_Vout = false;
    lb_thread.ChBx_LB8_CS3_Vout = false;

    lb_thread.ChBx_LB8_Temp_Sensor1 = false;
    lb_thread.ChBx_LB8_Temp_Sensor2 = false;
    lb_thread.ChBx_LB8_Temp_Sensor3 = false;
    lb_thread.ChBx_LB8_ADC_TEMP = false;
    lb_thread.ChBx_LB8_ADC_AVDD_2 = false;
    lb_thread.ChBx_LB8_ADC_GND = false;
    lb_thread.ChBx_LB8_FPGA_VCORE = false;
    lb_thread.ChBx_LB8_FPGA_VCCBRAM = false;
    lb_thread.ChBx_LB8_FPGA_VCCAUX = false;
    lb_thread.ChBx_LB8_FPGA_Temp = false;
    lb_thread.ChBx_LB8_ID_Number = false;
    lb_thread.ChBx_LB8_SEM_Counter = false;

    //======================================================

    //===================================================

    lb_thread.ChBx_LB9_1V = false;
    lb_thread.ChBx_LB9_1V8_Aux = false ;
    lb_thread.ChBx_LB9_1V_MGTAVCC = false;
    lb_thread.ChBx_LB9_1V_MGTAVTT = false;
    lb_thread.ChBx_LB9_1V_MGTVCCAUX = false;
    lb_thread.ChBx_LB9_1V5 = false;
    lb_thread.ChBx_LB9_1V8 = false;
    lb_thread.ChBx_LB9_2V5 = false;
    lb_thread.ChBx_LB9_3V3 = false;
    lb_thread.ChBx_LB9_3V3VDD = false;
    lb_thread.ChBx_LB9_CS1_Vout = false;
    lb_thread.ChBx_LB9_CS2_Vout = false;
    lb_thread.ChBx_LB9_CS3_Vout = false;

    lb_thread.ChBx_LB9_Temp_Sensor1 = false;
    lb_thread.ChBx_LB9_Temp_Sensor2 = false;
    lb_thread.ChBx_LB9_Temp_Sensor3 = false;
    lb_thread.ChBx_LB9_ADC_TEMP = false;
    lb_thread.ChBx_LB9_ADC_AVDD_2 = false;
    lb_thread.ChBx_LB9_ADC_GND = false;
    lb_thread.ChBx_LB9_FPGA_VCORE = false;
    lb_thread.ChBx_LB9_FPGA_VCCBRAM = false;
    lb_thread.ChBx_LB9_FPGA_VCCAUX = false;
    lb_thread.ChBx_LB9_FPGA_Temp = false;
    lb_thread.ChBx_LB9_ID_Number = false;
    lb_thread.ChBx_LB9_SEM_Counter = false;

    //======================================================

}

//==========================================================================
//          Function :
//
//==========================================================================

void MainWindow::Get_ch_thread_ChBx_Values(){

    //----------------------------------------------------------
    if (ui->ChBx_CB_1V->isChecked()) // check if repeat check box is checked
    {
        cb_thread.ChBx_CB_1V = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_1V8_Aux->isChecked())
    {
        cb_thread.ChBx_CB_1V8_Aux = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_1V_MGTAVCC->isChecked())
    {
        cb_thread.ChBx_CB_1V_MGTAVCC = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_1V_MGTAVTT->isChecked())
    {
        cb_thread.ChBx_CB_1V_MGTAVTT = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_1V_MGTVCCAUX->isChecked())
    {
        cb_thread.ChBx_CB_1V_MGTVCCAUX = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_1V5->isChecked())
    {
        cb_thread.ChBx_CB_1V5 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_1V8->isChecked())
    {
        cb_thread.ChBx_CB_1V8 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_2V5->isChecked())
    {
        cb_thread.ChBx_CB_2V5 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_3V3->isChecked())
    {
        cb_thread.ChBx_CB_3V3 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_3V3VDD->isChecked())
    {
        cb_thread.ChBx_CB_3V3VDD = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_CS1_Vout->isChecked())
    {
        cb_thread.ChBx_CB_CS1_Vout = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_CS2_Vout->isChecked())
    {
        cb_thread.ChBx_CB_CS2_Vout = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_CS3_Vout->isChecked())
    {
        cb_thread.ChBx_CB_CS3_Vout = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_Temp_Sensor1->isChecked())
    {
        cb_thread.ChBx_CB_Temp_Sensor1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_Temp_Sensor2->isChecked())
    {
        cb_thread.ChBx_CB_Temp_Sensor2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_Temp_Sensor3->isChecked())
    {
        cb_thread.ChBx_CB_Temp_Sensor3 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_ADC_TEMP->isChecked())
    {
        cb_thread.ChBx_CB_ADC_TEMP = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_ADC_AVDD_2->isChecked())
    {
        cb_thread.ChBx_CB_ADC_AVDD_2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_ADC_GND->isChecked())
    {
        cb_thread.ChBx_CB_ADC_GND = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FPGA_VCORE->isChecked())
    {
        cb_thread.ChBx_CB_FPGA_VCORE = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FPGA_VCCBRAM->isChecked())
    {
        cb_thread.ChBx_CB_FPGA_VCCBRAM = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FPGA_VCCAUX->isChecked())
    {
        cb_thread.ChBx_CB_FPGA_VCCAUX = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FPGA_Temp->isChecked())
    {
        cb_thread.ChBx_CB_FPGA_Temp = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_ID_Number->isChecked())
    {
        cb_thread.ChBx_CB_ID_Number = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_SEM_Counter->isChecked())
    {
        cb_thread.ChBx_CB_SEM_Counter = true;
    }
    //----------------------------------------------------------


    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB1_DAC1_Ch1_Set_Vth1->isChecked())
    {
        cb_thread.ChBx_CB_FEB1_DAC1_Ch1_Set_Vth1 = true;
        cb_thread.ChBx_CB_FEB1_DAC1_Ch1_Vth1_Value = ui->lineEdit_FEB1_DAC1_Ch1_Set_Vth1->text().toUInt();
        qDebug() << "cb_thread.ChBx_CB_FEB1_DAC1_Ch1_Vth1_Value" << cb_thread.ChBx_CB_FEB1_DAC1_Ch1_Vth1_Value;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB1_DAC1_Ch2_Set_Vth2->isChecked())
    {
        cb_thread.ChBx_CB_FEB1_DAC1_Ch2_Set_Vth2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB1_DAC1_Ch3_Set_Vmon1->isChecked())
    {
        cb_thread.ChBx_CB_FEB1_DAC1_Ch3_Set_Vmon1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB1_DAC1_Ch4_Set_Vmon2->isChecked())
    {
        cb_thread.ChBx_CB_FEB1_DAC1_Ch4_Set_Vmon2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB1_DAC1_ON->isChecked())
    {
        cb_thread.ChBx_CB_FEB1_DAC1_ON = true;
    }
    //----------------------------------------------------------



    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB1_ADC1_Read_Temp->isChecked())
    {
        cb_thread.ChBx_CB_FEB1_ADC1_Read_Temp = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB1_ADC1_Read_Ch1_Vth1->isChecked())
    {
        cb_thread.ChBx_CB_FEB1_ADC1_Read_Ch1_Vth1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB1_ADC1_Read_Ch2_Vth2->isChecked())
    {
        cb_thread.ChBx_CB_FEB1_ADC1_Read_Ch2_Vth2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB1_ADC1_Read_Ch3_VMon1->isChecked())
    {
        cb_thread.ChBx_CB_FEB1_ADC1_Read_Ch3_VMon1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB1_ADC1_Read_Ch4_VMon2->isChecked())
    {
        cb_thread.ChBx_CB_FEB1_ADC1_Read_Ch4_VMon2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB1_DAC2_Ch1_Set_Vth1->isChecked())
    {
        cb_thread.ChBx_CB_FEB1_DAC2_Ch1_Set_Vth1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB1_DAC2_Ch2_Set_Vth2->isChecked())
    {
        cb_thread.ChBx_CB_FEB1_DAC2_Ch2_Set_Vth2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB1_DAC2_Ch3_Set_Vmon1->isChecked())
    {
        cb_thread.ChBx_CB_FEB1_DAC2_Ch3_Set_Vmon1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB1_DAC2_Ch4_Set_Vmon2->isChecked())
    {
        cb_thread.ChBx_CB_FEB1_DAC2_Ch4_Set_Vmon2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB1_DAC2_ON->isChecked())
    {
        cb_thread.ChBx_CB_FEB1_DAC2_ON = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB1_ADC2_Read_Temp->isChecked())
    {
        cb_thread.ChBx_CB_FEB1_ADC2_Read_Temp = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB1_ADC2_Read_Ch1_Vth1->isChecked())
    {
        cb_thread.ChBx_CB_FEB1_ADC2_Read_Ch1_Vth1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB1_ADC2_Read_Ch2_Vth2->isChecked())
    {
        cb_thread.ChBx_CB_FEB1_ADC2_Read_Ch2_Vth2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB1_ADC2_Read_Ch3_VMon1->isChecked())
    {
        cb_thread.ChBx_CB_FEB1_ADC2_Read_Ch3_VMon1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB1_ADC2_Read_Ch4_VMon2->isChecked())
    {
        cb_thread.ChBx_CB_FEB1_ADC2_Read_Ch4_VMon2 = true;
    }
    //----------------------------------------------------------



    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB2_DAC1_Ch1_Set_Vth1->isChecked())
    {
        cb_thread.ChBx_CB_FEB2_DAC1_Ch1_Set_Vth1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB2_DAC1_Ch2_Set_Vth2->isChecked())
    {
        cb_thread.ChBx_CB_FEB2_DAC1_Ch2_Set_Vth2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB2_DAC1_Ch3_Set_Vmon1->isChecked())
    {
        cb_thread.ChBx_CB_FEB2_DAC1_Ch3_Set_Vmon1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB2_DAC1_Ch4_Set_Vmon2->isChecked())
    {
        cb_thread.ChBx_CB_FEB2_DAC1_Ch4_Set_Vmon2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB2_DAC1_ON->isChecked())
    {
        cb_thread.ChBx_CB_FEB2_DAC1_ON = true;
    }
    //----------------------------------------------------------




    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB2_DAC2_Ch1_Set_Vth1->isChecked())
    {
        cb_thread.ChBx_CB_FEB2_DAC2_Ch1_Set_Vth1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB2_DAC2_Ch2_Set_Vth2->isChecked())
    {
        cb_thread.ChBx_CB_FEB2_DAC2_Ch2_Set_Vth2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB2_DAC2_Ch3_Set_Vmon1->isChecked())
    {
        cb_thread.ChBx_CB_FEB2_DAC2_Ch3_Set_Vmon1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB2_DAC2_Ch4_Set_Vmon2->isChecked())
    {
        cb_thread.ChBx_CB_FEB2_DAC2_Ch4_Set_Vmon2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB2_DAC2_ON->isChecked())
    {
        cb_thread.ChBx_CB_FEB2_DAC2_ON = true;
    }
    //----------------------------------------------------------



    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB2_ADC1_Read_Temp->isChecked())
    {
        cb_thread.ChBx_CB_FEB2_ADC1_Read_Temp = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB2_ADC1_Read_Ch1_Vth1->isChecked())
    {
        cb_thread.ChBx_CB_FEB2_ADC1_Read_Ch1_Vth1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB2_ADC1_Read_Ch2_Vth2->isChecked())
    {
        cb_thread.ChBx_CB_FEB2_ADC1_Read_Ch2_Vth2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB2_ADC1_Read_Ch3_VMon1->isChecked())
    {
        cb_thread.ChBx_CB_FEB2_ADC1_Read_Ch3_VMon1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB2_ADC1_Read_Ch4_VMon2->isChecked())
    {
        cb_thread.ChBx_CB_FEB2_ADC1_Read_Ch4_VMon2 = true;
    }
    //----------------------------------------------------------


    //----------------------------------------------------------

    if(ui->ChBx_CB_FEB2_ADC2_Read_Temp->isChecked())
    {
        cb_thread.ChBx_CB_FEB2_ADC2_Read_Temp = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB2_ADC2_Read_Ch1_Vth1->isChecked())
    {
        cb_thread.ChBx_CB_FEB2_ADC2_Read_Ch1_Vth1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB2_ADC2_Read_Ch2_Vth2->isChecked())
    {
        cb_thread.ChBx_CB_FEB2_ADC2_Read_Ch2_Vth2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB2_ADC2_Read_Ch3_VMon1->isChecked())
    {
        cb_thread.ChBx_CB_FEB2_ADC2_Read_Ch3_VMon1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB2_ADC2_Read_Ch4_VMon2->isChecked())
    {
        cb_thread.ChBx_CB_FEB2_ADC2_Read_Ch4_VMon2 = true;
    }
    //----------------------------------------------------------






    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB3_DAC1_Ch1_Set_Vth1->isChecked())
    {
        cb_thread.ChBx_CB_FEB3_DAC1_Ch1_Set_Vth1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB3_DAC1_Ch2_Set_Vth2->isChecked())
    {
        cb_thread.ChBx_CB_FEB3_DAC1_Ch2_Set_Vth2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB3_DAC1_Ch3_Set_Vmon1->isChecked())
    {
        cb_thread.ChBx_CB_FEB3_DAC1_Ch3_Set_Vmon1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB3_DAC1_Ch4_Set_Vmon2->isChecked())
    {
        cb_thread.ChBx_CB_FEB3_DAC1_Ch4_Set_Vmon2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB3_DAC1_ON->isChecked())
    {
        cb_thread.ChBx_CB_FEB3_DAC1_ON = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB3_DAC2_Ch1_Set_Vth1->isChecked())
    {
        cb_thread.ChBx_CB_FEB3_DAC2_Ch1_Set_Vth1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB3_DAC2_Ch2_Set_Vth2->isChecked())
    {
        cb_thread.ChBx_CB_FEB3_DAC2_Ch2_Set_Vth2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB3_DAC2_Ch3_Set_Vmon1->isChecked())
    {
        cb_thread.ChBx_CB_FEB3_DAC2_Ch3_Set_Vmon1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB3_DAC2_Ch4_Set_Vmon2->isChecked())
    {
        cb_thread.ChBx_CB_FEB3_DAC2_Ch4_Set_Vmon2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB3_DAC2_ON->isChecked())
    {
        cb_thread.ChBx_CB_FEB3_DAC2_ON = true;
    }
    //----------------------------------------------------------





    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB3_ADC1_Read_Temp->isChecked())
    {
        cb_thread.ChBx_CB_FEB3_ADC1_Read_Temp = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB3_ADC1_Read_Ch1_Vth1->isChecked())
    {
        cb_thread.ChBx_CB_FEB3_ADC1_Read_Ch1_Vth1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB3_ADC1_Read_Ch2_Vth2->isChecked())
    {
        cb_thread.ChBx_CB_FEB3_ADC1_Read_Ch2_Vth2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB3_ADC1_Read_Ch3_VMon1->isChecked())
    {
        cb_thread.ChBx_CB_FEB3_ADC1_Read_Ch3_VMon1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB3_ADC1_Read_Ch4_VMon2->isChecked())
    {
        cb_thread.ChBx_CB_FEB3_ADC1_Read_Ch4_VMon2 = true;
    }
    //----------------------------------------------------------




    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB3_ADC2_Read_Temp->isChecked())
    {
        cb_thread.ChBx_CB_FEB3_ADC2_Read_Temp = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB3_ADC2_Read_Ch1_Vth1->isChecked())
    {
        cb_thread.ChBx_CB_FEB3_ADC2_Read_Ch1_Vth1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB3_ADC2_Read_Ch2_Vth2->isChecked())
    {
        cb_thread.ChBx_CB_FEB3_ADC2_Read_Ch2_Vth2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB3_ADC2_Read_Ch3_VMon1->isChecked())
    {
        cb_thread.ChBx_CB_FEB3_ADC2_Read_Ch3_VMon1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_CB_FEB3_ADC2_Read_Ch4_VMon2->isChecked())
    {
        cb_thread.ChBx_CB_FEB3_ADC2_Read_Ch4_VMon2 = true;
    }
    //----------------------------------------------------------

    if (ui->ChBx_CB_Cmd_Turn_ON_LB1->isChecked()){

        cb_thread.ChBx_CB_Cmd_Turn_ON_LBBX = true;
        cb_thread.ChBx_CB_Cmd_Turn_ON_LB1 = true;
    }

    if (ui->ChBx_CB_Cmd_Turn_ON_LB2->isChecked()){

        cb_thread.ChBx_CB_Cmd_Turn_ON_LBBX = true;
        cb_thread.ChBx_CB_Cmd_Turn_ON_LB2 = true;
    }

    if (ui->ChBx_CB_Cmd_Turn_ON_LB3->isChecked()){

        cb_thread.ChBx_CB_Cmd_Turn_ON_LBBX = true;
        cb_thread.ChBx_CB_Cmd_Turn_ON_LB3 = true;
    }

    if (ui->ChBx_CB_Cmd_Turn_ON_LB4->isChecked()){

        cb_thread.ChBx_CB_Cmd_Turn_ON_LBBX = true;
        cb_thread.ChBx_CB_Cmd_Turn_ON_LB4 = true;
    }

    if (ui->ChBx_CB_Cmd_Turn_ON_LB5->isChecked()){

        cb_thread.ChBx_CB_Cmd_Turn_ON_LBBX = true;
        cb_thread.ChBx_CB_Cmd_Turn_ON_LB5 = true;
    }

    if (ui->ChBx_CB_Cmd_Turn_ON_LB6->isChecked()){

        cb_thread.ChBx_CB_Cmd_Turn_ON_LBBX = true;
        cb_thread.ChBx_CB_Cmd_Turn_ON_LB6 = true;
    }

    if (ui->ChBx_CB_Cmd_Turn_ON_LB7->isChecked()){

        cb_thread.ChBx_CB_Cmd_Turn_ON_LBBX = true;
        cb_thread.ChBx_CB_Cmd_Turn_ON_LB7 = true;
    }
    if (ui->ChBx_CB_Cmd_Turn_ON_LB8->isChecked()){

        cb_thread.ChBx_CB_Cmd_Turn_ON_LBBX = true;
        cb_thread.ChBx_CB_Cmd_Turn_ON_LB8 = true;
    }
    if (ui->ChBx_CB_Cmd_Turn_ON_LB9->isChecked()){

        cb_thread.ChBx_CB_Cmd_Turn_ON_LBBX = true;
        cb_thread.ChBx_CB_Cmd_Turn_ON_LB9 = true;
    }


    //================================================================================
    //  Link Board 1
    //================================================================================
    //----------------------------------------------------------
    if (ui->ChBx_LB1_1V->isChecked()) // check if repeat check box is checked
    {
        lb_thread.ChBx_LB1_1V = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_1V8_Aux->isChecked())
    {
        lb_thread.ChBx_LB1_1V8_Aux = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_1V_MGTAVCC->isChecked())
    {
        lb_thread.ChBx_LB1_1V_MGTAVCC = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_1V_MGTAVTT->isChecked())
    {
        lb_thread.ChBx_LB1_1V_MGTAVTT = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_1V_MGTVCCAUX->isChecked())
    {
        lb_thread.ChBx_LB1_1V_MGTVCCAUX = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_1V5->isChecked())
    {
        lb_thread.ChBx_LB1_1V5 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_1V8->isChecked())
    {
        lb_thread.ChBx_LB1_1V8 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_2V5->isChecked())
    {
        lb_thread.ChBx_LB1_2V5 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_3V3->isChecked())
    {
        lb_thread.ChBx_LB1_3V3 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_3V3VDD->isChecked())
    {
        lb_thread.ChBx_LB1_3V3VDD = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_CS1_Vout->isChecked())
    {
        lb_thread.ChBx_LB1_CS1_Vout = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_CS2_Vout->isChecked())
    {
        lb_thread.ChBx_LB1_CS2_Vout = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_CS3_Vout->isChecked())
    {
        lb_thread.ChBx_LB1_CS3_Vout = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_Temp_Sensor1->isChecked())
    {
        lb_thread.ChBx_LB1_Temp_Sensor1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_Temp_Sensor2->isChecked())
    {
        lb_thread.ChBx_LB1_Temp_Sensor2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_Temp_Sensor3->isChecked())
    {
        lb_thread.ChBx_LB1_Temp_Sensor3 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_ADC_TEMP->isChecked())
    {
        lb_thread.ChBx_LB1_ADC_TEMP = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_ADC_AVDD_2->isChecked())
    {
        lb_thread.ChBx_LB1_ADC_AVDD_2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_ADC_GND->isChecked())
    {
        lb_thread.ChBx_LB1_ADC_GND = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_FPGA_VCORE->isChecked())
    {
        lb_thread.ChBx_LB1_FPGA_VCORE = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_FPGA_VCCBRAM->isChecked())
    {
        lb_thread.ChBx_LB1_FPGA_VCCBRAM = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_FPGA_VCCAUX->isChecked())
    {
        lb_thread.ChBx_LB1_FPGA_VCCAUX = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_FPGA_Temp->isChecked())
    {
        lb_thread.ChBx_LB1_FPGA_Temp = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_ID_Number->isChecked())
    {
        lb_thread.ChBx_LB1_ID_Number = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_SEM_Counter->isChecked())
    {
        lb_thread.ChBx_LB1_SEM_Counter = true;
    }
    //----------------------------------------------------------

    if(ui->ChBx_LB1_SelectTestSig->isChecked())
    {
        lb_thread.ChBx_LB1_SelectTestSig = true;
        lb_thread.LB1_TestSig_Number = ui->HS_LB1_TestSig->value();
    }

    //----------------------------------------------------------

    if(ui->ChBx_LB1_ClockDeskew->isChecked())
    {
        lb_thread.ChBx_LB1_ClockDeskew = true;
        lb_thread.LB1_ClockDeskew_Value = ui->HS_LB1_ClkDeskew->value();
    }

    //----------------------------------------------------------

    if(ui->ChBx_LB1_FullWin->isChecked())
    {
        lb_thread.ChBx_LB1_FullWin = true;
        lb_thread.LB1_FullWin_value = ui->HS_LB1_FullWin->value();
    }

    //----------------------------------------------------------

    if(ui->ChBx_LB1_AdjWin->isChecked())
    {
        lb_thread.ChBx_LB1_AdjWin = true;
        lb_thread.LB1_AdjWin_value = ui->HS_LB1_AdjWin->value();
    }

    //----------------------------------------------------------

    if(ui->ChBx_LB1_ReadMultiChCnts->isChecked())
    {
        lb_thread.ChBx_LB1_ReadMultiChCnts = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_TimingProfile->isChecked())
    {
        lb_thread.ChBx_LB1_TimingProfile = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB1_RpcRowData->isChecked())
    {
        lb_thread.ChBx_LB1_RpcRowData = true;
    }
    //----------------------------------------------------------

    if(ui->ChBx_BS_LB1->isChecked())
    {
        lb_thread.LB1_Select = true;
    }
    else
    {
       lb_thread.LB1_Select = false;
    }


    //================================================================================
    //  Link Board 2
    //================================================================================
    //----------------------------------------------------------
    if (ui->ChBx_LB2_1V->isChecked()) // check if repeat check box is checked
    {
        lb_thread.ChBx_LB2_1V = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB2_1V8_Aux->isChecked())
    {
        lb_thread.ChBx_LB2_1V8_Aux = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB2_1V_MGTAVCC->isChecked())
    {
        lb_thread.ChBx_LB2_1V_MGTAVCC = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB2_1V_MGTAVTT->isChecked())
    {
        lb_thread.ChBx_LB2_1V_MGTAVTT = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB2_1V_MGTVCCAUX->isChecked())
    {
        lb_thread.ChBx_LB2_1V_MGTVCCAUX = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB2_1V5->isChecked())
    {
        lb_thread.ChBx_LB2_1V5 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB2_1V8->isChecked())
    {
        lb_thread.ChBx_LB2_1V8 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB2_2V5->isChecked())
    {
        lb_thread.ChBx_LB2_2V5 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB2_3V3->isChecked())
    {
        lb_thread.ChBx_LB2_3V3 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB2_3V3VDD->isChecked())
    {
        lb_thread.ChBx_LB2_3V3VDD = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB2_CS1_Vout->isChecked())
    {
        lb_thread.ChBx_LB2_CS1_Vout = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB2_CS2_Vout->isChecked())
    {
        lb_thread.ChBx_LB2_CS2_Vout = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB2_CS3_Vout->isChecked())
    {
        lb_thread.ChBx_LB2_CS3_Vout = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB2_Temp_Sensor1->isChecked())
    {
        lb_thread.ChBx_LB2_Temp_Sensor1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB2_Temp_Sensor2->isChecked())
    {
        lb_thread.ChBx_LB2_Temp_Sensor2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB2_Temp_Sensor3->isChecked())
    {
        lb_thread.ChBx_LB2_Temp_Sensor3 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB2_ADC_TEMP->isChecked())
    {
        lb_thread.ChBx_LB2_ADC_TEMP = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB2_ADC_AVDD_2->isChecked())
    {
        lb_thread.ChBx_LB2_ADC_AVDD_2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB2_ADC_GND->isChecked())
    {
        lb_thread.ChBx_LB2_ADC_GND = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB2_FPGA_VCORE->isChecked())
    {
        lb_thread.ChBx_LB2_FPGA_VCORE = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB2_FPGA_VCCBRAM->isChecked())
    {
        lb_thread.ChBx_LB2_FPGA_VCCBRAM = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB2_FPGA_VCCAUX->isChecked())
    {
        lb_thread.ChBx_LB2_FPGA_VCCAUX = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB2_FPGA_Temp->isChecked())
    {
        lb_thread.ChBx_LB2_FPGA_Temp = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB2_ID_Number->isChecked())
    {
        lb_thread.ChBx_LB2_ID_Number = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB2_SEM_Counter->isChecked())
    {
        lb_thread.ChBx_LB2_SEM_Counter = true;
    }
    //----------------------------------------------------------



    //================================================================================
    //  Link Board 3
    //================================================================================
    /*
    //----------------------------------------------------------
    if (ui->ChBx_LB3_1V->isChecked()) // check if repeat check box is checked
    {
        lb_thread.ChBx_LB3_1V = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB3_1V8_Aux->isChecked())
    {
        lb_thread.ChBx_LB3_1V8_Aux = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB3_1V_MGTAVCC->isChecked())
    {
        lb_thread.ChBx_LB3_1V_MGTAVCC = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB3_1V_MGTAVTT->isChecked())
    {
        lb_thread.ChBx_LB3_1V_MGTAVTT = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB3_1V_MGTVCCAUX->isChecked())
    {
        lb_thread.ChBx_LB3_1V_MGTVCCAUX = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB3_1V5->isChecked())
    {
        lb_thread.ChBx_LB3_1V5 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB3_1V8->isChecked())
    {
        lb_thread.ChBx_LB3_1V8 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB3_2V5->isChecked())
    {
        lb_thread.ChBx_LB3_2V5 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB3_3V3->isChecked())
    {
        lb_thread.ChBx_LB3_3V3 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB3_3V3VDD->isChecked())
    {
        lb_thread.ChBx_LB3_3V3VDD = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB3_CS1_Vout->isChecked())
    {
        lb_thread.ChBx_LB3_CS1_Vout = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB3_CS2_Vout->isChecked())
    {
        lb_thread.ChBx_LB3_CS2_Vout = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB3_CS3_Vout->isChecked())
    {
        lb_thread.ChBx_LB3_CS3_Vout = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB3_Temp_Sensor1->isChecked())
    {
        lb_thread.ChBx_LB3_Temp_Sensor1 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB3_Temp_Sensor2->isChecked())
    {
        lb_thread.ChBx_LB3_Temp_Sensor2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB3_Temp_Sensor3->isChecked())
    {
        lb_thread.ChBx_LB3_Temp_Sensor3 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB3_ADC_TEMP->isChecked())
    {
        lb_thread.ChBx_LB3_ADC_TEMP = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB3_ADC_AVDD_2->isChecked())
    {
        lb_thread.ChBx_LB3_ADC_AVDD_2 = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB3_ADC_GND->isChecked())
    {
        lb_thread.ChBx_LB3_ADC_GND = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB3_FPGA_VCORE->isChecked())
    {
        lb_thread.ChBx_LB3_FPGA_VCORE = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB3_FPGA_VCCBRAM->isChecked())
    {
        lb_thread.ChBx_LB3_FPGA_VCCBRAM = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB3_FPGA_VCCAUX->isChecked())
    {
        lb_thread.ChBx_LB3_FPGA_VCCAUX = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB3_FPGA_Temp->isChecked())
    {
        lb_thread.ChBx_LB3_FPGA_Temp = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB3_ID_Number->isChecked())
    {
        lb_thread.ChBx_LB3_ID_Number = true;
    }
    //----------------------------------------------------------
    if(ui->ChBx_LB3_SEM_Counter->isChecked())
    {
        lb_thread.ChBx_LB3_SEM_Counter = true;
    }
    //----------------------------------------------------------
    */

}



//==========================================================================
//          Function :
//
//==========================================================================

void MainWindow::on_CB_RP_Load_clicked()
{

    QString FileName;
    QString FlashText;
    QString str;

    char file_data;
    unsigned char U_file_data ;
    QString string;
    UINT64 file_counter=0;

    unsigned char tempRead = 0 ;
    unsigned char niblLow = 0 ;
    unsigned char niblHigh = 0 ;
    unsigned char finalChar = 0 ;

    rp_thread.rp_remainLength = 0 ;
    rp_thread.rp_fileLength = 0 ;
    rp_thread.rp_packCnt = 0 ;
    rp_thread.packet_size = 200 ; //480

    QString filter = " MCS File (*.mcs);; Text File (*.txt) ;; All File (*.*) ";
    //FileName = QFileDialog::getOpenFileName(this,"Open a File", "C:\\M:\temp/QT/Sample1/LinkSystemGUI2/LSGUI/LSGUI/",filter);
    FileName = QFileDialog::getOpenFileName(this,"Open a File", QDir::toNativeSeparators(QDir::currentPath()),filter);

    QFile file(FileName);


    //--------------------------------------------------------
    if (!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(this,"Open File    ", "Error");
    }
    else
    {

        QTextStream in(&file);
        FlashText = in.readAll() ;
        fileLength = FlashText.size();
        qDebug() << "Flash File Length =" << fileLength ;
        file.close();

        //--------------------------------------------------------
        UsendBuf = (unsigned char*)malloc(fileLength); // char *flashBuf;
        memset(UsendBuf, 0, fileLength);
        //--------------------------------------------------------

        //--- Step 2 ----
        //  Load content of the flash buffet from configuration file
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this,"Open File    ", "Error");
        }
        else
        {
            while (!file.atEnd()){
                file.read(&file_data,sizeof(quint8));
                U_file_data = file_data;
                tempRead = conv_ascii_to_hex(U_file_data);
                if (tempRead != 127) {
                    niblHigh = tempRead ;
                    niblHigh = niblHigh << 4 ;
                }else{

                }

                file.read(&file_data,sizeof(quint8));
                U_file_data = file_data;
                tempRead = conv_ascii_to_hex(U_file_data);
                if (tempRead != 127) {
                    niblLow = tempRead ;
                    //niblLow = niblLow << 4 ;
                    finalChar = niblHigh | niblLow;

                    UsendBuf[file_counter] = finalChar;
                    //qDebug() << "niblHigh =" << niblHigh << "niblLow =" << niblLow << " UsendBuf[file_counter]" << UsendBuf[file_counter] ;
                    file_counter++;
                }
            }

            fileLength = file_counter;
            qDebug() << "Total number of Characters =" << file_counter ;
            file.close();


            //--- Step 3 ----
            //---------------------------------------------------------
            // push sendBuf buffer to the buffer of the Send Thread (rp_thread.t_sendBuf)
            //---------------------------------------------------------
            //rp_thread.rp_fileLength = fileLength;
            rp_thread.rp_fileLength = file_counter;

            rp_thread.rp_sendBuf = (unsigned char*)malloc(file_counter); // Create a buffer, char *sendBuf;
            memset(rp_thread.rp_sendBuf, 0, file_counter);      // Set all element to zero

            memcpy(rp_thread.rp_sendBuf,UsendBuf,file_counter);  // Copy current buffer to the thread buffer
            //---------------------------------------------------------
            rp_thread.rp_sendmem = (char*)malloc(rp_thread.packet_size); // Create a buffer, char *sendBuf;
            memset(rp_thread.rp_sendmem, 0, rp_thread.packet_size);
            //---------------------------------------------------------

            str = QString("%1").arg(file_counter);
            ui->lineEdit_fileSize->setText(str);


            load_complete = false;
            rp_thread.rp_quit = false;
            rp_thread.rp_prog_full = false;
            rp_thread.rp_packCnt = 0 ;
            rp_thread.rp_Addr_Ptr = 0 ;
            Prog_Full = 0 ;
            rp_thread.rp_cnt = 0 ;
            rp_thread.rp_remainLength = rp_thread.rp_fileLength - rp_thread.rp_packCnt ;
            //qDebug() << "rp_remainLength=" << rp_thread.rp_remainLength ;


            //--------------------------------------------
            //  To read the TCP control register, in the VHDL code, there is a process called
            //  TCP_regControler:process(Clke)
            //--------------------------------------------
            address = 4 ;
            ReadReg_status = YE_TCP_ReadReg(address); // At first, check buffer status
            qDebug() << "ReadReg_status" << ReadReg_status;

            str1 = QString("0x%1").arg(m_thread.t_value,0,16);
            ui->lineEdit_Reg4_Value->setText(str1);
            qDebug() << "t_value = " << QString("0x%1").arg(m_thread.t_value,0,16);


            Prog_Full = 0 ;
            Buf_empty = 0 ;

            Prog_Full = m_thread.t_value & 1 ; // Read Buffer Prog Full flag
            Buf_empty = m_thread.t_value & 2 ; // Read Buffer Empty flag

            qDebug() << "Prog_Full = " << Prog_Full;
            qDebug() << "Buf_empty = " << Buf_empty;

            rp_thread.RP_transaction(); //<---- START


            if ((Prog_Full == 0) & (Buf_empty == 2)) { // Buffer is empty and ready
                qDebug() << "State -0-" ;
                rp_thread.rp_prog_full = false; // Buffer is almost not full yet
                rp_thread.rp_buf_empty = true;  // Buffer is completely empty
                rp_thread.rp_buf_ready = true ; // Buffer is Ready
                rp_thread.RP_transaction(); //<---- START
            }
            else if ((Prog_Full == 1) & (Buf_empty == 0)) { // Almost full
                qDebug() << "State -1-" ;
                rp_thread.rp_prog_full = true; // Buffer is almost not full yet
                rp_thread.rp_buf_empty = false;  // Buffer is completely empty
                rp_thread.rp_buf_ready = false ; // Buffer is not Ready
                qtimer2 -> start(5); //<--- TIMER2 1000
            }
            else if ((Prog_Full == 0) & (Buf_empty == 0)) { // Almost Empty
                qDebug() << "State -2-" ;
                rp_thread.rp_prog_full = false; // Buffer is almost not full yet
                rp_thread.rp_buf_empty = false;  // Buffer is completely empty
                rp_thread.rp_buf_ready = false ; // Buffer is not Ready
                qtimer2 -> start(5); //<--- TIMER2 1000
            }
            else if ((Prog_Full == 1) & (Buf_empty == 2)) { // Forbidden Satatus
                qDebug() << "State -3-" ;
                rp_thread.rp_prog_full = true; // Buffer is almost full yet
                rp_thread.rp_buf_empty = true;  // Buffer is completely empty
                rp_thread.rp_buf_ready = false ; // Buffer is not Ready
                qtimer2 -> start(5); //<--- TIMER2 1000
            }

        }
     }
 }

//==========================================================================
//          Function :
//
//==========================================================================
 unsigned char MainWindow::conv_ascii_to_hex(unsigned char code)
 {

     unsigned char value;
     switch (code) {
         case '0' :value = 0;  break;
         case '1' :value = 1;  break;
         case '2' :value = 2;  break;
         case '3' :value = 3;  break;
         case '4' :value = 4;  break;
         case '5' :value = 5;  break;
         case '6' :value = 6;  break;
         case '7' :value = 7;  break;
         case '8' :value = 8;  break;
         case '9' :value = 9;  break;
         case 'A' :value = 10;  break;
         case 'B' :value = 11;  break;
         case 'C' :value = 12;  break;
         case 'D' :value = 13;  break;
         case 'E' :value = 14;  break;
         case 'F' :value = 15;  break;
         case 'a' :value = 10;  break;
         case 'b' :value = 11;  break;
         case 'c' :value = 12;  break;
         case 'd' :value = 13;  break;
         case 'e' :value = 14;  break;
         case 'f' :value = 15;  break;
         default: value = 127;  break;
     }
  return value;

 }

//==========================================================================
//          Function :
//
//==========================================================================

void MainWindow::ThreadSlot_rp_status_register( UINT32 RP_File_add_ptr){

    address = 4 ;
    ReadReg_status = YE_TCP_ReadReg(address); // At first, check buffer status

    str1 = QString("0x%1").arg(m_thread.t_value,0,16);
    ui->lineEdit_Reg4_Value->setText(str1);

    Prog_Full = 0 ;
    Buf_empty = 0 ;

    Prog_Full = m_thread.t_value & 1 ; // Read Buffer Prog Full flag
    Buf_empty = m_thread.t_value & 2 ; // Read Buffer Empty flag

    //qDebug() << "Prog_Full" << Prog_Full;
    //qDebug() << "Buf_empty" << Buf_empty;
    //qDebug() << "              " ;

    if ((Prog_Full == 0) & (Buf_empty == 2)) { // Buffer is ampty and ready
        qDebug() << "State -0-" ;
        rp_thread.rp_prog_full = false; // Buffer is almost not full yet
        rp_thread.rp_buf_empty = true;  // Buffer is completely empty
        rp_thread.rp_buf_ready = true ; // Buffer is Ready
        //rp_thread.RP_transaction(); //<---- START


        //--------------------------------------------
        str1 = QString("%1").arg(RP_File_add_ptr);
        ui->lineEdit_loadSize->setText(str1);
        //-------------------------------------------
        p1 = RP_File_add_ptr ;
        p2 = fileLength;
        p3 = (p1 / p2)*100 ;
        if (p3 < 100){
          progress = p3 ;
        }
        else
        {
          progress = 100;
          qtimer->stop();
          load_complete = true;
        }
        ui-> progressBar->setValue(progress);
        //------------------------------------------
        if (RP_File_add_ptr < fileLength ) {

            if (ui->radioButton_Load_Speed1->isChecked()){
                delay(500); // <---- For Debuging
            }else if (ui->radioButton_Load_Speed2->isChecked()){
                delay(100); // <---- For Debuging
            }else if (ui->radioButton_Load_Speed3->isChecked()){
                //delay(10); // <---- For Debuging
            }

            STAMP = RP_File_add_ptr ;
            qtimer -> start(5); // set timeout 50 ms
            //delay(5);
            rp_thread.RP_transaction();
        }
        else{
            QMessageBox::information(this,"Load File    ", "Done");
            qtimer->stop();
            load_complete = true;
        }//-----------------------------------------

    }
    else if ((Prog_Full == 1) & (Buf_empty == 0)) { // Almost full
        qDebug() << "State -1-" ;
        rp_thread.rp_prog_full = true; // Buffer is almost not full yet
        rp_thread.rp_buf_empty = false;  // Buffer is completely empty
        rp_thread.rp_buf_ready = false ; // Buffer is not Ready
        qtimer2 -> start(5); //<--- TIMER2 // 50
    }
    else if ((Prog_Full == 0) & (Buf_empty == 0)) { // Almost Empty
        qDebug() << "State -2-" ;
        rp_thread.rp_prog_full = false; // Buffer is almost not full yet
        rp_thread.rp_buf_empty = false;  // Buffer is completely empty
        rp_thread.rp_buf_ready = false ; // Buffer is not Ready
        qtimer2 -> start(5); //<--- TIMER2 -- 1000
    }
    else if ((Prog_Full == 1) & (Buf_empty == 2)) { // Forbidden Satatus
       qDebug() << "State -3-" ;
        rp_thread.rp_prog_full = true; // Buffer is almost full yet
        rp_thread.rp_buf_empty = true;  // Buffer is completely empty
        rp_thread.rp_buf_ready = false ; // Buffer is not Ready
        qtimer2 -> start(5); //<--- TIMER2 - 1000
    }

}


//==========================================================================
//          Function : TIMER TIMEOUT
//
//==========================================================================
void MainWindow::on_timeout(){

    qtimer->stop();
    //qDebug() << "Timer-1 Timeout" ;

    sent_char[1] = sent_char[0];
    sent_char[0] = STAMP;

    //qDebug() << "sent_char[1]" << sent_char[1] ;
    //qDebug() << "sent_char[0]" << sent_char[0] ;
    qtimer -> start(5); // set timeout 10 ms

    if ((sent_char[1]== sent_char[0]) && !(load_complete))
    {
       qtimer -> start(5); // set timeout 10 ms
       rp_thread.RP_transaction();

       //qDebug() << "Retrying Thread" ;
    }

}



//==========================================================================
//          Function : TIMER2 TIMEOUT
//
//==========================================================================
void MainWindow::on_timeout2(){

    qtimer2->stop();

    qDebug() << " " ;
    qDebug() << "TIMER-2 Timeout" ;

    address = 4 ;
    ReadReg_status = YE_TCP_ReadReg(address); // At first, check buffer status

    str1 = QString("0x%1").arg(m_thread.t_value,0,16);
    ui->lineEdit_Reg4_Value->setText(str1);


    Prog_Full = m_thread.t_value & 1 ; // Read Buffer Prog Full flag
    Buf_empty = m_thread.t_value & 2 ; // Read Buffer Empty flag

    //qDebug() << "TIMER-2 Timeout - Prog_Full" << Prog_Full;
    //qDebug() << "TIMER-2 Timeout - Buf_empty" << Buf_empty;

    if ((Prog_Full == 0) & (Buf_empty == 2)) { // Buffer is ampty and ready
        qDebug() << "TIMER-2 Timeout State -0-" ;
        rp_thread.rp_prog_full = false; // Buffer is almost not full yet
        rp_thread.rp_buf_empty = true;  // Buffer is completely empty
        rp_thread.rp_buf_ready = true ; // Buffer is Ready
        rp_thread.RP_transaction(); //<---- START
    }
    else if ((Prog_Full == 1) & (Buf_empty == 0)) { // Almost full
        qDebug() << "TIMER-2 Timeout State -1-" ;
        rp_thread.rp_prog_full = true; // Buffer is almost not full yet
        rp_thread.rp_buf_empty = false;  // Buffer is completely empty
        rp_thread.rp_buf_ready = false ; // Buffer is not Ready
        qtimer2 -> start(5); //<--- TIMER2 50 ms
    }
    else if ((Prog_Full == 0) & (Buf_empty == 0)) { // Almost Empty
        qDebug() << "TIMER-2 Timeout State -2-" ;
        rp_thread.rp_prog_full = false; // Buffer is almost not full yet
        rp_thread.rp_buf_empty = false;  // Buffer is completely empty
        rp_thread.rp_buf_ready = false ; // Buffer is not Ready
        qtimer2 -> start(5); //<--- TIMER2 50 ms
    }
    else if ((Prog_Full == 1) & (Buf_empty == 2)) { // Forbidden Satatus
        qDebug() << "TIMER-2 Timeout State -3-" ;
        rp_thread.rp_prog_full = true; // Buffer is almost full yet
        rp_thread.rp_buf_empty = true;  // Buffer is completely empty
        rp_thread.rp_buf_ready = false ; // Buffer is not Ready
        qtimer2 -> start(5); //<--- TIMER2 50 ms
    }

}

//==========================================================================
//          Function : TIMER3 TIMEOUT
//                     This timer is activated if in CB page
//                     auto trigger radio button is activated
//                     In this condition, after press UPDATE key
//                     all parameter periodically are plotted
//==========================================================================
void MainWindow::on_timeout3(){

    qtimer3->stop();
    qDebug() << "TIMER-3 Timeout" ;

    if (ui->radioButton_CB_ST1->isChecked()){

        retrig_interval = ui->lineEdit_25->text().toUInt();
        qtimer3->start(retrig_interval); // DEFAULT every 1500 ms

        ui->CB_Update->setPalette(QPalette(Qt::red));

        qDebug() << "TIMER-3 Restart" ;
        MainWindow::on_CB_Update_clicked();
    }


}


//==========================================================================
//          Function :
//
//==========================================================================
void MainWindow::on_CB_Stop_clicked()
{
    qtimer3->stop();
    qDebug() << "TIMER-3 Timeout" ;
    ui->radioButton_CB_ST0->setChecked(true);
    ui->radioButton_CB_ST1->setChecked(false);

}


//==========================================================================
//          Function : Test File Generator
//
//==========================================================================
void MainWindow::on_CB_RP_Verify_clicked()
{
    QString FileName;
    QString FlashText;
    QString str;
    QString string;


    QString filter = "Text File (*.txt) ;; MCS File (*.mcs) ;; All File (*.*) ";
    FileName = QFileDialog::getOpenFileName(this,"Open a File", "C:\\M:\temp/QT/Sample1/LinkSystemGUI2/LSGUI/LSGUI/",filter);
    QFile file(FileName);
    //--------------------------------------------------------
    if (!file.open(QIODevice::WriteOnly)){
        QMessageBox::information(this,"title", "file not open");
    }
    else
    {
        QDataStream out(&file);
        //QChar fillChar ;
        for (UINT i=0;i<256;i++){
            for (UINT j=0 ; j<256; j++){

                out << (qint8)j ;
                //str = QString("%1 ").arg(j,8,2, fillChar = QLatin1Char('0'));
                //out << str ;
                //qDebug()<<"str"<<str ;
            }
            //str = QString("\n");
            //out << str ;
            //qDebug()<<"str"<<str ;

        }
        //file.flush();
        file.close();
        QMessageBox::information(this,"title", "file is full");
    }

}



//==========================================================================
//          Function : Delay
//
//==========================================================================

void MainWindow::delay (int miliseconds){

    QEventLoop loop ;
    QTimer t ;
    t.connect(&t,&QTimer::timeout, &loop,&QEventLoop::quit);
    t.start(miliseconds);
    loop.exec();
}






//==========================================================================
//          Function :
//
//==========================================================================
void MainWindow::on_WriteConfig_clicked()
{

    unsigned int address = ui->lineEdit_5->text().toUInt();
    UINT value = ui->lineEdit_6->text().toUInt();

    WriteConfig(address, value);

    //YE_TCP_WriteConfig(address, value);

    /*
    qDebug() << "======================================================";
    qDebug() << " >> Read Configuration Register";
    qDebug() << " >> LAN status = "<<LanStatus ;
    USHORT address ;
    address = ui->lineEdit_5->text().toUShort();

    bool retVal = YE_TCP_ReadConfig(address);

    if (LanStatus){
        //this->transaction();

        if (!retVal)
        {
          str += QString("%1\n").arg("=========================");
          str += QString("%1\n").arg(">> Read Configuration Reg ERROR");
          str += QString("%1\n").arg("=========================");
        }
        else
        {

           str += QString("%1\n").arg("=========================");
           str += QString("%1\n").arg(">> Read Configuration Reg OK");

           str += QString("15-Register at Address (%1) = %2\n").arg(m_thread.t_address).arg(m_thread.t_value);
           str += QString("%1\n").arg("=========================");
           ui->textEdit->append(str);

           str1 = QString("%1").arg(m_thread.t_value);
           ui->lineEdit_6->setText(str1);
        }
    }
    */

}



//==========================================================================
//          Function :
//
//==========================================================================
void MainWindow::on_clear_pushBotton_2_clicked()
{
    str = QString("");
    str.clear();
    ui->textEdit->clear();
}

//==========================================================================
//          Function :
//
//==========================================================================
void MainWindow::sendSemCmd(unsigned int fileLength, char sendBuf[], unsigned int receiveBufSize, unsigned int cmdType, QString cmdText, unsigned int SemCnt){


    str3 = "" ;
    //------------------------------------------------
    str3 += QString("\n %1").arg("=========================");
    str3 += QString("\n %1%2%3").arg("No.").arg(SemCnt).arg(" - Clock :");
    str3+= TimeText;
    str3 += QString("\n %1").arg(cmdText);
    str3 += QString("\n ");
    //------------------------------------------------

    //------------------------------------------------------
    // First - Read Content of the File
    //------------------------------------------------------

    QFile file ("C:\\LinkSystemSEM.txt");
    if (!file.open(QFile::ReadOnly |QFile::Text)){
        str3 += QString("\n %1").arg("=========================");
        str3 += QString("\n %1").arg("FAIL IN READ FILE - FILE NOT OPEN");
        str3 += QString("\n %1").arg("=========================");
    }
    QTextStream in(&file);

    QString tempText1 = in.readAll(); // NOTE, TempText earas first and fills with new data
                             // Because += does not use here

    file.flush();
    file.close();

    //------------------------------------------------------
    // Second - Write log data to the the File
    //------------------------------------------------------

    QFile file2 ("C:\\LinkSystemSEM.txt");
    if (!file2.open(QFile::WriteOnly |QFile::Text)){
        str3 += QString("\n %1").arg("=========================");
        str3 += QString("\n %1").arg("FAIL IN WRITE FILE - FILE NOT OPEN");
        str3 += QString("\n %1").arg("=========================");
    }
    QTextStream out(&file2);


    tempText1 += str3;
    out << tempText1 ;

    //str2 += tempText1;
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText(tempText1);

    file2.flush();
    file2.close();
    //-------------------------------------------------------


    USHORT address  = 0 ;
    QString text;
    QByteArray text_qba;

    QString file_name;

    //address = ui->lineEdit_3->text().toUShort();
    //--------------------------------------------------------
    /*
    sendBuf = (char*)malloc(fileLength); // char *sendBuf;
    memset(sendBuf, 0, fileLength);
    */
    //--------------------------------------------------------

    /*
    SendFrame myFrame;

    myFrame.frame = ui->framelineEdit->text(); // Read string of 80-bits
    myFrame.config_buffer(); // Write 80-bit string to the 10-Bytes "char_array[i]"

    qDebug() << "frame value is :" << myFrame.frame;
    for (int i = 0 ; i < 16 ; i++)
    {
         sendBuf[i] = myFrame.char_array[i]; // Copy 10-byte of the char_array[i] to sendBuf
    }*/

    /*
    sendBuf[0] = 0X00;
    sendBuf[1] = 0X00;
    sendBuf[2] = 0X00;
    sendBuf[3] = 0X00;
    sendBuf[4] = 0X00;
    sendBuf[5] = 0X00;
    sendBuf[6] = 0X00;
    sendBuf[7] = 0X00;
    sendBuf[8] = 0X00;
    sendBuf[9] = 0X00;
    sendBuf[10] = 0X00;
    sendBuf[11] = 0X00;
    sendBuf[12] = 0X00;
    sendBuf[13] = 0X00;
    sendBuf[14] = 0X00;
    sendBuf[15] = 0X00;
    */

    //---------------------------------------------------------
    // push sendBuf buffer to the buffer of the Send Thread (s_thread.t_sendBuf)
    //---------------------------------------------------------

    s_thread.t_sendBuf = (char*)malloc(fileLength); // Create a buffer, char *sendBuf;
    memset(s_thread.t_sendBuf, 0, fileLength);      // Set all element to zero

    memcpy(s_thread.t_sendBuf,sendBuf,fileLength);  // Copy current buffer to the thread buffer
    //---------------------------------------------------------
    //s_thread.t_text = text;
    s_thread.t_fileLength = fileLength;             // Send size of buffer to the thread
    //---------------------------------------------------------

    //---------------------------------------------------------
    //if (ui->checkBox_4->isChecked()) // check if copy check box is checked
    //ui->plainTextEdit->setPlainText(text); // Copy content of file to the PlainText box

    qDebug() << "SEM Command Size (Byte) =" << fileLength;
    str += QString("%1\n").arg("=========================");
    str += QString("1-Bytes = %1\n").arg(fileLength); // Number of File lines
    str += QString("2-Words = %1\n").arg(fileLength/4);    // Number of Characters
    str += QString("%1\n").arg("=========================");
    ui->textEdit->append(str);


    //str2 += QString("%1\n").arg("=========================");
    //str2 += QString("%1\n").arg(" MONITORING SEM  ");
    //str2 += QString("%1\n").arg("=========================");
    //str.clear();
    //---------------------------------------------------------

    WriteConfig(0x00, 0x01u);   // Prepare Ethernt for Send packets
    s_thread.transaction_send(address); // Call Transaction funtion of the Thread
    //---------------------------------------------------------


    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    UINT iAsRateControl = 0x00u;

    //receiveBufSize = 120; //  Receive Buffer Size = Size of ProgFull

    //m_thread.t_receiveBuf = (unsigned char*) malloc(receiveBufSize); // Set the thread received buffer size

    memset(m_thread.t_receiveBuf, 0, receiveBufSize); // Set thread received buffers with 0s

    m_thread.t_receiveBufSize = receiveBufSize;
    m_thread.t_receiveBufIndex = 0 ;
    m_thread.t_buffer_full = 0 ;
    m_thread.t_receivedBuf = 0 ;
    m_thread.packetCount = 0 ;

    qDebug() << "======================================================";
    qDebug() << "   Receive BUFFER--";
    qDebug() << "   Receive Buffer Size = " << receiveBufSize ;
    qDebug() << "======================================================";

    m_thread.on_receive = true ;

    WriteReg(0x01, iAsRateControl); // (Address , Value) Request to Link Board for sending the BURST data
    WriteConfig(0x00, 0x02u);       // (Address , Value) AutoSend pin enable


    unsigned int uint_address = 4 ;
    UINT value = receiveBufSize * 65536 ; // set the length of send packet ;
    WriteConfig(uint_address, value); // write
    //------------------------------------------------


}




//==========================================================================
//          Function :
//
//==========================================================================
void MainWindow::on_monitorSem_clicked()
{

    SemCnt++;
    QString cmdTextStr = "COMMAND SEM MONITORING STATUS" ;
    unsigned int semCmdType = 1 ;

    receiveBufSize = 480;

    unsigned int fileLength = 16 ;
    sendBuf = (char*)malloc(fileLength); // char *sendBuf;
    memset(sendBuf, 0, fileLength);

    char sendBuf [16] ;
    sendBuf[0] = 0X00;
    sendBuf[1] = 0X00;
    sendBuf[2] = 0X00;
    sendBuf[3] = 0X00;
    sendBuf[4] = 0X00;
    sendBuf[5] = 0X00;
    sendBuf[6] = 0X00;
    sendBuf[7] = 0X00;
    sendBuf[8] = 0X00;
    sendBuf[9] = 0X00;
    sendBuf[10] = 0X00;
    sendBuf[11] = 0X00;
    sendBuf[12] = 0X00;
    sendBuf[13] = 0X00;
    sendBuf[14] = 0X00;
    sendBuf[15] = 0X00;

    sendSemCmd(fileLength, sendBuf, receiveBufSize, semCmdType, cmdTextStr, SemCnt );

}




//==========================================================================
//          Function :
//
//==========================================================================
void MainWindow::on_SemStatus_clicked()
{

    SemCnt++;
    QString cmdTextStr = "COMMAND SEM STATUS" ;
    unsigned int semCmdType = 2 ;

    receiveBufSize = 480;

    unsigned int fileLength = 16 ;
    sendBuf = (char*)malloc(fileLength); // char *sendBuf;
    memset(sendBuf, 0, fileLength);

    char sendBuf [16] ;

    sendBuf[0] = 0X49; // I
    sendBuf[1] = 0X53; // S
    sendBuf[2] = 0X00;
    sendBuf[3] = 0X00;
    sendBuf[4] = 0X00;
    sendBuf[5] = 0X00;
    sendBuf[6] = 0X00;
    sendBuf[7] = 0X00;
    sendBuf[8] = 0X00;
    sendBuf[9] = 0X00;
    sendBuf[10] = 0X00;
    sendBuf[11] = 0X00;
    sendBuf[12] = 0X00;
    sendBuf[13] = 0X00;
    sendBuf[14] = 0X00;
    sendBuf[15] = 0X00;

    sendSemCmd(fileLength, sendBuf, receiveBufSize, semCmdType, cmdTextStr, SemCnt );


}


//==========================================================================
//          Function :
//
//==========================================================================
void MainWindow::on_SemReset_clicked()
{


    SemCnt++;
    QString cmdTextStr = "COMMAND SEM RESET" ;
    unsigned int semCmdType = 3 ;

    receiveBufSize = 480;

    unsigned int fileLength = 16 ;
    sendBuf = (char*)malloc(fileLength); // char *sendBuf;
    memset(sendBuf, 0, fileLength);

    char sendBuf [16] ;

    sendBuf[0] = 0X49; // I
    sendBuf[1] = 0X52; // R
    sendBuf[2] = 0X20;
    sendBuf[3] = 0X30;
    sendBuf[4] = 0X30;
    sendBuf[5] = 0X00;
    sendBuf[6] = 0X00;
    sendBuf[7] = 0X00;
    sendBuf[8] = 0X00;
    sendBuf[9] = 0X00;
    sendBuf[10] = 0X00;
    sendBuf[11] = 0X00;
    sendBuf[12] = 0X00;
    sendBuf[13] = 0X00;
    sendBuf[14] = 0X00;
    sendBuf[15] = 0X00;

    sendSemCmd(fileLength, sendBuf, receiveBufSize, semCmdType, cmdTextStr, SemCnt );


}



//==========================================================================
//          Function :
//
//==========================================================================
void MainWindow::on_IdleState_clicked()
{


    SemCnt++;
    QString cmdTextStr = "COMMAND SEM IDLE" ;
    unsigned int semCmdType = 3 ;

    receiveBufSize = 480;

    unsigned int fileLength = 16 ;
    sendBuf = (char*)malloc(fileLength); // char *sendBuf;
    memset(sendBuf, 0, fileLength);

    char sendBuf [16] ;

    sendBuf[0] = 0X49; // I
    sendBuf[1] = 0X20;
    sendBuf[2] = 0X20;
    sendBuf[3] = 0X20;
    sendBuf[4] = 0X20;
    sendBuf[5] = 0X20;
    sendBuf[6] = 0X20;
    sendBuf[7] = 0X00;
    sendBuf[8] = 0X00;
    sendBuf[9] = 0X00;
    sendBuf[10] = 0X00;
    sendBuf[11] = 0X00;
    sendBuf[12] = 0X00;
    sendBuf[13] = 0X00;
    sendBuf[14] = 0X00;
    sendBuf[15] = 0X00;

    sendSemCmd(fileLength, sendBuf, receiveBufSize, semCmdType, cmdTextStr, SemCnt );

}




//==========================================================================
//          Function :
//
//==========================================================================
void MainWindow::on_Observation_clicked()
{

    SemCnt++;
    QString cmdTextStr = "COMMAND SEM OBSERVATION" ;
    unsigned int semCmdType = 3 ;

    receiveBufSize = 480;

    unsigned int fileLength = 16 ;
    sendBuf = (char*)malloc(fileLength); // char *sendBuf;
    memset(sendBuf, 0, fileLength);

    char sendBuf [16] ;


    sendBuf[0] = 0X4F; // I
    sendBuf[1] = 0X20;
    sendBuf[2] = 0X20;
    sendBuf[3] = 0X20;
    sendBuf[4] = 0X20;
    sendBuf[5] = 0X20;
    sendBuf[6] = 0X20;
    sendBuf[7] = 0X00;
    sendBuf[8] = 0X00;
    sendBuf[9] = 0X00;
    sendBuf[10] = 0X00;
    sendBuf[11] = 0X00;
    sendBuf[12] = 0X00;
    sendBuf[13] = 0X00;
    sendBuf[14] = 0X00;
    sendBuf[15] = 0X00;

    sendSemCmd(fileLength, sendBuf, receiveBufSize, semCmdType, cmdTextStr, SemCnt );



}

//==========================================================================
//          Function :
//
//==========================================================================
void MainWindow::on_Reserved_clicked()
{


}

//==========================================================================
//          Function :
//
//==========================================================================
void MainWindow::on_systemClock_timeout(){

    SystemTime = QTime::currentTime();

    TimeText = SystemTime.toString(" hh : mm : ss");
    ui->lineEdit_SysClock->setText(TimeText);

    //str2+= TimeText ;

    //ui->plainTextEdit->appendPlainText(str2);
}
//==========================================================================
//          Function :
//
//==========================================================================
void MainWindow::on_pushButton_3_clicked()
{

}

//==========================================================================
//          Function :
//
//==========================================================================
void MainWindow::on_pushButton_8_clicked()
{

}

//==========================================================================
//          Function :
//
//==========================================================================
void MainWindow::on_CB_Plot_clicked()
{

}
//==========================================================================
//          Function :
//
//==========================================================================
void MainWindow::on_CB_Clear_clicked()
{

}
//==========================================================================
//          Function :
//
//==========================================================================
void MainWindow::on_CB_Close_clicked()
{

}


//==========================================================================
//          Function :
//
//==========================================================================
void MainWindow::makeBackendPlot(void){

    //============================================================
    //  Plot-A RPC strip profile in "Bunch Crossing" VS "Sub-BX"
    //============================================================
    if (ui->ChBx_PlotSel_A->isChecked()){

        //backendbmu2 = new BackendEmu2();
        //backendbmu2 ->setWindowTitle(" PLOT-A) RPC Strip Hit Time Stamping");
        //backendbmu2 ->BeSetupPlot();

        if(backendbmu2 ->isVisible() == false){
            backendbmu2 ->show();
        }
    }

    /*
    unsigned int y0_StripData[200][200];
    unsigned int StripNum;
    StripNum = 1 ;
    //-----------------------------------------------
    backendbmu2->BePlotter(y0_StripData, StripNum);
    //-----------------------------------------------
    StripNum = 2 ;
    for (unsigned int jj=0;jj<125;jj++){
       y0_StripData[StripNum-1][jj] = jj;
    }
    //-----------------------------------------------
    backendbmu2->BePlotter(y0_StripData, StripNum);
    //-----------------------------------------------
    StripNum = 3 ;
    for (unsigned int jj=0;jj<125;jj++){
       y0_StripData[StripNum-1][jj] = 10;
    }
    //-----------------------------------------------
    backendbmu2->BePlotter(y0_StripData, StripNum);
    //-----------------------------------------------
    StripNum = 96 ;
    for (unsigned int jj=0;jj<125;jj++){
       y0_StripData[StripNum-1][jj] = 15;
    }
    //-----------------------------------------------
    backendbmu2->BePlotter(y0_StripData, StripNum);
    //============================================================
    */






    //============================================================
    //  Plot-B RPC strip profile in "Sub-BX" VS "Hit rate"
    //============================================================

    if (ui->ChBx_PlotSel_B->isChecked()){

        //backendstripprf = new BackendStripPrf();
        //backendstripprf ->setWindowTitle("PLOT-B) RPC Strip Hit Rate VS Sub-BX");
        //backendstripprf ->BeStripPrfSetupPlot();
        if(backendstripprf ->isVisible() == false){
            backendstripprf ->show();
        }
    }
    /*
    unsigned int y0_StripDataV2[200][200];
    unsigned int StripNumV2;
    StripNumV2 = 1 ;
    //-----------------------------------------------
    backendstripprf->BeStripPrfPlotter(y0_StripDataV2, StripNumV2);
    //-----------------------------------------------
    StripNumV2 = 2 ;
    for (unsigned int jj=0;jj<125;jj++){
       y0_StripDataV2[StripNumV2-1][jj] = jj;
    }
    //-----------------------------------------------
    backendstripprf->BeStripPrfPlotter(y0_StripDataV2, StripNumV2);
    //-----------------------------------------------
    StripNumV2 = 3 ;
    for (unsigned int jj=0;jj<125;jj++){
       y0_StripDataV2[StripNumV2-1][jj] = 10;
    }
    //-----------------------------------------------
    backendstripprf->BeStripPrfPlotter(y0_StripDataV2, StripNumV2);
    //-----------------------------------------------
    StripNumV2 = 96 ;
    for (unsigned int jj=0;jj<125;jj++){
       y0_StripDataV2[StripNumV2-1][jj] = 15;
    }
    //-----------------------------------------------
    backendstripprf->BeStripPrfPlotter(y0_StripDataV2, StripNumV2);
    //============================================================
    */




    //============================================================
    //  Plot-C Histogram "96-RPC channels" VS "Hit rate"
    //============================================================

    if (ui->ChBx_PlotSel_C->isChecked()){

        //backendhitplot = new BackendHitPlot();
        //backendhitplot ->setWindowTitle(" PLOT-C) RPC Hit Rate Histogram");
        //backendhitplot ->BeHistSetupPlot();
        if(backendhitplot ->isVisible() == false){
            backendhitplot ->show();
        }

    }

    /*
    unsigned int y0_HPStripData[200]; //
    unsigned int HPStripNum;

    HPStripNum = 1 ;
    y0_HPStripData[0]=0;
    y0_HPStripData[96]=30;
    for (unsigned int jj=1;jj<=96;jj++){
       y0_HPStripData[jj] = jj;
    }

    //-----------------------------------------------
    backendhitplot->BeHistPlotter(y0_HPStripData);
    //============================================================
    */

    //============================================================
    //  Plot-D Histogram "96-RPC channels" VS "Hit rate"
    //============================================================

    if (ui->ChBx_PlotSel_D->isChecked()){

        //backendtimingprf = new BackendTimingPrf();

        if(backendtimingprf ->isVisible() == false){
            backendtimingprf ->show();
        }

    }

    /*
    unsigned int y0_TimingPrfData[4000]; //
    unsigned int TPBxNum;

    TPBxNum = 1 ;
    y0_TimingPrfData[0]=0;
    y0_TimingPrfData[96]=30;
    for (unsigned int jj=1;jj<=3564;jj++){
       y0_TimingPrfData[jj] = jj;
    }
    //-----------------------------------------------
    backendtimingprf->BeTimingPrfPlotter(y0_TimingPrfData);
    //============================================================
    */
}

//==========================================================================
//
//==========================================================================
void MainWindow::BackendProcess(UINT32 frame_index , UINT32 packet_cnt){


    //Plot-C
    if (ui->ChBx_PlotSel_C->isChecked()){

        be_dpcPlotC_thread.packet_cnt_PlotC = packet_cnt;

        for (findex = 0 ; findex<120 ; findex++){
            be_dpcPlotC_thread.Rec_Reply_PlotC[findex][packet_cnt] = Rec_Reply[findex][packet_cnt];
        }

        be_dpcPlotC_thread.BE_dataProcessPlotC_transaction();

    }


    //Plot-D
    if (ui->ChBx_PlotSel_D->isChecked()){

        be_dpcPlotD_thread.packet_cnt_PlotD = packet_cnt;

        for (findex = 0 ; findex<120 ; findex++){
            be_dpcPlotD_thread.Rec_Reply_PlotD[findex][packet_cnt] = Rec_Reply[findex][packet_cnt];
        }

        be_dpcPlotD_thread.BE_dataProcessPlotD_transaction();
    }


    /*
    findex = 0 ;
    frameCnt = 0 ;

    for (findex = 0 ; findex<120 ; findex++){
        be_dpcPlotD_thread.Rec_Reply_PlotD[findex][packet_cnt] = Rec_Reply[findex][packet_cnt];
        be_dpcPlotC_thread.Rec_Reply_PlotC[findex][packet_cnt] = Rec_Reply[findex][packet_cnt];

    }


    be_dpcPlotD_thread.BE_dataProcessPlotD_transaction();
    be_dpcPlotC_thread.BE_dataProcessPlotC_transaction();
    */



    /*
    //qDebug() << "Backend Received Packet No. =: " << packet_cnt << "Frame No. =: " << frame_index ;


    findex = 0 ;
    frameCnt = 0 ;
    unsigned int  packet_cnt2 = 0;

    for (findex = 0 ; findex<117 ; findex=findex+3){

        //qDebug() << "1- findex : " << QString("%1").arg(findex, 0, 10);
        //qDebug() << "2- frameCnt : " << QString("%1").arg(frameCnt, 0, 10);


        //------------------------------------------------------------------------------
        //Field1 = Rec_Reply[findex+0][packet_cnt];
        //qDebug() << "3- 32-bit BE code(1) : " << QString("0x%1").arg(Field1, 0, 16);
        //------------------------------------------------------------------------------
        Field1 = Rec_Reply[findex+0][packet_cnt];
        Field1 = Field1 >> 26 ;
        //qDebug() << "4- CommadType : " << QString("0x%1").arg(Field1, 0, 16);
        //------------------------------------------------------------------------------
        if (Field1 == 15){

            Field1 = Rec_Reply[findex+0][packet_cnt];
            Field1 = Field1 << 6 ;
            hit1_stripNum[frameCnt][packet_cnt2] = Field1 >> 25 ;
            //qDebug() << "1- Hit-1 Strip No : " << QString("%1").arg(hit1_stripNum[frameCnt][packet_cnt], 0, 10);
            ////qDebug() << "5- Hit-1 Strip No : " << hit1_stripNum[frameCnt][packet_cnt];

            Field1 = Rec_Reply[findex+0][packet_cnt];
            Field1 = Field1 << 13 ;
            hit1_subBX[frameCnt][packet_cnt2] = Field1 >> 28 ;
            //qDebug() << "2- Hit-1 Sub-BX : " << QString("%1").arg(hit1_subBX[frameCnt][packet_cnt], 0, 10);
            //------------------------------------------------------------------------------
            Field1 = Rec_Reply[findex+0][packet_cnt];
            Field1 = Field1 << 17 ;
            hit2_stripNum[frameCnt][packet_cnt2] = Field1 >> 25 ;
            //qDebug() << "3- Hit-2 Strip No : " << QString("%1").arg(hit2_stripNum[frameCnt][packet_cnt], 0, 10);

            Field1 = Rec_Reply[findex+0][packet_cnt];
            Field1 = Field1 << 24 ;
            hit2_subBX[frameCnt][packet_cnt2] = Field1 >> 28 ;
            //qDebug() << "4- Hit-2 Sub-BX : " << QString("%1").arg(hit2_subBX[frameCnt][packet_cnt], 0, 10);
            //qDebug() << "" ;

            Field1 = Rec_Reply[findex+0][packet_cnt];
            //qDebug() << "5- Field(1) : " << QString("0x%1").arg(Field1, 0, 16);
            Field2 = Rec_Reply[findex+1][packet_cnt];
            //qDebug() << "6- Field(2) : " << QString("0x%1").arg(Field2, 0, 16);
            //------------------------------------------------------------------------------
            Field1 = Rec_Reply[findex+0][packet_cnt];
            Field1 = Field1 << 28 ;
            hit3_stripNum[frameCnt][packet_cnt2] = Field1 >> 25 ;
            //qDebug() << "7- Hit-3 Strip No (4-bit): " << QString("%1").arg(hit3_stripNum[frameCnt][packet_cnt], 0, 10);

            Field2 = Field2 >> 29 ;
            hit3_stripNum[frameCnt][packet_cnt2] = hit3_stripNum[frameCnt][packet_cnt2] | Field2 ;
            //qDebug() << "8- Hit-3 Strip No (7-bit): " << QString("%1").arg(hit3_stripNum[frameCnt][packet_cnt], 0, 10);

            Field2 = Rec_Reply[findex+1][packet_cnt];
            Field2 = Field2 << 3 ;
            hit3_subBX[frameCnt][packet_cnt2] = Field2 >> 28 ;
            //qDebug() << "9- Hit-3 Sub-BX : " << QString("%1").arg(hit3_subBX[frameCnt][packet_cnt], 0, 10);
            //qDebug() << "" ;
            //------------------------------------------------------------------------------
            Field1 = Rec_Reply[findex+0][packet_cnt];
            //qDebug() << "10- Field(1) : " << QString("0x%1").arg(Field1, 0, 16);
            Field2 = Rec_Reply[findex+1][packet_cnt];
            //qDebug() << "11- Field(2) : " << QString("0x%1").arg(Field2, 0, 16);
            //------------------------------------------------------------------------------
            Field2 = Rec_Reply[findex+1][packet_cnt];
            Field2 = Field2 << 7 ;
            hit4_stripNum [frameCnt][packet_cnt2]= Field2 >> 25 ;
            //qDebug() << "12- Hit-4 Strip No : " << QString("%1").arg(hit4_stripNum[frameCnt][packet_cnt], 0, 10);

            Field2 = Rec_Reply[findex+1][packet_cnt];
            Field2 = Field2 << 14 ;
            hit4_subBX [frameCnt][packet_cnt2]= Field2 >> 28 ;
            //qDebug() << "13- Hit-4 Sub-BX : " << QString("%1").arg(hit4_subBX[frameCnt][packet_cnt], 0, 10);
            //qDebug() << "" ;
            //------------------------------------------------------------------------------
            Field2 = Rec_Reply[findex+1][packet_cnt];
            Field2 = Field2 << 18 ;
            hit5_stripNum[frameCnt][packet_cnt2] = Field2 >> 25 ;
            //qDebug() << "14- Hit-5 Strip No : " << QString("%1").arg(hit5_stripNum[frameCnt][packet_cnt], 0, 10);

            Field2 = Rec_Reply[findex+1][packet_cnt];
            Field2 = Field2 << 25 ;
            hit5_subBX[frameCnt][packet_cnt2] = Field2 >> 28 ;
            //qDebug() << "15- Hit-5 Sub-BX : " << QString("%1").arg(hit5_subBX[frameCnt][packet_cnt], 0, 10);
            //qDebug() << "" ;
            //------------------------------------------------------------------------------
            Field2 = Rec_Reply[findex+1][packet_cnt];
            //qDebug() << "16- Field(2) : " << QString("0x%1").arg(Field2, 0, 16);
            Field3 = Rec_Reply[findex+2][packet_cnt];
            //qDebug() << "17- Field(3) : " << QString("0x%1").arg(Field3, 0, 16);
            //------------------------------------------------------------------------------
            Field2 = Rec_Reply[findex+1][packet_cnt];
            Field2 = Field2 << 29 ;
            hit6_stripNum[frameCnt][packet_cnt2] = Field2 >> 25 ;
            //qDebug() << "18- Hit-3 Strip No (3-bit): " << QString("%1").arg(hit6_stripNum[frameCnt][packet_cnt], 0, 10);

            Field3 = Field3 >> 28 ;
            hit6_stripNum[frameCnt][packet_cnt2] = hit6_stripNum[frameCnt][packet_cnt2] | Field3 ;
            //qDebug() << "19- Hit-3 Strip No (7-bit): " << QString("%1").arg(hit6_stripNum[frameCnt][packet_cnt], 0, 10);

            Field3 = Rec_Reply[findex+2][packet_cnt];
            Field3 = Field3 << 4 ;
            hit6_subBX[frameCnt][packet_cnt2] = Field3 >> 28 ;
            //qDebug() << "20- Hit-3 Sub-BX : " << QString("%1").arg(hit6_subBX[frameCnt][packet_cnt], 0, 10);
            //qDebug() << "" ;
            //------------------------------------------------------------------------------
            Field3 = Rec_Reply[findex+2][packet_cnt];
            //qDebug() << "21- Field(3) : " << QString("0x%1").arg(Field3, 0, 16);

            Field3 = Field3 << 8 ;
            bunchCrossing[frameCnt][packet_cnt2] = Field3 >> 20 ;
            //qDebug() << "22- Bunch Crossing : " << QString("%1").arg(bunchCrossing[frameCnt][packet_cnt], 0, 10);

            Field3 = Rec_Reply[findex+2][packet_cnt];
            Field3 = Field3 << 20 ;
            orbitNumber[frameCnt][packet_cnt2] = Field3 >> 20 ;
            //qDebug() << "23- Orbit Number : " << QString("%1").arg(orbitNumber[frameCnt][packet_cnt], 0, 10);
            //qDebug() << "" ;

            //------------------------------------------------------------------------------
            //  RPC hit time stamping - Plot A
            //------------------------------------------------------------------------------

            if (ui->ChBx_PlotSel_A->isChecked()){
                if ((hit1_stripNum[frameCnt][packet_cnt2]<=96)&&(hit1_subBX[frameCnt][packet_cnt2]<=16)&&(bunchCrossing[frameCnt][packet_cnt2]<=maxBX)){

                    ArrayPnt1 = hit1_stripNum[frameCnt][packet_cnt2] ;
                    ArrayPnt2 = bunchCrossing[frameCnt][packet_cnt2] ;

                    RPCStripHit[ArrayPnt1][ArrayPnt2] = hit1_subBX[frameCnt][packet_cnt2] ;
                    backendbmu2->BePlotter(RPCStripHit, hit1_stripNum[frameCnt][packet_cnt]);
                    //qDebug() << "1- Bunch Crossing : " << QString("%1").arg(bunchCrossing[frameCnt][packet_cnt], 0, 10);
                    //qDebug() << "2- Hit-1 Strip No : " << QString("%1").arg(hit1_stripNum[frameCnt][packet_cnt], 0, 10);
                    //qDebug() << "3- Hit-1 Sub-BX : " << QString("%1").arg(hit1_subBX[frameCnt][packet_cnt], 0, 10);
                }


                if ((hit2_stripNum[frameCnt][packet_cnt2]<=96)&&(hit2_subBX[frameCnt][packet_cnt2]<=16)&&(bunchCrossing[frameCnt][packet_cnt2]<=maxBX)){

                    //RPCStripHit[hit2_stripNum][bunchCrossing] = hit2_subBX ;
                    ArrayPnt1 = hit2_stripNum[frameCnt][packet_cnt2] ;
                    ArrayPnt2 = bunchCrossing[frameCnt][packet_cnt2] ;
                    RPCStripHit[ArrayPnt1][ArrayPnt2] = hit2_subBX[frameCnt][packet_cnt2] ;
                    backendbmu2->BePlotter(RPCStripHit, hit2_stripNum[frameCnt][packet_cnt]);
                    //qDebug() << "4- Hit-2 Strip No : " << QString("%1").arg(hit2_stripNum[frameCnt][packet_cnt], 0, 10);
                    //qDebug() << "5- Hit-2 Sub-BX : " << QString("%1").arg(hit2_subBX[frameCnt][packet_cnt], 0, 10);

                }

                if ((hit3_stripNum[frameCnt][packet_cnt2]<=96)&&(hit3_subBX[frameCnt][packet_cnt2]<=16)&&(bunchCrossing[frameCnt][packet_cnt2]<=maxBX)){

                    ArrayPnt1 = hit3_stripNum[frameCnt][packet_cnt2] ;
                    ArrayPnt2 = bunchCrossing[frameCnt][packet_cnt2] ;
                    RPCStripHit[ArrayPnt1][ArrayPnt2] = hit3_subBX[frameCnt][packet_cnt2] ;
                    backendbmu2->BePlotter(RPCStripHit, hit3_stripNum[frameCnt][packet_cnt]);
                    //qDebug() << "6- Hit-3 Strip No : " << QString("%1").arg(hit3_stripNum[frameCnt][packet_cnt], 0, 10);
                    //qDebug() << "7- Hit-3 Sub-BX : " << QString("%1").arg(hit3_subBX[frameCnt][packet_cnt], 0, 10);
                }

                if ((hit4_stripNum[frameCnt][packet_cnt2]<=96)&&(hit4_subBX[frameCnt][packet_cnt2]<=16)&&(bunchCrossing[frameCnt][packet_cnt2]<=maxBX)){

                    ArrayPnt1 = hit4_stripNum[frameCnt][packet_cnt2] ;
                    ArrayPnt2 = bunchCrossing[frameCnt][packet_cnt2] ;
                    RPCStripHit[ArrayPnt1][ArrayPnt2] = hit4_subBX[frameCnt][packet_cnt2] ;
                    backendbmu2->BePlotter(RPCStripHit, hit4_stripNum[frameCnt][packet_cnt]);
                    //qDebug() << "8- Hit-4 Strip No : " << QString("%1").arg(hit4_stripNum[frameCnt][packet_cnt], 0, 10);
                    //qDebug() << "9- Hit-4 Sub-BX : " << QString("%1").arg(hit4_subBX[frameCnt][packet_cnt], 0, 10);
                }

                if ((hit5_stripNum[frameCnt][packet_cnt2]<=96)&&(hit5_subBX[frameCnt][packet_cnt2]<=16)&&(bunchCrossing[frameCnt][packet_cnt2]<=maxBX)){

                    ArrayPnt1 = hit5_stripNum[frameCnt][packet_cnt2] ;
                    ArrayPnt2 = bunchCrossing[frameCnt][packet_cnt2] ;
                    RPCStripHit[ArrayPnt1][ArrayPnt2] = hit5_subBX[frameCnt][packet_cnt2] ;
                    backendbmu2->BePlotter(RPCStripHit, hit5_stripNum[frameCnt][packet_cnt]);
                    //qDebug() << "10- Hit-5 Strip No : " << QString("%1").arg(hit5_stripNum[frameCnt][packet_cnt], 0, 10);
                    //qDebug() << "11 Hit-5 Sub-BX : " << QString("%1").arg(hit5_subBX[frameCnt][packet_cnt], 0, 10);
                }

                if ((hit6_stripNum[frameCnt][packet_cnt2]<=96)&&(hit6_subBX[frameCnt][packet_cnt2]<=16)&&(bunchCrossing[frameCnt][packet_cnt2]<=maxBX)){

                    ArrayPnt1 = hit6_stripNum[frameCnt][packet_cnt2] ;
                    ArrayPnt2 = bunchCrossing[frameCnt][packet_cnt2] ;
                    RPCStripHit[ArrayPnt1][ArrayPnt2] = hit6_subBX[frameCnt][packet_cnt2] ;
                    backendbmu2->BePlotter(RPCStripHit, hit6_stripNum[frameCnt][packet_cnt]);
                    //qDebug() << "12- Hit-6 Strip No : " << QString("%1").arg(hit6_stripNum[frameCnt][packet_cnt], 0, 10);
                    //qDebug() << "13- Hit-6 Sub-BX : " << QString("%1").arg(hit6_subBX[frameCnt][packet_cnt], 0, 10);
                }

            }


            //------------------------------------------------------------------------------
            //  RPC hit timeStamping - Plot B
            //------------------------------------------------------------------------------
            if ((hit1_subBX[frameCnt][packet_cnt2]<=16)&&(hit1_stripNum[frameCnt][packet_cnt2]<=96)){

                ArrayPnt1 = hit1_subBX[frameCnt][packet_cnt2] ;
                ArrayPnt2 = hit1_stripNum[frameCnt][packet_cnt2] ;

                RPCHitSubBx[ArrayPnt1][ArrayPnt2] = RPCHitSubBx[ArrayPnt1][ArrayPnt2] + 1 ;
                //backendstripprf->BeStripPrfPlotter(RPCHitSubBx, hit1_stripNum[frameCnt][packet_cnt]);
                //qDebug() << "14- Hit-1 Strip No : " << QString("%1").arg(hit1_stripNum[frameCnt][packet_cnt], 0, 10);
                //qDebug() << "15- Hit-1 Sub-BX : " << QString("%1").arg(hit1_subBX[frameCnt][packet_cnt], 0, 10);
            }

            if ((hit2_subBX[frameCnt][packet_cnt2]<=16)&&(hit2_stripNum[frameCnt][packet_cnt2]<=96)){

                ArrayPnt1 = hit2_subBX[frameCnt][packet_cnt2] ;
                ArrayPnt2 = hit2_stripNum[frameCnt][packet_cnt2] ;
                //RPCHitSubBx[hit2_subBX][hit2_stripNum] = RPCHitSubBx[hit2_subBX][hit2_stripNum] + 1 ;
                RPCHitSubBx[ArrayPnt1][ArrayPnt2] = RPCHitSubBx[ArrayPnt1][ArrayPnt2] + 1 ;
                //backendstripprf->BeStripPrfPlotter(RPCHitSubBx, hit2_stripNum[frameCnt][packet_cnt]);
            }

            if ((hit3_subBX[frameCnt][packet_cnt2]<=16)&&(hit3_stripNum[frameCnt][packet_cnt2]<=96)){

                ArrayPnt1 = hit3_subBX[frameCnt][packet_cnt2] ;
                ArrayPnt2 = hit3_stripNum[frameCnt][packet_cnt2] ;

                RPCHitSubBx[ArrayPnt1][ArrayPnt2] = RPCHitSubBx[ArrayPnt1][ArrayPnt2] + 1 ;
                //backendstripprf->BeStripPrfPlotter(RPCHitSubBx, hit3_stripNum[frameCnt][packet_cnt]);
            }

            if ((hit4_subBX[frameCnt][packet_cnt2]<=16)&&(hit4_stripNum[frameCnt][packet_cnt2]<=96)){

                ArrayPnt1 = hit4_subBX[frameCnt][packet_cnt2] ;
                ArrayPnt2 = hit4_stripNum[frameCnt][packet_cnt2] ;

                RPCHitSubBx[ArrayPnt1][ArrayPnt2] = RPCHitSubBx[ArrayPnt1][ArrayPnt2] + 1 ;
                //backendstripprf->BeStripPrfPlotter(RPCHitSubBx, hit4_stripNum[frameCnt][packet_cnt]);
            }

            if ((hit5_subBX[frameCnt][packet_cnt2]<=16)&&(hit5_stripNum[frameCnt][packet_cnt2]<=96)){
                ArrayPnt1 = hit5_subBX[frameCnt][packet_cnt2] ;
                ArrayPnt2 = hit5_stripNum[frameCnt][packet_cnt2] ;

                RPCHitSubBx[ArrayPnt1][ArrayPnt2] = RPCHitSubBx[ArrayPnt1][ArrayPnt2] + 1 ;
                //backendstripprf->BeStripPrfPlotter(RPCHitSubBx, hit5_stripNum[frameCnt][packet_cnt]);
            }

            if ((hit6_subBX[frameCnt][packet_cnt2]<=16)&&(hit6_stripNum[frameCnt][packet_cnt2]<=96)){
                ArrayPnt1 = hit6_subBX[frameCnt][packet_cnt2] ;
                ArrayPnt2 = hit6_stripNum[frameCnt][packet_cnt2] ;

                RPCHitSubBx[ArrayPnt1][ArrayPnt2] = RPCHitSubBx[ArrayPnt1][ArrayPnt2] + 1 ;
                //backendstripprf->BeStripPrfPlotter(RPCHitSubBx, hit6_stripNum[frameCnt][packet_cnt]);
            }


            //------------------------------------------------------------------------------
            //  Histogram - Plot C
            //------------------------------------------------------------------------------

            if ((hit1_stripNum[frameCnt][packet_cnt2]<=96)&&(hit1_stripNum[frameCnt][packet_cnt2]!=127)){
                ArrayPnt1 = hit1_stripNum[frameCnt][packet_cnt2] ;
                RPCHist[ArrayPnt1] = RPCHist[ArrayPnt1] + 1 ;
            }

            if ((hit2_stripNum[frameCnt][packet_cnt2]<=96)&&(hit2_stripNum[frameCnt][packet_cnt2]!=127)){
                ArrayPnt1 = hit2_stripNum[frameCnt][packet_cnt2] ;
                RPCHist[ArrayPnt1] = RPCHist[ArrayPnt1] + 1 ;
            }

            if ((hit3_stripNum[frameCnt][packet_cnt2]<=96)&&(hit3_stripNum[frameCnt][packet_cnt2]!=127)){
                ArrayPnt1 = hit3_stripNum[frameCnt][packet_cnt2] ;
                RPCHist[ArrayPnt1] = RPCHist[ArrayPnt1] + 1 ;
            }

            if ((hit4_stripNum[frameCnt][packet_cnt2]<=96)&&(hit4_stripNum[frameCnt][packet_cnt2]!=127)){
                ArrayPnt1 = hit4_stripNum[frameCnt][packet_cnt2] ;
                RPCHist[ArrayPnt1] = RPCHist[ArrayPnt1] + 1 ;
            }

            if ((hit5_stripNum[frameCnt][packet_cnt2]<=96)&&(hit5_stripNum[frameCnt][packet_cnt2]!=127)){
                ArrayPnt1 = hit5_stripNum[frameCnt][packet_cnt2] ;
                RPCHist[ArrayPnt1] = RPCHist[ArrayPnt1] + 1 ;
            }

            if ((hit6_stripNum[frameCnt][packet_cnt2]<=96)&&(hit6_stripNum[frameCnt][packet_cnt2]!=127)){
                ArrayPnt1 = hit6_stripNum[frameCnt][packet_cnt2] ;
                RPCHist[ArrayPnt1] = RPCHist[ArrayPnt1] + 1 ;
            }


            //backendhitplot->BeHistPlotter(RPCHist);

            //backendhitplot->repaint();
            //backendhitplot->show();
            //-------------------------------------



            //------------------------------------------------------------------------------
            //  RPC hit timing Profile - Plot D
            //------------------------------------------------------------------------------

            ArrayPnt1 = bunchCrossing[frameCnt][packet_cnt2] ;

            if ((hit1_stripNum[frameCnt][packet_cnt2]<=96)&&(hit1_stripNum[frameCnt][packet_cnt2]!=127)){

                RPCHitTimingPrf[ArrayPnt1] =  RPCHitTimingPrf[ArrayPnt1] +  1 ;
            }

            if ((hit2_stripNum[frameCnt][packet_cnt2]<=96)&&(hit2_stripNum[frameCnt][packet_cnt2]!=127)){

                RPCHitTimingPrf[ArrayPnt1] =  RPCHitTimingPrf[ArrayPnt1] +  1 ;
            }

            if ((hit3_stripNum[frameCnt][packet_cnt2]<=96)&&(hit3_stripNum[frameCnt][packet_cnt2]!=127)){
                RPCHitTimingPrf[ArrayPnt1] =  RPCHitTimingPrf[ArrayPnt1] +  1 ;
            }

            if ((hit4_stripNum[frameCnt][packet_cnt2]<=96)&&(hit4_stripNum[frameCnt][packet_cnt2]!=127)){
                RPCHitTimingPrf[ArrayPnt1] =  RPCHitTimingPrf[ArrayPnt1] +  1 ;
            }

            if ((hit5_stripNum[frameCnt][packet_cnt2]<=96)&&(hit5_stripNum[frameCnt][packet_cnt2]!=127)){
                RPCHitTimingPrf[ArrayPnt1] =  RPCHitTimingPrf[ArrayPnt1] +  1 ;
            }

            if ((hit6_stripNum[frameCnt][packet_cnt2]<=96)&&(hit6_stripNum[frameCnt][packet_cnt2]!=127)){
                RPCHitTimingPrf[ArrayPnt1] =  RPCHitTimingPrf[ArrayPnt1] +  1 ;
            }
            //backendtimingprf->BeTimingPrfPlotter(RPCHitTimingPrf);
            //backendtimingprf->show();

        }
        else if(Field1 == 58){

        }

        frameCnt++;
    }

    //===========================================
    //
    //===========================================


    // PLOT A
    if (ui->ChBx_PlotSel_A->isChecked()){
        //backendbmu2->BePlotter(RPCStripHit, hit1_stripNum[frameCnt][packet_cnt]);
    }


    // PLOT B
    if (ui->ChBx_PlotSel_B->isChecked()){

    }

    // PLOT C
    if (ui->ChBx_PlotSel_C->isChecked()){
        backendhitplot->BeHistPlotter(RPCHist);
    }

    // PLOT D
    if (ui->ChBx_PlotSel_D->isChecked()){
        backendtimingprf->BeTimingPrfPlotter(RPCHitTimingPrf);
    }
    */

}


//==========================================================================
//          Function : Acknowledge function of the Receive Thread
//==========================================================================
/*
void MainWindow::ThreadSlot_be_dpc_plot( unsigned int frameCnt )//, boolean Buffer_full )
{


    //qDebug() << "BE_response_Thread: " << frameCnt ;

    // PLOT A
    if (ui->ChBx_PlotSel_A->isChecked()){
        //backendbmu2->BePlotter(RPCStripHit, hit1_stripNum[frameCnt][packet_cnt]);
    }


    // PLOT B
    if (ui->ChBx_PlotSel_B->isChecked()){

    }

    // PLOT C
    if (ui->ChBx_PlotSel_C->isChecked()){
        //backendhitplot->BeHistPlotter(RPCHist); //be_dpc_thread
        backendhitplot->BeHistPlotter(be_dpc_thread.RPCHist); //be_dpc_thread
    }

    // PLOT D
    if (ui->ChBx_PlotSel_D->isChecked()){
        //backendtimingprf->BeTimingPrfPlotter(RPCHitTimingPrf);
        backendtimingprf->BeTimingPrfPlotter(be_dpc_thread.RPCHitTimingPrf);
    }


    // PLOT D
    backendtimingprf->BeTimingPrfPlotter(be_dpc_thread.RPCHitTimingPrf);


}
*/



//==========================================================================
//          Function : Acknowledge function of the Receive Thread
//==========================================================================
void MainWindow::ThreadSlot_be_dpc_plotC( unsigned int frameCnt )//, boolean Buffer_full )
{

    // PLOT C

    backendhitplot->BeHistPlotter(be_dpcPlotC_thread.RPCHist_PlotC); //be_dpc_thread
}


//==========================================================================
//          Function : Acknowledge function of the Receive Thread
//==========================================================================
void MainWindow::ThreadSlot_be_dpc_plotD( unsigned int frameCnt )//, boolean Buffer_full )
{

    // PLOT D
    backendtimingprf->BeTimingPrfPlotter(be_dpcPlotD_thread.RPCHitTimingPrf_PlotD);

}


//==========================================================================
//          Function :
//==========================================================================
void MainWindow::on_pushButton_destroyed(QObject *arg1)
{


}


//==========================================================================
//          Function :
//==========================================================================

void MainWindow::on_Plot_ScaleTop_clicked()
{
    // PLOT A
    //if (ui->ChBx_PlotSel_A->isChecked()){
    //    //backendbmu2->BePlotter(RPCStripHit, hit1_stripNum[frameCnt][packet_cnt]);
    //}


    // PLOT B
    //if (ui->ChBx_PlotSel_B->isChecked()){
    //
    //}

    // PLOT C
    if (ui->ChBx_PlotSel_C->isChecked()){

        backendhitplot-> BackendHitPlot_scaleTop();

    }

    // PLOT D
    if (ui->ChBx_PlotSel_D->isChecked()){

        backendtimingprf->BeTimingPrf_scaleTop();

    }

}

//==========================================================================
//          Function :
//==========================================================================
void MainWindow::on_Plot_ScaleWindow_clicked()
{

    // PLOT A
    //if (ui->ChBx_PlotSel_A->isChecked()){
    //    //backendbmu2->BePlotter(RPCStripHit, hit1_stripNum[frameCnt][packet_cnt]);
    //}


    // PLOT B
    //if (ui->ChBx_PlotSel_B->isChecked()){
    //
    //}

    // PLOT C
    if (ui->ChBx_PlotSel_C->isChecked()){

        backendhitplot-> BackendHitPlot_scaleWindow();

    }

    // PLOT D
    if (ui->ChBx_PlotSel_D->isChecked()){

        backendtimingprf->BeTimingPrf_scaleWindow();

    }
}


void MainWindow::on_CB_RP_Prog_clicked()
{

}


void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
    if (ui->checkBox_4->isChecked()){

        qDebug() << "ALL Checked";


        ui->ChBx_CB_1V          ->setChecked(1);
        ui->ChBx_CB_1V8_Aux     ->setChecked(1);
        ui->ChBx_CB_1V_MGTAVCC  ->setChecked(1);
        ui->ChBx_CB_1V_MGTAVTT  ->setChecked(1);
        ui->ChBx_CB_1V_MGTVCCAUX->setChecked(1);
        ui->ChBx_CB_1V_MGTVCCAUX->setChecked(1);
        ui->ChBx_CB_1V5         ->setChecked(1);
        ui->ChBx_CB_1V8         ->setChecked(1);
        ui->ChBx_CB_2V5         ->setChecked(1);
        ui->ChBx_CB_3V3         ->setChecked(1);
        ui->ChBx_CB_3V3VDD      ->setChecked(1);
        ui->ChBx_CB_CS1_Vout    ->setChecked(1);
        ui->ChBx_CB_CS2_Vout    ->setChecked(1);
        ui->ChBx_CB_CS3_Vout    ->setChecked(1);

        ui->ChBx_CB_Temp_Sensor1->setChecked(1);
        ui->ChBx_CB_Temp_Sensor2->setChecked(1);
        ui->ChBx_CB_Temp_Sensor3->setChecked(1);
        ui->ChBx_CB_ADC_TEMP    ->setChecked(1);
        ui->ChBx_CB_ADC_AVDD_2  ->setChecked(1);
        ui->ChBx_CB_ADC_GND     ->setChecked(1);
        //ui->ChBx_CB_FPGA_VCORE  ->setChecked(1);
        //ui->ChBx_CB_FPGA_VCCBRAM->setChecked(1);
        //ui->ChBx_CB_FPGA_VCCAUX ->setChecked(1);
        //ui->ChBx_CB_FPGA_Temp   ->setChecked(1);
        ui->ChBx_CB_ID_Number   ->setChecked(1);
        //ui->ChBx_CB_SEM_Counter ->setChecked(1);


    }else{
       qDebug() << "ALL Un-Checked";


       ui->ChBx_CB_1V          ->setChecked(0);
       ui->ChBx_CB_1V8_Aux     ->setChecked(0);
       ui->ChBx_CB_1V_MGTAVCC  ->setChecked(0);
       ui->ChBx_CB_1V_MGTAVTT  ->setChecked(0);
       ui->ChBx_CB_1V_MGTVCCAUX->setChecked(0);
       ui->ChBx_CB_1V_MGTVCCAUX->setChecked(0);
       ui->ChBx_CB_1V5         ->setChecked(0);
       ui->ChBx_CB_1V8         ->setChecked(0);
       ui->ChBx_CB_2V5         ->setChecked(0);
       ui->ChBx_CB_3V3         ->setChecked(0);
       ui->ChBx_CB_3V3VDD      ->setChecked(0);
       ui->ChBx_CB_CS1_Vout    ->setChecked(0);
       ui->ChBx_CB_CS2_Vout    ->setChecked(0);
       ui->ChBx_CB_CS3_Vout    ->setChecked(0);

       ui->ChBx_CB_Temp_Sensor1->setChecked(0);
       ui->ChBx_CB_Temp_Sensor2->setChecked(0);
       ui->ChBx_CB_Temp_Sensor3->setChecked(0);
       ui->ChBx_CB_ADC_TEMP    ->setChecked(0);
       ui->ChBx_CB_ADC_AVDD_2  ->setChecked(0);
       ui->ChBx_CB_ADC_GND     ->setChecked(0);
       //ui->ChBx_CB_FPGA_VCORE  ->setChecked(0);
       //ui->ChBx_CB_FPGA_VCCBRAM->setChecked(0);
       //ui->ChBx_CB_FPGA_VCCAUX ->setChecked(0);
       //ui->ChBx_CB_FPGA_Temp   ->setChecked(0);
       ui->ChBx_CB_ID_Number   ->setChecked(0);
       //ui->ChBx_CB_SEM_Counter ->setChecked(0);


    }
}

