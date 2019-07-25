#include "DialogContourLevels.h"
#include "QMessageBox"
#pragma execution_character_set("utf-8")

DialogContourLevels::DialogContourLevels(QWidget *parent)
{
	m_ui.setupUi(this);

	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);
}

void DialogContourLevels::resetRange() 
{
	m_ui.lineEdit_minimunLevel->setText(QString::number(m_defaultMinLevel));
	m_ui.lineEdit_maximumLevel->setText(QString::number(m_defaultMaxLevel));
	m_ui.lineEdit_numberOfLevels->setText(QString::number(20));
};

void DialogContourLevels::accept()
{
	if (m_ui.lineEdit_minimunLevel->text() == "" || m_ui.lineEdit_maximumLevel->text() == "" || m_ui.lineEdit_numberOfLevels->text() == "")
	{
		QMessageBox::critical(this, "error", QString::fromUtf8("输入的参数不能为空"));
		return;
	}

	if (m_ui.lineEdit_maximumLevel->text().toFloat() < m_ui.lineEdit_minimunLevel->text().toFloat())
	{
		QMessageBox::critical(this, "error", QString::fromUtf8("输入的最大值不正"));
		return;
	}

	if (m_ui.lineEdit_numberOfLevels->text().toInt() == 0 || m_ui.lineEdit_numberOfLevels->text().toInt() == 1)
	{
		QMessageBox::critical(this, "error", QString::fromUtf8("level的数量不正"));
		return;
	}

	QDialog::accept();
}

void DialogContourLevels::onClickOK()
{
	if (m_ui.radioButton_exactLevels->isChecked())
	{
		m_levelCreationMode = 0;
	}
	else
	{
		m_levelCreationMode = 1;
	}

	if (m_ui.radioButton_range0->isChecked())
	{
		m_rangeDistribution = 0;
	}
	else if (m_ui.radioButton_range1->isChecked())
	{
		m_rangeDistribution = 1;
	}
	else
	{
		m_rangeDistribution = 2;
	}

	m_minLevel = m_ui.lineEdit_minimunLevel->text().toFloat();
	m_maxLevel = m_ui.lineEdit_maximumLevel->text().toFloat();
	m_numberOfLevel = m_ui.lineEdit_numberOfLevels->text().toFloat();
	m_delta = m_ui.lineEdit_delta->text().toFloat();
}

void DialogContourLevels::onClickExactLevels()
{
	m_ui.widget_rangeDistribution->show();
	m_ui.widget_minimunLevel->show();
	m_ui.widget_maximumLevel->show();
	m_ui.widget_delta->show();
	m_ui.pushButton_resetRange->show();

	if (m_ui.radioButton_range0->isChecked())
	{
		onClickRangeDistribution0();
	}
	else if (m_ui.radioButton_range1->isChecked())
	{
		onClickRangeDistribution1();
	}
	else if (m_ui.radioButton_range2->isChecked())
	{
		onClickRangeDistribution2();
	}
}

void DialogContourLevels::onClickApproximateLevels()
{
	m_ui.widget_rangeDistribution->hide();
	m_ui.widget_minimunLevel->hide();
	m_ui.widget_maximumLevel->hide();
	m_ui.widget_delta->hide();
	m_ui.pushButton_resetRange->hide();

	m_ui.lineEdit_numberOfLevels->setEnabled(true);
	m_ui.widget_numberofLevels->setGeometry(9, 85, m_ui.widget_numberofLevels->width(), m_ui.widget_numberofLevels->height());
}

void DialogContourLevels::onClickRangeDistribution0()
{
	m_ui.lineEdit_numberOfLevels->setEnabled(true);
	m_ui.lineEdit_delta->setEnabled(false);
	m_ui.pushButton_resetRange->setEnabled(true);
}

void DialogContourLevels::onClickRangeDistribution1()
{
	m_ui.lineEdit_numberOfLevels->setEnabled(false);
	m_ui.lineEdit_delta->setEnabled(true);
	m_ui.pushButton_resetRange->setEnabled(false);
}

void DialogContourLevels::onClickRangeDistribution2()
{
	m_ui.lineEdit_numberOfLevels->setEnabled(true);
	m_ui.lineEdit_delta->setEnabled(false);
	m_ui.pushButton_resetRange->setEnabled(false);
}

void DialogContourLevels::setValue(float minLevel, float maxLevel, float numberOfLevels, float delta)
{
	m_ui.lineEdit_minimunLevel->setText(QString::number(minLevel));
	m_ui.lineEdit_maximumLevel->setText(QString::number(maxLevel));
	m_ui.lineEdit_numberOfLevels->setText(QString::number(numberOfLevels));
	m_ui.lineEdit_delta->setText(QString::number(delta));
}

void DialogContourLevels::setValue(float minLevel, float maxLevel)
{
	m_defaultMinLevel = minLevel;
	m_defaultMaxLevel = maxLevel;
}
