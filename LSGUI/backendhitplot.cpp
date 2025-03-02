#include "backendhitplot.h"
#include "ui_backendhitplot.h"


#include "qcustomplot.h"

#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <QScrollArea>
#include <QScrollBar>
#include <QStandardPaths>
#include <QStatusBar>

QVector<double> tickN2(200) ;
QVector <double> y1_StripValue(200);

BackendHitPlot::BackendHitPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BackendHitPlot)
{
    ui->setupUi(this);
    BeHistSetupPlot();

}

BackendHitPlot::~BackendHitPlot()
{
    delete ui;
}


void BackendHitPlot::BeHistSetupPlot(void){

    ui->BeHPPlot->plotLayout()->clear();

    QCPLayoutGrid *mainLayout = new QCPLayoutGrid;
    ui->BeHPPlot->plotLayout()->addElement( 0 , 0 , mainLayout);

    subRect= new QCPAxisRect(ui->BeHPPlot, true);
    //subRect2= new QCPAxisRect(ui->BeHPPlot, true);
    mainLayout->addElement( 0 , 0, subRect  );
    //mainLayout->addElement( 0 , 0, subRect2  );
    //==================================================================
    ui->BeHPPlot->axisRect()->setupFullAxesBox(true);
    ui->BeHPPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                                  QCP::iSelectAxes | QCP::iSelectLegend |QCP::iSelectPlottables);
    //==================================================================


    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->BeHPPlot);
    subRect->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    foreach (QCPAxisRect *rect, ui->BeHPPlot->axisRects())
    {
      foreach (QCPAxis *axis, rect->axes())
      {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
        //axis->scaleRange(1);
        //axis->setPadding(2);
      }
    }

    //==================================================================
    // set dark background gradient:
    //==================================================================
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->BeHPPlot->setBackground(QBrush(gradient));
    //==================================================================
    //
    //==================================================================

    BeHistAddDetPlot (subRect  , 1 , "MLB-Backend Emulator - RPC Histogram");
    //BeHistAddDetPlot (subRect2  , 2 , "MLB-Backend RPC Hit Profile");
}


