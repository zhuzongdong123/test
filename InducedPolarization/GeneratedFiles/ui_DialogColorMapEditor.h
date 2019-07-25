/********************************************************************************
** Form generated from reading UI file 'DialogColorMapEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCOLORMAPEDITOR_H
#define UI_DIALOGCOLORMAPEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <myColorButtonV.h>

QT_BEGIN_NAMESPACE

class Ui_DialogColorMapEditor
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QLabel *label_5;
    QPushButton *pushButton;
    QLineEdit *lineEdit_R;
    QLineEdit *lineEdit_G;
    QLineEdit *lineEdit_B;
    QLineEdit *lineEdit_A;
    myColorButtonV *colorButtonV;
    QLabel *label_6;

    void setupUi(QDialog *DialogColorMapEditor)
    {
        if (DialogColorMapEditor->objectName().isEmpty())
            DialogColorMapEditor->setObjectName(QStringLiteral("DialogColorMapEditor"));
        DialogColorMapEditor->resize(386, 106);
        DialogColorMapEditor->setMinimumSize(QSize(386, 106));
        DialogColorMapEditor->setMaximumSize(QSize(386, 106));
        DialogColorMapEditor->setStyleSheet(QString::fromUtf8("font: 12px \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label = new QLabel(DialogColorMapEditor);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(12, 20, 141, 16));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(DialogColorMapEditor);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(230, 22, 16, 15));
        label_2->setMinimumSize(QSize(0, 15));
        label_2->setMaximumSize(QSize(16777215, 15));
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(DialogColorMapEditor);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(270, 22, 16, 15));
        label_3->setMinimumSize(QSize(0, 15));
        label_3->setMaximumSize(QSize(16777215, 15));
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(DialogColorMapEditor);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(310, 22, 16, 15));
        label_4->setMinimumSize(QSize(0, 15));
        label_4->setMaximumSize(QSize(16777215, 15));
        label_4->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(DialogColorMapEditor);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(12, 37, 359, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        comboBox = new QComboBox(layoutWidget);
        QIcon icon;
        icon.addFile(QStringLiteral(":/mainWindow/images/custom.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBox->addItem(icon, QString());
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/mainWindow/images/accents.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBox->addItem(icon1, QString());
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/mainWindow/images/color1.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBox->addItem(icon2, QString());
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/mainWindow/images/color2.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBox->addItem(icon3, QString());
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/mainWindow/images/color3.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBox->addItem(icon4, QString());
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/mainWindow/images/color4.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBox->addItem(icon5, QString());
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setMinimumSize(QSize(144, 21));
        comboBox->setMaximumSize(QSize(144, 21));
        comboBox->setStyleSheet(QLatin1String("QComboBox {\n"
"	border: 1px solid #bebebe;\n"
"	padding: 1px 18px 1px 3px;\n"
"	font: 75 10pt;\n"
"	\n"
"}"));
        comboBox->setIconSize(QSize(50, 20));

        horizontalLayout->addWidget(comboBox);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout->addWidget(label_5);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(36, 23));
        pushButton->setMaximumSize(QSize(36, 23));
        pushButton->setStyleSheet(QStringLiteral("QPushButton{background: rgba(229, 229, 229, 0)}"));
        pushButton->setFlat(false);

        horizontalLayout->addWidget(pushButton);

        lineEdit_R = new QLineEdit(layoutWidget);
        lineEdit_R->setObjectName(QStringLiteral("lineEdit_R"));
        lineEdit_R->setMinimumSize(QSize(32, 20));
        lineEdit_R->setMaximumSize(QSize(32, 20));
        lineEdit_R->setAlignment(Qt::AlignCenter);
        lineEdit_R->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit_R);

        lineEdit_G = new QLineEdit(layoutWidget);
        lineEdit_G->setObjectName(QStringLiteral("lineEdit_G"));
        lineEdit_G->setMinimumSize(QSize(32, 20));
        lineEdit_G->setMaximumSize(QSize(32, 20));
        lineEdit_G->setAlignment(Qt::AlignCenter);
        lineEdit_G->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit_G);

        lineEdit_B = new QLineEdit(layoutWidget);
        lineEdit_B->setObjectName(QStringLiteral("lineEdit_B"));
        lineEdit_B->setMinimumSize(QSize(32, 20));
        lineEdit_B->setMaximumSize(QSize(32, 20));
        lineEdit_B->setAlignment(Qt::AlignCenter);
        lineEdit_B->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit_B);

        lineEdit_A = new QLineEdit(layoutWidget);
        lineEdit_A->setObjectName(QStringLiteral("lineEdit_A"));
        lineEdit_A->setMinimumSize(QSize(32, 20));
        lineEdit_A->setMaximumSize(QSize(32, 20));

        horizontalLayout->addWidget(lineEdit_A);

        horizontalLayout->setStretch(0, 5);
        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(2, 1);
        horizontalLayout->setStretch(3, 1);
        horizontalLayout->setStretch(4, 1);
        horizontalLayout->setStretch(5, 1);
        horizontalLayout->setStretch(6, 1);
        colorButtonV = new myColorButtonV(DialogColorMapEditor);
        colorButtonV->setObjectName(QStringLiteral("colorButtonV"));
        colorButtonV->setGeometry(QRect(10, 70, 361, 24));
        label_6 = new QLabel(DialogColorMapEditor);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(350, 22, 16, 15));
        label_6->setMinimumSize(QSize(0, 15));
        label_6->setMaximumSize(QSize(16777215, 15));
        label_6->setAlignment(Qt::AlignCenter);

        retranslateUi(DialogColorMapEditor);
        QObject::connect(comboBox, SIGNAL(currentTextChanged(QString)), DialogColorMapEditor, SLOT(getChangedText(QString)));
        QObject::connect(colorButtonV, SIGNAL(setColorValue(int,int,int)), DialogColorMapEditor, SLOT(setColorValue(int,int,int)));
        QObject::connect(lineEdit_A, SIGNAL(textChanged(QString)), DialogColorMapEditor, SLOT(changeTransparency(QString)));

        QMetaObject::connectSlotsByName(DialogColorMapEditor);
    } // setupUi

    void retranslateUi(QDialog *DialogColorMapEditor)
    {
        DialogColorMapEditor->setWindowTitle(QApplication::translate("DialogColorMapEditor", "ColorMapping Editor", Q_NULLPTR));
        label->setText(QApplication::translate("DialogColorMapEditor", "Color Mapping", Q_NULLPTR));
        label_2->setText(QApplication::translate("DialogColorMapEditor", "R:", Q_NULLPTR));
        label_3->setText(QApplication::translate("DialogColorMapEditor", "G:", Q_NULLPTR));
        label_4->setText(QApplication::translate("DialogColorMapEditor", "B:", Q_NULLPTR));
        comboBox->setItemText(0, QApplication::translate("DialogColorMapEditor", "custom", Q_NULLPTR));
        comboBox->setItemText(1, QApplication::translate("DialogColorMapEditor", "accents", Q_NULLPTR));
        comboBox->setItemText(2, QApplication::translate("DialogColorMapEditor", "color1", Q_NULLPTR));
        comboBox->setItemText(3, QApplication::translate("DialogColorMapEditor", "color2", Q_NULLPTR));
        comboBox->setItemText(4, QApplication::translate("DialogColorMapEditor", "color3", Q_NULLPTR));
        comboBox->setItemText(5, QApplication::translate("DialogColorMapEditor", "color4", Q_NULLPTR));

        label_5->setText(QString());
        pushButton->setText(QApplication::translate("DialogColorMapEditor", "RGBA:", Q_NULLPTR));
        lineEdit_R->setText(QApplication::translate("DialogColorMapEditor", "255", Q_NULLPTR));
        lineEdit_G->setText(QApplication::translate("DialogColorMapEditor", "255", Q_NULLPTR));
        lineEdit_B->setText(QApplication::translate("DialogColorMapEditor", "255", Q_NULLPTR));
        lineEdit_A->setText(QApplication::translate("DialogColorMapEditor", "255", Q_NULLPTR));
        colorButtonV->setText(QString());
        label_6->setText(QApplication::translate("DialogColorMapEditor", "A:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogColorMapEditor: public Ui_DialogColorMapEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCOLORMAPEDITOR_H
