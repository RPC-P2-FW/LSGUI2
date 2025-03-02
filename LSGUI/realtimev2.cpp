#include "realtimev2.h"
#include "ui_realtimev2.h"
#include "qcustomplot.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <QRectF>

realtimev2::realtimev2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::realtimev2)
{
    ui->setupUi(this);
}

realtimev2::~realtimev2()
{
    delete ui;
}

//https://www.qcustomplot.com/documentation/thelayoutsystem.html
//https://www.qcustomplot.com/documentation/thelayoutsystem.html

void realtimev2::setupLocalPlot (QCPAxisRect *subRect  , unsigned int y0_StripData[200][200], unsigned int StripNum , QString stripNum ){

    QVector <double> y1_StripValue (3000);

    QVector <double> x1_SampleNum (200);

    //unsigned int counter = 0;
    //ui->plot_CB->setInteractions( QCP::iRangeZoom | QCP::iSelectPlottables);
    /*
    ui->plot_CB->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                 QCP::iSelectLegend | QCP::iSelectPlottables);
    ui->plot_CB->setInteraction(QCP::iRangeDrag, true);
    */
    //==================================================================
    //  STRIP 2
    //==================================================================

    QCPBars *stripN = new QCPBars (subRect->axis(QCPAxis::atBottom ),
                                     subRect->axis(QCPAxis::atLeft));




    /*
    QCPGraph *stripN = new QCPGraph (subRect->axis(QCPAxis::atBottom ),
                                     subRect->axis(QCPAxis::atLeft));

    */

    stripN->setAntialiased(true); // gives more crisp, pixel aligned bar borders
    stripN->setStackingGap(1);
    //stripN->setName("MultiChannel Histogram - Adjustable Window ");
    stripN->setPen(QPen(QColor(0, 168, 140).lighter(130)));
    stripN->setBrush(QColor(0, 168, 140));


    //==================================================================
    QVector<double> ticks (3000);
    QVector<QString> labels(3000);

    unsigned int max_value = 0 ;

    for (unsigned int j=BxCntVal+0 ; j< BxCntVal+129;j++){


            //ticks[j] = j+1 ;
            ticks[j] = j ;
            //labels[j] = QString("%1").arg(j+1);
            labels[j] = QString("%1").arg(j);

            y1_StripValue[j] = y0_StripData[StripNum-1][j-BxCntVal];

            if (y1_StripValue[j]>= max_value){ // Find Max Y value for right-Axis scaling
                max_value = y1_StripValue[j];
            }

    }


    //==================================================================

    //==================================================================
    /*
    for (unsigned int j= 0+BxCntVal ; j< BxCntVal+129 ; j++){

        y1_StripValue[j] = y0CB_StripData[StripNum-1][j-BxCntVal];
        //qDebug() <<  QString("3- y0CB_StripData[%1-1][%2] = %3").arg(StripNum).arg(j).arg(y0CB_StripData[StripNum-1][j]); //y0CB_StripData[StripNum-1][j];

    }*/
    //==================================================================


    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    subRect->axis(QCPAxis::atBottom)->setTicker(textTicker);
    //subRect->axis(QCPAxis::atTop)->setTicker(textTicker);



    //subRect->setInteractions( QCP::iRangeZoom | QCP::iSelectPlottables);

    //subRect->QCPAxis::SelectablePart(isFullScreen());
    //subRect-> setSelectionRectMode (QCP::SelectionRectMode  mode );
    //QRectF r1;
    //subRect->zoom(r1(100.0, 200.1, 11.2, 16.3));



    //============================================
    stripN->setData( ticks , y1_StripValue );
    //============================================

    subRect->setRangeZoom(Qt::Vertical);
    subRect->rangeZoom();

    subRect->axis(QCPAxis::atBottom)->setTickLabelRotation(90);
    subRect->axis(QCPAxis::atBottom)->setLabel(" Bunch Crossing Number "); // RPC Channel xx
    subRect->axis(QCPAxis::atBottom)->setSubTicks(true);
    subRect->axis(QCPAxis::atBottom)->setTickLength(0, 2);
    subRect->axis(QCPAxis::atBottom)->setRange(BxCntVal+0, BxCntVal +129);
    subRect->axis(QCPAxis::atBottom)->setBasePen(QPen(Qt::white));
    subRect->axis(QCPAxis::atBottom)->setTickPen(QPen(Qt::white));
    subRect->axis(QCPAxis::atBottom)->setSubTickPen(QPen(Qt::white));
    subRect->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    subRect->axis(QCPAxis::atBottom)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRect->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::white);
    subRect->axis(QCPAxis::atBottom)->setLabelColor(Qt::white);
    subRect->axis(QCPAxis::atBottom)->selectableParts().setFlag(QCPAxis::spAxis);
    subRect->axis(QCPAxis::atBottom)->setPadding(6); // a bit more space to the left border


    subRect->axis(QCPAxis::atTop)->setRange(BxCntVal+0, BxCntVal +129);
    subRect->axis(QCPAxis::atTop)->setTickLength(false, 2);
    subRect->axis(QCPAxis::atTop)->setLabel(stripNum); // RPC Channel xx
    subRect->axis(QCPAxis::atTop)->setSubTicks(false);
    subRect->axis(QCPAxis::atTop)->setBasePen(QPen(Qt::white));
    subRect->axis(QCPAxis::atTop)->setTickPen(QPen(Qt::white));
    subRect->axis(QCPAxis::atTop)->setSubTickPen(QPen(Qt::white));
    subRect->axis(QCPAxis::atTop)->grid()->setVisible(true);
    subRect->axis(QCPAxis::atTop)->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    subRect->axis(QCPAxis::atTop)->setTickLabelColor(Qt::white);
    subRect->axis(QCPAxis::atTop)->setLabelColor(Qt::white);
    subRect->axis(QCPAxis::atTop)->selectableParts().setFlag(QCPAxis::spAxis);
    subRect->axis(QCPAxis::atTop)->setPadding(6); // a bit more space to the left border

    // prepare y axis:
    subRect->axis(QCPAxis::atLeft)->setRange(0, 20);
    subRect->axis(QCPAxis::atLeft)->setRangeUpper (20);
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

    subRect->axis(QCPAxis::atRight)->setRange(0, 20);
    subRect->axis(QCPAxis::atLeft)->setRangeUpper (20);
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
    //==================================================================


    //connect(subRect, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel(subRect)));
    //subRect->setRangeZoom(Qt::Horizontal|Qt::Vertical);

}

void realtimev2::mouseWheel(QWheelEvent *e)
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
            ui->plot_CB->axisRect()->setRangeZoom(Qt::Vertical);
            //ui->plot_CB->xAxis->setRange(qAbs(e->position().x()),qAbs(e->position().x()));
            //ui->plot_CB->yAxis->setRange(0,counter);
        } else {
            result = "Mouse Wheel Event: LEFT";
        }
    } else if (delta < 0) {
        if (vertical) {
            result = "Mouse Wheel Event: DOWN";
            counter--;
            ui->plot_CB->axisRect()->setRangeZoom(Qt::Vertical);
            //ui->plot_CB->xAxis->setRange(qAbs(e->position().x())+counter,qAbs(e->position().x())+counter);
            //ui->plot_CB->yAxis->setRange(0,counter);
        } else {
            result = "Mouse Wheel Event: RIGHT";
        }
    }
    qDebug() << result;

}

void realtimev2::mousePress()
{
    // if an axis is selected, only allow the direction of that axis to be dragged
    // if no axis is selected, both directions may be dragged

    if (ui->plot_CB->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
      ui->plot_CB->axisRect()->setRangeDrag(ui->plot_CB->xAxis->orientation());
    else if (ui->plot_CB->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
      ui->plot_CB->axisRect()->setRangeDrag(ui->plot_CB->yAxis->orientation());
    else
      ui->plot_CB->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}




void realtimev2::setupPlot_CB(void){

    //QVector <double> y1_FullWinChannel (200);
    //QVector <double> y1_AdjWinChannel (200);

    //QVector <double> x1_stripFulW (200);
    //QVector <double> x1_stripAdjW (200);
    //unsigned int stripNum ;


    // configure axis rect:
    ui->plot_CB->plotLayout()->clear(); // clear default axis rect so we can start from scratch
    /*
    QCPAxisRect *wideAxisRect = new QCPAxisRect(ui->plot_CB);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers
    */

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;

    ui->plot_CB->plotLayout()->addElement(0, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
    //ui->plot_CB->plotLayout()->setColumnStretchFactor(1,10);
    //ui->plot_CB->setInteractions( QCP::iRangeZoom | QCP::iSelectPlottables);
    //ui->plot_CB->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // prepare axis rects that will be placed in the sublayout:
    QCPAxisRect *subRect1 = new QCPAxisRect(ui->plot_CB, true); // false means to not setup default axes
    QCPAxisRect *subRect2 = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect3 = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect4 = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect5 = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect6 = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect7 = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect8 = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect9 = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect10 = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect11 = new QCPAxisRect(ui->plot_CB, true); // true means to not setup default axes
    QCPAxisRect *subRect12 = new QCPAxisRect(ui->plot_CB, true);

    QCPAxisRect *subRect13  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect14  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect15  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect16  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect17  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect18  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect19  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect20  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect21  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect22  = new QCPAxisRect(ui->plot_CB, true);


    QCPAxisRect *subRect23  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect24  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect25  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect26  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect27  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect28  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect29  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect30  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect31  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect32  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect33  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect34  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect35  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect36  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect37  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect38  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect39  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect40  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect41  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect42  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect43  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect44  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect45  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect46  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect47  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect48  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect49  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect50  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect51  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect52  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect53  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect54  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect55  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect56  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect57  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect58  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect59  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect60  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect61  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect62  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect63  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect64  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect65  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect66  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect67  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect68  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect69  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect70  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect71  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect72  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect73  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect74  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect75  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect76  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect77  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect78  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect79  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect80  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect81  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect82  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect83  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect84  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect85  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect86  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect87  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect88  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect89  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect90  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect91  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect92  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect93  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect94  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect95  = new QCPAxisRect(ui->plot_CB, true);
    QCPAxisRect *subRect96  = new QCPAxisRect(ui->plot_CB, true);



    subLayout->addElement(0, 0, subRect1);
    subLayout->setRowStretchFactor(0, 2);

    subLayout->addElement(1, 0, subRect2);
    subLayout->setRowStretchFactor(1, 2);

    subLayout->addElement(2, 0, subRect3);
    subLayout->setRowStretchFactor(2, 2);

    subLayout->addElement(3, 0, subRect4);
    subLayout->setRowStretchFactor(3, 2);

    subLayout->addElement(4, 0, subRect5);
    subLayout->setRowStretchFactor(4, 2);

    subLayout->addElement(5, 0, subRect6);
    subLayout->setRowStretchFactor(5, 2);

    subLayout->addElement(6, 0, subRect7);
    subLayout->setRowStretchFactor(6, 2);

    subLayout->addElement(7, 0, subRect8);
    subLayout->addElement(8, 0, subRect9);
    subLayout->addElement(9, 0, subRect10);
    subLayout->addElement(10, 0, subRect11);
    subLayout->addElement(11, 0, subRect12);


    subLayout->addElement( 12, 0, subRect13 );
    subLayout->addElement( 13, 0, subRect14 );
    subLayout->addElement( 14, 0, subRect15 );
    subLayout->addElement( 15, 0, subRect16 );
    subLayout->addElement( 16, 0, subRect17 );
    subLayout->addElement( 17, 0, subRect18 );

    subLayout->addElement( 18, 0, subRect19 );
    subLayout->addElement( 19, 0, subRect20 );
    subLayout->addElement( 20, 0, subRect21 );
    subLayout->addElement( 21, 0, subRect22 );
    subLayout->addElement( 22, 0, subRect23 );
    subLayout->addElement( 23, 0, subRect24 );

    subLayout->addElement( 24, 0, subRect25 );
    subLayout->addElement( 25, 0, subRect26 );
    subLayout->addElement( 26, 0, subRect27 );
    subLayout->addElement( 27, 0, subRect28 );
    subLayout->addElement( 28, 0, subRect29 );
    subLayout->addElement( 29, 0, subRect30 );

    subLayout->addElement( 30, 0, subRect31 );
    subLayout->addElement( 31, 0, subRect32 );
    subLayout->addElement( 32, 0, subRect33 );
    subLayout->addElement( 33, 0, subRect34 );
    subLayout->addElement( 34, 0, subRect35 );
    subLayout->addElement( 35, 0, subRect36 );

    subLayout->addElement( 36, 0, subRect37 );
    subLayout->addElement( 37, 0, subRect38 );
    subLayout->addElement( 38, 0, subRect39 );
    subLayout->addElement( 39, 0, subRect40 );
    subLayout->addElement( 40, 0, subRect41 );
    subLayout->addElement( 41, 0, subRect42 );

    subLayout->addElement( 42, 0, subRect43 );
    subLayout->addElement( 43, 0, subRect44 );
    subLayout->addElement( 44, 0, subRect45 );
    subLayout->addElement( 45, 0, subRect46 );
    subLayout->addElement( 46, 0, subRect47 );
    subLayout->addElement( 47, 0, subRect48 );

    subLayout->addElement( 48, 0, subRect49 );
    subLayout->addElement( 49, 0, subRect50 );
    subLayout->addElement( 50, 0, subRect51 );
    subLayout->addElement( 51, 0, subRect52 );
    subLayout->addElement( 52, 0, subRect53 );
    subLayout->addElement( 53, 0, subRect54 );

    subLayout->addElement( 54, 0, subRect55 );
    subLayout->addElement( 55, 0, subRect56 );
    subLayout->addElement( 56, 0, subRect57 );
    subLayout->addElement( 57, 0, subRect58 );
    subLayout->addElement( 58, 0, subRect59 );
    subLayout->addElement( 59, 0, subRect60 );

    subLayout->addElement( 60, 0, subRect61 );
    subLayout->addElement( 61, 0, subRect62 );
    subLayout->addElement( 62, 0, subRect63 );
    subLayout->addElement( 63, 0, subRect64 );
    subLayout->addElement( 64, 0, subRect65 );
    subLayout->addElement( 65, 0, subRect66 );

    subLayout->addElement( 66, 0, subRect67 );
    subLayout->addElement( 67, 0, subRect68 );
    subLayout->addElement( 68, 0, subRect69 );
    subLayout->addElement( 69, 0, subRect70 );
    subLayout->addElement( 70, 0, subRect71 );
    subLayout->addElement( 71, 0, subRect72 );

    subLayout->addElement( 72, 0, subRect73 );
    subLayout->addElement( 73, 0, subRect74 );
    subLayout->addElement( 74, 0, subRect75 );
    subLayout->addElement( 75, 0, subRect76 );
    subLayout->addElement( 76, 0, subRect77);
    subLayout->addElement( 77, 0, subRect78 );

    subLayout->addElement( 78, 0, subRect79 );
    subLayout->addElement( 79, 0, subRect80 );
    subLayout->addElement( 80, 0, subRect81 );
    subLayout->addElement( 81, 0, subRect82 );
    subLayout->addElement( 82, 0, subRect83 );
    subLayout->addElement( 83, 0, subRect84 );

    subLayout->addElement( 84, 0, subRect85 );
    subLayout->addElement( 85, 0, subRect86 );
    subLayout->addElement( 86, 0, subRect87 );
    subLayout->addElement( 87, 0, subRect88 );
    subLayout->addElement( 88, 0, subRect89 );
    subLayout->addElement( 89, 0, subRect90 );

    subLayout->addElement( 90, 0, subRect91 );
    subLayout->addElement( 91, 0, subRect92 );
    subLayout->addElement( 92, 0, subRect93 );
    subLayout->addElement( 93, 0, subRect94 );
    subLayout->addElement( 94, 0, subRect95 );
    subLayout->addElement( 95, 0, subRect96 );


    // setup axes in sub layout axis rects:
    subRect1->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    //subRect1->axis(QCPAxis::atBottom)->ticker()->setTickCount(2);
    subRect1->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    subRect1->axis(QCPAxis::atLeft)->rescale(true);
    subRect1->axis(QCPAxis::atRight)->rescale(true);

    //subRect1->axis(QCPAxis::atLeft)->setScaleRatio(axis(QCPAxis::atRight)   ,1);

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

    subRect22 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect22 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect23 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect23 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect24 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect24 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect25 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect25 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect26 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect26 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect27 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect27 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect28 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect28 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect29 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect29 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect30 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect30 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect31 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect31 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect32 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect32 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect33 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect33 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect34 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect34 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect35 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect35 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect36 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect36 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect37 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect37 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect38 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect38 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect39 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect39 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect40 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect40 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect41 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect41 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect42 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect42 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect43 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect43 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect44 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect44 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect45 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect45 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect46 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect46 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect47 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect47 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect48 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect48 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect49 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect49 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect50 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect50 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect51 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect51 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect52 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect52 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect53 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect53 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect54 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect54 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect55 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect55 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect56 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect56 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect57 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect57 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect58 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect58 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect59 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect59 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect60 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect60 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect61 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect61 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect62 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect62 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect63 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect63 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect64 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect64 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect65 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect65 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect66 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect66 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect67 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect67 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect68 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect68 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect69 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect69 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect70 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect70 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect71 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect71 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect72 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect72 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect73 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect73 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect74 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect74 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect75 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect75 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect76 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect76 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect77 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect77 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect78 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect78 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect79 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect79 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect80 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect80 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect81 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect81 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect82 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect82 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect83 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect83 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect84 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect84 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect85 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect85 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect86 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect86 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect87 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect87 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect88 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect88 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect89 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect89 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect90 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect90 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect91 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect91 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect92 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect92 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect93 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect93 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect94 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect94 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect95 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect95 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect96 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect96 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);



    // synchronize the left and right margins of the top and bottom axis rects:
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot_CB);

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
    subRect22  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect23  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect24  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect25  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect26  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect27  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect28  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect29  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect30  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect31  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect32  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect33  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect34  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect35  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect36  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect37  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect38  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect39  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect40  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect41  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect42  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect43  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect44  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect45  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect46  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect47  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect48  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect49  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect50  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect51  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect52  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect53  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect54  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect55  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect56  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect57  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect58  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect59  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect60  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect61  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect62  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect63  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect64  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect65  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect66  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect67  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect68  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect69  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect70  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect71  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect72  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect73  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect74  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect75  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect76  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect77  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect78  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect79  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect80  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect81  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect82  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect83  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect84  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect85  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect86  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect87  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect88  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect89  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect90  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);

    subRect91  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect92  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect93  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect94  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect95  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);
    subRect96  ->setMarginGroup(QCP::msBottom | QCP::msLeft|QCP::msRight, marginGroup);


    ui->plot_CB->axisRect()->setupFullAxesBox(true);
    ui->plot_CB->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);


    //wideAxisRect->setMarginGroup(QCP::msTop | QCP::msBottom | QCP::msRight | QCP::msLeft, marginGroup);


    // move newly created axes on "axes" layer and grids on "grid" layer:

    foreach (QCPAxisRect *rect, ui->plot_CB->axisRects())
    {
      foreach (QCPAxis *axis, rect->axes())
      {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
        //axis->scaleRange(1);
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
    //
    //==================================================================




    setupLocalPlot (subRect1  , y0LB1_StripData, 1 , "RPC Channel  1");
    setupLocalPlot (subRect2  , y0LB1_StripData, 2 , "RPC Channel  2");
    setupLocalPlot (subRect3  , y0LB1_StripData, 3 , "RPC Channel  3");
    setupLocalPlot (subRect4  , y0LB1_StripData, 4 , "RPC Channel  4");
    setupLocalPlot (subRect5  , y0LB1_StripData, 5 , "RPC Channel  5");
    setupLocalPlot (subRect6  , y0LB1_StripData,  6 , "RPC Channel  6");

    setupLocalPlot (subRect7  , y0LB1_StripData,  7 , "RPC Channel  7");
    setupLocalPlot (subRect8  , y0LB1_StripData,  8 , "RPC Channel  8");
    setupLocalPlot (subRect9  , y0LB1_StripData,  9 , "RPC Channel  9");
    setupLocalPlot (subRect10 , y0LB1_StripData,  10 , "RPC Channel  10");
    setupLocalPlot (subRect11 , y0LB1_StripData,  11 , "RPC Channel  11");
    setupLocalPlot (subRect12 , y0LB1_StripData,  12 , "RPC Channel  12");

    setupLocalPlot (subRect13  , y0LB1_StripData,  13  , "RPC Channel 13");
    setupLocalPlot (subRect14  , y0LB1_StripData,  14  , "RPC Channel 14");
    setupLocalPlot (subRect15  , y0LB1_StripData,  15  , "RPC Channel 15");
    setupLocalPlot (subRect16  , y0LB1_StripData,  16  , "RPC Channel 16");
    setupLocalPlot (subRect17  , y0LB1_StripData, 17  , "RPC Channel 17");
    setupLocalPlot (subRect18  , y0LB1_StripData, 18  , "RPC Channel 18");

    setupLocalPlot (subRect19  , y0LB1_StripData, 19  , "RPC Channel 19");
    setupLocalPlot (subRect20  , y0LB1_StripData,  20 , "RPC Channel  20");
    setupLocalPlot (subRect21  , y0LB1_StripData, 21  , "RPC Channel  21");
    setupLocalPlot (subRect22  , y0LB1_StripData, 22  , "RPC Channel  22");
    setupLocalPlot (subRect23  , y0LB1_StripData, 23  , "RPC Channel  23");
    setupLocalPlot (subRect24  , y0LB1_StripData, 24  , "RPC Channel  24");

    setupLocalPlot (subRect25  , y0LB1_StripData, 25  , "RPC Channel  25");
    setupLocalPlot (subRect26  , y0LB1_StripData, 26  , "RPC Channel  26");
    setupLocalPlot (subRect27  , y0LB1_StripData, 27  , "RPC Channel  27");
    setupLocalPlot (subRect28  , y0LB1_StripData, 28  , "RPC Channel  28");
    setupLocalPlot (subRect29  , y0LB1_StripData, 29  , "RPC Channel  29");
    setupLocalPlot (subRect30  , y0LB1_StripData, 30  , "RPC Channel  30");

    setupLocalPlot (subRect31  , y0LB1_StripData, 31  , "RPC Channel  31");
    setupLocalPlot (subRect32  , y0LB1_StripData, 32  , "RPC Channel  32");
    setupLocalPlot (subRect33  , y0LB1_StripData, 33  , "RPC Channel  33");
    setupLocalPlot (subRect34  , y0LB1_StripData, 34  , "RPC Channel  34");
    setupLocalPlot (subRect35  , y0LB1_StripData, 35  , "RPC Channel  35");
    setupLocalPlot (subRect36  , y0LB1_StripData, 36  , "RPC Channel  36");

    setupLocalPlot (subRect37  , y0LB1_StripData, 37  , "RPC Channel  37");
    setupLocalPlot (subRect38  , y0LB1_StripData, 38  , "RPC Channel  38");
    setupLocalPlot (subRect39  , y0LB1_StripData, 39  , "RPC Channel  39");
    setupLocalPlot (subRect40  , y0LB1_StripData, 40  , "RPC Channel  40");
    setupLocalPlot (subRect41  , y0LB1_StripData, 41  , "RPC Channel  41");
    setupLocalPlot (subRect42  , y0LB1_StripData, 42  , "RPC Channel  42");

    setupLocalPlot (subRect43  , y0LB1_StripData, 43  , "RPC Channel  43");
    setupLocalPlot (subRect44  , y0LB1_StripData, 44  , "RPC Channel  44");
    setupLocalPlot (subRect45  , y0LB1_StripData, 45  , "RPC Channel  45");
    setupLocalPlot (subRect46  , y0LB1_StripData, 46  , "RPC Channel  46");
    setupLocalPlot (subRect47  , y0LB1_StripData, 47  , "RPC Channel  47");
    setupLocalPlot (subRect48  , y0LB1_StripData, 48  , "RPC Channel  48");

    setupLocalPlot (subRect49  , y0LB1_StripData, 49  , "RPC Channel  49");
    setupLocalPlot (subRect50  , y0LB1_StripData, 50  , "RPC Channel  50");
    setupLocalPlot (subRect51  , y0LB1_StripData, 51  , "RPC Channel  51");
    setupLocalPlot (subRect52  , y0LB1_StripData, 52  , "RPC Channel  52");
    setupLocalPlot (subRect53  , y0LB1_StripData, 53  , "RPC Channel  53");
    setupLocalPlot (subRect54  , y0LB1_StripData, 54  , "RPC Channel  54");

    setupLocalPlot (subRect55  , y0LB1_StripData, 55  , "RPC Channel  55");
    setupLocalPlot (subRect56  , y0LB1_StripData, 56  , "RPC Channel  56");
    setupLocalPlot (subRect57  , y0LB1_StripData, 57  , "RPC Channel  57");
    setupLocalPlot (subRect58  , y0LB1_StripData, 58  , "RPC Channel  58");
    setupLocalPlot (subRect59  , y0LB1_StripData, 59  , "RPC Channel  59");
    setupLocalPlot (subRect60  , y0LB1_StripData, 60  , "RPC Channel  60");

    setupLocalPlot (subRect61  , y0LB1_StripData, 61  , "RPC Channel  61");
    setupLocalPlot (subRect62  , y0LB1_StripData, 62  , "RPC Channel  62");
    setupLocalPlot (subRect63  , y0LB1_StripData, 62  , "RPC Channel  63");
    setupLocalPlot (subRect64  , y0LB1_StripData, 64  , "RPC Channel  64");
    setupLocalPlot (subRect65  , y0LB1_StripData, 65  , "RPC Channel  65");
    setupLocalPlot (subRect66  , y0LB1_StripData, 66  , "RPC Channel  66");

    setupLocalPlot (subRect67  , y0LB1_StripData, 67  , "RPC Channel  67");
    setupLocalPlot (subRect68  , y0LB1_StripData, 68  , "RPC Channel  68");
    setupLocalPlot (subRect69  , y0LB1_StripData, 69  , "RPC Channel  69");
    setupLocalPlot (subRect70  , y0LB1_StripData, 70  , "RPC Channel  70");
    setupLocalPlot (subRect71  , y0LB1_StripData, 71  , "RPC Channel  71");
    setupLocalPlot (subRect72  , y0LB1_StripData, 72  , "RPC Channel  72");

    setupLocalPlot (subRect73  , y0LB1_StripData, 73  , "RPC Channel  73");
    setupLocalPlot (subRect74  , y0LB1_StripData, 74  , "RPC Channel  74");
    setupLocalPlot (subRect75  , y0LB1_StripData, 75  , "RPC Channel  75");
    setupLocalPlot (subRect76  , y0LB1_StripData, 76  , "RPC Channel  76");
    setupLocalPlot (subRect77  , y0LB1_StripData, 77  , "RPC Channel  77");
    setupLocalPlot (subRect78  , y0LB1_StripData, 78  , "RPC Channel  78");

    setupLocalPlot (subRect79  , y0LB1_StripData, 79  , "RPC Channel  79");
    setupLocalPlot (subRect80  , y0LB1_StripData, 80  , "RPC Channel  80");
    setupLocalPlot (subRect81  , y0LB1_StripData, 81  , "RPC Channel  81");
    setupLocalPlot (subRect82  , y0LB1_StripData, 82  , "RPC Channel  82");
    setupLocalPlot (subRect83  , y0LB1_StripData, 83  , "RPC Channel  83");
    setupLocalPlot (subRect84  , y0LB1_StripData, 84  , "RPC Channel  84");

    setupLocalPlot (subRect85  , y0LB1_StripData, 85  , "RPC Channel  85");
    setupLocalPlot (subRect86  , y0LB1_StripData, 86  , "RPC Channel  86");
    setupLocalPlot (subRect87  , y0LB1_StripData, 87  , "RPC Channel  87");
    setupLocalPlot (subRect88  , y0LB1_StripData, 88  , "RPC Channel  88");
    setupLocalPlot (subRect89  , y0LB1_StripData, 89  , "RPC Channel  89");
    setupLocalPlot (subRect90  , y0LB1_StripData, 90  , "RPC Channel  90");

    setupLocalPlot (subRect91  , y0LB1_StripData, 91  , "RPC Channel  91");
    setupLocalPlot (subRect92  , y0LB1_StripData, 92  , "RPC Channel  92");
    setupLocalPlot (subRect93  , y0LB1_StripData, 93  , "RPC Channel  93");
    setupLocalPlot (subRect94  , y0LB1_StripData, 94  , "RPC Channel  94");
    setupLocalPlot (subRect95  , y0LB1_StripData, 95  , "RPC Channel  95");
    setupLocalPlot (subRect96  , y0LB1_StripData, 96  , "RPC Channel  96");



    connect(ui->plot_CB, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->plot_CB, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel(QWheelEvent*)));
    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->plot_CB->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_CB->xAxis, SLOT(setRange(QCPRange)));
    connect(ui->plot_CB->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_CB->yAxis, SLOT(setRange(QCPRange)));

    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 8);
    //ui->plot_LB1->replot()->setRowStretchFactor(1, 0.001);

    //connect(wideAxisRect, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

}



