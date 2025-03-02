#include "timingprofile.h"
#include "ui_timingprofile.h"
#include "qcustomplot.h"

#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>


timingprofile::timingprofile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::timingprofile)
{
    ui->setupUi(this);
}

timingprofile::~timingprofile()
{
    delete ui;
}


void timingprofile::setupPlot_CB(void){

    //-----------------------------------------------------------------
    // configure axis rect:
    ui->plot_CB->plotLayout()->clear(); // clear default axis rect so we can start from scratch
    ui->horizontalScrollBar->setRange(-500,500);
    ui->verticalScrollBar->setRange(-500, 500);

    // create connection between axes and scroll bars:
    /*
    connect(ui->horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int)));
    connect(ui->verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(vertScrollBarChanged(int)));
    connect(ui->plot_CB->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));
    connect(ui->plot_CB->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(yAxisChanged(QCPRange)));
    */
    // initialize axis range (and scroll bar positions via signals we just connected):
    //ui->plot_CB->xAxis->setRange(0, 6, Qt::AlignCenter);
    //ui->plot_CB->yAxis->setRange(0, 10, Qt::AlignCenter);
    ui->plot_CB->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    QCPAxisRect *wideAxisRect = new QCPAxisRect(ui->plot_CB);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers


    connect(ui->horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int)));
    connect(ui->verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(vertScrollBarChanged(int)));
    connect(ui->plot_CB->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));
    connect(ui->plot_CB->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(yAxisChanged(QCPRange)));
    //connect(wideAxisRect, SIGNAL(rangeChanged(QCPRange)), this, SLOT(yAxisChanged(QCPRange)));



    //wideAxisRect->setRangeZoomAxes();
    //-----------------------------------------------------------------

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    ui->plot_CB->plotLayout()->addElement(0, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)

    //-----------------------------------------------------------------
    QCPAxisRect *subRectTiming = new QCPAxisRect(ui->plot_CB, false);
    subLayout->addElement(0, 0, subRectTiming);
    //-----------------------------------------------------------------
    subRectTiming->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    //-----------------------------------------------------------------
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot_CB);
    subRectTiming->setMarginGroup(QCP::msBottom, marginGroup);
    wideAxisRect->setMarginGroup(QCP::msTop | QCP::msBottom | QCP::msRight | QCP::msLeft, marginGroup);
    //-----------------------------------------------------------------
    // move newly created axes on "axes" layer and grids on "grid" layer:




    foreach (QCPAxisRect *rect, ui->plot_CB->axisRects())
    {
      foreach (QCPAxis *axis, rect->axes())
      {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
        axis->scaleRange(2);
      }
    }


    //==================================================================
    // set dark background gradient:
    //==================================================================
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->plot_CB->setBackground(QBrush(gradient));
    //==================================================================

    //==================================================================
    QVector <double> y1_timingHist (5000);
    //QVector <double> x1_BxNum (130);
    //==================================================================
    QCPBars *TimingHist = new QCPBars(subRectTiming->axis(QCPAxis::atBottom), subRectTiming->axis(QCPAxis::atLeft));

    TimingHist->setAntialiased(true); // gives more crisp, pixel aligned bar borders
    TimingHist->setStackingGap(1);
    TimingHist->setName("Timing Histogram ");
    TimingHist->setPen(QPen(QColor("#6050F8"),2));
    TimingHist->setBrush(QColor("#6050F8")); // 6050F8 BLUE
                                            // 8070B8 Violet
                                            // FFA100 Yellow
                                            // FF51FF  PINK
                                            // AAAAff Light Blue
   // QLegend *legend = TimingHist->legend();


    //==================================================================
    QVector<double> ticks (5000);
    QVector<QString> labels(5000);

    for (unsigned int j=BxCntVal+0 ; j< BxCntVal+129;j++){

            //ticks[j] = j+1 ;
            ticks[j] = j ;
            //labels[j] = QString("%1").arg(j+1);
            labels[j] = QString("%1").arg(j);

            y1_timingHist[j] = y0LB1_timingHist[j-BxCntVal];

    }


    unsigned int max_value = 0 ;

    for (unsigned int j=BxCntVal+0 ; j< BxCntVal+129;j++){

       if (y1_timingHist[j]>= max_value){
           max_value = y1_timingHist[j];
       }
    }


    //==================================================================

    TimingHist->setData(ticks,y1_timingHist);
    //-----------------------------------------------------------------
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    //-----------------------------------------------------------------
    subRectTiming->axis(QCPAxis::atBottom)->setTicker(textTicker);
    subRectTiming->axis(QCPAxis::atBottom)->setTickLabelRotation(90);
    subRectTiming->axis(QCPAxis::atBottom)->setLabel("Bunch Crossing (#) ");
    subRectTiming->axis(QCPAxis::atBottom)->setSubTicks(false);
    subRectTiming->axis(QCPAxis::atBottom)->setTickLength(0, 4);
    subRectTiming->axis(QCPAxis::atBottom)->setRange(BxCntVal+0, BxCntVal +129); // notice: [BxCntVal+0, BxCntVal +129]
    subRectTiming->axis(QCPAxis::atBottom)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atBottom)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTiming->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atBottom)->setLabelColor(Qt::white);
    //-----------------------------------------------------------------

    subRectTiming->axis(QCPAxis::atTop)->setRange(BxCntVal+0, BxCntVal +129);
    subRectTiming->axis(QCPAxis::atTop)->setTickLength(0, 4);
    subRectTiming->axis(QCPAxis::atTop)->setSubTicks(true);
    subRectTiming->axis(QCPAxis::atTop)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->grid()->setVisible(true);
    subRectTiming->axis(QCPAxis::atTop)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTiming->axis(QCPAxis::atTop)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atTop)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atTop)->setLabel(" LB1 Timing Profile");
    //-----------------------------------------------------------------


    //-----------------------------------------------------------------
    // prepare y axis:
    subRectTiming->axis(QCPAxis::atLeft)->rescale(true);
    //subRectTiming->axis(QCPAxis::atLeft)->setRange(0, 5);
    subRectTiming->axis(QCPAxis::atLeft)->setPadding(1); // a bit more space to the left border
    subRectTiming->axis(QCPAxis::atLeft)->setLabel(" Total Hits ");
    subRectTiming->axis(QCPAxis::atLeft)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setSubGridVisible(true);
    subRectTiming->axis(QCPAxis::atLeft)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atLeft)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    //-----------------------------------------------------------------
    if (max_value == 0){
      subRectTiming->axis(QCPAxis::atRight)->setRange(-2.5, 2.5);
    }else{
        subRectTiming->axis(QCPAxis::atRight)->setRange(0, max_value);
    }
    //subRectTiming->axis(QCPAxis::atRight)->rescale(true);
    subRectTiming->axis(QCPAxis::atRight)->setPadding(1); // a bit more space to the left border
    subRectTiming->axis(QCPAxis::atRight)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->grid()->setSubGridVisible(true);
    subRectTiming->axis(QCPAxis::atRight)->setTickLabelColor(Qt::white);
    //subRectTiming->axis(QCPAxis::atRight)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atRight)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTiming->axis(QCPAxis::atRight)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    //-----------------------------------------------------------------
    ui->plot_CB->replot();
    //-----------------------------------------------------------------
}



