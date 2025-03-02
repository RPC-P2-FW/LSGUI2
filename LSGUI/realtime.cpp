#include "realtime.h"
#include "ui_realtime.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>

realTime::realTime(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::realTime)
{
    ui->setupUi(this);
}

realTime::~realTime()
{
    delete ui;
}



void realTime::setupPlot_CB(void){

    QVector <double> y1_FullWinChannel (100);
    QVector <double> y1_AdjWinChannel (100);

    QVector <double> x1_stripFulW (100);
    QVector <double> x1_stripAdjW (100);



    // configure axis rect:
    ui->plot_CB->plotLayout()->clear(); // clear default axis rect so we can start from scratch
    QCPAxisRect *wideAxisRect = new QCPAxisRect(ui->plot_CB);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers




    QCPLayoutGrid *subLayout = new QCPLayoutGrid;

    ui->plot_CB->plotLayout()->addElement(0, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)

    // prepare axis rects that will be placed in the sublayout:
    QCPAxisRect *subRectTop = new QCPAxisRect(ui->plot_CB, false); // false means to not setup default axes
    QCPAxisRect *subRectBotton = new QCPAxisRect(ui->plot_CB, false);
    QCPAxisRect *subRectTiming = new QCPAxisRect(ui->plot_CB, false);
    QCPAxisRect *subRectRowData = new QCPAxisRect(ui->plot_CB, false);

    subLayout->addElement(0, 0, subRectTop);
    subLayout->addElement(1, 0, subRectBotton);
    subLayout->addElement(2, 0, subRectTiming);
    //subLayout->addElement(3, 0, subRectRowData);

    //subRectTop->setMaximumSize(100, 100); // make bottom right axis rect size fixed 100x100
    //subRectTop->setMinimumSize(100, 100); // make bottom right axis rect size fixed 100x100

    //subRectBotton->setMaximumSize(100, 100); // make bottom right axis rect size fixed 100x100
    //subRectBotton->setMinimumSize(100, 100); // make bottom right axis rect size fixed 100x100



    // setup axes in sub layout axis rects:
    subRectTop->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    //subRectTop->axis(QCPAxis::atBottom)->ticker()->setTickCount(2);
    subRectTop->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRectBotton->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    //subRectBotton->axis(QCPAxis::atBottom)->ticker()->setTickCount(2);
    subRectBotton->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRectTiming->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    //subRectBotton->axis(QCPAxis::atBottom)->ticker()->setTickCount(2);
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    //subRectRowData->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    //subRectRowData->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    // synchronize the left and right margins of the top and bottom axis rects:
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot_CB);
    subRectTop->setMarginGroup(QCP::msBottom |QCP::msTop , marginGroup);
    subRectBotton->setMarginGroup(QCP::msBottom, marginGroup);
    subRectTiming->setMarginGroup(QCP::msBottom, marginGroup);
    //subRectRowData->setMarginGroup(QCP::msBottom, marginGroup);

    wideAxisRect->setMarginGroup(QCP::msTop | QCP::msBottom | QCP::msRight | QCP::msLeft, marginGroup);


    // move newly created axes on "axes" layer and grids on "grid" layer:

    foreach (QCPAxisRect *rect, ui->plot_CB->axisRects())
    {
      foreach (QCPAxis *axis, rect->axes())
      {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
      }
    }



    //==================================================================
    for (int j=0;j<95;j++){
        //qDebug() << "3)- x0_stripFulW[j] " << x0CB_stripAdjW[j] ;

        y1_FullWinChannel[j] = y0CB_FullWinChannel[j];
        y1_AdjWinChannel[j] = y0CB_AdjWinChannel[j];
        x1_stripFulW[j] = x0CB_stripFulW[j] ;
        x1_stripAdjW[j] = x0CB_stripAdjW[j] ;
    }

    //==================================================================
    QCPBars *AdjWinHst = new QCPBars(subRectTop->axis(QCPAxis::atBottom), subRectTop->axis(QCPAxis::atLeft));

    //QCPBars *AdjWinHst = new QCPBars(ui->plot_CB->xAxis, ui->plot_CB->yAxis);


    AdjWinHst->setAntialiased(false); // gives more crisp, pixel aligned bar borders
    AdjWinHst->setStackingGap(1);
    AdjWinHst->setName("MultiChannel Histogram - Adjustable Window ");
    AdjWinHst->setPen(QPen(QColor(0, 168, 140).lighter(130)));
    AdjWinHst->setBrush(QColor(0, 168, 140));
    //==================================================================


    QCPBars *FulWinHst = new QCPBars(subRectBotton->axis(QCPAxis::atBottom), subRectBotton->axis(QCPAxis::atLeft));

    FulWinHst->setAntialiased(true); // gives more crisp, pixel aligned bar borders
    FulWinHst->setStackingGap(1);
    FulWinHst->setName("MultiChannel Histogram - Full Window ");
    FulWinHst->setPen(QPen(QColor("#705BE8").lighter(130)));
    FulWinHst->setBrush(QColor("#705BE8"));
    //==================================================================








    // prepare x axis with channel labels:

    QVector<double> ticks (100);
    QVector<QString> labels(100);
    for (int j=0 ; j<95;j++){

        ticks[j] = j+1 ;
        labels[j] = QString("%1").arg(j+1);
    }
    //==================================================================

    // set dark background gradient:

    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->plot_CB->setBackground(QBrush(gradient));
    //==================================================================

    AdjWinHst->setData(ticks,y1_AdjWinChannel);

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->plot_CB->xAxis->setTicker(textTicker);
    subRectTop->axis(QCPAxis::atBottom)->setTickLabelRotation(60);
    subRectTop->axis(QCPAxis::atBottom)->setLabel("RPC Channels 1-96");
    subRectTop->axis(QCPAxis::atBottom)->setSubTicks(false);
    subRectTop->axis(QCPAxis::atBottom)->setTickLength(0, 4);
    subRectTop->axis(QCPAxis::atBottom)->setRange(0, 96);
    subRectTop->axis(QCPAxis::atBottom)->setBasePen(QPen(Qt::white));
    subRectTop->axis(QCPAxis::atBottom)->setTickPen(QPen(Qt::white));
    subRectTop->axis(QCPAxis::atBottom)->setSubTickPen(QPen(Qt::white));
    subRectTop->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    subRectTop->axis(QCPAxis::atBottom)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTop->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::white);
    subRectTop->axis(QCPAxis::atBottom)->setLabelColor(Qt::white);

    subRectTop->axis(QCPAxis::atTop)->setRange(0, 96);
    subRectTop->axis(QCPAxis::atTop)->setTickLength(0, 4);
    subRectTop->axis(QCPAxis::atTop)->setSubTicks(true);
    subRectTop->axis(QCPAxis::atTop)->setBasePen(QPen(Qt::white));
    subRectTop->axis(QCPAxis::atTop)->setTickPen(QPen(Qt::white));
    subRectTop->axis(QCPAxis::atTop)->setSubTickPen(QPen(Qt::white));
    subRectTop->axis(QCPAxis::atTop)->grid()->setVisible(true);
    subRectTop->axis(QCPAxis::atTop)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTop->axis(QCPAxis::atTop)->setTickLabelColor(Qt::white);
    subRectTop->axis(QCPAxis::atTop)->setLabelColor(Qt::white);

    // prepare y axis:
    subRectTop->axis(QCPAxis::atLeft)->setRange(0, 96);
    subRectTop->axis(QCPAxis::atLeft)->setPadding(1); // a bit more space to the left border
    subRectTop->axis(QCPAxis::atLeft)->setLabel(" Hit Rate (kHz) ");
    subRectTop->axis(QCPAxis::atLeft)->setBasePen(QPen(Qt::white));
    subRectTop->axis(QCPAxis::atLeft)->setTickPen(QPen(Qt::white));
    subRectTop->axis(QCPAxis::atLeft)->setSubTickPen(QPen(Qt::white));
    subRectTop->axis(QCPAxis::atLeft)->grid()->setSubGridVisible(true);
    subRectTop->axis(QCPAxis::atLeft)->setTickLabelColor(Qt::white);
    subRectTop->axis(QCPAxis::atLeft)->setLabelColor(Qt::white);
    subRectTop->axis(QCPAxis::atLeft)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTop->axis(QCPAxis::atLeft)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));


    subRectTop->axis(QCPAxis::atRight)->setRange(0, 96);
    subRectTop->axis(QCPAxis::atRight)->setPadding(1); // a bit more space to the left border
    subRectTop->axis(QCPAxis::atRight)->setBasePen(QPen(Qt::white));
    subRectTop->axis(QCPAxis::atRight)->setTickPen(QPen(Qt::white));
    subRectTop->axis(QCPAxis::atRight)->setSubTickPen(QPen(Qt::white));
    subRectTop->axis(QCPAxis::atRight)->grid()->setSubGridVisible(true);
    subRectTop->axis(QCPAxis::atRight)->setTickLabelColor(Qt::white);
    //subRectTop->axis(QCPAxis::atRight)->setLabelColor(Qt::white);
    subRectTop->axis(QCPAxis::atRight)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTop->axis(QCPAxis::atRight)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    //==================================================================


    FulWinHst->setData(ticks,y1_FullWinChannel);

    QSharedPointer<QCPAxisTickerText> textTicker2(new QCPAxisTickerText);
    textTicker2->addTicks(ticks, labels);
    subRectBotton->axis(QCPAxis::atBottom)->setTicker(textTicker2);
    subRectBotton->axis(QCPAxis::atBottom)->setTickLabelRotation(60);
    subRectBotton->axis(QCPAxis::atBottom)->setLabel("RPC Channels 1-96");
    subRectBotton->axis(QCPAxis::atBottom)->setSubTicks(false);
    subRectBotton->axis(QCPAxis::atBottom)->setTickLength(0, 4);
    subRectBotton->axis(QCPAxis::atBottom)->setRange(0, 96);
    subRectBotton->axis(QCPAxis::atBottom)->setBasePen(QPen(Qt::white));
    subRectBotton->axis(QCPAxis::atBottom)->setTickPen(QPen(Qt::white));
    subRectBotton->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    subRectBotton->axis(QCPAxis::atBottom)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectBotton->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::white);
    subRectBotton->axis(QCPAxis::atBottom)->setLabelColor(Qt::white);


    subRectBotton->axis(QCPAxis::atTop)->setRange(0, 96);
    subRectBotton->axis(QCPAxis::atTop)->setTickLength(0, 4);
    subRectBotton->axis(QCPAxis::atTop)->setSubTicks(true);
    subRectBotton->axis(QCPAxis::atTop)->setBasePen(QPen(Qt::white));
    subRectBotton->axis(QCPAxis::atTop)->setTickPen(QPen(Qt::white));
    subRectBotton->axis(QCPAxis::atTop)->setSubTickPen(QPen(Qt::white));
    subRectBotton->axis(QCPAxis::atTop)->grid()->setVisible(true);
    subRectBotton->axis(QCPAxis::atTop)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectBotton->axis(QCPAxis::atTop)->setTickLabelColor(Qt::white);
    subRectBotton->axis(QCPAxis::atTop)->setLabelColor(Qt::white);


    //subRectBotton->axis(QCPAxis::atTop)->setLabel("MultiChannel Histogram - Adjustable Window ");

    // prepare y axis:
    subRectBotton->axis(QCPAxis::atLeft)->setRange(0, 96);
    subRectBotton->axis(QCPAxis::atLeft)->setPadding(1); // a bit more space to the left border
    subRectBotton->axis(QCPAxis::atLeft)->setLabel(" Hit Rate (kHz) ");
    subRectBotton->axis(QCPAxis::atLeft)->setBasePen(QPen(Qt::white));
    subRectBotton->axis(QCPAxis::atLeft)->setTickPen(QPen(Qt::white));
    subRectBotton->axis(QCPAxis::atLeft)->setSubTickPen(QPen(Qt::white));
    subRectBotton->axis(QCPAxis::atLeft)->grid()->setSubGridVisible(true);
    subRectBotton->axis(QCPAxis::atLeft)->setTickLabelColor(Qt::white);
    subRectBotton->axis(QCPAxis::atLeft)->setLabelColor(Qt::white);
    subRectBotton->axis(QCPAxis::atLeft)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectBotton->axis(QCPAxis::atLeft)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    subRectBotton->axis(QCPAxis::atRight)->setRange(0, 96);
    subRectBotton->axis(QCPAxis::atRight)->setPadding(1); // a bit more space to the left border
    subRectBotton->axis(QCPAxis::atRight)->setBasePen(QPen(Qt::white));
    subRectBotton->axis(QCPAxis::atRight)->setTickPen(QPen(Qt::white));
    subRectBotton->axis(QCPAxis::atRight)->setSubTickPen(QPen(Qt::white));
    subRectBotton->axis(QCPAxis::atRight)->grid()->setSubGridVisible(true);
    subRectBotton->axis(QCPAxis::atRight)->setTickLabelColor(Qt::white);
    //subRectBotton->axis(QCPAxis::atRight)->setLabelColor(Qt::white);
    subRectBotton->axis(QCPAxis::atRight)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectBotton->axis(QCPAxis::atRight)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));



    // setup legend:


    /*
    ui->plot_CB->legend->setVisible(true);
    ui->plot_CB->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->plot_CB->legend->setBrush(QColor(255, 255, 255, 100));
    ui->plot_CB->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->plot_CB->legend->setFont(legendFont);
    ui->plot_CB->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    */

    //==================================================================
    QVector <double> y1_timingHist (130);
    QVector <double> x1_BxNum (130);
    //==================================================================
    QCPBars *TimingHist = new QCPBars(subRectTiming->axis(QCPAxis::atBottom), subRectTiming->axis(QCPAxis::atLeft));

    TimingHist->setAntialiased(true); // gives more crisp, pixel aligned bar borders
    TimingHist->setStackingGap(1);
    TimingHist->setName("Timing Histogram ");
    TimingHist->setPen(QPen(QColor("#FF51FF"),2));
    TimingHist->setBrush(QColor("#FF51FF")); // 6050F8 BLUE
                                            // 8070B8 Violet
                                            // FFA100 Yellow
                                            // FF51FF  PINK
                                            // AAAAff Light Blue

    //==================================================================

    for (int j=0;j<129;j++){
        //qDebug() << "3)- x0_stripFulW[j] " << x0CB_stripAdjW[j] ;

        y1_timingHist[j] = y0CB_timingHist[j];
        x1_BxNum[j] = x0CB_BxNum[j] ;
    }


    // prepare x axis with channel labels:

    QVector<double> timTicks (130);
    QVector<QString> timLabels(130);
    for (int j=0 ; j<129;j++){

        timTicks[j] = j+1 ;
        timLabels[j] = QString("%1").arg(j+1);
    }
    //==================================================================

    TimingHist->setData(timTicks,y1_timingHist);

    QSharedPointer<QCPAxisTickerText> textTicker3(new QCPAxisTickerText);
    textTicker3->addTicks(timTicks, timLabels);
    subRectTiming->axis(QCPAxis::atBottom)->setTicker(textTicker3);
    subRectTiming->axis(QCPAxis::atBottom)->setTickLabelRotation(90);
    subRectTiming->axis(QCPAxis::atBottom)->setLabel("Bunch Cross (#)");
    subRectTiming->axis(QCPAxis::atBottom)->setSubTicks(false);
    subRectTiming->axis(QCPAxis::atBottom)->setTickLength(0, 4);
    subRectTiming->axis(QCPAxis::atBottom)->setRange(0, 128);
    subRectTiming->axis(QCPAxis::atBottom)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atBottom)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTiming->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atBottom)->setLabelColor(Qt::white);


    subRectTiming->axis(QCPAxis::atTop)->setRange(0, 128);
    subRectTiming->axis(QCPAxis::atTop)->setTickLength(0, 4);
    subRectTiming->axis(QCPAxis::atTop)->setSubTicks(true);
    subRectTiming->axis(QCPAxis::atTop)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->grid()->setVisible(true);
    subRectTiming->axis(QCPAxis::atTop)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTiming->axis(QCPAxis::atTop)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atTop)->setLabelColor(Qt::white);


    //subRectTiming->axis(QCPAxis::atTop)->setLabel("MultiChannel Histogram - Adjustable Window ");

    // prepare y axis:
    subRectTiming->axis(QCPAxis::atLeft)->setRange(0, 128);
    subRectTiming->axis(QCPAxis::atLeft)->setPadding(1); // a bit more space to the left border
    subRectTiming->axis(QCPAxis::atLeft)->setLabel(" Hit Rate (kHz) ");
    subRectTiming->axis(QCPAxis::atLeft)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setSubGridVisible(true);
    subRectTiming->axis(QCPAxis::atLeft)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atLeft)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    subRectTiming->axis(QCPAxis::atRight)->setRange(0, 128);
    subRectTiming->axis(QCPAxis::atRight)->setPadding(1); // a bit more space to the left border
    subRectTiming->axis(QCPAxis::atRight)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->grid()->setSubGridVisible(true);
    subRectTiming->axis(QCPAxis::atRight)->setTickLabelColor(Qt::white);
    //subRectTiming->axis(QCPAxis::atRight)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atRight)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTiming->axis(QCPAxis::atRight)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));



    //=======================================================================
    //  ROW Data
    //=======================================================================
    /*
    QCPBars *RowData = new QCPBars(subRectRowData->axis(QCPAxis::atBottom), subRectRowData->axis(QCPAxis::atLeft));

    RowData->setAntialiased(true); // gives more crisp, pixel aligned bar borders
    RowData->setStackingGap(1);
    RowData->setName("RPC RAW DATA ");
    RowData->setPen(QPen(QColor("#AAAAff")));
    RowData->setBrush(QColor("#AAAAff"));// 6050F8 BLUE
                                        // 8070B8 Violet
                                        // FFA100 Yellow
                                        // FF51FF  PINK
                                        // AAAAff Light Blue
    //==================================================================

    //==================================================================
    QVector <double> y1_RawData (2066);
    QVector <double> x1_SubBxNum (2066);
    //==================================================================

    //==================================================================

    for (int j=0;j<2065;j++){
        //qDebug() << "3)- x0_stripFulW[j] " << x0CB_stripAdjW[j] ;

        y1_RawData[j] = y0CB_RawData[j];
        x1_SubBxNum[j] = x0CB_SubBxNum[j] ;
    }


    // prepare x axis with channel labels:

    QVector<double> RDataTicks (2100);
    QVector<QString> RDataLabels(2100);
    for (int j=0 ; j<2066;j++){

        RDataTicks[j] = j+1 ;
        RDataLabels[j] = QString("%1").arg(j+1);
    }
    //==================================================================

    RowData->setData( RDataTicks , y1_RawData );

    QSharedPointer<QCPAxisTickerText> textTicker4(new QCPAxisTickerText);
    textTicker4->addTicks(RDataTicks, RDataLabels);
    //subRectRowData->axis(QCPAxis::atBottom)->setTicker(textTicker4);
    subRectRowData->axis(QCPAxis::atBottom)->setTickLabelRotation(0);
    subRectRowData->axis(QCPAxis::atBottom)->setLabel("Sampling Time (1.5 ns)");
    subRectRowData->axis(QCPAxis::atBottom)->setSubTicks(false);
    subRectRowData->axis(QCPAxis::atBottom)->setTickLength(0, 4);
    subRectRowData->axis(QCPAxis::atBottom)->setRange(0, 2065);
    subRectRowData->axis(QCPAxis::atBottom)->setBasePen(QPen(Qt::white));
    subRectRowData->axis(QCPAxis::atBottom)->setTickPen(QPen(Qt::white));
    subRectRowData->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    subRectRowData->axis(QCPAxis::atBottom)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectRowData->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::white);
    subRectRowData->axis(QCPAxis::atBottom)->setLabelColor(Qt::white);


    subRectRowData->axis(QCPAxis::atTop)->setRange(0, 2065);
    subRectRowData->axis(QCPAxis::atTop)->setTickLength(0, 4);
    subRectRowData->axis(QCPAxis::atTop)->setSubTicks(true);
    subRectRowData->axis(QCPAxis::atTop)->setBasePen(QPen(Qt::white));
    subRectRowData->axis(QCPAxis::atTop)->setTickPen(QPen(Qt::white));
    subRectRowData->axis(QCPAxis::atTop)->setSubTickPen(QPen(Qt::white));
    subRectRowData->axis(QCPAxis::atTop)->grid()->setVisible(true);
    subRectRowData->axis(QCPAxis::atTop)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectRowData->axis(QCPAxis::atTop)->setTickLabelColor(Qt::white);
    subRectRowData->axis(QCPAxis::atTop)->setLabelColor(Qt::white);


    //subRectRowData->axis(QCPAxis::atTop)->setLabel("MultiChannel Histogram - Adjustable Window ");

    // prepare y axis:
    subRectRowData->axis(QCPAxis::atLeft)->setRange(0, 2065);
    subRectRowData->axis(QCPAxis::atLeft)->setPadding(1); // a bit more space to the left border
    subRectRowData->axis(QCPAxis::atLeft)->setLabel(" RPC Strip Value ");
    subRectRowData->axis(QCPAxis::atLeft)->setBasePen(QPen(Qt::white));
    subRectRowData->axis(QCPAxis::atLeft)->setTickPen(QPen(Qt::white));
    subRectRowData->axis(QCPAxis::atLeft)->setSubTickPen(QPen(Qt::white));
    subRectRowData->axis(QCPAxis::atLeft)->grid()->setSubGridVisible(true);
    subRectRowData->axis(QCPAxis::atLeft)->setTickLabelColor(Qt::white);
    subRectRowData->axis(QCPAxis::atLeft)->setLabelColor(Qt::white);
    subRectRowData->axis(QCPAxis::atLeft)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectRowData->axis(QCPAxis::atLeft)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    subRectRowData->axis(QCPAxis::atRight)->setRange(0, 2065);
    subRectRowData->axis(QCPAxis::atRight)->setPadding(1); // a bit more space to the left border
    subRectRowData->axis(QCPAxis::atRight)->setBasePen(QPen(Qt::white));
    subRectRowData->axis(QCPAxis::atRight)->setTickPen(QPen(Qt::white));
    subRectRowData->axis(QCPAxis::atRight)->setSubTickPen(QPen(Qt::white));
    subRectRowData->axis(QCPAxis::atRight)->grid()->setSubGridVisible(true);
    subRectRowData->axis(QCPAxis::atRight)->setTickLabelColor(Qt::white);
    //subRectRowData->axis(QCPAxis::atRight)->setLabelColor(Qt::white);
    subRectRowData->axis(QCPAxis::atRight)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectRowData->axis(QCPAxis::atRight)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    */




}



