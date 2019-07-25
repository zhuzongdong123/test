/********************************************************************************
** Form generated from reading UI file 'DialogForwardModelingParaSetting.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGFORWARDMODELINGPARASETTING_H
#define UI_DIALOGFORWARDMODELINGPARASETTING_H

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
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogForwardModelingParaSetting
{
public:
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

    void setupUi(QDialog *DialogForwardModelingParaSetting)
    {
        if (DialogForwardModelingParaSetting->objectName().isEmpty())
            DialogForwardModelingParaSetting->setObjectName(QStringLiteral("DialogForwardModelingParaSetting"));
        DialogForwardModelingParaSetting->resize(428, 380);
        DialogForwardModelingParaSetting->setMinimumSize(QSize(428, 380));
        DialogForwardModelingParaSetting->setMaximumSize(QSize(428, 380));
        DialogForwardModelingParaSetting->setStyleSheet(QStringLiteral("font: 12px;"));
        verticalLayout_2 = new QVBoxLayout(DialogForwardModelingParaSetting);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(DialogForwardModelingParaSetting);
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


        verticalLayout_2->addWidget(groupBox);


        retranslateUi(DialogForwardModelingParaSetting);

        QMetaObject::connectSlotsByName(DialogForwardModelingParaSetting);
    } // setupUi

    void retranslateUi(QDialog *DialogForwardModelingParaSetting)
    {
        DialogForwardModelingParaSetting->setWindowTitle(QApplication::translate("DialogForwardModelingParaSetting", "\346\255\243\346\274\224\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("DialogForwardModelingParaSetting", "\345\217\202\346\225\260", Q_NULLPTR));
        label->setText(QApplication::translate("DialogForwardModelingParaSetting", "\347\224\265\344\275\215\350\243\205\347\275\256\351\200\211\346\213\251\345\274\200\345\205\263\357\274\232         ", Q_NULLPTR));
        comboBox_selectionSwitch->clear();
        comboBox_selectionSwitch->insertItems(0, QStringList()
         << QApplication::translate("DialogForwardModelingParaSetting", "Schlumberger", Q_NULLPTR)
         << QApplication::translate("DialogForwardModelingParaSetting", "AMNB", Q_NULLPTR)
        );
        label_5->setText(QApplication::translate("DialogForwardModelingParaSetting", "\344\276\233\347\224\265\347\224\265\346\236\201\351\231\204\350\277\221\347\232\204\347\224\265\351\230\273\347\216\207\345\200\274\357\274\232   ", Q_NULLPTR));
        lineEdit_sgM0Value->setText(QApplication::translate("DialogForwardModelingParaSetting", "1000", Q_NULLPTR));
        label_CII->setText(QApplication::translate("DialogForwardModelingParaSetting", "\347\224\265\346\265\201\345\244\247\345\260\217CII\357\274\232              ", Q_NULLPTR));
        lineEdit_CII->setText(QApplication::translate("DialogForwardModelingParaSetting", "1.0", Q_NULLPTR));
        label_6->setText(QApplication::translate("DialogForwardModelingParaSetting", "\347\224\265\346\265\201\345\244\247\345\260\217II\357\274\232               ", Q_NULLPTR));
        lineEdit_II->setText(QApplication::translate("DialogForwardModelingParaSetting", "1.0", Q_NULLPTR));
        label_9->setText(QApplication::translate("DialogForwardModelingParaSetting", "\344\276\233\347\224\265\347\224\265\346\272\220\344\275\215\347\275\256XPos\357\274\232         ", Q_NULLPTR));
        lineEdit_currentINumX->setText(QApplication::translate("DialogForwardModelingParaSetting", "11", Q_NULLPTR));
        label_10->setText(QApplication::translate("DialogForwardModelingParaSetting", "\344\276\233\347\224\265\347\224\265\346\272\220\344\275\215\347\275\256YPos\357\274\232         ", Q_NULLPTR));
        lineEdit_currentINumY->setText(QApplication::translate("DialogForwardModelingParaSetting", "11", Q_NULLPTR));
        label_11->setText(QApplication::translate("DialogForwardModelingParaSetting", "\344\276\233\347\224\265\347\224\265\346\272\220\344\275\215\347\275\256ZPos\357\274\232         ", Q_NULLPTR));
        lineEdit_currentINumZ->setText(QApplication::translate("DialogForwardModelingParaSetting", "0", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogForwardModelingParaSetting: public Ui_DialogForwardModelingParaSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGFORWARDMODELINGPARASETTING_H
