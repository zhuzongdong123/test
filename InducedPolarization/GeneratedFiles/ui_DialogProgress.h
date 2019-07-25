/********************************************************************************
** Form generated from reading UI file 'DialogProgress.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGPROGRESS_H
#define UI_DIALOGPROGRESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogProgress
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QProgressBar *progressBar;

    void setupUi(QDialog *DialogProgress)
    {
        if (DialogProgress->objectName().isEmpty())
            DialogProgress->setObjectName(QStringLiteral("DialogProgress"));
        DialogProgress->resize(400, 647);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DialogProgress->sizePolicy().hasHeightForWidth());
        DialogProgress->setSizePolicy(sizePolicy);
        DialogProgress->setMinimumSize(QSize(0, 0));
        DialogProgress->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout = new QVBoxLayout(DialogProgress);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        textEdit = new QTextEdit(DialogProgress);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setEnabled(true);
        textEdit->setReadOnly(true);

        verticalLayout->addWidget(textEdit);

        progressBar = new QProgressBar(DialogProgress);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);


        retranslateUi(DialogProgress);

        QMetaObject::connectSlotsByName(DialogProgress);
    } // setupUi

    void retranslateUi(QDialog *DialogProgress)
    {
        DialogProgress->setWindowTitle(QApplication::translate("DialogProgress", "\346\255\243\345\217\215\346\274\224\350\277\220\347\256\227\350\277\233\345\272\246", Q_NULLPTR));
        textEdit->setDocumentTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class DialogProgress: public Ui_DialogProgress {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGPROGRESS_H
