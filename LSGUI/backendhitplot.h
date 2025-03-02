#ifndef BACKENDHITPLOT_H
#define BACKENDHITPLOT_H

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
class BackendHitPlot;
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
}

class BackendHitPlot : public QWidget
{
    Q_OBJECT

public:
    explicit BackendHitPlot(QWidget *parent = nullptr);
    ~BackendHitPlot();

    unsigned int const bunch_num = 129 ;

    //unsigned int y0BE_timingHist [200];
    //unsigned int y0BE_RawData   [5000];
    //unsigned int x0BE_BxNum     [5000];


    unsigned int BxCntVal = 0 ;

    void BeHistSetupPlot(void);
    void BeHistAddDetPlot (QCPAxisRect *subRect, unsigned int StripNum , QString stripNum);
    unsigned int counter = 0 ;
    void BeHistPlotter (unsigned int y0_StripData[200]);

    void BackendHitPlot_scaleTop();
    void BackendHitPlot_scaleWindow();

private slots:
/*
  void horzScrollBarChanged(int value);
  void vertScrollBarChanged(int value);
  void xAxisChanged(QCPRange range);
  void yAxisChanged(QCPRange range);
  void mousePress();
  void mouseWheel(QWheelEvent*);
*/

    void on_PB_3_clicked();

    void on_PB_4_clicked();

private:
    Ui::BackendHitPlot *ui;
    //QScrollArea *scrollArea;

    QCPAxisRect *subRect ;

    QCPAxisRect *subRect1;
    QCPAxisRect *subRect2;

    QCPBars *stripN ;

    unsigned int max_value = 0 ;
    unsigned int max_width = 0 ;
    unsigned int min_width = 0 ;

    boolean minVal = false ;


};

#endif // BACKENDHITPLOT_H
