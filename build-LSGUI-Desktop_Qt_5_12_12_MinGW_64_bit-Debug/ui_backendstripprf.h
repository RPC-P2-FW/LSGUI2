/********************************************************************************
** Form generated from reading UI file 'backendstripprf.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BACKENDSTRIPPRF_H
#define UI_BACKENDSTRIPPRF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_BackendStripPrf
{
public:
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QCustomPlot *BeStripPrfPlot;
    QGridLayout *gridLayout_3;
    QCheckBox *checkBox;

    void setupUi(QWidget *BackendStripPrf)
    {
        if (BackendStripPrf->objectName().isEmpty())
            BackendStripPrf->setObjectName(QString::fromUtf8("BackendStripPrf"));
        BackendStripPrf->resize(1010, 736);
        gridLayout = new QGridLayout(BackendStripPrf);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        scrollArea = new QScrollArea(BackendStripPrf);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 990, 716));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        BeStripPrfPlot = new QCustomPlot(scrollAreaWidgetContents);
        BeStripPrfPlot->setObjectName(QString::fromUtf8("BeStripPrfPlot"));
        gridLayout_3 = new QGridLayout(BeStripPrfPlot);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        checkBox = new QCheckBox(BeStripPrfPlot);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout_3->addWidget(checkBox, 0, 0, 1, 1);


        gridLayout_2->addWidget(BeStripPrfPlot, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);


        retranslateUi(BackendStripPrf);

        QMetaObject::connectSlotsByName(BackendStripPrf);
    } // setupUi

    void retranslateUi(QWidget *BackendStripPrf)
    {
        BackendStripPrf->setWindowTitle(QApplication::translate("BackendStripPrf", "Form", nullptr));
        checkBox->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BackendStripPrf: public Ui_BackendStripPrf {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BACKENDSTRIPPRF_H
