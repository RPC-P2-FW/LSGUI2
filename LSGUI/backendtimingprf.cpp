#include "backendtimingprf.h"
#include "ui_backendtimingprf.h"

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



QVector <double> y1_TimingPrfData (4000);
QVector<double> ticks (4000);

BackendTimingPrf::BackendTimingPrf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BackendTimingPrf)
{
    ui->setupUi(this);
}

BackendTimingPrf::~BackendTimingPrf()
{
    delete ui;
}


void BackendTimingPrf::BeTimingPrfSetupPlot(void){

    ui->BeTimPrfPlot->plotLayout()->clear();

    QCPLayoutGrid *mainLayout = new QCPLayoutGrid;
    ui->BeTimPrfPlot->plotLayout()->addElement( 0 , 0 , mainLayout);

    subRect= new QCPAxisRect(ui->BeTimPrfPlot, true);
    //subRect2= new QCPAxisRect(ui->BeTimPrfPlot, true);
    mainLayout->addElement( 0 , 0, subRect  );
    //mainLayout->addElement( 0 , 0, subRect2  );
    //==================================================================
    ui->BeTimPrfPlot->axisRect()->setupFullAxesBox(true);
    ui->BeTimPrfPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                                      QCP::iSelectAxes | QCP::iSelectLegend |QCP::iSelectPlottables);
    //==================================================================


    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->BeTimPrfPlot);
    subRect->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    foreach (QCPAxisRect *rect, ui->BeTimPrfPlot->axisRects())
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
    ui->BeTimPrfPlot->setBackground(QBrush(gradient));
    //==================================================================
    //
    //==================================================================

    BeTimingPrfAddDetPlot (subRect  , 1 , "RPC Timing Profile - Hit rate VS Bunch Crossing");
    //BeHistAddDetPlot (subRect2  , 2 , "MLB-Backend RPC Hit Profile");
}


void BackendTimingPrf::BeTimingPrfAddDetPlot (QCPAxisRect *subRect , unsigned int StripNum , QString stripNum){

    QFont legendFont = font();
    legendFont.setPointSize(11);
    ui->BeTimPrfPlot->setFont(legendFont);
    subRect->setupFullAxesBox(true);

    //subRect->setBackgroundScaled(10);
    //subRect->setMaximumSize(400,1600);
    subRect->setMinimumSize(40,170);

    //-----------------------------------------------------------------
    // prepare x axis with channel labels:
    // https://www.qcustomplot.com/documentation/classQCPAxisTicker.html
    //-----------------------------------------------------------------
    // Technique 1
    /*
    QVector<QString> labels(4000);

    for (int j=0 ; j<=3564;j++){

        ticks[j] = j ;
        labels[j] = QString("%1").arg(j+1);
    }

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->BeTimPrfPlot->xAxis->setTicker(textTicker);
    */
    //-----------------------------------------------------------------

    //-----------------------------------------------------------------

    //-----------------------------------------------------------------
    //Technique 2
    // https://www.qcustomplot.com/documentation/classQCPAxisTickerFixed.html

   QSharedPointer<QCPAxisTickerFixed> fixedTicker(new QCPAxisTickerFixed);
   fixedTicker->setTickStep(5.0);
   fixedTicker->setScaleStrategy(QCPAxisTickerFixed::ssNone);
   subRect->axis(QCPAxis::atBottom)->setTicker(fixedTicker);


   //------------------------------------------------------------------


    subRect->axis(QCPAxis::atBottom)->setTickLabelRotation(90);
    subRect->axis(QCPAxis::atBottom)->setLabel(" Bunch Crossing "); // RPC Channel xx
    subRect->axis(QCPAxis::atBottom)->setSubTicks(true);
    subRect->axis(QCPAxis::atBottom)->setTickLength(0, 5);
    subRect->axis(QCPAxis::atBottom)->setRange(0, 3564);
    subRect->axis(QCPAxis::atBottom)->setBasePen(QPen(Qt::white));
    subRect->axis(QCPAxis::atBottom)->setTickPen(QPen(Qt::white));
    subRect->axis(QCPAxis::atBottom)->setSubTickPen(QPen(Qt::white));
    subRect->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    subRect->axis(QCPAxis::atBottom)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRect->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::white);
    subRect->axis(QCPAxis::atBottom)->setLabelColor(Qt::white);
    subRect->axis(QCPAxis::atBottom)->selectableParts().setFlag(QCPAxis::spAxis);
    subRect->axis(QCPAxis::atBottom)->setPadding(5); // a bit more space to the left border



     subRect->axis(QCPAxis::atTop)->setRange(0, 3564);
     subRect->axis(QCPAxis::atTop)->setTickLength(0, 5);
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


     for (unsigned int j=0 ; j<=3564;j++){
         ticks[j] = j ;
     }


}


