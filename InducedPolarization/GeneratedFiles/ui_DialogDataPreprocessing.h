/********************************************************************************
** Form generated from reading UI file 'DialogDataPreprocessing.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGDATAPREPROCESSING_H
#define UI_DIALOGDATAPREPROCESSING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MyPushButtonH.h"
#include "MyPushButtonV.h"
#include "MyTableWidgetRemoveBadPoints.h"
#include "dataPreProcess/dataPreProcess.h"

QT_BEGIN_NAMESPACE

class Ui_DialogDataPreprocessing
{
public:
    QHBoxLayout *horizontalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tabRemovePoint;
    QVBoxLayout *verticalLayout;
    MyTableWidgetRemoveBadPoints *tableWidgetRemovePoint;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_measuring_edit;
    QPushButton *pushButton_measuring_update;
    QWidget *tabDataExtraction;
    QHBoxLayout *horizontalLayout_3;
    QTableWidget *tableWidgetDataExtraction;
    QWidget *tabMeasuringPoints;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    MyPushButtonV *pushButton_V;
    DataPreprocess *tableWidget_2;
    MyPushButtonH *pushButton_H;

    void setupUi(QDialog *DialogDataPreprocessing)
    {
        if (DialogDataPreprocessing->objectName().isEmpty())
            DialogDataPreprocessing->setObjectName(QStringLiteral("DialogDataPreprocessing"));
        DialogDataPreprocessing->resize(948, 684);
        DialogDataPreprocessing->setMinimumSize(QSize(0, 260));
        horizontalLayout_2 = new QHBoxLayout(DialogDataPreprocessing);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(DialogDataPreprocessing);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabRemovePoint = new QWidget();
        tabRemovePoint->setObjectName(QStringLiteral("tabRemovePoint"));
        verticalLayout = new QVBoxLayout(tabRemovePoint);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tableWidgetRemovePoint = new MyTableWidgetRemoveBadPoints(tabRemovePoint);
        tableWidgetRemovePoint->setObjectName(QStringLiteral("tableWidgetRemovePoint"));

        verticalLayout->addWidget(tableWidgetRemovePoint);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);

        pushButton_measuring_edit = new QPushButton(tabRemovePoint);
        pushButton_measuring_edit->setObjectName(QStringLiteral("pushButton_measuring_edit"));

        horizontalLayout_8->addWidget(pushButton_measuring_edit);

        pushButton_measuring_update = new QPushButton(tabRemovePoint);
        pushButton_measuring_update->setObjectName(QStringLiteral("pushButton_measuring_update"));
        pushButton_measuring_update->setEnabled(false);

        horizontalLayout_8->addWidget(pushButton_measuring_update);


        verticalLayout->addLayout(horizontalLayout_8);

        verticalLayout->setStretch(0, 100);
        verticalLayout->setStretch(1, 1);
        tabWidget->addTab(tabRemovePoint, QString());
        tabDataExtraction = new QWidget();
        tabDataExtraction->setObjectName(QStringLiteral("tabDataExtraction"));
        horizontalLayout_3 = new QHBoxLayout(tabDataExtraction);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        tableWidgetDataExtraction = new QTableWidget(tabDataExtraction);
        tableWidgetDataExtraction->setObjectName(QStringLiteral("tableWidgetDataExtraction"));
        tableWidgetDataExtraction->setEditTriggers(QAbstractItemView::NoEditTriggers);

        horizontalLayout_3->addWidget(tableWidgetDataExtraction);

        tabWidget->addTab(tabDataExtraction, QString());
        tabMeasuringPoints = new QWidget();
        tabMeasuringPoints->setObjectName(QStringLiteral("tabMeasuringPoints"));
        verticalLayout_4 = new QVBoxLayout(tabMeasuringPoints);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_V = new MyPushButtonV(tabMeasuringPoints);
        pushButton_V->setObjectName(QStringLiteral("pushButton_V"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_V->sizePolicy().hasHeightForWidth());
        pushButton_V->setSizePolicy(sizePolicy);
        pushButton_V->setStyleSheet(QStringLiteral("border:none;background-color: rgb(232, 232, 232);"));

        horizontalLayout->addWidget(pushButton_V);

        tableWidget_2 = new DataPreprocess(tabMeasuringPoints);
        tableWidget_2->setObjectName(QStringLiteral("tableWidget_2"));
        tableWidget_2->setStyleSheet(QStringLiteral("border:none"));

        horizontalLayout->addWidget(tableWidget_2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 100);

        verticalLayout_3->addLayout(horizontalLayout);

        pushButton_H = new MyPushButtonH(tabMeasuringPoints);
        pushButton_H->setObjectName(QStringLiteral("pushButton_H"));
        sizePolicy.setHeightForWidth(pushButton_H->sizePolicy().hasHeightForWidth());
        pushButton_H->setSizePolicy(sizePolicy);
        pushButton_H->setStyleSheet(QLatin1String("border:none;\n"
"background-color: rgb(232, 232, 232);"));
        pushButton_H->setFlat(false);

        verticalLayout_3->addWidget(pushButton_H);

        verticalLayout_3->setStretch(0, 100);
        verticalLayout_3->setStretch(1, 1);

        verticalLayout_4->addLayout(verticalLayout_3);

        tabWidget->addTab(tabMeasuringPoints, QString());

        horizontalLayout_2->addWidget(tabWidget);


        retranslateUi(DialogDataPreprocessing);
        QObject::connect(pushButton_measuring_edit, SIGNAL(clicked()), DialogDataPreprocessing, SLOT(onSupplyEditClick()));
        QObject::connect(pushButton_measuring_update, SIGNAL(clicked()), DialogDataPreprocessing, SLOT(onSupplyUpdateClick()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DialogDataPreprocessing);
    } // setupUi

    void retranslateUi(QDialog *DialogDataPreprocessing)
    {
        DialogDataPreprocessing->setWindowTitle(QApplication::translate("DialogDataPreprocessing", "\346\225\260\346\215\256\351\242\204\345\244\204\347\220\206", Q_NULLPTR));
        pushButton_measuring_edit->setText(QApplication::translate("DialogDataPreprocessing", "\347\274\226\350\276\221", Q_NULLPTR));
        pushButton_measuring_update->setText(QApplication::translate("DialogDataPreprocessing", "\346\233\264\346\226\260", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabRemovePoint), QApplication::translate("DialogDataPreprocessing", "\345\235\217\347\202\271\345\211\224\351\231\244", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabDataExtraction), QApplication::translate("DialogDataPreprocessing", "\350\247\202\346\265\213\346\225\260\346\215\256\346\217\220\345\217\226", Q_NULLPTR));
        pushButton_V->setText(QString());
        pushButton_H->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabMeasuringPoints), QApplication::translate("DialogDataPreprocessing", "\350\247\202\346\265\213\346\225\260\346\215\256\350\260\203\346\225\264", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogDataPreprocessing: public Ui_DialogDataPreprocessing {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGDATAPREPROCESSING_H
