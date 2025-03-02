/********************************************************************************
** Form generated from reading UI file 'backendhitplot.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BACKENDHITPLOT_H
#define UI_BACKENDHITPLOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_BackendHitPlot
{
public:
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QCustomPlot *BeHPPlot;
    QGridLayout *gridLayout_3;

    void setupUi(QWidget *BackendHitPlot)
    {
        if (BackendHitPlot->objectName().isEmpty())
            BackendHitPlot->setObjectName(QString::fromUtf8("BackendHitPlot"));
        BackendHitPlot->resize(718, 441);
        gridLayout = new QGridLayout(BackendHitPlot);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        scrollArea = new QScrollArea(BackendHitPlot);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 694, 417));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        BeHPPlot = new QCustomPlot(scrollAreaWidgetContents);
        BeHPPlot->setObjectName(QString::fromUtf8("BeHPPlot"));
        BeHPPlot->setAutoFillBackground(false);
        gridLayout_3 = new QGridLayout(BeHPPlot);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));

        gridLayout_2->addWidget(BeHPPlot, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);


        retranslateUi(BackendHitPlot);

        QMetaObject::connectSlotsByName(BackendHitPlot);
    } // setupUi

    void retranslateUi(QWidget *BackendHitPlot)
    {
        BackendHitPlot->setWindowTitle(QApplication::translate("BackendHitPlot", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BackendHitPlot: public Ui_BackendHitPlot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BACKENDHITPLOT_H
