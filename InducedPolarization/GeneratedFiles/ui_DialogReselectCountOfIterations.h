/********************************************************************************
** Form generated from reading UI file 'DialogReselectCountOfIterations.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGRESELECTCOUNTOFITERATIONS_H
#define UI_DIALOGRESELECTCOUNTOFITERATIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogReselectCountOfIterations
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QLineEdit *lineEdit;
    QLabel *label;

    void setupUi(QDialog *DialogReselectCountOfIterations)
    {
        if (DialogReselectCountOfIterations->objectName().isEmpty())
            DialogReselectCountOfIterations->setObjectName(QStringLiteral("DialogReselectCountOfIterations"));
        DialogReselectCountOfIterations->resize(215, 81);
        layoutWidget = new QWidget(DialogReselectCountOfIterations);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 40, 157, 33));
        hboxLayout = new QHBoxLayout(layoutWidget);
        hboxLayout->setSpacing(0);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QStringLiteral("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        hboxLayout->addWidget(cancelButton);

        lineEdit = new QLineEdit(DialogReselectCountOfIterations);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(150, 10, 51, 20));
        label = new QLabel(DialogReselectCountOfIterations);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 121, 16));

        retranslateUi(DialogReselectCountOfIterations);
        QObject::connect(okButton, SIGNAL(clicked()), DialogReselectCountOfIterations, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), DialogReselectCountOfIterations, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogReselectCountOfIterations);
    } // setupUi

    void retranslateUi(QDialog *DialogReselectCountOfIterations)
    {
        DialogReselectCountOfIterations->setWindowTitle(QApplication::translate("DialogReselectCountOfIterations", "\351\207\215\351\200\211", Q_NULLPTR));
        okButton->setText(QApplication::translate("DialogReselectCountOfIterations", "\347\241\256\345\256\232", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("DialogReselectCountOfIterations", "\345\217\226\346\266\210", Q_NULLPTR));
        label->setText(QApplication::translate("DialogReselectCountOfIterations", "\350\257\267\351\207\215\346\226\260\350\276\223\345\205\245\350\277\255\344\273\243\346\254\241\346\225\260\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogReselectCountOfIterations: public Ui_DialogReselectCountOfIterations {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGRESELECTCOUNTOFITERATIONS_H