void realTime::setupPlot_LB(unsigned int LBM){

    unsigned int const LB1 = 1 ;
    unsigned int const LB2 = 2 ;
    unsigned int const LB3 = 3 ;
    unsigned int const LB4 = 4 ;
    unsigned int const LB5 = 5 ;
    unsigned int const LB6 = 6 ;
    unsigned int const LB7 = 7 ;
    unsigned int const LB8 = 8 ;
    unsigned int const LB9 = 9 ;


    switch (LBM) {
        case LB1:
            setupPlot_LB1();
        break;

        case LB2:
            setupPlot_LB2();
        break;

        case LB3:
            setupPlot_LB3();
        break;

        case LB4:
            setupPlot_LB4();
        break;

        case LB5:
            setupPlot_LB5();
        break;

        case LB6:
            setupPlot_LB6();
        break;

        case LB7:
            setupPlot_LB7();
        break;

        case LB8:
            setupPlot_LB8();
        break;

        case LB9:
            setupPlot_LB9();
        break;
    }
}

//=================================================
void realTime::setupPlot_LB1(void){


    QVector <double> y1_FullWinChannel (100);
    QVector <double> y1_AdjWinChannel (100);

    QVector <double> x1_stripFulW (100);
    QVector <double> x1_stripAdjW (100);



    for (int j=0;j<95;j++){
        //qDebug() << "3)- x0_stripFulW[j] " << x0LB1_stripAdjW[j] ;

        y1_FullWinChannel[j] = y0LB1_FullWinChannel[j];
        y1_AdjWinChannel[j] = y0LB1_AdjWinChannel[j];
        x1_stripFulW[j] = x0LB1_stripFulW[j] ;
        x1_stripAdjW[j] = x0LB1_stripAdjW[j] ;
    }

    /*
    ui->plot_LB1 ->addGraph();
    // pass data points to graphs:
    ui->plot_LB1->graph(0)->setData(x1_stripFulW, y1_FullWinChannel);
    ui->plot_LB1->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot_LB1->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));// first graph will be filled with translucent blue
    ui->plot_LB1->xAxis->setRange(0,1000);
    ui->plot_LB1->yAxis->setRange(0,1000);
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->plot_LB1->xAxis2->setVisible(true);
    ui->plot_LB1->xAxis2->setTickLabels(false);
    ui->plot_LB1->yAxis2->setVisible(true);
    ui->plot_LB1->yAxis2->setTickLabels(false);

    ui->plot_LB1 ->addGraph();
    //ui->plot_LB1->graph(1)->setData(x,y);
    ui->plot_LB1->graph(1)->setScatterStyle(QCPScatterStyle::ssCross);
    ui->plot_LB1->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    ui->plot_LB1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->plot_LB1->graph(0)->rescaleAxes();

    ui->plot_LB1->legend->setVisible(true);
    ui->plot_LB1->legend->setFont(QFont("Helvetica",9));
    */





    // configure axis rect:
    ui->plot_LB1->plotLayout()->clear(); // clear default axis rect so we can start from scratch
    QCPAxisRect *wideAxisRect = new QCPAxisRect(ui->plot_LB1);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers




    QCPLayoutGrid *subLayout = new QCPLayoutGrid;

    ui->plot_LB1->plotLayout()->addElement(0, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)

    // prepare axis rects that will be placed in the sublayout:
    QCPAxisRect *subRectTop = new QCPAxisRect(ui->plot_LB1, false); // false means to not setup default axes
    QCPAxisRect *subRectBotton = new QCPAxisRect(ui->plot_LB1, false);
    subLayout->addElement(0, 0, subRectTop);
    subLayout->addElement(1, 0, subRectBotton);
    //subRectTop->setMaximumSize(100, 100); // make bottom right axis rect size fixed 100x100
    //subRectTop->setMinimumSize(100, 100); // make bottom right axis rect size fixed 100x100

    //subRectBotton->setMaximumSize(100, 100); // make bottom right axis rect size fixed 100x100
    //subRectBotton->setMinimumSize(100, 100); // make bottom right axis rect size fixed 100x100



    // setup axes in sub layout axis rects:
    subRectTop->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    //subRectTop->axis(QCPAxis::atBottom)->ticker()->setTickCount(2);
    subRectTop->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRectBotton->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    //subRectBotton->axis(QCPAxis::atBottom)->ticker()->setTickCount(2);
    subRectBotton->axis(QCPAxis::atBottom)->grid()->setVisible(true);




    // synchronize the left and right margins of the top and bottom axis rects:
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot_LB1);
    subRectTop->setMarginGroup(QCP::msBottom |QCP::msTop , marginGroup);
    subRectBotton->setMarginGroup(QCP::msBottom, marginGroup);
    wideAxisRect->setMarginGroup(QCP::msTop | QCP::msBottom | QCP::msRight | QCP::msLeft, marginGroup);


    // move newly created axes on "axes" layer and grids on "grid" layer:

    foreach (QCPAxisRect *rect, ui->plot_LB1->axisRects())
    {
      foreach (QCPAxis *axis, rect->axes())
      {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
      }
    }


    for (int j=0;j<95;j++){
        //qDebug() << "3)- x0_stripFulW[j] " << x0LB1_stripAdjW[j] ;

        y1_FullWinChannel[j] = y0LB1_FullWinChannel[j];
        y1_AdjWinChannel[j] = y0LB1_AdjWinChannel[j];
        x1_stripFulW[j] = x0LB1_stripFulW[j] ;
        x1_stripAdjW[j] = x0LB1_stripAdjW[j] ;
    }

    /*
    for (int j=0;j<95;j++){
        //qDebug() << "3)- x0_stripFulW[j] " << x0CB_stripAdjW[j] ;

        y1_FullWinChannel[j] = y0CB_FullWinChannel[j];
        y1_AdjWinChannel[j] = y0CB_AdjWinChannel[j];
        x1_stripFulW[j] = x0CB_stripFulW[j] ;
        x1_stripAdjW[j] = x0CB_stripAdjW[j] ;
    }*/

    QCPBars *AdjWinHst = new QCPBars(subRectTop->axis(QCPAxis::atBottom), subRectTop->axis(QCPAxis::atLeft));

    //QCPBars *AdjWinHst = new QCPBars(ui->plot_LB1->xAxis, ui->plot_LB1->yAxis);


    AdjWinHst->setAntialiased(false); // gives more crisp, pixel aligned bar borders
    AdjWinHst->setStackingGap(1);
    AdjWinHst->setName("MultiChannel Histogram - Adjustable Window ");
    AdjWinHst->setPen(QPen(QColor(0, 168, 140).lighter(130)));
    AdjWinHst->setBrush(QColor(0, 168, 140));



    QCPBars *FulWinHst = new QCPBars(subRectBotton->axis(QCPAxis::atBottom), subRectBotton->axis(QCPAxis::atLeft));

    FulWinHst->setAntialiased(true); // gives more crisp, pixel aligned bar borders
    FulWinHst->setStackingGap(1);
    FulWinHst->setName("MultiChannel Histogram - Full Window ");
    FulWinHst->setPen(QPen(QColor("#705BE8").lighter(130)));
    FulWinHst->setBrush(QColor("#705BE8"));


    // prepare x axis with channel labels:

    QVector<double> ticks (100);
    QVector<QString> labels(100);
    for (int j=0 ; j<95;j++){

        ticks[j] = j+1 ;
        labels[j] = QString("%1").arg(j+1);
    }

    // set dark background gradient:

    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->plot_LB1->setBackground(QBrush(gradient));


    AdjWinHst->setData(ticks,y1_AdjWinChannel);

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->plot_LB1->xAxis->setTicker(textTicker);
    subRectTop->axis(QCPAxis::atBottom)->setTickLabelRotation(60);
    subRectTop->axis(QCPAxis::atBottom)->setLabel("RPC Channels 1-96");
    subRectTop->axis(QCPAxis::atBottom)->setSubTicks(false);
    subRectTop->axis(QCPAxis::atBottom)->setTickLength(0, 4);
    subRectTop->axis(QCPAxis::atBottom)->setRange(0, 96);
    subRectTop->axis(QCPAxis::atBottom)->setBasePen(QPen(Qt::white));
    subRectTop->axis(QCPAxis::atBottom)->setTickPen(QPen(Qt::white));
    subRectTop->axis(QCPAxis::atBottom)->setSubTickPen(QPen(Qt::white));
    subRectTop->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    subRectTop->axis(QCPAxis::atBottom)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTop->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::white);
    subRectTop->axis(QCPAxis::atBottom)->setLabelColor(Qt::white);

    subRectTop->axis(QCPAxis::atTop)->setRange(0, 96);
    subRectTop->axis(QCPAxis::atTop)->setTickLength(0, 4);
    subRectTop->axis(QCPAxis::atTop)->setSubTicks(true);
    subRectTop->axis(QCPAxis::atTop)->setBasePen(QPen(Qt::white));
    subRectTop->axis(QCPAxis::atTop)->setTickPen(QPen(Qt::white));
    subRectTop->axis(QCPAxis::atTop)->setSubTickPen(QPen(Qt::white));
    subRectTop->axis(QCPAxis::atTop)->grid()->setVisible(true);
    subRectTop->axis(QCPAxis::atTop)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTop->axis(QCPAxis::atTop)->setTickLabelColor(Qt::white);
    subRectTop->axis(QCPAxis::atTop)->setLabelColor(Qt::white);

    // prepare y axis:
    subRectTop->axis(QCPAxis::atLeft)->setRange(0, 96);
    subRectTop->axis(QCPAxis::atLeft)->setPadding(1); // a bit more space to the left border
    subRectTop->axis(QCPAxis::atLeft)->setLabel(" Hit Rate (kHz) ");
    subRectTop->axis(QCPAxis::atLeft)->setBasePen(QPen(Qt::white));
    subRectTop->axis(QCPAxis::atLeft)->setTickPen(QPen(Qt::white));
    subRectTop->axis(QCPAxis::atLeft)->setSubTickPen(QPen(Qt::white));
    subRectTop->axis(QCPAxis::atLeft)->grid()->setSubGridVisible(true);
    subRectTop->axis(QCPAxis::atLeft)->setTickLabelColor(Qt::white);
    subRectTop->axis(QCPAxis::atLeft)->setLabelColor(Qt::white);
    subRectTop->axis(QCPAxis::atLeft)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTop->axis(QCPAxis::atLeft)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));


    subRectTop->axis(QCPAxis::atRight)->setRange(0, 96);
    subRectTop->axis(QCPAxis::atRight)->setPadding(1); // a bit more space to the left border
    subRectTop->axis(QCPAxis::atRight)->setBasePen(QPen(Qt::white));
    subRectTop->axis(QCPAxis::atRight)->setTickPen(QPen(Qt::white));
    subRectTop->axis(QCPAxis::atRight)->setSubTickPen(QPen(Qt::white));
    subRectTop->axis(QCPAxis::atRight)->grid()->setSubGridVisible(true);
    subRectTop->axis(QCPAxis::atRight)->setTickLabelColor(Qt::white);
    //subRectTop->axis(QCPAxis::atRight)->setLabelColor(Qt::white);
    subRectTop->axis(QCPAxis::atRight)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTop->axis(QCPAxis::atRight)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));



    FulWinHst->setData(ticks,y1_FullWinChannel);

    QSharedPointer<QCPAxisTickerText> textTicker2(new QCPAxisTickerText);
    textTicker2->addTicks(ticks, labels);
    subRectBotton->axis(QCPAxis::atBottom)->setTicker(textTicker);
    subRectBotton->axis(QCPAxis::atBottom)->setTickLabelRotation(60);
    subRectBotton->axis(QCPAxis::atBottom)->setLabel("RPC Channels 1-96");
    subRectBotton->axis(QCPAxis::atBottom)->setSubTicks(false);
    subRectBotton->axis(QCPAxis::atBottom)->setTickLength(0, 4);
    subRectBotton->axis(QCPAxis::atBottom)->setRange(0, 96);
    subRectBotton->axis(QCPAxis::atBottom)->setBasePen(QPen(Qt::white));
    subRectBotton->axis(QCPAxis::atBottom)->setTickPen(QPen(Qt::white));
    subRectBotton->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    subRectBotton->axis(QCPAxis::atBottom)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectBotton->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::white);
    subRectBotton->axis(QCPAxis::atBottom)->setLabelColor(Qt::white);


    subRectBotton->axis(QCPAxis::atTop)->setRange(0, 96);
    subRectBotton->axis(QCPAxis::atTop)->setTickLength(0, 4);
    subRectBotton->axis(QCPAxis::atTop)->setSubTicks(true);
    subRectBotton->axis(QCPAxis::atTop)->setBasePen(QPen(Qt::white));
    subRectBotton->axis(QCPAxis::atTop)->setTickPen(QPen(Qt::white));
    subRectBotton->axis(QCPAxis::atTop)->setSubTickPen(QPen(Qt::white));
    subRectBotton->axis(QCPAxis::atTop)->grid()->setVisible(true);
    subRectBotton->axis(QCPAxis::atTop)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectBotton->axis(QCPAxis::atTop)->setTickLabelColor(Qt::white);
    subRectBotton->axis(QCPAxis::atTop)->setLabelColor(Qt::white);


    //subRectBotton->axis(QCPAxis::atTop)->setLabel("MultiChannel Histogram - Adjustable Window ");

    // prepare y axis:
    subRectBotton->axis(QCPAxis::atLeft)->setRange(0, 96);
    subRectBotton->axis(QCPAxis::atLeft)->setPadding(1); // a bit more space to the left border
    subRectBotton->axis(QCPAxis::atLeft)->setLabel(" Hit Rate (kHz) ");
    subRectBotton->axis(QCPAxis::atLeft)->setBasePen(QPen(Qt::white));
    subRectBotton->axis(QCPAxis::atLeft)->setTickPen(QPen(Qt::white));
    subRectBotton->axis(QCPAxis::atLeft)->setSubTickPen(QPen(Qt::white));
    subRectBotton->axis(QCPAxis::atLeft)->grid()->setSubGridVisible(true);
    subRectBotton->axis(QCPAxis::atLeft)->setTickLabelColor(Qt::white);
    subRectBotton->axis(QCPAxis::atLeft)->setLabelColor(Qt::white);
    subRectBotton->axis(QCPAxis::atLeft)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectBotton->axis(QCPAxis::atLeft)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    subRectBotton->axis(QCPAxis::atRight)->setRange(0, 96);
    subRectBotton->axis(QCPAxis::atRight)->setPadding(1); // a bit more space to the left border
    subRectBotton->axis(QCPAxis::atRight)->setBasePen(QPen(Qt::white));
    subRectBotton->axis(QCPAxis::atRight)->setTickPen(QPen(Qt::white));
    subRectBotton->axis(QCPAxis::atRight)->setSubTickPen(QPen(Qt::white));
    subRectBotton->axis(QCPAxis::atRight)->grid()->setSubGridVisible(true);
    subRectBotton->axis(QCPAxis::atRight)->setTickLabelColor(Qt::white);
    //subRectBotton->axis(QCPAxis::atRight)->setLabelColor(Qt::white);
    subRectBotton->axis(QCPAxis::atRight)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectBotton->axis(QCPAxis::atRight)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));



    ui->plot_LB1->replot();

}
//=================================================


