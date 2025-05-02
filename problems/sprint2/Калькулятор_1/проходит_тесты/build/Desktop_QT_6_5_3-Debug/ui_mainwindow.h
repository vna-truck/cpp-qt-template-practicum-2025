/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *l_formula;
    QHBoxLayout *horizontalLayout;
    QLabel *l_memory;
    QLabel *l_result;
    QPushButton *pushButton_15;
    QPushButton *pushButton_16;
    QPushButton *pushButton_17;
    QPushButton *pushButton_23;
    QPushButton *pushButton_14;
    QPushButton *pushButton_13;
    QPushButton *pushButton_18;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_19;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_20;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_21;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QPushButton *pushButton_22;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(415, 388);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(14);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        l_formula = new QLabel(centralwidget);
        l_formula->setObjectName("l_formula");

        gridLayout->addWidget(l_formula, 0, 0, 1, 4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        l_memory = new QLabel(centralwidget);
        l_memory->setObjectName("l_memory");

        horizontalLayout->addWidget(l_memory);

        l_result = new QLabel(centralwidget);
        l_result->setObjectName("l_result");

        horizontalLayout->addWidget(l_result);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 4);

        pushButton_15 = new QPushButton(centralwidget);
        pushButton_15->setObjectName("pushButton_15");

        gridLayout->addWidget(pushButton_15, 2, 0, 1, 1);

        pushButton_16 = new QPushButton(centralwidget);
        pushButton_16->setObjectName("pushButton_16");

        gridLayout->addWidget(pushButton_16, 2, 1, 1, 1);

        pushButton_17 = new QPushButton(centralwidget);
        pushButton_17->setObjectName("pushButton_17");

        gridLayout->addWidget(pushButton_17, 2, 2, 1, 1);

        pushButton_23 = new QPushButton(centralwidget);
        pushButton_23->setObjectName("pushButton_23");

        gridLayout->addWidget(pushButton_23, 2, 3, 1, 1);

        pushButton_14 = new QPushButton(centralwidget);
        pushButton_14->setObjectName("pushButton_14");

        gridLayout->addWidget(pushButton_14, 3, 0, 1, 2);

        pushButton_13 = new QPushButton(centralwidget);
        pushButton_13->setObjectName("pushButton_13");

        gridLayout->addWidget(pushButton_13, 3, 2, 1, 1);

        pushButton_18 = new QPushButton(centralwidget);
        pushButton_18->setObjectName("pushButton_18");

        gridLayout->addWidget(pushButton_18, 3, 3, 1, 1);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");

        gridLayout->addWidget(pushButton, 4, 0, 1, 1);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");

        gridLayout->addWidget(pushButton_2, 4, 1, 1, 1);

        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");

        gridLayout->addWidget(pushButton_3, 4, 2, 1, 1);

        pushButton_19 = new QPushButton(centralwidget);
        pushButton_19->setObjectName("pushButton_19");

        gridLayout->addWidget(pushButton_19, 4, 3, 1, 1);

        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");

        gridLayout->addWidget(pushButton_4, 5, 0, 1, 1);

        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");

        gridLayout->addWidget(pushButton_5, 5, 1, 1, 1);

        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName("pushButton_6");

        gridLayout->addWidget(pushButton_6, 5, 2, 1, 1);

        pushButton_20 = new QPushButton(centralwidget);
        pushButton_20->setObjectName("pushButton_20");

        gridLayout->addWidget(pushButton_20, 5, 3, 1, 1);

        pushButton_7 = new QPushButton(centralwidget);
        pushButton_7->setObjectName("pushButton_7");

        gridLayout->addWidget(pushButton_7, 6, 0, 1, 1);

        pushButton_8 = new QPushButton(centralwidget);
        pushButton_8->setObjectName("pushButton_8");

        gridLayout->addWidget(pushButton_8, 6, 1, 1, 1);

        pushButton_9 = new QPushButton(centralwidget);
        pushButton_9->setObjectName("pushButton_9");

        gridLayout->addWidget(pushButton_9, 6, 2, 1, 1);

        pushButton_21 = new QPushButton(centralwidget);
        pushButton_21->setObjectName("pushButton_21");

        gridLayout->addWidget(pushButton_21, 6, 3, 1, 1);

        pushButton_10 = new QPushButton(centralwidget);
        pushButton_10->setObjectName("pushButton_10");

        gridLayout->addWidget(pushButton_10, 7, 0, 1, 1);

        pushButton_11 = new QPushButton(centralwidget);
        pushButton_11->setObjectName("pushButton_11");

        gridLayout->addWidget(pushButton_11, 7, 1, 1, 1);

        pushButton_12 = new QPushButton(centralwidget);
        pushButton_12->setObjectName("pushButton_12");

        gridLayout->addWidget(pushButton_12, 7, 2, 1, 1);

        pushButton_22 = new QPushButton(centralwidget);
        pushButton_22->setObjectName("pushButton_22");

        gridLayout->addWidget(pushButton_22, 7, 3, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\232\320\260\320\273\321\214\320\272\321\203\320\273\321\217\321\202\320\276\321\200", nullptr));
        l_formula->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"right\">l_formula</p></body></html>", nullptr));
        l_memory->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>l_memory</p></body></html>", nullptr));
        l_result->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"right\">l_result</p></body></html>", nullptr));
        pushButton_15->setText(QCoreApplication::translate("MainWindow", "MC", nullptr));
        pushButton_16->setText(QCoreApplication::translate("MainWindow", "MR", nullptr));
        pushButton_17->setText(QCoreApplication::translate("MainWindow", "MS", nullptr));
        pushButton_23->setText(QCoreApplication::translate("MainWindow", "x\312\270", nullptr));
        pushButton_14->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "\302\261", nullptr));
        pushButton_18->setText(QCoreApplication::translate("MainWindow", "\303\267", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        pushButton_19->setText(QCoreApplication::translate("MainWindow", "\303\227", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        pushButton_20->setText(QCoreApplication::translate("MainWindow", "\342\210\222", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        pushButton_21->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        pushButton_12->setText(QCoreApplication::translate("MainWindow", "\342\214\253", nullptr));
        pushButton_22->setText(QCoreApplication::translate("MainWindow", "=", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
