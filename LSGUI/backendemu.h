#ifndef BACKENDEMU_H
#define BACKENDEMU_H

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
class BackendEmu;
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
}

class BackendEmu : public QWidget
{
    Q_OBJECT

public:
    explicit BackendEmu(QWidget *parent = nullptr);
    ~BackendEmu();

    void setupPlot_BeE(void);

    unsigned int counter = 0 ;


private slots:
  void horzScrollBarChanged(int value);
  void vertScrollBarChanged(int value);
  void xAxisChanged(QCPRange range);
  void yAxisChanged(QCPRange range);
  void mousePress();
  void mouseWheel(QWheelEvent*);

private:
    Ui::BackendEmu *ui;
    QScrollArea *scrollArea;
    double scaleFactor = 1;

};

#endif // BACKENDEMU_H
