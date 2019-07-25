#include "DialogReselectCountOfIterations.h"
#include <QMessageBox>

DialogReselectCountOfIterations::DialogReselectCountOfIterations(QWidget *parent /*= nullptr*/) : QDialog(parent)
{
    m_ui.setupUi(this);

    setValidator();
}

DialogReselectCountOfIterations::~DialogReselectCountOfIterations()
{
}

void DialogReselectCountOfIterations::accept()
{
    if ("" == m_ui.lineEdit->text())
    {
        QMessageBox::warning(NULL, QString::fromUtf8("问题"), QString::fromUtf8("请输入正确的数字"));
        return;
    }

    m_count = m_ui.lineEdit->text().toInt();

    QDialog::accept();
}

void DialogReselectCountOfIterations::setValidator()
{
    m_ui.lineEdit->setValidator(new QIntValidator(0, 999999, this));
}