void BackendHitPlot::BeHistAddDetPlot (QCPAxisRect *subRect , unsigned int StripNum , QString stripNum){

    QFont legendFont = font();
    legendFont.setPointSize(11);
    ui->BeHPPlot->setFont(legendFont);
    subRect->setupFullAxesBox(true);

    //subRect->setBackgroundScaled(10);
    //subRect->setMaximumSize(400,1600);
    subRect->setMinimumSize(40,170);

    //-----------------------------------------------------------------
    // prepare x axis with channel labels:
    // https://www.qcustomplot.com/documentation/classQCPAxisTicker.html
    //-----------------------------------------------------------------
    //Technique 1
    /*
    QVector<QString> labels(97);
    for (int j=0 ; j<=97;j++){

        tickN2[j] = j ;
        labels[j] = QString("%1").arg(j+1);
    }

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(tickN2, labels);
    ui->BeHPPlot->xAxis->setTicker(textTicker);
    */

    //Technique 2
    // https://www.qcustomplot.com/documentation/classQCPAxisTickerFixed.html

    QSharedPointer<QCPAxisTickerFixed> fixedTicker(new QCPAxisTickerFixed);
    fixedTicker->setTickStep(1.0);
    fixedTicker->setScaleStrategy(QCPAxisTickerFixed::ssMultiples );
    //fixedTicker->setTickOrigin(0);
    fixedTicker->setTickCount(100);
    subRect->axis(QCPAxis::atBottom)->setTicker(fixedTicker);

    //-----------------------------------------------------------------

    subRect->axis(QCPAxis::atBottom)->setTickLabelRotation(90);
    subRect->axis(QCPAxis::atBottom)->setLabel(" RPC Strip Number "); // RPC Channel xx
    subRect->axis(QCPAxis::atBottom)->setSubTicks(false);
    subRect->axis(QCPAxis::atBottom)->setTickLength(0, 4);
    subRect->axis(QCPAxis::atBottom)->setRange(0, 97);
    subRect->axis(QCPAxis::atBottom)->setBasePen(QPen(Qt::white));
    subRect->axis(QCPAxis::atBottom)->setTickPen(QPen(Qt::white));
    subRect->axis(QCPAxis::atBottom)->setSubTickPen(QPen(Qt::white));
    subRect->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    subRect->axis(QCPAxis::atBottom)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRect->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::white);
    subRect->axis(QCPAxis::atBottom)->setLabelColor(Qt::white);
    subRect->axis(QCPAxis::atBottom)->selectableParts().setFlag(QCPAxis::spAxis);
    subRect->axis(QCPAxis::atBottom)->setPadding(5); // a bit more space to the left border



     subRect->axis(QCPAxis::atTop)->setRange(0, 97);
     subRect->axis(QCPAxis::atTop)->setTickLength(0, 4);
     subRect->axis(QCPAxis::atTop)->setLabel(stripNum); // RPC Channel xx
     subRect->axis(QCPAxis::atTop)->setSubTicks(true);
     subRect->axis(QCPAxis::atTop)->setBasePen(QPen(Qt::white));
     subRect->axis(QCPAxis::atTop)->setTickPen(QPen(Qt::white));
     subRect->axis(QCPAxis::atTop)->setSubTickPen(QPen(Qt::white));
     subRect->axis(QCPAxis::atTop)->grid()->setVisible(true);
     subRect->axis(QCPAxis::atTop)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
     subRect->axis(QCPAxis::atTop)->setTickLabelColor(Qt::white);
     subRect->axis(QCPAxis::atTop)->setLabelColor(Qt::white);
     subRect->axis(QCPAxis::atTop)->selectableParts().setFlag(QCPAxis::spAxis);
     subRect->axis(QCPAxis::atTop)->setPadding(5); // a bit more space to the left border

     // prepare y axis:
     subRect->axis(QCPAxis::atRight)->rescale(true);
     subRect->axis(QCPAxis::atLeft)->setRange(0, 200);
     //subRect->axis(QCPAxis::atLeft)->setRangeUpper (20);
     //subRect->axis(QCPAxis::atLeft)->setPadding(6); // a bit more space to the left border
     subRect->axis(QCPAxis::atLeft)->setLabel(" Hit Rate (Hz) "); // Vertical Text
     subRect->axis(QCPAxis::atLeft)->setBasePen(QPen(Qt::white));
     subRect->axis(QCPAxis::atLeft)->setTickPen(QPen(Qt::white));
     subRect->axis(QCPAxis::atLeft)->setSubTickPen(QPen(Qt::white));
     subRect->axis(QCPAxis::atLeft)->grid()->setSubGridVisible(true);
     subRect->axis(QCPAxis::atLeft)->setTickLabelColor(Qt::white);
     subRect->axis(QCPAxis::atLeft)->setLabelColor(Qt::white);
     subRect->axis(QCPAxis::atLeft)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
     subRect->axis(QCPAxis::atLeft)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
     subRect->axis(QCPAxis::atLeft)->selectableParts().setFlag(QCPAxis::spAxis);

     subRect->axis(QCPAxis::atRight)->rescale(true);
     subRect->axis(QCPAxis::atRight)->setRange(0, 200);
     //subRect->axis(QCPAxis::atRight)->setRangeUpper (20);
     //subRect->axis(QCPAxis::atRight)->setPadding(6); // a bit more space to the left border
     subRect->axis(QCPAxis::atRight)->setBasePen(QPen(Qt::white));
     subRect->axis(QCPAxis::atRight)->setTickPen(QPen(Qt::white));
     subRect->axis(QCPAxis::atRight)->setSubTickPen(QPen(Qt::white));
     subRect->axis(QCPAxis::atRight)->grid()->setSubGridVisible(true);
     subRect->axis(QCPAxis::atRight)->setTickLabelColor(Qt::white);
     subRect->axis(QCPAxis::atRight)->setLabelColor(Qt::white);
     subRect->axis(QCPAxis::atRight)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
     subRect->axis(QCPAxis::atRight)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
     subRect->axis(QCPAxis::atRight)->selectableParts().setFlag(QCPAxis::spAxis);

     //===================================================================
     subRect->setupFullAxesBox(true);
     //===================================================================
     stripN  = new QCPBars (subRect->axis(QCPAxis::atBottom ),
                          subRect->axis(QCPAxis::atLeft));

     //===================================================================
     stripN->setAntialiased(true); // gives more crisp, pixel aligned bar borders
     stripN->setStackingGap(1);
     stripN->setPen(QPen(QColor(0, 168, 140).lighter(130)));
     stripN->setBrush(QColor(0, 168, 140));
     //===================================================================

     for (unsigned int j=0 ; j<=96;j++){
         tickN2[j] = j ;
     }

}

//==========================================================================
//          Function :
//==========================================================================

void BackendHitPlot::BeHistPlotter(unsigned int y0_StripData[200]){


    //QVector<double> ticks (200);
    //QVector <double> y1_StripValue (200);

    max_value = 0 ;

    for (unsigned int j=0 ; j<=96;j++){

            //ticks[j] = j ;
            y1_StripValue[j] = y0_StripData[j];
            /*
            if (y1_StripValue[j]>= max_value){ // Find Max Y value for right-Axis scaling
                max_value = y1_StripValue[j];
            }*/
    }

    //subRect->axis(QCPAxis::atLeft)->setRange(0, max_value);
    //subRect->axis(QCPAxis::atRight)->setRange(0, max_value);

    //ui->BeHPPlot->rescaleAxes();
    //============================================
    stripN->setData( tickN2 , y1_StripValue );
    //============================================
    ui->BeHPPlot->replot();

}