void timingprofile::horzScrollBarChanged(int value)
{

    if (qAbs(ui->plot_CB->xAxis->range().center()-value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
  {
    ui->plot_CB->xAxis->setRange(value/100.0, ui->plot_CB->xAxis->range().size(), Qt::AlignCenter);
    ui->plot_CB->replot();
  }
}

void timingprofile::vertScrollBarChanged(int value)
{

  if (qAbs(ui->plot_CB->yAxis->range().center()+value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
  {
    ui->plot_CB->yAxis->setRange(-value/100.0, ui->plot_CB->yAxis->range().size(), Qt::AlignCenter);
    ui->plot_CB->replot();
  }
}

void timingprofile::xAxisChanged(QCPRange range)
{

    ui->horizontalScrollBar->setValue(qRound(range.center()*100.0)); // adjust position of scroll bar slider
  ui->horizontalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider

}

void timingprofile::yAxisChanged(QCPRange range)
{

  ui->verticalScrollBar->setValue(qRound(-range.center()*100.0)); // adjust position of scroll bar slider
  ui->verticalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider

}





void timingprofile::setupPlot_LB(unsigned int LBN){

    unsigned int const LB1 = 1 ;
    unsigned int const LB2 = 2 ;
    unsigned int const LB3 = 3 ;
    unsigned int const LB4 = 4 ;
    unsigned int const LB5 = 5 ;
    unsigned int const LB6 = 6 ;
    unsigned int const LB7 = 7 ;
    unsigned int const LB8 = 8 ;
    unsigned int const LB9 = 9 ;


    switch (LBN) {
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
void timingprofile::setupPlot_LB1(void){


    //-----------------------------------------------------------------
    // configure axis rect:
    ui->plot_LB1->plotLayout()->clear(); // clear default axis rect so we can start from scratch

    QCPAxisRect *wideAxisRect = new QCPAxisRect(ui->plot_LB1);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers
    //-----------------------------------------------------------------

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    ui->plot_LB1->plotLayout()->addElement(0, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
    //-----------------------------------------------------------------
    QCPAxisRect *subRectTiming = new QCPAxisRect(ui->plot_LB1, false);
    subLayout->addElement(0, 0, subRectTiming);
    //-----------------------------------------------------------------
    subRectTiming->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    //-----------------------------------------------------------------
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot_LB1);
    subRectTiming->setMarginGroup(QCP::msBottom, marginGroup);
    wideAxisRect->setMarginGroup(QCP::msTop | QCP::msBottom | QCP::msRight | QCP::msLeft, marginGroup);
    //-----------------------------------------------------------------
    // move newly created axes on "axes" layer and grids on "grid" layer:

    foreach (QCPAxisRect *rect, ui->plot_LB1->axisRects())
    {
      foreach (QCPAxis *axis, rect->axes())
      {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
      }
    }

    //==================================================================
    // set dark background gradient:
    //==================================================================
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->plot_LB1->setBackground(QBrush(gradient));
    //==================================================================

    //==================================================================
    QVector <double> y1_timingHist (5000);
    //QVector <double> x1_BxNum (130);
    //==================================================================
    QCPBars *TimingHist = new QCPBars(subRectTiming->axis(QCPAxis::atBottom), subRectTiming->axis(QCPAxis::atLeft));

    TimingHist->setAntialiased(true); // gives more crisp, pixel aligned bar borders
    TimingHist->setStackingGap(1);
    TimingHist->setName("Timing Histogram ");
    TimingHist->setPen(QPen(QColor("#6050F8"),2));
    TimingHist->setBrush(QColor("#6050F8")); // 6050F8 BLUE
                                            // 8070B8 Violet
                                            // FFA100 Yellow
                                            // FF51FF  PINK
                                            // AAAAff Light Blue
   // QLegend *legend = TimingHist->legend();


    //==================================================================
    QVector<double> ticks (5000);
    QVector<QString> labels(5000);

    for (unsigned int j=BxCntVal+0 ; j< BxCntVal+129;j++){

            //ticks[j] = j+1 ;
            ticks[j] = j ;
            //labels[j] = QString("%1").arg(j+1);
            labels[j] = QString("%1").arg(j);

            y1_timingHist[j] = y0LB1_timingHist[j-BxCntVal];

    }

    unsigned int max_value = 0 ;

    for (unsigned int j=BxCntVal+0 ; j< BxCntVal+129;j++){

       if (y1_timingHist[j]>= max_value){
           max_value = y1_timingHist[j];
       }
    }
    //==================================================================

    TimingHist->setData(ticks,y1_timingHist);
    //-----------------------------------------------------------------
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    //-----------------------------------------------------------------
    subRectTiming->axis(QCPAxis::atBottom)->setTicker(textTicker);
    subRectTiming->axis(QCPAxis::atBottom)->setTickLabelRotation(90);
    subRectTiming->axis(QCPAxis::atBottom)->setLabel("Bunch Cross (#) ");
    subRectTiming->axis(QCPAxis::atBottom)->setSubTicks(false);
    subRectTiming->axis(QCPAxis::atBottom)->setTickLength(0, 4);
    subRectTiming->axis(QCPAxis::atBottom)->setRange(BxCntVal+0, BxCntVal +129); // notice: [BxCntVal+0, BxCntVal +129]
    subRectTiming->axis(QCPAxis::atBottom)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atBottom)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTiming->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atBottom)->setLabelColor(Qt::white);
    //-----------------------------------------------------------------

    subRectTiming->axis(QCPAxis::atTop)->setRange(BxCntVal+0, BxCntVal +129);
    subRectTiming->axis(QCPAxis::atTop)->setTickLength(0, 4);
    subRectTiming->axis(QCPAxis::atTop)->setSubTicks(true);
    subRectTiming->axis(QCPAxis::atTop)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->grid()->setVisible(true);
    subRectTiming->axis(QCPAxis::atTop)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTiming->axis(QCPAxis::atTop)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atTop)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atTop)->setLabel(" LB1 Timing Profile");
    //-----------------------------------------------------------------

    //-----------------------------------------------------------------
    // prepare y axis:
    subRectTiming->axis(QCPAxis::atLeft)->rescale(true);
    //subRectTiming->axis(QCPAxis::atLeft)->setRange(0, 5);
    subRectTiming->axis(QCPAxis::atLeft)->setPadding(1); // a bit more space to the left border
    subRectTiming->axis(QCPAxis::atLeft)->setLabel(" Total Hits ");
    subRectTiming->axis(QCPAxis::atLeft)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setSubGridVisible(true);
    subRectTiming->axis(QCPAxis::atLeft)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atLeft)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    //-----------------------------------------------------------------
    if (max_value == 0){
      subRectTiming->axis(QCPAxis::atRight)->setRange(-2.5, 2.5);
    }else{
        subRectTiming->axis(QCPAxis::atRight)->setRange(0, max_value);
    }
    //subRectTiming->axis(QCPAxis::atRight)->rescale(true);
    //subRectTiming->axis(QCPAxis::atRight)->setPadding(1); // a bit more space to the left border
    subRectTiming->axis(QCPAxis::atRight)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->grid()->setSubGridVisible(true);
    subRectTiming->axis(QCPAxis::atRight)->setTickLabelColor(Qt::white);
    //subRectTiming->axis(QCPAxis::atRight)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atRight)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTiming->axis(QCPAxis::atRight)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    //-----------------------------------------------------------------

    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 9);

    ui->plot_LB1->replot();
    //-----------------------------------------------------------------

}
//=================================================