void realtimev2::setupPlot_LB(unsigned int LBM){

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
void realtimev2::setupPlot_LB1(void){


    //QVector <double> y1_FullWinChannel (200);
    //QVector <double> y1_AdjWinChannel (200);

    //QVector <double> x1_stripFulW (200);
    //QVector <double> x1_stripAdjW (200);
    //unsigned int stripNum ;


    // configure axis rect:
    ui->plot_LB1->plotLayout()->clear(); // clear default axis rect so we can start from scratch
    /*
    QCPAxisRect *wideAxisRect = new QCPAxisRect(ui->plot_LB1);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers
    */

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;

    ui->plot_LB1->plotLayout()->addElement(0, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
    //ui->plot_LB1->setInteractions( QCP::iRangeZoom | QCP::iSelectPlottables);
    //ui->plot_LB1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // prepare axis rects that will be placed in the sublayout:
    QCPAxisRect *subRect1 = new QCPAxisRect(ui->plot_LB1, false); // false means to not setup default axes
    QCPAxisRect *subRect2 = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect3 = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect4 = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect5 = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect6 = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect7 = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect8 = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect9 = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect10 = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect11 = new QCPAxisRect(ui->plot_LB1, false); // false means to not setup default axes
    QCPAxisRect *subRect12 = new QCPAxisRect(ui->plot_LB1, false);

    QCPAxisRect *subRect13  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect14  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect15  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect16  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect17  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect18  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect19  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect20  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect21  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect22  = new QCPAxisRect(ui->plot_LB1, false);


    QCPAxisRect *subRect23  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect24  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect25  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect26  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect27  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect28  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect29  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect30  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect31  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect32  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect33  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect34  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect35  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect36  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect37  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect38  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect39  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect40  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect41  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect42  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect43  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect44  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect45  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect46  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect47  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect48  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect49  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect50  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect51  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect52  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect53  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect54  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect55  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect56  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect57  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect58  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect59  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect60  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect61  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect62  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect63  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect64  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect65  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect66  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect67  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect68  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect69  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect70  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect71  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect72  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect73  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect74  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect75  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect76  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect77  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect78  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect79  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect80  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect81  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect82  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect83  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect84  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect85  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect86  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect87  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect88  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect89  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect90  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect91  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect92  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect93  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect94  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect95  = new QCPAxisRect(ui->plot_LB1, false);
    QCPAxisRect *subRect96  = new QCPAxisRect(ui->plot_LB1, false);



    subLayout->addElement(0, 0, subRect1);
    subLayout->addElement(1, 0, subRect2);
    subLayout->addElement(2, 0, subRect3);
    subLayout->addElement(3, 0, subRect4);
    subLayout->addElement(4, 0, subRect5);
    subLayout->addElement(5, 0, subRect6);

    subLayout->addElement(6, 0, subRect7);
    subLayout->addElement(7, 0, subRect8);
    subLayout->addElement(8, 0, subRect9);
    subLayout->addElement(9, 0, subRect10);
    subLayout->addElement(10, 0, subRect11);
    subLayout->addElement(11, 0, subRect12);


    subLayout->addElement( 12, 0, subRect13 );
    subLayout->addElement( 13, 0, subRect14 );
    subLayout->addElement( 14, 0, subRect15 );
    subLayout->addElement( 15, 0, subRect16 );
    subLayout->addElement( 16, 0, subRect17 );
    subLayout->addElement( 17, 0, subRect18 );

    subLayout->addElement( 18, 0, subRect19 );
    subLayout->addElement( 19, 0, subRect20 );
    subLayout->addElement( 20, 0, subRect21 );
    subLayout->addElement( 21, 0, subRect22 );
    subLayout->addElement( 22, 0, subRect23 );
    subLayout->addElement( 23, 0, subRect24 );

    subLayout->addElement( 24, 0, subRect25 );
    subLayout->addElement( 25, 0, subRect26 );
    subLayout->addElement( 26, 0, subRect27 );
    subLayout->addElement( 27, 0, subRect28 );
    subLayout->addElement( 28, 0, subRect29 );
    subLayout->addElement( 29, 0, subRect30 );

    subLayout->addElement( 30, 0, subRect31 );
    subLayout->addElement( 31, 0, subRect32 );
    subLayout->addElement( 32, 0, subRect33 );
    subLayout->addElement( 33, 0, subRect34 );
    subLayout->addElement( 34, 0, subRect35 );
    subLayout->addElement( 35, 0, subRect36 );

    subLayout->addElement( 36, 0, subRect37 );
    subLayout->addElement( 37, 0, subRect38 );
    subLayout->addElement( 38, 0, subRect39 );
    subLayout->addElement( 39, 0, subRect40 );
    subLayout->addElement( 40, 0, subRect41 );
    subLayout->addElement( 41, 0, subRect42 );

    subLayout->addElement( 42, 0, subRect43 );
    subLayout->addElement( 43, 0, subRect44 );
    subLayout->addElement( 44, 0, subRect45 );
    subLayout->addElement( 45, 0, subRect46 );
    subLayout->addElement( 46, 0, subRect47 );
    subLayout->addElement( 47, 0, subRect48 );

    subLayout->addElement( 48, 0, subRect49 );
    subLayout->addElement( 49, 0, subRect50 );
    subLayout->addElement( 50, 0, subRect51 );
    subLayout->addElement( 51, 0, subRect52 );
    subLayout->addElement( 52, 0, subRect53 );
    subLayout->addElement( 53, 0, subRect54 );

    subLayout->addElement( 54, 0, subRect55 );
    subLayout->addElement( 55, 0, subRect56 );
    subLayout->addElement( 56, 0, subRect57 );
    subLayout->addElement( 57, 0, subRect58 );
    subLayout->addElement( 58, 0, subRect59 );
    subLayout->addElement( 59, 0, subRect60 );

    subLayout->addElement( 60, 0, subRect61 );
    subLayout->addElement( 61, 0, subRect62 );
    subLayout->addElement( 62, 0, subRect63 );
    subLayout->addElement( 63, 0, subRect64 );
    subLayout->addElement( 64, 0, subRect65 );
    subLayout->addElement( 65, 0, subRect66 );

    subLayout->addElement( 66, 0, subRect67 );
    subLayout->addElement( 67, 0, subRect68 );
    subLayout->addElement( 68, 0, subRect69 );
    subLayout->addElement( 69, 0, subRect70 );
    subLayout->addElement( 70, 0, subRect71 );
    subLayout->addElement( 71, 0, subRect72 );

    subLayout->addElement( 72, 0, subRect73 );
    subLayout->addElement( 73, 0, subRect74 );
    subLayout->addElement( 74, 0, subRect75 );
    subLayout->addElement( 75, 0, subRect76 );
    subLayout->addElement( 76, 0, subRect77);
    subLayout->addElement( 77, 0, subRect78 );

    subLayout->addElement( 78, 0, subRect79 );
    subLayout->addElement( 79, 0, subRect80 );
    subLayout->addElement( 80, 0, subRect81 );
    subLayout->addElement( 81, 0, subRect82 );
    subLayout->addElement( 82, 0, subRect83 );
    subLayout->addElement( 83, 0, subRect84 );

    subLayout->addElement( 84, 0, subRect85 );
    subLayout->addElement( 85, 0, subRect86 );
    subLayout->addElement( 86, 0, subRect87 );
    subLayout->addElement( 87, 0, subRect88 );
    subLayout->addElement( 88, 0, subRect89 );
    subLayout->addElement( 89, 0, subRect90 );

    subLayout->addElement( 90, 0, subRect91 );
    subLayout->addElement( 91, 0, subRect92 );
    subLayout->addElement( 92, 0, subRect93 );
    subLayout->addElement( 93, 0, subRect94 );
    subLayout->addElement( 94, 0, subRect95 );
    subLayout->addElement( 95, 0, subRect96 );


    // setup axes in sub layout axis rects:
    subRect1->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    //subRect1->axis(QCPAxis::atBottom)->ticker()->setTickCount(2);
    subRect1->axis(QCPAxis::atBottom)->grid()->setVisible(true);

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

    subRect22 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect22 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect23 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect23 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect24 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect24 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect25 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect25 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect26 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect26 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect27 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect27 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect28 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect28 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect29 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect29 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect30 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect30 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect31 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect31 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect32 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect32 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect33 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect33 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect34 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect34 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect35 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect35 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect36 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect36 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect37 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect37 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect38 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect38 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect39 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect39 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect40 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect40 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect41 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect41 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect42 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect42 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect43 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect43 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect44 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect44 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect45 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect45 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect46 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect46 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect47 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect47 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect48 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect48 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect49 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect49 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect50 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect50 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect51 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect51 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect52 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect52 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect53 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect53 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect54 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect54 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect55 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect55 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect56 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect56 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect57 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect57 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect58 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect58 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect59 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect59 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect60 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect60 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect61 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect61 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect62 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect62 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect63 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect63 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect64 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect64 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect65 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect65 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect66 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect66 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect67 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect67 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect68 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect68 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect69 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect69 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect70 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect70 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect71 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect71 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect72 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect72 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect73 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect73 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect74 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect74 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect75 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect75 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect76 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect76 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect77 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect77 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect78 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect78 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect79 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect79 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect80 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect80 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect81 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect81 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect82 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect82 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect83 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect83 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect84 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect84 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect85 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect85 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect86 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect86 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect87 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect87 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect88 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect88 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect89 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect89 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect90 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect90 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect91 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect91 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect92 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect92 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect93 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect93 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect94 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect94 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect95 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect95 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect96 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect96 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);



    // synchronize the left and right margins of the top and bottom axis rects:
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot_LB1);

    subRect1->setMarginGroup(QCP::msBottom, marginGroup);
    subRect2->setMarginGroup(QCP::msBottom, marginGroup);
    subRect3->setMarginGroup(QCP::msBottom, marginGroup);
    subRect4->setMarginGroup(QCP::msBottom, marginGroup);
    subRect5->setMarginGroup(QCP::msBottom, marginGroup);
    subRect6->setMarginGroup(QCP::msBottom, marginGroup);
    subRect7->setMarginGroup(QCP::msBottom, marginGroup);
    subRect8->setMarginGroup(QCP::msBottom, marginGroup);
    subRect9->setMarginGroup(QCP::msBottom, marginGroup);
    subRect10->setMarginGroup(QCP::msBottom, marginGroup);
    subRect11->setMarginGroup(QCP::msBottom, marginGroup);
    subRect12->setMarginGroup(QCP::msBottom, marginGroup);

    subRect13  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect14  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect15  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect16  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect17  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect18  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect19  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect20  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect21  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect22  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect23  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect24  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect25  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect26  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect27  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect28  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect29  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect30  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect31  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect32  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect33  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect34  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect35  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect36  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect37  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect38  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect39  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect40  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect41  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect42  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect43  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect44  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect45  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect46  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect47  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect48  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect49  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect50  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect51  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect52  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect53  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect54  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect55  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect56  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect57  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect58  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect59  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect60  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect61  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect62  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect63  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect64  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect65  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect66  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect67  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect68  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect69  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect70  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect71  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect72  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect73  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect74  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect75  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect76  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect77  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect78  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect79  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect80  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect81  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect82  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect83  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect84  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect85  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect86  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect87  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect88  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect89  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect90  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect91  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect92  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect93  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect94  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect95  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect96  ->setMarginGroup(QCP::msBottom, marginGroup);




    //wideAxisRect->setMarginGroup(QCP::msTop | QCP::msBottom | QCP::msRight | QCP::msLeft, marginGroup);


    // move newly created axes on "axes" layer and grids on "grid" layer:

    foreach (QCPAxisRect *rect, ui->plot_LB1->axisRects())
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
    ui->plot_LB1->setBackground(QBrush(gradient));
    //==================================================================
    //
    //==================================================================




    setupLocalPlot (subRect1  , y0LB1_StripData, 1 , "RPC Channel  1");
    setupLocalPlot (subRect2  , y0LB1_StripData, 2 , "RPC Channel  2");
    setupLocalPlot (subRect3  , y0LB1_StripData, 3 , "RPC Channel  3");
    setupLocalPlot (subRect4  , y0LB1_StripData, 4 , "RPC Channel  4");
    setupLocalPlot (subRect5  , y0LB1_StripData, 5 , "RPC Channel  5");
    setupLocalPlot (subRect6  , y0LB1_StripData,  6 , "RPC Channel  6");

    setupLocalPlot (subRect7  , y0LB1_StripData,  7 , "RPC Channel  7");
    setupLocalPlot (subRect8  , y0LB1_StripData,  8 , "RPC Channel  8");
    setupLocalPlot (subRect9  , y0LB1_StripData,  9 , "RPC Channel  9");
    setupLocalPlot (subRect10 , y0LB1_StripData,  10 , "RPC Channel  10");
    setupLocalPlot (subRect11 , y0LB1_StripData,  11 , "RPC Channel  11");
    setupLocalPlot (subRect12 , y0LB1_StripData,  12 , "RPC Channel  12");

    setupLocalPlot (subRect13  , y0LB1_StripData,  13  , "RPC Channel 13");
    setupLocalPlot (subRect14  , y0LB1_StripData,  14  , "RPC Channel 14");
    setupLocalPlot (subRect15  , y0LB1_StripData,  15  , "RPC Channel 15");
    setupLocalPlot (subRect16  , y0LB1_StripData,  16  , "RPC Channel 16");
    setupLocalPlot (subRect17  , y0LB1_StripData, 17  , "RPC Channel 17");
    setupLocalPlot (subRect18  , y0LB1_StripData, 18  , "RPC Channel 18");

    setupLocalPlot (subRect19  , y0LB1_StripData, 19  , "RPC Channel 19");
    setupLocalPlot (subRect20  , y0LB1_StripData,  20 , "RPC Channel  20");
    setupLocalPlot (subRect21  , y0LB1_StripData, 21  , "RPC Channel  21");
    setupLocalPlot (subRect22  , y0LB1_StripData, 22  , "RPC Channel  22");
    setupLocalPlot (subRect23  , y0LB1_StripData, 23  , "RPC Channel  23");
    setupLocalPlot (subRect24  , y0LB1_StripData, 24  , "RPC Channel  24");

    setupLocalPlot (subRect25  , y0LB1_StripData, 25  , "RPC Channel  25");
    setupLocalPlot (subRect26  , y0LB1_StripData, 26  , "RPC Channel  26");
    setupLocalPlot (subRect27  , y0LB1_StripData, 27  , "RPC Channel  27");
    setupLocalPlot (subRect28  , y0LB1_StripData, 28  , "RPC Channel  28");
    setupLocalPlot (subRect29  , y0LB1_StripData, 29  , "RPC Channel  29");
    setupLocalPlot (subRect30  , y0LB1_StripData, 30  , "RPC Channel  30");

    setupLocalPlot (subRect31  , y0LB1_StripData, 31  , "RPC Channel  31");
    setupLocalPlot (subRect32  , y0LB1_StripData, 32  , "RPC Channel  32");
    setupLocalPlot (subRect33  , y0LB1_StripData, 33  , "RPC Channel  33");
    setupLocalPlot (subRect34  , y0LB1_StripData, 34  , "RPC Channel  34");
    setupLocalPlot (subRect35  , y0LB1_StripData, 35  , "RPC Channel  35");
    setupLocalPlot (subRect36  , y0LB1_StripData, 36  , "RPC Channel  36");

    setupLocalPlot (subRect37  , y0LB1_StripData, 37  , "RPC Channel  37");
    setupLocalPlot (subRect38  , y0LB1_StripData, 38  , "RPC Channel  38");
    setupLocalPlot (subRect39  , y0LB1_StripData, 39  , "RPC Channel  39");
    setupLocalPlot (subRect40  , y0LB1_StripData, 40  , "RPC Channel  40");
    setupLocalPlot (subRect41  , y0LB1_StripData, 41  , "RPC Channel  41");
    setupLocalPlot (subRect42  , y0LB1_StripData, 42  , "RPC Channel  42");

    setupLocalPlot (subRect43  , y0LB1_StripData, 43  , "RPC Channel  43");
    setupLocalPlot (subRect44  , y0LB1_StripData, 44  , "RPC Channel  44");
    setupLocalPlot (subRect45  , y0LB1_StripData, 45  , "RPC Channel  45");
    setupLocalPlot (subRect46  , y0LB1_StripData, 46  , "RPC Channel  46");
    setupLocalPlot (subRect47  , y0LB1_StripData, 47  , "RPC Channel  47");
    setupLocalPlot (subRect48  , y0LB1_StripData, 48  , "RPC Channel  48");

    setupLocalPlot (subRect49  , y0LB1_StripData, 49  , "RPC Channel  49");
    setupLocalPlot (subRect50  , y0LB1_StripData, 50  , "RPC Channel  50");
    setupLocalPlot (subRect51  , y0LB1_StripData, 51  , "RPC Channel  51");
    setupLocalPlot (subRect52  , y0LB1_StripData, 52  , "RPC Channel  52");
    setupLocalPlot (subRect53  , y0LB1_StripData, 53  , "RPC Channel  53");
    setupLocalPlot (subRect54  , y0LB1_StripData, 54  , "RPC Channel  54");

    setupLocalPlot (subRect55  , y0LB1_StripData, 55  , "RPC Channel  55");
    setupLocalPlot (subRect56  , y0LB1_StripData, 56  , "RPC Channel  56");
    setupLocalPlot (subRect57  , y0LB1_StripData, 57  , "RPC Channel  57");
    setupLocalPlot (subRect58  , y0LB1_StripData, 58  , "RPC Channel  58");
    setupLocalPlot (subRect59  , y0LB1_StripData, 59  , "RPC Channel  59");
    setupLocalPlot (subRect60  , y0LB1_StripData, 60  , "RPC Channel  60");

    setupLocalPlot (subRect61  , y0LB1_StripData, 61  , "RPC Channel  61");
    setupLocalPlot (subRect62  , y0LB1_StripData, 62  , "RPC Channel  62");
    setupLocalPlot (subRect63  , y0LB1_StripData, 62  , "RPC Channel  63");
    setupLocalPlot (subRect64  , y0LB1_StripData, 64  , "RPC Channel  64");
    setupLocalPlot (subRect65  , y0LB1_StripData, 65  , "RPC Channel  65");
    setupLocalPlot (subRect66  , y0LB1_StripData, 66  , "RPC Channel  66");

    setupLocalPlot (subRect67  , y0LB1_StripData, 67  , "RPC Channel  67");
    setupLocalPlot (subRect68  , y0LB1_StripData, 68  , "RPC Channel  68");
    setupLocalPlot (subRect69  , y0LB1_StripData, 69  , "RPC Channel  69");
    setupLocalPlot (subRect70  , y0LB1_StripData, 70  , "RPC Channel  70");
    setupLocalPlot (subRect71  , y0LB1_StripData, 71  , "RPC Channel  71");
    setupLocalPlot (subRect72  , y0LB1_StripData, 72  , "RPC Channel  72");

    setupLocalPlot (subRect73  , y0LB1_StripData, 73  , "RPC Channel  73");
    setupLocalPlot (subRect74  , y0LB1_StripData, 74  , "RPC Channel  74");
    setupLocalPlot (subRect75  , y0LB1_StripData, 75  , "RPC Channel  75");
    setupLocalPlot (subRect76  , y0LB1_StripData, 76  , "RPC Channel  76");
    setupLocalPlot (subRect77  , y0LB1_StripData, 77  , "RPC Channel  77");
    setupLocalPlot (subRect78  , y0LB1_StripData, 78  , "RPC Channel  78");

    setupLocalPlot (subRect79  , y0LB1_StripData, 79  , "RPC Channel  79");
    setupLocalPlot (subRect80  , y0LB1_StripData, 80  , "RPC Channel  80");
    setupLocalPlot (subRect81  , y0LB1_StripData, 81  , "RPC Channel  81");
    setupLocalPlot (subRect82  , y0LB1_StripData, 82  , "RPC Channel  82");
    setupLocalPlot (subRect83  , y0LB1_StripData, 83  , "RPC Channel  83");
    setupLocalPlot (subRect84  , y0LB1_StripData, 84  , "RPC Channel  84");

    setupLocalPlot (subRect85  , y0LB1_StripData, 85  , "RPC Channel  85");
    setupLocalPlot (subRect86  , y0LB1_StripData, 86  , "RPC Channel  86");
    setupLocalPlot (subRect87  , y0LB1_StripData, 87  , "RPC Channel  87");
    setupLocalPlot (subRect88  , y0LB1_StripData, 88  , "RPC Channel  88");
    setupLocalPlot (subRect89  , y0LB1_StripData, 89  , "RPC Channel  89");
    setupLocalPlot (subRect90  , y0LB1_StripData, 90  , "RPC Channel  90");

    setupLocalPlot (subRect91  , y0LB1_StripData, 91  , "RPC Channel  91");
    setupLocalPlot (subRect92  , y0LB1_StripData, 92  , "RPC Channel  92");
    setupLocalPlot (subRect93  , y0LB1_StripData, 93  , "RPC Channel  93");
    setupLocalPlot (subRect94  , y0LB1_StripData, 94  , "RPC Channel  94");
    setupLocalPlot (subRect95  , y0LB1_StripData, 95  , "RPC Channel  95");
    setupLocalPlot (subRect96  , y0LB1_StripData, 96  , "RPC Channel  96");


    connect(ui->plot_LB1, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->plot_LB1, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel(QWheelEvent*)));
    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->plot_LB1->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_LB1->xAxis, SLOT(setRange(QCPRange)));
    connect(ui->plot_LB1->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_LB1->yAxis, SLOT(setRange(QCPRange)));

    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 9);

    ui->plot_LB1->replot();


}
//=================================================


