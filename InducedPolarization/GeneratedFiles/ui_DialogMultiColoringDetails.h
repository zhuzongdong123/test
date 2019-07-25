/********************************************************************************
** Form generated from reading UI file 'DialogMultiColoringDetails.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGMULTICOLORINGDETAILS_H
#define UI_DIALOGMULTICOLORINGDETAILS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogMultiColoringDetails
{
public:
    QPushButton *pushButton_enterNewLevel;
    QComboBox *comboBox;

    void setupUi(QDialog *DialogMultiColoringDetails)
    {
        if (DialogMultiColoringDetails->objectName().isEmpty())
            DialogMultiColoringDetails->setObjectName(QStringLiteral("DialogMultiColoringDetails"));
        DialogMultiColoringDetails->resize(670, 482);
        pushButton_enterNewLevel = new QPushButton(DialogMultiColoringDetails);
        pushButton_enterNewLevel->setObjectName(QStringLiteral("pushButton_enterNewLevel"));
        pushButton_enterNewLevel->setGeometry(QRect(20, 20, 151, 23));
        comboBox = new QComboBox(DialogMultiColoringDetails);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(220, 20, 141, 22));

        retranslateUi(DialogMultiColoringDetails);
        QObject::connect(pushButton_enterNewLevel, SIGNAL(clicked()), DialogMultiColoringDetails, SLOT(enterNewLevel()));
        QObject::connect(comboBox, SIGNAL(currentTextChanged(QString)), DialogMultiColoringDetails, SLOT(colorGroupChanged(QString)));

        QMetaObject::connectSlotsByName(DialogMultiColoringDetails);
    } // setupUi

    void retranslateUi(QDialog *DialogMultiColoringDetails)
    {
        DialogMultiColoringDetails->setWindowTitle(QApplication::translate("DialogMultiColoringDetails", "DialogMultiColoringDetails", Q_NULLPTR));
        pushButton_enterNewLevel->setText(QApplication::translate("DialogMultiColoringDetails", "Enter New Level...", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogMultiColoringDetails", "jetColor", Q_NULLPTR)
         << QApplication::translate("DialogMultiColoringDetails", "customColor", Q_NULLPTR)
         << QApplication::translate("DialogMultiColoringDetails", "largeRainbow", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class DialogMultiColoringDetails: public Ui_DialogMultiColoringDetails {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGMULTICOLORINGDETAILS_H
