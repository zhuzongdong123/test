#include "DialogModeling.h"
#include "GlobalClass/GlobalParam.h"

DialogModeling::DialogModeling(QWidget *parent /*= nullptr*/) : QDialog(parent)
{
    m_ui.setupUi(this);

	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);
	m_isAutoModeling = true;
	initTable();
	setValidator();
}

DialogModeling::~DialogModeling()
{
	
}

void DialogModeling::doModel()
{
	//自动化建模的场合
	if (m_isAutoModeling)
	{
		m_ui.widget->doModel();

		//模型创建成功的场合
		if (m_ui.widget->getCreatFlag())
		{
			emit creatModelData(false, true, tr("建模"));
		}

		m_XLVector = m_ui.widget->getXLVector();
		m_YLVector = m_ui.widget->getYLVector();
		m_ZLVector = m_ui.widget->getZLVector();
		importData(m_XLVector, m_YLVector, m_ZLVector);
		importPara();
		m_isAutoModeling = false;
	}
}

void DialogModeling::clearModel()
{
	m_ui.widget->clearModel();
}

void DialogModeling::resizeEvent(QResizeEvent *e)
{
	m_ui.widget_2->setGeometry(m_ui.widget->width()-100,10, m_ui.widget_2->width(), m_ui.widget_2->height());
	QDialog::resizeEvent(e);
}

void DialogModeling::showEvent(QShowEvent *e)
{
	m_ui.widget_2->setGeometry(m_ui.widget->width() - 100, 10, m_ui.widget_2->width(), m_ui.widget_2->height());
	QDialog::showEvent(e);
}

unsigned int DialogModeling::getInvertBeginAreaX()
{
	return m_ui.lineEdit_invert_begin_x->text().toUInt();
}

unsigned int DialogModeling::getInvertEndAreaX()
{
	return m_ui.lineEdit_invert_end_x->text().toUInt();
}

unsigned int DialogModeling::getInvertBeginAreaY()
{
	return m_ui.lineEdit_invert_begin_y->text().toUInt();
}

unsigned int DialogModeling::getInvertEndAreaY()
{
	return m_ui.lineEdit_invert_end_y->text().toUInt();
}

unsigned int DialogModeling::getInvertBeginAreaZ()
{
	return m_ui.lineEdit_invert_begin_z->text().toUInt();
}

unsigned int DialogModeling::getInvertEndAreaZ()
{
	return m_ui.lineEdit_invert_end_z->text().toUInt();
}

//初始化表格
void DialogModeling::initTable()
{
	m_ui.tableWidget_modelData->setRowCount(300);
	m_ui.tableWidget_modelData->setColumnCount(4);
	m_ui.tableWidget_modelData->setWindowTitle(QString::fromUtf8("数据调整"));

	QStringList header;
	header << "编号"
		<< "X"
		<< "Y"
		<< "Z";

	m_ui.tableWidget_modelData->setHorizontalHeaderLabels(header);
	m_ui.tableWidget_modelData->verticalHeader()->setVisible(false);

	QFont font = m_ui.tableWidget_modelData->horizontalHeader()->font();
	font.setBold(true);
	m_ui.tableWidget_modelData->horizontalHeader()->setFont(font);

	m_ui.tableWidget_modelData->horizontalHeader()->setStretchLastSection(true);
	m_ui.tableWidget_modelData->verticalHeader()->setDefaultSectionSize(20);
	m_ui.tableWidget_modelData->setSelectionMode(QAbstractItemView::ExtendedSelection);
	m_ui.tableWidget_modelData->horizontalHeader()->resizeSection(0, 80);
	m_ui.tableWidget_modelData->horizontalHeader()->resizeSection(1, 150);
	m_ui.tableWidget_modelData->horizontalHeader()->resizeSection(2, 150);
	m_ui.tableWidget_modelData->horizontalHeader()->resizeSection(3, 150);
	m_ui.tableWidget_modelData->horizontalHeader()->setFixedHeight(25);

	m_ui.tableWidget_modelData->setStyleSheet("selection-background-color:lightblue;");
	m_ui.tableWidget_modelData->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
	m_ui.tableWidget_modelData->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_ui.groupBox->setEnabled(false);
	m_ui.tableWidget_modelData->setLockState(true);

}

void DialogModeling::importData(std::vector<double> vectorX, std::vector<double> vectorY, std::vector<double> vectorZ)
{
	m_ui.tableWidget_modelData->clearContents();

	for (size_t i = 0; i < m_ui.tableWidget_modelData->rowCount(); i++)
	{
		if (i >= vectorX.size() && i >= vectorY.size() && i >= vectorZ.size())
		{
			break;
		}

		m_ui.tableWidget_modelData->removeCellWidget(i, 0);
		m_ui.tableWidget_modelData->setItem(i, 0, new QTableWidgetItem(tr("编号") + QString::number(i)));

		if (i < vectorX.size())
		{
			m_ui.tableWidget_modelData->removeCellWidget(i, 1);
			m_ui.tableWidget_modelData->setItem(i, 1, new QTableWidgetItem(QString::number(vectorX[i])));
		}

		if (i < vectorY.size())
		{
			m_ui.tableWidget_modelData->removeCellWidget(i, 2);
			m_ui.tableWidget_modelData->setItem(i, 2, new QTableWidgetItem(QString::number(vectorY[i])));
		}

		if (i < vectorZ.size())
		{
			m_ui.tableWidget_modelData->removeCellWidget(i, 3);
			m_ui.tableWidget_modelData->setItem(i, 3, new QTableWidgetItem(QString::number(vectorZ[i])));
		}
	}

}

void DialogModeling::importPara()
{
	m_ui.lineEdit_invert_begin_x->setText(QString::number(m_ui.widget->getInvertionXBeg()));
	m_ui.lineEdit_invert_end_x->setText(QString::number(m_ui.widget->getInvertionXEnd()));
	m_ui.lineEdit_invert_begin_y->setText(QString::number(m_ui.widget->getInvertionYBeg()));
	m_ui.lineEdit_invert_end_y->setText(QString::number(m_ui.widget->getInvertionYEnd()));
	m_ui.lineEdit_TunnelCavityXBegin->setText(QString::number(m_ui.widget->getTunnelCavityXBegin()));
	m_ui.lineEdit_TunnelCavityXEnd->setText(QString::number(m_ui.widget->getTunnelCavityXEnd()));
	m_ui.lineEdit_TunnelCavityYBegin->setText(QString::number(m_ui.widget->getTunnelCavityYBegin()));
	m_ui.lineEdit_TunnelCavityYEnd->setText(QString::number(m_ui.widget->getTunnelCavityYEnd()));
	m_ui.lineEdit_invert_begin_z->setText(QString::number(m_ui.widget->getTunnelForZBeg()));
	m_ui.lineEdit_invert_end_z->setText(QString::number(m_ui.widget->getTunnelForZEnd()));

	std::vector<osg::Vec2> XYIndexVec = m_ui.widget->getMeasXYIndexVec();
	if (XYIndexVec.size() != 0 )
	{
		std::vector<osg::Vec2> XYIndexVecTemp;
		XYIndexVecTemp = XYIndexVec;
		std::sort(begin(XYIndexVecTemp), end(XYIndexVecTemp), [](const osg::Vec2 &lhs, const osg::Vec2 &rhs)
		{
			return lhs.x() < rhs.x();
		});
		m_ui.lineEdit_MeasuringElectrode_begin_x->setText(QString::number(XYIndexVecTemp[0].x()));
		m_ui.lineEdit_MeasuringElectrode_end_x->setText(QString::number(XYIndexVecTemp[XYIndexVecTemp.size()-1].x()));

		XYIndexVecTemp = XYIndexVec;
		std::sort(begin(XYIndexVecTemp), end(XYIndexVecTemp), [](const osg::Vec2 &lhs, const osg::Vec2 &rhs)
		{
			return lhs.y() < rhs.y();
		});
		m_ui.lineEdit_MeasuringElectrode_begin_y->setText(QString::number(XYIndexVecTemp[0].y()));
		m_ui.lineEdit_MeasuringElectrode_end_y->setText(QString::number(XYIndexVecTemp[XYIndexVecTemp.size()-1].y()));
	}
}

