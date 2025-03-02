#include "backendemu.h"
#include "ui_backendemu.h"
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


BackendEmu::BackendEmu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BackendEmu)
{
    ui->setupUi(this);

    //scrollArea->setBackgroundRole(QPalette::Dark);
    //scrollArea->setWidget(ui->BePlot);
    //scrollArea->setVisible(false);


    setupPlot_BeE();

    ui->horizontalScrollBar->setRange(-500, 500);
    ui->verticalScrollBar->setRange(-500, 500);

    connect(ui->horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int)));
    connect(ui->verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(vertScrollBarChanged(int)));

    connect(ui->BePlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));
    connect(ui->BePlot->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(yAxisChanged(QCPRange)));

    ui->BePlot->xAxis->setRange(0, 6, Qt::AlignCenter);
    ui->BePlot->yAxis->setRange(0, 10, Qt::AlignCenter);

}

BackendEmu::~BackendEmu()
{
    delete ui;
}


void BackendEmu::horzScrollBarChanged(int value)
{
  if (qAbs(ui->BePlot->xAxis->range().center()-value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
  {
    ui->BePlot->xAxis->setRange(value/100.0, ui->BePlot->xAxis->range().size(), Qt::AlignCenter);
    ui->BePlot->replot();
  }
}

void BackendEmu::vertScrollBarChanged(int value)
{
  if (qAbs(ui->BePlot->yAxis->range().center()+value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
  {
    ui->BePlot->yAxis->setRange(-value/100.0, ui->BePlot->yAxis->range().size(), Qt::AlignCenter);
    ui->BePlot->replot();
  }
}



void BackendEmu::xAxisChanged(QCPRange range)
{
  ui->horizontalScrollBar->setValue(qRound(range.center()*100.0)); // adjust position of scroll bar slider
  ui->horizontalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}

void BackendEmu::yAxisChanged(QCPRange range)
{
  ui->verticalScrollBar->setValue(qRound(-range.center()*100.0)); // adjust position of scroll bar slider
  ui->verticalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}


void BackendEmu::mouseWheel(QWheelEvent *e)
{

    /*
    ui->plot_CB->setInteractions( QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->plot_CB->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->plot_CB->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
    */
    QString result;
    const bool vertical = qAbs(e->angleDelta().y()) >= qAbs(e->angleDelta().x());
    const int delta = vertical ? e->angleDelta().y() : e->angleDelta().x();

    if (delta > 0) {
        if (vertical) {
            result = "Mouse Wheel Event: UP";
            counter++;
            ui->BePlot->axisRect()->setRangeZoom(Qt::Vertical);
            //ui->plot_CB->xAxis->setRange(qAbs(e->position().x()),qAbs(e->position().x()));
            //ui->plot_CB->yAxis->setRange(0,counter);
        } else {
            result = "Mouse Wheel Event: LEFT";
        }
    } else if (delta < 0) {
        if (vertical) {
            result = "Mouse Wheel Event: DOWN";
            counter--;
            ui->BePlot->axisRect()->setRangeZoom(Qt::Vertical);
            //ui->plot_CB->xAxis->setRange(qAbs(e->position().x())+counter,qAbs(e->position().x())+counter);
            //ui->plot_CB->yAxis->setRange(0,counter);
        } else {
            result = "Mouse Wheel Event: RIGHT";
        }
    }
    qDebug() << result;

}

void BackendEmu::mousePress()
{
    // if an axis is selected, only allow the direction of that axis to be dragged
    // if no axis is selected, both directions may be dragged

    if (ui->BePlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
      ui->BePlot->axisRect()->setRangeDrag(ui->BePlot->xAxis->orientation());
    else if (ui->BePlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
      ui->BePlot->axisRect()->setRangeDrag(ui->BePlot->yAxis->orientation());
    else
      ui->BePlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}






void BackendEmu::setupPlot_BeE(void){

    ui->BePlot->plotLayout()->clear();



    QCPLayoutGrid *mainLayout = new QCPLayoutGrid;
    ui->BePlot->plotLayout()->addElement( 0 , 0 , mainLayout);

    QCPAxisRect *subRect1 = new QCPAxisRect(ui->BePlot, true); // false means to not setup default axes
    QCPAxisRect *subRect2 = new QCPAxisRect(ui->BePlot, true);
    QCPAxisRect *subRect3 = new QCPAxisRect(ui->BePlot, true);
    QCPAxisRect *subRect4 = new QCPAxisRect(ui->BePlot, true);
    QCPAxisRect *subRect5 = new QCPAxisRect(ui->BePlot, true);
    QCPAxisRect *subRect6 = new QCPAxisRect(ui->BePlot, true);
    QCPAxisRect *subRect7 = new QCPAxisRect(ui->BePlot, true);
    QCPAxisRect *subRect8 = new QCPAxisRect(ui->BePlot, true);
    QCPAxisRect *subRect9 = new QCPAxisRect(ui->BePlot, true);
    QCPAxisRect *subRect10 = new QCPAxisRect(ui->BePlot, true);

    QCPAxisRect *subRect11 = new QCPAxisRect(ui->BePlot, true); // true means to not setup default axes
    QCPAxisRect *subRect12 = new QCPAxisRect(ui->BePlot, true);

    QCPAxisRect *subRect13  = new QCPAxisRect(ui->BePlot, true);
    QCPAxisRect *subRect14  = new QCPAxisRect(ui->BePlot, true);
    QCPAxisRect *subRect15  = new QCPAxisRect(ui->BePlot, true);
    QCPAxisRect *subRect16  = new QCPAxisRect(ui->BePlot, true);
    QCPAxisRect *subRect17  = new QCPAxisRect(ui->BePlot, true);
    QCPAxisRect *subRect18  = new QCPAxisRect(ui->BePlot, true);
    QCPAxisRect *subRect19  = new QCPAxisRect(ui->BePlot, true);
    QCPAxisRect *subRect20  = new QCPAxisRect(ui->BePlot, true);
    QCPAxisRect *subRect21  = new QCPAxisRect(ui->BePlot, true);
    QCPAxisRect *subRect22  = new QCPAxisRect(ui->BePlot, true);




    mainLayout->addElement(0, 0, subRect1);
    mainLayout->setRowStretchFactor(0, 1);

    mainLayout->addElement(1, 0, subRect2);
    mainLayout->setRowStretchFactor(1, 2);

    mainLayout->addElement(2, 0, subRect3);
    mainLayout->setRowStretchFactor(2, 3);

    mainLayout->addElement(3, 0, subRect4);
    mainLayout->setRowStretchFactor(3, 1);

    mainLayout->addElement(4, 0, subRect5);
    mainLayout->setRowStretchFactor(4, 10);

    mainLayout->addElement(5, 0, subRect6);
    mainLayout->setRowStretchFactor(5, 1);

    mainLayout->addElement(6, 0, subRect7);
    mainLayout->setRowStretchFactor(6, 1);

    mainLayout->addElement(7, 0, subRect8);
    mainLayout->setRowStretchFactor(7, 1);

    mainLayout->addElement(8, 0, subRect9);
    mainLayout->setRowStretchFactor(8, 1);

    mainLayout->addElement(9, 0, subRect10);
    mainLayout->setRowStretchFactor(9, 10);

    mainLayout->addElement(10, 0, subRect11);
    mainLayout->addElement(11, 0, subRect12);


    mainLayout->addElement( 12, 0, subRect13 );
    mainLayout->addElement( 13, 0, subRect14 );
    mainLayout->addElement( 14, 0, subRect15 );
    mainLayout->addElement( 15, 0, subRect16 );
    mainLayout->addElement( 16, 0, subRect17 );
    mainLayout->addElement( 17, 0, subRect18 );

    mainLayout->addElement( 18, 0, subRect19 );
    mainLayout->addElement( 19, 0, subRect20 );
    mainLayout->addElement( 20, 0, subRect21 );
    mainLayout->addElement( 21, 0, subRect22 );





    ui->BePlot->axisRect()->setupFullAxesBox(true);
    ui->BePlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    subRect1->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    //subRect1->axis(QCPAxis::atBottom)->ticker()->setTickCount(2);
    subRect1->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    subRect1->axis(QCPAxis::atLeft)->rescale(true);
    subRect1->axis(QCPAxis::atRight)->rescale(true);

    subRect2->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect2->axis(QCPAxis::atBottom)->grid()->setVisible(true);


    subRect3->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect3->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect4->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect4->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect5->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect5->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect6->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect6->axis(QCPAxis::atBottom)->grid()->setVisible(true);


    subRect7->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect7->axis(QCPAxis::atBottom)->grid()->setVisible(true);


    subRect8->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect8->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect9->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect9->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect10->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect10->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect11->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect11->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect12->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect12->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect13 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect13 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect14 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect14 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect15 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect15 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect16 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect16 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect17 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect17 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect18 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect18 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect19 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect19 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect20 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect20 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect21 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect21 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);



    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->BePlot);


    subRect1->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect2->setMarginGroup(QCP::msBottom| QCP::msLeft|QCP::msRight, marginGroup);
    subRect3->setMarginGroup(QCP::msBottom| QCP::msLeft|QCP::msRight, marginGroup);
    subRect4->setMarginGroup(QCP::msBottom| QCP::msLeft|QCP::msRight, marginGroup);
    subRect5->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect6->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect7->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect8->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect9->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect10->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect11->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect12->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect13  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect14  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect15  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect16  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect17  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect18  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect19  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect20  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect21  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);


    foreach (QCPAxisRect *rect, ui->BePlot->axisRects())
    {
      foreach (QCPAxis *axis, rect->axes())
      {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
        axis->scaleRange(1);
      }
    }

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    ui->BePlot->plotLayout()->addElement(0,0,subLayout);

    subLayout->setRowStretchFactor(0, 3); // left axis rect shall have 60% of width
    subLayout->setRowStretchFactor(1, 2); // right one only 40% (3:2 = 60:40)

    //==================================================================
    // set dark background gradient:
    //==================================================================
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->BePlot->setBackground(QBrush(gradient));
    //==================================================================
    //
    //==================================================================


    QCPBars *stripN = new QCPBars (subRect1->axis(QCPAxis::atBottom ),
                                     subRect1->axis(QCPAxis::atLeft));


    stripN->setAntialiased(true); // gives more crisp, pixel aligned bar borders
    stripN->setStackingGap(1);
    //stripN->setName("MultiChannel Histogram - Adjustable Window ");
    stripN->setPen(QPen(QColor(0, 168, 140).lighter(130)));
    stripN->setBrush(QColor(0, 168, 140));


    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    //textTicker->addTicks(ticks, labels);
    subRect1->axis(QCPAxis::atBottom)->setTicker(textTicker);

    subRect1->setRangeZoom(Qt::Vertical);
    subRect1->rangeZoom();


    subRect1->axis(QCPAxis::atBottom)->setTickLabelRotation(90);
    subRect1->axis(QCPAxis::atBottom)->setLabel(" Bunch Crossing Number "); // RPC Channel xx
    subRect1->axis(QCPAxis::atBottom)->setSubTicks(true);
    subRect1->axis(QCPAxis::atBottom)->setTickLength(0, 2);
    subRect1->axis(QCPAxis::atBottom)->setRange(0, 129);
    subRect1->axis(QCPAxis::atBottom)->setBasePen(QPen(Qt::white));
    subRect1->axis(QCPAxis::atBottom)->setTickPen(QPen(Qt::white));
    subRect1->axis(QCPAxis::atBottom)->setSubTickPen(QPen(Qt::white));
    subRect1->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    subRect1->axis(QCPAxis::atBottom)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRect1->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::white);
    subRect1->axis(QCPAxis::atBottom)->setLabelColor(Qt::white);
    subRect1->axis(QCPAxis::atBottom)->selectableParts().setFlag(QCPAxis::spAxis);
    subRect1->axis(QCPAxis::atBottom)->setPadding(6); // a bit more space to the left border


    subRect1->axis(QCPAxis::atTop)->setRange(0, 129);
    subRect1->axis(QCPAxis::atTop)->setTickLength(false, 2);
    //subRect1->axis(QCPAxis::atTop)->setLabel(stripNum); // RPC Channel xx
    subRect1->axis(QCPAxis::atTop)->setSubTicks(false);
    subRect1->axis(QCPAxis::atTop)->setBasePen(QPen(Qt::white));
    subRect1->axis(QCPAxis::atTop)->setTickPen(QPen(Qt::white));
    subRect1->axis(QCPAxis::atTop)->setSubTickPen(QPen(Qt::white));
    subRect1->axis(QCPAxis::atTop)->grid()->setVisible(true);
    subRect1->axis(QCPAxis::atTop)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRect1->axis(QCPAxis::atTop)->setTickLabelColor(Qt::white);
    subRect1->axis(QCPAxis::atTop)->setLabelColor(Qt::white);
    subRect1->axis(QCPAxis::atTop)->selectableParts().setFlag(QCPAxis::spAxis);
    subRect1->axis(QCPAxis::atTop)->setPadding(6); // a bit more space to the left border

    // prepare y axis:
    subRect1->axis(QCPAxis::atLeft)->setRange(0, 20);
    subRect1->axis(QCPAxis::atLeft)->setRangeUpper (20);
    subRect1->axis(QCPAxis::atLeft)->setPadding(6); // a bit more space to the left border
    subRect1->axis(QCPAxis::atLeft)->setLabel(" Sub-BX "); // Vertical Text
    subRect1->axis(QCPAxis::atLeft)->setBasePen(QPen(Qt::white));
    subRect1->axis(QCPAxis::atLeft)->setTickPen(QPen(Qt::white));
    subRect1->axis(QCPAxis::atLeft)->setSubTickPen(QPen(Qt::white));
    subRect1->axis(QCPAxis::atLeft)->grid()->setSubGridVisible(true);
    subRect1->axis(QCPAxis::atLeft)->setTickLabelColor(Qt::white);
    subRect1->axis(QCPAxis::atLeft)->setLabelColor(Qt::white);
    subRect1->axis(QCPAxis::atLeft)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRect1->axis(QCPAxis::atLeft)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRect1->axis(QCPAxis::atLeft)->selectableParts().setFlag(QCPAxis::spAxis);

    subRect1->axis(QCPAxis::atRight)->setRange(0, 20);
    subRect1->axis(QCPAxis::atLeft)->setRangeUpper (20);
    subRect1->axis(QCPAxis::atRight)->setPadding(6); // a bit more space to the left border
    subRect1->axis(QCPAxis::atRight)->setBasePen(QPen(Qt::white));
    subRect1->axis(QCPAxis::atRight)->setTickPen(QPen(Qt::white));
    subRect1->axis(QCPAxis::atRight)->setSubTickPen(QPen(Qt::white));
    subRect1->axis(QCPAxis::atRight)->grid()->setSubGridVisible(true);
    subRect1->axis(QCPAxis::atRight)->setTickLabelColor(Qt::white);
    //subRect1->axis(QCPAxis::atRight)->setLabelColor(Qt::white);
    subRect1->axis(QCPAxis::atRight)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    subRect1->axis(QCPAxis::atRight)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRect1->axis(QCPAxis::atRight)->selectableParts().setFlag(QCPAxis::spAxis);

}