//=================================================
void timingprofile::setupPlot_LB2(void){

    //-----------------------------------------------------------------
    // configure axis rect:
    ui->plot_LB2->plotLayout()->clear(); // clear default axis rect so we can start from scratch
    QCPAxisRect *wideAxisRect = new QCPAxisRect(ui->plot_LB2);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers
    //-----------------------------------------------------------------

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    ui->plot_LB2->plotLayout()->addElement(0, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
    //-----------------------------------------------------------------
    QCPAxisRect *subRectTiming = new QCPAxisRect(ui->plot_LB2, false);
    subLayout->addElement(0, 0, subRectTiming);
    //-----------------------------------------------------------------
    subRectTiming->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    //-----------------------------------------------------------------
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot_LB2);
    subRectTiming->setMarginGroup(QCP::msBottom, marginGroup);
    wideAxisRect->setMarginGroup(QCP::msTop | QCP::msBottom | QCP::msRight | QCP::msLeft, marginGroup);
    //-----------------------------------------------------------------
    // move newly created axes on "axes" layer and grids on "grid" layer:

    foreach (QCPAxisRect *rect, ui->plot_LB2->axisRects())
    {
      foreach (QCPAxis *axis, rect->axes())
      {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
      }
    }

    //==================================================================
    // set dark background gradient:
    //==================================================================
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->plot_LB2->setBackground(QBrush(gradient));
    //==================================================================

    //==================================================================
    QVector <double> y1_timingHist (5000);
    //QVector <double> x1_BxNum (130);
    //==================================================================
    QCPBars *TimingHist = new QCPBars(subRectTiming->axis(QCPAxis::atBottom), subRectTiming->axis(QCPAxis::atLeft));

    TimingHist->setAntialiased(true); // gives more crisp, pixel aligned bar borders
    TimingHist->setStackingGap(1);
    TimingHist->setName("Timing Histogram ");
    TimingHist->setPen(QPen(QColor("#6050F8"),2));
    TimingHist->setBrush(QColor("#6050F8")); // 6050F8 BLUE
                                            // 8070B8 Violet
                                            // FFA100 Yellow
                                            // FF51FF  PINK
                                            // AAAAff Light Blue
   // QLegend *legend = TimingHist->legend();


    //==================================================================
    QVector<double> ticks (5000);
    QVector<QString> labels(5000);

    for (unsigned int j=BxCntVal+0 ; j< BxCntVal+129;j++){

            //ticks[j] = j+1 ;
            ticks[j] = j ;
            //labels[j] = QString("%1").arg(j+1);
            labels[j] = QString("%1").arg(j);

            y1_timingHist[j] = y0LB1_timingHist[j-BxCntVal];

    }

    unsigned int max_value = 0 ;

    for (unsigned int j=BxCntVal+0 ; j< BxCntVal+129;j++){

       if (y1_timingHist[j]>= max_value){
           max_value = y1_timingHist[j];
       }
    }
    //==================================================================

    TimingHist->setData(ticks,y1_timingHist);
    //-----------------------------------------------------------------
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    //-----------------------------------------------------------------
    subRectTiming->axis(QCPAxis::atBottom)->setTicker(textTicker);
    subRectTiming->axis(QCPAxis::atBottom)->setTickLabelRotation(90);
    subRectTiming->axis(QCPAxis::atBottom)->setLabel("Bunch Cross (#) \n Timing Profile LB2");
    subRectTiming->axis(QCPAxis::atBottom)->setSubTicks(false);
    subRectTiming->axis(QCPAxis::atBottom)->setTickLength(0, 4);
    subRectTiming->axis(QCPAxis::atBottom)->setRange(BxCntVal+0, BxCntVal +129); // notice: [BxCntVal+0, BxCntVal +129]
    subRectTiming->axis(QCPAxis::atBottom)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atBottom)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTiming->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atBottom)->setLabelColor(Qt::white);
    //-----------------------------------------------------------------

    subRectTiming->axis(QCPAxis::atTop)->setRange(BxCntVal+0, BxCntVal +129);
    subRectTiming->axis(QCPAxis::atTop)->setTickLength(0, 4);
    subRectTiming->axis(QCPAxis::atTop)->setSubTicks(true);
    subRectTiming->axis(QCPAxis::atTop)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->grid()->setVisible(true);
    subRectTiming->axis(QCPAxis::atTop)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTiming->axis(QCPAxis::atTop)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atTop)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atTop)->setLabel(" LB2 Timing Profile");
    //-----------------------------------------------------------------

    //-----------------------------------------------------------------
    // prepare y axis:
    subRectTiming->axis(QCPAxis::atLeft)->rescale(true);
    //subRectTiming->axis(QCPAxis::atLeft)->setRange(0, 5);
    subRectTiming->axis(QCPAxis::atLeft)->setPadding(1); // a bit more space to the left border
    subRectTiming->axis(QCPAxis::atLeft)->setLabel(" Total Hits ");
    subRectTiming->axis(QCPAxis::atLeft)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setSubGridVisible(true);
    subRectTiming->axis(QCPAxis::atLeft)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atLeft)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    //-----------------------------------------------------------------
    if (max_value == 0){
      subRectTiming->axis(QCPAxis::atRight)->setRange(-2.5, 2.5);
    }else{
        subRectTiming->axis(QCPAxis::atRight)->setRange(0, max_value);
    }
    //subRectTiming->axis(QCPAxis::atRight)->rescale(true);
    subRectTiming->axis(QCPAxis::atRight)->setPadding(1); // a bit more space to the left border
    subRectTiming->axis(QCPAxis::atRight)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->grid()->setSubGridVisible(true);
    subRectTiming->axis(QCPAxis::atRight)->setTickLabelColor(Qt::white);
    //subRectTiming->axis(QCPAxis::atRight)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atRight)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTiming->axis(QCPAxis::atRight)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    //-----------------------------------------------------------------
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 8);
    ui->plot_LB2->replot();
    //-----------------------------------------------------------------


}
//=================================================


