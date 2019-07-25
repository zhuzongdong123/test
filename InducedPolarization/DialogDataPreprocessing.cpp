#include "DialogDataPreprocessing.h"
#include <QtWidgets/QApplication>
#include "GlobalClass/DataManager.h"
#include <QtWidgets/QMessageBox>
#include "../osg/Vec4d"
#include "QAbstractItemView"
#include "../3ddisplay/dataPreProcess/dataPreProcess.h"
#include "QTableWidget"
#include "GlobalClass/GlobalParam.h"

DialogDataPreprocessing::DialogDataPreprocessing(QWidget *parent /*= Q_NULLPTR*/)
{
    m_defaultTableHeight = 100;
    m_ui.setupUi(this);

    m_ui.tableWidgetRemovePoint->setEditTriggers(QAbstractItemView::NoEditTriggers);

    if (!initRemovePointsTable())
    {
        return;
    }

    if (!initDataExtractionTable())
    {
        return;
    }

	QObject::connect(m_ui.tableWidget_2->getPickHandle(), SIGNAL(updateAdjustData()), this, SLOT(updateAdjustData()));
	QObject::connect(m_ui.tableWidget_2, SIGNAL(reDraw()), this, SLOT(importAllData()));
}

DialogDataPreprocessing::~DialogDataPreprocessing()
{
}

bool DialogDataPreprocessing::initRemovePointsTable()
{
    //m_ui.tableWidgetRemovePoint->clear();

    m_ui.tableWidgetRemovePoint->setRowCount(300);
    m_ui.tableWidgetRemovePoint->setColumnCount(6);
    m_ui.tableWidgetRemovePoint->setWindowTitle(QString::fromUtf8("网格大小设置"));

    QStringList header;
    header << "编号"
		   << "A1"
           << "A2"
           << "A3"
           << "A4"
           << "Avg";

    m_ui.tableWidgetRemovePoint->setHorizontalHeaderLabels(header);
    m_ui.tableWidgetRemovePoint->verticalHeader()->setVisible(false);

    QFont font = m_ui.tableWidgetRemovePoint->horizontalHeader()->font();
    font.setBold(true);
    m_ui.tableWidgetRemovePoint->horizontalHeader()->setFont(font);

    m_ui.tableWidgetRemovePoint->horizontalHeader()->setStretchLastSection(true);
    m_ui.tableWidgetRemovePoint->verticalHeader()->setDefaultSectionSize(20);
    m_ui.tableWidgetRemovePoint->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_ui.tableWidgetRemovePoint->horizontalHeader()->resizeSection(0, 80);
    m_ui.tableWidgetRemovePoint->horizontalHeader()->resizeSection(1, 80);
    m_ui.tableWidgetRemovePoint->horizontalHeader()->resizeSection(2, 80);
	m_ui.tableWidgetRemovePoint->horizontalHeader()->resizeSection(3, 80);
    m_ui.tableWidgetRemovePoint->horizontalHeader()->setFixedHeight(25);

    m_ui.tableWidgetRemovePoint->setStyleSheet("selection-background-color:lightblue;");
    m_ui.tableWidgetRemovePoint->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");

    //m_simuPointTableDataVec.clear();

    //     for (unsigned int i = 0; i < 300; i++)
    //     {
    //         for (unsigned int j = 0; j < 5; j++)
    //         {
    //             auto p = new QTableWidgetItem("");
    //             m_ui.tableWidgetRemovePoint->setItem(i, j, p);
    //         }
    //     }

    return true;
}

