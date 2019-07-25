/********************************************************************************
** Form generated from reading UI file 'DialogInversionParaSetting.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGINVERSIONPARASETTING_H
#define UI_DIALOGINVERSIONPARASETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_DialogInversionParaSetting
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *comboBox_selectionSwitch;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_7;
    QCheckBox *checkBox_compare;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_9;
    QLineEdit *lineEdit_INVMAX;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_EPS;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLineEdit *lineEdit_EPSRMS;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *comboBox_computingMethod;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *lineEdit_BoundU;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QLineEdit *lineEdit_BoundL;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_8;
    QComboBox *comboBox_dataWeighting;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_13;
    QHBoxLayout *horizontalLayout_7;
    QRadioButton *radioButton_use;
    QRadioButton *radioButton_notUse;
    QLineEdit *lineEdit_Lamda;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_PCGEPS;
    QLineEdit *lineEdit_PCGEPS;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_11;
    QLineEdit *lineEdit_PCGRELERR;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_10;
    QLineEdit *lineEdit_PCGITMAX;

    void setupUi(QDialog *DialogInversionParaSetting)
    {
        if (DialogInversionParaSetting->objectName().isEmpty())
            DialogInversionParaSetting->setObjectName(QStringLiteral("DialogInversionParaSetting"));
        DialogInversionParaSetting->resize(364, 608);
        DialogInversionParaSetting->setMinimumSize(QSize(364, 608));
        DialogInversionParaSetting->setMaximumSize(QSize(364, 608));
        gridLayout_3 = new QGridLayout(DialogInversionParaSetting);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        groupBox = new QGroupBox(DialogInversionParaSetting);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
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
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        comboBox_selectionSwitch = new QComboBox(groupBox);
        comboBox_selectionSwitch->setObjectName(QStringLiteral("comboBox_selectionSwitch"));

        horizontalLayout_2->addWidget(comboBox_selectionSwitch);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 2);

        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_14->addWidget(label_7);

        checkBox_compare = new QCheckBox(groupBox);
        checkBox_compare->setObjectName(QStringLiteral("checkBox_compare"));
        checkBox_compare->setChecked(true);

        horizontalLayout_14->addWidget(checkBox_compare);


        gridLayout->addLayout(horizontalLayout_14, 1, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(0);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_9->addWidget(label_9);

        lineEdit_INVMAX = new QLineEdit(groupBox);
        lineEdit_INVMAX->setObjectName(QStringLiteral("lineEdit_INVMAX"));

        horizontalLayout_9->addWidget(lineEdit_INVMAX);


        gridLayout->addLayout(horizontalLayout_9, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit_EPS = new QLineEdit(groupBox);
        lineEdit_EPS->setObjectName(QStringLiteral("lineEdit_EPS"));

        horizontalLayout->addWidget(lineEdit_EPS);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 2);

        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        lineEdit_EPSRMS = new QLineEdit(groupBox);
        lineEdit_EPSRMS->setObjectName(QStringLiteral("lineEdit_EPSRMS"));

        horizontalLayout_5->addWidget(lineEdit_EPSRMS);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 2);

        gridLayout->addLayout(horizontalLayout_5, 4, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        comboBox_computingMethod = new QComboBox(groupBox);
        comboBox_computingMethod->setObjectName(QStringLiteral("comboBox_computingMethod"));

        horizontalLayout_3->addWidget(comboBox_computingMethod);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 2);

        gridLayout->addLayout(horizontalLayout_3, 5, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        lineEdit_BoundU = new QLineEdit(groupBox);
        lineEdit_BoundU->setObjectName(QStringLiteral("lineEdit_BoundU"));

        horizontalLayout_4->addWidget(lineEdit_BoundU);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 2);

        gridLayout->addLayout(horizontalLayout_4, 6, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_6->addWidget(label_6);

        lineEdit_BoundL = new QLineEdit(groupBox);
        lineEdit_BoundL->setObjectName(QStringLiteral("lineEdit_BoundL"));

        horizontalLayout_6->addWidget(lineEdit_BoundL);

        horizontalLayout_6->setStretch(0, 1);
        horizontalLayout_6->setStretch(1, 2);

        gridLayout->addLayout(horizontalLayout_6, 7, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_8->addWidget(label_8);

        comboBox_dataWeighting = new QComboBox(groupBox);
        comboBox_dataWeighting->setObjectName(QStringLiteral("comboBox_dataWeighting"));

        horizontalLayout_8->addWidget(comboBox_dataWeighting);

        horizontalLayout_8->setStretch(0, 1);
        horizontalLayout_8->setStretch(1, 2);

        gridLayout->addLayout(horizontalLayout_8, 8, 0, 1, 1);

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setMaximumSize(QSize(16777215, 45));
        horizontalLayout_13 = new QHBoxLayout(groupBox_3);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(0, -1, 0, -1);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        radioButton_use = new QRadioButton(groupBox_3);
        radioButton_use->setObjectName(QStringLiteral("radioButton_use"));

        horizontalLayout_7->addWidget(radioButton_use);

        radioButton_notUse = new QRadioButton(groupBox_3);
        radioButton_notUse->setObjectName(QStringLiteral("radioButton_notUse"));
        radioButton_notUse->setChecked(true);

        horizontalLayout_7->addWidget(radioButton_notUse);


        horizontalLayout_13->addLayout(horizontalLayout_7);

        lineEdit_Lamda = new QLineEdit(groupBox_3);
        lineEdit_Lamda->setObjectName(QStringLiteral("lineEdit_Lamda"));
        lineEdit_Lamda->setEnabled(false);
        lineEdit_Lamda->setMinimumSize(QSize(178, 0));
        lineEdit_Lamda->setMaximumSize(QSize(178, 16777215));

        horizontalLayout_13->addWidget(lineEdit_Lamda);

        horizontalLayout_13->setStretch(0, 1);
        horizontalLayout_13->setStretch(1, 2);

        gridLayout->addWidget(groupBox_3, 9, 0, 1, 1);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(16777215, 103));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(0);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_PCGEPS = new QLabel(groupBox_2);
        label_PCGEPS->setObjectName(QStringLiteral("label_PCGEPS"));

        horizontalLayout_11->addWidget(label_PCGEPS);

        lineEdit_PCGEPS = new QLineEdit(groupBox_2);
        lineEdit_PCGEPS->setObjectName(QStringLiteral("lineEdit_PCGEPS"));

        horizontalLayout_11->addWidget(lineEdit_PCGEPS);


        gridLayout_2->addLayout(horizontalLayout_11, 0, 0, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(0);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_12->addWidget(label_11);

        lineEdit_PCGRELERR = new QLineEdit(groupBox_2);
        lineEdit_PCGRELERR->setObjectName(QStringLiteral("lineEdit_PCGRELERR"));

        horizontalLayout_12->addWidget(lineEdit_PCGRELERR);


        gridLayout_2->addLayout(horizontalLayout_12, 1, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(0);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_10->addWidget(label_10);

        lineEdit_PCGITMAX = new QLineEdit(groupBox_2);
        lineEdit_PCGITMAX->setObjectName(QStringLiteral("lineEdit_PCGITMAX"));

        horizontalLayout_10->addWidget(lineEdit_PCGITMAX);


        gridLayout_2->addLayout(horizontalLayout_10, 2, 0, 1, 1);


        gridLayout->addWidget(groupBox_2, 10, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(DialogInversionParaSetting);
        QObject::connect(radioButton_use, SIGNAL(clicked()), DialogInversionParaSetting, SLOT(onClickedUseLAMDA()));
        QObject::connect(radioButton_notUse, SIGNAL(clicked()), DialogInversionParaSetting, SLOT(onClickedNotUseLAMDA()));

        QMetaObject::connectSlotsByName(DialogInversionParaSetting);
    } // setupUi

    void retranslateUi(QDialog *DialogInversionParaSetting)
    {
        DialogInversionParaSetting->setWindowTitle(QApplication::translate("DialogInversionParaSetting", "\345\217\215\346\274\224\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("DialogInversionParaSetting", "\345\217\202\346\225\260", Q_NULLPTR));
        label_2->setText(QApplication::translate("DialogInversionParaSetting", "\345\217\215\346\274\224\346\226\271\346\263\225\351\200\211\346\213\251\345\274\200\345\205\263\357\274\232      ", Q_NULLPTR));
        comboBox_selectionSwitch->clear();
        comboBox_selectionSwitch->insertItems(0, QStringList()
         << QApplication::translate("DialogInversionParaSetting", "\346\234\200\345\260\217\344\272\214\344\271\230", Q_NULLPTR)
         << QApplication::translate("DialogInversionParaSetting", "GA", Q_NULLPTR)
         << QApplication::translate("DialogInversionParaSetting", "\350\201\224\345\220\210", Q_NULLPTR)
         << QApplication::translate("DialogInversionParaSetting", "\350\232\201\347\276\244", Q_NULLPTR)
        );
        label_7->setText(QApplication::translate("DialogInversionParaSetting", "\345\274\202\345\270\270\344\275\223\347\274\226\350\276\221\344\277\241\346\201\257\345\257\271\346\257\224\345\274\200\345\205\263\357\274\232", Q_NULLPTR));
        checkBox_compare->setText(QString());
        label_9->setText(QApplication::translate("DialogInversionParaSetting", "\345\217\215\346\274\224\346\254\241\346\225\260\344\270\212\351\231\220\357\274\232          ", Q_NULLPTR));
        lineEdit_INVMAX->setText(QApplication::translate("DialogInversionParaSetting", "3", Q_NULLPTR));
        label->setText(QApplication::translate("DialogInversionParaSetting", "\350\257\257\345\267\256\345\256\271\350\256\270\345\200\274\357\274\232            ", Q_NULLPTR));
        lineEdit_EPS->setText(QApplication::translate("DialogInversionParaSetting", "0.000001", Q_NULLPTR));
        label_5->setText(QApplication::translate("DialogInversionParaSetting", "\347\233\270\345\257\271\346\213\237\345\220\210\345\267\256\347\232\204\346\224\266\346\225\233\346\225\260\346\215\256\357\274\232  ", Q_NULLPTR));
        lineEdit_EPSRMS->setText(QApplication::translate("DialogInversionParaSetting", "0.000003", Q_NULLPTR));
        label_3->setText(QApplication::translate("DialogInversionParaSetting", "\345\205\211\346\273\221\345\272\246\347\237\251\351\230\265\347\232\204\350\256\241\347\256\227\346\226\271\346\263\225\357\274\232  ", Q_NULLPTR));
        comboBox_computingMethod->clear();
        comboBox_computingMethod->insertItems(0, QStringList()
         << QApplication::translate("DialogInversionParaSetting", "\344\270\215\345\220\253\350\267\235\347\246\273\345\233\240\345\255\220", Q_NULLPTR)
         << QApplication::translate("DialogInversionParaSetting", "\345\220\253\350\267\235\347\246\273\345\233\240\345\255\220", Q_NULLPTR)
        );
        label_4->setText(QApplication::translate("DialogInversionParaSetting", "\345\217\215\346\274\224\346\250\241\345\236\213\344\270\255\347\232\204\347\224\265\351\230\273\347\216\207\344\270\212\351\231\220\357\274\232", Q_NULLPTR));
        lineEdit_BoundU->setText(QApplication::translate("DialogInversionParaSetting", "2000", Q_NULLPTR));
        label_6->setText(QApplication::translate("DialogInversionParaSetting", "\345\217\215\346\274\224\346\250\241\345\236\213\344\270\255\347\232\204\347\224\265\351\230\273\347\216\207\344\270\213\351\231\220\357\274\232", Q_NULLPTR));
        lineEdit_BoundL->setText(QApplication::translate("DialogInversionParaSetting", "7", Q_NULLPTR));
        label_8->setText(QApplication::translate("DialogInversionParaSetting", "\346\225\260\346\215\256\345\212\240\346\235\203\357\274\232              ", Q_NULLPTR));
        comboBox_dataWeighting->clear();
        comboBox_dataWeighting->insertItems(0, QStringList()
         << QApplication::translate("DialogInversionParaSetting", "\347\272\277\346\200\247", Q_NULLPTR)
         << QApplication::translate("DialogInversionParaSetting", "\346\214\207\346\225\260", Q_NULLPTR)
         << QApplication::translate("DialogInversionParaSetting", "\344\272\214\346\254\241", Q_NULLPTR)
         << QApplication::translate("DialogInversionParaSetting", "\346\227\240\345\212\240\346\235\203", Q_NULLPTR)
        );
        groupBox_3->setTitle(QApplication::translate("DialogInversionParaSetting", "\351\230\273\345\260\274\345\233\240\345\255\220", Q_NULLPTR));
        radioButton_use->setText(QApplication::translate("DialogInversionParaSetting", "\344\275\277\347\224\250", Q_NULLPTR));
        radioButton_notUse->setText(QApplication::translate("DialogInversionParaSetting", "\344\270\215\344\275\277\347\224\250", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("DialogInversionParaSetting", "PCG\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        label_PCGEPS->setText(QApplication::translate("DialogInversionParaSetting", "PCG\346\263\225\350\247\243\346\226\271\347\250\213\346\227\266\347\232\204\345\235\207\346\226\271\345\267\256\357\274\232    ", Q_NULLPTR));
        lineEdit_PCGEPS->setText(QApplication::translate("DialogInversionParaSetting", "0.000003", Q_NULLPTR));
        label_11->setText(QApplication::translate("DialogInversionParaSetting", "PCG\346\224\266\346\225\233\345\256\271\350\256\270\350\257\257\345\267\256\357\274\232          ", Q_NULLPTR));
        lineEdit_PCGRELERR->setText(QApplication::translate("DialogInversionParaSetting", "0.1", Q_NULLPTR));
        label_10->setText(QApplication::translate("DialogInversionParaSetting", "PCG\350\277\255\344\273\243\346\254\241\346\225\260\344\270\212\351\231\220\357\274\232          ", Q_NULLPTR));
        lineEdit_PCGITMAX->setText(QApplication::translate("DialogInversionParaSetting", "800000", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogInversionParaSetting: public Ui_DialogInversionParaSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGINVERSIONPARASETTING_H
