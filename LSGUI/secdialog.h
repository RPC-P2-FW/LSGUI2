#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>
#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QTimer>





namespace Ui {
class secDialog;
}

class secDialog : public QDialog
{
    Q_OBJECT

public:


    unsigned int const strip_num = 96 ;

    unsigned int y0CB_FullWinChannel [100];
    unsigned int y0CB_AdjWinChannel [100];
    unsigned int y0CB_timingHist [130];
    unsigned int y0CB_RawData [2100];

    unsigned int x0CB_stripFulW [100];
    unsigned int x0CB_stripAdjW [100];
    unsigned int x0CB_BxNum [130];
    unsigned int x0CB_SubBxNum [2100];

    unsigned int y0LB1_FullWinChannel [100];
    unsigned int y0LB1_AdjWinChannel [100];
    unsigned int x0LB1_stripFulW [100];
    unsigned int x0LB1_stripAdjW [100];

    unsigned int y0LB2_FullWinChannel [100];
    unsigned int y0LB2_AdjWinChannel [100];
    unsigned int x0LB2_stripFulW [100];
    unsigned int x0LB2_stripAdjW [100];

    unsigned int y0LB3_FullWinChannel [100];
    unsigned int y0LB3_AdjWinChannel [100];
    unsigned int x0LB3_stripFulW [100];
    unsigned int x0LB3_stripAdjW [100];

    unsigned int y0LB4_FullWinChannel [100];
    unsigned int y0LB4_AdjWinChannel [100];
    unsigned int x0LB4_stripFulW [100];
    unsigned int x0LB4_stripAdjW [100];

    unsigned int y0LB5_FullWinChannel [100];
    unsigned int y0LB5_AdjWinChannel [100];
    unsigned int x0LB5_stripFulW [100];
    unsigned int x0LB5_stripAdjW [100];

    unsigned int y0LB6_FullWinChannel [100];
    unsigned int y0LB6_AdjWinChannel [100];
    unsigned int x0LB6_stripFulW [100];
    unsigned int x0LB6_stripAdjW [100];

    unsigned int y0LB7_FullWinChannel [100];
    unsigned int y0LB7_AdjWinChannel [100];
    unsigned int x0LB7_stripFulW [100];
    unsigned int x0LB7_stripAdjW [100];

    unsigned int y0LB8_FullWinChannel [100];
    unsigned int y0LB8_AdjWinChannel [100];
    unsigned int x0LB8_stripFulW [100];
    unsigned int x0LB8_stripAdjW [100];

    unsigned int y0LB9_FullWinChannel [100];
    unsigned int y0LB9_AdjWinChannel [100];
    unsigned int x0LB9_stripFulW [100];
    unsigned int x0LB9_stripAdjW [100];

    explicit secDialog(QWidget *parent = nullptr);
    ~secDialog();

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


private:

    Ui::secDialog *ui;
};

#endif // SECDIALOG_H