bool DialogDataPreprocessing::initDataExtractionTable()
{
    m_ui.tableWidgetDataExtraction->setRowCount(m_defaultTableHeight);
    m_ui.tableWidgetDataExtraction->setColumnCount(2);
    m_ui.tableWidgetDataExtraction->setWindowTitle(QString::fromUtf8("正演数据结果"));

    QStringList header;
    header << " 编号 "
           << "Data";

    m_ui.tableWidgetDataExtraction->setHorizontalHeaderLabels(header);
    m_ui.tableWidgetDataExtraction->verticalHeader()->setVisible(false);

    QFont font = m_ui.tableWidgetDataExtraction->horizontalHeader()->font();
    font.setBold(true);
    m_ui.tableWidgetDataExtraction->horizontalHeader()->setFont(font);

    m_ui.tableWidgetDataExtraction->horizontalHeader()->setStretchLastSection(true);
    m_ui.tableWidgetDataExtraction->verticalHeader()->setDefaultSectionSize(20);
    m_ui.tableWidgetDataExtraction->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_ui.tableWidgetDataExtraction->horizontalHeader()->resizeSection(0, m_defaultTableHeight);
    m_ui.tableWidgetDataExtraction->horizontalHeader()->resizeSection(1, 205);
    // 	m_ui.tableWidgetDataExtraction->horizontalHeader()->resizeSection(2, 105);
    m_ui.tableWidgetDataExtraction->horizontalHeader()->setFixedHeight(25);

    m_ui.tableWidgetDataExtraction->setStyleSheet("selection-background-color:lightblue;");
    m_ui.tableWidgetDataExtraction->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    for (unsigned int i = 0; i < m_defaultTableHeight; i++)
    {
        for (unsigned int j = 0; j < 2; j++)
        {
            auto p = new QTableWidgetItem("");
            m_ui.tableWidgetDataExtraction->setItem(i, j, p);
        }
    }

	m_ui.tableWidgetDataExtraction->resizeColumnsToContents();
	m_ui.tableWidgetDataExtraction->resizeRowsToContents();

    return true;
}

void DialogDataPreprocessing::saveSupplyTableData()
{
	DataManager::DataList &dataList = DataManager::instance()->getDataListRef();

	dataList.clear();

	unsigned int rowCount = 0;

	while (QTableWidgetItem* item = m_ui.tableWidgetRemovePoint->item(rowCount, 0))
	{
		rowCount++;
	}

	m_ui.pushButton_measuring_edit->setEnabled(true);
	m_ui.pushButton_measuring_update->setEnabled(false);
	m_ui.tableWidgetRemovePoint->setLockState(true);
	m_ui.tableWidgetRemovePoint->setEditTriggers(QAbstractItemView::NoEditTriggers);

	vector<osg::Vec4d> &syncList = GlobalParam::instance()->getDataPreProcessInfo().badPointsList;
	syncList.clear();

	shared_ptr<DataManager::DataInfo> dataInfo = shared_ptr<DataManager::DataInfo>(new DataManager::DataInfo);
	memset(dataInfo.get(), 0, sizeof(DataManager::DataInfo));

	dataInfo->data = new double*[rowCount];
	memset(dataInfo->data, 0, sizeof(double*) * rowCount);

	for (unsigned int i = 0; i < rowCount; i++)
	{
		dataInfo->data[i] = new double[4];
		memset(dataInfo->data[i], 0, sizeof(double) * 4);
	}

	dataInfo->col = 4;

	for (int i = 0; i < rowCount; i++)
	{
		QString v1 = m_ui.tableWidgetRemovePoint->item(i, 1)->text();
		QString v2 = m_ui.tableWidgetRemovePoint->item(i, 2)->text();
		QString v3 = m_ui.tableWidgetRemovePoint->item(i, 3)->text();
		QString v4 = m_ui.tableWidgetRemovePoint->item(i, 4)->text();

		dataInfo->data[i][0] = v1.toDouble();
		dataInfo->data[i][1] = v2.toDouble();
		dataInfo->data[i][2] = v3.toDouble();
		dataInfo->data[i][3] = v4.toDouble();

		dataInfo->row = i + 1;
	}

	dataList.push_back(dataInfo);

	importAllData();
}

void DialogDataPreprocessing::onSupplyEditClick()
{
    m_ui.pushButton_measuring_edit->setEnabled(false);
    m_ui.pushButton_measuring_update->setEnabled(true);

    m_ui.tableWidgetRemovePoint->setLockState(false);
    m_ui.tableWidgetRemovePoint->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
}

void DialogDataPreprocessing::onSupplyUpdateClick()
{
	saveSupplyTableData();
}

