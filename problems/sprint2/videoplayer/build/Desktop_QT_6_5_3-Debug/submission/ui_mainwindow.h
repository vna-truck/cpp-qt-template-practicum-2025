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
#include <QtMultimediaWidgets/QVideoWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QVideoWidget *video_output;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_pause;
    QSlider *sld_pos;
    QPushButton *btn_choose;
    QSlider *sld_volume;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(548, 380);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        video_output = new QVideoWidget(centralwidget);
        video_output->setObjectName("video_output");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(video_output->sizePolicy().hasHeightForWidth());
        video_output->setSizePolicy(sizePolicy);
        video_output->setMinimumSize(QSize(100, 100));

        verticalLayout->addWidget(video_output);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(15, 0, 15, 5);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName("horizontalLayout");
        btn_pause = new QPushButton(centralwidget);
        btn_pause->setObjectName("btn_pause");
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btn_pause->sizePolicy().hasHeightForWidth());
        btn_pause->setSizePolicy(sizePolicy1);
        btn_pause->setMinimumSize(QSize(39, 0));
        btn_pause->setMaximumSize(QSize(39, 16777215));

        horizontalLayout->addWidget(btn_pause, 0, Qt::AlignTop);

        sld_pos = new QSlider(centralwidget);
        sld_pos->setObjectName("sld_pos");
        sld_pos->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(sld_pos, 0, Qt::AlignTop);


        verticalLayout_2->addLayout(horizontalLayout);

        btn_choose = new QPushButton(centralwidget);
        btn_choose->setObjectName("btn_choose");
        btn_choose->setMinimumSize(QSize(100, 32));

        verticalLayout_2->addWidget(btn_choose);


        horizontalLayout_2->addLayout(verticalLayout_2);

        sld_volume = new QSlider(centralwidget);
        sld_volume->setObjectName("sld_volume");
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Ignored);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(sld_volume->sizePolicy().hasHeightForWidth());
        sld_volume->setSizePolicy(sizePolicy2);
        sld_volume->setMaximumSize(QSize(16777215, 1000));
        sld_volume->setMaximum(100);
        sld_volume->setValue(100);
        sld_volume->setOrientation(Qt::Vertical);

        horizontalLayout_2->addWidget(sld_volume);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout->setStretch(0, 1);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\222\320\270\320\264\320\265\320\276\320\277\320\273\320\265\320\265\321\200", nullptr));
        btn_pause->setText(QCoreApplication::translate("MainWindow", "\342\217\270", nullptr));
        btn_choose->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