//=================================================
void timingprofile::setupPlot_LB3(void){

    //-----------------------------------------------------------------
    // configure axis rect:
    ui->plot_LB3->plotLayout()->clear(); // clear default axis rect so we can start from scratch
    QCPAxisRect *wideAxisRect = new QCPAxisRect(ui->plot_LB3);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers
    //-----------------------------------------------------------------

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    ui->plot_LB3->plotLayout()->addElement(0, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
    //-----------------------------------------------------------------
    QCPAxisRect *subRectTiming = new QCPAxisRect(ui->plot_LB3, false);
    subLayout->addElement(0, 0, subRectTiming);
    //-----------------------------------------------------------------
    subRectTiming->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    //-----------------------------------------------------------------
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot_LB3);
    subRectTiming->setMarginGroup(QCP::msBottom, marginGroup);
    wideAxisRect->setMarginGroup(QCP::msTop | QCP::msBottom | QCP::msRight | QCP::msLeft, marginGroup);
    //-----------------------------------------------------------------
    // move newly created axes on "axes" layer and grids on "grid" layer:

    foreach (QCPAxisRect *rect, ui->plot_LB3->axisRects())
    {
      foreach (QCPAxis *axis, rect->axes())
      {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
      }
    }

    //==================================================================
    // set dark background gradient:
    //==================================================================
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->plot_LB3->setBackground(QBrush(gradient));
    //==================================================================

    //==================================================================
    QVector <double> y1_timingHist (5000);
    //QVector <double> x1_BxNum (130);
    //==================================================================
    QCPBars *TimingHist = new QCPBars(subRectTiming->axis(QCPAxis::atBottom), subRectTiming->axis(QCPAxis::atLeft));

    TimingHist->setAntialiased(true); // gives more crisp, pixel aligned bar borders
    TimingHist->setStackingGap(1);
    TimingHist->setName("Timing Histogram ");
    TimingHist->setPen(QPen(QColor("#6050F8"),2));
    TimingHist->setBrush(QColor("#6050F8")); // 6050F8 BLUE
                                            // 8070B8 Violet
                                            // FFA100 Yellow
                                            // FF51FF  PINK
                                            // AAAAff Light Blue
   // QLegend *legend = TimingHist->legend();


    //==================================================================
    QVector<double> ticks (5000);
    QVector<QString> labels(5000);

    for (unsigned int j=BxCntVal+0 ; j< BxCntVal+129;j++){

            //ticks[j] = j+1 ;
            ticks[j] = j ;
            //labels[j] = QString("%1").arg(j+1);
            labels[j] = QString("%1").arg(j);

            y1_timingHist[j] = y0LB1_timingHist[j-BxCntVal];

    }
    unsigned int max_value = 0 ;

    for (unsigned int j=BxCntVal+0 ; j< BxCntVal+129;j++){

       if (y1_timingHist[j]>= max_value){
           max_value = y1_timingHist[j];
       }
    }
    //==================================================================

    TimingHist->setData(ticks,y1_timingHist);
    //-----------------------------------------------------------------
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    //-----------------------------------------------------------------
    subRectTiming->axis(QCPAxis::atBottom)->setTicker(textTicker);
    subRectTiming->axis(QCPAxis::atBottom)->setTickLabelRotation(90);
    subRectTiming->axis(QCPAxis::atBottom)->setLabel("Bunch Cross (#) \n Timing Profile LB2");
    subRectTiming->axis(QCPAxis::atBottom)->setSubTicks(false);
    subRectTiming->axis(QCPAxis::atBottom)->setTickLength(0, 4);
    subRectTiming->axis(QCPAxis::atBottom)->setRange(BxCntVal+0, BxCntVal +129); // notice: [BxCntVal+0, BxCntVal +129]
    subRectTiming->axis(QCPAxis::atBottom)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atBottom)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTiming->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atBottom)->setLabelColor(Qt::white);
    //-----------------------------------------------------------------

    subRectTiming->axis(QCPAxis::atTop)->setRange(BxCntVal+0, BxCntVal +129);
    subRectTiming->axis(QCPAxis::atTop)->setTickLength(0, 4);
    subRectTiming->axis(QCPAxis::atTop)->setSubTicks(true);
    subRectTiming->axis(QCPAxis::atTop)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->grid()->setVisible(true);
    subRectTiming->axis(QCPAxis::atTop)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTiming->axis(QCPAxis::atTop)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atTop)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atTop)->setLabel(" LB3 Timing Profile");
    //-----------------------------------------------------------------

    //-----------------------------------------------------------------
    // prepare y axis:
    subRectTiming->axis(QCPAxis::atLeft)->rescale(true);
    //subRectTiming->axis(QCPAxis::atLeft)->setRange(0, 5);
    subRectTiming->axis(QCPAxis::atLeft)->setPadding(1); // a bit more space to the left border
    subRectTiming->axis(QCPAxis::atLeft)->setLabel(" Total Hits ");
    subRectTiming->axis(QCPAxis::atLeft)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setSubGridVisible(true);
    subRectTiming->axis(QCPAxis::atLeft)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atLeft)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    //-----------------------------------------------------------------
    if (max_value == 0){
      subRectTiming->axis(QCPAxis::atRight)->setRange(-2.5, 2.5);
    }else{
        subRectTiming->axis(QCPAxis::atRight)->setRange(0, max_value);
    }
    //subRectTiming->axis(QCPAxis::atRight)->rescale(true);
    subRectTiming->axis(QCPAxis::atRight)->setPadding(1); // a bit more space to the left border
    subRectTiming->axis(QCPAxis::atRight)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->grid()->setSubGridVisible(true);
    subRectTiming->axis(QCPAxis::atRight)->setTickLabelColor(Qt::white);
    //subRectTiming->axis(QCPAxis::atRight)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atRight)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTiming->axis(QCPAxis::atRight)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    //-----------------------------------------------------------------
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 7);
    ui->plot_LB3->replot();
    //-----------------------------------------------------------------
}
//=================================================

//=================================================
void timingprofile::setupPlot_LB4(void){

    //-----------------------------------------------------------------
    // configure axis rect:
    ui->plot_LB4->plotLayout()->clear(); // clear default axis rect so we can start from scratch
    QCPAxisRect *wideAxisRect = new QCPAxisRect(ui->plot_LB4);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers
    //-----------------------------------------------------------------

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    ui->plot_LB4->plotLayout()->addElement(0, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
    //-----------------------------------------------------------------
    QCPAxisRect *subRectTiming = new QCPAxisRect(ui->plot_LB4, false);
    subLayout->addElement(0, 0, subRectTiming);
    //-----------------------------------------------------------------
    subRectTiming->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    //-----------------------------------------------------------------
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot_LB4);
    subRectTiming->setMarginGroup(QCP::msBottom, marginGroup);
    wideAxisRect->setMarginGroup(QCP::msTop | QCP::msBottom | QCP::msRight | QCP::msLeft, marginGroup);
    //-----------------------------------------------------------------
    // move newly created axes on "axes" layer and grids on "grid" layer:

    foreach (QCPAxisRect *rect, ui->plot_LB4->axisRects())
    {
      foreach (QCPAxis *axis, rect->axes())
      {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
      }
    }

    //==================================================================
    // set dark background gradient:
    //==================================================================
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->plot_LB4->setBackground(QBrush(gradient));
    //==================================================================

    //==================================================================
    QVector <double> y1_timingHist (5000);
    //QVector <double> x1_BxNum (130);
    //==================================================================
    QCPBars *TimingHist = new QCPBars(subRectTiming->axis(QCPAxis::atBottom), subRectTiming->axis(QCPAxis::atLeft));

    TimingHist->setAntialiased(true); // gives more crisp, pixel aligned bar borders
    TimingHist->setStackingGap(1);
    TimingHist->setName("Timing Histogram ");
    TimingHist->setPen(QPen(QColor("#6050F8"),2));
    TimingHist->setBrush(QColor("#6050F8")); // 6050F8 BLUE
                                            // 8070B8 Violet
                                            // FFA100 Yellow
                                            // FF51FF  PINK
                                            // AAAAff Light Blue
   // QLegend *legend = TimingHist->legend();


    //==================================================================
    QVector<double> ticks (5000);
    QVector<QString> labels(5000);

    for (unsigned int j=BxCntVal+0 ; j< BxCntVal+129;j++){

            //ticks[j] = j+1 ;
            ticks[j] = j ;
            //labels[j] = QString("%1").arg(j+1);
            labels[j] = QString("%1").arg(j);

            y1_timingHist[j] = y0LB1_timingHist[j-BxCntVal];

    }
    unsigned int max_value = 0 ;

    for (unsigned int j=BxCntVal+0 ; j< BxCntVal+129;j++){

       if (y1_timingHist[j]>= max_value){
           max_value = y1_timingHist[j];
       }
    }
    //==================================================================

    TimingHist->setData(ticks,y1_timingHist);
    //-----------------------------------------------------------------
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    //-----------------------------------------------------------------
    subRectTiming->axis(QCPAxis::atBottom)->setTicker(textTicker);
    subRectTiming->axis(QCPAxis::atBottom)->setTickLabelRotation(90);
    subRectTiming->axis(QCPAxis::atBottom)->setLabel("Bunch Cross (#) \n Timing Profile LB2");
    subRectTiming->axis(QCPAxis::atBottom)->setSubTicks(false);
    subRectTiming->axis(QCPAxis::atBottom)->setTickLength(0, 4);
    subRectTiming->axis(QCPAxis::atBottom)->setRange(BxCntVal+0, BxCntVal +129); // notice: [BxCntVal+0, BxCntVal +129]
    subRectTiming->axis(QCPAxis::atBottom)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atBottom)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTiming->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atBottom)->setLabelColor(Qt::white);
    //-----------------------------------------------------------------

    subRectTiming->axis(QCPAxis::atTop)->setRange(BxCntVal+0, BxCntVal +129);
    subRectTiming->axis(QCPAxis::atTop)->setTickLength(0, 4);
    subRectTiming->axis(QCPAxis::atTop)->setSubTicks(true);
    subRectTiming->axis(QCPAxis::atTop)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->grid()->setVisible(true);
    subRectTiming->axis(QCPAxis::atTop)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTiming->axis(QCPAxis::atTop)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atTop)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atTop)->setLabel(" LB4 Timing Profile");
    //-----------------------------------------------------------------

    //-----------------------------------------------------------------
    // prepare y axis:
    subRectTiming->axis(QCPAxis::atLeft)->rescale(true);
    //subRectTiming->axis(QCPAxis::atLeft)->setRange(0, 5);
    subRectTiming->axis(QCPAxis::atLeft)->setPadding(1); // a bit more space to the left border
    subRectTiming->axis(QCPAxis::atLeft)->setLabel(" Total Hits ");
    subRectTiming->axis(QCPAxis::atLeft)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setSubGridVisible(true);
    subRectTiming->axis(QCPAxis::atLeft)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atLeft)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    //-----------------------------------------------------------------
    if (max_value == 0){
      subRectTiming->axis(QCPAxis::atRight)->setRange(-2.5, 2.5);
    }else{
        subRectTiming->axis(QCPAxis::atRight)->setRange(0, max_value);
    }
    //subRectTiming->axis(QCPAxis::atRight)->rescale(true);
    subRectTiming->axis(QCPAxis::atRight)->setPadding(1); // a bit more space to the left border
    subRectTiming->axis(QCPAxis::atRight)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->grid()->setSubGridVisible(true);
    subRectTiming->axis(QCPAxis::atRight)->setTickLabelColor(Qt::white);
    //subRectTiming->axis(QCPAxis::atRight)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atRight)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTiming->axis(QCPAxis::atRight)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    //-----------------------------------------------------------------
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 6);
    ui->plot_LB4->replot();
    //-----------------------------------------------------------------

}
//=================================================

