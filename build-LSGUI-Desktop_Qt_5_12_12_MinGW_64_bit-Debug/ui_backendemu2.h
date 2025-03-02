/********************************************************************************
** Form generated from reading UI file 'backendemu2.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BACKENDEMU2_H
#define UI_BACKENDEMU2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_BackendEmu2
{
public:
    QGridLayout *gridLayout_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QCustomPlot *BePlot;
    QGridLayout *gridLayout_2;
    QScrollBar *verticalScrollBar;
    QScrollBar *horizontalScrollBar;

    void setupUi(QWidget *BackendEmu2)
    {
        if (BackendEmu2->objectName().isEmpty())
            BackendEmu2->setObjectName(QString::fromUtf8("BackendEmu2"));
        BackendEmu2->resize(1097, 673);
        gridLayout_3 = new QGridLayout(BackendEmu2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        scrollArea = new QScrollArea(BackendEmu2);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1057, 633));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        BePlot = new QCustomPlot(scrollAreaWidgetContents);
        BePlot->setObjectName(QString::fromUtf8("BePlot"));
        gridLayout_2 = new QGridLayout(BePlot);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));

        gridLayout->addWidget(BePlot, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_3->addWidget(scrollArea, 0, 0, 1, 1);

        verticalScrollBar = new QScrollBar(BackendEmu2);
        verticalScrollBar->setObjectName(QString::fromUtf8("verticalScrollBar"));
        verticalScrollBar->setOrientation(Qt::Vertical);

        gridLayout_3->addWidget(verticalScrollBar, 0, 1, 1, 1);

        horizontalScrollBar = new QScrollBar(BackendEmu2);
        horizontalScrollBar->setObjectName(QString::fromUtf8("horizontalScrollBar"));
        horizontalScrollBar->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(horizontalScrollBar, 1, 0, 1, 1);


        retranslateUi(BackendEmu2);

        QMetaObject::connectSlotsByName(BackendEmu2);
    } // setupUi

    void retranslateUi(QWidget *BackendEmu2)
    {
        BackendEmu2->setWindowTitle(QApplication::translate("BackendEmu2", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BackendEmu2: public Ui_BackendEmu2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BACKENDEMU2_H
