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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "include\3ddisplay\ViewerWidget3d.h"

QT_BEGIN_NAMESPACE

class Ui_InducedPolarization
{
public:
    QAction *action22;
    QAction *action_openOSGFile1;
    QAction *action_openOSGFile2;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    ViewerWidget3d *widget_leftUpper;
    ViewerWidget3d *widget_rightUpper;
    QHBoxLayout *horizontalLayout_2;
    ViewerWidget3d *widget_leftDown;
    ViewerWidget3d *widget_rightDown;
    QMenuBar *menubar;
    QMenu *menudfA;
    QMenu *menuOSG;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *InducedPolarization)
    {
        if (InducedPolarization->objectName().isEmpty())
            InducedPolarization->setObjectName(QStringLiteral("InducedPolarization"));
        InducedPolarization->resize(986, 742);
        action22 = new QAction(InducedPolarization);
        action22->setObjectName(QStringLiteral("action22"));
        action_openOSGFile1 = new QAction(InducedPolarization);
        action_openOSGFile1->setObjectName(QStringLiteral("action_openOSGFile1"));
        action_openOSGFile2 = new QAction(InducedPolarization);
        action_openOSGFile2->setObjectName(QStringLiteral("action_openOSGFile2"));
        centralwidget = new QWidget(InducedPolarization);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget_leftUpper = new ViewerWidget3d(centralwidget);
        widget_leftUpper->setObjectName(QStringLiteral("widget_leftUpper"));

        horizontalLayout->addWidget(widget_leftUpper);

        widget_rightUpper = new ViewerWidget3d(centralwidget);
        widget_rightUpper->setObjectName(QStringLiteral("widget_rightUpper"));

        horizontalLayout->addWidget(widget_rightUpper);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        widget_leftDown = new ViewerWidget3d(centralwidget);
        widget_leftDown->setObjectName(QStringLiteral("widget_leftDown"));

        horizontalLayout_2->addWidget(widget_leftDown);

        widget_rightDown = new ViewerWidget3d(centralwidget);
        widget_rightDown->setObjectName(QStringLiteral("widget_rightDown"));

        horizontalLayout_2->addWidget(widget_rightDown);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);
        InducedPolarization->setCentralWidget(centralwidget);
        menubar = new QMenuBar(InducedPolarization);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 986, 18));
        menudfA = new QMenu(menubar);
        menudfA->setObjectName(QStringLiteral("menudfA"));
        menuOSG = new QMenu(menudfA);
        menuOSG->setObjectName(QStringLiteral("menuOSG"));
        InducedPolarization->setMenuBar(menubar);
        statusbar = new QStatusBar(InducedPolarization);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        InducedPolarization->setStatusBar(statusbar);

        menubar->addAction(menudfA->menuAction());
        menudfA->addAction(menuOSG->menuAction());
        menudfA->addSeparator();
        menudfA->addAction(action22);
        menuOSG->addAction(action_openOSGFile1);
        menuOSG->addSeparator();
        menuOSG->addAction(action_openOSGFile2);

        retranslateUi(InducedPolarization);
        QObject::connect(action_openOSGFile1, SIGNAL(triggered()), InducedPolarization, SLOT(openOSGFile1()));
        QObject::connect(action_openOSGFile2, SIGNAL(triggered()), InducedPolarization, SLOT(openOSGFile2()));

        QMetaObject::connectSlotsByName(InducedPolarization);
    } // setupUi

    void retranslateUi(QMainWindow *InducedPolarization)
    {
        InducedPolarization->setWindowTitle(QApplication::translate("InducedPolarization", "MainWindow", Q_NULLPTR));
        action22->setText(QApplication::translate("InducedPolarization", "\350\247\202\346\265\213\347\263\273\347\273\237", Q_NULLPTR));
        action_openOSGFile1->setText(QApplication::translate("InducedPolarization", "\346\226\207\344\273\2661", Q_NULLPTR));
        action_openOSGFile2->setText(QApplication::translate("InducedPolarization", "\346\226\207\344\273\2662", Q_NULLPTR));
        menudfA->setTitle(QApplication::translate("InducedPolarization", "\346\226\207\344\273\266", Q_NULLPTR));
        menuOSG->setTitle(QApplication::translate("InducedPolarization", "OSG\346\226\207\344\273\266", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class InducedPolarization: public Ui_InducedPolarization {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INDUCEDPOLARIZATION_H