//=================================================
void realTime::setupPlot_LB2(void){


    QVector <double> y1_FullWinChannel (100);
    QVector <double> y1_AdjWinChannel (100);

    QVector <double> x1_stripFulW (100);
    QVector <double> x1_stripAdjW (100);



    for (int j=0;j<95;j++){
        //qDebug() << "3)- x0_stripFulW[j] " << x0LB2_stripAdjW[j] ;

        y1_FullWinChannel[j] = y0LB2_FullWinChannel[j];
        y1_AdjWinChannel[j] = y0LB2_AdjWinChannel[j];
        x1_stripFulW[j] = x0LB2_stripFulW[j] ;
        x1_stripAdjW[j] = x0LB2_stripAdjW[j] ;
    }


    ui->plot_LB2 ->addGraph();
    // pass data points to graphs:
    ui->plot_LB2->graph(0)->setData(x1_stripFulW, y1_FullWinChannel);
    ui->plot_LB2->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot_LB2->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));// first graph will be filled with translucent blue
    ui->plot_LB2->xAxis->setRange(0,1000);
    ui->plot_LB2->yAxis->setRange(0,1000);
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->plot_LB2->xAxis2->setVisible(true);
    ui->plot_LB2->xAxis2->setTickLabels(false);
    ui->plot_LB2->yAxis2->setVisible(true);
    ui->plot_LB2->yAxis2->setTickLabels(false);

    ui->plot_LB2 ->addGraph();
    //ui->plot_LB2->graph(1)->setData(x,y);
    ui->plot_LB2->graph(1)->setScatterStyle(QCPScatterStyle::ssCross);
    ui->plot_LB2->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    ui->plot_LB2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->plot_LB2->graph(0)->rescaleAxes();

    ui->plot_LB2->legend->setVisible(true);
    ui->plot_LB2->legend->setFont(QFont("Helvetica",9));
    ui->plot_LB2->replot();

}
//=================================================


