/********************************************************************************
** Form generated from reading UI file 'InducedPolarization.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INDUCEDPOLARIZATION_H
#define UI_INDUCEDPOLARIZATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "include\3ddisplay\ViewerWidget3d.h"

QT_BEGIN_NAMESPACE

class Ui_InducedPolarizationClass
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_leftDown;
    QVBoxLayout *verticalLayout;
    ViewerWidget3d *widget_leftUpper;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_rightDown;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_rightUpper;

    void setupUi(QDialog *InducedPolarizationClass)
    {
        if (InducedPolarizationClass->objectName().isEmpty())
            InducedPolarizationClass->setObjectName(QStringLiteral("InducedPolarizationClass"));
        InducedPolarizationClass->resize(1023, 807);
        gridLayout = new QGridLayout(InducedPolarizationClass);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        widget_leftDown = new QWidget(InducedPolarizationClass);
        widget_leftDown->setObjectName(QStringLiteral("widget_leftDown"));

        verticalLayout_3->addWidget(widget_leftDown);

        verticalLayout_3->setStretch(0, 100);

        gridLayout->addLayout(verticalLayout_3, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget_leftUpper = new ViewerWidget3d(InducedPolarizationClass);
        widget_leftUpper->setObjectName(QStringLiteral("widget_leftUpper"));

        verticalLayout->addWidget(widget_leftUpper);

        verticalLayout->setStretch(0, 100);

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        widget_rightDown = new QWidget(InducedPolarizationClass);
        widget_rightDown->setObjectName(QStringLiteral("widget_rightDown"));

        verticalLayout_4->addWidget(widget_rightDown);

        verticalLayout_4->setStretch(0, 100);

        gridLayout->addLayout(verticalLayout_4, 1, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        widget_rightUpper = new QWidget(InducedPolarizationClass);
        widget_rightUpper->setObjectName(QStringLiteral("widget_rightUpper"));

        verticalLayout_2->addWidget(widget_rightUpper);

        verticalLayout_2->setStretch(0, 100);

        gridLayout->addLayout(verticalLayout_2, 0, 1, 1, 1);


        retranslateUi(InducedPolarizationClass);

        QMetaObject::connectSlotsByName(InducedPolarizationClass);
    } // setupUi

    void retranslateUi(QDialog *InducedPolarizationClass)
    {
        InducedPolarizationClass->setWindowTitle(QApplication::translate("InducedPolarizationClass", "\345\217\257\350\247\206\345\214\226\345\244\232\347\272\247\347\225\214\351\235\242", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class InducedPolarizationClass: public Ui_InducedPolarizationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INDUCEDPOLARIZATION_H
