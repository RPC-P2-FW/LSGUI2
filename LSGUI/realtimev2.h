#ifndef REALTIMEV2_H
#define REALTIMEV2_H
#include "ui_realtimev2.h"

#include <QWidget>
#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QTimer>
#include <QMouseEvent>
#include <QWheelEvent>

namespace Ui {
class realtimev2;
}

class realtimev2 : public QWidget
{
    Q_OBJECT

public:
    explicit realtimev2(QWidget *parent = nullptr);
    ~realtimev2();


    unsigned int y0CB_StripData [200][200];

    unsigned int y0LB1_StripData [200][200];
    unsigned int y0LB2_StripData [200][200];
    unsigned int y0LB3_StripData [200][200];
    unsigned int y0LB4_StripData [200][200];
    unsigned int y0LB5_StripData [200][200];
    unsigned int y0LB6_StripData [200][200];
    unsigned int y0LB7_StripData [200][200];
    unsigned int y0LB8_StripData [200][200];
    unsigned int y0LB9_StripData [200][200];


    unsigned int y0CB_FullWinChannel [200];
    unsigned int y0CB_AdjWinChannel [200];
    unsigned int y0CB_timingHist [230];
    unsigned int y0CB_RawData [2100];

    unsigned int x0CB_stripFulW [200];
    unsigned int x0CB_stripAdjW [200];
    unsigned int x0CB_BxNum [200];
    unsigned int x0CB_SubBxNum [2100];

    unsigned int y0LB1_FullWinChannel [200];
    unsigned int y0LB1_AdjWinChannel [200];
    unsigned int x0LB1_stripFulW [200];
    unsigned int x0LB1_stripAdjW [200];

    unsigned int y0LB2_FullWinChannel [200];
    unsigned int y0LB2_AdjWinChannel [200];
    unsigned int x0LB2_stripFulW [200];
    unsigned int x0LB2_stripAdjW [200];

    unsigned int y0LB3_FullWinChannel [200];
    unsigned int y0LB3_AdjWinChannel [200];
    unsigned int x0LB3_stripFulW [200];
    unsigned int x0LB3_stripAdjW [200];

    unsigned int y0LB4_FullWinChannel [200];
    unsigned int y0LB4_AdjWinChannel [200];
    unsigned int x0LB4_stripFulW [200];
    unsigned int x0LB4_stripAdjW [200];

    unsigned int y0LB5_FullWinChannel [200];
    unsigned int y0LB5_AdjWinChannel [200];
    unsigned int x0LB5_stripFulW [200];
    unsigned int x0LB5_stripAdjW [200];

    unsigned int y0LB6_FullWinChannel [200];
    unsigned int y0LB6_AdjWinChannel [200];
    unsigned int x0LB6_stripFulW [200];
    unsigned int x0LB6_stripAdjW [200];

    unsigned int y0LB7_FullWinChannel [200];
    unsigned int y0LB7_AdjWinChannel [200];
    unsigned int x0LB7_stripFulW [200];
    unsigned int x0LB7_stripAdjW [200];

    unsigned int y0LB8_FullWinChannel [200];
    unsigned int y0LB8_AdjWinChannel [200];
    unsigned int x0LB8_stripFulW [200];
    unsigned int x0LB8_stripAdjW [200];

    unsigned int y0LB9_FullWinChannel [200];
    unsigned int y0LB9_AdjWinChannel [200];
    unsigned int x0LB9_stripFulW [200];
    unsigned int x0LB9_stripAdjW [200];






    unsigned int const strip_num = 96 ;

    unsigned int y0CB_Strip [200][200];

    unsigned int y0LB1_Strip [200][200];
    unsigned int y0LB2_Strip [200][200];
    unsigned int y0LB3_Strip [200][200];
    unsigned int y0LB4_Strip [200][200];
    unsigned int y0LB5_Strip [200][200];
    unsigned int y0LB6_Strip [200][200];
    unsigned int y0LB7_Strip [200][200];
    unsigned int y0LB8_Strip [200][200];
    unsigned int y0LB9_Strip [200][200];

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
    void setupLocalPlot (QCPAxisRect *subRect  , unsigned int y0_StripData[200][200], unsigned int StripNum , QString stripNum);


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
    unsigned int counter = 0 ;

    unsigned int BxCntVal = 0 ;

private slots:
    void mousePress();
    void mouseWheel(QWheelEvent*);


private:
    Ui::realtimev2 *ui;

};

#endif // REALTIMEV2_H