//=================================================
void realTime::setupPlot_LB3(void){


    QVector <double> y1_FullWinChannel (100);
    QVector <double> y1_AdjWinChannel (100);

    QVector <double> x1_stripFulW (100);
    QVector <double> x1_stripAdjW (100);



    for (int j=0;j<95;j++){
        //qDebug() << "3)- x0_stripFulW[j] " << x0LB3_stripAdjW[j] ;

        y1_FullWinChannel[j] = y0LB3_FullWinChannel[j];
        y1_AdjWinChannel[j] = y0LB3_AdjWinChannel[j];
        x1_stripFulW[j] = x0LB3_stripFulW[j] ;
        x1_stripAdjW[j] = x0LB3_stripAdjW[j] ;
    }


    ui->plot_LB3 ->addGraph();
    // pass data points to graphs:
    ui->plot_LB3->graph(0)->setData(x1_stripFulW, y1_FullWinChannel);
    ui->plot_LB3->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot_LB3->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));// first graph will be filled with translucent blue
    ui->plot_LB3->xAxis->setRange(0,1000);
    ui->plot_LB3->yAxis->setRange(0,1000);
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->plot_LB3->xAxis2->setVisible(true);
    ui->plot_LB3->xAxis2->setTickLabels(false);
    ui->plot_LB3->yAxis2->setVisible(true);
    ui->plot_LB3->yAxis2->setTickLabels(false);

    ui->plot_LB3 ->addGraph();
    //ui->plot_LB3->graph(1)->setData(x,y);
    ui->plot_LB3->graph(1)->setScatterStyle(QCPScatterStyle::ssCross);
    ui->plot_LB3->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    ui->plot_LB3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->plot_LB3->graph(0)->rescaleAxes();

    ui->plot_LB3->legend->setVisible(true);
    ui->plot_LB3->legend->setFont(QFont("Helvetica",9));
    ui->plot_LB3->replot();

}
//=================================================

