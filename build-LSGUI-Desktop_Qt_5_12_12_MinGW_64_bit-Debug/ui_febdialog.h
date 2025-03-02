/********************************************************************************
** Form generated from reading UI file 'febdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FEBDIALOG_H
#define UI_FEBDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_febDialog
{
public:
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *groupBox;
    QPushButton *pushButton;
    QLabel *label;
    QLineEdit *lineEdit_dacValue;
    QLabel *label_3;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QRadioButton *rB_Feb_Read;
    QRadioButton *rB_Feb_Set;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *rB_DB_No1;
    QRadioButton *rB_DB_No2;
    QRadioButton *rB_DB_No3;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *rB_DB_P1;
    QRadioButton *rB_DB_P2;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *rB_Feb1;
    QRadioButton *rB_Feb2;
    QRadioButton *rB_Feb3;
    QRadioButton *rB_Feb4;
    QWidget *layoutWidget4;
    QVBoxLayout *verticalLayout_5;
    QRadioButton *rB_Dac1;
    QRadioButton *rB_Dac2;
    QRadioButton *rB_Adc1;
    QRadioButton *rB_Adc2;
    QWidget *layoutWidget5;
    QVBoxLayout *verticalLayout_6;
    QRadioButton *rB_Vth1;
    QRadioButton *rB_Vth2;
    QRadioButton *rB_Vmon1;
    QRadioButton *rB_Vmon2;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QFrame *line_5;
    QPlainTextEdit *plainTextEdit;
    QLabel *label_2;
    QPlainTextEdit *plainTextEdit_2;
    QLabel *label_4;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QWidget *layoutWidget6;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QWidget *tab_2;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;

    void setupUi(QDialog *febDialog)
    {
        if (febDialog->objectName().isEmpty())
            febDialog->setObjectName(QString::fromUtf8("febDialog"));
        febDialog->resize(800, 320);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(febDialog->sizePolicy().hasHeightForWidth());
        febDialog->setSizePolicy(sizePolicy);
        febDialog->setMinimumSize(QSize(800, 320));
        febDialog->setMaximumSize(QSize(800, 320));
        gridLayout_2 = new QGridLayout(febDialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tabWidget = new QTabWidget(febDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(600, 10, 171, 151));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 100, 141, 24));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(12, 30, 49, 16));
        lineEdit_dacValue = new QLineEdit(groupBox);
        lineEdit_dacValue->setObjectName(QString::fromUtf8("lineEdit_dacValue"));
        lineEdit_dacValue->setGeometry(QRect(12, 50, 61, 24));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(80, 50, 21, 21));
        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 10, 581, 151));
        layoutWidget = new QWidget(groupBox_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 32, 74, 52));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        rB_Feb_Read = new QRadioButton(layoutWidget);
        rB_Feb_Read->setObjectName(QString::fromUtf8("rB_Feb_Read"));

        verticalLayout->addWidget(rB_Feb_Read);

        rB_Feb_Set = new QRadioButton(layoutWidget);
        rB_Feb_Set->setObjectName(QString::fromUtf8("rB_Feb_Set"));

        verticalLayout->addWidget(rB_Feb_Set);

        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(90, 32, 135, 80));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        rB_DB_No1 = new QRadioButton(layoutWidget1);
        rB_DB_No1->setObjectName(QString::fromUtf8("rB_DB_No1"));

        verticalLayout_2->addWidget(rB_DB_No1);

        rB_DB_No2 = new QRadioButton(layoutWidget1);
        rB_DB_No2->setObjectName(QString::fromUtf8("rB_DB_No2"));

        verticalLayout_2->addWidget(rB_DB_No2);

        rB_DB_No3 = new QRadioButton(layoutWidget1);
        rB_DB_No3->setObjectName(QString::fromUtf8("rB_DB_No3"));

        verticalLayout_2->addWidget(rB_DB_No3);

        layoutWidget2 = new QWidget(groupBox_2);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(230, 32, 143, 52));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        rB_DB_P1 = new QRadioButton(layoutWidget2);
        rB_DB_P1->setObjectName(QString::fromUtf8("rB_DB_P1"));

        verticalLayout_3->addWidget(rB_DB_P1);

        rB_DB_P2 = new QRadioButton(layoutWidget2);
        rB_DB_P2->setObjectName(QString::fromUtf8("rB_DB_P2"));

        verticalLayout_3->addWidget(rB_DB_P2);

        layoutWidget3 = new QWidget(groupBox_2);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(380, 32, 67, 108));
        verticalLayout_4 = new QVBoxLayout(layoutWidget3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        rB_Feb1 = new QRadioButton(layoutWidget3);
        rB_Feb1->setObjectName(QString::fromUtf8("rB_Feb1"));

        verticalLayout_4->addWidget(rB_Feb1);

        rB_Feb2 = new QRadioButton(layoutWidget3);
        rB_Feb2->setObjectName(QString::fromUtf8("rB_Feb2"));

        verticalLayout_4->addWidget(rB_Feb2);

        rB_Feb3 = new QRadioButton(layoutWidget3);
        rB_Feb3->setObjectName(QString::fromUtf8("rB_Feb3"));

        verticalLayout_4->addWidget(rB_Feb3);

        rB_Feb4 = new QRadioButton(layoutWidget3);
        rB_Feb4->setObjectName(QString::fromUtf8("rB_Feb4"));

        verticalLayout_4->addWidget(rB_Feb4);

        layoutWidget4 = new QWidget(groupBox_2);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(450, 32, 55, 108));
        verticalLayout_5 = new QVBoxLayout(layoutWidget4);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        rB_Dac1 = new QRadioButton(layoutWidget4);
        rB_Dac1->setObjectName(QString::fromUtf8("rB_Dac1"));

        verticalLayout_5->addWidget(rB_Dac1);

        rB_Dac2 = new QRadioButton(layoutWidget4);
        rB_Dac2->setObjectName(QString::fromUtf8("rB_Dac2"));

        verticalLayout_5->addWidget(rB_Dac2);

        rB_Adc1 = new QRadioButton(layoutWidget4);
        rB_Adc1->setObjectName(QString::fromUtf8("rB_Adc1"));

        verticalLayout_5->addWidget(rB_Adc1);

        rB_Adc2 = new QRadioButton(layoutWidget4);
        rB_Adc2->setObjectName(QString::fromUtf8("rB_Adc2"));

        verticalLayout_5->addWidget(rB_Adc2);

        layoutWidget5 = new QWidget(groupBox_2);
        layoutWidget5->setObjectName(QString::fromUtf8("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(510, 32, 60, 108));
        verticalLayout_6 = new QVBoxLayout(layoutWidget5);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        rB_Vth1 = new QRadioButton(layoutWidget5);
        rB_Vth1->setObjectName(QString::fromUtf8("rB_Vth1"));

        verticalLayout_6->addWidget(rB_Vth1);

        rB_Vth2 = new QRadioButton(layoutWidget5);
        rB_Vth2->setObjectName(QString::fromUtf8("rB_Vth2"));

        verticalLayout_6->addWidget(rB_Vth2);

        rB_Vmon1 = new QRadioButton(layoutWidget5);
        rB_Vmon1->setObjectName(QString::fromUtf8("rB_Vmon1"));

        verticalLayout_6->addWidget(rB_Vmon1);

        rB_Vmon2 = new QRadioButton(layoutWidget5);
        rB_Vmon2->setObjectName(QString::fromUtf8("rB_Vmon2"));

        verticalLayout_6->addWidget(rB_Vmon2);

        line = new QFrame(groupBox_2);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(80, 31, 16, 81));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(groupBox_2);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(220, 31, 16, 81));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(groupBox_2);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(370, 31, 16, 111));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(groupBox_2);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(440, 30, 16, 111));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(groupBox_2);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setGeometry(QRect(500, 31, 16, 111));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);
        plainTextEdit = new QPlainTextEdit(tab);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(240, 180, 151, 71));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(plainTextEdit->sizePolicy().hasHeightForWidth());
        plainTextEdit->setSizePolicy(sizePolicy2);
        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(240, 160, 121, 21));
        plainTextEdit_2 = new QPlainTextEdit(tab);
        plainTextEdit_2->setObjectName(QString::fromUtf8("plainTextEdit_2"));
        plainTextEdit_2->setGeometry(QRect(450, 180, 281, 71));
        sizePolicy2.setHeightForWidth(plainTextEdit_2->sizePolicy().hasHeightForWidth());
        plainTextEdit_2->setSizePolicy(sizePolicy2);
        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(450, 160, 121, 21));
        layoutWidget_2 = new QWidget(tab);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(210, 180, 21, 71));
        verticalLayout_8 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(layoutWidget_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout_8->addWidget(label_9);

        label_10 = new QLabel(layoutWidget_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        verticalLayout_8->addWidget(label_10);

        label_11 = new QLabel(layoutWidget_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        verticalLayout_8->addWidget(label_11);

        label_12 = new QLabel(layoutWidget_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        verticalLayout_8->addWidget(label_12);

        layoutWidget6 = new QWidget(tab);
        layoutWidget6->setObjectName(QString::fromUtf8("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(420, 180, 21, 71));
        verticalLayout_7 = new QVBoxLayout(layoutWidget6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget6);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_7->addWidget(label_5);

        label_6 = new QLabel(layoutWidget6);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_7->addWidget(label_6);

        label_7 = new QLabel(layoutWidget6);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_7->addWidget(label_7);

        label_8 = new QLabel(layoutWidget6);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_7->addWidget(label_8);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout = new QGridLayout(tab_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableWidget = new QTableWidget(tab_2);
        if (tableWidget->columnCount() < 8)
            tableWidget->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        if (tableWidget->rowCount() < 8)
            tableWidget->setRowCount(8);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem15);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        sizePolicy1.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(febDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(febDialog);
    } // setupUi

    void retranslateUi(QDialog *febDialog)
    {
        febDialog->setWindowTitle(QApplication::translate("febDialog", "Dialog", nullptr));
        groupBox->setTitle(QApplication::translate("febDialog", "Insert Analog Value", nullptr));
        pushButton->setText(QApplication::translate("febDialog", "Convert", nullptr));
        label->setText(QApplication::translate("febDialog", "DAC Value", nullptr));
        label_3->setText(QApplication::translate("febDialog", "mV", nullptr));
        groupBox_2->setTitle(QApplication::translate("febDialog", "Select Parameter", nullptr));
        rB_Feb_Read->setText(QApplication::translate("febDialog", "Read FEB", nullptr));
        rB_Feb_Set->setText(QApplication::translate("febDialog", "Wrire FEB", nullptr));
        rB_DB_No1->setText(QApplication::translate("febDialog", "Distribution Board No.1", nullptr));
        rB_DB_No2->setText(QApplication::translate("febDialog", "Distribution Board No.2", nullptr));
        rB_DB_No3->setText(QApplication::translate("febDialog", "Distribution Board No.2", nullptr));
        rB_DB_P1->setText(QApplication::translate("febDialog", "Distribution Board Port 1", nullptr));
        rB_DB_P2->setText(QApplication::translate("febDialog", "Distribution Board Port 2", nullptr));
        rB_Feb1->setText(QApplication::translate("febDialog", "FEB No1", nullptr));
        rB_Feb2->setText(QApplication::translate("febDialog", "FEB No2", nullptr));
        rB_Feb3->setText(QApplication::translate("febDialog", "FEB No3", nullptr));
        rB_Feb4->setText(QApplication::translate("febDialog", "FEB No4", nullptr));
        rB_Dac1->setText(QApplication::translate("febDialog", "DAC 1", nullptr));
        rB_Dac2->setText(QApplication::translate("febDialog", "DAC 2", nullptr));
        rB_Adc1->setText(QApplication::translate("febDialog", "ADC1", nullptr));
        rB_Adc2->setText(QApplication::translate("febDialog", "ADC 2", nullptr));
        rB_Vth1->setText(QApplication::translate("febDialog", "Vth1", nullptr));
        rB_Vth2->setText(QApplication::translate("febDialog", "Vth2", nullptr));
        rB_Vmon1->setText(QApplication::translate("febDialog", "Vmon1", nullptr));
        rB_Vmon2->setText(QApplication::translate("febDialog", "Vmon2", nullptr));
        label_2->setText(QApplication::translate("febDialog", "128 Bit Result (HEX) ", nullptr));
        label_4->setText(QApplication::translate("febDialog", "128 Bit Result (BIN) ", nullptr));
        label_9->setText(QApplication::translate("febDialog", "D(3)", nullptr));
        label_10->setText(QApplication::translate("febDialog", "D(2)", nullptr));
        label_11->setText(QApplication::translate("febDialog", "D(1)", nullptr));
        label_12->setText(QApplication::translate("febDialog", "D(0)", nullptr));
        label_5->setText(QApplication::translate("febDialog", "D(3)", nullptr));
        label_6->setText(QApplication::translate("febDialog", "D(2)", nullptr));
        label_7->setText(QApplication::translate("febDialog", "D(1)", nullptr));
        label_8->setText(QApplication::translate("febDialog", "D(0)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("febDialog", "FEB Command Generator", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("febDialog", "Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("febDialog", "Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("febDialog", "Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("febDialog", "Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("febDialog", "Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("febDialog", "Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("febDialog", "New ", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("febDialog", "Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem8->setText(QApplication::translate("febDialog", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem9->setText(QApplication::translate("febDialog", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem10->setText(QApplication::translate("febDialog", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem11->setText(QApplication::translate("febDialog", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem12->setText(QApplication::translate("febDialog", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem13->setText(QApplication::translate("febDialog", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem14->setText(QApplication::translate("febDialog", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem15->setText(QApplication::translate("febDialog", "New Row", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("febDialog", "Adjusts", nullptr));
    } // retranslateUi

};

namespace Ui {
    class febDialog: public Ui_febDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FEBDIALOG_H
