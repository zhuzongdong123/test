//��˥ʱ��������

#pragma once
#include "MyTableWidget.h"

class MyTableWidgetHalfLifeCurve : public MyTableWidget
{
	Q_OBJECT
public:
	MyTableWidgetHalfLifeCurve(QWidget *parent = nullptr);
	virtual ~MyTableWidgetHalfLifeCurve();

	void clearData();
	void updateData();	//����
	void updateTableDataFromDataMgr();
};