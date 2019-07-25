//半衰时成像表格类

#pragma once
#include "MyTableWidget.h"

class MyTableWidgetHalfLifeCurve : public MyTableWidget
{
	Q_OBJECT
public:
	MyTableWidgetHalfLifeCurve(QWidget *parent = nullptr);
	virtual ~MyTableWidgetHalfLifeCurve();

	void clearData();
	void updateData();	//更新
	void updateTableDataFromDataMgr();
};