//=================================================
void realtimev2::setupPlot_LB2(void){


    //QVector <double> y1_FullWinChannel (200);
    //QVector <double> y1_AdjWinChannel (200);

    //QVector <double> x1_stripFulW (200);
    //QVector <double> x1_stripAdjW (200);
    //unsigned int stripNum ;


    // configure axis rect:
    ui->plot_LB2->plotLayout()->clear(); // clear default axis rect so we can start from scratch
    /*
    QCPAxisRect *wideAxisRect = new QCPAxisRect(ui->plot_LB2);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers
    */

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;

    ui->plot_LB2->plotLayout()->addElement(0, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
    //ui->plot_LB2->setInteractions( QCP::iRangeZoom | QCP::iSelectPlottables);
    //ui->plot_LB2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // prepare axis rects that will be placed in the sublayout:
    QCPAxisRect *subRect1 = new QCPAxisRect(ui->plot_LB2, false); // false means to not setup default axes
    QCPAxisRect *subRect2 = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect3 = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect4 = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect5 = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect6 = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect7 = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect8 = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect9 = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect10 = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect11 = new QCPAxisRect(ui->plot_LB2, false); // false means to not setup default axes
    QCPAxisRect *subRect12 = new QCPAxisRect(ui->plot_LB2, false);

    QCPAxisRect *subRect13  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect14  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect15  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect16  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect17  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect18  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect19  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect20  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect21  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect22  = new QCPAxisRect(ui->plot_LB2, false);


    QCPAxisRect *subRect23  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect24  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect25  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect26  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect27  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect28  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect29  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect30  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect31  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect32  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect33  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect34  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect35  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect36  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect37  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect38  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect39  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect40  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect41  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect42  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect43  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect44  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect45  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect46  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect47  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect48  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect49  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect50  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect51  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect52  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect53  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect54  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect55  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect56  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect57  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect58  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect59  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect60  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect61  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect62  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect63  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect64  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect65  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect66  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect67  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect68  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect69  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect70  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect71  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect72  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect73  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect74  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect75  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect76  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect77  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect78  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect79  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect80  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect81  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect82  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect83  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect84  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect85  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect86  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect87  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect88  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect89  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect90  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect91  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect92  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect93  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect94  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect95  = new QCPAxisRect(ui->plot_LB2, false);
    QCPAxisRect *subRect96  = new QCPAxisRect(ui->plot_LB2, false);



    subLayout->addElement(0, 0, subRect1);
    subLayout->addElement(1, 0, subRect2);
    subLayout->addElement(2, 0, subRect3);
    subLayout->addElement(3, 0, subRect4);
    subLayout->addElement(4, 0, subRect5);
    subLayout->addElement(5, 0, subRect6);

    subLayout->addElement(6, 0, subRect7);
    subLayout->addElement(7, 0, subRect8);
    subLayout->addElement(8, 0, subRect9);
    subLayout->addElement(9, 0, subRect10);
    subLayout->addElement(10, 0, subRect11);
    subLayout->addElement(11, 0, subRect12);


    subLayout->addElement( 12, 0, subRect13 );
    subLayout->addElement( 13, 0, subRect14 );
    subLayout->addElement( 14, 0, subRect15 );
    subLayout->addElement( 15, 0, subRect16 );
    subLayout->addElement( 16, 0, subRect17 );
    subLayout->addElement( 17, 0, subRect18 );

    subLayout->addElement( 18, 0, subRect19 );
    subLayout->addElement( 19, 0, subRect20 );
    subLayout->addElement( 20, 0, subRect21 );
    subLayout->addElement( 21, 0, subRect22 );
    subLayout->addElement( 22, 0, subRect23 );
    subLayout->addElement( 23, 0, subRect24 );

    subLayout->addElement( 24, 0, subRect25 );
    subLayout->addElement( 25, 0, subRect26 );
    subLayout->addElement( 26, 0, subRect27 );
    subLayout->addElement( 27, 0, subRect28 );
    subLayout->addElement( 28, 0, subRect29 );
    subLayout->addElement( 29, 0, subRect30 );

    subLayout->addElement( 30, 0, subRect31 );
    subLayout->addElement( 31, 0, subRect32 );
    subLayout->addElement( 32, 0, subRect33 );
    subLayout->addElement( 33, 0, subRect34 );
    subLayout->addElement( 34, 0, subRect35 );
    subLayout->addElement( 35, 0, subRect36 );

    subLayout->addElement( 36, 0, subRect37 );
    subLayout->addElement( 37, 0, subRect38 );
    subLayout->addElement( 38, 0, subRect39 );
    subLayout->addElement( 39, 0, subRect40 );
    subLayout->addElement( 40, 0, subRect41 );
    subLayout->addElement( 41, 0, subRect42 );

    subLayout->addElement( 42, 0, subRect43 );
    subLayout->addElement( 43, 0, subRect44 );
    subLayout->addElement( 44, 0, subRect45 );
    subLayout->addElement( 45, 0, subRect46 );
    subLayout->addElement( 46, 0, subRect47 );
    subLayout->addElement( 47, 0, subRect48 );

    subLayout->addElement( 48, 0, subRect49 );
    subLayout->addElement( 49, 0, subRect50 );
    subLayout->addElement( 50, 0, subRect51 );
    subLayout->addElement( 51, 0, subRect52 );
    subLayout->addElement( 52, 0, subRect53 );
    subLayout->addElement( 53, 0, subRect54 );

    subLayout->addElement( 54, 0, subRect55 );
    subLayout->addElement( 55, 0, subRect56 );
    subLayout->addElement( 56, 0, subRect57 );
    subLayout->addElement( 57, 0, subRect58 );
    subLayout->addElement( 58, 0, subRect59 );
    subLayout->addElement( 59, 0, subRect60 );

    subLayout->addElement( 60, 0, subRect61 );
    subLayout->addElement( 61, 0, subRect62 );
    subLayout->addElement( 62, 0, subRect63 );
    subLayout->addElement( 63, 0, subRect64 );
    subLayout->addElement( 64, 0, subRect65 );
    subLayout->addElement( 65, 0, subRect66 );

    subLayout->addElement( 66, 0, subRect67 );
    subLayout->addElement( 67, 0, subRect68 );
    subLayout->addElement( 68, 0, subRect69 );
    subLayout->addElement( 69, 0, subRect70 );
    subLayout->addElement( 70, 0, subRect71 );
    subLayout->addElement( 71, 0, subRect72 );

    subLayout->addElement( 72, 0, subRect73 );
    subLayout->addElement( 73, 0, subRect74 );
    subLayout->addElement( 74, 0, subRect75 );
    subLayout->addElement( 75, 0, subRect76 );
    subLayout->addElement( 76, 0, subRect77);
    subLayout->addElement( 77, 0, subRect78 );

    subLayout->addElement( 78, 0, subRect79 );
    subLayout->addElement( 79, 0, subRect80 );
    subLayout->addElement( 80, 0, subRect81 );
    subLayout->addElement( 81, 0, subRect82 );
    subLayout->addElement( 82, 0, subRect83 );
    subLayout->addElement( 83, 0, subRect84 );

    subLayout->addElement( 84, 0, subRect85 );
    subLayout->addElement( 85, 0, subRect86 );
    subLayout->addElement( 86, 0, subRect87 );
    subLayout->addElement( 87, 0, subRect88 );
    subLayout->addElement( 88, 0, subRect89 );
    subLayout->addElement( 89, 0, subRect90 );

    subLayout->addElement( 90, 0, subRect91 );
    subLayout->addElement( 91, 0, subRect92 );
    subLayout->addElement( 92, 0, subRect93 );
    subLayout->addElement( 93, 0, subRect94 );
    subLayout->addElement( 94, 0, subRect95 );
    subLayout->addElement( 95, 0, subRect96 );


    // setup axes in sub layout axis rects:
    subRect1->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    //subRect1->axis(QCPAxis::atBottom)->ticker()->setTickCount(2);
    subRect1->axis(QCPAxis::atBottom)->grid()->setVisible(true);

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

    subRect22 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect22 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect23 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect23 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect24 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect24 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect25 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect25 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect26 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect26 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect27 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect27 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect28 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect28 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect29 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect29 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect30 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect30 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect31 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect31 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect32 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect32 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect33 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect33 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect34 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect34 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect35 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect35 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect36 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect36 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect37 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect37 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect38 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect38 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect39 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect39 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect40 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect40 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect41 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect41 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect42 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect42 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect43 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect43 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect44 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect44 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect45 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect45 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect46 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect46 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect47 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect47 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect48 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect48 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect49 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect49 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect50 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect50 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect51 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect51 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect52 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect52 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect53 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect53 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect54 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect54 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect55 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect55 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect56 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect56 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect57 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect57 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect58 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect58 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect59 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect59 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect60 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect60 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect61 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect61 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect62 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect62 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect63 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect63 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect64 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect64 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect65 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect65 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect66 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect66 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect67 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect67 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect68 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect68 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect69 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect69 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect70 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect70 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect71 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect71 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect72 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect72 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect73 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect73 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect74 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect74 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect75 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect75 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect76 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect76 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect77 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect77 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect78 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect78 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect79 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect79 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect80 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect80 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect81 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect81 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect82 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect82 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect83 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect83 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect84 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect84 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect85 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect85 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect86 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect86 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect87 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect87 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect88 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect88 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect89 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect89 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect90 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect90 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect91 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect91 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect92 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect92 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect93 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect93 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect94 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect94 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect95 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect95 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect96 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect96 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);



    // synchronize the left and right margins of the top and bottom axis rects:
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot_LB2);

    subRect1->setMarginGroup(QCP::msBottom, marginGroup);
    subRect2->setMarginGroup(QCP::msBottom, marginGroup);
    subRect3->setMarginGroup(QCP::msBottom, marginGroup);
    subRect4->setMarginGroup(QCP::msBottom, marginGroup);
    subRect5->setMarginGroup(QCP::msBottom, marginGroup);
    subRect6->setMarginGroup(QCP::msBottom, marginGroup);
    subRect7->setMarginGroup(QCP::msBottom, marginGroup);
    subRect8->setMarginGroup(QCP::msBottom, marginGroup);
    subRect9->setMarginGroup(QCP::msBottom, marginGroup);
    subRect10->setMarginGroup(QCP::msBottom, marginGroup);
    subRect11->setMarginGroup(QCP::msBottom, marginGroup);
    subRect12->setMarginGroup(QCP::msBottom, marginGroup);

    subRect13  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect14  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect15  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect16  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect17  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect18  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect19  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect20  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect21  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect22  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect23  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect24  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect25  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect26  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect27  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect28  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect29  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect30  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect31  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect32  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect33  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect34  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect35  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect36  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect37  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect38  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect39  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect40  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect41  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect42  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect43  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect44  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect45  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect46  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect47  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect48  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect49  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect50  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect51  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect52  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect53  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect54  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect55  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect56  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect57  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect58  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect59  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect60  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect61  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect62  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect63  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect64  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect65  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect66  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect67  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect68  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect69  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect70  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect71  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect72  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect73  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect74  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect75  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect76  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect77  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect78  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect79  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect80  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect81  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect82  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect83  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect84  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect85  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect86  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect87  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect88  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect89  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect90  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect91  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect92  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect93  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect94  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect95  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect96  ->setMarginGroup(QCP::msBottom, marginGroup);




    //wideAxisRect->setMarginGroup(QCP::msTop | QCP::msBottom | QCP::msRight | QCP::msLeft, marginGroup);


    // move newly created axes on "axes" layer and grids on "grid" layer:

    foreach (QCPAxisRect *rect, ui->plot_LB2->axisRects())
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
    ui->plot_LB2->setBackground(QBrush(gradient));
    //==================================================================
    //
    //==================================================================




    setupLocalPlot (subRect1  , y0LB2_StripData, 1 , "RPC Channel  1");
    setupLocalPlot (subRect2  , y0LB2_StripData, 2 , "RPC Channel  2");
    setupLocalPlot (subRect3  , y0LB2_StripData, 3 , "RPC Channel  3");
    setupLocalPlot (subRect4  , y0LB2_StripData, 4 , "RPC Channel  4");
    setupLocalPlot (subRect5  , y0LB2_StripData, 5 , "RPC Channel  5");
    setupLocalPlot (subRect6  , y0LB2_StripData,  6 , "RPC Channel  6");

    setupLocalPlot (subRect7  , y0LB2_StripData,  7 , "RPC Channel  7");
    setupLocalPlot (subRect8  , y0LB2_StripData,  8 , "RPC Channel  8");
    setupLocalPlot (subRect9  , y0LB2_StripData,  9 , "RPC Channel  9");
    setupLocalPlot (subRect10 , y0LB2_StripData,  10 , "RPC Channel  10");
    setupLocalPlot (subRect11 , y0LB2_StripData,  11 , "RPC Channel  11");
    setupLocalPlot (subRect12 , y0LB2_StripData,  12 , "RPC Channel  12");

    setupLocalPlot (subRect13  , y0LB2_StripData,  13  , "RPC Channel 13");
    setupLocalPlot (subRect14  , y0LB2_StripData,  14  , "RPC Channel 14");
    setupLocalPlot (subRect15  , y0LB2_StripData,  15  , "RPC Channel 15");
    setupLocalPlot (subRect16  , y0LB2_StripData,  16  , "RPC Channel 16");
    setupLocalPlot (subRect17  , y0LB2_StripData, 17  , "RPC Channel 17");
    setupLocalPlot (subRect18  , y0LB2_StripData, 18  , "RPC Channel 18");

    setupLocalPlot (subRect19  , y0LB2_StripData, 19  , "RPC Channel 19");
    setupLocalPlot (subRect20  , y0LB2_StripData,  20 , "RPC Channel  20");
    setupLocalPlot (subRect21  , y0LB2_StripData, 21  , "RPC Channel  21");
    setupLocalPlot (subRect22  , y0LB2_StripData, 22  , "RPC Channel  22");
    setupLocalPlot (subRect23  , y0LB2_StripData, 23  , "RPC Channel  23");
    setupLocalPlot (subRect24  , y0LB2_StripData, 24  , "RPC Channel  24");

    setupLocalPlot (subRect25  , y0LB2_StripData, 25  , "RPC Channel  25");
    setupLocalPlot (subRect26  , y0LB2_StripData, 26  , "RPC Channel  26");
    setupLocalPlot (subRect27  , y0LB2_StripData, 27  , "RPC Channel  27");
    setupLocalPlot (subRect28  , y0LB2_StripData, 28  , "RPC Channel  28");
    setupLocalPlot (subRect29  , y0LB2_StripData, 29  , "RPC Channel  29");
    setupLocalPlot (subRect30  , y0LB2_StripData, 30  , "RPC Channel  30");

    setupLocalPlot (subRect31  , y0LB2_StripData, 31  , "RPC Channel  31");
    setupLocalPlot (subRect32  , y0LB2_StripData, 32  , "RPC Channel  32");
    setupLocalPlot (subRect33  , y0LB2_StripData, 33  , "RPC Channel  33");
    setupLocalPlot (subRect34  , y0LB2_StripData, 34  , "RPC Channel  34");
    setupLocalPlot (subRect35  , y0LB2_StripData, 35  , "RPC Channel  35");
    setupLocalPlot (subRect36  , y0LB2_StripData, 36  , "RPC Channel  36");

    setupLocalPlot (subRect37  , y0LB2_StripData, 37  , "RPC Channel  37");
    setupLocalPlot (subRect38  , y0LB2_StripData, 38  , "RPC Channel  38");
    setupLocalPlot (subRect39  , y0LB2_StripData, 39  , "RPC Channel  39");
    setupLocalPlot (subRect40  , y0LB2_StripData, 40  , "RPC Channel  40");
    setupLocalPlot (subRect41  , y0LB2_StripData, 41  , "RPC Channel  41");
    setupLocalPlot (subRect42  , y0LB2_StripData, 42  , "RPC Channel  42");

    setupLocalPlot (subRect43  , y0LB2_StripData, 43  , "RPC Channel  43");
    setupLocalPlot (subRect44  , y0LB2_StripData, 44  , "RPC Channel  44");
    setupLocalPlot (subRect45  , y0LB2_StripData, 45  , "RPC Channel  45");
    setupLocalPlot (subRect46  , y0LB2_StripData, 46  , "RPC Channel  46");
    setupLocalPlot (subRect47  , y0LB2_StripData, 47  , "RPC Channel  47");
    setupLocalPlot (subRect48  , y0LB2_StripData, 48  , "RPC Channel  48");

    setupLocalPlot (subRect49  , y0LB2_StripData, 49  , "RPC Channel  49");
    setupLocalPlot (subRect50  , y0LB2_StripData, 50  , "RPC Channel  50");
    setupLocalPlot (subRect51  , y0LB2_StripData, 51  , "RPC Channel  51");
    setupLocalPlot (subRect52  , y0LB2_StripData, 52  , "RPC Channel  52");
    setupLocalPlot (subRect53  , y0LB2_StripData, 53  , "RPC Channel  53");
    setupLocalPlot (subRect54  , y0LB2_StripData, 54  , "RPC Channel  54");

    setupLocalPlot (subRect55  , y0LB2_StripData, 55  , "RPC Channel  55");
    setupLocalPlot (subRect56  , y0LB2_StripData, 56  , "RPC Channel  56");
    setupLocalPlot (subRect57  , y0LB2_StripData, 57  , "RPC Channel  57");
    setupLocalPlot (subRect58  , y0LB2_StripData, 58  , "RPC Channel  58");
    setupLocalPlot (subRect59  , y0LB2_StripData, 59  , "RPC Channel  59");
    setupLocalPlot (subRect60  , y0LB2_StripData, 60  , "RPC Channel  60");

    setupLocalPlot (subRect61  , y0LB2_StripData, 61  , "RPC Channel  61");
    setupLocalPlot (subRect62  , y0LB2_StripData, 62  , "RPC Channel  62");
    setupLocalPlot (subRect63  , y0LB2_StripData, 62  , "RPC Channel  63");
    setupLocalPlot (subRect64  , y0LB2_StripData, 64  , "RPC Channel  64");
    setupLocalPlot (subRect65  , y0LB2_StripData, 65  , "RPC Channel  65");
    setupLocalPlot (subRect66  , y0LB2_StripData, 66  , "RPC Channel  66");

    setupLocalPlot (subRect67  , y0LB2_StripData, 67  , "RPC Channel  67");
    setupLocalPlot (subRect68  , y0LB2_StripData, 68  , "RPC Channel  68");
    setupLocalPlot (subRect69  , y0LB2_StripData, 69  , "RPC Channel  69");
    setupLocalPlot (subRect70  , y0LB2_StripData, 70  , "RPC Channel  70");
    setupLocalPlot (subRect71  , y0LB2_StripData, 71  , "RPC Channel  71");
    setupLocalPlot (subRect72  , y0LB2_StripData, 72  , "RPC Channel  72");

    setupLocalPlot (subRect73  , y0LB2_StripData, 73  , "RPC Channel  73");
    setupLocalPlot (subRect74  , y0LB2_StripData, 74  , "RPC Channel  74");
    setupLocalPlot (subRect75  , y0LB2_StripData, 75  , "RPC Channel  75");
    setupLocalPlot (subRect76  , y0LB2_StripData, 76  , "RPC Channel  76");
    setupLocalPlot (subRect77  , y0LB2_StripData, 77  , "RPC Channel  77");
    setupLocalPlot (subRect78  , y0LB2_StripData, 78  , "RPC Channel  78");

    setupLocalPlot (subRect79  , y0LB2_StripData, 79  , "RPC Channel  79");
    setupLocalPlot (subRect80  , y0LB2_StripData, 80  , "RPC Channel  80");
    setupLocalPlot (subRect81  , y0LB2_StripData, 81  , "RPC Channel  81");
    setupLocalPlot (subRect82  , y0LB2_StripData, 82  , "RPC Channel  82");
    setupLocalPlot (subRect83  , y0LB2_StripData, 83  , "RPC Channel  83");
    setupLocalPlot (subRect84  , y0LB2_StripData, 84  , "RPC Channel  84");

    setupLocalPlot (subRect85  , y0LB2_StripData, 85  , "RPC Channel  85");
    setupLocalPlot (subRect86  , y0LB2_StripData, 86  , "RPC Channel  86");
    setupLocalPlot (subRect87  , y0LB2_StripData, 87  , "RPC Channel  87");
    setupLocalPlot (subRect88  , y0LB2_StripData, 88  , "RPC Channel  88");
    setupLocalPlot (subRect89  , y0LB2_StripData, 89  , "RPC Channel  89");
    setupLocalPlot (subRect90  , y0LB2_StripData, 90  , "RPC Channel  90");

    setupLocalPlot (subRect91  , y0LB2_StripData, 91  , "RPC Channel  91");
    setupLocalPlot (subRect92  , y0LB2_StripData, 92  , "RPC Channel  92");
    setupLocalPlot (subRect93  , y0LB2_StripData, 93  , "RPC Channel  93");
    setupLocalPlot (subRect94  , y0LB2_StripData, 94  , "RPC Channel  94");
    setupLocalPlot (subRect95  , y0LB2_StripData, 95  , "RPC Channel  95");
    setupLocalPlot (subRect96  , y0LB2_StripData, 96  , "RPC Channel  96");


    connect(ui->plot_LB2, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->plot_LB2, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel(QWheelEvent*)));
    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->plot_LB2->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_LB2->xAxis, SLOT(setRange(QCPRange)));
    connect(ui->plot_LB2->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_LB2->yAxis, SLOT(setRange(QCPRange)));

    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 8);

    ui->plot_LB2->replot();

}
//=================================================


//=================================================
void realtimev2::setupPlot_LB3(void){


    //QVector <double> y1_FullWinChannel (200);
    //QVector <double> y1_AdjWinChannel (200);

    //QVector <double> x1_stripFulW (200);
    //QVector <double> x1_stripAdjW (200);
    //unsigned int stripNum ;


    // configure axis rect:
    ui->plot_LB3->plotLayout()->clear(); // clear default axis rect so we can start from scratch
    /*
    QCPAxisRect *wideAxisRect = new QCPAxisRect(ui->plot_LB3);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers
    */

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;

    ui->plot_LB3->plotLayout()->addElement(0, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
    //ui->plot_LB3->setInteractions( QCP::iRangeZoom | QCP::iSelectPlottables);
    //ui->plot_LB3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // prepare axis rects that will be placed in the sublayout:
    QCPAxisRect *subRect1 = new QCPAxisRect(ui->plot_LB3, false); // false means to not setup default axes
    QCPAxisRect *subRect2 = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect3 = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect4 = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect5 = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect6 = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect7 = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect8 = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect9 = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect10 = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect11 = new QCPAxisRect(ui->plot_LB3, false); // false means to not setup default axes
    QCPAxisRect *subRect12 = new QCPAxisRect(ui->plot_LB3, false);

    QCPAxisRect *subRect13  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect14  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect15  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect16  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect17  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect18  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect19  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect20  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect21  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect22  = new QCPAxisRect(ui->plot_LB3, false);


    QCPAxisRect *subRect23  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect24  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect25  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect26  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect27  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect28  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect29  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect30  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect31  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect32  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect33  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect34  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect35  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect36  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect37  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect38  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect39  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect40  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect41  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect42  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect43  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect44  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect45  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect46  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect47  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect48  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect49  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect50  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect51  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect52  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect53  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect54  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect55  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect56  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect57  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect58  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect59  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect60  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect61  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect62  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect63  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect64  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect65  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect66  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect67  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect68  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect69  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect70  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect71  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect72  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect73  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect74  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect75  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect76  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect77  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect78  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect79  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect80  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect81  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect82  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect83  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect84  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect85  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect86  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect87  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect88  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect89  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect90  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect91  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect92  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect93  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect94  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect95  = new QCPAxisRect(ui->plot_LB3, false);
    QCPAxisRect *subRect96  = new QCPAxisRect(ui->plot_LB3, false);



    subLayout->addElement(0, 0, subRect1);
    subLayout->addElement(1, 0, subRect2);
    subLayout->addElement(2, 0, subRect3);
    subLayout->addElement(3, 0, subRect4);
    subLayout->addElement(4, 0, subRect5);
    subLayout->addElement(5, 0, subRect6);

    subLayout->addElement(6, 0, subRect7);
    subLayout->addElement(7, 0, subRect8);
    subLayout->addElement(8, 0, subRect9);
    subLayout->addElement(9, 0, subRect10);
    subLayout->addElement(10, 0, subRect11);
    subLayout->addElement(11, 0, subRect12);


    subLayout->addElement( 12, 0, subRect13 );
    subLayout->addElement( 13, 0, subRect14 );
    subLayout->addElement( 14, 0, subRect15 );
    subLayout->addElement( 15, 0, subRect16 );
    subLayout->addElement( 16, 0, subRect17 );
    subLayout->addElement( 17, 0, subRect18 );

    subLayout->addElement( 18, 0, subRect19 );
    subLayout->addElement( 19, 0, subRect20 );
    subLayout->addElement( 20, 0, subRect21 );
    subLayout->addElement( 21, 0, subRect22 );
    subLayout->addElement( 22, 0, subRect23 );
    subLayout->addElement( 23, 0, subRect24 );

    subLayout->addElement( 24, 0, subRect25 );
    subLayout->addElement( 25, 0, subRect26 );
    subLayout->addElement( 26, 0, subRect27 );
    subLayout->addElement( 27, 0, subRect28 );
    subLayout->addElement( 28, 0, subRect29 );
    subLayout->addElement( 29, 0, subRect30 );

    subLayout->addElement( 30, 0, subRect31 );
    subLayout->addElement( 31, 0, subRect32 );
    subLayout->addElement( 32, 0, subRect33 );
    subLayout->addElement( 33, 0, subRect34 );
    subLayout->addElement( 34, 0, subRect35 );
    subLayout->addElement( 35, 0, subRect36 );

    subLayout->addElement( 36, 0, subRect37 );
    subLayout->addElement( 37, 0, subRect38 );
    subLayout->addElement( 38, 0, subRect39 );
    subLayout->addElement( 39, 0, subRect40 );
    subLayout->addElement( 40, 0, subRect41 );
    subLayout->addElement( 41, 0, subRect42 );

    subLayout->addElement( 42, 0, subRect43 );
    subLayout->addElement( 43, 0, subRect44 );
    subLayout->addElement( 44, 0, subRect45 );
    subLayout->addElement( 45, 0, subRect46 );
    subLayout->addElement( 46, 0, subRect47 );
    subLayout->addElement( 47, 0, subRect48 );

    subLayout->addElement( 48, 0, subRect49 );
    subLayout->addElement( 49, 0, subRect50 );
    subLayout->addElement( 50, 0, subRect51 );
    subLayout->addElement( 51, 0, subRect52 );
    subLayout->addElement( 52, 0, subRect53 );
    subLayout->addElement( 53, 0, subRect54 );

    subLayout->addElement( 54, 0, subRect55 );
    subLayout->addElement( 55, 0, subRect56 );
    subLayout->addElement( 56, 0, subRect57 );
    subLayout->addElement( 57, 0, subRect58 );
    subLayout->addElement( 58, 0, subRect59 );
    subLayout->addElement( 59, 0, subRect60 );

    subLayout->addElement( 60, 0, subRect61 );
    subLayout->addElement( 61, 0, subRect62 );
    subLayout->addElement( 62, 0, subRect63 );
    subLayout->addElement( 63, 0, subRect64 );
    subLayout->addElement( 64, 0, subRect65 );
    subLayout->addElement( 65, 0, subRect66 );

    subLayout->addElement( 66, 0, subRect67 );
    subLayout->addElement( 67, 0, subRect68 );
    subLayout->addElement( 68, 0, subRect69 );
    subLayout->addElement( 69, 0, subRect70 );
    subLayout->addElement( 70, 0, subRect71 );
    subLayout->addElement( 71, 0, subRect72 );

    subLayout->addElement( 72, 0, subRect73 );
    subLayout->addElement( 73, 0, subRect74 );
    subLayout->addElement( 74, 0, subRect75 );
    subLayout->addElement( 75, 0, subRect76 );
    subLayout->addElement( 76, 0, subRect77);
    subLayout->addElement( 77, 0, subRect78 );

    subLayout->addElement( 78, 0, subRect79 );
    subLayout->addElement( 79, 0, subRect80 );
    subLayout->addElement( 80, 0, subRect81 );
    subLayout->addElement( 81, 0, subRect82 );
    subLayout->addElement( 82, 0, subRect83 );
    subLayout->addElement( 83, 0, subRect84 );

    subLayout->addElement( 84, 0, subRect85 );
    subLayout->addElement( 85, 0, subRect86 );
    subLayout->addElement( 86, 0, subRect87 );
    subLayout->addElement( 87, 0, subRect88 );
    subLayout->addElement( 88, 0, subRect89 );
    subLayout->addElement( 89, 0, subRect90 );

    subLayout->addElement( 90, 0, subRect91 );
    subLayout->addElement( 91, 0, subRect92 );
    subLayout->addElement( 92, 0, subRect93 );
    subLayout->addElement( 93, 0, subRect94 );
    subLayout->addElement( 94, 0, subRect95 );
    subLayout->addElement( 95, 0, subRect96 );


    // setup axes in sub layout axis rects:
    subRect1->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    //subRect1->axis(QCPAxis::atBottom)->ticker()->setTickCount(2);
    subRect1->axis(QCPAxis::atBottom)->grid()->setVisible(true);

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

    subRect22 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect22 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect23 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect23 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect24 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect24 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect25 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect25 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect26 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect26 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect27 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect27 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect28 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect28 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect29 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect29 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect30 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect30 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect31 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect31 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect32 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect32 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect33 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect33 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect34 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect34 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect35 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect35 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect36 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect36 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect37 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect37 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect38 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect38 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect39 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect39 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect40 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect40 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect41 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect41 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect42 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect42 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect43 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect43 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect44 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect44 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect45 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect45 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect46 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect46 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect47 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect47 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect48 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect48 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect49 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect49 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect50 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect50 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect51 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect51 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect52 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect52 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect53 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect53 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect54 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect54 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect55 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect55 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect56 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect56 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect57 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect57 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect58 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect58 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect59 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect59 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect60 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect60 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect61 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect61 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect62 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect62 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect63 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect63 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect64 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect64 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect65 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect65 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect66 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect66 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect67 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect67 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect68 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect68 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect69 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect69 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect70 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect70 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect71 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect71 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect72 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect72 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect73 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect73 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect74 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect74 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect75 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect75 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect76 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect76 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect77 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect77 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect78 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect78 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect79 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect79 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect80 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect80 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect81 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect81 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect82 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect82 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect83 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect83 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect84 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect84 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect85 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect85 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect86 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect86 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect87 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect87 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect88 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect88 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect89 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect89 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect90 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect90 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect91 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect91 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect92 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect92 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect93 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect93 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect94 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect94 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect95 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect95 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect96 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect96 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);



    // synchronize the left and right margins of the top and bottom axis rects:
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot_LB3);

    subRect1->setMarginGroup(QCP::msBottom, marginGroup);
    subRect2->setMarginGroup(QCP::msBottom, marginGroup);
    subRect3->setMarginGroup(QCP::msBottom, marginGroup);
    subRect4->setMarginGroup(QCP::msBottom, marginGroup);
    subRect5->setMarginGroup(QCP::msBottom, marginGroup);
    subRect6->setMarginGroup(QCP::msBottom, marginGroup);
    subRect7->setMarginGroup(QCP::msBottom, marginGroup);
    subRect8->setMarginGroup(QCP::msBottom, marginGroup);
    subRect9->setMarginGroup(QCP::msBottom, marginGroup);
    subRect10->setMarginGroup(QCP::msBottom, marginGroup);
    subRect11->setMarginGroup(QCP::msBottom, marginGroup);
    subRect12->setMarginGroup(QCP::msBottom, marginGroup);

    subRect13  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect14  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect15  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect16  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect17  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect18  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect19  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect20  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect21  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect22  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect23  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect24  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect25  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect26  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect27  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect28  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect29  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect30  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect31  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect32  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect33  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect34  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect35  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect36  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect37  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect38  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect39  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect40  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect41  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect42  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect43  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect44  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect45  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect46  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect47  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect48  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect49  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect50  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect51  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect52  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect53  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect54  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect55  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect56  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect57  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect58  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect59  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect60  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect61  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect62  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect63  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect64  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect65  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect66  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect67  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect68  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect69  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect70  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect71  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect72  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect73  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect74  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect75  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect76  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect77  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect78  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect79  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect80  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect81  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect82  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect83  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect84  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect85  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect86  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect87  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect88  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect89  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect90  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect91  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect92  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect93  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect94  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect95  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect96  ->setMarginGroup(QCP::msBottom, marginGroup);




    //wideAxisRect->setMarginGroup(QCP::msTop | QCP::msBottom | QCP::msRight | QCP::msLeft, marginGroup);


    // move newly created axes on "axes" layer and grids on "grid" layer:

    foreach (QCPAxisRect *rect, ui->plot_LB3->axisRects())
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
    ui->plot_LB3->setBackground(QBrush(gradient));
    //==================================================================
    //
    //==================================================================




    setupLocalPlot (subRect1  , y0LB3_StripData, 1 , "RPC Channel  1");
    setupLocalPlot (subRect2  , y0LB3_StripData, 2 , "RPC Channel  2");
    setupLocalPlot (subRect3  , y0LB3_StripData, 3 , "RPC Channel  3");
    setupLocalPlot (subRect4  , y0LB3_StripData, 4 , "RPC Channel  4");
    setupLocalPlot (subRect5  , y0LB3_StripData, 5 , "RPC Channel  5");
    setupLocalPlot (subRect6  , y0LB3_StripData,  6 , "RPC Channel  6");

    setupLocalPlot (subRect7  , y0LB3_StripData,  7 , "RPC Channel  7");
    setupLocalPlot (subRect8  , y0LB3_StripData,  8 , "RPC Channel  8");
    setupLocalPlot (subRect9  , y0LB3_StripData,  9 , "RPC Channel  9");
    setupLocalPlot (subRect10 , y0LB3_StripData,  10 , "RPC Channel  10");
    setupLocalPlot (subRect11 , y0LB3_StripData,  11 , "RPC Channel  11");
    setupLocalPlot (subRect12 , y0LB3_StripData,  12 , "RPC Channel  12");

    setupLocalPlot (subRect13  , y0LB3_StripData,  13  , "RPC Channel 13");
    setupLocalPlot (subRect14  , y0LB3_StripData,  14  , "RPC Channel 14");
    setupLocalPlot (subRect15  , y0LB3_StripData,  15  , "RPC Channel 15");
    setupLocalPlot (subRect16  , y0LB3_StripData,  16  , "RPC Channel 16");
    setupLocalPlot (subRect17  , y0LB3_StripData, 17  , "RPC Channel 17");
    setupLocalPlot (subRect18  , y0LB3_StripData, 18  , "RPC Channel 18");

    setupLocalPlot (subRect19  , y0LB3_StripData, 19  , "RPC Channel 19");
    setupLocalPlot (subRect20  , y0LB3_StripData,  20 , "RPC Channel  20");
    setupLocalPlot (subRect21  , y0LB3_StripData, 21  , "RPC Channel  21");
    setupLocalPlot (subRect22  , y0LB3_StripData, 22  , "RPC Channel  22");
    setupLocalPlot (subRect23  , y0LB3_StripData, 23  , "RPC Channel  23");
    setupLocalPlot (subRect24  , y0LB3_StripData, 24  , "RPC Channel  24");

    setupLocalPlot (subRect25  , y0LB3_StripData, 25  , "RPC Channel  25");
    setupLocalPlot (subRect26  , y0LB3_StripData, 26  , "RPC Channel  26");
    setupLocalPlot (subRect27  , y0LB3_StripData, 27  , "RPC Channel  27");
    setupLocalPlot (subRect28  , y0LB3_StripData, 28  , "RPC Channel  28");
    setupLocalPlot (subRect29  , y0LB3_StripData, 29  , "RPC Channel  29");
    setupLocalPlot (subRect30  , y0LB3_StripData, 30  , "RPC Channel  30");

    setupLocalPlot (subRect31  , y0LB3_StripData, 31  , "RPC Channel  31");
    setupLocalPlot (subRect32  , y0LB3_StripData, 32  , "RPC Channel  32");
    setupLocalPlot (subRect33  , y0LB3_StripData, 33  , "RPC Channel  33");
    setupLocalPlot (subRect34  , y0LB3_StripData, 34  , "RPC Channel  34");
    setupLocalPlot (subRect35  , y0LB3_StripData, 35  , "RPC Channel  35");
    setupLocalPlot (subRect36  , y0LB3_StripData, 36  , "RPC Channel  36");

    setupLocalPlot (subRect37  , y0LB3_StripData, 37  , "RPC Channel  37");
    setupLocalPlot (subRect38  , y0LB3_StripData, 38  , "RPC Channel  38");
    setupLocalPlot (subRect39  , y0LB3_StripData, 39  , "RPC Channel  39");
    setupLocalPlot (subRect40  , y0LB3_StripData, 40  , "RPC Channel  40");
    setupLocalPlot (subRect41  , y0LB3_StripData, 41  , "RPC Channel  41");
    setupLocalPlot (subRect42  , y0LB3_StripData, 42  , "RPC Channel  42");

    setupLocalPlot (subRect43  , y0LB3_StripData, 43  , "RPC Channel  43");
    setupLocalPlot (subRect44  , y0LB3_StripData, 44  , "RPC Channel  44");
    setupLocalPlot (subRect45  , y0LB3_StripData, 45  , "RPC Channel  45");
    setupLocalPlot (subRect46  , y0LB3_StripData, 46  , "RPC Channel  46");
    setupLocalPlot (subRect47  , y0LB3_StripData, 47  , "RPC Channel  47");
    setupLocalPlot (subRect48  , y0LB3_StripData, 48  , "RPC Channel  48");

    setupLocalPlot (subRect49  , y0LB3_StripData, 49  , "RPC Channel  49");
    setupLocalPlot (subRect50  , y0LB3_StripData, 50  , "RPC Channel  50");
    setupLocalPlot (subRect51  , y0LB3_StripData, 51  , "RPC Channel  51");
    setupLocalPlot (subRect52  , y0LB3_StripData, 52  , "RPC Channel  52");
    setupLocalPlot (subRect53  , y0LB3_StripData, 53  , "RPC Channel  53");
    setupLocalPlot (subRect54  , y0LB3_StripData, 54  , "RPC Channel  54");

    setupLocalPlot (subRect55  , y0LB3_StripData, 55  , "RPC Channel  55");
    setupLocalPlot (subRect56  , y0LB3_StripData, 56  , "RPC Channel  56");
    setupLocalPlot (subRect57  , y0LB3_StripData, 57  , "RPC Channel  57");
    setupLocalPlot (subRect58  , y0LB3_StripData, 58  , "RPC Channel  58");
    setupLocalPlot (subRect59  , y0LB3_StripData, 59  , "RPC Channel  59");
    setupLocalPlot (subRect60  , y0LB3_StripData, 60  , "RPC Channel  60");

    setupLocalPlot (subRect61  , y0LB3_StripData, 61  , "RPC Channel  61");
    setupLocalPlot (subRect62  , y0LB3_StripData, 62  , "RPC Channel  62");
    setupLocalPlot (subRect63  , y0LB3_StripData, 62  , "RPC Channel  63");
    setupLocalPlot (subRect64  , y0LB3_StripData, 64  , "RPC Channel  64");
    setupLocalPlot (subRect65  , y0LB3_StripData, 65  , "RPC Channel  65");
    setupLocalPlot (subRect66  , y0LB3_StripData, 66  , "RPC Channel  66");

    setupLocalPlot (subRect67  , y0LB3_StripData, 67  , "RPC Channel  67");
    setupLocalPlot (subRect68  , y0LB3_StripData, 68  , "RPC Channel  68");
    setupLocalPlot (subRect69  , y0LB3_StripData, 69  , "RPC Channel  69");
    setupLocalPlot (subRect70  , y0LB3_StripData, 70  , "RPC Channel  70");
    setupLocalPlot (subRect71  , y0LB3_StripData, 71  , "RPC Channel  71");
    setupLocalPlot (subRect72  , y0LB3_StripData, 72  , "RPC Channel  72");

    setupLocalPlot (subRect73  , y0LB3_StripData, 73  , "RPC Channel  73");
    setupLocalPlot (subRect74  , y0LB3_StripData, 74  , "RPC Channel  74");
    setupLocalPlot (subRect75  , y0LB3_StripData, 75  , "RPC Channel  75");
    setupLocalPlot (subRect76  , y0LB3_StripData, 76  , "RPC Channel  76");
    setupLocalPlot (subRect77  , y0LB3_StripData, 77  , "RPC Channel  77");
    setupLocalPlot (subRect78  , y0LB3_StripData, 78  , "RPC Channel  78");

    setupLocalPlot (subRect79  , y0LB3_StripData, 79  , "RPC Channel  79");
    setupLocalPlot (subRect80  , y0LB3_StripData, 80  , "RPC Channel  80");
    setupLocalPlot (subRect81  , y0LB3_StripData, 81  , "RPC Channel  81");
    setupLocalPlot (subRect82  , y0LB3_StripData, 82  , "RPC Channel  82");
    setupLocalPlot (subRect83  , y0LB3_StripData, 83  , "RPC Channel  83");
    setupLocalPlot (subRect84  , y0LB3_StripData, 84  , "RPC Channel  84");

    setupLocalPlot (subRect85  , y0LB3_StripData, 85  , "RPC Channel  85");
    setupLocalPlot (subRect86  , y0LB3_StripData, 86  , "RPC Channel  86");
    setupLocalPlot (subRect87  , y0LB3_StripData, 87  , "RPC Channel  87");
    setupLocalPlot (subRect88  , y0LB3_StripData, 88  , "RPC Channel  88");
    setupLocalPlot (subRect89  , y0LB3_StripData, 89  , "RPC Channel  89");
    setupLocalPlot (subRect90  , y0LB3_StripData, 90  , "RPC Channel  90");

    setupLocalPlot (subRect91  , y0LB3_StripData, 91  , "RPC Channel  91");
    setupLocalPlot (subRect92  , y0LB3_StripData, 92  , "RPC Channel  92");
    setupLocalPlot (subRect93  , y0LB3_StripData, 93  , "RPC Channel  93");
    setupLocalPlot (subRect94  , y0LB3_StripData, 94  , "RPC Channel  94");
    setupLocalPlot (subRect95  , y0LB3_StripData, 95  , "RPC Channel  95");
    setupLocalPlot (subRect96  , y0LB3_StripData, 96  , "RPC Channel  96");


    connect(ui->plot_LB3, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->plot_LB3, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel(QWheelEvent*)));
    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->plot_LB3->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_LB3->xAxis, SLOT(setRange(QCPRange)));
    connect(ui->plot_LB3->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_LB2->yAxis, SLOT(setRange(QCPRange)));

    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 7);

    ui->plot_LB3->replot();

}
//=================================================

