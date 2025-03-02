#ifndef TIMINGPROFILE_H
#define TIMINGPROFILE_H

#include <QWidget>
#include <QDialog>
#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QTimer>
#include "qcustomplot.h"

namespace Ui {
class timingprofile;
}

class timingprofile : public QWidget
{
    Q_OBJECT

public:

    unsigned int const bunch_num = 129 ;

    unsigned int y0CB_timingHist [200];
    unsigned int y0CB_RawData   [5000];
    unsigned int x0CB_BxNum     [5000];


    unsigned int y0LB1_timingHist [200];
    unsigned int y0LB1_RawData   [5000];
    unsigned int x0LB1_BxNum     [5000];


    unsigned int y0LB2_timingHist [200];
    unsigned int y0LB2_RawData   [5000];
    unsigned int x0LB2_BxNum     [5000];


    unsigned int y0LB3_timingHist [200];
    unsigned int y0LB3_RawData   [5000];
    unsigned int x0LB3_BxNum     [5000];


    unsigned int y0LB4_timingHist [200];
    unsigned int y0LB4_RawData   [5000];
    unsigned int x0LB4_BxNum     [5000];

    unsigned int y0LB5_timingHist [200];
    unsigned int y0LB5_RawData   [5000];
    unsigned int x0LB5_BxNum     [5000];

    unsigned int y0LB6_timingHist [200];
    unsigned int y0LB6_RawData   [5000];
    unsigned int x0LB6_BxNum     [5000];

    unsigned int y0LB7_timingHist [200];
    unsigned int y0LB7_RawData   [5000];
    unsigned int x0LB7_BxNum     [5000];

    unsigned int y0LB8_timingHist [200];
    unsigned int y0LB8_RawData   [5000];
    unsigned int x0LB8_BxNum     [5000];

    unsigned int y0LB9_timingHist [200];
    unsigned int y0LB9_RawData   [5000];
    unsigned int x0LB9_BxNum     [5000];


    explicit timingprofile(QWidget *parent = nullptr);
    ~timingprofile();


    void setupPlot_CB(void);

    void setupPlot_LB(unsigned int);
    void setupPlot_LB1(void);
    void setupPlot_LB2(void);
    void setupPlot_LB3(void);
    void setupPlot_LB4(void);
    void setupPlot_LB5(void);
    void setupPlot_LB6(void);
    void setupPlot_LB7(void);
    void setupPlot_LB8(void);
    void setupPlot_LB9(void);


    bool plotCB = false ;
    bool plotLB1 = false ;
    bool plotLB2 = false ;
    bool plotLB3 = false ;
    bool plotLB4 = false ;
    bool plotLB5 = false ;
    bool plotLB6 = false ;
    bool plotLB7 = false ;
    bool plotLB8 = false ;
    bool plotLB9 = false ;

    unsigned int BxCntVal = 0 ;

private slots:
  void horzScrollBarChanged(int value);
  void vertScrollBarChanged(int value);
  void xAxisChanged(QCPRange range);
  void yAxisChanged(QCPRange range);


private:
    Ui::timingprofile *ui;
};

#endif // TIMINGPROFILE_H