//==========================================================================
//          Function :
//==========================================================================

void BackendHitPlot::on_PB_3_clicked()
{

    //QVector<double> ticks (200);
    //QVector <double> y1_StripValue (200);

    max_value = 0 ;

    for (unsigned int j=0 ; j<=96;j++){

        //ticks[j] = j ;
        //y1_StripValue[j] = y0_StripData[j];

            if (y1_StripValue[j]>= max_value){ // Find Max Y value for right-Axis scaling
                max_value = y1_StripValue[j];
            }
    }

    subRect->axis(QCPAxis::atLeft)->setRange(0, max_value);
    subRect->axis(QCPAxis::atRight)->setRange(0, max_value);

    //ui->BeHPPlot->rescaleAxes();
    //============================================
    stripN->setData( tickN2 , y1_StripValue );
    //============================================
    ui->BeHPPlot->replot();
}

//==========================================================================
//          Function :
//==========================================================================
void BackendHitPlot::on_PB_4_clicked()
{

    //QVector<double> ticks (200);
    //QVector <double> y1_StripValue (200);

    max_value = 0 ;
    max_width = 0 ;
    minVal=false ;

    for (unsigned int j=0 ; j<=96;j++){

        //ticks[j] = j ;
        //y1_StripValue[j] = y0_StripData[j];

        if (y1_StripValue[j]>= max_value){ // Find Max Y value for right-Axis scaling
            max_value = y1_StripValue[j];
        }

        if ((y1_StripValue[j] != 0)&& (minVal==false)){ // Find Max Y value for right-Axis scaling
            min_width = j;

            minVal=true ;
        }

        if ((y1_StripValue[j] != 0)&& (minVal==true)){ // Find Max Y value for right-Axis scaling
            max_width = j;
        }


    }

    subRect->axis(QCPAxis::atLeft)->setRange(0, max_value);
    subRect->axis(QCPAxis::atRight)->setRange(0, max_value);

    subRect->axis(QCPAxis::atBottom)->setRange(min_width-5, max_width+5);
    subRect->axis(QCPAxis::atTop)->setRange(min_width-5, max_width+5);

    //ui->BeHPPlot->rescaleAxes();
    //============================================
    stripN->setData( tickN2 , y1_StripValue );
    //============================================
    ui->BeHPPlot->replot();

}



//==========================================================================
//          Function :
//==========================================================================

void BackendHitPlot::BackendHitPlot_scaleTop()
{

    //QVector<double> ticks (200);
    //QVector <double> y1_StripValue (200);

    max_value = 0 ;

    for (unsigned int j=0 ; j<=96;j++){

        //ticks[j] = j ;
        //y1_StripValue[j] = y0_StripData[j];

        if (y1_StripValue[j]>= max_value){ // Find Max Y value for right-Axis scaling
            max_value = y1_StripValue[j];
        }
    }

    subRect->axis(QCPAxis::atLeft)->setRange(0, max_value);
    subRect->axis(QCPAxis::atRight)->setRange(0, max_value);

    //ui->BeHPPlot->rescaleAxes();
    //============================================
    stripN->setData( tickN2 , y1_StripValue );
    //============================================
    ui->BeHPPlot->replot();
}

//==========================================================================
//          Function :
//==========================================================================
void BackendHitPlot::BackendHitPlot_scaleWindow()
{

    //QVector<double> ticks (200);
    //QVector <double> y1_StripValue (200);

    max_value = 0 ;
    max_width = 0 ;
    minVal=false ;

    for (unsigned int j=0 ; j<=96;j++){

        //ticks[j] = j ;
        //y1_StripValue[j] = y0_StripData[j];

        if (y1_StripValue[j]>= max_value){ // Find Max Y value for right-Axis scaling
            max_value = y1_StripValue[j];
        }

        if ((y1_StripValue[j] != 0)&& (minVal==false)){ // Find Max Y value for right-Axis scaling
            min_width = j;

            minVal=true ;
        }

        if ((y1_StripValue[j] != 0)&& (minVal==true)){ // Find Max Y value for right-Axis scaling
            max_width = j;
        }


    }

    subRect->axis(QCPAxis::atLeft)->setRange(0, max_value);
    subRect->axis(QCPAxis::atRight)->setRange(0, max_value);

    subRect->axis(QCPAxis::atBottom)->setRange(min_width-5, max_width+5);
    subRect->axis(QCPAxis::atTop)->setRange(min_width-5, max_width+5);

    //ui->BeHPPlot->rescaleAxes();
    //============================================
    stripN->setData( tickN2 , y1_StripValue );
    //============================================
    ui->BeHPPlot->replot();

}