void DialogDataPreprocessing::onObserveDataLoaded()
{
	importAllData();
}

void DialogDataPreprocessing::updateForwardDataTable(std::vector<double> vecResult)
{
	if (vecResult.size() == 0)	return;

	DataManager::instance()->setObserveDataList(vecResult);
	importAllData();
}

void DialogDataPreprocessing::importAllData()
{
	DataManager::DataList& dataList = DataManager::instance()->getDataListRef();				//取实测数据
	const vector<double>& observeDataList = DataManager::instance()->getObserveDataList();		//取正演数据

	//清空建模所有数据
	m_ui.tableWidgetRemovePoint->clearContents();
	m_ui.tableWidgetDataExtraction->clearContents();
	m_ui.tableWidget_2->clearLinesData();
	m_ui.pushButton_V->reDraw(0, 0, "");
	m_ui.pushButton_H->reDraw(0);
	m_simuPointTableDataVec.clear();	//实测数据
	m_measureTableDataVec.clear();		//正演数据
	m_adjustmentDataVec.clear();		//调整数据
	m_maxValue = 0.0;

	//导入实测数据到表格中
	unsigned rowIndex = 0;
	for (unsigned int z = 0; z < dataList.size(); z++)
	{
		shared_ptr<DataManager::DataInfo> info = dataList[z];

		for (unsigned int j = 0; j < info->row; j++)
		{
			for (unsigned int i = 0; i < 6; i++)
			{
				double value = 0.0;

				if (0 == i)
				{
					//设置编号
					m_ui.tableWidgetRemovePoint->removeCellWidget(rowIndex, 0);
					m_ui.tableWidgetRemovePoint->setItem(rowIndex, 0, new QTableWidgetItem(tr("编号") + QString::number(rowIndex + 1)));
					continue;
				}

				if (5 == i)
				{
					int count = 0;
					for (size_t k = 0; k < 4; k++)
					{
						if (fabs(info->data[j][k]) > 1e-17)
						{
							count++;
						}
					}

					if (count != 0)
					{ 
						value = (info->data[j][0] + info->data[j][1] + info->data[j][2] + info->data[j][3]) / count;
					}
					else
					{
						value = 0;
					}									
					
					m_simuPointTableDataVec.push_back(value);

					//求最大值
					if (value > m_maxValue)
					{
						m_maxValue = value;
					}
				}
				else
				{
					value = info->data[j][i - 1];
				}

				QString str = QString::number(value);

				auto p = new QTableWidgetItem(str);
				if (5 == i)
				{
					p->setFlags(Qt::ItemIsEnabled);
				}
				m_ui.tableWidgetRemovePoint->removeCellWidget(j + z * info->row, i);
				m_ui.tableWidgetRemovePoint->setItem(j + z * info->row, i, p);
			}

			rowIndex++;
		}
	}

	//导入正演数据到表格中
	for (unsigned int j = 0; j < observeDataList.size(); j++)
	{
		for (unsigned int i = 0; i < 2; i++)
		{
			double value = observeDataList[j];

			QString str = QString::number(value);

			auto p = new QTableWidgetItem(str);
			if (0 == i)
			{
				p->setFlags(Qt::ItemIsEnabled);
				m_ui.tableWidgetDataExtraction->setItem(j, 0, new QTableWidgetItem(tr("编号") + QString::number(j + 1)));
				continue;
			}

			m_ui.tableWidgetDataExtraction->setItem(j, i, p);

			//求最大值
			if (value > m_maxValue)
			{
				m_maxValue = value;
			}
		}
	}

	m_ui.tableWidget_2->setMaxValue(m_maxValue);

	//正演数据和实测数据都存在的时候，绘制调整数据的曲线
	if (observeDataList.size() != 0 && m_simuPointTableDataVec.size() != 0)
	{
		m_adjustmentDataVec = getMeasuredDataTranslationValue(m_simuPointTableDataVec, observeDataList);
		m_ui.tableWidget_2->setMaxValue(m_maxValue);
		m_ui.tableWidget_2->draw(m_adjustmentDataVec, osg::Vec4d(0.0, 1.0, 0.0, 1.0), DataType::ajustData);

		//更新坐标轴
		m_ui.pushButton_V->reDraw(0, m_ui.tableWidget_2->getMaxValue(), "");
		m_ui.pushButton_H->reDraw(m_ui.tableWidget_2->getMaxWidth());

		//更新dat数据
		emit updateDatData();
	}

	//正演数据存在的时候，绘制曲线
	if (observeDataList.size() != 0)
	{
		m_measureTableDataVec = observeDataList;
		m_ui.tableWidget_2->draw(observeDataList, osg::Vec4d(1.0, 0.0, 0.0, 1.0), DataType::simulationData);

		//更新坐标轴
		m_ui.pushButton_V->reDraw(0,m_ui.tableWidget_2->getMaxValue(),"");
		m_ui.pushButton_H->reDraw(m_ui.tableWidget_2->getMaxWidth());
	}

	//实测数据存在的时候，绘制曲线
	if (m_simuPointTableDataVec.size() != 0)
	{
		m_ui.tableWidget_2->draw(m_simuPointTableDataVec, osg::Vec4d(0.0, 0, 1.0, 1.0), DataType::measuredData);

		//更新坐标轴
		m_ui.pushButton_V->reDraw(0,m_ui.tableWidget_2->getMaxValue(),"");
		m_ui.pushButton_H->reDraw(m_ui.tableWidget_2->getMaxWidth());
	}
}

