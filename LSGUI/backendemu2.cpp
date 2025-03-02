#include "backendemu2.h"
#include "ui_backendemu2.h"
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

//======================================================================================
//
//======================================================================================
BackendEmu2::BackendEmu2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BackendEmu2)
{
    //unsigned int (*y0_StripData)[200];

    ui->setupUi(this);


    BeSetupPlot();

    ui->horizontalScrollBar->setRange(-500, 500);
    ui->verticalScrollBar->setRange(-500, 500);

    connect(ui->horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int)));
    connect(ui->verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(vertScrollBarChanged(int)));

    connect(ui->BePlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));
    connect(ui->BePlot->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(yAxisChanged(QCPRange)));

    //ui->BePlot->xAxis->setRange(0, 6, Qt::AlignCenter);
    //ui->BePlot->yAxis->setRange(0, 10, Qt::AlignCenter);

    //BePlotter(y0_StripData, 1);

}

BackendEmu2::~BackendEmu2()
{
    delete ui;
}

//======================================================================================
//
//======================================================================================



void BackendEmu2::horzScrollBarChanged(int value)
{
  if (qAbs(ui->BePlot->xAxis->range().center()-value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
  {
    ui->BePlot->xAxis->setRange(value/100.0, ui->BePlot->xAxis->range().size(), Qt::AlignCenter);
    ui->BePlot->replot();
  }
}

//======================================================================================
//
//======================================================================================

void BackendEmu2::vertScrollBarChanged(int value)
{
  if (qAbs(ui->BePlot->yAxis->range().center()+value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
  {
    ui->BePlot->yAxis->setRange(-value/100.0, ui->BePlot->yAxis->range().size(), Qt::AlignCenter);
    ui->BePlot->replot();
  }
}


//======================================================================================
//
//======================================================================================


void BackendEmu2::xAxisChanged(QCPRange range)
{
  ui->horizontalScrollBar->setValue(qRound(range.center()*100.0)); // adjust position of scroll bar slider
  ui->horizontalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}

//======================================================================================
//
//======================================================================================

void BackendEmu2::yAxisChanged(QCPRange range)
{
  ui->verticalScrollBar->setValue(qRound(-range.center()*100.0)); // adjust position of scroll bar slider
  ui->verticalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}

//======================================================================================
//
//======================================================================================


void BackendEmu2::mouseWheel(QWheelEvent *e)
{

    /*
    ui->BePlot->setInteractions( QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->BePlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->BePlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
    */
    QString result;
    const bool vertical = qAbs(e->angleDelta().y()) >= qAbs(e->angleDelta().x());
    const int delta = vertical ? e->angleDelta().y() : e->angleDelta().x();

    if (delta > 0) {
        if (vertical) {
            result = "Mouse Wheel Event: UP";
            counter++;
            ui->BePlot->axisRect()->setRangeZoom(Qt::Vertical);
            //ui->BePlot->xAxis->setRange(qAbs(e->position().x()),qAbs(e->position().x()));
            //ui->BePlot->yAxis->setRange(0,counter);
        } else {
            result = "Mouse Wheel Event: LEFT";
        }
    } else if (delta < 0) {
        if (vertical) {
            result = "Mouse Wheel Event: DOWN";
            counter--;
            ui->BePlot->axisRect()->setRangeZoom(Qt::Vertical);
            //ui->BePlot->xAxis->setRange(qAbs(e->position().x())+counter,qAbs(e->position().x())+counter);
            //ui->BePlot->yAxis->setRange(0,counter);
        } else {
            result = "Mouse Wheel Event: RIGHT";
        }
    }
    qDebug() << result;

}


//======================================================================================
//
//======================================================================================

void BackendEmu2::mousePress()
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



//======================================================================================
//
//======================================================================================
void BackendEmu2::BeSetupPlot(void){

    ui->BePlot->plotLayout()->clear();

    QCPLayoutGrid *mainLayout = new QCPLayoutGrid;
    ui->BePlot->plotLayout()->addElement( 0 , 0 , mainLayout);

    subRect1= new QCPAxisRect(ui->BePlot, true); // false means to not setup default axes
    subRect2 = new QCPAxisRect(ui->BePlot, true);
    subRect3 = new QCPAxisRect(ui->BePlot, true);
    subRect4 = new QCPAxisRect(ui->BePlot, true);
    subRect5 = new QCPAxisRect(ui->BePlot, true);
    subRect6 = new QCPAxisRect(ui->BePlot, true);
    subRect7 = new QCPAxisRect(ui->BePlot, true);
    subRect8 = new QCPAxisRect(ui->BePlot, true);
    subRect9 = new QCPAxisRect(ui->BePlot, true);
    subRect10 = new QCPAxisRect(ui->BePlot, true);
    subRect11 = new QCPAxisRect(ui->BePlot, true); // true means to not setup default axes
    subRect12 = new QCPAxisRect(ui->BePlot, true);

    subRect13  = new QCPAxisRect(ui->BePlot, true);
    subRect14  = new QCPAxisRect(ui->BePlot, true);
    subRect15  = new QCPAxisRect(ui->BePlot, true);
    subRect16  = new QCPAxisRect(ui->BePlot, true);
    subRect17  = new QCPAxisRect(ui->BePlot, true);
    subRect18  = new QCPAxisRect(ui->BePlot, true);
    subRect19  = new QCPAxisRect(ui->BePlot, true);
    subRect20  = new QCPAxisRect(ui->BePlot, true);
    subRect21  = new QCPAxisRect(ui->BePlot, true);
    subRect22  = new QCPAxisRect(ui->BePlot, true);

    subRect23  = new QCPAxisRect(ui->BePlot, true);
    subRect24  = new QCPAxisRect(ui->BePlot, true);
    subRect25  = new QCPAxisRect(ui->BePlot, true);
    subRect26  = new QCPAxisRect(ui->BePlot, true);
    subRect27  = new QCPAxisRect(ui->BePlot, true);
    subRect28  = new QCPAxisRect(ui->BePlot, true);
    subRect29  = new QCPAxisRect(ui->BePlot, true);
    subRect30  = new QCPAxisRect(ui->BePlot, true);
    subRect31  = new QCPAxisRect(ui->BePlot, true);
    subRect32  = new QCPAxisRect(ui->BePlot, true);
    subRect33  = new QCPAxisRect(ui->BePlot, true);
    subRect34  = new QCPAxisRect(ui->BePlot, true);
    subRect35  = new QCPAxisRect(ui->BePlot, true);
    subRect36  = new QCPAxisRect(ui->BePlot, true);
    subRect37  = new QCPAxisRect(ui->BePlot, true);
    subRect38  = new QCPAxisRect(ui->BePlot, true);
    subRect39  = new QCPAxisRect(ui->BePlot, true);
    subRect40  = new QCPAxisRect(ui->BePlot, true);
    subRect41  = new QCPAxisRect(ui->BePlot, true);
    subRect42  = new QCPAxisRect(ui->BePlot, true);
    subRect43  = new QCPAxisRect(ui->BePlot, true);
    subRect44  = new QCPAxisRect(ui->BePlot, true);
    subRect45  = new QCPAxisRect(ui->BePlot, true);
    subRect46  = new QCPAxisRect(ui->BePlot, true);
    subRect47  = new QCPAxisRect(ui->BePlot, true);
    subRect48  = new QCPAxisRect(ui->BePlot, true);
    subRect49  = new QCPAxisRect(ui->BePlot, true);
    subRect50  = new QCPAxisRect(ui->BePlot, true);
    subRect51  = new QCPAxisRect(ui->BePlot, true);
    subRect52  = new QCPAxisRect(ui->BePlot, true);
    subRect53  = new QCPAxisRect(ui->BePlot, true);
    subRect54  = new QCPAxisRect(ui->BePlot, true);
    subRect55  = new QCPAxisRect(ui->BePlot, true);
    subRect56  = new QCPAxisRect(ui->BePlot, true);
    subRect57  = new QCPAxisRect(ui->BePlot, true);
    subRect58  = new QCPAxisRect(ui->BePlot, true);
    subRect59  = new QCPAxisRect(ui->BePlot, true);
    subRect60  = new QCPAxisRect(ui->BePlot, true);
    subRect61  = new QCPAxisRect(ui->BePlot, true);
    subRect62  = new QCPAxisRect(ui->BePlot, true);
    subRect63  = new QCPAxisRect(ui->BePlot, true);
    subRect64  = new QCPAxisRect(ui->BePlot, true);
    subRect65  = new QCPAxisRect(ui->BePlot, true);
    subRect66  = new QCPAxisRect(ui->BePlot, true);
    subRect67  = new QCPAxisRect(ui->BePlot, true);
    subRect68  = new QCPAxisRect(ui->BePlot, true);
    subRect69  = new QCPAxisRect(ui->BePlot, true);
    subRect70  = new QCPAxisRect(ui->BePlot, true);
    subRect71  = new QCPAxisRect(ui->BePlot, true);
    subRect72  = new QCPAxisRect(ui->BePlot, true);
    subRect73  = new QCPAxisRect(ui->BePlot, true);
    subRect74  = new QCPAxisRect(ui->BePlot, true);
    subRect75  = new QCPAxisRect(ui->BePlot, true);
    subRect76  = new QCPAxisRect(ui->BePlot, true);
    subRect77  = new QCPAxisRect(ui->BePlot, true);
    subRect78  = new QCPAxisRect(ui->BePlot, true);
    subRect79  = new QCPAxisRect(ui->BePlot, true);
    subRect80  = new QCPAxisRect(ui->BePlot, true);
    subRect81  = new QCPAxisRect(ui->BePlot, true);
    subRect82  = new QCPAxisRect(ui->BePlot, true);
    subRect83  = new QCPAxisRect(ui->BePlot, true);
    subRect84  = new QCPAxisRect(ui->BePlot, true);
    subRect85  = new QCPAxisRect(ui->BePlot, true);
    subRect86  = new QCPAxisRect(ui->BePlot, true);
    subRect87  = new QCPAxisRect(ui->BePlot, true);
    subRect88  = new QCPAxisRect(ui->BePlot, true);
    subRect89  = new QCPAxisRect(ui->BePlot, true);
    subRect90  = new QCPAxisRect(ui->BePlot, true);
    subRect91  = new QCPAxisRect(ui->BePlot, true);
    subRect92  = new QCPAxisRect(ui->BePlot, true);
    subRect93  = new QCPAxisRect(ui->BePlot, true);
    subRect94  = new QCPAxisRect(ui->BePlot, true);
    subRect95  = new QCPAxisRect(ui->BePlot, true);
    subRect96  = new QCPAxisRect(ui->BePlot, true);


    mainLayout->addElement( 0 , 0, subRect1  );
    mainLayout->addElement( 1 , 0, subRect2  );
    mainLayout->addElement( 2 , 0, subRect3  );
    mainLayout->addElement( 3 , 0, subRect4  );
    mainLayout->addElement( 4 , 0, subRect5  );
    mainLayout->addElement( 5 , 0, subRect6  );
    mainLayout->addElement( 6 , 0, subRect7  );
    mainLayout->addElement( 7 , 0, subRect8  );
    mainLayout->addElement( 8 , 0, subRect9  );
    mainLayout->addElement( 9 , 0, subRect10 );
    mainLayout->addElement( 10, 0, subRect11 );
    mainLayout->addElement( 11, 0, subRect12 );
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
    mainLayout->addElement( 22, 0, subRect23 );
    mainLayout->addElement( 23, 0, subRect24 );

    mainLayout->addElement( 24, 0, subRect25 );
    mainLayout->addElement( 25, 0, subRect26 );
    mainLayout->addElement( 26, 0, subRect27 );
    mainLayout->addElement( 27, 0, subRect28 );
    mainLayout->addElement( 28, 0, subRect29 );
    mainLayout->addElement( 29, 0, subRect30 );

    mainLayout->addElement( 30, 0, subRect31 );
    mainLayout->addElement( 31, 0, subRect32 );
    mainLayout->addElement( 32, 0, subRect33 );
    mainLayout->addElement( 33, 0, subRect34 );
    mainLayout->addElement( 34, 0, subRect35 );
    mainLayout->addElement( 35, 0, subRect36 );

    mainLayout->addElement( 36, 0, subRect37 );
    mainLayout->addElement( 37, 0, subRect38 );
    mainLayout->addElement( 38, 0, subRect39 );
    mainLayout->addElement( 39, 0, subRect40 );
    mainLayout->addElement( 40, 0, subRect41 );
    mainLayout->addElement( 41, 0, subRect42 );

    mainLayout->addElement( 42, 0, subRect43 );
    mainLayout->addElement( 43, 0, subRect44 );
    mainLayout->addElement( 44, 0, subRect45 );
    mainLayout->addElement( 45, 0, subRect46 );
    mainLayout->addElement( 46, 0, subRect47 );
    mainLayout->addElement( 47, 0, subRect48 );

    mainLayout->addElement( 48, 0, subRect49 );
    mainLayout->addElement( 49, 0, subRect50 );
    mainLayout->addElement( 50, 0, subRect51 );
    mainLayout->addElement( 51, 0, subRect52 );
    mainLayout->addElement( 52, 0, subRect53 );
    mainLayout->addElement( 53, 0, subRect54 );

    mainLayout->addElement( 54, 0, subRect55 );
    mainLayout->addElement( 55, 0, subRect56 );
    mainLayout->addElement( 56, 0, subRect57 );
    mainLayout->addElement( 57, 0, subRect58 );
    mainLayout->addElement( 58, 0, subRect59 );
    mainLayout->addElement( 59, 0, subRect60 );

    mainLayout->addElement( 60, 0, subRect61 );
    mainLayout->addElement( 61, 0, subRect62 );
    mainLayout->addElement( 62, 0, subRect63 );
    mainLayout->addElement( 63, 0, subRect64 );
    mainLayout->addElement( 64, 0, subRect65 );
    mainLayout->addElement( 65, 0, subRect66 );

    mainLayout->addElement( 66, 0, subRect67 );
    mainLayout->addElement( 67, 0, subRect68 );
    mainLayout->addElement( 68, 0, subRect69 );
    mainLayout->addElement( 69, 0, subRect70 );
    mainLayout->addElement( 70, 0, subRect71 );
    mainLayout->addElement( 71, 0, subRect72 );

    mainLayout->addElement( 72, 0, subRect73 );
    mainLayout->addElement( 73, 0, subRect74 );
    mainLayout->addElement( 74, 0, subRect75 );
    mainLayout->addElement( 75, 0, subRect76 );
    mainLayout->addElement( 76, 0, subRect77);
    mainLayout->addElement( 77, 0, subRect78 );

    mainLayout->addElement( 78, 0, subRect79 );
    mainLayout->addElement( 79, 0, subRect80 );
    mainLayout->addElement( 80, 0, subRect81 );
    mainLayout->addElement( 81, 0, subRect82 );
    mainLayout->addElement( 82, 0, subRect83 );
    mainLayout->addElement( 83, 0, subRect84 );

    mainLayout->addElement( 84, 0, subRect85 );
    mainLayout->addElement( 85, 0, subRect86 );
    mainLayout->addElement( 86, 0, subRect87 );
    mainLayout->addElement( 87, 0, subRect88 );
    mainLayout->addElement( 88, 0, subRect89 );
    mainLayout->addElement( 89, 0, subRect90 );

    mainLayout->addElement( 90, 0, subRect91 );
    mainLayout->addElement( 91, 0, subRect92 );
    mainLayout->addElement( 92, 0, subRect93 );
    mainLayout->addElement( 93, 0, subRect94 );
    mainLayout->addElement( 94, 0, subRect95 );
    mainLayout->addElement( 95, 0, subRect96 );

    //subRect2->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    //subRect2->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    //==================================================================
    ui->BePlot->axisRect()->setupFullAxesBox(true);
    ui->BePlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    //==================================================================


    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->BePlot);


    subRect1->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect2->setMarginGroup(QCP::msTop |QCP::msBottom| QCP::msLeft|QCP::msRight, marginGroup);
    subRect3->setMarginGroup(QCP::msTop |QCP::msBottom| QCP::msLeft|QCP::msRight, marginGroup);
    subRect4->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect5->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect6->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect7->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect8->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect9->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect10->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect11->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect12->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect13  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect14  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect15  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect16  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect17  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect18  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect19  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect20  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect21  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect22  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect23  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect24  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect25  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect26  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect27  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect28  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect29  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect30  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect31  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect32  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect33  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect34  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect35  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect36  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect37  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect38  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect39  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect40  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect41  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect42  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect43  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect44  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect45  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect46  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect47  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect48  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect49  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect50  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect51  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect52  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect53  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect54  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect55  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect56  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect57  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect58  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect59  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect60  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect61  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect62  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect63  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect64  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect65  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect66  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect67  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect68  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect69  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect70  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect71  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect72  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect73  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect74  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect75  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect76  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect77  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect78  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect79  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect80  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect81  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect82  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect83  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect84  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect85  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect86  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect87  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect88  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect89  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect90  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect91  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect92  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect93  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect94  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect95  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect96  ->setMarginGroup(QCP::msTop |QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);


    foreach (QCPAxisRect *rect, ui->BePlot->axisRects())
    {
      foreach (QCPAxis *axis, rect->axes())
      {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
        axis->scaleRange(1);
        axis->setPadding(2);
      }
    }



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

    BeAddDetPlot (subRect1  , 1 , "RPC Channel  1");
    BeAddDetPlot (subRect2  , 2 , "RPC Channel  2");
    BeAddDetPlot (subRect3  , 3 , "RPC Channel  3");
    BeAddDetPlot (subRect4  , 4 , "RPC Channel  4");
    BeAddDetPlot (subRect5  , 5 , "RPC Channel  5");
    BeAddDetPlot (subRect6  , 6 , "RPC Channel  6");

    BeAddDetPlot (subRect7  , 7 , "RPC Channel  7");
    BeAddDetPlot (subRect8  , 8 , "RPC Channel  8");
    BeAddDetPlot (subRect9  , 9 , "RPC Channel  9");
    BeAddDetPlot (subRect10 , 10 , "RPC Channel  10");
    BeAddDetPlot (subRect11 , 11 , "RPC Channel  11");
    BeAddDetPlot (subRect12 , 12 , "RPC Channel  12");

    BeAddDetPlot (subRect13  , 13  , "RPC Channel 13");
    BeAddDetPlot (subRect14  , 14  , "RPC Channel 14");
    BeAddDetPlot (subRect15  , 15  , "RPC Channel 15");
    BeAddDetPlot (subRect16  , 16  , "RPC Channel 16");
    BeAddDetPlot (subRect17  , 17  , "RPC Channel 17");
    BeAddDetPlot (subRect18  , 18  , "RPC Channel 18");

    BeAddDetPlot (subRect19  , 19  , "RPC Channel 19");
    BeAddDetPlot (subRect20  ,  20 , "RPC Channel  20");
    BeAddDetPlot (subRect21  , 21  , "RPC Channel  21");
    BeAddDetPlot (subRect22  , 22  , "RPC Channel  22");
    BeAddDetPlot (subRect23  , 23  , "RPC Channel  23");
    BeAddDetPlot (subRect24  , 24  , "RPC Channel  24");

    BeAddDetPlot (subRect25  , 25  , "RPC Channel  25");
    BeAddDetPlot (subRect26  , 26  , "RPC Channel  26");
    BeAddDetPlot (subRect27  , 27  , "RPC Channel  27");
    BeAddDetPlot (subRect28  , 28  , "RPC Channel  28");
    BeAddDetPlot (subRect29  , 29  , "RPC Channel  29");
    BeAddDetPlot (subRect30  , 30  , "RPC Channel  30");

    BeAddDetPlot (subRect31  , 31  , "RPC Channel  31");
    BeAddDetPlot (subRect32  , 32  , "RPC Channel  32");
    BeAddDetPlot (subRect33  , 33  , "RPC Channel  33");
    BeAddDetPlot (subRect34  , 34  , "RPC Channel  34");
    BeAddDetPlot (subRect35  , 35  , "RPC Channel  35");
    BeAddDetPlot (subRect36  , 36  , "RPC Channel  36");

    BeAddDetPlot (subRect37  , 37  , "RPC Channel  37");
    BeAddDetPlot (subRect38  , 38  , "RPC Channel  38");
    BeAddDetPlot (subRect39  , 39  , "RPC Channel  39");
    BeAddDetPlot (subRect40  , 40  , "RPC Channel  40");
    BeAddDetPlot (subRect41  , 41  , "RPC Channel  41");
    BeAddDetPlot (subRect42  , 42  , "RPC Channel  42");

    BeAddDetPlot (subRect43  , 43  , "RPC Channel  43");
    BeAddDetPlot (subRect44  , 44  , "RPC Channel  44");
    BeAddDetPlot (subRect45  , 45  , "RPC Channel  45");
    BeAddDetPlot (subRect46  , 46  , "RPC Channel  46");
    BeAddDetPlot (subRect47  , 47  , "RPC Channel  47");
    BeAddDetPlot (subRect48  , 48  , "RPC Channel  48");

    BeAddDetPlot (subRect49  , 49  , "RPC Channel  49");
    BeAddDetPlot (subRect50  , 50  , "RPC Channel  50");
    BeAddDetPlot (subRect51  , 51  , "RPC Channel  51");
    BeAddDetPlot (subRect52  , 52  , "RPC Channel  52");
    BeAddDetPlot (subRect53  , 53  , "RPC Channel  53");
    BeAddDetPlot (subRect54  , 54  , "RPC Channel  54");

    BeAddDetPlot (subRect55  , 55  , "RPC Channel  55");
    BeAddDetPlot (subRect56  , 56  , "RPC Channel  56");
    BeAddDetPlot (subRect57  , 57  , "RPC Channel  57");
    BeAddDetPlot (subRect58  , 58  , "RPC Channel  58");
    BeAddDetPlot (subRect59  , 59  , "RPC Channel  59");
    BeAddDetPlot (subRect60  , 60  , "RPC Channel  60");

    BeAddDetPlot (subRect61  , 61  , "RPC Channel  61");
    BeAddDetPlot (subRect62  , 62  , "RPC Channel  62");
    BeAddDetPlot (subRect63  , 62  , "RPC Channel  63");
    BeAddDetPlot (subRect64  , 64  , "RPC Channel  64");
    BeAddDetPlot (subRect65  , 65  , "RPC Channel  65");
    BeAddDetPlot (subRect66  , 66  , "RPC Channel  66");

    BeAddDetPlot (subRect67  , 67  , "RPC Channel  67");
    BeAddDetPlot (subRect68  , 68  , "RPC Channel  68");
    BeAddDetPlot (subRect69  , 69  , "RPC Channel  69");
    BeAddDetPlot (subRect70  , 70  , "RPC Channel  70");
    BeAddDetPlot (subRect71  , 71  , "RPC Channel  71");
    BeAddDetPlot (subRect72  , 72  , "RPC Channel  72");

    BeAddDetPlot (subRect73  , 73  , "RPC Channel  73");
    BeAddDetPlot (subRect74  , 74  , "RPC Channel  74");
    BeAddDetPlot (subRect75  , 75  , "RPC Channel  75");
    BeAddDetPlot (subRect76  , 76  , "RPC Channel  76");
    BeAddDetPlot (subRect77  , 77  , "RPC Channel  77");
    BeAddDetPlot (subRect78  , 78  , "RPC Channel  78");

    BeAddDetPlot (subRect79  , 79  , "RPC Channel  79");
    BeAddDetPlot (subRect80  , 80  , "RPC Channel  80");
    BeAddDetPlot (subRect81  , 81  , "RPC Channel  81");
    BeAddDetPlot (subRect82  , 82  , "RPC Channel  82");
    BeAddDetPlot (subRect83  , 83  , "RPC Channel  83");
    BeAddDetPlot (subRect84  , 84  , "RPC Channel  84");

    BeAddDetPlot (subRect85  , 85  , "RPC Channel  85");
    BeAddDetPlot (subRect86  , 86  , "RPC Channel  86");
    BeAddDetPlot (subRect87  , 87  , "RPC Channel  87");
    BeAddDetPlot (subRect88  , 88  , "RPC Channel  88");
    BeAddDetPlot (subRect89  , 89  , "RPC Channel  89");
    BeAddDetPlot (subRect90  , 90  , "RPC Channel  90");

    BeAddDetPlot (subRect91  , 91  , "RPC Channel  91");
    BeAddDetPlot (subRect92  , 92  , "RPC Channel  92");
    BeAddDetPlot (subRect93  , 93  , "RPC Channel  93");
    BeAddDetPlot (subRect94  , 94  , "RPC Channel  94");
    BeAddDetPlot (subRect95  , 95  , "RPC Channel  95");
    BeAddDetPlot (subRect96  , 96  , "RPC Channel  96");


}

//======================================================================================
//
//======================================================================================
void BackendEmu2::BeAddDetPlot (QCPAxisRect *subRect , unsigned int StripNum , QString stripNum){

    QFont legendFont = font();
    legendFont.setPointSize(11);
    ui->BePlot->setFont(legendFont);
    subRect->setupFullAxesBox(true);

    //subRect->setBackgroundScaled(10);
    //subRect->setMaximumSize(400,1600);
    subRect->setMinimumSize(40,170);



    subRect->axis(QCPAxis::atBottom)->setTickLabelRotation(90);
    subRect->axis(QCPAxis::atBottom)->setLabel(" Bunch Crossing Number "); // RPC Channel xx


    subRect->axis(QCPAxis::atBottom)->setSubTicks(false);
    subRect->axis(QCPAxis::atBottom)->setTickLength(0, 4);
    subRect->axis(QCPAxis::atBottom)->setRange(0, 200);
    subRect->axis(QCPAxis::atBottom)->setBasePen(QPen(Qt::white));
    subRect->axis(QCPAxis::atBottom)->setTickPen(QPen(Qt::white));
    subRect->axis(QCPAxis::atBottom)->setSubTickPen(QPen(Qt::white));
    subRect->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect->axis(QCPAxis::atBottom)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRect->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::white);
    subRect->axis(QCPAxis::atBottom)->setLabelColor(Qt::white);
    subRect->axis(QCPAxis::atBottom)->selectableParts().setFlag(QCPAxis::spAxis);
    subRect->axis(QCPAxis::atBottom)->setPadding(20); // a bit more space to the left border



     subRect->axis(QCPAxis::atTop)->setRange(0, 200);
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
     subRect->axis(QCPAxis::atTop)->setPadding(20); // a bit more space to the left border

     // prepare y axis:
     //subRect->axis(QCPAxis::atLeft)->setRange(0, 20);
     //subRect->axis(QCPAxis::atLeft)->setRangeUpper (20);
     subRect->axis(QCPAxis::atLeft)->setPadding(6); // a bit more space to the left border
     subRect->axis(QCPAxis::atLeft)->setLabel(" Sub-BX "); // Vertical Text
     subRect->axis(QCPAxis::atLeft)->setBasePen(QPen(Qt::white));
     subRect->axis(QCPAxis::atLeft)->setTickPen(QPen(Qt::white));
     subRect->axis(QCPAxis::atLeft)->setSubTickPen(QPen(Qt::white));
     subRect->axis(QCPAxis::atLeft)->grid()->setSubGridVisible(true);
     subRect->axis(QCPAxis::atLeft)->setTickLabelColor(Qt::white);
     subRect->axis(QCPAxis::atLeft)->setLabelColor(Qt::white);
     subRect->axis(QCPAxis::atLeft)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
     subRect->axis(QCPAxis::atLeft)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
     subRect->axis(QCPAxis::atLeft)->selectableParts().setFlag(QCPAxis::spAxis);

     //subRect->axis(QCPAxis::atRight)->setRange(0, 20);
     //subRect->axis(QCPAxis::atRight)->setRangeUpper (20);
     subRect->axis(QCPAxis::atRight)->setPadding(6); // a bit more space to the left border
     subRect->axis(QCPAxis::atRight)->setBasePen(QPen(Qt::white));
     subRect->axis(QCPAxis::atRight)->setTickPen(QPen(Qt::white));
     subRect->axis(QCPAxis::atRight)->setSubTickPen(QPen(Qt::white));
     subRect->axis(QCPAxis::atRight)->grid()->setSubGridVisible(true);
     subRect->axis(QCPAxis::atRight)->setTickLabelColor(Qt::white);
     //subRect->axis(QCPAxis::atRight)->setLabelColor(Qt::white);
     subRect->axis(QCPAxis::atRight)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
     subRect->axis(QCPAxis::atRight)->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
     subRect->axis(QCPAxis::atRight)->selectableParts().setFlag(QCPAxis::spAxis);


     //-----------------------------------------------------------------
     // prepare x axis with channel labels:
     // https://www.qcustomplot.com/documentation/classQCPAxisTicker.html
     //-----------------------------------------------------------------
     /* Technique 1

     QVector<double> ticks (200);
     QVector<QString> labels(200);
     for (int j=0 ; j<=129;){

         ticks[j] = j+1 ;
         labels[j] = QString("%1").arg(j+1);
         j=j+9;
     }

     QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
     textTicker->addTicks(ticks, labels);
     subRect->axis(QCPAxis::atBottom)->setTicker(textTicker);
    */
     //-----------------------------------------------------------------
     //Technique 2
     // https://www.qcustomplot.com/documentation/classQCPAxisTickerFixed.html

    QSharedPointer<QCPAxisTickerFixed> fixedTicker(new QCPAxisTickerFixed);
    fixedTicker->setTickStep(10.0);
    fixedTicker->setScaleStrategy(QCPAxisTickerFixed::ssNone);
    subRect->axis(QCPAxis::atBottom)->setTicker(fixedTicker);
    //------------------------------------------------------------------
}

//======================================================================================
//
//======================================================================================
void BackendEmu2::BePlotter(unsigned int y0_StripData[200][200], unsigned int StripNum){


    QCPBars *stripN ;

    switch (StripNum) {
        case 1:
           subRect = subRect1 ;
        break;
        case 2:
            subRect = subRect2 ;
        break;

        case 3:
            subRect = subRect3 ;
        break;
        case 4:
            subRect = subRect4 ;
        break;
        case 5:
            subRect = subRect5 ;
        break;
        case 6:
            subRect = subRect6 ;
        break;
        case 7:
            subRect = subRect7 ;
        break;
        case 8:
            subRect = subRect8 ;
        break;
        case 9:
            subRect = subRect9 ;
        break;
        case 10:
            subRect = subRect10 ;
        break;
        case 11:
            subRect = subRect11 ;
        break;
        case 12:
            subRect = subRect12 ;
        break;
        //===================================================================
        case 13:
            subRect = subRect13 ;
        break;
        case 14:
            subRect = subRect14 ;
        break;
        case 15:
            subRect = subRect15 ;
        break;
        case 16:
            subRect = subRect16 ;
        break;
        case 17:
            subRect = subRect17 ;
        break;
        case 18:
            subRect = subRect18 ;
        break;
        case 19:
            subRect = subRect19 ;
        break;
        case 20:
            subRect = subRect20 ;
        break;
        case 21:
            subRect = subRect21 ;
        break;
        case 22:
            subRect = subRect22 ;
        break;
        case 23:
            subRect = subRect23 ;
        break;
        case 24:
            subRect = subRect24 ;
        break;
        //===================================================================
        case 25:
            subRect = subRect25 ;
        break;
        case 26:
            subRect = subRect26 ;
        break;
        case 27:
            subRect = subRect27 ;
        break;
        case 28:
            subRect = subRect28 ;
        break;
        case 29:
            subRect = subRect29 ;
        break;
        case 30:
            subRect = subRect30 ;
        break;
        case 31:
            subRect = subRect31 ;
        break;
        case 32:
            subRect = subRect32 ;
        break;
        case 33:
            subRect = subRect33 ;
        break;
        case 34:
            subRect = subRect34 ;
        break;
        case 35:
            subRect = subRect35 ;
        break;
        case 36:
            subRect = subRect36 ;
        break;
        //===================================================================
        case 37:
            subRect = subRect37 ;
        break;
        case 38:
            subRect = subRect38 ;
        break;
        case 39:
            subRect = subRect39 ;
        break;
        case 40:
            subRect = subRect40 ;
        break;
        case 41:
            subRect = subRect41 ;
        break;
        case 42:
            subRect = subRect42 ;
        break;
        case 43:
            subRect = subRect43 ;
        break;
        case 44:
            subRect = subRect44 ;
        break;
        case 45:
            subRect = subRect45 ;
        break;
        case 46:
            subRect = subRect46 ;
        break;
        case 47:
            subRect = subRect47 ;
        break;
        case 48:
            subRect = subRect48 ;
        break;
        //===================================================================
        case 49:
            subRect = subRect49 ;
        break;
        case 50:
            subRect = subRect50 ;
        break;
        case 51:
            subRect = subRect51 ;
        break;
        case 52:
            subRect = subRect52 ;
        break;
        case 53:
            subRect = subRect53 ;
        break;
        case 54:
            subRect = subRect54 ;
        break;
        case 55:
            subRect = subRect55 ;
        break;
        case 56:
            subRect = subRect56 ;
        break;
        case 57:
            subRect = subRect57 ;
        break;
        case 58:
            subRect = subRect58 ;
        break;
        case 59:
            subRect = subRect59 ;
        break;
        case 60:
            subRect = subRect60 ;
        break;
        //===================================================================
        case 61:
            subRect = subRect61 ;
        break;
        case 62:
            subRect = subRect62 ;
        break;
        case 63:
            subRect = subRect63 ;
        break;
        case 64:
            subRect = subRect64 ;
        break;
        case 65:
            subRect = subRect65 ;
        break;
        case 66:
            subRect = subRect66 ;
        break;
        case 67:
            subRect = subRect67 ;
        break;
        case 68:
            subRect = subRect68 ;
        break;
        case 69:
            subRect = subRect69 ;
        break;
        case 70:
            subRect = subRect70 ;
        break;
        case 71:
            subRect = subRect71 ;
        break;
        case 72:
            subRect = subRect72 ;
        break;
        //===================================================================
        case 73:
            subRect = subRect73 ;
        break;
        case 74:
            subRect = subRect74 ;
        break;
        case 75:
            subRect = subRect75 ;
        break;
        case 76:
            subRect = subRect76 ;
        break;
        case 77:
            subRect = subRect77 ;
        break;
        case 78:
            subRect = subRect78 ;
        break;
        case 79:
            subRect = subRect79 ;
        break;
        case 80:
            subRect = subRect80 ;
        break;
        case 81:
            subRect = subRect81 ;
        break;
        case 82:
            subRect = subRect82 ;
        break;
        case 83:
            subRect = subRect83 ;
        break;
        case 84:
            subRect = subRect84 ;
        break;
        //===================================================================
        case 85:
            subRect = subRect85 ;
        break;
        case 86:
            subRect = subRect86 ;
        break;
        case 87:
            subRect = subRect87 ;
        break;
        case 88:
            subRect = subRect88 ;
        break;
        case 89:
            subRect = subRect89 ;
        break;
        case 90:
            subRect = subRect90 ;
        break;
        case 91:
            subRect = subRect91 ;
        break;
        case 92:
            subRect = subRect92 ;
        break;
        case 93:
            subRect = subRect93 ;
        break;
        case 94:
            subRect = subRect94 ;
        break;
        case 95:
            subRect = subRect95 ;
        break;
        case 96:
            subRect = subRect96 ;
        break;

        default:
            subRect = subRect1 ;
        break;
    }
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

    QVector <double> y1_StripValue (4000);

    //-----------------------------------------------------------------
    // prepare x axis with channel labels:
    //-----------------------------------------------------------------
    QVector<double> ticks (4000);
    QVector<QString> labels(4000);

    unsigned int max_value = 0 ;
    BxCntVal = 0 ;

    for (unsigned int j=BxCntVal+0 ; j< BxCntVal+200;j++){

            ticks[j] = j ;

            labels[j] = QString("%1").arg(j);

            //y1_StripValue[j] = y0_StripData[StripNum-1][j-BxCntVal];
            y1_StripValue[j] = y0_StripData[StripNum][j-BxCntVal];

            if (y1_StripValue[j]>= max_value){ // Find Max Y value for right-Axis scaling
                max_value = y1_StripValue[j];
            }
    }

    subRect->axis(QCPAxis::atLeft)->setRange(0, max_value);
    subRect->axis(QCPAxis::atRight)->setRange(0, max_value);
    //============================================
    stripN->setData( ticks , y1_StripValue );
    //============================================
    ui->BePlot->replot();
}
