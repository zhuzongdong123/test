/********************************************************************************
** Form generated from reading UI file 'DialogModeling.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGMODELING_H
#define UI_DIALOGMODELING_H

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
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "ModelingSubdivision.h"
#include "MyTableWidget.h"

QT_BEGIN_NAMESPACE

class Ui_DialogModeling
{
public:
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    ModelingSubdivision *widget;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *radioButton_body;
    QRadioButton *radioButton_point;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    MyTableWidget *tableWidget_modelData;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *lineEdit_invert_begin_x;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *lineEdit_invert_end_x;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLineEdit *lineEdit_invert_begin_y;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QLineEdit *lineEdit_invert_end_y;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_5;
    QLineEdit *lineEdit_TunnelCavityXBegin;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_6;
    QLineEdit *lineEdit_TunnelCavityXEnd;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_7;
    QLineEdit *lineEdit_TunnelCavityYBegin;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_8;
    QLineEdit *lineEdit_TunnelCavityYEnd;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_9;
    QLineEdit *lineEdit_invert_begin_z;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_10;
    QLineEdit *lineEdit_invert_end_z;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_11;
    QLineEdit *lineEdit_MeasuringElectrode_begin_x;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_12;
    QLineEdit *lineEdit_MeasuringElectrode_end_x;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_13;
    QLineEdit *lineEdit_MeasuringElectrode_begin_y;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_14;
    QLineEdit *lineEdit_MeasuringElectrode_end_y;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_edit;
    QPushButton *pushButton_update;

    void setupUi(QDialog *DialogModeling)
    {
        if (DialogModeling->objectName().isEmpty())
            DialogModeling->setObjectName(QStringLiteral("DialogModeling"));
        DialogModeling->resize(938, 832);
        verticalLayout_3 = new QVBoxLayout(DialogModeling);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(DialogModeling);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new ModelingSubdivision(tab);
        widget->setObjectName(QStringLiteral("widget"));
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(830, 0, 91, 80));
        widget_2->setStyleSheet(QStringLiteral("background-color: rgb(130, 150, 170);"));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        radioButton_body = new QRadioButton(widget_2);
        radioButton_body->setObjectName(QStringLiteral("radioButton_body"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(radioButton_body->sizePolicy().hasHeightForWidth());
        radioButton_body->setSizePolicy(sizePolicy);
        radioButton_body->setChecked(true);

        verticalLayout_2->addWidget(radioButton_body);

        radioButton_point = new QRadioButton(widget_2);
        radioButton_point->setObjectName(QStringLiteral("radioButton_point"));
        sizePolicy.setHeightForWidth(radioButton_point->sizePolicy().hasHeightForWidth());
        radioButton_point->setSizePolicy(sizePolicy);
        radioButton_point->setChecked(false);

        verticalLayout_2->addWidget(radioButton_point);


        verticalLayout->addWidget(widget);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_6 = new QVBoxLayout(tab_2);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        tableWidget_modelData = new MyTableWidget(tab_2);
        tableWidget_modelData->setObjectName(QStringLiteral("tableWidget_modelData"));

        horizontalLayout_2->addWidget(tableWidget_modelData);

        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        lineEdit_invert_begin_x = new QLineEdit(groupBox);
        lineEdit_invert_begin_x->setObjectName(QStringLiteral("lineEdit_invert_begin_x"));

        horizontalLayout_3->addWidget(lineEdit_invert_begin_x);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        lineEdit_invert_end_x = new QLineEdit(groupBox);
        lineEdit_invert_end_x->setObjectName(QStringLiteral("lineEdit_invert_end_x"));

        horizontalLayout_4->addWidget(lineEdit_invert_end_x);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_5->addWidget(label_3);

        lineEdit_invert_begin_y = new QLineEdit(groupBox);
        lineEdit_invert_begin_y->setObjectName(QStringLiteral("lineEdit_invert_begin_y"));

        horizontalLayout_5->addWidget(lineEdit_invert_begin_y);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_6->addWidget(label_4);

        lineEdit_invert_end_y = new QLineEdit(groupBox);
        lineEdit_invert_end_y->setObjectName(QStringLiteral("lineEdit_invert_end_y"));

        horizontalLayout_6->addWidget(lineEdit_invert_end_y);


        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_7->addWidget(label_5);

        lineEdit_TunnelCavityXBegin = new QLineEdit(groupBox);
        lineEdit_TunnelCavityXBegin->setObjectName(QStringLiteral("lineEdit_TunnelCavityXBegin"));

        horizontalLayout_7->addWidget(lineEdit_TunnelCavityXBegin);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_8->addWidget(label_6);

        lineEdit_TunnelCavityXEnd = new QLineEdit(groupBox);
        lineEdit_TunnelCavityXEnd->setObjectName(QStringLiteral("lineEdit_TunnelCavityXEnd"));

        horizontalLayout_8->addWidget(lineEdit_TunnelCavityXEnd);


        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_9->addWidget(label_7);

        lineEdit_TunnelCavityYBegin = new QLineEdit(groupBox);
        lineEdit_TunnelCavityYBegin->setObjectName(QStringLiteral("lineEdit_TunnelCavityYBegin"));

        horizontalLayout_9->addWidget(lineEdit_TunnelCavityYBegin);


        verticalLayout_4->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_10->addWidget(label_8);

        lineEdit_TunnelCavityYEnd = new QLineEdit(groupBox);
        lineEdit_TunnelCavityYEnd->setObjectName(QStringLiteral("lineEdit_TunnelCavityYEnd"));

        horizontalLayout_10->addWidget(lineEdit_TunnelCavityYEnd);


        verticalLayout_4->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_11->addWidget(label_9);

        lineEdit_invert_begin_z = new QLineEdit(groupBox);
        lineEdit_invert_begin_z->setObjectName(QStringLiteral("lineEdit_invert_begin_z"));

        horizontalLayout_11->addWidget(lineEdit_invert_begin_z);


        verticalLayout_4->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_12->addWidget(label_10);

        lineEdit_invert_end_z = new QLineEdit(groupBox);
        lineEdit_invert_end_z->setObjectName(QStringLiteral("lineEdit_invert_end_z"));

        horizontalLayout_12->addWidget(lineEdit_invert_end_z);


        verticalLayout_4->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_13->addWidget(label_11);

        lineEdit_MeasuringElectrode_begin_x = new QLineEdit(groupBox);
        lineEdit_MeasuringElectrode_begin_x->setObjectName(QStringLiteral("lineEdit_MeasuringElectrode_begin_x"));

        horizontalLayout_13->addWidget(lineEdit_MeasuringElectrode_begin_x);


        verticalLayout_4->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_14->addWidget(label_12);

        lineEdit_MeasuringElectrode_end_x = new QLineEdit(groupBox);
        lineEdit_MeasuringElectrode_end_x->setObjectName(QStringLiteral("lineEdit_MeasuringElectrode_end_x"));

        horizontalLayout_14->addWidget(lineEdit_MeasuringElectrode_end_x);


        verticalLayout_4->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_15->addWidget(label_13);

        lineEdit_MeasuringElectrode_begin_y = new QLineEdit(groupBox);
        lineEdit_MeasuringElectrode_begin_y->setObjectName(QStringLiteral("lineEdit_MeasuringElectrode_begin_y"));

        horizontalLayout_15->addWidget(lineEdit_MeasuringElectrode_begin_y);


        verticalLayout_4->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_16->addWidget(label_14);

        lineEdit_MeasuringElectrode_end_y = new QLineEdit(groupBox);
        lineEdit_MeasuringElectrode_end_y->setObjectName(QStringLiteral("lineEdit_MeasuringElectrode_end_y"));

        horizontalLayout_16->addWidget(lineEdit_MeasuringElectrode_end_y);


        verticalLayout_4->addLayout(horizontalLayout_16);


        horizontalLayout_2->addWidget(groupBox);

        horizontalLayout_2->setStretch(0, 2);
        horizontalLayout_2->setStretch(1, 1);

        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_edit = new QPushButton(tab_2);
        pushButton_edit->setObjectName(QStringLiteral("pushButton_edit"));

        horizontalLayout->addWidget(pushButton_edit);

        pushButton_update = new QPushButton(tab_2);
        pushButton_update->setObjectName(QStringLiteral("pushButton_update"));

        horizontalLayout->addWidget(pushButton_update);

        horizontalLayout->setStretch(0, 100);
        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(2, 1);

        verticalLayout_5->addLayout(horizontalLayout);


        verticalLayout_6->addLayout(verticalLayout_5);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_3->addWidget(tabWidget);


        retranslateUi(DialogModeling);
        QObject::connect(radioButton_body, SIGNAL(clicked()), widget, SLOT(modelSubBodyDisplay()));
        QObject::connect(radioButton_point, SIGNAL(clicked()), widget, SLOT(modelSubBodyHidden()));
        QObject::connect(pushButton_update, SIGNAL(clicked()), DialogModeling, SLOT(updateData()));
        QObject::connect(pushButton_edit, SIGNAL(clicked()), DialogModeling, SLOT(editData()));
        QObject::connect(lineEdit_invert_begin_z, SIGNAL(textChanged(QString)), DialogModeling, SLOT(invertBeginZTextChanged(QString)));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DialogModeling);
    } // setupUi

    void retranslateUi(QDialog *DialogModeling)
    {
        DialogModeling->setWindowTitle(QApplication::translate("DialogModeling", "\345\273\272\346\250\241", Q_NULLPTR));
        radioButton_body->setText(QApplication::translate("DialogModeling", "\345\211\226\345\210\206\344\275\223", Q_NULLPTR));
        radioButton_point->setText(QApplication::translate("DialogModeling", "\345\211\226\345\210\206\347\275\221\346\240\274", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("DialogModeling", "\346\250\241\345\236\213\346\230\276\347\244\272", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("DialogModeling", "\345\273\272\346\250\241\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        label->setText(QApplication::translate("DialogModeling", "\345\217\215\346\274\224\345\214\272\345\237\237X\350\265\267\347\202\271\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("DialogModeling", "\345\217\215\346\274\224\345\214\272\345\237\237X\347\273\210\347\202\271\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("DialogModeling", "\345\217\215\346\274\224\345\214\272\345\237\237Y\350\265\267\347\202\271\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("DialogModeling", "\345\217\215\346\274\224\345\214\272\345\237\237Y\347\273\210\347\202\271\357\274\232", Q_NULLPTR));
        label_5->setText(QApplication::translate("DialogModeling", "\351\232\247\351\201\223\347\251\272\350\205\224X\350\265\267\347\202\271\357\274\232", Q_NULLPTR));
        label_6->setText(QApplication::translate("DialogModeling", "\351\232\247\351\201\223\347\251\272\350\205\224X\347\273\210\347\202\271\357\274\232", Q_NULLPTR));
        label_7->setText(QApplication::translate("DialogModeling", "\351\232\247\351\201\223\347\251\272\350\205\224Y\350\265\267\347\202\271\357\274\232", Q_NULLPTR));
        label_8->setText(QApplication::translate("DialogModeling", "\351\232\247\351\201\223\347\251\272\350\205\224Y\347\273\210\347\202\271\357\274\232", Q_NULLPTR));
        label_9->setText(QApplication::translate("DialogModeling", "\351\242\204\346\265\213\345\214\272\345\237\237Z\350\265\267\347\202\271\357\274\232", Q_NULLPTR));
        label_10->setText(QApplication::translate("DialogModeling", "\351\242\204\346\265\213\345\214\272\345\237\237Z\347\273\210\347\202\271\357\274\232", Q_NULLPTR));
        label_11->setText(QApplication::translate("DialogModeling", "\346\265\213\351\207\217\347\224\265\346\236\201X\350\265\267\347\202\271\357\274\232", Q_NULLPTR));
        label_12->setText(QApplication::translate("DialogModeling", "\346\265\213\351\207\217\347\224\265\346\236\201X\347\273\210\347\202\271\357\274\232", Q_NULLPTR));
        label_13->setText(QApplication::translate("DialogModeling", "\346\265\213\351\207\217\347\224\265\346\236\201Y\350\265\267\347\202\271\357\274\232", Q_NULLPTR));
        label_14->setText(QApplication::translate("DialogModeling", "\346\265\213\351\207\217\347\224\265\346\236\201Y\347\273\210\347\202\271\357\274\232", Q_NULLPTR));
        pushButton_edit->setText(QApplication::translate("DialogModeling", "\347\274\226\350\276\221", Q_NULLPTR));
        pushButton_update->setText(QApplication::translate("DialogModeling", "\346\233\264\346\226\260", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("DialogModeling", "\345\211\226\345\210\206\345\220\216\346\225\260\346\215\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogModeling: public Ui_DialogModeling {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGMODELING_H
