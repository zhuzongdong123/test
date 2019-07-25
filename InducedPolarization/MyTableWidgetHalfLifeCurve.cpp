#include "MyTableWidgetHalfLifeCurve.h"
#include "..\osg\Array"
#include "GlobalClass\DataManager.h"

MyTableWidgetHalfLifeCurve::MyTableWidgetHalfLifeCurve(QWidget *parent) : MyTableWidget(parent)
{
	//setRowCount(30);
	//setColumnCount(2);
	//setWindowTitle(QString::fromUtf8("网格大小设置"));

	//QStringList header;
	//header << "X" << "Y";

	//setHorizontalHeaderLabels(header);
	////QHeaderView * aa = verticalHeader();
	////aa->setVisible(false);

	////QFont font = horizontalHeader()->font();
	////font.setBold(true);
	////horizontalHeader()->setFont(font);

	////horizontalHeader()->setStretchLastSection(true);
	////verticalHeader()->setDefaultSectionSize(20);
	////setSelectionMode(QAbstractItemView::ExtendedSelection);
	////horizontalHeader()->resizeSection(0, 105);
	////horizontalHeader()->resizeSection(1, 105);
	////horizontalHeader()->resizeSection(2, 105);
	////horizontalHeader()->setFixedHeight(25);

	//setStyleSheet("selection-background-color:lightblue;");
	////horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
}

MyTableWidgetHalfLifeCurve::~MyTableWidgetHalfLifeCurve() {}

void MyTableWidgetHalfLifeCurve::clearData()
{

}

/********************************************************************/
//更新表格数据
/********************************************************************/
void MyTableWidgetHalfLifeCurve::updateData()
{
	//数据一行行保存，只保存xl,yl,zl的数据
// 	std::vector<osg::Vec3d> s_data;
// 
// 	for (int i = 0; i < this->rowCount(); i++)
// 	{
// 		osg::Vec3d v;
// 
// 		bool bSet = false;
// 
// 		for (int j = 1; j < this->columnCount(); j++)
// 		{
// 			if (this->item(i, j) == NULL || this->item(i, j)->text() == "")
// 			{
// 				break;
// 			}
// 
// 			else if (1 == j)
// 			{
// 				v.x() = this->item(i, j)->text().toDouble();
// 			}
// 			else if (2 == j)
// 			{
// 				v.y() = this->item(i, j)->text().toDouble();
// 			}
// 			else if (3 == j)
// 			{
// 				v.z() = this->item(i, j)->text().toDouble();
// 			}
// 
// 			bSet = true;
// 		}
// 
// 		if (bSet)
// 		{
// 			s_data.push_back(v);
// 		}
// 	}
// 
// 	if (s_data.size() > 0)
// 	{
// 		//数据保存
// 		GlobalParam::instance()->getModeling().saveRightTabelData(s_data);
// 	}
}

void MyTableWidgetHalfLifeCurve::updateTableDataFromDataMgr()
{
	osg::ref_ptr<osg::Vec2dArray> list = DataManager::instance()->getHalfLifeCurveDataList();

	clearContents();

	for (unsigned int i = 0; i < list->size(); i++)
	{
		for (unsigned int j = 0; j < 3; j++)
		{
			switch (j)
			{
			case 0:
			{
				auto p = new QTableWidgetItem(QString::fromUtf8("编号") + QString::number(i + 1));
				setItem(i, 0, p);
				break;
			}
			case 1:
			{
				auto p = new QTableWidgetItem(QString::number(list->at(i).x()));
				setItem(i, 1, p);
				break;
			}
			case 2:
			{
				auto p = new QTableWidgetItem(QString::number(list->at(i).y()));
				setItem(i, 2, p);
				break;
			}
			default:
				break;
			}
		}
	}
}
