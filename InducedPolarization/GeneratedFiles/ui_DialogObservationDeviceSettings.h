/********************************************************************************
** Form generated from reading UI file 'DialogObservationDeviceSettings.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGOBSERVATIONDEVICESETTINGS_H
#define UI_DIALOGOBSERVATIONDEVICESETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
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
#include "DetectObserv/detectobserver.h"
#include "MyTableWidget.h"

QT_BEGIN_NAMESPACE

class Ui_DialogObservationDevice
{
public:
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tabObservationDevice;
    QHBoxLayout *horizontalLayout_15;
    QHBoxLayout *horizontalLayout_14;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEditFaceX;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QLineEdit *lineEditFaceY;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_7;
    QLineEdit *lineEditFaceZ;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_11;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEditFaceWidth;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEditFaceHeight;
    QSpacerItem *verticalSpacer_3;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_8;
    QLineEdit *lineEditMileageNum;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_15;
    QComboBox *comboBox_ExcavationDir;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_14;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *update_param;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_6;
    QWidget *tabPowerSupply;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_7;
    MyTableWidget *tableWidgetSupply;
    MyTableWidget *tableWidgetNew;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_supply_edit;
    QPushButton *pushButton_supply_update;
    QWidget *tabMeasuringPoints;
    QVBoxLayout *verticalLayout_7;
    MyTableWidget *tableWidgetMeasuring;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_measuring_edit;
    QPushButton *pushButton_measuring_update;
    QWidget *tabElectrode;
    QVBoxLayout *verticalLayout_8;
    DetectObserver *widget_device;
    QLabel *label_text;
    QWidget *widget_selectBox_2;
    QVBoxLayout *verticalLayout_27;
    QRadioButton *radioButton_tunnelEntity_2;
    QRadioButton *radioButton_tunnelGrid_3;

    void setupUi(QDialog *DialogObservationDevice)
    {
        if (DialogObservationDevice->objectName().isEmpty())
            DialogObservationDevice->setObjectName(QStringLiteral("DialogObservationDevice"));
        DialogObservationDevice->resize(899, 750);
        DialogObservationDevice->setMinimumSize(QSize(380, 0));
        verticalLayout_2 = new QVBoxLayout(DialogObservationDevice);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tabWidget = new QTabWidget(DialogObservationDevice);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabObservationDevice = new QWidget();
        tabObservationDevice->setObjectName(QStringLiteral("tabObservationDevice"));
        horizontalLayout_15 = new QHBoxLayout(tabObservationDevice);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_5);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        groupBox = new QGroupBox(tabObservationDevice);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        lineEditFaceX = new QLineEdit(groupBox_3);
        lineEditFaceX->setObjectName(QStringLiteral("lineEditFaceX"));

        horizontalLayout_3->addWidget(lineEditFaceX);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 4);

        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_4->addWidget(label_6);

        lineEditFaceY = new QLineEdit(groupBox_3);
        lineEditFaceY->setObjectName(QStringLiteral("lineEditFaceY"));

        horizontalLayout_4->addWidget(lineEditFaceY);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 4);

        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_5->addWidget(label_7);

        lineEditFaceZ = new QLineEdit(groupBox_3);
        lineEditFaceZ->setObjectName(QStringLiteral("lineEditFaceZ"));

        horizontalLayout_5->addWidget(lineEditFaceZ);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 4);

        verticalLayout_3->addLayout(horizontalLayout_5);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 1);
        verticalLayout_3->setStretch(2, 1);

        gridLayout_2->addWidget(groupBox_3, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_11 = new QHBoxLayout(groupBox_2);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        lineEditFaceWidth = new QLineEdit(groupBox_2);
        lineEditFaceWidth->setObjectName(QStringLiteral("lineEditFaceWidth"));

        horizontalLayout_2->addWidget(lineEditFaceWidth);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 3);

        horizontalLayout_11->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEditFaceHeight = new QLineEdit(groupBox_2);
        lineEditFaceHeight->setObjectName(QStringLiteral("lineEditFaceHeight"));

        horizontalLayout->addWidget(lineEditFaceHeight);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 3);

        horizontalLayout_11->addLayout(horizontalLayout);

        horizontalLayout_11->setStretch(0, 1);
        horizontalLayout_11->setStretch(1, 1);

        gridLayout_2->addWidget(groupBox_2, 0, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 2, 0, 1, 1);


        verticalLayout_4->addWidget(groupBox);

        groupBox_5 = new QGroupBox(tabObservationDevice);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        gridLayout_5 = new QGridLayout(groupBox_5);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_8 = new QLabel(groupBox_5);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_12->addWidget(label_8);

        lineEditMileageNum = new QLineEdit(groupBox_5);
        lineEditMileageNum->setObjectName(QStringLiteral("lineEditMileageNum"));

        horizontalLayout_12->addWidget(lineEditMileageNum);

        horizontalLayout_12->setStretch(0, 1);
        horizontalLayout_12->setStretch(1, 4);

        gridLayout_5->addLayout(horizontalLayout_12, 0, 0, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_15 = new QLabel(groupBox_5);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_13->addWidget(label_15);

        comboBox_ExcavationDir = new QComboBox(groupBox_5);
        comboBox_ExcavationDir->setObjectName(QStringLiteral("comboBox_ExcavationDir"));

        horizontalLayout_13->addWidget(comboBox_ExcavationDir);

        horizontalLayout_13->setStretch(0, 3);
        horizontalLayout_13->setStretch(1, 7);

        gridLayout_5->addLayout(horizontalLayout_13, 1, 0, 1, 1);


        verticalLayout_4->addWidget(groupBox_5);

        groupBox_4 = new QGroupBox(tabObservationDevice);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        verticalLayout = new QVBoxLayout(groupBox_4);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_9->addWidget(label_14);

        comboBox = new QComboBox(groupBox_4);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_9->addWidget(comboBox);

        horizontalLayout_9->setStretch(0, 4);
        horizontalLayout_9->setStretch(1, 6);

        verticalLayout->addLayout(horizontalLayout_9);


        verticalLayout_4->addWidget(groupBox_4);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_3);

        update_param = new QPushButton(tabObservationDevice);
        update_param->setObjectName(QStringLiteral("update_param"));

        horizontalLayout_10->addWidget(update_param);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_4);


        verticalLayout_4->addLayout(horizontalLayout_10);

        verticalLayout_4->setStretch(0, 1);
        verticalLayout_4->setStretch(1, 1);
        verticalLayout_4->setStretch(2, 1);
        verticalLayout_4->setStretch(3, 1);

        verticalLayout_5->addLayout(verticalLayout_4);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        verticalLayout_5->setStretch(0, 2);
        verticalLayout_5->setStretch(1, 50);
        verticalLayout_5->setStretch(2, 10);

        horizontalLayout_14->addLayout(verticalLayout_5);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_6);


        horizontalLayout_15->addLayout(horizontalLayout_14);

        tabWidget->addTab(tabObservationDevice, QString());
        tabPowerSupply = new QWidget();
        tabPowerSupply->setObjectName(QStringLiteral("tabPowerSupply"));
        verticalLayout_6 = new QVBoxLayout(tabPowerSupply);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(2);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        tableWidgetSupply = new MyTableWidget(tabPowerSupply);
        tableWidgetSupply->setObjectName(QStringLiteral("tableWidgetSupply"));

        horizontalLayout_7->addWidget(tableWidgetSupply);

        tableWidgetNew = new MyTableWidget(tabPowerSupply);
        tableWidgetNew->setObjectName(QStringLiteral("tableWidgetNew"));

        horizontalLayout_7->addWidget(tableWidgetNew);

        horizontalLayout_7->setStretch(0, 1);
        horizontalLayout_7->setStretch(1, 1);

        verticalLayout_6->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        pushButton_supply_edit = new QPushButton(tabPowerSupply);
        pushButton_supply_edit->setObjectName(QStringLiteral("pushButton_supply_edit"));

        horizontalLayout_6->addWidget(pushButton_supply_edit);

        pushButton_supply_update = new QPushButton(tabPowerSupply);
        pushButton_supply_update->setObjectName(QStringLiteral("pushButton_supply_update"));

        horizontalLayout_6->addWidget(pushButton_supply_update);


        verticalLayout_6->addLayout(horizontalLayout_6);

        verticalLayout_6->setStretch(0, 100);
        verticalLayout_6->setStretch(1, 1);
        tabWidget->addTab(tabPowerSupply, QString());
        tabMeasuringPoints = new QWidget();
        tabMeasuringPoints->setObjectName(QStringLiteral("tabMeasuringPoints"));
        verticalLayout_7 = new QVBoxLayout(tabMeasuringPoints);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        tableWidgetMeasuring = new MyTableWidget(tabMeasuringPoints);
        tableWidgetMeasuring->setObjectName(QStringLiteral("tableWidgetMeasuring"));

        verticalLayout_7->addWidget(tableWidgetMeasuring);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);

        pushButton_measuring_edit = new QPushButton(tabMeasuringPoints);
        pushButton_measuring_edit->setObjectName(QStringLiteral("pushButton_measuring_edit"));

        horizontalLayout_8->addWidget(pushButton_measuring_edit);

        pushButton_measuring_update = new QPushButton(tabMeasuringPoints);
        pushButton_measuring_update->setObjectName(QStringLiteral("pushButton_measuring_update"));

        horizontalLayout_8->addWidget(pushButton_measuring_update);


        verticalLayout_7->addLayout(horizontalLayout_8);

        verticalLayout_7->setStretch(0, 100);
        verticalLayout_7->setStretch(1, 1);
        tabWidget->addTab(tabMeasuringPoints, QString());
        tabElectrode = new QWidget();
        tabElectrode->setObjectName(QStringLiteral("tabElectrode"));
        verticalLayout_8 = new QVBoxLayout(tabElectrode);
        verticalLayout_8->setSpacing(0);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        widget_device = new DetectObserver(tabElectrode);
        widget_device->setObjectName(QStringLiteral("widget_device"));
        label_text = new QLabel(widget_device);
        label_text->setObjectName(QStringLiteral("label_text"));
        label_text->setGeometry(QRect(750, 10, 101, 61));
        label_text->setStyleSheet(QLatin1String("font: 10pt \"Arial Rounded MT Bold\";\n"
"color: rgb(225, 225, 225);\n"
"background-color: rgba(130, 150, 170, 100%);\n"
""));
        widget_selectBox_2 = new QWidget(widget_device);
        widget_selectBox_2->setObjectName(QStringLiteral("widget_selectBox_2"));
        widget_selectBox_2->setGeometry(QRect(10, 10, 101, 51));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(130, 150, 170, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(195, 225, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(162, 187, 212, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(65, 75, 85, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(87, 100, 113, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush7(QColor(192, 202, 212, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        QBrush brush8(QColor(255, 255, 220, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        widget_selectBox_2->setPalette(palette);
        widget_selectBox_2->setStyleSheet(QStringLiteral("background-color: rgba(130, 150, 170, 100%);"));
        verticalLayout_27 = new QVBoxLayout(widget_selectBox_2);
        verticalLayout_27->setSpacing(0);
        verticalLayout_27->setObjectName(QStringLiteral("verticalLayout_27"));
        verticalLayout_27->setContentsMargins(0, 0, 0, 0);
        radioButton_tunnelEntity_2 = new QRadioButton(widget_selectBox_2);
        radioButton_tunnelEntity_2->setObjectName(QStringLiteral("radioButton_tunnelEntity_2"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(radioButton_tunnelEntity_2->sizePolicy().hasHeightForWidth());
        radioButton_tunnelEntity_2->setSizePolicy(sizePolicy);

        verticalLayout_27->addWidget(radioButton_tunnelEntity_2);

        radioButton_tunnelGrid_3 = new QRadioButton(widget_selectBox_2);
        radioButton_tunnelGrid_3->setObjectName(QStringLiteral("radioButton_tunnelGrid_3"));
        sizePolicy.setHeightForWidth(radioButton_tunnelGrid_3->sizePolicy().hasHeightForWidth());
        radioButton_tunnelGrid_3->setSizePolicy(sizePolicy);
        radioButton_tunnelGrid_3->setChecked(false);

        verticalLayout_27->addWidget(radioButton_tunnelGrid_3);


        verticalLayout_8->addWidget(widget_device);

        tabWidget->addTab(tabElectrode, QString());

        verticalLayout_2->addWidget(tabWidget);


        retranslateUi(DialogObservationDevice);
        QObject::connect(radioButton_tunnelEntity_2, SIGNAL(toggled(bool)), widget_device, SLOT(setTunnelEntity(bool)));
        QObject::connect(radioButton_tunnelGrid_3, SIGNAL(toggled(bool)), widget_device, SLOT(setTunnelView(bool)));

        tabWidget->setCurrentIndex(0);
        comboBox_ExcavationDir->setCurrentIndex(0);
        comboBox->setCurrentIndex(11);


        QMetaObject::connectSlotsByName(DialogObservationDevice);
    } // setupUi

    void retranslateUi(QDialog *DialogObservationDevice)
    {
        DialogObservationDevice->setWindowTitle(QApplication::translate("DialogObservationDevice", "\350\247\202\346\265\213\350\243\205\347\275\256\350\256\276\347\275\256", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("DialogObservationDevice", "\345\217\202\346\225\260\350\256\276\345\256\232", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("DialogObservationDevice", "\346\216\214\345\255\220\351\235\242\344\270\255\345\277\203\344\275\215\347\275\256", Q_NULLPTR));
        label_3->setText(QApplication::translate("DialogObservationDevice", "X\345\235\220\346\240\207:", Q_NULLPTR));
        label_6->setText(QApplication::translate("DialogObservationDevice", "Y\345\235\220\346\240\207:", Q_NULLPTR));
        label_7->setText(QApplication::translate("DialogObservationDevice", "Z\345\235\220\346\240\207:", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("DialogObservationDevice", "\346\216\214\345\255\220\351\235\242\345\244\247\345\260\217", Q_NULLPTR));
        label->setText(QApplication::translate("DialogObservationDevice", "\345\256\275:", Q_NULLPTR));
        label_2->setText(QApplication::translate("DialogObservationDevice", "\351\253\230:", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("DialogObservationDevice", "\351\207\214\347\250\213\345\217\267\350\256\276\347\275\256", Q_NULLPTR));
        label_8->setText(QApplication::translate("DialogObservationDevice", "\351\207\214\347\250\213\345\217\267:", Q_NULLPTR));
        label_15->setText(QApplication::translate("DialogObservationDevice", "\346\216\230\350\277\233\346\226\271\345\220\221:", Q_NULLPTR));
        comboBox_ExcavationDir->clear();
        comboBox_ExcavationDir->insertItems(0, QStringList()
         << QApplication::translate("DialogObservationDevice", "\345\244\247\344\272\216\351\207\214\347\250\213\345\217\267", Q_NULLPTR)
         << QApplication::translate("DialogObservationDevice", "\345\260\217\344\272\216\351\207\214\347\250\213\345\217\267", Q_NULLPTR)
        );
        comboBox_ExcavationDir->setCurrentText(QApplication::translate("DialogObservationDevice", "\345\244\247\344\272\216\351\207\214\347\250\213\345\217\267", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("DialogObservationDevice", "\350\243\205\347\275\256\347\261\273\345\236\213", Q_NULLPTR));
        label_14->setText(QApplication::translate("DialogObservationDevice", " \350\243\205\347\275\256\347\261\273\345\236\213:", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogObservationDevice", "\350\243\205\347\275\2561", Q_NULLPTR)
         << QApplication::translate("DialogObservationDevice", "\350\243\205\347\275\2562", Q_NULLPTR)
         << QApplication::translate("DialogObservationDevice", "\350\243\205\347\275\2563", Q_NULLPTR)
         << QApplication::translate("DialogObservationDevice", "\350\243\205\347\275\2564", Q_NULLPTR)
         << QApplication::translate("DialogObservationDevice", "\350\243\205\347\275\2565", Q_NULLPTR)
         << QApplication::translate("DialogObservationDevice", "\350\243\205\347\275\2566", Q_NULLPTR)
         << QApplication::translate("DialogObservationDevice", "\350\243\205\347\275\2567", Q_NULLPTR)
         << QApplication::translate("DialogObservationDevice", "\350\243\205\347\275\2568", Q_NULLPTR)
         << QApplication::translate("DialogObservationDevice", "\350\243\205\347\275\2569", Q_NULLPTR)
         << QApplication::translate("DialogObservationDevice", "\350\243\205\347\275\25610", Q_NULLPTR)
         << QApplication::translate("DialogObservationDevice", "ESCAN", Q_NULLPTR)
         << QApplication::translate("DialogObservationDevice", "\350\201\232\347\204\246\346\265\213\346\267\261", Q_NULLPTR)
        );
        comboBox->setCurrentText(QApplication::translate("DialogObservationDevice", "\350\201\232\347\204\246\346\265\213\346\267\261", Q_NULLPTR));
        update_param->setText(QApplication::translate("DialogObservationDevice", "\346\233\264\346\226\260", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabObservationDevice), QApplication::translate("DialogObservationDevice", "\350\247\202\346\265\213\350\243\205\347\275\256", Q_NULLPTR));
        pushButton_supply_edit->setText(QApplication::translate("DialogObservationDevice", "\347\274\226\350\276\221", Q_NULLPTR));
        pushButton_supply_update->setText(QApplication::translate("DialogObservationDevice", "\346\233\264\346\226\260", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabPowerSupply), QApplication::translate("DialogObservationDevice", "\344\276\233\347\224\265\347\202\271\344\275\215\347\275\256", Q_NULLPTR));
        pushButton_measuring_edit->setText(QApplication::translate("DialogObservationDevice", "\347\274\226\350\276\221", Q_NULLPTR));
        pushButton_measuring_update->setText(QApplication::translate("DialogObservationDevice", "\346\233\264\346\226\260", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabMeasuringPoints), QApplication::translate("DialogObservationDevice", "\346\265\213\351\207\217\347\202\271\344\275\215\347\275\256", Q_NULLPTR));
        label_text->setText(QApplication::translate("DialogObservationDevice", "X \357\274\232 \351\232\247\351\201\223\351\253\230\345\272\246\n"
"Y \357\274\232 \351\232\247\351\201\223\345\256\275\345\272\246\n"
"Z \357\274\232 \351\232\247\351\201\223\347\272\265\346\267\261", Q_NULLPTR));
        radioButton_tunnelEntity_2->setText(QApplication::translate("DialogObservationDevice", "\351\232\247\351\201\223\347\272\265\345\220\221\346\274\253\346\270\270", Q_NULLPTR));
        radioButton_tunnelGrid_3->setText(QApplication::translate("DialogObservationDevice", "\351\232\247\351\201\223360\345\272\246\346\274\253\346\270\270", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabElectrode), QApplication::translate("DialogObservationDevice", "\347\224\265\346\236\201\344\275\215\347\275\256\347\244\272\346\204\217\345\233\276", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogObservationDevice: public Ui_DialogObservationDevice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGOBSERVATIONDEVICESETTINGS_H
