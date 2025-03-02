/********************************************************************************
** Form generated from reading UI file 'timingprofile.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMINGPROFILE_H
#define UI_TIMINGPROFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_timingprofile
{
public:
    QGridLayout *gridLayout_21;
    QTabWidget *tabWidget;
    QWidget *tab_CB;
    QGridLayout *gridLayout_12;
    QCustomPlot *plot_CB;
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QScrollBar *horizontalScrollBar;
    QScrollBar *verticalScrollBar;
    QWidget *tab_LB1;
    QGridLayout *gridLayout_13;
    QCustomPlot *plot_LB1;
    QWidget *tab_LB2;
    QGridLayout *gridLayout_14;
    QCustomPlot *plot_LB2;
    QWidget *tab_LB3;
    QGridLayout *gridLayout_2;
    QCustomPlot *plot_LB3;
    QWidget *tab_LB4;
    QGridLayout *gridLayout_15;
    QCustomPlot *plot_LB4;
    QWidget *tab_LB5;
    QGridLayout *gridLayout_16;
    QCustomPlot *plot_LB5;
    QWidget *tab_LB6;
    QGridLayout *gridLayout_17;
    QCustomPlot *plot_LB6;
    QWidget *tab_LB7;
    QGridLayout *gridLayout_18;
    QCustomPlot *plot_LB7;
    QWidget *tab_LB8;
    QGridLayout *gridLayout_19;
    QCustomPlot *plot_LB8;
    QWidget *tab_LB9;
    QGridLayout *gridLayout_20;
    QCustomPlot *plot_LB9;

    void setupUi(QWidget *timingprofile)
    {
        if (timingprofile->objectName().isEmpty())
            timingprofile->setObjectName(QString::fromUtf8("timingprofile"));
        timingprofile->resize(1029, 673);
        gridLayout_21 = new QGridLayout(timingprofile);
        gridLayout_21->setObjectName(QString::fromUtf8("gridLayout_21"));
        tabWidget = new QTabWidget(timingprofile);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tab_CB = new QWidget();
        tab_CB->setObjectName(QString::fromUtf8("tab_CB"));
        gridLayout_12 = new QGridLayout(tab_CB);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        plot_CB = new QCustomPlot(tab_CB);
        plot_CB->setObjectName(QString::fromUtf8("plot_CB"));
        sizePolicy.setHeightForWidth(plot_CB->sizePolicy().hasHeightForWidth());
        plot_CB->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(plot_CB);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonBox = new QDialogButtonBox(plot_CB);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        sizePolicy.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::NoButton);

        gridLayout->addWidget(buttonBox, 0, 0, 1, 1);

        horizontalScrollBar = new QScrollBar(plot_CB);
        horizontalScrollBar->setObjectName(QString::fromUtf8("horizontalScrollBar"));
        horizontalScrollBar->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalScrollBar, 1, 0, 1, 1);

        verticalScrollBar = new QScrollBar(plot_CB);
        verticalScrollBar->setObjectName(QString::fromUtf8("verticalScrollBar"));
        verticalScrollBar->setOrientation(Qt::Vertical);

        gridLayout->addWidget(verticalScrollBar, 0, 1, 1, 1);


        gridLayout_12->addWidget(plot_CB, 0, 0, 1, 1);

        tabWidget->addTab(tab_CB, QString());
        tab_LB1 = new QWidget();
        tab_LB1->setObjectName(QString::fromUtf8("tab_LB1"));
        gridLayout_13 = new QGridLayout(tab_LB1);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        plot_LB1 = new QCustomPlot(tab_LB1);
        plot_LB1->setObjectName(QString::fromUtf8("plot_LB1"));

        gridLayout_13->addWidget(plot_LB1, 0, 0, 1, 1);

        tabWidget->addTab(tab_LB1, QString());
        tab_LB2 = new QWidget();
        tab_LB2->setObjectName(QString::fromUtf8("tab_LB2"));
        gridLayout_14 = new QGridLayout(tab_LB2);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        plot_LB2 = new QCustomPlot(tab_LB2);
        plot_LB2->setObjectName(QString::fromUtf8("plot_LB2"));

        gridLayout_14->addWidget(plot_LB2, 0, 0, 1, 1);

        tabWidget->addTab(tab_LB2, QString());
        tab_LB3 = new QWidget();
        tab_LB3->setObjectName(QString::fromUtf8("tab_LB3"));
        gridLayout_2 = new QGridLayout(tab_LB3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        plot_LB3 = new QCustomPlot(tab_LB3);
        plot_LB3->setObjectName(QString::fromUtf8("plot_LB3"));

        gridLayout_2->addWidget(plot_LB3, 0, 0, 1, 1);

        tabWidget->addTab(tab_LB3, QString());
        tab_LB4 = new QWidget();
        tab_LB4->setObjectName(QString::fromUtf8("tab_LB4"));
        gridLayout_15 = new QGridLayout(tab_LB4);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        plot_LB4 = new QCustomPlot(tab_LB4);
        plot_LB4->setObjectName(QString::fromUtf8("plot_LB4"));

        gridLayout_15->addWidget(plot_LB4, 0, 0, 1, 1);

        tabWidget->addTab(tab_LB4, QString());
        tab_LB5 = new QWidget();
        tab_LB5->setObjectName(QString::fromUtf8("tab_LB5"));
        gridLayout_16 = new QGridLayout(tab_LB5);
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        plot_LB5 = new QCustomPlot(tab_LB5);
        plot_LB5->setObjectName(QString::fromUtf8("plot_LB5"));

        gridLayout_16->addWidget(plot_LB5, 0, 0, 1, 1);

        tabWidget->addTab(tab_LB5, QString());
        tab_LB6 = new QWidget();
        tab_LB6->setObjectName(QString::fromUtf8("tab_LB6"));
        gridLayout_17 = new QGridLayout(tab_LB6);
        gridLayout_17->setObjectName(QString::fromUtf8("gridLayout_17"));
        plot_LB6 = new QCustomPlot(tab_LB6);
        plot_LB6->setObjectName(QString::fromUtf8("plot_LB6"));

        gridLayout_17->addWidget(plot_LB6, 0, 0, 1, 1);

        tabWidget->addTab(tab_LB6, QString());
        tab_LB7 = new QWidget();
        tab_LB7->setObjectName(QString::fromUtf8("tab_LB7"));
        gridLayout_18 = new QGridLayout(tab_LB7);
        gridLayout_18->setObjectName(QString::fromUtf8("gridLayout_18"));
        plot_LB7 = new QCustomPlot(tab_LB7);
        plot_LB7->setObjectName(QString::fromUtf8("plot_LB7"));

        gridLayout_18->addWidget(plot_LB7, 0, 0, 1, 1);

        tabWidget->addTab(tab_LB7, QString());
        tab_LB8 = new QWidget();
        tab_LB8->setObjectName(QString::fromUtf8("tab_LB8"));
        gridLayout_19 = new QGridLayout(tab_LB8);
        gridLayout_19->setObjectName(QString::fromUtf8("gridLayout_19"));
        plot_LB8 = new QCustomPlot(tab_LB8);
        plot_LB8->setObjectName(QString::fromUtf8("plot_LB8"));

        gridLayout_19->addWidget(plot_LB8, 0, 0, 1, 1);

        tabWidget->addTab(tab_LB8, QString());
        tab_LB9 = new QWidget();
        tab_LB9->setObjectName(QString::fromUtf8("tab_LB9"));
        gridLayout_20 = new QGridLayout(tab_LB9);
        gridLayout_20->setObjectName(QString::fromUtf8("gridLayout_20"));
        plot_LB9 = new QCustomPlot(tab_LB9);
        plot_LB9->setObjectName(QString::fromUtf8("plot_LB9"));

        gridLayout_20->addWidget(plot_LB9, 0, 0, 1, 1);

        tabWidget->addTab(tab_LB9, QString());

        gridLayout_21->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(timingprofile);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(timingprofile);
    } // setupUi

    void retranslateUi(QWidget *timingprofile)
    {
        timingprofile->setWindowTitle(QApplication::translate("timingprofile", "Form", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_CB), QApplication::translate("timingprofile", "CB", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_LB1), QApplication::translate("timingprofile", "LB1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_LB2), QApplication::translate("timingprofile", "LB2", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_LB3), QApplication::translate("timingprofile", "LB3", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_LB4), QApplication::translate("timingprofile", "LB4", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_LB5), QApplication::translate("timingprofile", "LB5", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_LB6), QApplication::translate("timingprofile", "LB6", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_LB7), QApplication::translate("timingprofile", "LB7", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_LB8), QApplication::translate("timingprofile", "LB8", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_LB9), QApplication::translate("timingprofile", "LB9", nullptr));
    } // retranslateUi

};

namespace Ui {
    class timingprofile: public Ui_timingprofile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMINGPROFILE_H
