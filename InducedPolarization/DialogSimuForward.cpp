#include "DialogSimuForward.h"
#include "GlobalClass/GlobalParam.h"
#include "QMessageBox"

DialogSimuForward::DialogSimuForward(QWidget *parent /*= nullptr*/) : QDialog(parent)
{
	m_ui.setupUi(this);

	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);

	m_invertBeginX = 0;
	m_invertEndX = 0;

	m_invertBeginY = 0;
	m_invertEndY = 0;

	m_invertBeginZ = 0;
	m_invertEndZ = 0;

	setValidator();
}

void DialogSimuForward::showEvent(QShowEvent *e)
{
	setData();

	QDialog::showEvent(e);
}

void DialogSimuForward::closeEvent(QCloseEvent *e)
{
	saveData();
	QDialog::closeEvent(e);
}

void DialogSimuForward::saveData()
{
	GlobalParam::PotentialDeviceSelectionSwitch selectionSwitch;
	if (m_ui.comboBox_selectionSwitch->currentText() == "Schlumberger")
	{
		selectionSwitch = GlobalParam::PotentialDeviceSelectionSwitch::Schlumberger;
	}
	else if (m_ui.comboBox_selectionSwitch->currentText() == "AMNB")
	{
		selectionSwitch = GlobalParam::PotentialDeviceSelectionSwitch::AMNB;
	}

	//数据保存
	GlobalParam::instance()->getForwardModelingParaSetting().saveSettingValue(selectionSwitch, m_ui.lineEdit_sgM0Value->text().toDouble(), m_ui.lineEdit_CII->text().toDouble(), m_ui.lineEdit_II->text().toDouble(),
		m_ui.lineEdit_currentINumX->text().toInt(), m_ui.lineEdit_currentINumY->text().toInt(), m_ui.lineEdit_currentINumZ->text().toInt());

	GlobalParam::instance()->getForwardModelingParaSetting().saveSimuForwardSettingValue(m_ui.lineEdit_inverX1->text().toInt(), m_ui.lineEdit_inverX2->text().toInt(),
		m_ui.lineEdit_inverY1->text().toInt(), m_ui.lineEdit_inverY2->text().toInt(),
		m_ui.lineEdit_inverZ1->text().toInt(), m_ui.lineEdit_inverZ2->text().toInt());
}

void DialogSimuForward::importData()
{

}

void DialogSimuForward::clearData()
{

}

void DialogSimuForward::onActualLocationXMaxChanged()
{
	if (m_invertBeginX > m_ui.lineEdit_inverX2->text().toInt() || m_invertEndX + 1 < m_ui.lineEdit_inverX2->text().toInt())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("超出范围"), QString::fromLocal8Bit("请输入反演区间的值，反演区间为%1到%2").arg(m_invertBeginX).arg(m_invertEndX));
		return;
	}

	m_ui.lineEdit_actual_end_x->setText(QString::number(getActualLocationValue(m_xlVector, m_invertBeginX, m_ui.lineEdit_inverX2->text().toInt()+1)));
	GlobalParam::instance()->getForwardModelingParaSetting().saveSimuForwardSettingActualValue(m_ui.lineEdit_actual_begin_x->text().toFloat(), m_ui.lineEdit_actual_end_x->text().toFloat(),
		m_ui.lineEdit_actual_begin_y->text().toFloat(), m_ui.lineEdit_actual_end_y->text().toFloat(),
		m_ui.lineEdit_actual_begin_z->text().toFloat(), m_ui.lineEdit_actual_end_z->text().toFloat());

	emit textChanged();
}

void DialogSimuForward::onActualLocationYMaxChanged()
{
	if (m_invertBeginY > m_ui.lineEdit_inverY2->text().toInt() || m_invertEndY + 1 < m_ui.lineEdit_inverY2->text().toInt())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("超出范围"), QString::fromLocal8Bit("请输入反演区间的值，反演区间为%1到%2").arg(m_invertBeginY).arg(m_invertEndY));
		return;
	}

	m_ui.lineEdit_actual_end_y->setText(QString::number(getActualLocationValue(m_ylVector, m_invertBeginY, m_ui.lineEdit_inverY2->text().toInt()+1)));
	GlobalParam::instance()->getForwardModelingParaSetting().saveSimuForwardSettingActualValue(m_ui.lineEdit_actual_begin_x->text().toFloat(), m_ui.lineEdit_actual_end_x->text().toFloat(),
		m_ui.lineEdit_actual_begin_y->text().toFloat(), m_ui.lineEdit_actual_end_y->text().toFloat(),
		m_ui.lineEdit_actual_begin_z->text().toFloat(), m_ui.lineEdit_actual_end_z->text().toFloat());

	emit textChanged();
}

