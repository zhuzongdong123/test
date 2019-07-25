/********************************************************************************
** Form generated from reading UI file 'DialogSetup.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSETUP_H
#define UI_DIALOGSETUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogSetup
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QCheckBox *checkBox_debugLog;
    QCheckBox *checkBox_DPCGRCLog;
    QCheckBox *checkBox_NroLog;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QCheckBox *checkBox_isWriteFile;
    QGridLayout *gridLayout_3;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *DialogSetup)
    {
        if (DialogSetup->objectName().isEmpty())
            DialogSetup->setObjectName(QStringLiteral("DialogSetup"));
        DialogSetup->resize(362, 151);
        DialogSetup->setMinimumSize(QSize(362, 151));
        DialogSetup->setMaximumSize(QSize(362, 151));
        verticalLayout = new QVBoxLayout(DialogSetup);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox = new QGroupBox(DialogSetup);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        checkBox_debugLog = new QCheckBox(groupBox);
        checkBox_debugLog->setObjectName(QStringLiteral("checkBox_debugLog"));

        gridLayout->addWidget(checkBox_debugLog, 0, 0, 1, 1);

        checkBox_DPCGRCLog = new QCheckBox(groupBox);
        checkBox_DPCGRCLog->setObjectName(QStringLiteral("checkBox_DPCGRCLog"));

        gridLayout->addWidget(checkBox_DPCGRCLog, 1, 0, 1, 1);

        checkBox_NroLog = new QCheckBox(groupBox);
        checkBox_NroLog->setObjectName(QStringLiteral("checkBox_NroLog"));

        gridLayout->addWidget(checkBox_NroLog, 2, 0, 1, 1);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(DialogSetup);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        checkBox_isWriteFile = new QCheckBox(groupBox_2);
        checkBox_isWriteFile->setObjectName(QStringLiteral("checkBox_isWriteFile"));

        gridLayout_2->addWidget(checkBox_isWriteFile, 0, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_2);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(spacerItem, 0, 0, 1, 1);

        okButton = new QPushButton(DialogSetup);
        okButton->setObjectName(QStringLiteral("okButton"));

        gridLayout_3->addWidget(okButton, 0, 1, 1, 1);

        cancelButton = new QPushButton(DialogSetup);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        gridLayout_3->addWidget(cancelButton, 0, 2, 1, 1);


        verticalLayout->addLayout(gridLayout_3);


        retranslateUi(DialogSetup);
        QObject::connect(okButton, SIGNAL(clicked()), DialogSetup, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), DialogSetup, SLOT(reject()));
        QObject::connect(okButton, SIGNAL(clicked()), DialogSetup, SLOT(onOkButton()));

        QMetaObject::connectSlotsByName(DialogSetup);
    } // setupUi

    void retranslateUi(QDialog *DialogSetup)
    {
        DialogSetup->setWindowTitle(QApplication::translate("DialogSetup", "\350\256\276\347\275\256", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("DialogSetup", "\346\227\245\345\277\227\344\277\241\346\201\257\350\277\207\346\273\244\350\256\276\347\275\256", Q_NULLPTR));
        checkBox_debugLog->setText(QApplication::translate("DialogSetup", "\346\255\243\345\217\215\346\274\224\344\277\241\346\201\257", Q_NULLPTR));
        checkBox_DPCGRCLog->setText(QApplication::translate("DialogSetup", "DPCGRC\346\224\266\346\225\233\344\277\241\346\201\257", Q_NULLPTR));
        checkBox_NroLog->setText(QApplication::translate("DialogSetup", "NRO\344\277\241\346\201\257", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("DialogSetup", "\346\227\245\345\277\227\345\237\272\346\234\254\350\256\276\347\275\256", Q_NULLPTR));
        checkBox_isWriteFile->setText(QApplication::translate("DialogSetup", "\346\227\245\345\277\227\346\230\257\345\220\246\345\206\231\345\205\245\345\210\260\346\226\207\344\273\266", Q_NULLPTR));
        okButton->setText(QApplication::translate("DialogSetup", "\347\241\256\345\256\232", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("DialogSetup", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogSetup: public Ui_DialogSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSETUP_H
