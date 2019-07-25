/********************************************************************************
** Form generated from reading UI file 'DialogDisplayImage.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGDISPLAYIMAGE_H
#define UI_DIALOGDISPLAYIMAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include "include\3ddisplay\ViewerWidget3d.h"

QT_BEGIN_NAMESPACE

class Ui_DialogDisplayImage
{
public:
    QVBoxLayout *verticalLayout;
    ViewerWidget3d *widget_show;

    void setupUi(QDialog *DialogDisplayImage)
    {
        if (DialogDisplayImage->objectName().isEmpty())
            DialogDisplayImage->setObjectName(QStringLiteral("DialogDisplayImage"));
        DialogDisplayImage->resize(463, 397);
        verticalLayout = new QVBoxLayout(DialogDisplayImage);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_show = new ViewerWidget3d(DialogDisplayImage);
        widget_show->setObjectName(QStringLiteral("widget_show"));

        verticalLayout->addWidget(widget_show);


        retranslateUi(DialogDisplayImage);

        QMetaObject::connectSlotsByName(DialogDisplayImage);
    } // setupUi

    void retranslateUi(QDialog *DialogDisplayImage)
    {
        DialogDisplayImage->setWindowTitle(QApplication::translate("DialogDisplayImage", "\345\215\225\347\213\254\347\252\227\345\217\243\346\230\276\347\244\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogDisplayImage: public Ui_DialogDisplayImage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGDISPLAYIMAGE_H