//=================================================
void realtimev2::setupPlot_LB4(void){


    //QVector <double> y1_FullWinChannel (200);
    //QVector <double> y1_AdjWinChannel (200);

    //QVector <double> x1_stripFulW (200);
    //QVector <double> x1_stripAdjW (200);
    //unsigned int stripNum ;


    // configure axis rect:
    ui->plot_LB4->plotLayout()->clear(); // clear default axis rect so we can start from scratch
    /*
    QCPAxisRect *wideAxisRect = new QCPAxisRect(ui->plot_LB4);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers
    */

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;

    ui->plot_LB4->plotLayout()->addElement(0, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
    //ui->plot_LB4->setInteractions( QCP::iRangeZoom | QCP::iSelectPlottables);
    //ui->plot_LB4->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // prepare axis rects that will be placed in the sublayout:
    QCPAxisRect *subRect1 = new QCPAxisRect(ui->plot_LB4, false); // false means to not setup default axes
    QCPAxisRect *subRect2 = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect3 = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect4 = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect5 = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect6 = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect7 = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect8 = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect9 = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect10 = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect11 = new QCPAxisRect(ui->plot_LB4, false); // false means to not setup default axes
    QCPAxisRect *subRect12 = new QCPAxisRect(ui->plot_LB4, false);

    QCPAxisRect *subRect13  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect14  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect15  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect16  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect17  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect18  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect19  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect20  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect21  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect22  = new QCPAxisRect(ui->plot_LB4, false);


    QCPAxisRect *subRect23  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect24  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect25  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect26  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect27  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect28  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect29  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect30  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect31  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect32  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect33  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect34  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect35  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect36  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect37  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect38  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect39  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect40  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect41  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect42  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect43  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect44  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect45  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect46  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect47  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect48  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect49  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect50  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect51  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect52  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect53  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect54  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect55  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect56  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect57  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect58  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect59  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect60  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect61  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect62  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect63  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect64  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect65  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect66  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect67  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect68  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect69  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect70  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect71  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect72  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect73  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect74  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect75  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect76  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect77  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect78  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect79  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect80  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect81  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect82  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect83  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect84  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect85  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect86  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect87  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect88  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect89  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect90  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect91  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect92  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect93  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect94  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect95  = new QCPAxisRect(ui->plot_LB4, false);
    QCPAxisRect *subRect96  = new QCPAxisRect(ui->plot_LB4, false);



    subLayout->addElement(0, 0, subRect1);
    subLayout->addElement(1, 0, subRect2);
    subLayout->addElement(2, 0, subRect3);
    subLayout->addElement(3, 0, subRect4);
    subLayout->addElement(4, 0, subRect5);
    subLayout->addElement(5, 0, subRect6);

    subLayout->addElement(6, 0, subRect7);
    subLayout->addElement(7, 0, subRect8);
    subLayout->addElement(8, 0, subRect9);
    subLayout->addElement(9, 0, subRect10);
    subLayout->addElement(10, 0, subRect11);
    subLayout->addElement(11, 0, subRect12);


    subLayout->addElement( 12, 0, subRect13 );
    subLayout->addElement( 13, 0, subRect14 );
    subLayout->addElement( 14, 0, subRect15 );
    subLayout->addElement( 15, 0, subRect16 );
    subLayout->addElement( 16, 0, subRect17 );
    subLayout->addElement( 17, 0, subRect18 );

    subLayout->addElement( 18, 0, subRect19 );
    subLayout->addElement( 19, 0, subRect20 );
    subLayout->addElement( 20, 0, subRect21 );
    subLayout->addElement( 21, 0, subRect22 );
    subLayout->addElement( 22, 0, subRect23 );
    subLayout->addElement( 23, 0, subRect24 );

    subLayout->addElement( 24, 0, subRect25 );
    subLayout->addElement( 25, 0, subRect26 );
    subLayout->addElement( 26, 0, subRect27 );
    subLayout->addElement( 27, 0, subRect28 );
    subLayout->addElement( 28, 0, subRect29 );
    subLayout->addElement( 29, 0, subRect30 );

    subLayout->addElement( 30, 0, subRect31 );
    subLayout->addElement( 31, 0, subRect32 );
    subLayout->addElement( 32, 0, subRect33 );
    subLayout->addElement( 33, 0, subRect34 );
    subLayout->addElement( 34, 0, subRect35 );
    subLayout->addElement( 35, 0, subRect36 );

    subLayout->addElement( 36, 0, subRect37 );
    subLayout->addElement( 37, 0, subRect38 );
    subLayout->addElement( 38, 0, subRect39 );
    subLayout->addElement( 39, 0, subRect40 );
    subLayout->addElement( 40, 0, subRect41 );
    subLayout->addElement( 41, 0, subRect42 );

    subLayout->addElement( 42, 0, subRect43 );
    subLayout->addElement( 43, 0, subRect44 );
    subLayout->addElement( 44, 0, subRect45 );
    subLayout->addElement( 45, 0, subRect46 );
    subLayout->addElement( 46, 0, subRect47 );
    subLayout->addElement( 47, 0, subRect48 );

    subLayout->addElement( 48, 0, subRect49 );
    subLayout->addElement( 49, 0, subRect50 );
    subLayout->addElement( 50, 0, subRect51 );
    subLayout->addElement( 51, 0, subRect52 );
    subLayout->addElement( 52, 0, subRect53 );
    subLayout->addElement( 53, 0, subRect54 );

    subLayout->addElement( 54, 0, subRect55 );
    subLayout->addElement( 55, 0, subRect56 );
    subLayout->addElement( 56, 0, subRect57 );
    subLayout->addElement( 57, 0, subRect58 );
    subLayout->addElement( 58, 0, subRect59 );
    subLayout->addElement( 59, 0, subRect60 );

    subLayout->addElement( 60, 0, subRect61 );
    subLayout->addElement( 61, 0, subRect62 );
    subLayout->addElement( 62, 0, subRect63 );
    subLayout->addElement( 63, 0, subRect64 );
    subLayout->addElement( 64, 0, subRect65 );
    subLayout->addElement( 65, 0, subRect66 );

    subLayout->addElement( 66, 0, subRect67 );
    subLayout->addElement( 67, 0, subRect68 );
    subLayout->addElement( 68, 0, subRect69 );
    subLayout->addElement( 69, 0, subRect70 );
    subLayout->addElement( 70, 0, subRect71 );
    subLayout->addElement( 71, 0, subRect72 );

    subLayout->addElement( 72, 0, subRect73 );
    subLayout->addElement( 73, 0, subRect74 );
    subLayout->addElement( 74, 0, subRect75 );
    subLayout->addElement( 75, 0, subRect76 );
    subLayout->addElement( 76, 0, subRect77);
    subLayout->addElement( 77, 0, subRect78 );

    subLayout->addElement( 78, 0, subRect79 );
    subLayout->addElement( 79, 0, subRect80 );
    subLayout->addElement( 80, 0, subRect81 );
    subLayout->addElement( 81, 0, subRect82 );
    subLayout->addElement( 82, 0, subRect83 );
    subLayout->addElement( 83, 0, subRect84 );

    subLayout->addElement( 84, 0, subRect85 );
    subLayout->addElement( 85, 0, subRect86 );
    subLayout->addElement( 86, 0, subRect87 );
    subLayout->addElement( 87, 0, subRect88 );
    subLayout->addElement( 88, 0, subRect89 );
    subLayout->addElement( 89, 0, subRect90 );

    subLayout->addElement( 90, 0, subRect91 );
    subLayout->addElement( 91, 0, subRect92 );
    subLayout->addElement( 92, 0, subRect93 );
    subLayout->addElement( 93, 0, subRect94 );
    subLayout->addElement( 94, 0, subRect95 );
    subLayout->addElement( 95, 0, subRect96 );


    // setup axes in sub layout axis rects:
    subRect1->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    //subRect1->axis(QCPAxis::atBottom)->ticker()->setTickCount(2);
    subRect1->axis(QCPAxis::atBottom)->grid()->setVisible(true);

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

    subRect22 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect22 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect23 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect23 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect24 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect24 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect25 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect25 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect26 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect26 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect27 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect27 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect28 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect28 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect29 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect29 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect30 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect30 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect31 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect31 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect32 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect32 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect33 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect33 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect34 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect34 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect35 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect35 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect36 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect36 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect37 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect37 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect38 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect38 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect39 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect39 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect40 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect40 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect41 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect41 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect42 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect42 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect43 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect43 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect44 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect44 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect45 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect45 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect46 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect46 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect47 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect47 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect48 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect48 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect49 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect49 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect50 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect50 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect51 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect51 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect52 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect52 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect53 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect53 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect54 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect54 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect55 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect55 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect56 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect56 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect57 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect57 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect58 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect58 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect59 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect59 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect60 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect60 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect61 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect61 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect62 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect62 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect63 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect63 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect64 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect64 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect65 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect65 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect66 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect66 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect67 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect67 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect68 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect68 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect69 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect69 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect70 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect70 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect71 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect71 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect72 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect72 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect73 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect73 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect74 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect74 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect75 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect75 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect76 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect76 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect77 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect77 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect78 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect78 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect79 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect79 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect80 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect80 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect81 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect81 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect82 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect82 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect83 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect83 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect84 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect84 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect85 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect85 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect86 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect86 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect87 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect87 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect88 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect88 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect89 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect89 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect90 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect90 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect91 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect91 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect92 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect92 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect93 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect93 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect94 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect94 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect95 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect95 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect96 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect96 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);



    // synchronize the left and right margins of the top and bottom axis rects:
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot_LB4);

    subRect1->setMarginGroup(QCP::msBottom, marginGroup);
    subRect2->setMarginGroup(QCP::msBottom, marginGroup);
    subRect3->setMarginGroup(QCP::msBottom, marginGroup);
    subRect4->setMarginGroup(QCP::msBottom, marginGroup);
    subRect5->setMarginGroup(QCP::msBottom, marginGroup);
    subRect6->setMarginGroup(QCP::msBottom, marginGroup);
    subRect7->setMarginGroup(QCP::msBottom, marginGroup);
    subRect8->setMarginGroup(QCP::msBottom, marginGroup);
    subRect9->setMarginGroup(QCP::msBottom, marginGroup);
    subRect10->setMarginGroup(QCP::msBottom, marginGroup);
    subRect11->setMarginGroup(QCP::msBottom, marginGroup);
    subRect12->setMarginGroup(QCP::msBottom, marginGroup);

    subRect13  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect14  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect15  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect16  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect17  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect18  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect19  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect20  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect21  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect22  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect23  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect24  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect25  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect26  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect27  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect28  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect29  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect30  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect31  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect32  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect33  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect34  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect35  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect36  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect37  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect38  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect39  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect40  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect41  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect42  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect43  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect44  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect45  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect46  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect47  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect48  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect49  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect50  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect51  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect52  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect53  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect54  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect55  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect56  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect57  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect58  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect59  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect60  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect61  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect62  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect63  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect64  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect65  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect66  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect67  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect68  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect69  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect70  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect71  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect72  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect73  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect74  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect75  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect76  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect77  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect78  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect79  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect80  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect81  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect82  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect83  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect84  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect85  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect86  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect87  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect88  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect89  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect90  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect91  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect92  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect93  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect94  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect95  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect96  ->setMarginGroup(QCP::msBottom, marginGroup);




    //wideAxisRect->setMarginGroup(QCP::msTop | QCP::msBottom | QCP::msRight | QCP::msLeft, marginGroup);


    // move newly created axes on "axes" layer and grids on "grid" layer:

    foreach (QCPAxisRect *rect, ui->plot_LB4->axisRects())
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
    ui->plot_LB4->setBackground(QBrush(gradient));
    //==================================================================
    //
    //==================================================================




    setupLocalPlot (subRect1  , y0LB4_StripData, 1 , "RPC Channel  1");
    setupLocalPlot (subRect2  , y0LB4_StripData, 2 , "RPC Channel  2");
    setupLocalPlot (subRect3  , y0LB4_StripData, 3 , "RPC Channel  3");
    setupLocalPlot (subRect4  , y0LB4_StripData, 4 , "RPC Channel  4");
    setupLocalPlot (subRect5  , y0LB4_StripData, 5 , "RPC Channel  5");
    setupLocalPlot (subRect6  , y0LB4_StripData,  6 , "RPC Channel  6");

    setupLocalPlot (subRect7  , y0LB4_StripData,  7 , "RPC Channel  7");
    setupLocalPlot (subRect8  , y0LB4_StripData,  8 , "RPC Channel  8");
    setupLocalPlot (subRect9  , y0LB4_StripData,  9 , "RPC Channel  9");
    setupLocalPlot (subRect10 , y0LB4_StripData,  10 , "RPC Channel  10");
    setupLocalPlot (subRect11 , y0LB4_StripData,  11 , "RPC Channel  11");
    setupLocalPlot (subRect12 , y0LB4_StripData,  12 , "RPC Channel  12");

    setupLocalPlot (subRect13  , y0LB4_StripData,  13  , "RPC Channel 13");
    setupLocalPlot (subRect14  , y0LB4_StripData,  14  , "RPC Channel 14");
    setupLocalPlot (subRect15  , y0LB4_StripData,  15  , "RPC Channel 15");
    setupLocalPlot (subRect16  , y0LB4_StripData,  16  , "RPC Channel 16");
    setupLocalPlot (subRect17  , y0LB4_StripData, 17  , "RPC Channel 17");
    setupLocalPlot (subRect18  , y0LB4_StripData, 18  , "RPC Channel 18");

    setupLocalPlot (subRect19  , y0LB4_StripData, 19  , "RPC Channel 19");
    setupLocalPlot (subRect20  , y0LB4_StripData,  20 , "RPC Channel  20");
    setupLocalPlot (subRect21  , y0LB4_StripData, 21  , "RPC Channel  21");
    setupLocalPlot (subRect22  , y0LB4_StripData, 22  , "RPC Channel  22");
    setupLocalPlot (subRect23  , y0LB4_StripData, 23  , "RPC Channel  23");
    setupLocalPlot (subRect24  , y0LB4_StripData, 24  , "RPC Channel  24");

    setupLocalPlot (subRect25  , y0LB4_StripData, 25  , "RPC Channel  25");
    setupLocalPlot (subRect26  , y0LB4_StripData, 26  , "RPC Channel  26");
    setupLocalPlot (subRect27  , y0LB4_StripData, 27  , "RPC Channel  27");
    setupLocalPlot (subRect28  , y0LB4_StripData, 28  , "RPC Channel  28");
    setupLocalPlot (subRect29  , y0LB4_StripData, 29  , "RPC Channel  29");
    setupLocalPlot (subRect30  , y0LB4_StripData, 30  , "RPC Channel  30");

    setupLocalPlot (subRect31  , y0LB4_StripData, 31  , "RPC Channel  31");
    setupLocalPlot (subRect32  , y0LB4_StripData, 32  , "RPC Channel  32");
    setupLocalPlot (subRect33  , y0LB4_StripData, 33  , "RPC Channel  33");
    setupLocalPlot (subRect34  , y0LB4_StripData, 34  , "RPC Channel  34");
    setupLocalPlot (subRect35  , y0LB4_StripData, 35  , "RPC Channel  35");
    setupLocalPlot (subRect36  , y0LB4_StripData, 36  , "RPC Channel  36");

    setupLocalPlot (subRect37  , y0LB4_StripData, 37  , "RPC Channel  37");
    setupLocalPlot (subRect38  , y0LB4_StripData, 38  , "RPC Channel  38");
    setupLocalPlot (subRect39  , y0LB4_StripData, 39  , "RPC Channel  39");
    setupLocalPlot (subRect40  , y0LB4_StripData, 40  , "RPC Channel  40");
    setupLocalPlot (subRect41  , y0LB4_StripData, 41  , "RPC Channel  41");
    setupLocalPlot (subRect42  , y0LB4_StripData, 42  , "RPC Channel  42");

    setupLocalPlot (subRect43  , y0LB4_StripData, 43  , "RPC Channel  43");
    setupLocalPlot (subRect44  , y0LB4_StripData, 44  , "RPC Channel  44");
    setupLocalPlot (subRect45  , y0LB4_StripData, 45  , "RPC Channel  45");
    setupLocalPlot (subRect46  , y0LB4_StripData, 46  , "RPC Channel  46");
    setupLocalPlot (subRect47  , y0LB4_StripData, 47  , "RPC Channel  47");
    setupLocalPlot (subRect48  , y0LB4_StripData, 48  , "RPC Channel  48");

    setupLocalPlot (subRect49  , y0LB4_StripData, 49  , "RPC Channel  49");
    setupLocalPlot (subRect50  , y0LB4_StripData, 50  , "RPC Channel  50");
    setupLocalPlot (subRect51  , y0LB4_StripData, 51  , "RPC Channel  51");
    setupLocalPlot (subRect52  , y0LB4_StripData, 52  , "RPC Channel  52");
    setupLocalPlot (subRect53  , y0LB4_StripData, 53  , "RPC Channel  53");
    setupLocalPlot (subRect54  , y0LB4_StripData, 54  , "RPC Channel  54");

    setupLocalPlot (subRect55  , y0LB4_StripData, 55  , "RPC Channel  55");
    setupLocalPlot (subRect56  , y0LB4_StripData, 56  , "RPC Channel  56");
    setupLocalPlot (subRect57  , y0LB4_StripData, 57  , "RPC Channel  57");
    setupLocalPlot (subRect58  , y0LB4_StripData, 58  , "RPC Channel  58");
    setupLocalPlot (subRect59  , y0LB4_StripData, 59  , "RPC Channel  59");
    setupLocalPlot (subRect60  , y0LB4_StripData, 60  , "RPC Channel  60");

    setupLocalPlot (subRect61  , y0LB4_StripData, 61  , "RPC Channel  61");
    setupLocalPlot (subRect62  , y0LB4_StripData, 62  , "RPC Channel  62");
    setupLocalPlot (subRect63  , y0LB4_StripData, 62  , "RPC Channel  63");
    setupLocalPlot (subRect64  , y0LB4_StripData, 64  , "RPC Channel  64");
    setupLocalPlot (subRect65  , y0LB4_StripData, 65  , "RPC Channel  65");
    setupLocalPlot (subRect66  , y0LB4_StripData, 66  , "RPC Channel  66");

    setupLocalPlot (subRect67  , y0LB4_StripData, 67  , "RPC Channel  67");
    setupLocalPlot (subRect68  , y0LB4_StripData, 68  , "RPC Channel  68");
    setupLocalPlot (subRect69  , y0LB4_StripData, 69  , "RPC Channel  69");
    setupLocalPlot (subRect70  , y0LB4_StripData, 70  , "RPC Channel  70");
    setupLocalPlot (subRect71  , y0LB4_StripData, 71  , "RPC Channel  71");
    setupLocalPlot (subRect72  , y0LB4_StripData, 72  , "RPC Channel  72");

    setupLocalPlot (subRect73  , y0LB4_StripData, 73  , "RPC Channel  73");
    setupLocalPlot (subRect74  , y0LB4_StripData, 74  , "RPC Channel  74");
    setupLocalPlot (subRect75  , y0LB4_StripData, 75  , "RPC Channel  75");
    setupLocalPlot (subRect76  , y0LB4_StripData, 76  , "RPC Channel  76");
    setupLocalPlot (subRect77  , y0LB4_StripData, 77  , "RPC Channel  77");
    setupLocalPlot (subRect78  , y0LB4_StripData, 78  , "RPC Channel  78");

    setupLocalPlot (subRect79  , y0LB4_StripData, 79  , "RPC Channel  79");
    setupLocalPlot (subRect80  , y0LB4_StripData, 80  , "RPC Channel  80");
    setupLocalPlot (subRect81  , y0LB4_StripData, 81  , "RPC Channel  81");
    setupLocalPlot (subRect82  , y0LB4_StripData, 82  , "RPC Channel  82");
    setupLocalPlot (subRect83  , y0LB4_StripData, 83  , "RPC Channel  83");
    setupLocalPlot (subRect84  , y0LB4_StripData, 84  , "RPC Channel  84");

    setupLocalPlot (subRect85  , y0LB4_StripData, 85  , "RPC Channel  85");
    setupLocalPlot (subRect86  , y0LB4_StripData, 86  , "RPC Channel  86");
    setupLocalPlot (subRect87  , y0LB4_StripData, 87  , "RPC Channel  87");
    setupLocalPlot (subRect88  , y0LB4_StripData, 88  , "RPC Channel  88");
    setupLocalPlot (subRect89  , y0LB4_StripData, 89  , "RPC Channel  89");
    setupLocalPlot (subRect90  , y0LB4_StripData, 90  , "RPC Channel  90");

    setupLocalPlot (subRect91  , y0LB4_StripData, 91  , "RPC Channel  91");
    setupLocalPlot (subRect92  , y0LB4_StripData, 92  , "RPC Channel  92");
    setupLocalPlot (subRect93  , y0LB4_StripData, 93  , "RPC Channel  93");
    setupLocalPlot (subRect94  , y0LB4_StripData, 94  , "RPC Channel  94");
    setupLocalPlot (subRect95  , y0LB4_StripData, 95  , "RPC Channel  95");
    setupLocalPlot (subRect96  , y0LB4_StripData, 96  , "RPC Channel  96");


    connect(ui->plot_LB4, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->plot_LB4, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel(QWheelEvent*)));
    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->plot_LB4->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_LB4->xAxis, SLOT(setRange(QCPRange)));
    connect(ui->plot_LB4->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_LB4->yAxis, SLOT(setRange(QCPRange)));

    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 6);

    ui->plot_LB4->replot();

}
//=================================================