//=================================================
void timingprofile::setupPlot_LB5(void){

    //-----------------------------------------------------------------
    // configure axis rect:
    ui->plot_LB5->plotLayout()->clear(); // clear default axis rect so we can start from scratch
    QCPAxisRect *wideAxisRect = new QCPAxisRect(ui->plot_LB5);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers
    //-----------------------------------------------------------------

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    ui->plot_LB5->plotLayout()->addElement(0, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
    //-----------------------------------------------------------------
    QCPAxisRect *subRectTiming = new QCPAxisRect(ui->plot_LB5, false);
    subLayout->addElement(0, 0, subRectTiming);
    //-----------------------------------------------------------------
    subRectTiming->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    //-----------------------------------------------------------------
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot_LB5);
    subRectTiming->setMarginGroup(QCP::msBottom, marginGroup);
    wideAxisRect->setMarginGroup(QCP::msTop | QCP::msBottom | QCP::msRight | QCP::msLeft, marginGroup);
    //-----------------------------------------------------------------
    // move newly created axes on "axes" layer and grids on "grid" layer:

    foreach (QCPAxisRect *rect, ui->plot_LB5->axisRects())
    {
      foreach (QCPAxis *axis, rect->axes())
      {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
      }
    }

    //==================================================================
    // set dark background gradient:
    //==================================================================
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->plot_LB5->setBackground(QBrush(gradient));
    //==================================================================

    //==================================================================
    QVector <double> y1_timingHist (5000);
    //QVector <double> x1_BxNum (130);
    //==================================================================
    QCPBars *TimingHist = new QCPBars(subRectTiming->axis(QCPAxis::atBottom), subRectTiming->axis(QCPAxis::atLeft));

    TimingHist->setAntialiased(true); // gives more crisp, pixel aligned bar borders
    TimingHist->setStackingGap(1);
    TimingHist->setName("Timing Histogram ");
    TimingHist->setPen(QPen(QColor("#6050F8"),2));
    TimingHist->setBrush(QColor("#6050F8")); // 6050F8 BLUE
                                            // 8070B8 Violet
                                            // FFA100 Yellow
                                            // FF51FF  PINK
                                            // AAAAff Light Blue
   // QLegend *legend = TimingHist->legend();


    //==================================================================
    QVector<double> ticks (5000);
    QVector<QString> labels(5000);

    for (unsigned int j=BxCntVal+0 ; j< BxCntVal+129;j++){

            //ticks[j] = j+1 ;
            ticks[j] = j ;
            //labels[j] = QString("%1").arg(j+1);
            labels[j] = QString("%1").arg(j);

            y1_timingHist[j] = y0LB1_timingHist[j-BxCntVal];

    }

    unsigned int max_value = 0 ;

    for (unsigned int j=BxCntVal+0 ; j< BxCntVal+129;j++){

       if (y1_timingHist[j]>= max_value){
           max_value = y1_timingHist[j];
       }
    }

    //==================================================================

    TimingHist->setData(ticks,y1_timingHist);
    //-----------------------------------------------------------------
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    //-----------------------------------------------------------------
    subRectTiming->axis(QCPAxis::atBottom)->setTicker(textTicker);
    subRectTiming->axis(QCPAxis::atBottom)->setTickLabelRotation(90);
    subRectTiming->axis(QCPAxis::atBottom)->setLabel("Bunch Cross (#) \n Timing Profile LB2");
    subRectTiming->axis(QCPAxis::atBottom)->setSubTicks(false);
    subRectTiming->axis(QCPAxis::atBottom)->setTickLength(0, 4);
    subRectTiming->axis(QCPAxis::atBottom)->setRange(BxCntVal+0, BxCntVal +129); // notice: [BxCntVal+0, BxCntVal +129]
    subRectTiming->axis(QCPAxis::atBottom)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atBottom)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTiming->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atBottom)->setLabelColor(Qt::white);
    //-----------------------------------------------------------------

    subRectTiming->axis(QCPAxis::atTop)->setRange(BxCntVal+0, BxCntVal +129);
    subRectTiming->axis(QCPAxis::atTop)->setTickLength(0, 4);
    subRectTiming->axis(QCPAxis::atTop)->setSubTicks(true);
    subRectTiming->axis(QCPAxis::atTop)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->grid()->setVisible(true);
    subRectTiming->axis(QCPAxis::atTop)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTiming->axis(QCPAxis::atTop)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atTop)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atTop)->setLabel(" LB5 Timing Profile");
    //-----------------------------------------------------------------

    //-----------------------------------------------------------------
    // prepare y axis:
    subRectTiming->axis(QCPAxis::atLeft)->rescale(true);
    //subRectTiming->axis(QCPAxis::atLeft)->setRange(0, 5);
    subRectTiming->axis(QCPAxis::atLeft)->setPadding(1); // a bit more space to the left border
    subRectTiming->axis(QCPAxis::atLeft)->setLabel(" Total Hits ");
    subRectTiming->axis(QCPAxis::atLeft)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setSubGridVisible(true);
    subRectTiming->axis(QCPAxis::atLeft)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atLeft)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    //-----------------------------------------------------------------
    if (max_value == 0){
      subRectTiming->axis(QCPAxis::atRight)->setRange(-2.5, 2.5);
    }else{
        subRectTiming->axis(QCPAxis::atRight)->setRange(0, max_value);
    }

    //subRectTiming->axis(QCPAxis::atRight)->rescale(true);
    subRectTiming->axis(QCPAxis::atRight)->setPadding(1); // a bit more space to the left border
    subRectTiming->axis(QCPAxis::atRight)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->grid()->setSubGridVisible(true);
    subRectTiming->axis(QCPAxis::atRight)->setTickLabelColor(Qt::white);
    //subRectTiming->axis(QCPAxis::atRight)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atRight)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTiming->axis(QCPAxis::atRight)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    //-----------------------------------------------------------------
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 5);
    ui->plot_LB5->replot();
    //-----------------------------------------------------------------

}
//=================================================

//=================================================
void timingprofile::setupPlot_LB6(void){

    //-----------------------------------------------------------------
    // configure axis rect:
    ui->plot_LB6->plotLayout()->clear(); // clear default axis rect so we can start from scratch
    QCPAxisRect *wideAxisRect = new QCPAxisRect(ui->plot_LB6);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers
    //-----------------------------------------------------------------

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    ui->plot_LB6->plotLayout()->addElement(0, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
    //-----------------------------------------------------------------
    QCPAxisRect *subRectTiming = new QCPAxisRect(ui->plot_LB6, false);
    subLayout->addElement(0, 0, subRectTiming);
    //-----------------------------------------------------------------
    subRectTiming->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    //-----------------------------------------------------------------
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot_LB6);
    subRectTiming->setMarginGroup(QCP::msBottom, marginGroup);
    wideAxisRect->setMarginGroup(QCP::msTop | QCP::msBottom | QCP::msRight | QCP::msLeft, marginGroup);
    //-----------------------------------------------------------------
    // move newly created axes on "axes" layer and grids on "grid" layer:

    foreach (QCPAxisRect *rect, ui->plot_LB6->axisRects())
    {
      foreach (QCPAxis *axis, rect->axes())
      {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
      }
    }

    //==================================================================
    // set dark background gradient:
    //==================================================================
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->plot_LB6->setBackground(QBrush(gradient));
    //==================================================================

    //==================================================================
    QVector <double> y1_timingHist (5000);
    //QVector <double> x1_BxNum (130);
    //==================================================================
    QCPBars *TimingHist = new QCPBars(subRectTiming->axis(QCPAxis::atBottom), subRectTiming->axis(QCPAxis::atLeft));

    TimingHist->setAntialiased(true); // gives more crisp, pixel aligned bar borders
    TimingHist->setStackingGap(1);
    TimingHist->setName("Timing Histogram ");
    TimingHist->setPen(QPen(QColor("#6050F8"),2));
    TimingHist->setBrush(QColor("#6050F8")); // 6050F8 BLUE
                                            // 8070B8 Violet
                                            // FFA100 Yellow
                                            // FF51FF  PINK
                                            // AAAAff Light Blue
   // QLegend *legend = TimingHist->legend();


    //==================================================================
    QVector<double> ticks (5000);
    QVector<QString> labels(5000);

    for (unsigned int j=BxCntVal+0 ; j< BxCntVal+129;j++){

            //ticks[j] = j+1 ;
            ticks[j] = j ;
            //labels[j] = QString("%1").arg(j+1);
            labels[j] = QString("%1").arg(j);

            y1_timingHist[j] = y0LB1_timingHist[j-BxCntVal];

    }

    unsigned int max_value = 0 ;

    for (unsigned int j=BxCntVal+0 ; j< BxCntVal+129;j++){

       if (y1_timingHist[j]>= max_value){
           max_value = y1_timingHist[j];
       }
    }
    //==================================================================

    TimingHist->setData(ticks,y1_timingHist);
    //-----------------------------------------------------------------
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    //-----------------------------------------------------------------
    subRectTiming->axis(QCPAxis::atBottom)->setTicker(textTicker);
    subRectTiming->axis(QCPAxis::atBottom)->setTickLabelRotation(90);
    subRectTiming->axis(QCPAxis::atBottom)->setLabel("Bunch Cross (#) \n Timing Profile LB2");
    subRectTiming->axis(QCPAxis::atBottom)->setSubTicks(false);
    subRectTiming->axis(QCPAxis::atBottom)->setTickLength(0, 4);
    subRectTiming->axis(QCPAxis::atBottom)->setRange(BxCntVal+0, BxCntVal +129); // notice: [BxCntVal+0, BxCntVal +129]
    subRectTiming->axis(QCPAxis::atBottom)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atBottom)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTiming->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atBottom)->setLabelColor(Qt::white);
    //-----------------------------------------------------------------

    subRectTiming->axis(QCPAxis::atTop)->setRange(BxCntVal+0, BxCntVal +129);
    subRectTiming->axis(QCPAxis::atTop)->setTickLength(0, 4);
    subRectTiming->axis(QCPAxis::atTop)->setSubTicks(true);
    subRectTiming->axis(QCPAxis::atTop)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->grid()->setVisible(true);
    subRectTiming->axis(QCPAxis::atTop)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTiming->axis(QCPAxis::atTop)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atTop)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atTop)->setLabel(" LB6 Timing Profile");
    //-----------------------------------------------------------------

    //-----------------------------------------------------------------
    // prepare y axis:
    subRectTiming->axis(QCPAxis::atLeft)->rescale(true);
    //subRectTiming->axis(QCPAxis::atLeft)->setRange(0, 5);
    subRectTiming->axis(QCPAxis::atLeft)->setPadding(1); // a bit more space to the left border
    subRectTiming->axis(QCPAxis::atLeft)->setLabel(" Total Hits ");
    subRectTiming->axis(QCPAxis::atLeft)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setSubGridVisible(true);
    subRectTiming->axis(QCPAxis::atLeft)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atLeft)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    //-----------------------------------------------------------------
    if (max_value == 0){
      subRectTiming->axis(QCPAxis::atRight)->setRange(-2.5, 2.5);
    }else{
        subRectTiming->axis(QCPAxis::atRight)->setRange(0, max_value);
    }
    //subRectTiming->axis(QCPAxis::atRight)->rescale(true);
    subRectTiming->axis(QCPAxis::atRight)->setPadding(1); // a bit more space to the left border
    subRectTiming->axis(QCPAxis::atRight)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->grid()->setSubGridVisible(true);
    subRectTiming->axis(QCPAxis::atRight)->setTickLabelColor(Qt::white);
    //subRectTiming->axis(QCPAxis::atRight)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atRight)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTiming->axis(QCPAxis::atRight)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    //-----------------------------------------------------------------
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 4);
    ui->plot_LB6->replot();
    //-----------------------------------------------------------------
}
//=================================================

