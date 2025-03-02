/********************************************************************************
** Form generated from reading UI file 'realtimev2.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REALTIMEV2_H
#define UI_REALTIMEV2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_realtimev2
{
public:
    QGridLayout *gridLayout_20;
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QGridLayout *gridLayout_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_15;
    QCustomPlot *plot_CB;
    QGridLayout *gridLayout_14;
    QDialogButtonBox *buttonBox;
    QWidget *tab_2;
    QGridLayout *gridLayout_13;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QGridLayout *gridLayout_12;
    QCustomPlot *plot_LB1;
    QGridLayout *gridLayout_4;
    QDialogButtonBox *buttonBox_2;
    QWidget *tab_3;
    QGridLayout *gridLayout_16;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_4;
    QGridLayout *gridLayout_5;
    QCustomPlot *plot_LB2;
    QGridLayout *gridLayout_17;
    QDialogButtonBox *buttonBox_3;
    QWidget *tab_4;
    QGridLayout *gridLayout_19;
    QScrollArea *scrollArea_4;
    QWidget *scrollAreaWidgetContents_5;
    QGridLayout *gridLayout;
    QCustomPlot *plot_LB3;
    QGridLayout *gridLayout_18;
    QDialogButtonBox *buttonBox_4;
    QWidget *tab;
    QGridLayout *gridLayout_6;
    QScrollArea *scrollArea_5;
    QWidget *scrollAreaWidgetContents_6;
    QGridLayout *gridLayout_23;
    QCustomPlot *plot_LB4;
    QGridLayout *gridLayout_2;
    QDialogButtonBox *buttonBox_5;
    QWidget *tab_5;
    QGridLayout *gridLayout_22;
    QScrollArea *scrollArea_6;
    QWidget *scrollAreaWidgetContents_7;
    QGridLayout *gridLayout_21;
    QCustomPlot *plot_LB5;
    QGridLayout *gridLayout_7;
    QDialogButtonBox *buttonBox_6;
    QWidget *tab_6;
    QGridLayout *gridLayout_25;
    QScrollArea *scrollArea_7;
    QWidget *scrollAreaWidgetContents_8;
    QGridLayout *gridLayout_24;
    QCustomPlot *plot_LB6;
    QGridLayout *gridLayout_8;
    QDialogButtonBox *buttonBox_7;
    QWidget *tab_7;
    QGridLayout *gridLayout_27;
    QScrollArea *scrollArea_8;
    QWidget *scrollAreaWidgetContents_9;
    QGridLayout *gridLayout_26;
    QCustomPlot *plot_LB7;
    QGridLayout *gridLayout_9;
    QDialogButtonBox *buttonBox_8;
    QWidget *tab_8;
    QGridLayout *gridLayout_29;
    QScrollArea *scrollArea_9;
    QWidget *scrollAreaWidgetContents_10;
    QGridLayout *gridLayout_28;
    QCustomPlot *plot_LB8;
    QGridLayout *gridLayout_10;
    QDialogButtonBox *buttonBox_9;
    QWidget *tab_9;
    QGridLayout *gridLayout_31;
    QScrollArea *scrollArea_10;
    QWidget *scrollAreaWidgetContents_11;
    QGridLayout *gridLayout_30;
    QCustomPlot *plot_LB9;
    QGridLayout *gridLayout_11;
    QDialogButtonBox *buttonBox_10;

    void setupUi(QWidget *realtimev2)
    {
        if (realtimev2->objectName().isEmpty())
            realtimev2->setObjectName(QString::fromUtf8("realtimev2"));
        realtimev2->resize(1150, 782);
        gridLayout_20 = new QGridLayout(realtimev2);
        gridLayout_20->setObjectName(QString::fromUtf8("gridLayout_20"));
        tabWidget = new QTabWidget(realtimev2);
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
        scrollArea = new QScrollArea(tab_1);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1108, 717));
        gridLayout_15 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        plot_CB = new QCustomPlot(scrollAreaWidgetContents);
        plot_CB->setObjectName(QString::fromUtf8("plot_CB"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(10);
        sizePolicy1.setVerticalStretch(10);
        sizePolicy1.setHeightForWidth(plot_CB->sizePolicy().hasHeightForWidth());
        plot_CB->setSizePolicy(sizePolicy1);
        gridLayout_14 = new QGridLayout(plot_CB);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        buttonBox = new QDialogButtonBox(plot_CB);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(3);
        sizePolicy2.setVerticalStretch(3);
        sizePolicy2.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy2);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::NoButton);

        gridLayout_14->addWidget(buttonBox, 0, 0, 1, 1);


        gridLayout_15->addWidget(plot_CB, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_3->addWidget(scrollArea, 0, 0, 1, 1);

        tabWidget->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_13 = new QGridLayout(tab_2);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        scrollArea_2 = new QScrollArea(tab_2);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 1108, 717));
        gridLayout_12 = new QGridLayout(scrollAreaWidgetContents_2);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        plot_LB1 = new QCustomPlot(scrollAreaWidgetContents_2);
        plot_LB1->setObjectName(QString::fromUtf8("plot_LB1"));
        gridLayout_4 = new QGridLayout(plot_LB1);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        buttonBox_2 = new QDialogButtonBox(plot_LB1);
        buttonBox_2->setObjectName(QString::fromUtf8("buttonBox_2"));
        sizePolicy.setHeightForWidth(buttonBox_2->sizePolicy().hasHeightForWidth());
        buttonBox_2->setSizePolicy(sizePolicy);
        buttonBox_2->setOrientation(Qt::Horizontal);
        buttonBox_2->setStandardButtons(QDialogButtonBox::NoButton);

        gridLayout_4->addWidget(buttonBox_2, 0, 0, 1, 1);


        gridLayout_12->addWidget(plot_LB1, 0, 0, 1, 1);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        gridLayout_13->addWidget(scrollArea_2, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_16 = new QGridLayout(tab_3);
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        scrollArea_3 = new QScrollArea(tab_3);
        scrollArea_3->setObjectName(QString::fromUtf8("scrollArea_3"));
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 1108, 717));
        gridLayout_5 = new QGridLayout(scrollAreaWidgetContents_4);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        plot_LB2 = new QCustomPlot(scrollAreaWidgetContents_4);
        plot_LB2->setObjectName(QString::fromUtf8("plot_LB2"));
        gridLayout_17 = new QGridLayout(plot_LB2);
        gridLayout_17->setObjectName(QString::fromUtf8("gridLayout_17"));
        buttonBox_3 = new QDialogButtonBox(plot_LB2);
        buttonBox_3->setObjectName(QString::fromUtf8("buttonBox_3"));
        buttonBox_3->setStandardButtons(QDialogButtonBox::NoButton);

        gridLayout_17->addWidget(buttonBox_3, 0, 0, 1, 1);


        gridLayout_5->addWidget(plot_LB2, 0, 0, 1, 1);

        scrollArea_3->setWidget(scrollAreaWidgetContents_4);

        gridLayout_16->addWidget(scrollArea_3, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        gridLayout_19 = new QGridLayout(tab_4);
        gridLayout_19->setObjectName(QString::fromUtf8("gridLayout_19"));
        scrollArea_4 = new QScrollArea(tab_4);
        scrollArea_4->setObjectName(QString::fromUtf8("scrollArea_4"));
        scrollArea_4->setWidgetResizable(true);
        scrollAreaWidgetContents_5 = new QWidget();
        scrollAreaWidgetContents_5->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_5"));
        scrollAreaWidgetContents_5->setGeometry(QRect(0, 0, 1108, 717));
        gridLayout = new QGridLayout(scrollAreaWidgetContents_5);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        plot_LB3 = new QCustomPlot(scrollAreaWidgetContents_5);
        plot_LB3->setObjectName(QString::fromUtf8("plot_LB3"));
        gridLayout_18 = new QGridLayout(plot_LB3);
        gridLayout_18->setObjectName(QString::fromUtf8("gridLayout_18"));
        buttonBox_4 = new QDialogButtonBox(plot_LB3);
        buttonBox_4->setObjectName(QString::fromUtf8("buttonBox_4"));
        buttonBox_4->setStandardButtons(QDialogButtonBox::NoButton);

        gridLayout_18->addWidget(buttonBox_4, 0, 0, 1, 1);


        gridLayout->addWidget(plot_LB3, 0, 0, 1, 1);

        scrollArea_4->setWidget(scrollAreaWidgetContents_5);

        gridLayout_19->addWidget(scrollArea_4, 0, 0, 1, 1);

        tabWidget->addTab(tab_4, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_6 = new QGridLayout(tab);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        scrollArea_5 = new QScrollArea(tab);
        scrollArea_5->setObjectName(QString::fromUtf8("scrollArea_5"));
        scrollArea_5->setWidgetResizable(true);
        scrollAreaWidgetContents_6 = new QWidget();
        scrollAreaWidgetContents_6->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_6"));
        scrollAreaWidgetContents_6->setGeometry(QRect(0, 0, 1108, 717));
        gridLayout_23 = new QGridLayout(scrollAreaWidgetContents_6);
        gridLayout_23->setObjectName(QString::fromUtf8("gridLayout_23"));
        plot_LB4 = new QCustomPlot(scrollAreaWidgetContents_6);
        plot_LB4->setObjectName(QString::fromUtf8("plot_LB4"));
        gridLayout_2 = new QGridLayout(plot_LB4);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        buttonBox_5 = new QDialogButtonBox(plot_LB4);
        buttonBox_5->setObjectName(QString::fromUtf8("buttonBox_5"));
        buttonBox_5->setStandardButtons(QDialogButtonBox::NoButton);

        gridLayout_2->addWidget(buttonBox_5, 0, 0, 1, 1);


        gridLayout_23->addWidget(plot_LB4, 0, 0, 1, 1);

        scrollArea_5->setWidget(scrollAreaWidgetContents_6);

        gridLayout_6->addWidget(scrollArea_5, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        gridLayout_22 = new QGridLayout(tab_5);
        gridLayout_22->setObjectName(QString::fromUtf8("gridLayout_22"));
        scrollArea_6 = new QScrollArea(tab_5);
        scrollArea_6->setObjectName(QString::fromUtf8("scrollArea_6"));
        scrollArea_6->setWidgetResizable(true);
        scrollAreaWidgetContents_7 = new QWidget();
        scrollAreaWidgetContents_7->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_7"));
        scrollAreaWidgetContents_7->setGeometry(QRect(0, 0, 1108, 717));
        gridLayout_21 = new QGridLayout(scrollAreaWidgetContents_7);
        gridLayout_21->setObjectName(QString::fromUtf8("gridLayout_21"));
        plot_LB5 = new QCustomPlot(scrollAreaWidgetContents_7);
        plot_LB5->setObjectName(QString::fromUtf8("plot_LB5"));
        gridLayout_7 = new QGridLayout(plot_LB5);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        buttonBox_6 = new QDialogButtonBox(plot_LB5);
        buttonBox_6->setObjectName(QString::fromUtf8("buttonBox_6"));
        buttonBox_6->setStandardButtons(QDialogButtonBox::NoButton);

        gridLayout_7->addWidget(buttonBox_6, 0, 0, 1, 1);


        gridLayout_21->addWidget(plot_LB5, 0, 0, 1, 1);

        scrollArea_6->setWidget(scrollAreaWidgetContents_7);

        gridLayout_22->addWidget(scrollArea_6, 0, 0, 1, 1);

        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        gridLayout_25 = new QGridLayout(tab_6);
        gridLayout_25->setObjectName(QString::fromUtf8("gridLayout_25"));
        scrollArea_7 = new QScrollArea(tab_6);
        scrollArea_7->setObjectName(QString::fromUtf8("scrollArea_7"));
        scrollArea_7->setWidgetResizable(true);
        scrollAreaWidgetContents_8 = new QWidget();
        scrollAreaWidgetContents_8->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_8"));
        scrollAreaWidgetContents_8->setGeometry(QRect(0, 0, 1108, 717));
        gridLayout_24 = new QGridLayout(scrollAreaWidgetContents_8);
        gridLayout_24->setObjectName(QString::fromUtf8("gridLayout_24"));
        plot_LB6 = new QCustomPlot(scrollAreaWidgetContents_8);
        plot_LB6->setObjectName(QString::fromUtf8("plot_LB6"));
        gridLayout_8 = new QGridLayout(plot_LB6);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        buttonBox_7 = new QDialogButtonBox(plot_LB6);
        buttonBox_7->setObjectName(QString::fromUtf8("buttonBox_7"));
        buttonBox_7->setStandardButtons(QDialogButtonBox::NoButton);

        gridLayout_8->addWidget(buttonBox_7, 0, 0, 1, 1);


        gridLayout_24->addWidget(plot_LB6, 0, 0, 1, 1);

        scrollArea_7->setWidget(scrollAreaWidgetContents_8);

        gridLayout_25->addWidget(scrollArea_7, 0, 0, 1, 1);

        tabWidget->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QString::fromUtf8("tab_7"));
        gridLayout_27 = new QGridLayout(tab_7);
        gridLayout_27->setObjectName(QString::fromUtf8("gridLayout_27"));
        scrollArea_8 = new QScrollArea(tab_7);
        scrollArea_8->setObjectName(QString::fromUtf8("scrollArea_8"));
        scrollArea_8->setWidgetResizable(true);
        scrollAreaWidgetContents_9 = new QWidget();
        scrollAreaWidgetContents_9->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_9"));
        scrollAreaWidgetContents_9->setGeometry(QRect(0, 0, 1108, 717));
        gridLayout_26 = new QGridLayout(scrollAreaWidgetContents_9);
        gridLayout_26->setObjectName(QString::fromUtf8("gridLayout_26"));
        plot_LB7 = new QCustomPlot(scrollAreaWidgetContents_9);
        plot_LB7->setObjectName(QString::fromUtf8("plot_LB7"));
        gridLayout_9 = new QGridLayout(plot_LB7);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        buttonBox_8 = new QDialogButtonBox(plot_LB7);
        buttonBox_8->setObjectName(QString::fromUtf8("buttonBox_8"));
        buttonBox_8->setStandardButtons(QDialogButtonBox::NoButton);

        gridLayout_9->addWidget(buttonBox_8, 0, 0, 1, 1);


        gridLayout_26->addWidget(plot_LB7, 0, 0, 1, 1);

        scrollArea_8->setWidget(scrollAreaWidgetContents_9);

        gridLayout_27->addWidget(scrollArea_8, 0, 0, 1, 1);

        tabWidget->addTab(tab_7, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName(QString::fromUtf8("tab_8"));
        gridLayout_29 = new QGridLayout(tab_8);
        gridLayout_29->setObjectName(QString::fromUtf8("gridLayout_29"));
        scrollArea_9 = new QScrollArea(tab_8);
        scrollArea_9->setObjectName(QString::fromUtf8("scrollArea_9"));
        scrollArea_9->setWidgetResizable(true);
        scrollAreaWidgetContents_10 = new QWidget();
        scrollAreaWidgetContents_10->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_10"));
        scrollAreaWidgetContents_10->setGeometry(QRect(0, 0, 1108, 717));
        gridLayout_28 = new QGridLayout(scrollAreaWidgetContents_10);
        gridLayout_28->setObjectName(QString::fromUtf8("gridLayout_28"));
        plot_LB8 = new QCustomPlot(scrollAreaWidgetContents_10);
        plot_LB8->setObjectName(QString::fromUtf8("plot_LB8"));
        gridLayout_10 = new QGridLayout(plot_LB8);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        buttonBox_9 = new QDialogButtonBox(plot_LB8);
        buttonBox_9->setObjectName(QString::fromUtf8("buttonBox_9"));
        buttonBox_9->setStandardButtons(QDialogButtonBox::NoButton);

        gridLayout_10->addWidget(buttonBox_9, 0, 0, 1, 1);


        gridLayout_28->addWidget(plot_LB8, 0, 0, 1, 1);

        scrollArea_9->setWidget(scrollAreaWidgetContents_10);

        gridLayout_29->addWidget(scrollArea_9, 0, 0, 1, 1);

        tabWidget->addTab(tab_8, QString());
        tab_9 = new QWidget();
        tab_9->setObjectName(QString::fromUtf8("tab_9"));
        gridLayout_31 = new QGridLayout(tab_9);
        gridLayout_31->setObjectName(QString::fromUtf8("gridLayout_31"));
        scrollArea_10 = new QScrollArea(tab_9);
        scrollArea_10->setObjectName(QString::fromUtf8("scrollArea_10"));
        scrollArea_10->setWidgetResizable(true);
        scrollAreaWidgetContents_11 = new QWidget();
        scrollAreaWidgetContents_11->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_11"));
        scrollAreaWidgetContents_11->setGeometry(QRect(0, 0, 1108, 717));
        gridLayout_30 = new QGridLayout(scrollAreaWidgetContents_11);
        gridLayout_30->setObjectName(QString::fromUtf8("gridLayout_30"));
        plot_LB9 = new QCustomPlot(scrollAreaWidgetContents_11);
        plot_LB9->setObjectName(QString::fromUtf8("plot_LB9"));
        gridLayout_11 = new QGridLayout(plot_LB9);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        buttonBox_10 = new QDialogButtonBox(plot_LB9);
        buttonBox_10->setObjectName(QString::fromUtf8("buttonBox_10"));
        buttonBox_10->setStandardButtons(QDialogButtonBox::NoButton);

        gridLayout_11->addWidget(buttonBox_10, 0, 0, 1, 1);


        gridLayout_30->addWidget(plot_LB9, 0, 0, 1, 1);

        scrollArea_10->setWidget(scrollAreaWidgetContents_11);

        gridLayout_31->addWidget(scrollArea_10, 0, 0, 1, 1);

        tabWidget->addTab(tab_9, QString());

        gridLayout_20->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(realtimev2);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(realtimev2);
    } // setupUi

    void retranslateUi(QWidget *realtimev2)
    {
        realtimev2->setWindowTitle(QApplication::translate("realtimev2", "Form", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QApplication::translate("realtimev2", "CB", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("realtimev2", "LB1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("realtimev2", "LB2", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("realtimev2", "LB3", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("realtimev2", "LB4", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("realtimev2", "LB5", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("realtimev2", "LB6", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QApplication::translate("realtimev2", "LB7", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_8), QApplication::translate("realtimev2", "LB8", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_9), QApplication::translate("realtimev2", "LB9", nullptr));
    } // retranslateUi

};

namespace Ui {
    class realtimev2: public Ui_realtimev2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REALTIMEV2_H