//=================================================
void realtimev2::setupPlot_LB5(void){


    //QVector <double> y1_FullWinChannel (200);
    //QVector <double> y1_AdjWinChannel (200);

    //QVector <double> x1_stripFulW (200);
    //QVector <double> x1_stripAdjW (200);
    //unsigned int stripNum ;


    // configure axis rect:
    ui->plot_LB5->plotLayout()->clear(); // clear default axis rect so we can start from scratch
    /*
    QCPAxisRect *wideAxisRect = new QCPAxisRect(ui->plot_LB5);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers
    */

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;

    ui->plot_LB5->plotLayout()->addElement(0, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
    //ui->plot_LB5->setInteractions( QCP::iRangeZoom | QCP::iSelectPlottables);
    //ui->plot_LB5->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // prepare axis rects that will be placed in the sublayout:
    QCPAxisRect *subRect1 = new QCPAxisRect(ui->plot_LB5, false); // false means to not setup default axes
    QCPAxisRect *subRect2 = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect3 = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect4 = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect5 = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect6 = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect7 = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect8 = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect9 = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect10 = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect11 = new QCPAxisRect(ui->plot_LB5, false); // false means to not setup default axes
    QCPAxisRect *subRect12 = new QCPAxisRect(ui->plot_LB5, false);

    QCPAxisRect *subRect13  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect14  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect15  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect16  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect17  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect18  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect19  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect20  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect21  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect22  = new QCPAxisRect(ui->plot_LB5, false);


    QCPAxisRect *subRect23  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect24  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect25  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect26  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect27  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect28  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect29  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect30  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect31  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect32  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect33  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect34  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect35  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect36  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect37  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect38  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect39  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect40  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect41  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect42  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect43  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect44  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect45  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect46  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect47  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect48  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect49  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect50  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect51  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect52  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect53  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect54  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect55  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect56  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect57  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect58  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect59  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect60  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect61  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect62  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect63  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect64  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect65  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect66  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect67  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect68  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect69  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect70  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect71  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect72  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect73  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect74  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect75  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect76  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect77  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect78  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect79  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect80  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect81  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect82  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect83  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect84  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect85  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect86  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect87  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect88  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect89  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect90  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect91  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect92  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect93  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect94  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect95  = new QCPAxisRect(ui->plot_LB5, false);
    QCPAxisRect *subRect96  = new QCPAxisRect(ui->plot_LB5, false);



    subLayout->addElement(0, 0, subRect1);
    subLayout->addElement(1, 0, subRect2);
    subLayout->addElement(2, 0, subRect3);
    subLayout->addElement(3, 0, subRect4);
    subLayout->addElement(4, 0, subRect5);
    subLayout->addElement(5, 0, subRect6);

    subLayout->addElement(6, 0, subRect7);
    subLayout->addElement(7, 0, subRect8);
    subLayout->addElement(8, 0, subRect9);
    subLayout->addElement(9, 0, subRect10);
    subLayout->addElement(10, 0, subRect11);
    subLayout->addElement(11, 0, subRect12);


    subLayout->addElement( 12, 0, subRect13 );
    subLayout->addElement( 13, 0, subRect14 );
    subLayout->addElement( 14, 0, subRect15 );
    subLayout->addElement( 15, 0, subRect16 );
    subLayout->addElement( 16, 0, subRect17 );
    subLayout->addElement( 17, 0, subRect18 );

    subLayout->addElement( 18, 0, subRect19 );
    subLayout->addElement( 19, 0, subRect20 );
    subLayout->addElement( 20, 0, subRect21 );
    subLayout->addElement( 21, 0, subRect22 );
    subLayout->addElement( 22, 0, subRect23 );
    subLayout->addElement( 23, 0, subRect24 );

    subLayout->addElement( 24, 0, subRect25 );
    subLayout->addElement( 25, 0, subRect26 );
    subLayout->addElement( 26, 0, subRect27 );
    subLayout->addElement( 27, 0, subRect28 );
    subLayout->addElement( 28, 0, subRect29 );
    subLayout->addElement( 29, 0, subRect30 );

    subLayout->addElement( 30, 0, subRect31 );
    subLayout->addElement( 31, 0, subRect32 );
    subLayout->addElement( 32, 0, subRect33 );
    subLayout->addElement( 33, 0, subRect34 );
    subLayout->addElement( 34, 0, subRect35 );
    subLayout->addElement( 35, 0, subRect36 );

    subLayout->addElement( 36, 0, subRect37 );
    subLayout->addElement( 37, 0, subRect38 );
    subLayout->addElement( 38, 0, subRect39 );
    subLayout->addElement( 39, 0, subRect40 );
    subLayout->addElement( 40, 0, subRect41 );
    subLayout->addElement( 41, 0, subRect42 );

    subLayout->addElement( 42, 0, subRect43 );
    subLayout->addElement( 43, 0, subRect44 );
    subLayout->addElement( 44, 0, subRect45 );
    subLayout->addElement( 45, 0, subRect46 );
    subLayout->addElement( 46, 0, subRect47 );
    subLayout->addElement( 47, 0, subRect48 );

    subLayout->addElement( 48, 0, subRect49 );
    subLayout->addElement( 49, 0, subRect50 );
    subLayout->addElement( 50, 0, subRect51 );
    subLayout->addElement( 51, 0, subRect52 );
    subLayout->addElement( 52, 0, subRect53 );
    subLayout->addElement( 53, 0, subRect54 );

    subLayout->addElement( 54, 0, subRect55 );
    subLayout->addElement( 55, 0, subRect56 );
    subLayout->addElement( 56, 0, subRect57 );
    subLayout->addElement( 57, 0, subRect58 );
    subLayout->addElement( 58, 0, subRect59 );
    subLayout->addElement( 59, 0, subRect60 );

    subLayout->addElement( 60, 0, subRect61 );
    subLayout->addElement( 61, 0, subRect62 );
    subLayout->addElement( 62, 0, subRect63 );
    subLayout->addElement( 63, 0, subRect64 );
    subLayout->addElement( 64, 0, subRect65 );
    subLayout->addElement( 65, 0, subRect66 );

    subLayout->addElement( 66, 0, subRect67 );
    subLayout->addElement( 67, 0, subRect68 );
    subLayout->addElement( 68, 0, subRect69 );
    subLayout->addElement( 69, 0, subRect70 );
    subLayout->addElement( 70, 0, subRect71 );
    subLayout->addElement( 71, 0, subRect72 );

    subLayout->addElement( 72, 0, subRect73 );
    subLayout->addElement( 73, 0, subRect74 );
    subLayout->addElement( 74, 0, subRect75 );
    subLayout->addElement( 75, 0, subRect76 );
    subLayout->addElement( 76, 0, subRect77);
    subLayout->addElement( 77, 0, subRect78 );

    subLayout->addElement( 78, 0, subRect79 );
    subLayout->addElement( 79, 0, subRect80 );
    subLayout->addElement( 80, 0, subRect81 );
    subLayout->addElement( 81, 0, subRect82 );
    subLayout->addElement( 82, 0, subRect83 );
    subLayout->addElement( 83, 0, subRect84 );

    subLayout->addElement( 84, 0, subRect85 );
    subLayout->addElement( 85, 0, subRect86 );
    subLayout->addElement( 86, 0, subRect87 );
    subLayout->addElement( 87, 0, subRect88 );
    subLayout->addElement( 88, 0, subRect89 );
    subLayout->addElement( 89, 0, subRect90 );

    subLayout->addElement( 90, 0, subRect91 );
    subLayout->addElement( 91, 0, subRect92 );
    subLayout->addElement( 92, 0, subRect93 );
    subLayout->addElement( 93, 0, subRect94 );
    subLayout->addElement( 94, 0, subRect95 );
    subLayout->addElement( 95, 0, subRect96 );


    // setup axes in sub layout axis rects:
    subRect1->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    //subRect1->axis(QCPAxis::atBottom)->ticker()->setTickCount(2);
    subRect1->axis(QCPAxis::atBottom)->grid()->setVisible(true);

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

    subRect22 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect22 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect23 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect23 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect24 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect24 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect25 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect25 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect26 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect26 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect27 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect27 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect28 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect28 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect29 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect29 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect30 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect30 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect31 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect31 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect32 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect32 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect33 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect33 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect34 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect34 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect35 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect35 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect36 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect36 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect37 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect37 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect38 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect38 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect39 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect39 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect40 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect40 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect41 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect41 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect42 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect42 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect43 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect43 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect44 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect44 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect45 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect45 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect46 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect46 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect47 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect47 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect48 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect48 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect49 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect49 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect50 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect50 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect51 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect51 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect52 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect52 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect53 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect53 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect54 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect54 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect55 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect55 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect56 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect56 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect57 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect57 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect58 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect58 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect59 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect59 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect60 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect60 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect61 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect61 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect62 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect62 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect63 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect63 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect64 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect64 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect65 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect65 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect66 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect66 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect67 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect67 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect68 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect68 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect69 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect69 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect70 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect70 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect71 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect71 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect72 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect72 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect73 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect73 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect74 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect74 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect75 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect75 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect76 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect76 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect77 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect77 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect78 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect78 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect79 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect79 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect80 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect80 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect81 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect81 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect82 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect82 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect83 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect83 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect84 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect84 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect85 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect85 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect86 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect86 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect87 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect87 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect88 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect88 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect89 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect89 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect90 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect90 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect91 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect91 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect92 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect92 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect93 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect93 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect94 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect94 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect95 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect95 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect96 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect96 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);



    // synchronize the left and right margins of the top and bottom axis rects:
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot_LB5);

    subRect1->setMarginGroup(QCP::msBottom, marginGroup);
    subRect2->setMarginGroup(QCP::msBottom, marginGroup);
    subRect3->setMarginGroup(QCP::msBottom, marginGroup);
    subRect4->setMarginGroup(QCP::msBottom, marginGroup);
    subRect5->setMarginGroup(QCP::msBottom, marginGroup);
    subRect6->setMarginGroup(QCP::msBottom, marginGroup);
    subRect7->setMarginGroup(QCP::msBottom, marginGroup);
    subRect8->setMarginGroup(QCP::msBottom, marginGroup);
    subRect9->setMarginGroup(QCP::msBottom, marginGroup);
    subRect10->setMarginGroup(QCP::msBottom, marginGroup);
    subRect11->setMarginGroup(QCP::msBottom, marginGroup);
    subRect12->setMarginGroup(QCP::msBottom, marginGroup);

    subRect13  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect14  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect15  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect16  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect17  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect18  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect19  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect20  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect21  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect22  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect23  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect24  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect25  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect26  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect27  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect28  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect29  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect30  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect31  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect32  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect33  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect34  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect35  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect36  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect37  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect38  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect39  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect40  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect41  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect42  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect43  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect44  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect45  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect46  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect47  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect48  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect49  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect50  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect51  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect52  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect53  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect54  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect55  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect56  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect57  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect58  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect59  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect60  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect61  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect62  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect63  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect64  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect65  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect66  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect67  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect68  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect69  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect70  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect71  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect72  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect73  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect74  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect75  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect76  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect77  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect78  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect79  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect80  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect81  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect82  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect83  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect84  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect85  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect86  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect87  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect88  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect89  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect90  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect91  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect92  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect93  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect94  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect95  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect96  ->setMarginGroup(QCP::msBottom, marginGroup);




    //wideAxisRect->setMarginGroup(QCP::msTop | QCP::msBottom | QCP::msRight | QCP::msLeft, marginGroup);


    // move newly created axes on "axes" layer and grids on "grid" layer:

    foreach (QCPAxisRect *rect, ui->plot_LB5->axisRects())
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
    ui->plot_LB5->setBackground(QBrush(gradient));
    //==================================================================
    //
    //==================================================================




    setupLocalPlot (subRect1  , y0LB5_StripData, 1 , "RPC Channel  1");
    setupLocalPlot (subRect2  , y0LB5_StripData, 2 , "RPC Channel  2");
    setupLocalPlot (subRect3  , y0LB5_StripData, 3 , "RPC Channel  3");
    setupLocalPlot (subRect4  , y0LB5_StripData, 4 , "RPC Channel  4");
    setupLocalPlot (subRect5  , y0LB5_StripData, 5 , "RPC Channel  5");
    setupLocalPlot (subRect6  , y0LB5_StripData,  6 , "RPC Channel  6");

    setupLocalPlot (subRect7  , y0LB5_StripData,  7 , "RPC Channel  7");
    setupLocalPlot (subRect8  , y0LB5_StripData,  8 , "RPC Channel  8");
    setupLocalPlot (subRect9  , y0LB5_StripData,  9 , "RPC Channel  9");
    setupLocalPlot (subRect10 , y0LB5_StripData,  10 , "RPC Channel  10");
    setupLocalPlot (subRect11 , y0LB5_StripData,  11 , "RPC Channel  11");
    setupLocalPlot (subRect12 , y0LB5_StripData,  12 , "RPC Channel  12");

    setupLocalPlot (subRect13  , y0LB5_StripData,  13  , "RPC Channel 13");
    setupLocalPlot (subRect14  , y0LB5_StripData,  14  , "RPC Channel 14");
    setupLocalPlot (subRect15  , y0LB5_StripData,  15  , "RPC Channel 15");
    setupLocalPlot (subRect16  , y0LB5_StripData,  16  , "RPC Channel 16");
    setupLocalPlot (subRect17  , y0LB5_StripData, 17  , "RPC Channel 17");
    setupLocalPlot (subRect18  , y0LB5_StripData, 18  , "RPC Channel 18");

    setupLocalPlot (subRect19  , y0LB5_StripData, 19  , "RPC Channel 19");
    setupLocalPlot (subRect20  , y0LB5_StripData,  20 , "RPC Channel  20");
    setupLocalPlot (subRect21  , y0LB5_StripData, 21  , "RPC Channel  21");
    setupLocalPlot (subRect22  , y0LB5_StripData, 22  , "RPC Channel  22");
    setupLocalPlot (subRect23  , y0LB5_StripData, 23  , "RPC Channel  23");
    setupLocalPlot (subRect24  , y0LB5_StripData, 24  , "RPC Channel  24");

    setupLocalPlot (subRect25  , y0LB5_StripData, 25  , "RPC Channel  25");
    setupLocalPlot (subRect26  , y0LB5_StripData, 26  , "RPC Channel  26");
    setupLocalPlot (subRect27  , y0LB5_StripData, 27  , "RPC Channel  27");
    setupLocalPlot (subRect28  , y0LB5_StripData, 28  , "RPC Channel  28");
    setupLocalPlot (subRect29  , y0LB5_StripData, 29  , "RPC Channel  29");
    setupLocalPlot (subRect30  , y0LB5_StripData, 30  , "RPC Channel  30");

    setupLocalPlot (subRect31  , y0LB5_StripData, 31  , "RPC Channel  31");
    setupLocalPlot (subRect32  , y0LB5_StripData, 32  , "RPC Channel  32");
    setupLocalPlot (subRect33  , y0LB5_StripData, 33  , "RPC Channel  33");
    setupLocalPlot (subRect34  , y0LB5_StripData, 34  , "RPC Channel  34");
    setupLocalPlot (subRect35  , y0LB5_StripData, 35  , "RPC Channel  35");
    setupLocalPlot (subRect36  , y0LB5_StripData, 36  , "RPC Channel  36");

    setupLocalPlot (subRect37  , y0LB5_StripData, 37  , "RPC Channel  37");
    setupLocalPlot (subRect38  , y0LB5_StripData, 38  , "RPC Channel  38");
    setupLocalPlot (subRect39  , y0LB5_StripData, 39  , "RPC Channel  39");
    setupLocalPlot (subRect40  , y0LB5_StripData, 40  , "RPC Channel  40");
    setupLocalPlot (subRect41  , y0LB5_StripData, 41  , "RPC Channel  41");
    setupLocalPlot (subRect42  , y0LB5_StripData, 42  , "RPC Channel  42");

    setupLocalPlot (subRect43  , y0LB5_StripData, 43  , "RPC Channel  43");
    setupLocalPlot (subRect44  , y0LB5_StripData, 44  , "RPC Channel  44");
    setupLocalPlot (subRect45  , y0LB5_StripData, 45  , "RPC Channel  45");
    setupLocalPlot (subRect46  , y0LB5_StripData, 46  , "RPC Channel  46");
    setupLocalPlot (subRect47  , y0LB5_StripData, 47  , "RPC Channel  47");
    setupLocalPlot (subRect48  , y0LB5_StripData, 48  , "RPC Channel  48");

    setupLocalPlot (subRect49  , y0LB5_StripData, 49  , "RPC Channel  49");
    setupLocalPlot (subRect50  , y0LB5_StripData, 50  , "RPC Channel  50");
    setupLocalPlot (subRect51  , y0LB5_StripData, 51  , "RPC Channel  51");
    setupLocalPlot (subRect52  , y0LB5_StripData, 52  , "RPC Channel  52");
    setupLocalPlot (subRect53  , y0LB5_StripData, 53  , "RPC Channel  53");
    setupLocalPlot (subRect54  , y0LB5_StripData, 54  , "RPC Channel  54");

    setupLocalPlot (subRect55  , y0LB5_StripData, 55  , "RPC Channel  55");
    setupLocalPlot (subRect56  , y0LB5_StripData, 56  , "RPC Channel  56");
    setupLocalPlot (subRect57  , y0LB5_StripData, 57  , "RPC Channel  57");
    setupLocalPlot (subRect58  , y0LB5_StripData, 58  , "RPC Channel  58");
    setupLocalPlot (subRect59  , y0LB5_StripData, 59  , "RPC Channel  59");
    setupLocalPlot (subRect60  , y0LB5_StripData, 60  , "RPC Channel  60");

    setupLocalPlot (subRect61  , y0LB5_StripData, 61  , "RPC Channel  61");
    setupLocalPlot (subRect62  , y0LB5_StripData, 62  , "RPC Channel  62");
    setupLocalPlot (subRect63  , y0LB5_StripData, 62  , "RPC Channel  63");
    setupLocalPlot (subRect64  , y0LB5_StripData, 64  , "RPC Channel  64");
    setupLocalPlot (subRect65  , y0LB5_StripData, 65  , "RPC Channel  65");
    setupLocalPlot (subRect66  , y0LB5_StripData, 66  , "RPC Channel  66");

    setupLocalPlot (subRect67  , y0LB5_StripData, 67  , "RPC Channel  67");
    setupLocalPlot (subRect68  , y0LB5_StripData, 68  , "RPC Channel  68");
    setupLocalPlot (subRect69  , y0LB5_StripData, 69  , "RPC Channel  69");
    setupLocalPlot (subRect70  , y0LB5_StripData, 70  , "RPC Channel  70");
    setupLocalPlot (subRect71  , y0LB5_StripData, 71  , "RPC Channel  71");
    setupLocalPlot (subRect72  , y0LB5_StripData, 72  , "RPC Channel  72");

    setupLocalPlot (subRect73  , y0LB5_StripData, 73  , "RPC Channel  73");
    setupLocalPlot (subRect74  , y0LB5_StripData, 74  , "RPC Channel  74");
    setupLocalPlot (subRect75  , y0LB5_StripData, 75  , "RPC Channel  75");
    setupLocalPlot (subRect76  , y0LB5_StripData, 76  , "RPC Channel  76");
    setupLocalPlot (subRect77  , y0LB5_StripData, 77  , "RPC Channel  77");
    setupLocalPlot (subRect78  , y0LB5_StripData, 78  , "RPC Channel  78");

    setupLocalPlot (subRect79  , y0LB5_StripData, 79  , "RPC Channel  79");
    setupLocalPlot (subRect80  , y0LB5_StripData, 80  , "RPC Channel  80");
    setupLocalPlot (subRect81  , y0LB5_StripData, 81  , "RPC Channel  81");
    setupLocalPlot (subRect82  , y0LB5_StripData, 82  , "RPC Channel  82");
    setupLocalPlot (subRect83  , y0LB5_StripData, 83  , "RPC Channel  83");
    setupLocalPlot (subRect84  , y0LB5_StripData, 84  , "RPC Channel  84");

    setupLocalPlot (subRect85  , y0LB5_StripData, 85  , "RPC Channel  85");
    setupLocalPlot (subRect86  , y0LB5_StripData, 86  , "RPC Channel  86");
    setupLocalPlot (subRect87  , y0LB5_StripData, 87  , "RPC Channel  87");
    setupLocalPlot (subRect88  , y0LB5_StripData, 88  , "RPC Channel  88");
    setupLocalPlot (subRect89  , y0LB5_StripData, 89  , "RPC Channel  89");
    setupLocalPlot (subRect90  , y0LB5_StripData, 90  , "RPC Channel  90");

    setupLocalPlot (subRect91  , y0LB5_StripData, 91  , "RPC Channel  91");
    setupLocalPlot (subRect92  , y0LB5_StripData, 92  , "RPC Channel  92");
    setupLocalPlot (subRect93  , y0LB5_StripData, 93  , "RPC Channel  93");
    setupLocalPlot (subRect94  , y0LB5_StripData, 94  , "RPC Channel  94");
    setupLocalPlot (subRect95  , y0LB5_StripData, 95  , "RPC Channel  95");
    setupLocalPlot (subRect96  , y0LB5_StripData, 96  , "RPC Channel  96");


    connect(ui->plot_LB5, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->plot_LB5, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel(QWheelEvent*)));
    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->plot_LB5->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_LB5->xAxis, SLOT(setRange(QCPRange)));
    connect(ui->plot_LB5->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_LB5->yAxis, SLOT(setRange(QCPRange)));

    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 5);

    ui->plot_LB5->replot();
}
//=================================================