void BackendTimingPrf::BeTimingPrfPlotter(unsigned int y0_TimingPrfData[4000]){


    //QVector<double> ticks (4000);
    //QVector <double> y1_TimingPrfData (4000);

    max_value = 0 ;

    for (unsigned int j=0 ; j<=3564;j++){

            //ticks[j] = j ;
            y1_TimingPrfData[j] = y0_TimingPrfData[j];

            /*
            if (y1_TimingPrfData[j]>= max_value){ // Find Max Y value for right-Axis scaling
                max_value = y1_TimingPrfData[j];
            }*/
    }

    //subRect->axis(QCPAxis::atLeft)->setRange(0, max_value);
    //subRect->axis(QCPAxis::atRight)->setRange(0, max_value);

    //============================================
    stripN->setData( ticks , y1_TimingPrfData );
    //============================================
    ui->BeTimPrfPlot->replot();

}


//==========================================================================
//          Function :
//==========================================================================

void BackendTimingPrf::on_PB1_clicked()
{
    max_value = 0 ;

    for (unsigned int j=0 ; j<=3564;j++){

        //ticks[j] = j ;
        //y1_TimingPrfData[j] = y0_TimingPrfData[j];


            if (y1_TimingPrfData[j]>= max_value){ // Find Max Y value for right-Axis scaling
                max_value = y1_TimingPrfData[j];
            }
    }

    subRect->axis(QCPAxis::atLeft)->setRange(0, max_value);
    subRect->axis(QCPAxis::atRight)->setRange(0, max_value);

    //============================================
    stripN->setData( ticks , y1_TimingPrfData );
    //============================================
    ui->BeTimPrfPlot->replot();

}

//==========================================================================
//          Function :
//==========================================================================
void BackendTimingPrf::on_PB_2_clicked()
{

    max_value = 0 ;
    max_width = 0 ;
    minVal=false ;

    for (unsigned int j=0 ; j<=3564;j++){

        //ticks[j] = j ;
        //y1_TimingPrfData[j] = y0_TimingPrfData[j];


        if (y1_TimingPrfData[j]>= max_value){ // Find Max Y value for right-Axis scaling
            max_value = y1_TimingPrfData[j];
        }

        if ((y1_TimingPrfData[j] != 0)&& (minVal==false)){ // Find Max Y value for right-Axis scaling
            min_width = j;

            minVal=true ;
        }

        if ((y1_TimingPrfData[j] != 0)&& (minVal==true)){ // Find Max Y value for right-Axis scaling
            max_width = j;
        }


    }

    subRect->axis(QCPAxis::atLeft)->setRange(0, max_value);
    subRect->axis(QCPAxis::atRight)->setRange(0, max_value);

    subRect->axis(QCPAxis::atBottom)->setRange(min_width-5, max_width+5);
    subRect->axis(QCPAxis::atTop)->setRange(min_width-5, max_width+5);

    //============================================
    stripN->setData( ticks , y1_TimingPrfData );
    //============================================
    ui->BeTimPrfPlot->replot();
}





void BackendTimingPrf:: BeTimingPrf_scaleTop(){

    max_value = 0 ;

    for (unsigned int j=0 ; j<=3564;j++){

        //ticks[j] = j ;
        //y1_TimingPrfData[j] = y0_TimingPrfData[j];


        if (y1_TimingPrfData[j]>= max_value){ // Find Max Y value for right-Axis scaling
            max_value = y1_TimingPrfData[j];
        }
    }

    subRect->axis(QCPAxis::atLeft)->setRange(0, max_value);
    subRect->axis(QCPAxis::atRight)->setRange(0, max_value);

    //============================================
    stripN->setData( ticks , y1_TimingPrfData );
    //============================================
    ui->BeTimPrfPlot->replot();

}
void BackendTimingPrf:: BeTimingPrf_scaleWindow(){

    max_value = 0 ;
    max_width = 0 ;
    minVal=false ;

    for (unsigned int j=0 ; j<=3564;j++){

        //ticks[j] = j ;
        //y1_TimingPrfData[j] = y0_TimingPrfData[j];


        if (y1_TimingPrfData[j]>= max_value){ // Find Max Y value for right-Axis scaling
            max_value = y1_TimingPrfData[j];
        }

        if ((y1_TimingPrfData[j] != 0)&& (minVal==false)){ // Find Max Y value for right-Axis scaling
            min_width = j;

            minVal=true ;
        }

        if ((y1_TimingPrfData[j] != 0)&& (minVal==true)){ // Find Max Y value for right-Axis scaling
            max_width = j;
        }


    }

    subRect->axis(QCPAxis::atLeft)->setRange(0, max_value);
    subRect->axis(QCPAxis::atRight)->setRange(0, max_value);

    subRect->axis(QCPAxis::atBottom)->setRange(min_width-5, max_width+5);
    subRect->axis(QCPAxis::atTop)->setRange(min_width-5, max_width+5);

    //============================================
    stripN->setData( ticks , y1_TimingPrfData );
    //============================================
    ui->BeTimPrfPlot->replot();
}

