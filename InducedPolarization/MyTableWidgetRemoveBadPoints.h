#pragma once

#include "MyTableWidget.h"

class MyTableWidgetRemoveBadPoints : public MyTableWidget
{
	Q_OBJECT
public:
	MyTableWidgetRemoveBadPoints(QWidget *parent = nullptr);

	void paste();
	void mousePressEvent(QMouseEvent *event);

	void updateTableData(int row, double text);

private:
	QAction* m_pasteAction;
	QAction* m_deleteAction;
};