void DialogSimuForward::onActualLocationZMaxChanged()
{
	if (m_invertBeginZ > m_ui.lineEdit_inverZ2->text().toInt() || m_invertEndZ + 1 < m_ui.lineEdit_inverZ2->text().toInt())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("超出范围"), QString::fromLocal8Bit("请输入反演区间的值，反演区间为%1到%2").arg(m_invertBeginZ).arg(m_invertEndZ));
		return;
	}

	m_ui.lineEdit_actual_end_z->setText(QString::number(getActualLocationValue(m_zlVector, m_invertBeginZ, m_ui.lineEdit_inverZ2->text().toInt()+1)));
	GlobalParam::instance()->getForwardModelingParaSetting().saveSimuForwardSettingActualValue(m_ui.lineEdit_actual_begin_x->text().toFloat(), m_ui.lineEdit_actual_end_x->text().toFloat(),
		m_ui.lineEdit_actual_begin_y->text().toFloat(), m_ui.lineEdit_actual_end_y->text().toFloat(),
		m_ui.lineEdit_actual_begin_z->text().toFloat(), m_ui.lineEdit_actual_end_z->text().toFloat());

	emit textChanged();
}

void DialogSimuForward::onActualLocationXMinChanged()
{
	if (m_invertBeginX > m_ui.lineEdit_inverX1->text().toInt() || m_invertEndX + 1 < m_ui.lineEdit_inverX1->text().toInt())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("超出范围"), QString::fromLocal8Bit("请输入反演区间的值，反演区间为%1到%2").arg(m_invertBeginX).arg(m_invertEndX));
		return;
	}

	m_ui.lineEdit_actual_begin_x->setText(QString::number(getActualLocationValue(m_xlVector, m_invertBeginX, m_ui.lineEdit_inverX1->text().toInt())));
	GlobalParam::instance()->getForwardModelingParaSetting().saveSimuForwardSettingActualValue(m_ui.lineEdit_actual_begin_x->text().toFloat(), m_ui.lineEdit_actual_end_x->text().toFloat(),
		m_ui.lineEdit_actual_begin_y->text().toFloat(), m_ui.lineEdit_actual_end_y->text().toFloat(),
		m_ui.lineEdit_actual_begin_z->text().toFloat(), m_ui.lineEdit_actual_end_z->text().toFloat());

	emit textChanged();
}

void DialogSimuForward::onActualLocationYMinChanged()
{
	if (m_invertBeginY > m_ui.lineEdit_inverY1->text().toInt() || m_invertEndY + 1 < m_ui.lineEdit_inverY1->text().toInt())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("超出范围"), QString::fromLocal8Bit("请输入反演区间的值，反演区间为%1到%2").arg(m_invertBeginY).arg(m_invertEndY));
		return;
	}

	m_ui.lineEdit_actual_begin_y->setText(QString::number(getActualLocationValue(m_ylVector, m_invertBeginY, m_ui.lineEdit_inverY1->text().toInt())));
	GlobalParam::instance()->getForwardModelingParaSetting().saveSimuForwardSettingActualValue(m_ui.lineEdit_actual_begin_x->text().toFloat(), m_ui.lineEdit_actual_end_x->text().toFloat(),
		m_ui.lineEdit_actual_begin_y->text().toFloat(), m_ui.lineEdit_actual_end_y->text().toFloat(),
		m_ui.lineEdit_actual_begin_z->text().toFloat(), m_ui.lineEdit_actual_end_z->text().toFloat());

	emit textChanged();
}

void DialogSimuForward::onActualLocationZMinChanged()
{
	if (m_invertBeginZ > m_ui.lineEdit_inverZ1->text().toInt() || m_invertEndZ + 1 < m_ui.lineEdit_inverZ1->text().toInt())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("超出范围"), QString::fromLocal8Bit("请输入反演区间的值，反演区间为%1到%2").arg(m_invertBeginZ).arg(m_invertEndZ));
		return;
	}

	m_ui.lineEdit_actual_begin_z->setText(QString::number(getActualLocationValue(m_zlVector, m_invertBeginZ, m_ui.lineEdit_inverZ1->text().toInt())));
	GlobalParam::instance()->getForwardModelingParaSetting().saveSimuForwardSettingActualValue(m_ui.lineEdit_actual_begin_x->text().toFloat(), m_ui.lineEdit_actual_end_x->text().toFloat(),
		m_ui.lineEdit_actual_begin_y->text().toFloat(), m_ui.lineEdit_actual_end_y->text().toFloat(),
		m_ui.lineEdit_actual_begin_z->text().toFloat(), m_ui.lineEdit_actual_end_z->text().toFloat());

	emit textChanged();
}