/***************************************************************************************/
//function:调整数据顶点值
void DialogDataPreprocessing::updateAdjustData()
{
	std::vector<float> adjustYVec = m_ui.tableWidget_2->adjustPointYValue();
	for (int i = 0 ; i < adjustYVec.size(); i ++)
	{
		m_adjustmentDataVec[i] = adjustYVec[i];
	}
	//更新dat数据
	emit updateDatData();
}

void DialogDataPreprocessing::resetData()
{
    //initRemovePointsTable();
}

void DialogDataPreprocessing::searchPoints(std::vector<double> resultSet, double &effectiveStartValue, double &effectiveEndValue)
{
    double value_2_1, value_4_1, value_4_3;

    //自动排序
    std::sort(begin(resultSet), end(resultSet));

    vector<double>::iterator it;
    int size = resultSet.size();

    //求中间点(1/2)的值
    if (size % 2 == 0)
    {
        int key   = size / 2;
        value_2_1 = (resultSet[key] + resultSet[key - 1]) / 2;
    }
    else
    {
        int key   = (size - 1) / 2;
        value_2_1 = resultSet[key];
    }

    //求(1/4)和(3/4)的值
    if (size % 4 == 0)
    {
        int key = size / 4;
        key--;
        value_4_1 = resultSet[key];

        key = size * 3 / 4;
        key--;
        value_4_3 = resultSet[key];
    }
    else
    {
        float keyF = float(size) / 4;
        int key = size / 4;
        if (keyF - key >= 0.5)
        {
            key++;
        }
        key--;
        value_4_1 = resultSet[key];

        keyF = float(size * 3) / 4;
        key = float(size * 3) / 4;
        if (keyF - key >= 0.5)
        {
            key++;
        }
        key--;
        value_4_3 = resultSet[key];
    }

    effectiveStartValue = value_2_1 - (value_4_3 - value_4_1);
    effectiveEndValue   = value_2_1 + (value_4_3 - value_4_1);
}

//vector1是实测数据，vector2是模拟数据
std::vector<double> DialogDataPreprocessing::getMeasuredDataTranslationValue(std::vector<double> vector1, std::vector<double> vector2)
{
    std::vector<double> result;
    if (vector1.size() == 0 || vector2.size() == 0)
    {
        return result;
    }

	if (m_circleNum * m_measurePointNum != vector1.size())
	{
		QMessageBox::warning(nullptr, QString::fromUtf8("警告"), QString::fromUtf8("导入的实际数据与观测系统的电极数据不匹配"));
		return result;
	}

    //求实测数据的平均值
    double effectiveStartValue, effectiveEndValue;
    std::vector<double> vectorTemp = vector1;
	
    double data, currentData;
    int count;
    double radio, total, ave2, ave1;
    for (size_t i = 0; i < vectorTemp.size(); i+= m_measurePointNum)
    {
		std::vector<double> adjustVec;
		adjustVec.assign(vector1.begin()+i,vector1.begin()+i+m_measurePointNum);
		searchPoints(adjustVec, effectiveStartValue, effectiveEndValue);
        data        = 0.0;
        
        //每10个数值为一组,求模拟数据和实测数据的比例
		//求模拟数据的平均值
		{
			total = 0.0;
			count = 0;
			for (size_t j = i; j < i + m_measurePointNum; j++)
			{
				if (j + 1 > vector2.size())
				{
					QMessageBox::warning(this, "error", "not");
					break;
				}
				total = total + vector2[j];
				count++;
			}
			ave2 = total / count;
		}

		//求实测数据的平均值
		{
			total = 0.0;
			count = 0;
			for (size_t j = i; j < i + m_measurePointNum; j++)
			{
				currentData = vectorTemp[j];
				if (effectiveStartValue <= vectorTemp[j] && vectorTemp[j] <= effectiveEndValue)
				{
					total = total + currentData;
					count++;
					continue;
				}
			}
			ave1 = total / count;
		}

		//求模拟数据和实测数据的比例
		radio = ave2 / ave1;

		for (int kk = i; kk < i + m_measurePointNum; kk++)
		{
			currentData = vectorTemp[kk];
			//坏点补值，把该位置对应的模拟数据赋值给实测数据坏点位置
			if (effectiveStartValue > currentData || currentData > effectiveEndValue)
			{
				//m_ui.tableWidgetRemovePoint->updateTableData(kk, vector2[kk]);
				//if (m_simuPointTableDataVec.size() > kk) 
				//	m_simuPointTableDataVec[kk] = vector2[kk];
				data = vector2[kk];
			}
			//实测数据平移=实测数据*（模拟数据的平均值与实测数据的平均值的比值））
			else
			{
				data = currentData * radio;
			}

			result.push_back(data);

			//求最大值
			if (data > m_maxValue)
			{
				m_maxValue = data;
			}
		}
    }

    return result;

	//double data, currentData;
 //   int count;
 //   double radio, total, ave2, ave1;
 //   for (size_t i = 0; i < vectorTemp.size(); i++)
 //   {
 //       data        = 0.0;
 //       currentData = vectorTemp[i];

 //       //每10个数值为一组,求模拟数据和实测数据的比例
 //       if (i % 10 == 0)
 //       {
 //           //求模拟数据的平均值
 //           {
 //               total = 0.0;
 //               for (size_t j = i; j < i + 10; j++)
 //               {
 //                   if (j + 1 > vector2.size())
 //                   {
 //                       QMessageBox::warning(this, "error", "not");
 //                       break;
 //                   }
 //                   total = total + vector2[j];
 //               }

 //               ave2 = total / 10;
 //           }

 //           //求实测数据的平均值
 //           {
 //               total = 0.0;
 //               count = 0;
 //               for (size_t j = i; j < i + 10; j++)
 //               {
 //                   if (effectiveStartValue <= vectorTemp[j] && vectorTemp[j] <= effectiveEndValue)
 //                   {
 //                       total = total + vectorTemp[j];
 //                       count++;
 //                       continue;
 //                   }
 //               }
 //               ave1 = total / count;
 //           }

 //           //求模拟数据和实测数据的比例
 //           radio = ave2 / ave1;
 //       }

 //       //坏点补值，把该位置对应的模拟数据赋值给实测数据坏点位置
 //       if (effectiveStartValue > currentData || currentData > effectiveEndValue)
 //       {
 //           m_ui.tableWidgetRemovePoint->updateTableData(i, vector2[i]);
 //           data = vector2[i];
 //       }
 //       //实测数据平移=实测数据*（模拟数据的平均值与实测数据的平均值的比值））
 //       else
 //       {
 //           data = currentData * radio;
 //       }

 //       result.push_back(data);
 //   }

 //   return result;
}