//=================================================
void timingprofile::setupPlot_LB7(void){

    //-----------------------------------------------------------------
    // configure axis rect:
    ui->plot_LB7->plotLayout()->clear(); // clear default axis rect so we can start from scratch
    QCPAxisRect *wideAxisRect = new QCPAxisRect(ui->plot_LB7);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers
    //-----------------------------------------------------------------

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    ui->plot_LB7->plotLayout()->addElement(0, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
    //-----------------------------------------------------------------
    QCPAxisRect *subRectTiming = new QCPAxisRect(ui->plot_LB7, false);
    subLayout->addElement(0, 0, subRectTiming);
    //-----------------------------------------------------------------
    subRectTiming->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    //-----------------------------------------------------------------
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot_LB7);
    subRectTiming->setMarginGroup(QCP::msBottom, marginGroup);
    wideAxisRect->setMarginGroup(QCP::msTop | QCP::msBottom | QCP::msRight | QCP::msLeft, marginGroup);
    //-----------------------------------------------------------------
    // move newly created axes on "axes" layer and grids on "grid" layer:

    foreach (QCPAxisRect *rect, ui->plot_LB7->axisRects())
    {
      foreach (QCPAxis *axis, rect->axes())
      {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
      }
    }

    //==================================================================
    // set dark background gradient:
    //==================================================================
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->plot_LB7->setBackground(QBrush(gradient));
    //==================================================================

    //==================================================================
    QVector <double> y1_timingHist (5000);
    //QVector <double> x1_BxNum (130);
    //==================================================================
    QCPBars *TimingHist = new QCPBars(subRectTiming->axis(QCPAxis::atBottom), subRectTiming->axis(QCPAxis::atLeft));

    TimingHist->setAntialiased(true); // gives more crisp, pixel aligned bar borders
    TimingHist->setStackingGap(1);
    TimingHist->setName("Timing Histogram ");
    TimingHist->setPen(QPen(QColor("#6050F8"),2));
    TimingHist->setBrush(QColor("#6050F8")); // 6050F8 BLUE
                                            // 8070B8 Violet
                                            // FFA100 Yellow
                                            // FF51FF  PINK
                                            // AAAAff Light Blue
   // QLegend *legend = TimingHist->legend();


    //==================================================================
    QVector<double> ticks (5000);
    QVector<QString> labels(5000);

    for (unsigned int j=BxCntVal+0 ; j< BxCntVal+129;j++){

            //ticks[j] = j+1 ;
            ticks[j] = j ;
            //labels[j] = QString("%1").arg(j+1);
            labels[j] = QString("%1").arg(j);

            y1_timingHist[j] = y0LB1_timingHist[j-BxCntVal];

    }

    unsigned int max_value = 0 ;

    for (unsigned int j=BxCntVal+0 ; j< BxCntVal+129;j++){

       if (y1_timingHist[j]>= max_value){
           max_value = y1_timingHist[j];
       }
    }
    //==================================================================

    TimingHist->setData(ticks,y1_timingHist);
    //-----------------------------------------------------------------
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    //-----------------------------------------------------------------
    subRectTiming->axis(QCPAxis::atBottom)->setTicker(textTicker);
    subRectTiming->axis(QCPAxis::atBottom)->setTickLabelRotation(90);
    subRectTiming->axis(QCPAxis::atBottom)->setLabel("Bunch Cross (#) \n Timing Profile LB2");
    subRectTiming->axis(QCPAxis::atBottom)->setSubTicks(false);
    subRectTiming->axis(QCPAxis::atBottom)->setTickLength(0, 4);
    subRectTiming->axis(QCPAxis::atBottom)->setRange(BxCntVal+0, BxCntVal +129); // notice: [BxCntVal+0, BxCntVal +129]
    subRectTiming->axis(QCPAxis::atBottom)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atBottom)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTiming->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atBottom)->setLabelColor(Qt::white);
    //-----------------------------------------------------------------

    subRectTiming->axis(QCPAxis::atTop)->setRange(BxCntVal+0, BxCntVal +129);
    subRectTiming->axis(QCPAxis::atTop)->setTickLength(0, 4);
    subRectTiming->axis(QCPAxis::atTop)->setSubTicks(true);
    subRectTiming->axis(QCPAxis::atTop)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->grid()->setVisible(true);
    subRectTiming->axis(QCPAxis::atTop)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTiming->axis(QCPAxis::atTop)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atTop)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atTop)->setLabel(" LB7 Timing Profile");
    //-----------------------------------------------------------------

    //-----------------------------------------------------------------
    // prepare y axis:
    subRectTiming->axis(QCPAxis::atLeft)->rescale(true);
    //subRectTiming->axis(QCPAxis::atLeft)->setRange(0, 5);
    subRectTiming->axis(QCPAxis::atLeft)->setPadding(1); // a bit more space to the left border
    subRectTiming->axis(QCPAxis::atLeft)->setLabel(" Total Hits ");
    subRectTiming->axis(QCPAxis::atLeft)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setSubGridVisible(true);
    subRectTiming->axis(QCPAxis::atLeft)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atLeft)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    //-----------------------------------------------------------------
    if (max_value == 0){
      subRectTiming->axis(QCPAxis::atRight)->setRange(-2.5, 2.5);
    }else{
        subRectTiming->axis(QCPAxis::atRight)->setRange(0, max_value);
    }
    //subRectTiming->axis(QCPAxis::atRight)->rescale(true);
    subRectTiming->axis(QCPAxis::atRight)->setPadding(1); // a bit more space to the left border
    subRectTiming->axis(QCPAxis::atRight)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->grid()->setSubGridVisible(true);
    subRectTiming->axis(QCPAxis::atRight)->setTickLabelColor(Qt::white);
    //subRectTiming->axis(QCPAxis::atRight)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atRight)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTiming->axis(QCPAxis::atRight)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    //-----------------------------------------------------------------
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 3);
    ui->plot_LB7->replot();
    //-----------------------------------------------------------------
}
//=================================================

//=================================================
void timingprofile::setupPlot_LB8(void){

    //-----------------------------------------------------------------
    // configure axis rect:
    ui->plot_LB8->plotLayout()->clear(); // clear default axis rect so we can start from scratch
    QCPAxisRect *wideAxisRect = new QCPAxisRect(ui->plot_LB8);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers
    //-----------------------------------------------------------------

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    ui->plot_LB8->plotLayout()->addElement(0, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
    //-----------------------------------------------------------------
    QCPAxisRect *subRectTiming = new QCPAxisRect(ui->plot_LB8, false);
    subLayout->addElement(0, 0, subRectTiming);
    //-----------------------------------------------------------------
    subRectTiming->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    //-----------------------------------------------------------------
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot_LB8);
    subRectTiming->setMarginGroup(QCP::msBottom, marginGroup);
    wideAxisRect->setMarginGroup(QCP::msTop | QCP::msBottom | QCP::msRight | QCP::msLeft, marginGroup);
    //-----------------------------------------------------------------
    // move newly created axes on "axes" layer and grids on "grid" layer:

    foreach (QCPAxisRect *rect, ui->plot_LB8->axisRects())
    {
      foreach (QCPAxis *axis, rect->axes())
      {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
      }
    }

    //==================================================================
    // set dark background gradient:
    //==================================================================
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->plot_LB8->setBackground(QBrush(gradient));
    //==================================================================

    //==================================================================
    QVector <double> y1_timingHist (5000);
    //QVector <double> x1_BxNum (130);
    //==================================================================
    QCPBars *TimingHist = new QCPBars(subRectTiming->axis(QCPAxis::atBottom), subRectTiming->axis(QCPAxis::atLeft));

    TimingHist->setAntialiased(true); // gives more crisp, pixel aligned bar borders
    TimingHist->setStackingGap(1);
    TimingHist->setName("Timing Histogram ");
    TimingHist->setPen(QPen(QColor("#6050F8"),2));
    TimingHist->setBrush(QColor("#6050F8")); // 6050F8 BLUE
                                            // 8070B8 Violet
                                            // FFA100 Yellow
                                            // FF51FF  PINK
                                            // AAAAff Light Blue
   // QLegend *legend = TimingHist->legend();


    //==================================================================
    QVector<double> ticks (5000);
    QVector<QString> labels(5000);

    for (unsigned int j=BxCntVal+0 ; j< BxCntVal+129;j++){

            //ticks[j] = j+1 ;
            ticks[j] = j ;
            //labels[j] = QString("%1").arg(j+1);
            labels[j] = QString("%1").arg(j);

            y1_timingHist[j] = y0LB1_timingHist[j-BxCntVal];

    }

    unsigned int max_value = 0 ;

    for (unsigned int j=BxCntVal+0 ; j< BxCntVal+129;j++){

       if (y1_timingHist[j]>= max_value){
           max_value = y1_timingHist[j];
       }
    }
    //==================================================================

    TimingHist->setData(ticks,y1_timingHist);
    //-----------------------------------------------------------------
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    //-----------------------------------------------------------------
    subRectTiming->axis(QCPAxis::atBottom)->setTicker(textTicker);
    subRectTiming->axis(QCPAxis::atBottom)->setTickLabelRotation(90);
    subRectTiming->axis(QCPAxis::atBottom)->setLabel("Bunch Cross (#) \n Timing Profile LB2");
    subRectTiming->axis(QCPAxis::atBottom)->setSubTicks(false);
    subRectTiming->axis(QCPAxis::atBottom)->setTickLength(0, 4);
    subRectTiming->axis(QCPAxis::atBottom)->setRange(BxCntVal+0, BxCntVal +129); // notice: [BxCntVal+0, BxCntVal +129]
    subRectTiming->axis(QCPAxis::atBottom)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atBottom)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTiming->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atBottom)->setLabelColor(Qt::white);
    //-----------------------------------------------------------------

    subRectTiming->axis(QCPAxis::atTop)->setRange(BxCntVal+0, BxCntVal +129);
    subRectTiming->axis(QCPAxis::atTop)->setTickLength(0, 4);
    subRectTiming->axis(QCPAxis::atTop)->setSubTicks(true);
    subRectTiming->axis(QCPAxis::atTop)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->grid()->setVisible(true);
    subRectTiming->axis(QCPAxis::atTop)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTiming->axis(QCPAxis::atTop)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atTop)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atTop)->setLabel(" LB8 Timing Profile");
    //-----------------------------------------------------------------

    //-----------------------------------------------------------------
    // prepare y axis:
    subRectTiming->axis(QCPAxis::atLeft)->rescale(true);
    //subRectTiming->axis(QCPAxis::atLeft)->setRange(0, 5);
    subRectTiming->axis(QCPAxis::atLeft)->setPadding(1); // a bit more space to the left border
    subRectTiming->axis(QCPAxis::atLeft)->setLabel(" Total Hits ");
    subRectTiming->axis(QCPAxis::atLeft)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setSubGridVisible(true);
    subRectTiming->axis(QCPAxis::atLeft)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atLeft)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    //-----------------------------------------------------------------
    if (max_value == 0){
      subRectTiming->axis(QCPAxis::atRight)->setRange(-2.5, 2.5);
    }else{
        subRectTiming->axis(QCPAxis::atRight)->setRange(0, max_value);
    }
    //subRectTiming->axis(QCPAxis::atRight)->rescale(true);
    subRectTiming->axis(QCPAxis::atRight)->setPadding(1); // a bit more space to the left border
    subRectTiming->axis(QCPAxis::atRight)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->grid()->setSubGridVisible(true);
    subRectTiming->axis(QCPAxis::atRight)->setTickLabelColor(Qt::white);
    //subRectTiming->axis(QCPAxis::atRight)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atRight)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTiming->axis(QCPAxis::atRight)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    //-----------------------------------------------------------------
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 3);
    ui->plot_LB8->replot();
    //-----------------------------------------------------------------

}
//=================================================

