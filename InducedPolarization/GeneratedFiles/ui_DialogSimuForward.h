/********************************************************************************
** Form generated from reading UI file 'DialogSimuForward.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSIMUFORWARD_H
#define UI_DIALOGSIMUFORWARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogSimuForward
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label;
    QComboBox *comboBox_selectionSwitch;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLineEdit *lineEdit_sgM0Value;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_CII;
    QLineEdit *lineEdit_CII;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QLineEdit *lineEdit_II;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_9;
    QLineEdit *lineEdit_currentINumX;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_10;
    QLineEdit *lineEdit_currentINumY;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_11;
    QLineEdit *lineEdit_currentINumZ;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_17;
    QLineEdit *lineEdit_inverX1;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *lineEdit_actual_begin_x;
    QHBoxLayout *horizontalLayout_27;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_12;
    QLineEdit *lineEdit_inverX2;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_3;
    QLineEdit *lineEdit_actual_end_x;
    QHBoxLayout *horizontalLayout_26;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_13;
    QLineEdit *lineEdit_inverY1;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_4;
    QLineEdit *lineEdit_actual_begin_y;
    QHBoxLayout *horizontalLayout_25;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_14;
    QLineEdit *lineEdit_inverY2;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_7;
    QLineEdit *lineEdit_actual_end_y;
    QHBoxLayout *horizontalLayout_24;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_15;
    QLineEdit *lineEdit_inverZ1;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_8;
    QLineEdit *lineEdit_actual_begin_z;
    QHBoxLayout *horizontalLayout_23;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_18;
    QLineEdit *lineEdit_inverZ2;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_16;
    QLineEdit *lineEdit_actual_end_z;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *DialogSimuForward)
    {
        if (DialogSimuForward->objectName().isEmpty())
            DialogSimuForward->setObjectName(QStringLiteral("DialogSimuForward"));
        DialogSimuForward->resize(510, 580);
        DialogSimuForward->setMinimumSize(QSize(510, 580));
        DialogSimuForward->setMaximumSize(QSize(510, 580));
        horizontalLayout_2 = new QHBoxLayout(DialogSimuForward);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(DialogSimuForward);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setStyleSheet(QLatin1String("QGroupBox \n"
"{border: 2px solid #0000EE;\n"
" border-radius: 5px;\n"
"margin-top: 1ex;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"subcontrol-origin: margin;\n"
"subcontrol-position: top center;\n"
"padding: 0 3px;\n"
"}"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(0);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_13->addWidget(label);

        comboBox_selectionSwitch = new QComboBox(groupBox);
        comboBox_selectionSwitch->setObjectName(QStringLiteral("comboBox_selectionSwitch"));

        horizontalLayout_13->addWidget(comboBox_selectionSwitch);

        horizontalLayout_13->setStretch(0, 1);
        horizontalLayout_13->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout_13);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        lineEdit_sgM0Value = new QLineEdit(groupBox);
        lineEdit_sgM0Value->setObjectName(QStringLiteral("lineEdit_sgM0Value"));

        horizontalLayout_5->addWidget(lineEdit_sgM0Value);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_CII = new QLabel(groupBox);
        label_CII->setObjectName(QStringLiteral("label_CII"));

        horizontalLayout_8->addWidget(label_CII);

        lineEdit_CII = new QLineEdit(groupBox);
        lineEdit_CII->setObjectName(QStringLiteral("lineEdit_CII"));

        horizontalLayout_8->addWidget(lineEdit_CII);

        horizontalLayout_8->setStretch(0, 1);
        horizontalLayout_8->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_6->addWidget(label_6);

        lineEdit_II = new QLineEdit(groupBox);
        lineEdit_II->setObjectName(QStringLiteral("lineEdit_II"));

        horizontalLayout_6->addWidget(lineEdit_II);

        horizontalLayout_6->setStretch(0, 1);
        horizontalLayout_6->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(0);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_10->addWidget(label_9);

        lineEdit_currentINumX = new QLineEdit(groupBox);
        lineEdit_currentINumX->setObjectName(QStringLiteral("lineEdit_currentINumX"));

        horizontalLayout_10->addWidget(lineEdit_currentINumX);

        horizontalLayout_10->setStretch(0, 1);
        horizontalLayout_10->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(0);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_11->addWidget(label_10);

        lineEdit_currentINumY = new QLineEdit(groupBox);
        lineEdit_currentINumY->setObjectName(QStringLiteral("lineEdit_currentINumY"));

        horizontalLayout_11->addWidget(lineEdit_currentINumY);

        horizontalLayout_11->setStretch(0, 1);
        horizontalLayout_11->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(0);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_12->addWidget(label_11);

        lineEdit_currentINumZ = new QLineEdit(groupBox);
        lineEdit_currentINumZ->setObjectName(QStringLiteral("lineEdit_currentINumZ"));
        lineEdit_currentINumZ->setReadOnly(true);

        horizontalLayout_12->addWidget(lineEdit_currentINumZ);

        horizontalLayout_12->setStretch(0, 1);
        horizontalLayout_12->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(12);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QStringLiteral("label_17"));

        horizontalLayout_3->addWidget(label_17);

        lineEdit_inverX1 = new QLineEdit(groupBox);
        lineEdit_inverX1->setObjectName(QStringLiteral("lineEdit_inverX1"));

        horizontalLayout_3->addWidget(lineEdit_inverX1);


        horizontalLayout_7->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        lineEdit_actual_begin_x = new QLineEdit(groupBox);
        lineEdit_actual_begin_x->setObjectName(QStringLiteral("lineEdit_actual_begin_x"));
        lineEdit_actual_begin_x->setReadOnly(true);

        horizontalLayout_4->addWidget(lineEdit_actual_begin_x);


        horizontalLayout_7->addLayout(horizontalLayout_4);

        horizontalLayout_7->setStretch(0, 1);
        horizontalLayout_7->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(12);
        horizontalLayout_27->setObjectName(QStringLiteral("horizontalLayout_27"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(0);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_9->addWidget(label_12);

        lineEdit_inverX2 = new QLineEdit(groupBox);
        lineEdit_inverX2->setObjectName(QStringLiteral("lineEdit_inverX2"));

        horizontalLayout_9->addWidget(lineEdit_inverX2);


        horizontalLayout_27->addLayout(horizontalLayout_9);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(0);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_14->addWidget(label_3);

        lineEdit_actual_end_x = new QLineEdit(groupBox);
        lineEdit_actual_end_x->setObjectName(QStringLiteral("lineEdit_actual_end_x"));
        lineEdit_actual_end_x->setReadOnly(true);

        horizontalLayout_14->addWidget(lineEdit_actual_end_x);


        horizontalLayout_27->addLayout(horizontalLayout_14);

        horizontalLayout_27->setStretch(0, 1);
        horizontalLayout_27->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_27);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setSpacing(12);
        horizontalLayout_26->setObjectName(QStringLiteral("horizontalLayout_26"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(0);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_15->addWidget(label_13);

        lineEdit_inverY1 = new QLineEdit(groupBox);
        lineEdit_inverY1->setObjectName(QStringLiteral("lineEdit_inverY1"));

        horizontalLayout_15->addWidget(lineEdit_inverY1);


        horizontalLayout_26->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(0);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_16->addWidget(label_4);

        lineEdit_actual_begin_y = new QLineEdit(groupBox);
        lineEdit_actual_begin_y->setObjectName(QStringLiteral("lineEdit_actual_begin_y"));
        lineEdit_actual_begin_y->setReadOnly(true);

        horizontalLayout_16->addWidget(lineEdit_actual_begin_y);


        horizontalLayout_26->addLayout(horizontalLayout_16);

        horizontalLayout_26->setStretch(0, 1);
        horizontalLayout_26->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_26);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(12);
        horizontalLayout_25->setObjectName(QStringLiteral("horizontalLayout_25"));
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(0);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_17->addWidget(label_14);

        lineEdit_inverY2 = new QLineEdit(groupBox);
        lineEdit_inverY2->setObjectName(QStringLiteral("lineEdit_inverY2"));

        horizontalLayout_17->addWidget(lineEdit_inverY2);


        horizontalLayout_25->addLayout(horizontalLayout_17);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(0);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_18->addWidget(label_7);

        lineEdit_actual_end_y = new QLineEdit(groupBox);
        lineEdit_actual_end_y->setObjectName(QStringLiteral("lineEdit_actual_end_y"));
        lineEdit_actual_end_y->setReadOnly(true);

        horizontalLayout_18->addWidget(lineEdit_actual_end_y);


        horizontalLayout_25->addLayout(horizontalLayout_18);

        horizontalLayout_25->setStretch(0, 1);
        horizontalLayout_25->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_25);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(12);
        horizontalLayout_24->setObjectName(QStringLiteral("horizontalLayout_24"));
        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(0);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_19->addWidget(label_15);

        lineEdit_inverZ1 = new QLineEdit(groupBox);
        lineEdit_inverZ1->setObjectName(QStringLiteral("lineEdit_inverZ1"));

        horizontalLayout_19->addWidget(lineEdit_inverZ1);


        horizontalLayout_24->addLayout(horizontalLayout_19);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(0);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_20->addWidget(label_8);

        lineEdit_actual_begin_z = new QLineEdit(groupBox);
        lineEdit_actual_begin_z->setObjectName(QStringLiteral("lineEdit_actual_begin_z"));
        lineEdit_actual_begin_z->setReadOnly(true);

        horizontalLayout_20->addWidget(lineEdit_actual_begin_z);


        horizontalLayout_24->addLayout(horizontalLayout_20);

        horizontalLayout_24->setStretch(0, 1);
        horizontalLayout_24->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_24);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(12);
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(0);
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        label_18 = new QLabel(groupBox);
        label_18->setObjectName(QStringLiteral("label_18"));

        horizontalLayout_21->addWidget(label_18);

        lineEdit_inverZ2 = new QLineEdit(groupBox);
        lineEdit_inverZ2->setObjectName(QStringLiteral("lineEdit_inverZ2"));

        horizontalLayout_21->addWidget(lineEdit_inverZ2);


        horizontalLayout_23->addLayout(horizontalLayout_21);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(0);
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QStringLiteral("label_16"));

        horizontalLayout_22->addWidget(label_16);

        lineEdit_actual_end_z = new QLineEdit(groupBox);
        lineEdit_actual_end_z->setObjectName(QStringLiteral("lineEdit_actual_end_z"));
        lineEdit_actual_end_z->setReadOnly(true);

        horizontalLayout_22->addWidget(lineEdit_actual_end_z);


        horizontalLayout_23->addLayout(horizontalLayout_22);

        horizontalLayout_23->setStretch(0, 1);
        horizontalLayout_23->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_23);


        verticalLayout_2->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(DialogSimuForward);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton_2 = new QPushButton(DialogSimuForward);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout_2->setStretch(0, 20);
        verticalLayout_2->setStretch(1, 1);

        horizontalLayout_2->addLayout(verticalLayout_2);


        retranslateUi(DialogSimuForward);
        QObject::connect(pushButton, SIGNAL(clicked()), DialogSimuForward, SLOT(accept()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), DialogSimuForward, SLOT(reject()));
        QObject::connect(lineEdit_inverX1, SIGNAL(editingFinished()), DialogSimuForward, SLOT(onActualLocationXMinChanged()));
        QObject::connect(lineEdit_inverY1, SIGNAL(editingFinished()), DialogSimuForward, SLOT(onActualLocationYMinChanged()));
        QObject::connect(lineEdit_inverZ1, SIGNAL(editingFinished()), DialogSimuForward, SLOT(onActualLocationZMinChanged()));
        QObject::connect(lineEdit_inverX2, SIGNAL(editingFinished()), DialogSimuForward, SLOT(onActualLocationXMaxChanged()));
        QObject::connect(lineEdit_inverY2, SIGNAL(editingFinished()), DialogSimuForward, SLOT(onActualLocationYMaxChanged()));
        QObject::connect(lineEdit_inverZ2, SIGNAL(editingFinished()), DialogSimuForward, SLOT(onActualLocationZMaxChanged()));

        QMetaObject::connectSlotsByName(DialogSimuForward);
    } // setupUi

    void retranslateUi(QDialog *DialogSimuForward)
    {
        DialogSimuForward->setWindowTitle(QApplication::translate("DialogSimuForward", "\346\250\241\346\213\237\346\255\243\346\274\224\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("DialogSimuForward", "\345\217\202\346\225\260", Q_NULLPTR));
        label->setText(QApplication::translate("DialogSimuForward", "\347\224\265\344\275\215\350\243\205\347\275\256\351\200\211\346\213\251\345\274\200\345\205\263\357\274\232         ", Q_NULLPTR));
        comboBox_selectionSwitch->clear();
        comboBox_selectionSwitch->insertItems(0, QStringList()
         << QApplication::translate("DialogSimuForward", "Schlumberger", Q_NULLPTR)
         << QApplication::translate("DialogSimuForward", "AMNB", Q_NULLPTR)
        );
        label_5->setText(QApplication::translate("DialogSimuForward", "\344\276\233\347\224\265\347\224\265\346\236\201\351\231\204\350\277\221\347\232\204\347\224\265\351\230\273\347\216\207\345\200\274\357\274\232   ", Q_NULLPTR));
        lineEdit_sgM0Value->setText(QApplication::translate("DialogSimuForward", "1000", Q_NULLPTR));
        label_CII->setText(QApplication::translate("DialogSimuForward", "\347\224\265\346\265\201\345\244\247\345\260\217CII\357\274\232              ", Q_NULLPTR));
        lineEdit_CII->setText(QApplication::translate("DialogSimuForward", "1.0", Q_NULLPTR));
        label_6->setText(QApplication::translate("DialogSimuForward", "\347\224\265\346\265\201\345\244\247\345\260\217II\357\274\232               ", Q_NULLPTR));
        lineEdit_II->setText(QApplication::translate("DialogSimuForward", "1.0", Q_NULLPTR));
        label_9->setText(QApplication::translate("DialogSimuForward", "\344\276\233\347\224\265\347\224\265\346\272\220\344\275\215\347\275\256XPos\357\274\232         ", Q_NULLPTR));
        lineEdit_currentINumX->setText(QApplication::translate("DialogSimuForward", "11", Q_NULLPTR));
        label_10->setText(QApplication::translate("DialogSimuForward", "\344\276\233\347\224\265\347\224\265\346\272\220\344\275\215\347\275\256YPos\357\274\232         ", Q_NULLPTR));
        lineEdit_currentINumY->setText(QApplication::translate("DialogSimuForward", "11", Q_NULLPTR));
        label_11->setText(QApplication::translate("DialogSimuForward", "\344\276\233\347\224\265\347\224\265\346\272\220\344\275\215\347\275\256ZPos\357\274\232         ", Q_NULLPTR));
        lineEdit_currentINumZ->setText(QApplication::translate("DialogSimuForward", "0", Q_NULLPTR));
        label_17->setText(QApplication::translate("DialogSimuForward", "\345\274\202\345\270\270\344\275\223\345\215\225\345\205\203\350\212\202\347\202\271XMin\357\274\232", Q_NULLPTR));
        lineEdit_inverX1->setText(QApplication::translate("DialogSimuForward", "9", Q_NULLPTR));
        label_2->setText(QApplication::translate("DialogSimuForward", "\345\274\202\345\270\270\344\275\223\345\256\236\351\231\205\344\275\215\347\275\256\357\274\232", Q_NULLPTR));
        label_12->setText(QApplication::translate("DialogSimuForward", "\345\274\202\345\270\270\344\275\223\345\215\225\345\205\203\350\212\202\347\202\271XMax\357\274\232", Q_NULLPTR));
        lineEdit_inverX2->setText(QApplication::translate("DialogSimuForward", "14", Q_NULLPTR));
        label_3->setText(QApplication::translate("DialogSimuForward", "\345\274\202\345\270\270\344\275\223\345\256\236\351\231\205\344\275\215\347\275\256\357\274\232", Q_NULLPTR));
        label_13->setText(QApplication::translate("DialogSimuForward", "\345\274\202\345\270\270\344\275\223\345\215\225\345\205\203\350\212\202\347\202\271YMin\357\274\232", Q_NULLPTR));
        lineEdit_inverY1->setText(QApplication::translate("DialogSimuForward", "10", Q_NULLPTR));
        label_4->setText(QApplication::translate("DialogSimuForward", "\345\274\202\345\270\270\344\275\223\345\256\236\351\231\205\344\275\215\347\275\256\357\274\232", Q_NULLPTR));
        label_14->setText(QApplication::translate("DialogSimuForward", "\345\274\202\345\270\270\344\275\223\345\215\225\345\205\203\350\212\202\347\202\271YMax\357\274\232", Q_NULLPTR));
        lineEdit_inverY2->setText(QApplication::translate("DialogSimuForward", "15", Q_NULLPTR));
        label_7->setText(QApplication::translate("DialogSimuForward", "\345\274\202\345\270\270\344\275\223\345\256\236\351\231\205\344\275\215\347\275\256\357\274\232", Q_NULLPTR));
        label_15->setText(QApplication::translate("DialogSimuForward", "\345\274\202\345\270\270\344\275\223\345\215\225\345\205\203\350\212\202\347\202\271ZMin\357\274\232", Q_NULLPTR));
        lineEdit_inverZ1->setText(QApplication::translate("DialogSimuForward", "22", Q_NULLPTR));
        label_8->setText(QApplication::translate("DialogSimuForward", "\345\274\202\345\270\270\344\275\223\345\256\236\351\231\205\344\275\215\347\275\256\357\274\232", Q_NULLPTR));
        label_18->setText(QApplication::translate("DialogSimuForward", "\345\274\202\345\270\270\344\275\223\345\215\225\345\205\203\350\212\202\347\202\271ZMax\357\274\232", Q_NULLPTR));
        lineEdit_inverZ2->setText(QApplication::translate("DialogSimuForward", "27", Q_NULLPTR));
        label_16->setText(QApplication::translate("DialogSimuForward", "\345\274\202\345\270\270\344\275\223\345\256\236\351\231\205\344\275\215\347\275\256\357\274\232", Q_NULLPTR));
        pushButton->setText(QApplication::translate("DialogSimuForward", "OK", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("DialogSimuForward", "Cancle", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogSimuForward: public Ui_DialogSimuForward {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSIMUFORWARD_H