void DialogModeling::setValidator()
{
	m_ui.lineEdit_invert_begin_x->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_invert_end_x->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_invert_begin_y->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_invert_end_y->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_TunnelCavityXBegin->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_TunnelCavityXEnd->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_TunnelCavityYBegin->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_TunnelCavityYEnd->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_invert_begin_z->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_invert_end_z->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_MeasuringElectrode_begin_x->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_MeasuringElectrode_end_x->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_MeasuringElectrode_begin_y->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_MeasuringElectrode_end_y->setValidator(new QIntValidator(0, 999999, this));
}

//编辑
void DialogModeling::editData()
{
	m_ui.pushButton_edit->setEnabled(false);
	m_ui.pushButton_update->setEnabled(true);
	m_ui.tableWidget_modelData->setLockState(false);
	m_ui.tableWidget_modelData->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
	m_ui.groupBox->setEnabled(true);
}

//更新建模参数
void DialogModeling::updateParaData()
{
	std::vector<double> tmpXL;
	std::vector<double> tmpYL;
	std::vector<double> tmpZL;

	for (int i = 0; i < m_ui.tableWidget_modelData->rowCount(); i++)
	{
		for (int j = 0; j < m_ui.tableWidget_modelData->columnCount(); j++)
		{
			if (m_ui.tableWidget_modelData->item(i, j) == NULL
				|| m_ui.tableWidget_modelData->item(i, j)->text() == "")
				continue;

			if (0 == j)
			{
				continue;
			}
			else if (1 == j)
			{
				double tmpXValue = m_ui.tableWidget_modelData->item(i, j)->text().toDouble();
				tmpXL.push_back(tmpXValue);
			}
			else if (2 == j)
			{
				double tmpYValue = m_ui.tableWidget_modelData->item(i, j)->text().toDouble();
				tmpYL.push_back(tmpYValue);
			}
			else if (3 == j)
			{
				double tmpZValue = m_ui.tableWidget_modelData->item(i, j)->text().toDouble();
				tmpZL.push_back(tmpZValue);
			}
		}
	}

	m_XLVector = tmpXL;
	m_YLVector = tmpYL;
	m_ZLVector = tmpZL;
	importData(m_XLVector, m_YLVector, m_ZLVector);

	m_ui.widget->setXLVector(tmpXL);
	m_ui.widget->setYLVector(tmpYL);
	m_ui.widget->setZLVector(tmpZL);
}

//更新
void DialogModeling::updateData()
{
	m_ui.pushButton_edit->setEnabled(true);
	m_ui.pushButton_update->setEnabled(false);
	m_ui.tableWidget_modelData->setLockState(true);
	m_ui.tableWidget_modelData->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_ui.groupBox->setEnabled(false);
	m_isAutoModeling = false;
	//更新参数，重新绘制
	updateParaData();
	m_ui.widget->initModelParameter(m_ui.lineEdit_invert_begin_x->text().toInt(), m_ui.lineEdit_invert_end_x->text().toInt(), m_ui.lineEdit_invert_begin_y->text().toInt(), m_ui.lineEdit_invert_end_y->text().toInt(),
		m_ui.lineEdit_TunnelCavityXBegin->text().toInt(), m_ui.lineEdit_TunnelCavityXEnd->text().toInt(), m_ui.lineEdit_TunnelCavityYBegin->text().toInt(), m_ui.lineEdit_TunnelCavityYEnd->text().toInt(),
		m_ui.lineEdit_invert_begin_z->text().toInt(), m_ui.lineEdit_invert_end_z->text().toInt());

	m_ui.widget->initMeasurePointParam(m_ui.lineEdit_MeasuringElectrode_begin_x->text().toInt(), m_ui.lineEdit_MeasuringElectrode_end_x->text().toInt(),
		m_ui.lineEdit_MeasuringElectrode_begin_y->text().toInt(), m_ui.lineEdit_MeasuringElectrode_end_y->text().toInt());
	
	m_ui.widget->updateModel();

	//模型创建成功的场合
	if (m_ui.widget->getCreatFlag())
	{
		emit creatModelData(false, true, tr("建模"));
	}
}

void DialogModeling::invertBeginZTextChanged(QString text)
{
	GlobalParam::instance()->getForwardModelingParaSetting().saveSimuForwardSettingInverZ1Value(text.toInt());
}