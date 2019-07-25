/********************************************************************************
** Form generated from reading UI file 'DialogContourLevels.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCONTOURLEVELS_H
#define UI_DIALOGCONTOURLEVELS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogContourLevels
{
public:
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton_exactLevels;
    QRadioButton *radioButton_approximateLevels;
    QWidget *widget_rangeDistribution;
    QVBoxLayout *verticalLayout_8;
    QGroupBox *groupBox_rangeDistribution;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *radioButton_range0;
    QRadioButton *radioButton_range1;
    QRadioButton *radioButton_range2;
    QWidget *widget_minimunLevel;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout;
    QLabel *label_minimunLevel;
    QLineEdit *lineEdit_minimunLevel;
    QWidget *widget_maximumLevel;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_maximumLevel;
    QLineEdit *lineEdit_maximumLevel;
    QWidget *widget_numberofLevels;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_numberOfLevels;
    QLineEdit *lineEdit_numberOfLevels;
    QWidget *widget_delta;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_delta;
    QLineEdit *lineEdit_delta;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_resetRange;
    QLabel *label_space;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_cancle;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *DialogContourLevels)
    {
        if (DialogContourLevels->objectName().isEmpty())
            DialogContourLevels->setObjectName(QStringLiteral("DialogContourLevels"));
        DialogContourLevels->resize(265, 389);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DialogContourLevels->sizePolicy().hasHeightForWidth());
        DialogContourLevels->setSizePolicy(sizePolicy);
        DialogContourLevels->setMinimumSize(QSize(265, 389));
        DialogContourLevels->setMaximumSize(QSize(265, 389));
        verticalLayout_3 = new QVBoxLayout(DialogContourLevels);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox = new QGroupBox(DialogContourLevels);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        radioButton_exactLevels = new QRadioButton(groupBox);
        radioButton_exactLevels->setObjectName(QStringLiteral("radioButton_exactLevels"));
        radioButton_exactLevels->setChecked(true);

        verticalLayout->addWidget(radioButton_exactLevels);

        radioButton_approximateLevels = new QRadioButton(groupBox);
        radioButton_approximateLevels->setObjectName(QStringLiteral("radioButton_approximateLevels"));

        verticalLayout->addWidget(radioButton_approximateLevels);


        verticalLayout_3->addWidget(groupBox);

        widget_rangeDistribution = new QWidget(DialogContourLevels);
        widget_rangeDistribution->setObjectName(QStringLiteral("widget_rangeDistribution"));
        verticalLayout_8 = new QVBoxLayout(widget_rangeDistribution);
        verticalLayout_8->setSpacing(0);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        groupBox_rangeDistribution = new QGroupBox(widget_rangeDistribution);
        groupBox_rangeDistribution->setObjectName(QStringLiteral("groupBox_rangeDistribution"));
        verticalLayout_2 = new QVBoxLayout(groupBox_rangeDistribution);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        radioButton_range0 = new QRadioButton(groupBox_rangeDistribution);
        radioButton_range0->setObjectName(QStringLiteral("radioButton_range0"));
        radioButton_range0->setChecked(true);

        verticalLayout_2->addWidget(radioButton_range0);

        radioButton_range1 = new QRadioButton(groupBox_rangeDistribution);
        radioButton_range1->setObjectName(QStringLiteral("radioButton_range1"));

        verticalLayout_2->addWidget(radioButton_range1);

        radioButton_range2 = new QRadioButton(groupBox_rangeDistribution);
        radioButton_range2->setObjectName(QStringLiteral("radioButton_range2"));

        verticalLayout_2->addWidget(radioButton_range2);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 1);
        verticalLayout_2->setStretch(2, 1);

        verticalLayout_8->addWidget(groupBox_rangeDistribution);


        verticalLayout_3->addWidget(widget_rangeDistribution);

        widget_minimunLevel = new QWidget(DialogContourLevels);
        widget_minimunLevel->setObjectName(QStringLiteral("widget_minimunLevel"));
        verticalLayout_5 = new QVBoxLayout(widget_minimunLevel);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_minimunLevel = new QLabel(widget_minimunLevel);
        label_minimunLevel->setObjectName(QStringLiteral("label_minimunLevel"));
        sizePolicy.setHeightForWidth(label_minimunLevel->sizePolicy().hasHeightForWidth());
        label_minimunLevel->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label_minimunLevel);

        lineEdit_minimunLevel = new QLineEdit(widget_minimunLevel);
        lineEdit_minimunLevel->setObjectName(QStringLiteral("lineEdit_minimunLevel"));

        horizontalLayout->addWidget(lineEdit_minimunLevel);


        verticalLayout_5->addLayout(horizontalLayout);


        verticalLayout_3->addWidget(widget_minimunLevel);

        widget_maximumLevel = new QWidget(DialogContourLevels);
        widget_maximumLevel->setObjectName(QStringLiteral("widget_maximumLevel"));
        verticalLayout_6 = new QVBoxLayout(widget_maximumLevel);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_maximumLevel = new QLabel(widget_maximumLevel);
        label_maximumLevel->setObjectName(QStringLiteral("label_maximumLevel"));
        sizePolicy.setHeightForWidth(label_maximumLevel->sizePolicy().hasHeightForWidth());
        label_maximumLevel->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_maximumLevel);

        lineEdit_maximumLevel = new QLineEdit(widget_maximumLevel);
        lineEdit_maximumLevel->setObjectName(QStringLiteral("lineEdit_maximumLevel"));
        sizePolicy.setHeightForWidth(lineEdit_maximumLevel->sizePolicy().hasHeightForWidth());
        lineEdit_maximumLevel->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(lineEdit_maximumLevel);


        verticalLayout_6->addLayout(horizontalLayout_2);


        verticalLayout_3->addWidget(widget_maximumLevel);

        widget_numberofLevels = new QWidget(DialogContourLevels);
        widget_numberofLevels->setObjectName(QStringLiteral("widget_numberofLevels"));
        verticalLayout_4 = new QVBoxLayout(widget_numberofLevels);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_numberOfLevels = new QLabel(widget_numberofLevels);
        label_numberOfLevels->setObjectName(QStringLiteral("label_numberOfLevels"));
        sizePolicy.setHeightForWidth(label_numberOfLevels->sizePolicy().hasHeightForWidth());
        label_numberOfLevels->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_numberOfLevels);

        lineEdit_numberOfLevels = new QLineEdit(widget_numberofLevels);
        lineEdit_numberOfLevels->setObjectName(QStringLiteral("lineEdit_numberOfLevels"));
        sizePolicy1.setHeightForWidth(lineEdit_numberOfLevels->sizePolicy().hasHeightForWidth());
        lineEdit_numberOfLevels->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(lineEdit_numberOfLevels);


        verticalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout_3->addWidget(widget_numberofLevels);

        widget_delta = new QWidget(DialogContourLevels);
        widget_delta->setObjectName(QStringLiteral("widget_delta"));
        verticalLayout_7 = new QVBoxLayout(widget_delta);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_delta = new QLabel(widget_delta);
        label_delta->setObjectName(QStringLiteral("label_delta"));
        label_delta->setEnabled(false);
        sizePolicy.setHeightForWidth(label_delta->sizePolicy().hasHeightForWidth());
        label_delta->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(label_delta);

        lineEdit_delta = new QLineEdit(widget_delta);
        lineEdit_delta->setObjectName(QStringLiteral("lineEdit_delta"));
        lineEdit_delta->setEnabled(false);

        horizontalLayout_4->addWidget(lineEdit_delta);


        verticalLayout_7->addLayout(horizontalLayout_4);


        verticalLayout_3->addWidget(widget_delta);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        pushButton_resetRange = new QPushButton(DialogContourLevels);
        pushButton_resetRange->setObjectName(QStringLiteral("pushButton_resetRange"));

        horizontalLayout_5->addWidget(pushButton_resetRange);


        verticalLayout_3->addLayout(horizontalLayout_5);

        label_space = new QLabel(DialogContourLevels);
        label_space->setObjectName(QStringLiteral("label_space"));
        label_space->setMinimumSize(QSize(0, 5));
        label_space->setMaximumSize(QSize(16777215, 5));

        verticalLayout_3->addWidget(label_space);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);

        pushButton_ok = new QPushButton(DialogContourLevels);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));

        horizontalLayout_6->addWidget(pushButton_ok);

        pushButton_cancle = new QPushButton(DialogContourLevels);
        pushButton_cancle->setObjectName(QStringLiteral("pushButton_cancle"));

        horizontalLayout_6->addWidget(pushButton_cancle);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_6);

        verticalLayout_3->setStretch(0, 3);
        verticalLayout_3->setStretch(1, 3);
        verticalLayout_3->setStretch(2, 1);
        verticalLayout_3->setStretch(3, 1);
        verticalLayout_3->setStretch(4, 1);
        verticalLayout_3->setStretch(5, 1);
        verticalLayout_3->setStretch(6, 1);
        verticalLayout_3->setStretch(7, 1);
        verticalLayout_3->setStretch(8, 1);

        retranslateUi(DialogContourLevels);
        QObject::connect(pushButton_cancle, SIGNAL(clicked()), DialogContourLevels, SLOT(reject()));
        QObject::connect(pushButton_resetRange, SIGNAL(clicked()), DialogContourLevels, SLOT(resetRange()));
        QObject::connect(pushButton_ok, SIGNAL(clicked()), DialogContourLevels, SLOT(onClickOK()));
        QObject::connect(pushButton_ok, SIGNAL(clicked()), DialogContourLevels, SLOT(accept()));
        QObject::connect(radioButton_exactLevels, SIGNAL(clicked()), DialogContourLevels, SLOT(onClickExactLevels()));
        QObject::connect(radioButton_approximateLevels, SIGNAL(clicked()), DialogContourLevels, SLOT(onClickApproximateLevels()));
        QObject::connect(radioButton_range0, SIGNAL(clicked()), DialogContourLevels, SLOT(onClickRangeDistribution0()));
        QObject::connect(radioButton_range1, SIGNAL(clicked()), DialogContourLevels, SLOT(onClickRangeDistribution1()));
        QObject::connect(radioButton_range2, SIGNAL(clicked()), DialogContourLevels, SLOT(onClickRangeDistribution2()));

        QMetaObject::connectSlotsByName(DialogContourLevels);
    } // setupUi

    void retranslateUi(QDialog *DialogContourLevels)
    {
        DialogContourLevels->setWindowTitle(QApplication::translate("DialogContourLevels", "Enter Contour Levels", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("DialogContourLevels", "Level Creation Mode", Q_NULLPTR));
        radioButton_exactLevels->setText(QApplication::translate("DialogContourLevels", "Exact levels", Q_NULLPTR));
        radioButton_approximateLevels->setText(QApplication::translate("DialogContourLevels", "Approximate levels for nice values", Q_NULLPTR));
        groupBox_rangeDistribution->setTitle(QApplication::translate("DialogContourLevels", "Range Distribution", Q_NULLPTR));
        radioButton_range0->setText(QApplication::translate("DialogContourLevels", "Min, max, and number of levels", Q_NULLPTR));
        radioButton_range1->setText(QApplication::translate("DialogContourLevels", "Min, max, and delta", Q_NULLPTR));
        radioButton_range2->setText(QApplication::translate("DialogContourLevels", "Exponential distribution", Q_NULLPTR));
        label_minimunLevel->setText(QApplication::translate("DialogContourLevels", "Minimum level:    ", Q_NULLPTR));
        label_maximumLevel->setText(QApplication::translate("DialogContourLevels", "Maximum level:    ", Q_NULLPTR));
        label_numberOfLevels->setText(QApplication::translate("DialogContourLevels", "Number of levels: ", Q_NULLPTR));
        label_delta->setText(QApplication::translate("DialogContourLevels", "Delta:            ", Q_NULLPTR));
        pushButton_resetRange->setText(QApplication::translate("DialogContourLevels", "Reset Range", Q_NULLPTR));
        label_space->setText(QString());
        pushButton_ok->setText(QApplication::translate("DialogContourLevels", "OK", Q_NULLPTR));
        pushButton_cancle->setText(QApplication::translate("DialogContourLevels", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogContourLevels: public Ui_DialogContourLevels {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCONTOURLEVELS_H