//=================================================
void realtimev2::setupPlot_LB6(void){


    //QVector <double> y1_FullWinChannel (200);
    //QVector <double> y1_AdjWinChannel (200);

    //QVector <double> x1_stripFulW (200);
    //QVector <double> x1_stripAdjW (200);
    //unsigned int stripNum ;


    // configure axis rect:
    ui->plot_LB6->plotLayout()->clear(); // clear default axis rect so we can start from scratch
    /*
    QCPAxisRect *wideAxisRect = new QCPAxisRect(ui->plot_LB6);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers
    */

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;

    ui->plot_LB6->plotLayout()->addElement(0, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
    //ui->plot_LB6->setInteractions( QCP::iRangeZoom | QCP::iSelectPlottables);
    //ui->plot_LB6->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // prepare axis rects that will be placed in the sublayout:
    QCPAxisRect *subRect1 = new QCPAxisRect(ui->plot_LB6, false); // false means to not setup default axes
    QCPAxisRect *subRect2 = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect3 = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect4 = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect5 = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect6 = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect7 = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect8 = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect9 = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect10 = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect11 = new QCPAxisRect(ui->plot_LB6, false); // false means to not setup default axes
    QCPAxisRect *subRect12 = new QCPAxisRect(ui->plot_LB6, false);

    QCPAxisRect *subRect13  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect14  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect15  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect16  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect17  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect18  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect19  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect20  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect21  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect22  = new QCPAxisRect(ui->plot_LB6, false);


    QCPAxisRect *subRect23  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect24  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect25  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect26  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect27  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect28  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect29  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect30  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect31  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect32  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect33  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect34  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect35  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect36  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect37  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect38  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect39  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect40  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect41  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect42  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect43  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect44  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect45  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect46  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect47  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect48  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect49  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect50  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect51  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect52  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect53  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect54  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect55  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect56  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect57  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect58  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect59  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect60  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect61  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect62  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect63  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect64  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect65  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect66  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect67  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect68  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect69  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect70  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect71  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect72  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect73  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect74  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect75  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect76  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect77  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect78  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect79  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect80  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect81  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect82  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect83  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect84  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect85  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect86  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect87  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect88  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect89  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect90  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect91  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect92  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect93  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect94  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect95  = new QCPAxisRect(ui->plot_LB6, false);
    QCPAxisRect *subRect96  = new QCPAxisRect(ui->plot_LB6, false);



    subLayout->addElement(0, 0, subRect1);
    subLayout->addElement(1, 0, subRect2);
    subLayout->addElement(2, 0, subRect3);
    subLayout->addElement(3, 0, subRect4);
    subLayout->addElement(4, 0, subRect5);
    subLayout->addElement(5, 0, subRect6);

    subLayout->addElement(6, 0, subRect7);
    subLayout->addElement(7, 0, subRect8);
    subLayout->addElement(8, 0, subRect9);
    subLayout->addElement(9, 0, subRect10);
    subLayout->addElement(10, 0, subRect11);
    subLayout->addElement(11, 0, subRect12);


    subLayout->addElement( 12, 0, subRect13 );
    subLayout->addElement( 13, 0, subRect14 );
    subLayout->addElement( 14, 0, subRect15 );
    subLayout->addElement( 15, 0, subRect16 );
    subLayout->addElement( 16, 0, subRect17 );
    subLayout->addElement( 17, 0, subRect18 );

    subLayout->addElement( 18, 0, subRect19 );
    subLayout->addElement( 19, 0, subRect20 );
    subLayout->addElement( 20, 0, subRect21 );
    subLayout->addElement( 21, 0, subRect22 );
    subLayout->addElement( 22, 0, subRect23 );
    subLayout->addElement( 23, 0, subRect24 );

    subLayout->addElement( 24, 0, subRect25 );
    subLayout->addElement( 25, 0, subRect26 );
    subLayout->addElement( 26, 0, subRect27 );
    subLayout->addElement( 27, 0, subRect28 );
    subLayout->addElement( 28, 0, subRect29 );
    subLayout->addElement( 29, 0, subRect30 );

    subLayout->addElement( 30, 0, subRect31 );
    subLayout->addElement( 31, 0, subRect32 );
    subLayout->addElement( 32, 0, subRect33 );
    subLayout->addElement( 33, 0, subRect34 );
    subLayout->addElement( 34, 0, subRect35 );
    subLayout->addElement( 35, 0, subRect36 );

    subLayout->addElement( 36, 0, subRect37 );
    subLayout->addElement( 37, 0, subRect38 );
    subLayout->addElement( 38, 0, subRect39 );
    subLayout->addElement( 39, 0, subRect40 );
    subLayout->addElement( 40, 0, subRect41 );
    subLayout->addElement( 41, 0, subRect42 );

    subLayout->addElement( 42, 0, subRect43 );
    subLayout->addElement( 43, 0, subRect44 );
    subLayout->addElement( 44, 0, subRect45 );
    subLayout->addElement( 45, 0, subRect46 );
    subLayout->addElement( 46, 0, subRect47 );
    subLayout->addElement( 47, 0, subRect48 );

    subLayout->addElement( 48, 0, subRect49 );
    subLayout->addElement( 49, 0, subRect50 );
    subLayout->addElement( 50, 0, subRect51 );
    subLayout->addElement( 51, 0, subRect52 );
    subLayout->addElement( 52, 0, subRect53 );
    subLayout->addElement( 53, 0, subRect54 );

    subLayout->addElement( 54, 0, subRect55 );
    subLayout->addElement( 55, 0, subRect56 );
    subLayout->addElement( 56, 0, subRect57 );
    subLayout->addElement( 57, 0, subRect58 );
    subLayout->addElement( 58, 0, subRect59 );
    subLayout->addElement( 59, 0, subRect60 );

    subLayout->addElement( 60, 0, subRect61 );
    subLayout->addElement( 61, 0, subRect62 );
    subLayout->addElement( 62, 0, subRect63 );
    subLayout->addElement( 63, 0, subRect64 );
    subLayout->addElement( 64, 0, subRect65 );
    subLayout->addElement( 65, 0, subRect66 );

    subLayout->addElement( 66, 0, subRect67 );
    subLayout->addElement( 67, 0, subRect68 );
    subLayout->addElement( 68, 0, subRect69 );
    subLayout->addElement( 69, 0, subRect70 );
    subLayout->addElement( 70, 0, subRect71 );
    subLayout->addElement( 71, 0, subRect72 );

    subLayout->addElement( 72, 0, subRect73 );
    subLayout->addElement( 73, 0, subRect74 );
    subLayout->addElement( 74, 0, subRect75 );
    subLayout->addElement( 75, 0, subRect76 );
    subLayout->addElement( 76, 0, subRect77);
    subLayout->addElement( 77, 0, subRect78 );

    subLayout->addElement( 78, 0, subRect79 );
    subLayout->addElement( 79, 0, subRect80 );
    subLayout->addElement( 80, 0, subRect81 );
    subLayout->addElement( 81, 0, subRect82 );
    subLayout->addElement( 82, 0, subRect83 );
    subLayout->addElement( 83, 0, subRect84 );

    subLayout->addElement( 84, 0, subRect85 );
    subLayout->addElement( 85, 0, subRect86 );
    subLayout->addElement( 86, 0, subRect87 );
    subLayout->addElement( 87, 0, subRect88 );
    subLayout->addElement( 88, 0, subRect89 );
    subLayout->addElement( 89, 0, subRect90 );

    subLayout->addElement( 90, 0, subRect91 );
    subLayout->addElement( 91, 0, subRect92 );
    subLayout->addElement( 92, 0, subRect93 );
    subLayout->addElement( 93, 0, subRect94 );
    subLayout->addElement( 94, 0, subRect95 );
    subLayout->addElement( 95, 0, subRect96 );


    // setup axes in sub layout axis rects:
    subRect1->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    //subRect1->axis(QCPAxis::atBottom)->ticker()->setTickCount(2);
    subRect1->axis(QCPAxis::atBottom)->grid()->setVisible(true);

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

    subRect22 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect22 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect23 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect23 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect24 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect24 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect25 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect25 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect26 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect26 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect27 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect27 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect28 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect28 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect29 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect29 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect30 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect30 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect31 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect31 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect32 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect32 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect33 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect33 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect34 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect34 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect35 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect35 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect36 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect36 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect37 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect37 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect38 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect38 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect39 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect39 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect40 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect40 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect41 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect41 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect42 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect42 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect43 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect43 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect44 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect44 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect45 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect45 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect46 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect46 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect47 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect47 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect48 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect48 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect49 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect49 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect50 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect50 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect51 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect51 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect52 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect52 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect53 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect53 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect54 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect54 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect55 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect55 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect56 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect56 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect57 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect57 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect58 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect58 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect59 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect59 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect60 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect60 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect61 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect61 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect62 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect62 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect63 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect63 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect64 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect64 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect65 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect65 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect66 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect66 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect67 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect67 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect68 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect68 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect69 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect69 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect70 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect70 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect71 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect71 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect72 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect72 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect73 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect73 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect74 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect74 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect75 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect75 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect76 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect76 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect77 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect77 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect78 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect78 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect79 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect79 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect80 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect80 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect81 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect81 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect82 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect82 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect83 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect83 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect84 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect84 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect85 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect85 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect86 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect86 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect87 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect87 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect88 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect88 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect89 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect89 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect90 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect90 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect91 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect91 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect92 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect92 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect93 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect93 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect94 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect94 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect95 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect95 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect96 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect96 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);



    // synchronize the left and right margins of the top and bottom axis rects:
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot_LB6);

    subRect1->setMarginGroup(QCP::msBottom, marginGroup);
    subRect2->setMarginGroup(QCP::msBottom, marginGroup);
    subRect3->setMarginGroup(QCP::msBottom, marginGroup);
    subRect4->setMarginGroup(QCP::msBottom, marginGroup);
    subRect5->setMarginGroup(QCP::msBottom, marginGroup);
    subRect6->setMarginGroup(QCP::msBottom, marginGroup);
    subRect7->setMarginGroup(QCP::msBottom, marginGroup);
    subRect8->setMarginGroup(QCP::msBottom, marginGroup);
    subRect9->setMarginGroup(QCP::msBottom, marginGroup);
    subRect10->setMarginGroup(QCP::msBottom, marginGroup);
    subRect11->setMarginGroup(QCP::msBottom, marginGroup);
    subRect12->setMarginGroup(QCP::msBottom, marginGroup);

    subRect13  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect14  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect15  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect16  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect17  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect18  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect19  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect20  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect21  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect22  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect23  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect24  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect25  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect26  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect27  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect28  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect29  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect30  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect31  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect32  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect33  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect34  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect35  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect36  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect37  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect38  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect39  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect40  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect41  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect42  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect43  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect44  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect45  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect46  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect47  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect48  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect49  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect50  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect51  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect52  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect53  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect54  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect55  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect56  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect57  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect58  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect59  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect60  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect61  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect62  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect63  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect64  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect65  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect66  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect67  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect68  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect69  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect70  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect71  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect72  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect73  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect74  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect75  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect76  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect77  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect78  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect79  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect80  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect81  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect82  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect83  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect84  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect85  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect86  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect87  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect88  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect89  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect90  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect91  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect92  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect93  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect94  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect95  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect96  ->setMarginGroup(QCP::msBottom, marginGroup);




    //wideAxisRect->setMarginGroup(QCP::msTop | QCP::msBottom | QCP::msRight | QCP::msLeft, marginGroup);


    // move newly created axes on "axes" layer and grids on "grid" layer:

    foreach (QCPAxisRect *rect, ui->plot_LB6->axisRects())
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
    ui->plot_LB6->setBackground(QBrush(gradient));
    //==================================================================
    //
    //==================================================================




    setupLocalPlot (subRect1  , y0LB6_StripData, 1 , "RPC Channel  1");
    setupLocalPlot (subRect2  , y0LB6_StripData, 2 , "RPC Channel  2");
    setupLocalPlot (subRect3  , y0LB6_StripData, 3 , "RPC Channel  3");
    setupLocalPlot (subRect4  , y0LB6_StripData, 4 , "RPC Channel  4");
    setupLocalPlot (subRect5  , y0LB6_StripData, 5 , "RPC Channel  5");
    setupLocalPlot (subRect6  , y0LB6_StripData,  6 , "RPC Channel  6");

    setupLocalPlot (subRect7  , y0LB6_StripData,  7 , "RPC Channel  7");
    setupLocalPlot (subRect8  , y0LB6_StripData,  8 , "RPC Channel  8");
    setupLocalPlot (subRect9  , y0LB6_StripData,  9 , "RPC Channel  9");
    setupLocalPlot (subRect10 , y0LB6_StripData,  10 , "RPC Channel  10");
    setupLocalPlot (subRect11 , y0LB6_StripData,  11 , "RPC Channel  11");
    setupLocalPlot (subRect12 , y0LB6_StripData,  12 , "RPC Channel  12");

    setupLocalPlot (subRect13  , y0LB6_StripData,  13  , "RPC Channel 13");
    setupLocalPlot (subRect14  , y0LB6_StripData,  14  , "RPC Channel 14");
    setupLocalPlot (subRect15  , y0LB6_StripData,  15  , "RPC Channel 15");
    setupLocalPlot (subRect16  , y0LB6_StripData,  16  , "RPC Channel 16");
    setupLocalPlot (subRect17  , y0LB6_StripData, 17  , "RPC Channel 17");
    setupLocalPlot (subRect18  , y0LB6_StripData, 18  , "RPC Channel 18");

    setupLocalPlot (subRect19  , y0LB6_StripData, 19  , "RPC Channel 19");
    setupLocalPlot (subRect20  , y0LB6_StripData,  20 , "RPC Channel  20");
    setupLocalPlot (subRect21  , y0LB6_StripData, 21  , "RPC Channel  21");
    setupLocalPlot (subRect22  , y0LB6_StripData, 22  , "RPC Channel  22");
    setupLocalPlot (subRect23  , y0LB6_StripData, 23  , "RPC Channel  23");
    setupLocalPlot (subRect24  , y0LB6_StripData, 24  , "RPC Channel  24");

    setupLocalPlot (subRect25  , y0LB6_StripData, 25  , "RPC Channel  25");
    setupLocalPlot (subRect26  , y0LB6_StripData, 26  , "RPC Channel  26");
    setupLocalPlot (subRect27  , y0LB6_StripData, 27  , "RPC Channel  27");
    setupLocalPlot (subRect28  , y0LB6_StripData, 28  , "RPC Channel  28");
    setupLocalPlot (subRect29  , y0LB6_StripData, 29  , "RPC Channel  29");
    setupLocalPlot (subRect30  , y0LB6_StripData, 30  , "RPC Channel  30");

    setupLocalPlot (subRect31  , y0LB6_StripData, 31  , "RPC Channel  31");
    setupLocalPlot (subRect32  , y0LB6_StripData, 32  , "RPC Channel  32");
    setupLocalPlot (subRect33  , y0LB6_StripData, 33  , "RPC Channel  33");
    setupLocalPlot (subRect34  , y0LB6_StripData, 34  , "RPC Channel  34");
    setupLocalPlot (subRect35  , y0LB6_StripData, 35  , "RPC Channel  35");
    setupLocalPlot (subRect36  , y0LB6_StripData, 36  , "RPC Channel  36");

    setupLocalPlot (subRect37  , y0LB6_StripData, 37  , "RPC Channel  37");
    setupLocalPlot (subRect38  , y0LB6_StripData, 38  , "RPC Channel  38");
    setupLocalPlot (subRect39  , y0LB6_StripData, 39  , "RPC Channel  39");
    setupLocalPlot (subRect40  , y0LB6_StripData, 40  , "RPC Channel  40");
    setupLocalPlot (subRect41  , y0LB6_StripData, 41  , "RPC Channel  41");
    setupLocalPlot (subRect42  , y0LB6_StripData, 42  , "RPC Channel  42");

    setupLocalPlot (subRect43  , y0LB6_StripData, 43  , "RPC Channel  43");
    setupLocalPlot (subRect44  , y0LB6_StripData, 44  , "RPC Channel  44");
    setupLocalPlot (subRect45  , y0LB6_StripData, 45  , "RPC Channel  45");
    setupLocalPlot (subRect46  , y0LB6_StripData, 46  , "RPC Channel  46");
    setupLocalPlot (subRect47  , y0LB6_StripData, 47  , "RPC Channel  47");
    setupLocalPlot (subRect48  , y0LB6_StripData, 48  , "RPC Channel  48");

    setupLocalPlot (subRect49  , y0LB6_StripData, 49  , "RPC Channel  49");
    setupLocalPlot (subRect50  , y0LB6_StripData, 50  , "RPC Channel  50");
    setupLocalPlot (subRect51  , y0LB6_StripData, 51  , "RPC Channel  51");
    setupLocalPlot (subRect52  , y0LB6_StripData, 52  , "RPC Channel  52");
    setupLocalPlot (subRect53  , y0LB6_StripData, 53  , "RPC Channel  53");
    setupLocalPlot (subRect54  , y0LB6_StripData, 54  , "RPC Channel  54");

    setupLocalPlot (subRect55  , y0LB6_StripData, 55  , "RPC Channel  55");
    setupLocalPlot (subRect56  , y0LB6_StripData, 56  , "RPC Channel  56");
    setupLocalPlot (subRect57  , y0LB6_StripData, 57  , "RPC Channel  57");
    setupLocalPlot (subRect58  , y0LB6_StripData, 58  , "RPC Channel  58");
    setupLocalPlot (subRect59  , y0LB6_StripData, 59  , "RPC Channel  59");
    setupLocalPlot (subRect60  , y0LB6_StripData, 60  , "RPC Channel  60");

    setupLocalPlot (subRect61  , y0LB6_StripData, 61  , "RPC Channel  61");
    setupLocalPlot (subRect62  , y0LB6_StripData, 62  , "RPC Channel  62");
    setupLocalPlot (subRect63  , y0LB6_StripData, 62  , "RPC Channel  63");
    setupLocalPlot (subRect64  , y0LB6_StripData, 64  , "RPC Channel  64");
    setupLocalPlot (subRect65  , y0LB6_StripData, 65  , "RPC Channel  65");
    setupLocalPlot (subRect66  , y0LB6_StripData, 66  , "RPC Channel  66");

    setupLocalPlot (subRect67  , y0LB6_StripData, 67  , "RPC Channel  67");
    setupLocalPlot (subRect68  , y0LB6_StripData, 68  , "RPC Channel  68");
    setupLocalPlot (subRect69  , y0LB6_StripData, 69  , "RPC Channel  69");
    setupLocalPlot (subRect70  , y0LB6_StripData, 70  , "RPC Channel  70");
    setupLocalPlot (subRect71  , y0LB6_StripData, 71  , "RPC Channel  71");
    setupLocalPlot (subRect72  , y0LB6_StripData, 72  , "RPC Channel  72");

    setupLocalPlot (subRect73  , y0LB6_StripData, 73  , "RPC Channel  73");
    setupLocalPlot (subRect74  , y0LB6_StripData, 74  , "RPC Channel  74");
    setupLocalPlot (subRect75  , y0LB6_StripData, 75  , "RPC Channel  75");
    setupLocalPlot (subRect76  , y0LB6_StripData, 76  , "RPC Channel  76");
    setupLocalPlot (subRect77  , y0LB6_StripData, 77  , "RPC Channel  77");
    setupLocalPlot (subRect78  , y0LB6_StripData, 78  , "RPC Channel  78");

    setupLocalPlot (subRect79  , y0LB6_StripData, 79  , "RPC Channel  79");
    setupLocalPlot (subRect80  , y0LB6_StripData, 80  , "RPC Channel  80");
    setupLocalPlot (subRect81  , y0LB6_StripData, 81  , "RPC Channel  81");
    setupLocalPlot (subRect82  , y0LB6_StripData, 82  , "RPC Channel  82");
    setupLocalPlot (subRect83  , y0LB6_StripData, 83  , "RPC Channel  83");
    setupLocalPlot (subRect84  , y0LB6_StripData, 84  , "RPC Channel  84");

    setupLocalPlot (subRect85  , y0LB6_StripData, 85  , "RPC Channel  85");
    setupLocalPlot (subRect86  , y0LB6_StripData, 86  , "RPC Channel  86");
    setupLocalPlot (subRect87  , y0LB6_StripData, 87  , "RPC Channel  87");
    setupLocalPlot (subRect88  , y0LB6_StripData, 88  , "RPC Channel  88");
    setupLocalPlot (subRect89  , y0LB6_StripData, 89  , "RPC Channel  89");
    setupLocalPlot (subRect90  , y0LB6_StripData, 90  , "RPC Channel  90");

    setupLocalPlot (subRect91  , y0LB6_StripData, 91  , "RPC Channel  91");
    setupLocalPlot (subRect92  , y0LB6_StripData, 92  , "RPC Channel  92");
    setupLocalPlot (subRect93  , y0LB6_StripData, 93  , "RPC Channel  93");
    setupLocalPlot (subRect94  , y0LB6_StripData, 94  , "RPC Channel  94");
    setupLocalPlot (subRect95  , y0LB6_StripData, 95  , "RPC Channel  95");
    setupLocalPlot (subRect96  , y0LB6_StripData, 96  , "RPC Channel  96");


    connect(ui->plot_LB6, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->plot_LB6, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel(QWheelEvent*)));
    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->plot_LB6->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_LB6->xAxis, SLOT(setRange(QCPRange)));
    connect(ui->plot_LB6->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_LB6->yAxis, SLOT(setRange(QCPRange)));

    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 4);

    ui->plot_LB6->replot();

}
//=================================================