float DialogSimuForward::getActualLocationValue(const vector<double>& l, unsigned int begin, unsigned int end)
{
	if (l.size() <= begin || l.size() <= end)
	{
		//throw std::logic_error("Out Of Range,Hao");
		return 0.0f;
	}

	float value = 0.0f;

	for (unsigned int i = begin;i < end;i++)
	{
		value += l[i];
	}

	return value;
}

void DialogSimuForward::setValidator()
{
	m_ui.lineEdit_currentINumX->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_currentINumY->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_currentINumZ->setValidator(new QIntValidator(0, 999999, this));

	m_ui.lineEdit_inverX1->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_inverX2->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_inverY1->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_inverY2->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_inverZ1->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_inverZ2->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_actual_begin_x->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_actual_begin_y->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_actual_begin_z->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_actual_end_x->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_actual_end_y->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_actual_end_z->setValidator(new QIntValidator(0, 999999, this));

	QRegExp double_rx("10000|([0-9]{0,4}[\.][0-9]{1,4})");

	m_ui.lineEdit_sgM0Value->setValidator(new QRegExpValidator(double_rx, this));
	m_ui.lineEdit_CII->setValidator(new QRegExpValidator(double_rx, this));
	m_ui.lineEdit_II->setValidator(new QRegExpValidator(double_rx, this));
}

void DialogSimuForward::setData()
{
	//得到正演参数的设置值
	GlobalParam::ForwardModelingParaSetting& setting = GlobalParam::instance()->getForwardModelingParaSetting();

	//只有正演参数对话框被打开的场合，才进行以下操作
	if (true)
	{
		//正演参数对话框的值设置到模拟正演对话框中
		int index = setting.potentialDeviceSelectionSwitch;
		m_ui.comboBox_selectionSwitch->setCurrentIndex(index);
		m_ui.lineEdit_sgM0Value->setText(QString::number(setting.sgM0Value));
		m_ui.lineEdit_CII->setText(QString::number(setting.CII));
		m_ui.lineEdit_II->setText(QString::number(setting.II));
		m_ui.lineEdit_currentINumX->setText(QString::number(setting.currentINumX));
		m_ui.lineEdit_currentINumY->setText(QString::number(setting.currentINumY));
		m_ui.lineEdit_currentINumZ->setText(QString::number(setting.faceZInModel + 1));
		m_ui.lineEdit_inverX1->setText(QString::number(setting.inverX1));
		m_ui.lineEdit_inverX2->setText(QString::number(setting.inverX2));
		m_ui.lineEdit_inverY1->setText(QString::number(setting.inverY1));
		m_ui.lineEdit_inverY2->setText(QString::number(setting.inverY2));
		m_ui.lineEdit_inverZ1->setText(QString::number(setting.inverZ1));
		m_ui.lineEdit_inverZ2->setText(QString::number(setting.inverZ2));
		m_ui.lineEdit_actual_begin_x->setText(QString::number(getActualLocationValue(m_xlVector, m_invertBeginX, m_ui.lineEdit_inverX1->text().toInt())));
		m_ui.lineEdit_actual_end_x->setText(QString::number(getActualLocationValue(m_xlVector, m_invertBeginX, m_ui.lineEdit_inverX2->text().toInt() + 1)));
		m_ui.lineEdit_actual_begin_y->setText(QString::number(getActualLocationValue(m_ylVector, m_invertBeginY, m_ui.lineEdit_inverY1->text().toInt())));
		m_ui.lineEdit_actual_end_y->setText(QString::number(getActualLocationValue(m_ylVector, m_invertBeginY, m_ui.lineEdit_inverY2->text().toInt() + 1)));
		m_ui.lineEdit_actual_begin_z->setText(QString::number(getActualLocationValue(m_zlVector, m_invertBeginZ, m_ui.lineEdit_inverZ1->text().toInt())));
		m_ui.lineEdit_actual_end_z->setText(QString::number(getActualLocationValue(m_zlVector, m_invertBeginZ, m_ui.lineEdit_inverZ2->text().toInt() + 1)));

		GlobalParam::instance()->getForwardModelingParaSetting().saveSimuForwardSettingActualValue(getActualLocationValue(m_xlVector, m_invertBeginX, m_ui.lineEdit_inverX1->text().toInt()), getActualLocationValue(m_xlVector, m_invertBeginX, m_ui.lineEdit_inverX2->text().toInt() + 1),
			getActualLocationValue(m_ylVector, m_invertBeginY, m_ui.lineEdit_inverY1->text().toInt()), getActualLocationValue(m_ylVector, m_invertBeginY, m_ui.lineEdit_inverY2->text().toInt() + 1),
			getActualLocationValue(m_zlVector, m_invertBeginZ, m_ui.lineEdit_inverZ1->text().toInt()), getActualLocationValue(m_zlVector, m_invertBeginZ, m_ui.lineEdit_inverZ2->text().toInt() + 1));

		emit textChanged();
	}
}