//=================================================
void realTime::setupPlot_LB4(void){


    QVector <double> y1_FullWinChannel (100);
    QVector <double> y1_AdjWinChannel (100);

    QVector <double> x1_stripFulW (100);
    QVector <double> x1_stripAdjW (100);



    for (int j=0;j<95;j++){
        //qDebug() << "3)- x0_stripFulW[j] " << x0LB4_stripAdjW[j] ;

        y1_FullWinChannel[j] = y0LB4_FullWinChannel[j];
        y1_AdjWinChannel[j] = y0LB4_AdjWinChannel[j];
        x1_stripFulW[j] = x0LB4_stripFulW[j] ;
        x1_stripAdjW[j] = x0LB4_stripAdjW[j] ;
    }


    ui->plot_LB4 ->addGraph();
    // pass data points to graphs:
    ui->plot_LB4->graph(0)->setData(x1_stripFulW, y1_FullWinChannel);
    ui->plot_LB4->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot_LB4->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));// first graph will be filled with translucent blue
    ui->plot_LB4->xAxis->setRange(0,1000);
    ui->plot_LB4->yAxis->setRange(0,1000);
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->plot_LB4->xAxis2->setVisible(true);
    ui->plot_LB4->xAxis2->setTickLabels(false);
    ui->plot_LB4->yAxis2->setVisible(true);
    ui->plot_LB4->yAxis2->setTickLabels(false);

    ui->plot_LB4 ->addGraph();
    //ui->plot_LB4->graph(1)->setData(x,y);
    ui->plot_LB4->graph(1)->setScatterStyle(QCPScatterStyle::ssCross);
    ui->plot_LB4->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    ui->plot_LB4->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->plot_LB4->graph(0)->rescaleAxes();

    ui->plot_LB4->legend->setVisible(true);
    ui->plot_LB4->legend->setFont(QFont("Helvetica",9));
    ui->plot_LB4->replot();

}
//=================================================