//=================================================
void realtimev2::setupPlot_LB7(void){


    //QVector <double> y1_FullWinChannel (200);
    //QVector <double> y1_AdjWinChannel (200);

    //QVector <double> x1_stripFulW (200);
    //QVector <double> x1_stripAdjW (200);
    //unsigned int stripNum ;


    // configure axis rect:
    ui->plot_LB7->plotLayout()->clear(); // clear default axis rect so we can start from scratch
    /*
    QCPAxisRect *wideAxisRect = new QCPAxisRect(ui->plot_LB7);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers
    */

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;

    ui->plot_LB7->plotLayout()->addElement(0, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
    //ui->plot_LB7->setInteractions( QCP::iRangeZoom | QCP::iSelectPlottables);
    //ui->plot_LB7->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // prepare axis rects that will be placed in the sublayout:
    QCPAxisRect *subRect1 = new QCPAxisRect(ui->plot_LB7, false); // false means to not setup default axes
    QCPAxisRect *subRect2 = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect3 = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect4 = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect5 = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect6 = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect7 = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect8 = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect9 = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect10 = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect11 = new QCPAxisRect(ui->plot_LB7, false); // false means to not setup default axes
    QCPAxisRect *subRect12 = new QCPAxisRect(ui->plot_LB7, false);

    QCPAxisRect *subRect13  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect14  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect15  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect16  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect17  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect18  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect19  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect20  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect21  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect22  = new QCPAxisRect(ui->plot_LB7, false);


    QCPAxisRect *subRect23  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect24  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect25  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect26  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect27  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect28  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect29  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect30  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect31  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect32  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect33  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect34  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect35  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect36  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect37  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect38  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect39  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect40  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect41  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect42  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect43  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect44  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect45  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect46  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect47  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect48  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect49  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect50  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect51  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect52  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect53  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect54  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect55  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect56  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect57  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect58  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect59  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect60  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect61  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect62  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect63  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect64  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect65  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect66  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect67  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect68  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect69  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect70  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect71  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect72  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect73  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect74  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect75  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect76  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect77  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect78  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect79  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect80  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect81  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect82  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect83  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect84  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect85  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect86  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect87  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect88  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect89  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect90  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect91  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect92  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect93  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect94  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect95  = new QCPAxisRect(ui->plot_LB7, false);
    QCPAxisRect *subRect96  = new QCPAxisRect(ui->plot_LB7, false);



    subLayout->addElement(0, 0, subRect1);
    subLayout->addElement(1, 0, subRect2);
    subLayout->addElement(2, 0, subRect3);
    subLayout->addElement(3, 0, subRect4);
    subLayout->addElement(4, 0, subRect5);
    subLayout->addElement(5, 0, subRect6);

    subLayout->addElement(6, 0, subRect7);
    subLayout->addElement(7, 0, subRect8);
    subLayout->addElement(8, 0, subRect9);
    subLayout->addElement(9, 0, subRect10);
    subLayout->addElement(10, 0, subRect11);
    subLayout->addElement(11, 0, subRect12);


    subLayout->addElement( 12, 0, subRect13 );
    subLayout->addElement( 13, 0, subRect14 );
    subLayout->addElement( 14, 0, subRect15 );
    subLayout->addElement( 15, 0, subRect16 );
    subLayout->addElement( 16, 0, subRect17 );
    subLayout->addElement( 17, 0, subRect18 );

    subLayout->addElement( 18, 0, subRect19 );
    subLayout->addElement( 19, 0, subRect20 );
    subLayout->addElement( 20, 0, subRect21 );
    subLayout->addElement( 21, 0, subRect22 );
    subLayout->addElement( 22, 0, subRect23 );
    subLayout->addElement( 23, 0, subRect24 );

    subLayout->addElement( 24, 0, subRect25 );
    subLayout->addElement( 25, 0, subRect26 );
    subLayout->addElement( 26, 0, subRect27 );
    subLayout->addElement( 27, 0, subRect28 );
    subLayout->addElement( 28, 0, subRect29 );
    subLayout->addElement( 29, 0, subRect30 );

    subLayout->addElement( 30, 0, subRect31 );
    subLayout->addElement( 31, 0, subRect32 );
    subLayout->addElement( 32, 0, subRect33 );
    subLayout->addElement( 33, 0, subRect34 );
    subLayout->addElement( 34, 0, subRect35 );
    subLayout->addElement( 35, 0, subRect36 );

    subLayout->addElement( 36, 0, subRect37 );
    subLayout->addElement( 37, 0, subRect38 );
    subLayout->addElement( 38, 0, subRect39 );
    subLayout->addElement( 39, 0, subRect40 );
    subLayout->addElement( 40, 0, subRect41 );
    subLayout->addElement( 41, 0, subRect42 );

    subLayout->addElement( 42, 0, subRect43 );
    subLayout->addElement( 43, 0, subRect44 );
    subLayout->addElement( 44, 0, subRect45 );
    subLayout->addElement( 45, 0, subRect46 );
    subLayout->addElement( 46, 0, subRect47 );
    subLayout->addElement( 47, 0, subRect48 );

    subLayout->addElement( 48, 0, subRect49 );
    subLayout->addElement( 49, 0, subRect50 );
    subLayout->addElement( 50, 0, subRect51 );
    subLayout->addElement( 51, 0, subRect52 );
    subLayout->addElement( 52, 0, subRect53 );
    subLayout->addElement( 53, 0, subRect54 );

    subLayout->addElement( 54, 0, subRect55 );
    subLayout->addElement( 55, 0, subRect56 );
    subLayout->addElement( 56, 0, subRect57 );
    subLayout->addElement( 57, 0, subRect58 );
    subLayout->addElement( 58, 0, subRect59 );
    subLayout->addElement( 59, 0, subRect60 );

    subLayout->addElement( 60, 0, subRect61 );
    subLayout->addElement( 61, 0, subRect62 );
    subLayout->addElement( 62, 0, subRect63 );
    subLayout->addElement( 63, 0, subRect64 );
    subLayout->addElement( 64, 0, subRect65 );
    subLayout->addElement( 65, 0, subRect66 );

    subLayout->addElement( 66, 0, subRect67 );
    subLayout->addElement( 67, 0, subRect68 );
    subLayout->addElement( 68, 0, subRect69 );
    subLayout->addElement( 69, 0, subRect70 );
    subLayout->addElement( 70, 0, subRect71 );
    subLayout->addElement( 71, 0, subRect72 );

    subLayout->addElement( 72, 0, subRect73 );
    subLayout->addElement( 73, 0, subRect74 );
    subLayout->addElement( 74, 0, subRect75 );
    subLayout->addElement( 75, 0, subRect76 );
    subLayout->addElement( 76, 0, subRect77);
    subLayout->addElement( 77, 0, subRect78 );

    subLayout->addElement( 78, 0, subRect79 );
    subLayout->addElement( 79, 0, subRect80 );
    subLayout->addElement( 80, 0, subRect81 );
    subLayout->addElement( 81, 0, subRect82 );
    subLayout->addElement( 82, 0, subRect83 );
    subLayout->addElement( 83, 0, subRect84 );

    subLayout->addElement( 84, 0, subRect85 );
    subLayout->addElement( 85, 0, subRect86 );
    subLayout->addElement( 86, 0, subRect87 );
    subLayout->addElement( 87, 0, subRect88 );
    subLayout->addElement( 88, 0, subRect89 );
    subLayout->addElement( 89, 0, subRect90 );

    subLayout->addElement( 90, 0, subRect91 );
    subLayout->addElement( 91, 0, subRect92 );
    subLayout->addElement( 92, 0, subRect93 );
    subLayout->addElement( 93, 0, subRect94 );
    subLayout->addElement( 94, 0, subRect95 );
    subLayout->addElement( 95, 0, subRect96 );


    // setup axes in sub layout axis rects:
    subRect1->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    //subRect1->axis(QCPAxis::atBottom)->ticker()->setTickCount(2);
    subRect1->axis(QCPAxis::atBottom)->grid()->setVisible(true);

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

    subRect22 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect22 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect23 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect23 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect24 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect24 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect25 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect25 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect26 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect26 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect27 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect27 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect28 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect28 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect29 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect29 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect30 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect30 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect31 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect31 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect32 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect32 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect33 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect33 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect34 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect34 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect35 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect35 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect36 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect36 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect37 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect37 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect38 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect38 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect39 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect39 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect40 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect40 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect41 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect41 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect42 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect42 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect43 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect43 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect44 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect44 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect45 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect45 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect46 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect46 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect47 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect47 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect48 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect48 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect49 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect49 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect50 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect50 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect51 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect51 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect52 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect52 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect53 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect53 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect54 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect54 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect55 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect55 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect56 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect56 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect57 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect57 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect58 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect58 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect59 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect59 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect60 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect60 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect61 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect61 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect62 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect62 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect63 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect63 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect64 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect64 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect65 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect65 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect66 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect66 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect67 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect67 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect68 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect68 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect69 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect69 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect70 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect70 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect71 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect71 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect72 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect72 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect73 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect73 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect74 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect74 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect75 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect75 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect76 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect76 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect77 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect77 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect78 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect78 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect79 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect79 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect80 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect80 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect81 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect81 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect82 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect82 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect83 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect83 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect84 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect84 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect85 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect85 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect86 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect86 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect87 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect87 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect88 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect88 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect89 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect89 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect90 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect90 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect91 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect91 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect92 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect92 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect93 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect93 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect94 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect94 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect95 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect95 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect96 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect96 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);



    // synchronize the left and right margins of the top and bottom axis rects:
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot_LB7);

    subRect1->setMarginGroup(QCP::msBottom, marginGroup);
    subRect2->setMarginGroup(QCP::msBottom, marginGroup);
    subRect3->setMarginGroup(QCP::msBottom, marginGroup);
    subRect4->setMarginGroup(QCP::msBottom, marginGroup);
    subRect5->setMarginGroup(QCP::msBottom, marginGroup);
    subRect6->setMarginGroup(QCP::msBottom, marginGroup);
    subRect7->setMarginGroup(QCP::msBottom, marginGroup);
    subRect8->setMarginGroup(QCP::msBottom, marginGroup);
    subRect9->setMarginGroup(QCP::msBottom, marginGroup);
    subRect10->setMarginGroup(QCP::msBottom, marginGroup);
    subRect11->setMarginGroup(QCP::msBottom, marginGroup);
    subRect12->setMarginGroup(QCP::msBottom, marginGroup);

    subRect13  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect14  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect15  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect16  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect17  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect18  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect19  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect20  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect21  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect22  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect23  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect24  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect25  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect26  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect27  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect28  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect29  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect30  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect31  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect32  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect33  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect34  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect35  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect36  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect37  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect38  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect39  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect40  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect41  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect42  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect43  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect44  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect45  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect46  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect47  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect48  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect49  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect50  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect51  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect52  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect53  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect54  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect55  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect56  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect57  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect58  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect59  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect60  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect61  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect62  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect63  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect64  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect65  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect66  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect67  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect68  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect69  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect70  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect71  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect72  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect73  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect74  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect75  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect76  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect77  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect78  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect79  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect80  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect81  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect82  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect83  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect84  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect85  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect86  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect87  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect88  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect89  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect90  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect91  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect92  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect93  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect94  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect95  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect96  ->setMarginGroup(QCP::msBottom, marginGroup);




    //wideAxisRect->setMarginGroup(QCP::msTop | QCP::msBottom | QCP::msRight | QCP::msLeft, marginGroup);


    // move newly created axes on "axes" layer and grids on "grid" layer:

    foreach (QCPAxisRect *rect, ui->plot_LB7->axisRects())
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
    ui->plot_LB7->setBackground(QBrush(gradient));
    //==================================================================
    //
    //==================================================================




    setupLocalPlot (subRect1  , y0LB7_StripData, 1 , "RPC Channel  1");
    setupLocalPlot (subRect2  , y0LB7_StripData, 2 , "RPC Channel  2");
    setupLocalPlot (subRect3  , y0LB7_StripData, 3 , "RPC Channel  3");
    setupLocalPlot (subRect4  , y0LB7_StripData, 4 , "RPC Channel  4");
    setupLocalPlot (subRect5  , y0LB7_StripData, 5 , "RPC Channel  5");
    setupLocalPlot (subRect6  , y0LB7_StripData,  6 , "RPC Channel  6");

    setupLocalPlot (subRect7  , y0LB7_StripData,  7 , "RPC Channel  7");
    setupLocalPlot (subRect8  , y0LB7_StripData,  8 , "RPC Channel  8");
    setupLocalPlot (subRect9  , y0LB7_StripData,  9 , "RPC Channel  9");
    setupLocalPlot (subRect10 , y0LB7_StripData,  10 , "RPC Channel  10");
    setupLocalPlot (subRect11 , y0LB7_StripData,  11 , "RPC Channel  11");
    setupLocalPlot (subRect12 , y0LB7_StripData,  12 , "RPC Channel  12");

    setupLocalPlot (subRect13  , y0LB7_StripData,  13  , "RPC Channel 13");
    setupLocalPlot (subRect14  , y0LB7_StripData,  14  , "RPC Channel 14");
    setupLocalPlot (subRect15  , y0LB7_StripData,  15  , "RPC Channel 15");
    setupLocalPlot (subRect16  , y0LB7_StripData,  16  , "RPC Channel 16");
    setupLocalPlot (subRect17  , y0LB7_StripData, 17  , "RPC Channel 17");
    setupLocalPlot (subRect18  , y0LB7_StripData, 18  , "RPC Channel 18");

    setupLocalPlot (subRect19  , y0LB7_StripData, 19  , "RPC Channel 19");
    setupLocalPlot (subRect20  , y0LB7_StripData,  20 , "RPC Channel  20");
    setupLocalPlot (subRect21  , y0LB7_StripData, 21  , "RPC Channel  21");
    setupLocalPlot (subRect22  , y0LB7_StripData, 22  , "RPC Channel  22");
    setupLocalPlot (subRect23  , y0LB7_StripData, 23  , "RPC Channel  23");
    setupLocalPlot (subRect24  , y0LB7_StripData, 24  , "RPC Channel  24");

    setupLocalPlot (subRect25  , y0LB7_StripData, 25  , "RPC Channel  25");
    setupLocalPlot (subRect26  , y0LB7_StripData, 26  , "RPC Channel  26");
    setupLocalPlot (subRect27  , y0LB7_StripData, 27  , "RPC Channel  27");
    setupLocalPlot (subRect28  , y0LB7_StripData, 28  , "RPC Channel  28");
    setupLocalPlot (subRect29  , y0LB7_StripData, 29  , "RPC Channel  29");
    setupLocalPlot (subRect30  , y0LB7_StripData, 30  , "RPC Channel  30");

    setupLocalPlot (subRect31  , y0LB7_StripData, 31  , "RPC Channel  31");
    setupLocalPlot (subRect32  , y0LB7_StripData, 32  , "RPC Channel  32");
    setupLocalPlot (subRect33  , y0LB7_StripData, 33  , "RPC Channel  33");
    setupLocalPlot (subRect34  , y0LB7_StripData, 34  , "RPC Channel  34");
    setupLocalPlot (subRect35  , y0LB7_StripData, 35  , "RPC Channel  35");
    setupLocalPlot (subRect36  , y0LB7_StripData, 36  , "RPC Channel  36");

    setupLocalPlot (subRect37  , y0LB7_StripData, 37  , "RPC Channel  37");
    setupLocalPlot (subRect38  , y0LB7_StripData, 38  , "RPC Channel  38");
    setupLocalPlot (subRect39  , y0LB7_StripData, 39  , "RPC Channel  39");
    setupLocalPlot (subRect40  , y0LB7_StripData, 40  , "RPC Channel  40");
    setupLocalPlot (subRect41  , y0LB7_StripData, 41  , "RPC Channel  41");
    setupLocalPlot (subRect42  , y0LB7_StripData, 42  , "RPC Channel  42");

    setupLocalPlot (subRect43  , y0LB7_StripData, 43  , "RPC Channel  43");
    setupLocalPlot (subRect44  , y0LB7_StripData, 44  , "RPC Channel  44");
    setupLocalPlot (subRect45  , y0LB7_StripData, 45  , "RPC Channel  45");
    setupLocalPlot (subRect46  , y0LB7_StripData, 46  , "RPC Channel  46");
    setupLocalPlot (subRect47  , y0LB7_StripData, 47  , "RPC Channel  47");
    setupLocalPlot (subRect48  , y0LB7_StripData, 48  , "RPC Channel  48");

    setupLocalPlot (subRect49  , y0LB7_StripData, 49  , "RPC Channel  49");
    setupLocalPlot (subRect50  , y0LB7_StripData, 50  , "RPC Channel  50");
    setupLocalPlot (subRect51  , y0LB7_StripData, 51  , "RPC Channel  51");
    setupLocalPlot (subRect52  , y0LB7_StripData, 52  , "RPC Channel  52");
    setupLocalPlot (subRect53  , y0LB7_StripData, 53  , "RPC Channel  53");
    setupLocalPlot (subRect54  , y0LB7_StripData, 54  , "RPC Channel  54");

    setupLocalPlot (subRect55  , y0LB7_StripData, 55  , "RPC Channel  55");
    setupLocalPlot (subRect56  , y0LB7_StripData, 56  , "RPC Channel  56");
    setupLocalPlot (subRect57  , y0LB7_StripData, 57  , "RPC Channel  57");
    setupLocalPlot (subRect58  , y0LB7_StripData, 58  , "RPC Channel  58");
    setupLocalPlot (subRect59  , y0LB7_StripData, 59  , "RPC Channel  59");
    setupLocalPlot (subRect60  , y0LB7_StripData, 60  , "RPC Channel  60");

    setupLocalPlot (subRect61  , y0LB7_StripData, 61  , "RPC Channel  61");
    setupLocalPlot (subRect62  , y0LB7_StripData, 62  , "RPC Channel  62");
    setupLocalPlot (subRect63  , y0LB7_StripData, 62  , "RPC Channel  63");
    setupLocalPlot (subRect64  , y0LB7_StripData, 64  , "RPC Channel  64");
    setupLocalPlot (subRect65  , y0LB7_StripData, 65  , "RPC Channel  65");
    setupLocalPlot (subRect66  , y0LB7_StripData, 66  , "RPC Channel  66");

    setupLocalPlot (subRect67  , y0LB7_StripData, 67  , "RPC Channel  67");
    setupLocalPlot (subRect68  , y0LB7_StripData, 68  , "RPC Channel  68");
    setupLocalPlot (subRect69  , y0LB7_StripData, 69  , "RPC Channel  69");
    setupLocalPlot (subRect70  , y0LB7_StripData, 70  , "RPC Channel  70");
    setupLocalPlot (subRect71  , y0LB7_StripData, 71  , "RPC Channel  71");
    setupLocalPlot (subRect72  , y0LB7_StripData, 72  , "RPC Channel  72");

    setupLocalPlot (subRect73  , y0LB7_StripData, 73  , "RPC Channel  73");
    setupLocalPlot (subRect74  , y0LB7_StripData, 74  , "RPC Channel  74");
    setupLocalPlot (subRect75  , y0LB7_StripData, 75  , "RPC Channel  75");
    setupLocalPlot (subRect76  , y0LB7_StripData, 76  , "RPC Channel  76");
    setupLocalPlot (subRect77  , y0LB7_StripData, 77  , "RPC Channel  77");
    setupLocalPlot (subRect78  , y0LB7_StripData, 78  , "RPC Channel  78");

    setupLocalPlot (subRect79  , y0LB7_StripData, 79  , "RPC Channel  79");
    setupLocalPlot (subRect80  , y0LB7_StripData, 80  , "RPC Channel  80");
    setupLocalPlot (subRect81  , y0LB7_StripData, 81  , "RPC Channel  81");
    setupLocalPlot (subRect82  , y0LB7_StripData, 82  , "RPC Channel  82");
    setupLocalPlot (subRect83  , y0LB7_StripData, 83  , "RPC Channel  83");
    setupLocalPlot (subRect84  , y0LB7_StripData, 84  , "RPC Channel  84");

    setupLocalPlot (subRect85  , y0LB7_StripData, 85  , "RPC Channel  85");
    setupLocalPlot (subRect86  , y0LB7_StripData, 86  , "RPC Channel  86");
    setupLocalPlot (subRect87  , y0LB7_StripData, 87  , "RPC Channel  87");
    setupLocalPlot (subRect88  , y0LB7_StripData, 88  , "RPC Channel  88");
    setupLocalPlot (subRect89  , y0LB7_StripData, 89  , "RPC Channel  89");
    setupLocalPlot (subRect90  , y0LB7_StripData, 90  , "RPC Channel  90");

    setupLocalPlot (subRect91  , y0LB7_StripData, 91  , "RPC Channel  91");
    setupLocalPlot (subRect92  , y0LB7_StripData, 92  , "RPC Channel  92");
    setupLocalPlot (subRect93  , y0LB7_StripData, 93  , "RPC Channel  93");
    setupLocalPlot (subRect94  , y0LB7_StripData, 94  , "RPC Channel  94");
    setupLocalPlot (subRect95  , y0LB7_StripData, 95  , "RPC Channel  95");
    setupLocalPlot (subRect96  , y0LB7_StripData, 96  , "RPC Channel  96");


    connect(ui->plot_LB7, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->plot_LB7, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel(QWheelEvent*)));
    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->plot_LB7->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_LB7->xAxis, SLOT(setRange(QCPRange)));
    connect(ui->plot_LB7->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_LB7->yAxis, SLOT(setRange(QCPRange)));

    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 3);

    ui->plot_LB7->replot();

}
//=================================================

//=================================================
void realtimev2::setupPlot_LB8(void){


    //QVector <double> y1_FullWinChannel (200);
    //QVector <double> y1_AdjWinChannel (200);

    //QVector <double> x1_stripFulW (200);
    //QVector <double> x1_stripAdjW (200);
    //unsigned int stripNum ;


    // configure axis rect:
    ui->plot_LB8->plotLayout()->clear(); // clear default axis rect so we can start from scratch
    /*
    QCPAxisRect *wideAxisRect = new QCPAxisRect(ui->plot_LB8);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers
    */

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;

    ui->plot_LB8->plotLayout()->addElement(0, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
    //ui->plot_LB8->setInteractions( QCP::iRangeZoom | QCP::iSelectPlottables);
    //ui->plot_LB8->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // prepare axis rects that will be placed in the sublayout:
    QCPAxisRect *subRect1 = new QCPAxisRect(ui->plot_LB8, false); // false means to not setup default axes
    QCPAxisRect *subRect2 = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect3 = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect4 = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect5 = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect6 = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect7 = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect8 = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect9 = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect10 = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect11 = new QCPAxisRect(ui->plot_LB8, false); // false means to not setup default axes
    QCPAxisRect *subRect12 = new QCPAxisRect(ui->plot_LB8, false);

    QCPAxisRect *subRect13  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect14  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect15  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect16  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect17  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect18  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect19  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect20  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect21  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect22  = new QCPAxisRect(ui->plot_LB8, false);


    QCPAxisRect *subRect23  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect24  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect25  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect26  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect27  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect28  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect29  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect30  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect31  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect32  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect33  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect34  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect35  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect36  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect37  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect38  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect39  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect40  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect41  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect42  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect43  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect44  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect45  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect46  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect47  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect48  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect49  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect50  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect51  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect52  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect53  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect54  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect55  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect56  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect57  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect58  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect59  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect60  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect61  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect62  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect63  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect64  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect65  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect66  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect67  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect68  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect69  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect70  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect71  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect72  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect73  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect74  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect75  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect76  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect77  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect78  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect79  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect80  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect81  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect82  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect83  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect84  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect85  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect86  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect87  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect88  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect89  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect90  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect91  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect92  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect93  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect94  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect95  = new QCPAxisRect(ui->plot_LB8, false);
    QCPAxisRect *subRect96  = new QCPAxisRect(ui->plot_LB8, false);



    subLayout->addElement(0, 0, subRect1);
    subLayout->addElement(1, 0, subRect2);
    subLayout->addElement(2, 0, subRect3);
    subLayout->addElement(3, 0, subRect4);
    subLayout->addElement(4, 0, subRect5);
    subLayout->addElement(5, 0, subRect6);

    subLayout->addElement(6, 0, subRect7);
    subLayout->addElement(7, 0, subRect8);
    subLayout->addElement(8, 0, subRect9);
    subLayout->addElement(9, 0, subRect10);
    subLayout->addElement(10, 0, subRect11);
    subLayout->addElement(11, 0, subRect12);


    subLayout->addElement( 12, 0, subRect13 );
    subLayout->addElement( 13, 0, subRect14 );
    subLayout->addElement( 14, 0, subRect15 );
    subLayout->addElement( 15, 0, subRect16 );
    subLayout->addElement( 16, 0, subRect17 );
    subLayout->addElement( 17, 0, subRect18 );

    subLayout->addElement( 18, 0, subRect19 );
    subLayout->addElement( 19, 0, subRect20 );
    subLayout->addElement( 20, 0, subRect21 );
    subLayout->addElement( 21, 0, subRect22 );
    subLayout->addElement( 22, 0, subRect23 );
    subLayout->addElement( 23, 0, subRect24 );

    subLayout->addElement( 24, 0, subRect25 );
    subLayout->addElement( 25, 0, subRect26 );
    subLayout->addElement( 26, 0, subRect27 );
    subLayout->addElement( 27, 0, subRect28 );
    subLayout->addElement( 28, 0, subRect29 );
    subLayout->addElement( 29, 0, subRect30 );

    subLayout->addElement( 30, 0, subRect31 );
    subLayout->addElement( 31, 0, subRect32 );
    subLayout->addElement( 32, 0, subRect33 );
    subLayout->addElement( 33, 0, subRect34 );
    subLayout->addElement( 34, 0, subRect35 );
    subLayout->addElement( 35, 0, subRect36 );

    subLayout->addElement( 36, 0, subRect37 );
    subLayout->addElement( 37, 0, subRect38 );
    subLayout->addElement( 38, 0, subRect39 );
    subLayout->addElement( 39, 0, subRect40 );
    subLayout->addElement( 40, 0, subRect41 );
    subLayout->addElement( 41, 0, subRect42 );

    subLayout->addElement( 42, 0, subRect43 );
    subLayout->addElement( 43, 0, subRect44 );
    subLayout->addElement( 44, 0, subRect45 );
    subLayout->addElement( 45, 0, subRect46 );
    subLayout->addElement( 46, 0, subRect47 );
    subLayout->addElement( 47, 0, subRect48 );

    subLayout->addElement( 48, 0, subRect49 );
    subLayout->addElement( 49, 0, subRect50 );
    subLayout->addElement( 50, 0, subRect51 );
    subLayout->addElement( 51, 0, subRect52 );
    subLayout->addElement( 52, 0, subRect53 );
    subLayout->addElement( 53, 0, subRect54 );

    subLayout->addElement( 54, 0, subRect55 );
    subLayout->addElement( 55, 0, subRect56 );
    subLayout->addElement( 56, 0, subRect57 );
    subLayout->addElement( 57, 0, subRect58 );
    subLayout->addElement( 58, 0, subRect59 );
    subLayout->addElement( 59, 0, subRect60 );

    subLayout->addElement( 60, 0, subRect61 );
    subLayout->addElement( 61, 0, subRect62 );
    subLayout->addElement( 62, 0, subRect63 );
    subLayout->addElement( 63, 0, subRect64 );
    subLayout->addElement( 64, 0, subRect65 );
    subLayout->addElement( 65, 0, subRect66 );

    subLayout->addElement( 66, 0, subRect67 );
    subLayout->addElement( 67, 0, subRect68 );
    subLayout->addElement( 68, 0, subRect69 );
    subLayout->addElement( 69, 0, subRect70 );
    subLayout->addElement( 70, 0, subRect71 );
    subLayout->addElement( 71, 0, subRect72 );

    subLayout->addElement( 72, 0, subRect73 );
    subLayout->addElement( 73, 0, subRect74 );
    subLayout->addElement( 74, 0, subRect75 );
    subLayout->addElement( 75, 0, subRect76 );
    subLayout->addElement( 76, 0, subRect77);
    subLayout->addElement( 77, 0, subRect78 );

    subLayout->addElement( 78, 0, subRect79 );
    subLayout->addElement( 79, 0, subRect80 );
    subLayout->addElement( 80, 0, subRect81 );
    subLayout->addElement( 81, 0, subRect82 );
    subLayout->addElement( 82, 0, subRect83 );
    subLayout->addElement( 83, 0, subRect84 );

    subLayout->addElement( 84, 0, subRect85 );
    subLayout->addElement( 85, 0, subRect86 );
    subLayout->addElement( 86, 0, subRect87 );
    subLayout->addElement( 87, 0, subRect88 );
    subLayout->addElement( 88, 0, subRect89 );
    subLayout->addElement( 89, 0, subRect90 );

    subLayout->addElement( 90, 0, subRect91 );
    subLayout->addElement( 91, 0, subRect92 );
    subLayout->addElement( 92, 0, subRect93 );
    subLayout->addElement( 93, 0, subRect94 );
    subLayout->addElement( 94, 0, subRect95 );
    subLayout->addElement( 95, 0, subRect96 );


    // setup axes in sub layout axis rects:
    subRect1->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    //subRect1->axis(QCPAxis::atBottom)->ticker()->setTickCount(2);
    subRect1->axis(QCPAxis::atBottom)->grid()->setVisible(true);

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

    subRect22 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect22 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect23 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect23 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect24 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect24 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect25 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect25 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect26 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect26 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect27 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect27 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect28 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect28 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect29 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect29 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect30 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect30 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect31 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect31 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect32 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect32 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect33 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect33 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect34 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect34 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect35 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect35 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect36 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect36 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect37 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect37 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect38 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect38 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect39 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect39 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect40 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect40 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect41 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect41 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect42 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect42 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect43 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect43 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect44 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect44 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect45 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect45 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect46 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect46 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect47 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect47 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect48 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect48 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect49 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect49 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect50 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect50 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect51 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect51 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect52 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect52 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect53 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect53 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect54 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect54 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect55 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect55 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect56 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect56 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect57 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect57 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect58 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect58 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect59 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect59 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect60 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect60 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect61 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect61 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect62 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect62 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect63 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect63 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect64 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect64 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect65 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect65 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect66 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect66 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect67 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect67 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect68 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect68 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect69 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect69 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect70 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect70 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect71 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect71 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect72 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect72 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect73 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect73 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect74 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect74 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect75 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect75 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect76 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect76 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect77 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect77 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect78 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect78 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect79 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect79 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect80 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect80 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect81 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect81 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect82 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect82 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect83 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect83 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect84 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect84 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect85 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect85 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect86 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect86 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect87 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect87 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect88 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect88 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect89 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect89 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect90 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect90 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect91 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect91 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect92 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect92 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect93 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect93 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect94 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect94 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect95 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect95 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect96 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect96 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);



    // synchronize the left and right margins of the top and bottom axis rects:
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot_LB8);

    subRect1->setMarginGroup(QCP::msBottom, marginGroup);
    subRect2->setMarginGroup(QCP::msBottom, marginGroup);
    subRect3->setMarginGroup(QCP::msBottom, marginGroup);
    subRect4->setMarginGroup(QCP::msBottom, marginGroup);
    subRect5->setMarginGroup(QCP::msBottom, marginGroup);
    subRect6->setMarginGroup(QCP::msBottom, marginGroup);
    subRect7->setMarginGroup(QCP::msBottom, marginGroup);
    subRect8->setMarginGroup(QCP::msBottom, marginGroup);
    subRect9->setMarginGroup(QCP::msBottom, marginGroup);
    subRect10->setMarginGroup(QCP::msBottom, marginGroup);
    subRect11->setMarginGroup(QCP::msBottom, marginGroup);
    subRect12->setMarginGroup(QCP::msBottom, marginGroup);

    subRect13  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect14  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect15  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect16  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect17  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect18  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect19  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect20  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect21  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect22  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect23  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect24  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect25  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect26  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect27  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect28  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect29  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect30  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect31  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect32  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect33  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect34  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect35  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect36  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect37  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect38  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect39  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect40  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect41  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect42  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect43  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect44  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect45  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect46  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect47  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect48  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect49  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect50  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect51  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect52  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect53  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect54  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect55  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect56  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect57  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect58  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect59  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect60  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect61  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect62  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect63  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect64  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect65  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect66  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect67  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect68  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect69  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect70  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect71  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect72  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect73  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect74  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect75  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect76  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect77  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect78  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect79  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect80  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect81  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect82  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect83  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect84  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect85  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect86  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect87  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect88  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect89  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect90  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect91  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect92  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect93  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect94  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect95  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect96  ->setMarginGroup(QCP::msBottom, marginGroup);




    //wideAxisRect->setMarginGroup(QCP::msTop | QCP::msBottom | QCP::msRight | QCP::msLeft, marginGroup);


    // move newly created axes on "axes" layer and grids on "grid" layer:

    foreach (QCPAxisRect *rect, ui->plot_LB8->axisRects())
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
    ui->plot_LB8->setBackground(QBrush(gradient));
    //==================================================================
    //
    //==================================================================




    setupLocalPlot (subRect1  , y0LB8_StripData, 1 , "RPC Channel  1");
    setupLocalPlot (subRect2  , y0LB8_StripData, 2 , "RPC Channel  2");
    setupLocalPlot (subRect3  , y0LB8_StripData, 3 , "RPC Channel  3");
    setupLocalPlot (subRect4  , y0LB8_StripData, 4 , "RPC Channel  4");
    setupLocalPlot (subRect5  , y0LB8_StripData, 5 , "RPC Channel  5");
    setupLocalPlot (subRect6  , y0LB8_StripData,  6 , "RPC Channel  6");

    setupLocalPlot (subRect7  , y0LB8_StripData,  7 , "RPC Channel  7");
    setupLocalPlot (subRect8  , y0LB8_StripData,  8 , "RPC Channel  8");
    setupLocalPlot (subRect9  , y0LB8_StripData,  9 , "RPC Channel  9");
    setupLocalPlot (subRect10 , y0LB8_StripData,  10 , "RPC Channel  10");
    setupLocalPlot (subRect11 , y0LB8_StripData,  11 , "RPC Channel  11");
    setupLocalPlot (subRect12 , y0LB8_StripData,  12 , "RPC Channel  12");

    setupLocalPlot (subRect13  , y0LB8_StripData,  13  , "RPC Channel 13");
    setupLocalPlot (subRect14  , y0LB8_StripData,  14  , "RPC Channel 14");
    setupLocalPlot (subRect15  , y0LB8_StripData,  15  , "RPC Channel 15");
    setupLocalPlot (subRect16  , y0LB8_StripData,  16  , "RPC Channel 16");
    setupLocalPlot (subRect17  , y0LB8_StripData, 17  , "RPC Channel 17");
    setupLocalPlot (subRect18  , y0LB8_StripData, 18  , "RPC Channel 18");

    setupLocalPlot (subRect19  , y0LB8_StripData, 19  , "RPC Channel 19");
    setupLocalPlot (subRect20  , y0LB8_StripData,  20 , "RPC Channel  20");
    setupLocalPlot (subRect21  , y0LB8_StripData, 21  , "RPC Channel  21");
    setupLocalPlot (subRect22  , y0LB8_StripData, 22  , "RPC Channel  22");
    setupLocalPlot (subRect23  , y0LB8_StripData, 23  , "RPC Channel  23");
    setupLocalPlot (subRect24  , y0LB8_StripData, 24  , "RPC Channel  24");

    setupLocalPlot (subRect25  , y0LB8_StripData, 25  , "RPC Channel  25");
    setupLocalPlot (subRect26  , y0LB8_StripData, 26  , "RPC Channel  26");
    setupLocalPlot (subRect27  , y0LB8_StripData, 27  , "RPC Channel  27");
    setupLocalPlot (subRect28  , y0LB8_StripData, 28  , "RPC Channel  28");
    setupLocalPlot (subRect29  , y0LB8_StripData, 29  , "RPC Channel  29");
    setupLocalPlot (subRect30  , y0LB8_StripData, 30  , "RPC Channel  30");

    setupLocalPlot (subRect31  , y0LB8_StripData, 31  , "RPC Channel  31");
    setupLocalPlot (subRect32  , y0LB8_StripData, 32  , "RPC Channel  32");
    setupLocalPlot (subRect33  , y0LB8_StripData, 33  , "RPC Channel  33");
    setupLocalPlot (subRect34  , y0LB8_StripData, 34  , "RPC Channel  34");
    setupLocalPlot (subRect35  , y0LB8_StripData, 35  , "RPC Channel  35");
    setupLocalPlot (subRect36  , y0LB8_StripData, 36  , "RPC Channel  36");

    setupLocalPlot (subRect37  , y0LB8_StripData, 37  , "RPC Channel  37");
    setupLocalPlot (subRect38  , y0LB8_StripData, 38  , "RPC Channel  38");
    setupLocalPlot (subRect39  , y0LB8_StripData, 39  , "RPC Channel  39");
    setupLocalPlot (subRect40  , y0LB8_StripData, 40  , "RPC Channel  40");
    setupLocalPlot (subRect41  , y0LB8_StripData, 41  , "RPC Channel  41");
    setupLocalPlot (subRect42  , y0LB8_StripData, 42  , "RPC Channel  42");

    setupLocalPlot (subRect43  , y0LB8_StripData, 43  , "RPC Channel  43");
    setupLocalPlot (subRect44  , y0LB8_StripData, 44  , "RPC Channel  44");
    setupLocalPlot (subRect45  , y0LB8_StripData, 45  , "RPC Channel  45");
    setupLocalPlot (subRect46  , y0LB8_StripData, 46  , "RPC Channel  46");
    setupLocalPlot (subRect47  , y0LB8_StripData, 47  , "RPC Channel  47");
    setupLocalPlot (subRect48  , y0LB8_StripData, 48  , "RPC Channel  48");

    setupLocalPlot (subRect49  , y0LB8_StripData, 49  , "RPC Channel  49");
    setupLocalPlot (subRect50  , y0LB8_StripData, 50  , "RPC Channel  50");
    setupLocalPlot (subRect51  , y0LB8_StripData, 51  , "RPC Channel  51");
    setupLocalPlot (subRect52  , y0LB8_StripData, 52  , "RPC Channel  52");
    setupLocalPlot (subRect53  , y0LB8_StripData, 53  , "RPC Channel  53");
    setupLocalPlot (subRect54  , y0LB8_StripData, 54  , "RPC Channel  54");

    setupLocalPlot (subRect55  , y0LB8_StripData, 55  , "RPC Channel  55");
    setupLocalPlot (subRect56  , y0LB8_StripData, 56  , "RPC Channel  56");
    setupLocalPlot (subRect57  , y0LB8_StripData, 57  , "RPC Channel  57");
    setupLocalPlot (subRect58  , y0LB8_StripData, 58  , "RPC Channel  58");
    setupLocalPlot (subRect59  , y0LB8_StripData, 59  , "RPC Channel  59");
    setupLocalPlot (subRect60  , y0LB8_StripData, 60  , "RPC Channel  60");

    setupLocalPlot (subRect61  , y0LB8_StripData, 61  , "RPC Channel  61");
    setupLocalPlot (subRect62  , y0LB8_StripData, 62  , "RPC Channel  62");
    setupLocalPlot (subRect63  , y0LB8_StripData, 62  , "RPC Channel  63");
    setupLocalPlot (subRect64  , y0LB8_StripData, 64  , "RPC Channel  64");
    setupLocalPlot (subRect65  , y0LB8_StripData, 65  , "RPC Channel  65");
    setupLocalPlot (subRect66  , y0LB8_StripData, 66  , "RPC Channel  66");

    setupLocalPlot (subRect67  , y0LB8_StripData, 67  , "RPC Channel  67");
    setupLocalPlot (subRect68  , y0LB8_StripData, 68  , "RPC Channel  68");
    setupLocalPlot (subRect69  , y0LB8_StripData, 69  , "RPC Channel  69");
    setupLocalPlot (subRect70  , y0LB8_StripData, 70  , "RPC Channel  70");
    setupLocalPlot (subRect71  , y0LB8_StripData, 71  , "RPC Channel  71");
    setupLocalPlot (subRect72  , y0LB8_StripData, 72  , "RPC Channel  72");

    setupLocalPlot (subRect73  , y0LB8_StripData, 73  , "RPC Channel  73");
    setupLocalPlot (subRect74  , y0LB8_StripData, 74  , "RPC Channel  74");
    setupLocalPlot (subRect75  , y0LB8_StripData, 75  , "RPC Channel  75");
    setupLocalPlot (subRect76  , y0LB8_StripData, 76  , "RPC Channel  76");
    setupLocalPlot (subRect77  , y0LB8_StripData, 77  , "RPC Channel  77");
    setupLocalPlot (subRect78  , y0LB8_StripData, 78  , "RPC Channel  78");

    setupLocalPlot (subRect79  , y0LB8_StripData, 79  , "RPC Channel  79");
    setupLocalPlot (subRect80  , y0LB8_StripData, 80  , "RPC Channel  80");
    setupLocalPlot (subRect81  , y0LB8_StripData, 81  , "RPC Channel  81");
    setupLocalPlot (subRect82  , y0LB8_StripData, 82  , "RPC Channel  82");
    setupLocalPlot (subRect83  , y0LB8_StripData, 83  , "RPC Channel  83");
    setupLocalPlot (subRect84  , y0LB8_StripData, 84  , "RPC Channel  84");

    setupLocalPlot (subRect85  , y0LB8_StripData, 85  , "RPC Channel  85");
    setupLocalPlot (subRect86  , y0LB8_StripData, 86  , "RPC Channel  86");
    setupLocalPlot (subRect87  , y0LB8_StripData, 87  , "RPC Channel  87");
    setupLocalPlot (subRect88  , y0LB8_StripData, 88  , "RPC Channel  88");
    setupLocalPlot (subRect89  , y0LB8_StripData, 89  , "RPC Channel  89");
    setupLocalPlot (subRect90  , y0LB8_StripData, 90  , "RPC Channel  90");

    setupLocalPlot (subRect91  , y0LB8_StripData, 91  , "RPC Channel  91");
    setupLocalPlot (subRect92  , y0LB8_StripData, 92  , "RPC Channel  92");
    setupLocalPlot (subRect93  , y0LB8_StripData, 93  , "RPC Channel  93");
    setupLocalPlot (subRect94  , y0LB8_StripData, 94  , "RPC Channel  94");
    setupLocalPlot (subRect95  , y0LB8_StripData, 95  , "RPC Channel  95");
    setupLocalPlot (subRect96  , y0LB8_StripData, 96  , "RPC Channel  96");


    connect(ui->plot_LB8, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->plot_LB8, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel(QWheelEvent*)));
    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->plot_LB8->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_LB8->xAxis, SLOT(setRange(QCPRange)));
    connect(ui->plot_LB8->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_LB8->yAxis, SLOT(setRange(QCPRange)));

    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 2);

    ui->plot_LB8->replot();

}
//=================================================