//=================================================
void timingprofile::setupPlot_LB9(void){

    //-----------------------------------------------------------------
    // configure axis rect:
    ui->plot_LB9->plotLayout()->clear(); // clear default axis rect so we can start from scratch
    QCPAxisRect *wideAxisRect = new QCPAxisRect(ui->plot_LB9);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers
    //-----------------------------------------------------------------

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    ui->plot_LB9->plotLayout()->addElement(0, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
    //-----------------------------------------------------------------
    QCPAxisRect *subRectTiming = new QCPAxisRect(ui->plot_LB9, false);
    subLayout->addElement(0, 0, subRectTiming);
    //-----------------------------------------------------------------
    subRectTiming->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    //-----------------------------------------------------------------
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot_LB9);
    subRectTiming->setMarginGroup(QCP::msBottom, marginGroup);
    wideAxisRect->setMarginGroup(QCP::msTop | QCP::msBottom | QCP::msRight | QCP::msLeft, marginGroup);
    //-----------------------------------------------------------------
    // move newly created axes on "axes" layer and grids on "grid" layer:

    foreach (QCPAxisRect *rect, ui->plot_LB9->axisRects())
    {
      foreach (QCPAxis *axis, rect->axes())
      {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
      }
    }

    //==================================================================
    // set dark background gradient:
    //==================================================================
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->plot_LB9->setBackground(QBrush(gradient));
    //==================================================================

    //==================================================================
    QVector <double> y1_timingHist (5000);
    //QVector <double> x1_BxNum (130);
    //==================================================================
    QCPBars *TimingHist = new QCPBars(subRectTiming->axis(QCPAxis::atBottom), subRectTiming->axis(QCPAxis::atLeft));

    TimingHist->setAntialiased(true); // gives more crisp, pixel aligned bar borders
    TimingHist->setStackingGap(1);
    TimingHist->setName("Timing Histogram ");
    TimingHist->setPen(QPen(QColor("#6050F8"),2));
    TimingHist->setBrush(QColor("#6050F8")); // 6050F8 BLUE
                                            // 8070B8 Violet
                                            // FFA100 Yellow
                                            // FF51FF  PINK
                                            // AAAAff Light Blue
   // QLegend *legend = TimingHist->legend();


    //==================================================================
    QVector<double> ticks (5000);
    QVector<QString> labels(5000);

    for (unsigned int j=BxCntVal+0 ; j< BxCntVal+129;j++){

            //ticks[j] = j+1 ;
            ticks[j] = j ;
            //labels[j] = QString("%1").arg(j+1);
            labels[j] = QString("%1").arg(j);

            y1_timingHist[j] = y0LB1_timingHist[j-BxCntVal];

    }

    unsigned int max_value = 0 ;

    for (unsigned int j=BxCntVal+0 ; j< BxCntVal+129;j++){

       if (y1_timingHist[j]>= max_value){
           max_value = y1_timingHist[j];
       }
    }
    //==================================================================

    TimingHist->setData(ticks,y1_timingHist);
    //-----------------------------------------------------------------
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    //-----------------------------------------------------------------
    subRectTiming->axis(QCPAxis::atBottom)->setTicker(textTicker);
    subRectTiming->axis(QCPAxis::atBottom)->setTickLabelRotation(90);
    subRectTiming->axis(QCPAxis::atBottom)->setLabel("Bunch Cross (#) \n Timing Profile LB2");
    subRectTiming->axis(QCPAxis::atBottom)->setSubTicks(false);
    subRectTiming->axis(QCPAxis::atBottom)->setTickLength(0, 4);
    subRectTiming->axis(QCPAxis::atBottom)->setRange(BxCntVal+0, BxCntVal +129); // notice: [BxCntVal+0, BxCntVal +129]
    subRectTiming->axis(QCPAxis::atBottom)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atBottom)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    subRectTiming->axis(QCPAxis::atBottom)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTiming->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atBottom)->setLabelColor(Qt::white);
    //-----------------------------------------------------------------

    subRectTiming->axis(QCPAxis::atTop)->setRange(BxCntVal+0, BxCntVal +129);
    subRectTiming->axis(QCPAxis::atTop)->setTickLength(0, 4);
    subRectTiming->axis(QCPAxis::atTop)->setSubTicks(true);
    subRectTiming->axis(QCPAxis::atTop)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atTop)->grid()->setVisible(true);
    subRectTiming->axis(QCPAxis::atTop)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRectTiming->axis(QCPAxis::atTop)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atTop)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atTop)->setLabel(" LB9 Timing Profile");
    //-----------------------------------------------------------------

    //-----------------------------------------------------------------
    // prepare y axis:
    subRectTiming->axis(QCPAxis::atLeft)->rescale(true);
    //subRectTiming->axis(QCPAxis::atLeft)->setRange(0, 5);
    subRectTiming->axis(QCPAxis::atLeft)->setPadding(1); // a bit more space to the left border
    subRectTiming->axis(QCPAxis::atLeft)->setLabel(" Total Hits ");
    subRectTiming->axis(QCPAxis::atLeft)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setSubGridVisible(true);
    subRectTiming->axis(QCPAxis::atLeft)->setTickLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atLeft)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTiming->axis(QCPAxis::atLeft)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    //-----------------------------------------------------------------
    if (max_value == 0){
      subRectTiming->axis(QCPAxis::atRight)->setRange(-2.5, 2.5);
    }else{
        subRectTiming->axis(QCPAxis::atRight)->setRange(0, max_value);
    }
    //subRectTiming->axis(QCPAxis::atRight)->rescale(true);
    subRectTiming->axis(QCPAxis::atRight)->setPadding(1); // a bit more space to the left border
    subRectTiming->axis(QCPAxis::atRight)->setBasePen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->setTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->setSubTickPen(QPen(Qt::white));
    subRectTiming->axis(QCPAxis::atRight)->grid()->setSubGridVisible(true);
    subRectTiming->axis(QCPAxis::atRight)->setTickLabelColor(Qt::white);
    //subRectTiming->axis(QCPAxis::atRight)->setLabelColor(Qt::white);
    subRectTiming->axis(QCPAxis::atRight)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRectTiming->axis(QCPAxis::atRight)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    //-----------------------------------------------------------------
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 2);
    ui->plot_LB9->replot();
    //-----------------------------------------------------------------
}
//=================================================
