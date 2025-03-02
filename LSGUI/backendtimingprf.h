#ifndef BACKENDTIMINGPRF_H
#define BACKENDTIMINGPRF_H

#include <QWidget>
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
#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QTimer>
#include <QMouseEvent>
#include <QWheelEvent>


namespace Ui {
class BackendTimingPrf;
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
}

class BackendTimingPrf : public QWidget
{
    Q_OBJECT

public:
    explicit BackendTimingPrf(QWidget *parent = nullptr);
    ~BackendTimingPrf();



    unsigned int const bunch_num = 3564 ;

    unsigned int y0BE_timingHist [200];
    unsigned int y0BE_RawData   [5000];
    unsigned int x0BE_BxNum     [5000];

    unsigned int BxCntVal = 0 ;

    void BeTimingPrfSetupPlot(void);
    void BeTimingPrfAddDetPlot (QCPAxisRect *subRect, unsigned int StripNum , QString stripNum);
    unsigned int counter = 0 ;
    void BeTimingPrfPlotter (unsigned int y0_TimingPrfData[4000]);
    void BeTimingPrf_scaleTop();
    void BeTimingPrf_scaleWindow();


private slots:
    void on_PB1_clicked();

    void on_PB_2_clicked();

private:
    Ui::BackendTimingPrf *ui;

    QCPAxisRect *subRect ;

    QCPAxisRect *subRect1;
    QCPAxisRect *subRect2;

    QCPBars *stripN ;

    unsigned int max_value = 0 ;
    unsigned int max_width = 0 ;
    unsigned int min_width = 0 ;

    boolean minVal = false ;

};

#endif // BACKENDTIMINGPRF_H