//=================================================
void realTime::setupPlot_LB5(void){


    QVector <double> y1_FullWinChannel (100);
    QVector <double> y1_AdjWinChannel (100);

    QVector <double> x1_stripFulW (100);
    QVector <double> x1_stripAdjW (100);



    for (int j=0;j<95;j++){
        //qDebug() << "3)- x0_stripFulW[j] " << x0LB5_stripAdjW[j] ;

        y1_FullWinChannel[j] = y0LB5_FullWinChannel[j];
        y1_AdjWinChannel[j] = y0LB5_AdjWinChannel[j];
        x1_stripFulW[j] = x0LB5_stripFulW[j] ;
        x1_stripAdjW[j] = x0LB5_stripAdjW[j] ;
    }


    ui->plot_LB5 ->addGraph();
    // pass data points to graphs:
    ui->plot_LB5->graph(0)->setData(x1_stripFulW, y1_FullWinChannel);
    ui->plot_LB5->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot_LB5->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));// first graph will be filled with translucent blue
    ui->plot_LB5->xAxis->setRange(0,1000);
    ui->plot_LB5->yAxis->setRange(0,1000);
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->plot_LB5->xAxis2->setVisible(true);
    ui->plot_LB5->xAxis2->setTickLabels(false);
    ui->plot_LB5->yAxis2->setVisible(true);
    ui->plot_LB5->yAxis2->setTickLabels(false);

    ui->plot_LB5 ->addGraph();
    //ui->plot_LB5->graph(1)->setData(x,y);
    ui->plot_LB5->graph(1)->setScatterStyle(QCPScatterStyle::ssCross);
    ui->plot_LB5->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    ui->plot_LB5->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->plot_LB5->graph(0)->rescaleAxes();

    ui->plot_LB5->legend->setVisible(true);
    ui->plot_LB5->legend->setFont(QFont("Helvetica",9));
    ui->plot_LB5->replot();

}
//=================================================

