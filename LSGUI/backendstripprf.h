#ifndef BACKENDSTRIPPRF_H
#define BACKENDSTRIPPRF_H

#include <QWidget>
#include "qcustomplot.h"

#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>


#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QTimer>
#include <QMouseEvent>
#include <QWheelEvent>


namespace Ui {
class BackendStripPrf;
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
}

class BackendStripPrf : public QWidget
{
    Q_OBJECT

public:
    explicit BackendStripPrf(QWidget *parent = nullptr);
    ~BackendStripPrf();

    unsigned int const bunch_num = 129 ;

    //unsigned int y0BE_timingHist [200];
    //unsigned int y0BE_RawData   [5000];
    //unsigned int x0BE_BxNum     [5000];

    bool plotBe = false ;
    unsigned int BxCntVal = 0 ;

    void BeStripPrfSetupPlot(void);
    void BeStripPrfAddDetPlot (QCPAxisRect *subRect, unsigned int StripNum , QString stripNum);
    unsigned int counter = 0 ;

    void BeStripPrfPlotter (unsigned int y0_StripData[16][100], unsigned int StripNum );





private:
    Ui::BackendStripPrf *ui;
    QScrollArea *scrollArea;

    QCPAxisRect *subRect ;

    QCPAxisRect *subRect1;
    QCPAxisRect *subRect2;
    QCPAxisRect *subRect3;
    QCPAxisRect *subRect4;
    QCPAxisRect *subRect5;
    QCPAxisRect *subRect6;
    QCPAxisRect *subRect7;
    QCPAxisRect *subRect8;
    QCPAxisRect *subRect9;
    QCPAxisRect *subRect10;
    QCPAxisRect *subRect11;
    QCPAxisRect *subRect12;

    QCPAxisRect *subRect13;
    QCPAxisRect *subRect14;
    QCPAxisRect *subRect15;
    QCPAxisRect *subRect16;
    QCPAxisRect *subRect17;
    QCPAxisRect *subRect18;
    QCPAxisRect *subRect19;
    QCPAxisRect *subRect20;
    QCPAxisRect *subRect21;
    QCPAxisRect *subRect22;
    QCPAxisRect *subRect23;
    QCPAxisRect *subRect24;

    QCPAxisRect *subRect25 ;
    QCPAxisRect *subRect26 ;
    QCPAxisRect *subRect27 ;
    QCPAxisRect *subRect28 ;
    QCPAxisRect *subRect29 ;
    QCPAxisRect *subRect30 ;
    QCPAxisRect *subRect31 ;
    QCPAxisRect *subRect32 ;
    QCPAxisRect *subRect33 ;
    QCPAxisRect *subRect34  ;
    QCPAxisRect *subRect35  ;
    QCPAxisRect *subRect36  ;

    QCPAxisRect *subRect37 ;
    QCPAxisRect *subRect38 ;
    QCPAxisRect *subRect39 ;
    QCPAxisRect *subRect40 ;
    QCPAxisRect *subRect41 ;
    QCPAxisRect *subRect42 ;
    QCPAxisRect *subRect43 ;
    QCPAxisRect *subRect44 ;
    QCPAxisRect *subRect45 ;
    QCPAxisRect *subRect46  ;
    QCPAxisRect *subRect47  ;
    QCPAxisRect *subRect48  ;

    QCPAxisRect *subRect49 ;
    QCPAxisRect *subRect50 ;
    QCPAxisRect *subRect51 ;
    QCPAxisRect *subRect52 ;
    QCPAxisRect *subRect53 ;
    QCPAxisRect *subRect54 ;
    QCPAxisRect *subRect55 ;
    QCPAxisRect *subRect56 ;
    QCPAxisRect *subRect57 ;
    QCPAxisRect *subRect58  ;
    QCPAxisRect *subRect59  ;
    QCPAxisRect *subRect60  ;

    QCPAxisRect *subRect61 ;
    QCPAxisRect *subRect62 ;
    QCPAxisRect *subRect63 ;
    QCPAxisRect *subRect64 ;
    QCPAxisRect *subRect65 ;
    QCPAxisRect *subRect66 ;
    QCPAxisRect *subRect67 ;
    QCPAxisRect *subRect68 ;
    QCPAxisRect *subRect69 ;
    QCPAxisRect *subRect70  ;
    QCPAxisRect *subRect71  ;
    QCPAxisRect *subRect72  ;

    QCPAxisRect *subRect73 ;
    QCPAxisRect *subRect74 ;
    QCPAxisRect *subRect75 ;
    QCPAxisRect *subRect76 ;
    QCPAxisRect *subRect77 ;
    QCPAxisRect *subRect78 ;
    QCPAxisRect *subRect79 ;
    QCPAxisRect *subRect80 ;
    QCPAxisRect *subRect81 ;
    QCPAxisRect *subRect82  ;
    QCPAxisRect *subRect83  ;
    QCPAxisRect *subRect84  ;


    QCPAxisRect *subRect85 ;
    QCPAxisRect *subRect86 ;
    QCPAxisRect *subRect87 ;
    QCPAxisRect *subRect88 ;
    QCPAxisRect *subRect89 ;
    QCPAxisRect *subRect90 ;
    QCPAxisRect *subRect91 ;
    QCPAxisRect *subRect92 ;
    QCPAxisRect *subRect93 ;
    QCPAxisRect *subRect94  ;
    QCPAxisRect *subRect95  ;
    QCPAxisRect *subRect96  ;
};

#endif // BACKENDSTRIPPRF_H
