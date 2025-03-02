/********************************************************************************
** Form generated from reading UI file 'histogram.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTOGRAM_H
#define UI_HISTOGRAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_histogram
{
public:
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QGridLayout *gridLayout_3;
    QCustomPlot *plot_CB;
    QFormLayout *formLayout;
    QDialogButtonBox *buttonBox;
    QWidget *tab_2;
    QGridLayout *gridLayout_4;
    QCustomPlot *plot_LB1;
    QWidget *tab_3;
    QGridLayout *gridLayout_5;
    QCustomPlot *plot_LB2;
    QWidget *tab_4;
    QGridLayout *gridLayout;
    QCustomPlot *plot_LB3;
    QWidget *tab;
    QGridLayout *gridLayout_6;
    QCustomPlot *plot_LB4;
    QWidget *tab_5;
    QGridLayout *gridLayout_7;
    QCustomPlot *plot_LB5;
    QWidget *tab_6;
    QGridLayout *gridLayout_8;
    QCustomPlot *plot_LB6;
    QWidget *tab_7;
    QGridLayout *gridLayout_9;
    QCustomPlot *plot_LB7;
    QWidget *tab_8;
    QGridLayout *gridLayout_10;
    QCustomPlot *plot_LB8;
    QWidget *tab_9;
    QGridLayout *gridLayout_11;
    QCustomPlot *plot_LB9;

    void setupUi(QWidget *histogram)
    {
        if (histogram->objectName().isEmpty())
            histogram->setObjectName(QString::fromUtf8("histogram"));
        histogram->resize(1069, 567);
        gridLayout_2 = new QGridLayout(histogram);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tabWidget = new QTabWidget(histogram);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tab_1 = new QWidget();
        tab_1->setObjectName(QString::fromUtf8("tab_1"));
        gridLayout_3 = new QGridLayout(tab_1);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        plot_CB = new QCustomPlot(tab_1);
        plot_CB->setObjectName(QString::fromUtf8("plot_CB"));
        sizePolicy.setHeightForWidth(plot_CB->sizePolicy().hasHeightForWidth());
        plot_CB->setSizePolicy(sizePolicy);
        formLayout = new QFormLayout(plot_CB);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        buttonBox = new QDialogButtonBox(plot_CB);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        sizePolicy.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::NoButton);

        formLayout->setWidget(0, QFormLayout::LabelRole, buttonBox);


        gridLayout_3->addWidget(plot_CB, 0, 0, 1, 1);

        tabWidget->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_4 = new QGridLayout(tab_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        plot_LB1 = new QCustomPlot(tab_2);
        plot_LB1->setObjectName(QString::fromUtf8("plot_LB1"));

        gridLayout_4->addWidget(plot_LB1, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_5 = new QGridLayout(tab_3);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        plot_LB2 = new QCustomPlot(tab_3);
        plot_LB2->setObjectName(QString::fromUtf8("plot_LB2"));

        gridLayout_5->addWidget(plot_LB2, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        gridLayout = new QGridLayout(tab_4);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        plot_LB3 = new QCustomPlot(tab_4);
        plot_LB3->setObjectName(QString::fromUtf8("plot_LB3"));

        gridLayout->addWidget(plot_LB3, 0, 0, 1, 1);

        tabWidget->addTab(tab_4, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_6 = new QGridLayout(tab);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        plot_LB4 = new QCustomPlot(tab);
        plot_LB4->setObjectName(QString::fromUtf8("plot_LB4"));

        gridLayout_6->addWidget(plot_LB4, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        gridLayout_7 = new QGridLayout(tab_5);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        plot_LB5 = new QCustomPlot(tab_5);
        plot_LB5->setObjectName(QString::fromUtf8("plot_LB5"));

        gridLayout_7->addWidget(plot_LB5, 0, 0, 1, 1);

        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        gridLayout_8 = new QGridLayout(tab_6);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        plot_LB6 = new QCustomPlot(tab_6);
        plot_LB6->setObjectName(QString::fromUtf8("plot_LB6"));

        gridLayout_8->addWidget(plot_LB6, 0, 0, 1, 1);

        tabWidget->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QString::fromUtf8("tab_7"));
        gridLayout_9 = new QGridLayout(tab_7);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        plot_LB7 = new QCustomPlot(tab_7);
        plot_LB7->setObjectName(QString::fromUtf8("plot_LB7"));

        gridLayout_9->addWidget(plot_LB7, 0, 0, 1, 1);

        tabWidget->addTab(tab_7, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName(QString::fromUtf8("tab_8"));
        gridLayout_10 = new QGridLayout(tab_8);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        plot_LB8 = new QCustomPlot(tab_8);
        plot_LB8->setObjectName(QString::fromUtf8("plot_LB8"));

        gridLayout_10->addWidget(plot_LB8, 0, 0, 1, 1);

        tabWidget->addTab(tab_8, QString());
        tab_9 = new QWidget();
        tab_9->setObjectName(QString::fromUtf8("tab_9"));
        gridLayout_11 = new QGridLayout(tab_9);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        plot_LB9 = new QCustomPlot(tab_9);
        plot_LB9->setObjectName(QString::fromUtf8("plot_LB9"));

        gridLayout_11->addWidget(plot_LB9, 0, 0, 1, 1);

        tabWidget->addTab(tab_9, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(histogram);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(histogram);
    } // setupUi

    void retranslateUi(QWidget *histogram)
    {
        histogram->setWindowTitle(QApplication::translate("histogram", "Form", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QApplication::translate("histogram", "CB", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("histogram", "LB1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("histogram", "LB2", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("histogram", "LB3", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("histogram", "LB4", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("histogram", "LB5", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("histogram", "LB6", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QApplication::translate("histogram", "LB7", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_8), QApplication::translate("histogram", "LB8", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_9), QApplication::translate("histogram", "LB9", nullptr));
    } // retranslateUi

};

namespace Ui {
    class histogram: public Ui_histogram {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTOGRAM_H