//=================================================
void realTime::setupPlot_LB6(void){


    QVector <double> y1_FullWinChannel (100);
    QVector <double> y1_AdjWinChannel (100);

    QVector <double> x1_stripFulW (100);
    QVector <double> x1_stripAdjW (100);



    for (int j=0;j<95;j++){
        //qDebug() << "3)- x0_stripFulW[j] " << x0LB6_stripAdjW[j] ;

        y1_FullWinChannel[j] = y0LB6_FullWinChannel[j];
        y1_AdjWinChannel[j] = y0LB6_AdjWinChannel[j];
        x1_stripFulW[j] = x0LB6_stripFulW[j] ;
        x1_stripAdjW[j] = x0LB6_stripAdjW[j] ;
    }


    ui->plot_LB6 ->addGraph();
    // pass data points to graphs:
    ui->plot_LB6->graph(0)->setData(x1_stripFulW, y1_FullWinChannel);
    ui->plot_LB6->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot_LB6->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));// first graph will be filled with translucent blue
    ui->plot_LB6->xAxis->setRange(0,1000);
    ui->plot_LB6->yAxis->setRange(0,1000);
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->plot_LB6->xAxis2->setVisible(true);
    ui->plot_LB6->xAxis2->setTickLabels(false);
    ui->plot_LB6->yAxis2->setVisible(true);
    ui->plot_LB6->yAxis2->setTickLabels(false);

    ui->plot_LB6 ->addGraph();
    //ui->plot_LB6->graph(1)->setData(x,y);
    ui->plot_LB6->graph(1)->setScatterStyle(QCPScatterStyle::ssCross);
    ui->plot_LB6->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    ui->plot_LB6->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->plot_LB6->graph(0)->rescaleAxes();

    ui->plot_LB6->legend->setVisible(true);
    ui->plot_LB6->legend->setFont(QFont("Helvetica",9));
    ui->plot_LB6->replot();

}
//=================================================

