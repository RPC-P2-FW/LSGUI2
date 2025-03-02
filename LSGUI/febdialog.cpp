#include "febdialog.h"
#include "ui_febdialog.h"
#include <QWaitCondition>
#include <QString>
#include <QObject>
#include <QtCore>

febDialog::febDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::febDialog)
{
    ui->setupUi(this);
}

febDialog::~febDialog()
{
    delete ui;
}

void febDialog::on_pushButton_clicked()
{
    unsigned int aw, bw, cw, dw , tw ;
    unsigned int w[4] = {};
    unsigned char i = 0 ;

    aw = 0 ;
    bw = 0 ;
    cw = 0 ;
    dw = 0 ;

    tw = 0 ;

    w[0]=  0xD0D0D0D0;
    w[1]=  0xD0D00000,
    w[2]=  0x00000000,
    w[3]=  0x00000000;

    unsigned int cmd_opr = 0 ;
    unsigned int db_no = 0 ;
    unsigned int db_port = 0 ;
    unsigned int feb_no = 0 ;
    unsigned int dac_no = 0 ;
    unsigned int dac_ch = 0 ;
    unsigned int adc_no = 0 ;
    unsigned int adc_ch = 0 ;
    unsigned int cmd = 2 ;

    for (i=0;i<4;i++){
        qDebug() << QString("w(%1)=0x%2").arg(i).arg(w[i], 8, 16, QChar('0'));
    }

    for (i=0;i<4;i++){
        qDebug() << QString("w(%1)=0x%2").arg(i).arg(w[i], 32, 2, QChar('0'));
    }

    QString dac_value_str = ui->lineEdit_dacValue->text();
    ui->plainTextEdit->setPlainText(dac_value_str);

    unsigned int dac_value_int = ui->lineEdit_dacValue->text().toUInt();



    qDebug() << QString("dac= 0x%1").arg(dac_value_int, 32, 2, QChar('0'));
    //ui->plainTextEdit->setPlainText(dac_value_int);

    aw = dac_value_int << 26;
    //qDebug() << QString("aw=  0x%1").arg(aw, 32, 2, QChar('0'));

    tw = dac_value_int >> 6;
    //qDebug() << QString("tw=  0x%1").arg(tw, 32, 2, QChar('0'));

    if (ui->rB_Feb_Read->isChecked()){
        cmd_opr = 0 ;
    }
    if (ui->rB_Feb_Set ->isChecked()){
        cmd_opr = 1 ;
    }
    //---------------------------------------------------
    if (ui->rB_DB_No1->isChecked()){
        db_no = 0 ;
    }
    if (ui->rB_DB_No2 ->isChecked()){
        db_no = 1 ;
    }
    if (ui->rB_DB_No3 ->isChecked()){
        db_no = 2 ;
    }
    //---------------------------------------------------
    if (ui->rB_DB_P1->isChecked()){
        db_port = 0 ;
    }
    if (ui->rB_DB_P2->isChecked()){
        db_port = 1 ;
    }
    //---------------------------------------------------
    if (ui->rB_Feb1->isChecked()){
        feb_no = 0;
    }
    if (ui->rB_Feb2->isChecked()){
        feb_no = 1;
    }
    if (ui->rB_Feb3->isChecked()){
        feb_no = 2;
    }
    if (ui->rB_Feb4->isChecked()){
        feb_no = 3;
    }
    //---------------------------------------------------
    if (ui->rB_Dac1->isChecked()) {
        dac_no = 0;
    }
    if (ui->rB_Dac2->isChecked()) {
        dac_no = 1;
    }

    //---------------------------------------------------
    if (ui->rB_Vth1->isChecked()) {
        dac_ch = 1;
    }
    if (ui->rB_Vth2->isChecked()) {
        dac_ch = 2;
    }
    if (ui->rB_Vmon1->isChecked()) {
        dac_ch = 3;
    }
    if (ui->rB_Vmon2->isChecked()) {
        dac_ch = 4;
    }
    //---------------------------------------------------
    //---------------------------------------------------
    if (ui->rB_Adc1->isChecked()) {
        adc_no = 0;
    }
    if (ui->rB_Adc2->isChecked()) {
        adc_no = 1;
    }

    //---------------------------------------------------
    dac_ch  = dac_ch    <<  4 ;
    dac_no  = dac_no    << (3+4);
    adc_no  = adc_no    << (3+4);
    feb_no  = feb_no    << (1+3+4);
    db_port = db_port   << (2+1+3+4);
    db_no   = db_no     << (1+2+1+3+4);
    cmd_opr = cmd_opr   << (3+1+2+1+3+4);
    bw |= dac_ch  ;
    bw |= dac_no  ;
    bw |= adc_no  ;
    bw |= feb_no  ;
    bw |= db_port ;
    bw |= db_no   ;
    bw |= cmd_opr ;
    bw |= tw ;

    qDebug() << QString("aw=  0x%1").arg(aw, 32, 2, QChar('0'));
    qDebug() << QString("bw=  0x%1").arg(bw, 32, 2, QChar('0'));

    cw = 0xd0d00000;
    cmd = 2 ;
    cmd = cmd   << (2+6);
    cw |= cmd ;
    qDebug() << QString("cw=  0x%1").arg(cw, 32, 2, QChar('0'));

    dw = 0xd0d0d0d0 ;
    qDebug() << QString("dw=  0x%1").arg(dw, 32, 2, QChar('0'));

    qDebug() << QString("aw=  0x%1").arg(aw, 8, 16, QChar('0'));
    qDebug() << QString("bw=  0x%1").arg(bw, 8, 16, QChar('0'));
    qDebug() << QString("cw=  0x%1").arg(cw, 8, 16, QChar('0'));
    qDebug() << QString("dw=  0x%1").arg(dw, 8, 16, QChar('0'));

    QString aw_s ;
    aw_s  = QString("0x%1\n").arg(dw, 8, 16, QChar('0'));
    aw_s += QString("0x%1\n").arg(cw, 8, 16, QChar('0'));
    aw_s += QString("0x%1\n").arg(bw, 8, 16, QChar('0'));
    aw_s += QString("0x%1\n").arg(aw, 8, 16, QChar('0'));

    ui->plainTextEdit->setPlainText(aw_s);


    aw_s  = QString("%1\n").arg(dw, 32, 2, QChar('0'));
    aw_s += QString("%1\n").arg(cw, 32, 2, QChar('0'));
    aw_s += QString("%1\n").arg(bw, 32, 2, QChar('0'));
    aw_s += QString("%1\n").arg(aw, 32, 2, QChar('0'));

    ui->plainTextEdit_2->setPlainText(aw_s);


}