//=================================================
void realtimev2::setupPlot_LB9(void){


    //QVector <double> y1_FullWinChannel (200);
    //QVector <double> y1_AdjWinChannel (200);

    //QVector <double> x1_stripFulW (200);
    //QVector <double> x1_stripAdjW (200);
    //unsigned int stripNum ;


    // configure axis rect:
    ui->plot_LB9->plotLayout()->clear(); // clear default axis rect so we can start from scratch
    /*
    QCPAxisRect *wideAxisRect = new QCPAxisRect(ui->plot_LB9);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);
    wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers
    */

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;

    ui->plot_LB9->plotLayout()->addElement(0, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
    //ui->plot_LB9->setInteractions( QCP::iRangeZoom | QCP::iSelectPlottables);
    //ui->plot_LB9->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // prepare axis rects that will be placed in the sublayout:
    QCPAxisRect *subRect1 = new QCPAxisRect(ui->plot_LB9, false); // false means to not setup default axes
    QCPAxisRect *subRect2 = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect3 = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect4 = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect5 = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect6 = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect7 = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect8 = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect9 = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect10 = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect11 = new QCPAxisRect(ui->plot_LB9, false); // false means to not setup default axes
    QCPAxisRect *subRect12 = new QCPAxisRect(ui->plot_LB9, false);

    QCPAxisRect *subRect13  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect14  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect15  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect16  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect17  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect18  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect19  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect20  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect21  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect22  = new QCPAxisRect(ui->plot_LB9, false);


    QCPAxisRect *subRect23  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect24  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect25  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect26  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect27  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect28  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect29  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect30  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect31  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect32  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect33  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect34  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect35  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect36  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect37  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect38  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect39  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect40  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect41  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect42  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect43  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect44  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect45  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect46  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect47  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect48  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect49  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect50  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect51  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect52  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect53  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect54  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect55  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect56  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect57  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect58  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect59  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect60  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect61  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect62  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect63  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect64  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect65  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect66  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect67  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect68  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect69  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect70  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect71  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect72  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect73  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect74  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect75  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect76  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect77  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect78  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect79  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect80  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect81  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect82  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect83  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect84  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect85  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect86  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect87  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect88  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect89  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect90  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect91  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect92  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect93  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect94  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect95  = new QCPAxisRect(ui->plot_LB9, false);
    QCPAxisRect *subRect96  = new QCPAxisRect(ui->plot_LB9, false);



    subLayout->addElement(0, 0, subRect1);
    subLayout->addElement(1, 0, subRect2);
    subLayout->addElement(2, 0, subRect3);
    subLayout->addElement(3, 0, subRect4);
    subLayout->addElement(4, 0, subRect5);
    subLayout->addElement(5, 0, subRect6);

    subLayout->addElement(6, 0, subRect7);
    subLayout->addElement(7, 0, subRect8);
    subLayout->addElement(8, 0, subRect9);
    subLayout->addElement(9, 0, subRect10);
    subLayout->addElement(10, 0, subRect11);
    subLayout->addElement(11, 0, subRect12);


    subLayout->addElement( 12, 0, subRect13 );
    subLayout->addElement( 13, 0, subRect14 );
    subLayout->addElement( 14, 0, subRect15 );
    subLayout->addElement( 15, 0, subRect16 );
    subLayout->addElement( 16, 0, subRect17 );
    subLayout->addElement( 17, 0, subRect18 );

    subLayout->addElement( 18, 0, subRect19 );
    subLayout->addElement( 19, 0, subRect20 );
    subLayout->addElement( 20, 0, subRect21 );
    subLayout->addElement( 21, 0, subRect22 );
    subLayout->addElement( 22, 0, subRect23 );
    subLayout->addElement( 23, 0, subRect24 );

    subLayout->addElement( 24, 0, subRect25 );
    subLayout->addElement( 25, 0, subRect26 );
    subLayout->addElement( 26, 0, subRect27 );
    subLayout->addElement( 27, 0, subRect28 );
    subLayout->addElement( 28, 0, subRect29 );
    subLayout->addElement( 29, 0, subRect30 );

    subLayout->addElement( 30, 0, subRect31 );
    subLayout->addElement( 31, 0, subRect32 );
    subLayout->addElement( 32, 0, subRect33 );
    subLayout->addElement( 33, 0, subRect34 );
    subLayout->addElement( 34, 0, subRect35 );
    subLayout->addElement( 35, 0, subRect36 );

    subLayout->addElement( 36, 0, subRect37 );
    subLayout->addElement( 37, 0, subRect38 );
    subLayout->addElement( 38, 0, subRect39 );
    subLayout->addElement( 39, 0, subRect40 );
    subLayout->addElement( 40, 0, subRect41 );
    subLayout->addElement( 41, 0, subRect42 );

    subLayout->addElement( 42, 0, subRect43 );
    subLayout->addElement( 43, 0, subRect44 );
    subLayout->addElement( 44, 0, subRect45 );
    subLayout->addElement( 45, 0, subRect46 );
    subLayout->addElement( 46, 0, subRect47 );
    subLayout->addElement( 47, 0, subRect48 );

    subLayout->addElement( 48, 0, subRect49 );
    subLayout->addElement( 49, 0, subRect50 );
    subLayout->addElement( 50, 0, subRect51 );
    subLayout->addElement( 51, 0, subRect52 );
    subLayout->addElement( 52, 0, subRect53 );
    subLayout->addElement( 53, 0, subRect54 );

    subLayout->addElement( 54, 0, subRect55 );
    subLayout->addElement( 55, 0, subRect56 );
    subLayout->addElement( 56, 0, subRect57 );
    subLayout->addElement( 57, 0, subRect58 );
    subLayout->addElement( 58, 0, subRect59 );
    subLayout->addElement( 59, 0, subRect60 );

    subLayout->addElement( 60, 0, subRect61 );
    subLayout->addElement( 61, 0, subRect62 );
    subLayout->addElement( 62, 0, subRect63 );
    subLayout->addElement( 63, 0, subRect64 );
    subLayout->addElement( 64, 0, subRect65 );
    subLayout->addElement( 65, 0, subRect66 );

    subLayout->addElement( 66, 0, subRect67 );
    subLayout->addElement( 67, 0, subRect68 );
    subLayout->addElement( 68, 0, subRect69 );
    subLayout->addElement( 69, 0, subRect70 );
    subLayout->addElement( 70, 0, subRect71 );
    subLayout->addElement( 71, 0, subRect72 );

    subLayout->addElement( 72, 0, subRect73 );
    subLayout->addElement( 73, 0, subRect74 );
    subLayout->addElement( 74, 0, subRect75 );
    subLayout->addElement( 75, 0, subRect76 );
    subLayout->addElement( 76, 0, subRect77);
    subLayout->addElement( 77, 0, subRect78 );

    subLayout->addElement( 78, 0, subRect79 );
    subLayout->addElement( 79, 0, subRect80 );
    subLayout->addElement( 80, 0, subRect81 );
    subLayout->addElement( 81, 0, subRect82 );
    subLayout->addElement( 82, 0, subRect83 );
    subLayout->addElement( 83, 0, subRect84 );

    subLayout->addElement( 84, 0, subRect85 );
    subLayout->addElement( 85, 0, subRect86 );
    subLayout->addElement( 86, 0, subRect87 );
    subLayout->addElement( 87, 0, subRect88 );
    subLayout->addElement( 88, 0, subRect89 );
    subLayout->addElement( 89, 0, subRect90 );

    subLayout->addElement( 90, 0, subRect91 );
    subLayout->addElement( 91, 0, subRect92 );
    subLayout->addElement( 92, 0, subRect93 );
    subLayout->addElement( 93, 0, subRect94 );
    subLayout->addElement( 94, 0, subRect95 );
    subLayout->addElement( 95, 0, subRect96 );


    // setup axes in sub layout axis rects:
    subRect1->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    //subRect1->axis(QCPAxis::atBottom)->ticker()->setTickCount(2);
    subRect1->axis(QCPAxis::atBottom)->grid()->setVisible(true);

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

    subRect22 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect22 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect23 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect23 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect24 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect24 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect25 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect25 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect26 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect26 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect27 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect27 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect28 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect28 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect29 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect29 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect30 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect30 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect31 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect31 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect32 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect32 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect33 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect33 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect34 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect34 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect35 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect35 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect36 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect36 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect37 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect37 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect38 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect38 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect39 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect39 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect40 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect40 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect41 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect41 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect42 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect42 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect43 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect43 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect44 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect44 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect45 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect45 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect46 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect46 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect47 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect47 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect48 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect48 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect49 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect49 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect50 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect50 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect51 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect51 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect52 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect52 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect53 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect53 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect54 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect54 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect55 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect55 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect56 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect56 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect57 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect57 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect58 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect58 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect59 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect59 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect60 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect60 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect61 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect61 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect62 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect62 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect63 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect63 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect64 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect64 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect65 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect65 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect66 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect66 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect67 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect67 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect68 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect68 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect69 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect69 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect70 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect70 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect71 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect71 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect72 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect72 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect73 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect73 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect74 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect74 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect75 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect75 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect76 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect76 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect77 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect77 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect78 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect78 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect79 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect79 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect80 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect80 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect81 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect81 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect82 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect82 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect83 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect83 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect84 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect84 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect85 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect85 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect86 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect86 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect87 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect87 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect88 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect88 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect89 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect89 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect90 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect90 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect91 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect91 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect92 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect92 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect93 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect93 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect94 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect94 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect95 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect95 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);

    subRect96 ->addAxes(QCPAxis::atBottom |QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight);
    subRect96 ->axis(QCPAxis::atBottom)->grid()->setVisible(true);



    // synchronize the left and right margins of the top and bottom axis rects:
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot_LB9);

    subRect1->setMarginGroup(QCP::msBottom, marginGroup);
    subRect2->setMarginGroup(QCP::msBottom, marginGroup);
    subRect3->setMarginGroup(QCP::msBottom, marginGroup);
    subRect4->setMarginGroup(QCP::msBottom, marginGroup);
    subRect5->setMarginGroup(QCP::msBottom, marginGroup);
    subRect6->setMarginGroup(QCP::msBottom, marginGroup);
    subRect7->setMarginGroup(QCP::msBottom, marginGroup);
    subRect8->setMarginGroup(QCP::msBottom, marginGroup);
    subRect9->setMarginGroup(QCP::msBottom, marginGroup);
    subRect10->setMarginGroup(QCP::msBottom, marginGroup);
    subRect11->setMarginGroup(QCP::msBottom, marginGroup);
    subRect12->setMarginGroup(QCP::msBottom, marginGroup);

    subRect13  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect14  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect15  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect16  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect17  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect18  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect19  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect20  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect21  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect22  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect23  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect24  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect25  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect26  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect27  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect28  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect29  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect30  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect31  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect32  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect33  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect34  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect35  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect36  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect37  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect38  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect39  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect40  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect41  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect42  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect43  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect44  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect45  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect46  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect47  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect48  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect49  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect50  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect51  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect52  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect53  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect54  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect55  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect56  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect57  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect58  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect59  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect60  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect61  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect62  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect63  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect64  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect65  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect66  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect67  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect68  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect69  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect70  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect71  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect72  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect73  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect74  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect75  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect76  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect77  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect78  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect79  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect80  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect81  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect82  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect83  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect84  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect85  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect86  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect87  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect88  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect89  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect90  ->setMarginGroup(QCP::msBottom, marginGroup);

    subRect91  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect92  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect93  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect94  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect95  ->setMarginGroup(QCP::msBottom, marginGroup);
    subRect96  ->setMarginGroup(QCP::msBottom, marginGroup);




    //wideAxisRect->setMarginGroup(QCP::msTop | QCP::msBottom | QCP::msRight | QCP::msLeft, marginGroup);


    // move newly created axes on "axes" layer and grids on "grid" layer:

    foreach (QCPAxisRect *rect, ui->plot_LB9->axisRects())
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
    ui->plot_LB9->setBackground(QBrush(gradient));
    //==================================================================
    //
    //==================================================================




    setupLocalPlot (subRect1  , y0LB9_StripData, 1 , "RPC Channel  1");
    setupLocalPlot (subRect2  , y0LB9_StripData, 2 , "RPC Channel  2");
    setupLocalPlot (subRect3  , y0LB9_StripData, 3 , "RPC Channel  3");
    setupLocalPlot (subRect4  , y0LB9_StripData, 4 , "RPC Channel  4");
    setupLocalPlot (subRect5  , y0LB9_StripData, 5 , "RPC Channel  5");
    setupLocalPlot (subRect6  , y0LB9_StripData,  6 , "RPC Channel  6");

    setupLocalPlot (subRect7  , y0LB9_StripData,  7 , "RPC Channel  7");
    setupLocalPlot (subRect8  , y0LB9_StripData,  8 , "RPC Channel  8");
    setupLocalPlot (subRect9  , y0LB9_StripData,  9 , "RPC Channel  9");
    setupLocalPlot (subRect10 , y0LB9_StripData,  10 , "RPC Channel  10");
    setupLocalPlot (subRect11 , y0LB9_StripData,  11 , "RPC Channel  11");
    setupLocalPlot (subRect12 , y0LB9_StripData,  12 , "RPC Channel  12");

    setupLocalPlot (subRect13  , y0LB9_StripData,  13  , "RPC Channel 13");
    setupLocalPlot (subRect14  , y0LB9_StripData,  14  , "RPC Channel 14");
    setupLocalPlot (subRect15  , y0LB9_StripData,  15  , "RPC Channel 15");
    setupLocalPlot (subRect16  , y0LB9_StripData,  16  , "RPC Channel 16");
    setupLocalPlot (subRect17  , y0LB9_StripData, 17  , "RPC Channel 17");
    setupLocalPlot (subRect18  , y0LB9_StripData, 18  , "RPC Channel 18");

    setupLocalPlot (subRect19  , y0LB9_StripData, 19  , "RPC Channel 19");
    setupLocalPlot (subRect20  , y0LB9_StripData,  20 , "RPC Channel  20");
    setupLocalPlot (subRect21  , y0LB9_StripData, 21  , "RPC Channel  21");
    setupLocalPlot (subRect22  , y0LB9_StripData, 22  , "RPC Channel  22");
    setupLocalPlot (subRect23  , y0LB9_StripData, 23  , "RPC Channel  23");
    setupLocalPlot (subRect24  , y0LB9_StripData, 24  , "RPC Channel  24");

    setupLocalPlot (subRect25  , y0LB9_StripData, 25  , "RPC Channel  25");
    setupLocalPlot (subRect26  , y0LB9_StripData, 26  , "RPC Channel  26");
    setupLocalPlot (subRect27  , y0LB9_StripData, 27  , "RPC Channel  27");
    setupLocalPlot (subRect28  , y0LB9_StripData, 28  , "RPC Channel  28");
    setupLocalPlot (subRect29  , y0LB9_StripData, 29  , "RPC Channel  29");
    setupLocalPlot (subRect30  , y0LB9_StripData, 30  , "RPC Channel  30");

    setupLocalPlot (subRect31  , y0LB9_StripData, 31  , "RPC Channel  31");
    setupLocalPlot (subRect32  , y0LB9_StripData, 32  , "RPC Channel  32");
    setupLocalPlot (subRect33  , y0LB9_StripData, 33  , "RPC Channel  33");
    setupLocalPlot (subRect34  , y0LB9_StripData, 34  , "RPC Channel  34");
    setupLocalPlot (subRect35  , y0LB9_StripData, 35  , "RPC Channel  35");
    setupLocalPlot (subRect36  , y0LB9_StripData, 36  , "RPC Channel  36");

    setupLocalPlot (subRect37  , y0LB9_StripData, 37  , "RPC Channel  37");
    setupLocalPlot (subRect38  , y0LB9_StripData, 38  , "RPC Channel  38");
    setupLocalPlot (subRect39  , y0LB9_StripData, 39  , "RPC Channel  39");
    setupLocalPlot (subRect40  , y0LB9_StripData, 40  , "RPC Channel  40");
    setupLocalPlot (subRect41  , y0LB9_StripData, 41  , "RPC Channel  41");
    setupLocalPlot (subRect42  , y0LB9_StripData, 42  , "RPC Channel  42");

    setupLocalPlot (subRect43  , y0LB9_StripData, 43  , "RPC Channel  43");
    setupLocalPlot (subRect44  , y0LB9_StripData, 44  , "RPC Channel  44");
    setupLocalPlot (subRect45  , y0LB9_StripData, 45  , "RPC Channel  45");
    setupLocalPlot (subRect46  , y0LB9_StripData, 46  , "RPC Channel  46");
    setupLocalPlot (subRect47  , y0LB9_StripData, 47  , "RPC Channel  47");
    setupLocalPlot (subRect48  , y0LB9_StripData, 48  , "RPC Channel  48");

    setupLocalPlot (subRect49  , y0LB9_StripData, 49  , "RPC Channel  49");
    setupLocalPlot (subRect50  , y0LB9_StripData, 50  , "RPC Channel  50");
    setupLocalPlot (subRect51  , y0LB9_StripData, 51  , "RPC Channel  51");
    setupLocalPlot (subRect52  , y0LB9_StripData, 52  , "RPC Channel  52");
    setupLocalPlot (subRect53  , y0LB9_StripData, 53  , "RPC Channel  53");
    setupLocalPlot (subRect54  , y0LB9_StripData, 54  , "RPC Channel  54");

    setupLocalPlot (subRect55  , y0LB9_StripData, 55  , "RPC Channel  55");
    setupLocalPlot (subRect56  , y0LB9_StripData, 56  , "RPC Channel  56");
    setupLocalPlot (subRect57  , y0LB9_StripData, 57  , "RPC Channel  57");
    setupLocalPlot (subRect58  , y0LB9_StripData, 58  , "RPC Channel  58");
    setupLocalPlot (subRect59  , y0LB9_StripData, 59  , "RPC Channel  59");
    setupLocalPlot (subRect60  , y0LB9_StripData, 60  , "RPC Channel  60");

    setupLocalPlot (subRect61  , y0LB9_StripData, 61  , "RPC Channel  61");
    setupLocalPlot (subRect62  , y0LB9_StripData, 62  , "RPC Channel  62");
    setupLocalPlot (subRect63  , y0LB9_StripData, 62  , "RPC Channel  63");
    setupLocalPlot (subRect64  , y0LB9_StripData, 64  , "RPC Channel  64");
    setupLocalPlot (subRect65  , y0LB9_StripData, 65  , "RPC Channel  65");
    setupLocalPlot (subRect66  , y0LB9_StripData, 66  , "RPC Channel  66");

    setupLocalPlot (subRect67  , y0LB9_StripData, 67  , "RPC Channel  67");
    setupLocalPlot (subRect68  , y0LB9_StripData, 68  , "RPC Channel  68");
    setupLocalPlot (subRect69  , y0LB9_StripData, 69  , "RPC Channel  69");
    setupLocalPlot (subRect70  , y0LB9_StripData, 70  , "RPC Channel  70");
    setupLocalPlot (subRect71  , y0LB9_StripData, 71  , "RPC Channel  71");
    setupLocalPlot (subRect72  , y0LB9_StripData, 72  , "RPC Channel  72");

    setupLocalPlot (subRect73  , y0LB9_StripData, 73  , "RPC Channel  73");
    setupLocalPlot (subRect74  , y0LB9_StripData, 74  , "RPC Channel  74");
    setupLocalPlot (subRect75  , y0LB9_StripData, 75  , "RPC Channel  75");
    setupLocalPlot (subRect76  , y0LB9_StripData, 76  , "RPC Channel  76");
    setupLocalPlot (subRect77  , y0LB9_StripData, 77  , "RPC Channel  77");
    setupLocalPlot (subRect78  , y0LB9_StripData, 78  , "RPC Channel  78");

    setupLocalPlot (subRect79  , y0LB9_StripData, 79  , "RPC Channel  79");
    setupLocalPlot (subRect80  , y0LB9_StripData, 80  , "RPC Channel  80");
    setupLocalPlot (subRect81  , y0LB9_StripData, 81  , "RPC Channel  81");
    setupLocalPlot (subRect82  , y0LB9_StripData, 82  , "RPC Channel  82");
    setupLocalPlot (subRect83  , y0LB9_StripData, 83  , "RPC Channel  83");
    setupLocalPlot (subRect84  , y0LB9_StripData, 84  , "RPC Channel  84");

    setupLocalPlot (subRect85  , y0LB9_StripData, 85  , "RPC Channel  85");
    setupLocalPlot (subRect86  , y0LB9_StripData, 86  , "RPC Channel  86");
    setupLocalPlot (subRect87  , y0LB9_StripData, 87  , "RPC Channel  87");
    setupLocalPlot (subRect88  , y0LB9_StripData, 88  , "RPC Channel  88");
    setupLocalPlot (subRect89  , y0LB9_StripData, 89  , "RPC Channel  89");
    setupLocalPlot (subRect90  , y0LB9_StripData, 90  , "RPC Channel  90");

    setupLocalPlot (subRect91  , y0LB9_StripData, 91  , "RPC Channel  91");
    setupLocalPlot (subRect92  , y0LB9_StripData, 92  , "RPC Channel  92");
    setupLocalPlot (subRect93  , y0LB9_StripData, 93  , "RPC Channel  93");
    setupLocalPlot (subRect94  , y0LB9_StripData, 94  , "RPC Channel  94");
    setupLocalPlot (subRect95  , y0LB9_StripData, 95  , "RPC Channel  95");
    setupLocalPlot (subRect96  , y0LB9_StripData, 96  , "RPC Channel  96");


    connect(ui->plot_LB9, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->plot_LB9, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel(QWheelEvent*)));
    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->plot_LB9->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_LB9->xAxis, SLOT(setRange(QCPRange)));
    connect(ui->plot_LB9->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_LB9->yAxis, SLOT(setRange(QCPRange)));

    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);

    ui->plot_LB9->replot();

}
//=================================================
