//自定义表格基类
#pragma once
#pragma execution_character_set("utf-8")

#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include <QtWidgets/QAction>
#include <QtGui/QKeyEvent>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QMenu>
#include <QtGui/QClipboard>
#include <QtGui/QFont>
#include <QtCore/QMimeData>
#include <sstream>
#include "osg/Vec3d"
#include "GlobalClass/GlobalParam.h"
#include <memory>
using namespace std;

class MyTableWidget : public QTableWidget
{
	Q_OBJECT
public:
	MyTableWidget(QWidget *parent = nullptr);
	virtual ~MyTableWidget();

	//void updateData();	//更新

	virtual void keyPressEvent(QKeyEvent * event);
	virtual void mousePressEvent(QMouseEvent *event);
	void setAutoComplete(QString preWord) { m_autoPreWord = preWord; }
	void setLockState(bool lock);


	bool getLockOperation() { return m_lockOperation; }

public slots:	
	virtual void paste();
	virtual void deleteRange();
	virtual void copy();

private:
	void deleteText();
	void backspace();

private:
	QAction* m_pasteAction;
	QAction* m_deleteAction;
	QAction* m_copyAction;
	QString m_autoPreWord;

	bool m_lockOperation;
};