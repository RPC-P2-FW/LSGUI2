/********************************************************************************
** Form generated from reading UI file 'backendtimingprf.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BACKENDTIMINGPRF_H
#define UI_BACKENDTIMINGPRF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_BackendTimingPrf
{
public:
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QCustomPlot *BeTimPrfPlot;
    QGridLayout *gridLayout_3;

    void setupUi(QWidget *BackendTimingPrf)
    {
        if (BackendTimingPrf->objectName().isEmpty())
            BackendTimingPrf->setObjectName(QString::fromUtf8("BackendTimingPrf"));
        BackendTimingPrf->resize(718, 441);
        gridLayout = new QGridLayout(BackendTimingPrf);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        scrollArea = new QScrollArea(BackendTimingPrf);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 694, 417));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        BeTimPrfPlot = new QCustomPlot(scrollAreaWidgetContents);
        BeTimPrfPlot->setObjectName(QString::fromUtf8("BeTimPrfPlot"));
        gridLayout_3 = new QGridLayout(BeTimPrfPlot);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));

        gridLayout_2->addWidget(BeTimPrfPlot, 3, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);


        retranslateUi(BackendTimingPrf);

        QMetaObject::connectSlotsByName(BackendTimingPrf);
    } // setupUi

    void retranslateUi(QWidget *BackendTimingPrf)
    {
        BackendTimingPrf->setWindowTitle(QApplication::translate("BackendTimingPrf", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BackendTimingPrf: public Ui_BackendTimingPrf {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BACKENDTIMINGPRF_H
