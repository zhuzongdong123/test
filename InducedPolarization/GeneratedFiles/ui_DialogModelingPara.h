/********************************************************************************
** Form generated from reading UI file 'DialogModelingPara.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGMODELINGPARA_H
#define UI_DIALOGMODELINGPARA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogModelingPara
{
public:
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit_grid_size_x;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEdit_grid_size_y;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *lineEdit_tunnel_cavity_range_x;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLineEdit *lineEdit_tunnel_cavity_range_y;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_7;
    QLineEdit *lineEdit_inversion_area_x;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_8;
    QLineEdit *lineEdit_inversion_area_y;

    void setupUi(QDialog *DialogModelingPara)
    {
        if (DialogModelingPara->objectName().isEmpty())
            DialogModelingPara->setObjectName(QStringLiteral("DialogModelingPara"));
        DialogModelingPara->resize(358, 389);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DialogModelingPara->sizePolicy().hasHeightForWidth());
        DialogModelingPara->setSizePolicy(sizePolicy);
        DialogModelingPara->setMinimumSize(QSize(358, 389));
        DialogModelingPara->setMaximumSize(QSize(358, 389));
        verticalLayout_6 = new QVBoxLayout(DialogModelingPara);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(12);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(6, 0, -1, -1);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        groupBox_2 = new QGroupBox(DialogModelingPara);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        lineEdit_grid_size_x = new QLineEdit(groupBox_2);
        lineEdit_grid_size_x->setObjectName(QStringLiteral("lineEdit_grid_size_x"));

        horizontalLayout_2->addWidget(lineEdit_grid_size_x);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        lineEdit_grid_size_y = new QLineEdit(groupBox_2);
        lineEdit_grid_size_y->setObjectName(QStringLiteral("lineEdit_grid_size_y"));

        horizontalLayout_3->addWidget(lineEdit_grid_size_y);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_4->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(DialogModelingPara);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_5->addWidget(label_4);

        lineEdit_tunnel_cavity_range_x = new QLineEdit(groupBox_3);
        lineEdit_tunnel_cavity_range_x->setObjectName(QStringLiteral("lineEdit_tunnel_cavity_range_x"));
        lineEdit_tunnel_cavity_range_x->setReadOnly(true);

        horizontalLayout_5->addWidget(lineEdit_tunnel_cavity_range_x);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_6->addWidget(label_5);

        lineEdit_tunnel_cavity_range_y = new QLineEdit(groupBox_3);
        lineEdit_tunnel_cavity_range_y->setObjectName(QStringLiteral("lineEdit_tunnel_cavity_range_y"));
        lineEdit_tunnel_cavity_range_y->setReadOnly(true);

        horizontalLayout_6->addWidget(lineEdit_tunnel_cavity_range_y);


        verticalLayout_2->addLayout(horizontalLayout_6);


        verticalLayout_4->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(DialogModelingPara);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        verticalLayout_3 = new QVBoxLayout(groupBox_4);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_8->addWidget(label_7);

        lineEdit_inversion_area_x = new QLineEdit(groupBox_4);
        lineEdit_inversion_area_x->setObjectName(QStringLiteral("lineEdit_inversion_area_x"));

        horizontalLayout_8->addWidget(lineEdit_inversion_area_x);


        verticalLayout_3->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_9->addWidget(label_8);

        lineEdit_inversion_area_y = new QLineEdit(groupBox_4);
        lineEdit_inversion_area_y->setObjectName(QStringLiteral("lineEdit_inversion_area_y"));

        horizontalLayout_9->addWidget(lineEdit_inversion_area_y);


        verticalLayout_3->addLayout(horizontalLayout_9);


        verticalLayout_4->addWidget(groupBox_4);

        verticalLayout_4->setStretch(0, 1);
        verticalLayout_4->setStretch(1, 1);
        verticalLayout_4->setStretch(2, 1);

        horizontalLayout->addLayout(verticalLayout_4);

        horizontalLayout->setStretch(0, 2);

        horizontalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_4->setStretch(0, 6);

        verticalLayout_5->addLayout(horizontalLayout_4);

        verticalLayout_5->setStretch(0, 6);

        verticalLayout_6->addLayout(verticalLayout_5);


        retranslateUi(DialogModelingPara);

        QMetaObject::connectSlotsByName(DialogModelingPara);
    } // setupUi

    void retranslateUi(QDialog *DialogModelingPara)
    {
        DialogModelingPara->setWindowTitle(QApplication::translate("DialogModelingPara", "\345\273\272\346\250\241\345\217\202\346\225\260\350\256\276\345\256\232", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("DialogModelingPara", "\351\242\204\346\212\245\345\214\272\345\237\237\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        label->setText(QApplication::translate("DialogModelingPara", "\351\242\204\346\212\245\351\225\277\345\272\246\357\274\232      ", Q_NULLPTR));
        lineEdit_grid_size_x->setText(QApplication::translate("DialogModelingPara", "30", Q_NULLPTR));
        label_2->setText(QApplication::translate("DialogModelingPara", "\351\242\204\346\212\245\345\215\225\345\205\203\346\240\274\351\227\264\350\267\235\357\274\232", Q_NULLPTR));
        lineEdit_grid_size_y->setText(QApplication::translate("DialogModelingPara", "2", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("DialogModelingPara", "\351\232\247\351\201\223\347\251\272\350\205\224\350\214\203\345\233\264", Q_NULLPTR));
        label_4->setText(QApplication::translate("DialogModelingPara", "X:", Q_NULLPTR));
        lineEdit_tunnel_cavity_range_x->setText(QApplication::translate("DialogModelingPara", "0", Q_NULLPTR));
        label_5->setText(QApplication::translate("DialogModelingPara", "Y:", Q_NULLPTR));
        lineEdit_tunnel_cavity_range_y->setText(QApplication::translate("DialogModelingPara", "0", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("DialogModelingPara", "\345\217\215\346\274\224\345\214\272\345\237\237\350\214\203\345\233\264", Q_NULLPTR));
        label_7->setText(QApplication::translate("DialogModelingPara", "X:", Q_NULLPTR));
        lineEdit_inversion_area_x->setText(QApplication::translate("DialogModelingPara", "30", Q_NULLPTR));
        label_8->setText(QApplication::translate("DialogModelingPara", "Y:", Q_NULLPTR));
        lineEdit_inversion_area_y->setText(QApplication::translate("DialogModelingPara", "30", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogModelingPara: public Ui_DialogModelingPara {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGMODELINGPARA_H