//=================================================
void realTime::setupPlot_LB7(void){


    QVector <double> y1_FullWinChannel (100);
    QVector <double> y1_AdjWinChannel (100);

    QVector <double> x1_stripFulW (100);
    QVector <double> x1_stripAdjW (100);



    for (int j=0;j<95;j++){
        //qDebug() << "3)- x0_stripFulW[j] " << x0LB7_stripAdjW[j] ;

        y1_FullWinChannel[j] = y0LB7_FullWinChannel[j];
        y1_AdjWinChannel[j] = y0LB7_AdjWinChannel[j];
        x1_stripFulW[j] = x0LB7_stripFulW[j] ;
        x1_stripAdjW[j] = x0LB7_stripAdjW[j] ;
    }


    ui->plot_LB7 ->addGraph();
    // pass data points to graphs:
    ui->plot_LB7->graph(0)->setData(x1_stripFulW, y1_FullWinChannel);
    ui->plot_LB7->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot_LB7->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));// first graph will be filled with translucent blue
    ui->plot_LB7->xAxis->setRange(0,1000);
    ui->plot_LB7->yAxis->setRange(0,1000);
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->plot_LB7->xAxis2->setVisible(true);
    ui->plot_LB7->xAxis2->setTickLabels(false);
    ui->plot_LB7->yAxis2->setVisible(true);
    ui->plot_LB7->yAxis2->setTickLabels(false);

    ui->plot_LB7 ->addGraph();
    //ui->plot_LB7->graph(1)->setData(x,y);
    ui->plot_LB7->graph(1)->setScatterStyle(QCPScatterStyle::ssCross);
    ui->plot_LB7->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    ui->plot_LB7->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->plot_LB7->graph(0)->rescaleAxes();

    ui->plot_LB7->legend->setVisible(true);
    ui->plot_LB7->legend->setFont(QFont("Helvetica",9));
    ui->plot_LB7->replot();

}
//=================================================

//=================================================
void realTime::setupPlot_LB8(void){


    QVector <double> y1_FullWinChannel (100);
    QVector <double> y1_AdjWinChannel (100);

    QVector <double> x1_stripFulW (100);
    QVector <double> x1_stripAdjW (100);



    for (int j=0;j<95;j++){
        //qDebug() << "3)- x0_stripFulW[j] " << x0LB8_stripAdjW[j] ;

        y1_FullWinChannel[j] = y0LB8_FullWinChannel[j];
        y1_AdjWinChannel[j] = y0LB8_AdjWinChannel[j];
        x1_stripFulW[j] = x0LB8_stripFulW[j] ;
        x1_stripAdjW[j] = x0LB8_stripAdjW[j] ;
    }


    ui->plot_LB8 ->addGraph();
    // pass data points to graphs:
    ui->plot_LB8->graph(0)->setData(x1_stripFulW, y1_FullWinChannel);
    ui->plot_LB8->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot_LB8->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));// first graph will be filled with translucent blue
    ui->plot_LB8->xAxis->setRange(0,1000);
    ui->plot_LB8->yAxis->setRange(0,1000);
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->plot_LB8->xAxis2->setVisible(true);
    ui->plot_LB8->xAxis2->setTickLabels(false);
    ui->plot_LB8->yAxis2->setVisible(true);
    ui->plot_LB8->yAxis2->setTickLabels(false);

    ui->plot_LB8 ->addGraph();
    //ui->plot_LB8->graph(1)->setData(x,y);
    ui->plot_LB8->graph(1)->setScatterStyle(QCPScatterStyle::ssCross);
    ui->plot_LB8->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    ui->plot_LB8->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->plot_LB8->graph(0)->rescaleAxes();

    ui->plot_LB8->legend->setVisible(true);
    ui->plot_LB8->legend->setFont(QFont("Helvetica",9));
    ui->plot_LB8->replot();

}
//=================================================

//=================================================
void realTime::setupPlot_LB9(void){


    QVector <double> y1_FullWinChannel (100);
    QVector <double> y1_AdjWinChannel (100);

    QVector <double> x1_stripFulW (100);
    QVector <double> x1_stripAdjW (100);



    for (int j=0;j<95;j++){
        //qDebug() << "3)- x0_stripFulW[j] " << x0LB9_stripAdjW[j] ;

        y1_FullWinChannel[j] = y0LB9_FullWinChannel[j];
        y1_AdjWinChannel[j] = y0LB9_AdjWinChannel[j];
        x1_stripFulW[j] = x0LB9_stripFulW[j] ;
        x1_stripAdjW[j] = x0LB9_stripAdjW[j] ;
    }


    ui->plot_LB9 ->addGraph();
    // pass data points to graphs:
    ui->plot_LB9->graph(0)->setData(x1_stripFulW, y1_FullWinChannel);
    ui->plot_LB9->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot_LB9->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));// first graph will be filled with translucent blue
    ui->plot_LB9->xAxis->setRange(0,1000);
    ui->plot_LB9->yAxis->setRange(0,1000);
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->plot_LB9->xAxis2->setVisible(true);
    ui->plot_LB9->xAxis2->setTickLabels(false);
    ui->plot_LB9->yAxis2->setVisible(true);
    ui->plot_LB9->yAxis2->setTickLabels(false);

    ui->plot_LB9 ->addGraph();
    //ui->plot_LB9->graph(1)->setData(x,y);
    ui->plot_LB9->graph(1)->setScatterStyle(QCPScatterStyle::ssCross);
    ui->plot_LB9->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    ui->plot_LB9->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->plot_LB9->graph(0)->rescaleAxes();

    ui->plot_LB9->legend->setVisible(true);
    ui->plot_LB9->legend->setFont(QFont("Helvetica",9));
    ui->plot_LB9->replot();

}
//=================================================
