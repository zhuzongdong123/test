/********************************************************************************
** Form generated from reading UI file 'DialogCreateProject.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCREATEPROJECT_H
#define UI_DIALOGCREATEPROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogCreateProject
{
public:
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit_proj_name;
    QLabel *label_2;
    QLineEdit *lineEdit_proj_pos;
    QLabel *label_3;
    QLineEdit *lineEdit_area_name;
    QLabel *label_4;
    QDateEdit *dateEdit_date;
    QLabel *label_5;
    QLineEdit *lineEdit_path;
    QToolButton *toolButton_path;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *DialogCreateProject)
    {
        if (DialogCreateProject->objectName().isEmpty())
            DialogCreateProject->setObjectName(QStringLiteral("DialogCreateProject"));
        DialogCreateProject->resize(477, 200);
        DialogCreateProject->setMinimumSize(QSize(477, 200));
        DialogCreateProject->setMaximumSize(QSize(477, 200));
        DialogCreateProject->setStyleSheet(QString::fromUtf8("font: 12px \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        groupBox = new QGroupBox(DialogCreateProject);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 371, 181));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit_proj_name = new QLineEdit(groupBox);
        lineEdit_proj_name->setObjectName(QStringLiteral("lineEdit_proj_name"));

        gridLayout->addWidget(lineEdit_proj_name, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_proj_pos = new QLineEdit(groupBox);
        lineEdit_proj_pos->setObjectName(QStringLiteral("lineEdit_proj_pos"));

        gridLayout->addWidget(lineEdit_proj_pos, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineEdit_area_name = new QLineEdit(groupBox);
        lineEdit_area_name->setObjectName(QStringLiteral("lineEdit_area_name"));

        gridLayout->addWidget(lineEdit_area_name, 2, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        dateEdit_date = new QDateEdit(groupBox);
        dateEdit_date->setObjectName(QStringLiteral("dateEdit_date"));

        gridLayout->addWidget(dateEdit_date, 3, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        lineEdit_path = new QLineEdit(groupBox);
        lineEdit_path->setObjectName(QStringLiteral("lineEdit_path"));
        lineEdit_path->setFrame(true);

        gridLayout->addWidget(lineEdit_path, 4, 1, 1, 1);

        toolButton_path = new QToolButton(groupBox);
        toolButton_path->setObjectName(QStringLiteral("toolButton_path"));

        gridLayout->addWidget(toolButton_path, 4, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        okButton = new QPushButton(DialogCreateProject);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setGeometry(QRect(390, 60, 75, 23));
        cancelButton = new QPushButton(DialogCreateProject);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(390, 93, 75, 23));

        retranslateUi(DialogCreateProject);
        QObject::connect(okButton, SIGNAL(clicked()), DialogCreateProject, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), DialogCreateProject, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogCreateProject);
    } // setupUi

    void retranslateUi(QDialog *DialogCreateProject)
    {
        DialogCreateProject->setWindowTitle(QApplication::translate("DialogCreateProject", "\346\226\260\345\273\272\345\267\245\347\250\213", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("DialogCreateProject", "\345\267\245\347\250\213\345\261\236\346\200\247", Q_NULLPTR));
        label->setText(QApplication::translate("DialogCreateProject", "\345\267\245\347\250\213\345\220\215\347\247\260", Q_NULLPTR));
        label_2->setText(QApplication::translate("DialogCreateProject", "\345\267\245\347\250\213\344\275\215\347\275\256", Q_NULLPTR));
        label_3->setText(QApplication::translate("DialogCreateProject", "\345\267\245\345\214\272\345\220\215\347\247\260", Q_NULLPTR));
        label_4->setText(QApplication::translate("DialogCreateProject", "\346\226\275\345\267\245\346\227\245\346\234\237", Q_NULLPTR));
        label_5->setText(QApplication::translate("DialogCreateProject", "\345\267\245\347\250\213\350\267\257\345\276\204", Q_NULLPTR));
        toolButton_path->setText(QApplication::translate("DialogCreateProject", "...", Q_NULLPTR));
        okButton->setText(QApplication::translate("DialogCreateProject", "Create", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("DialogCreateProject", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogCreateProject: public Ui_DialogCreateProject {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCREATEPROJECT_H
