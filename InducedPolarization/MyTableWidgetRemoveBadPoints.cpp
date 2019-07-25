#include "MyTableWidgetRemoveBadPoints.h"
#include <QtWidgets/QMenu>


MyTableWidgetRemoveBadPoints::MyTableWidgetRemoveBadPoints(QWidget *parent) : MyTableWidget(parent)
{
	m_pasteAction = new QAction(QString::fromUtf8("ճ��"), this);
	m_deleteAction = new QAction(QString::fromUtf8("ɾ��"), this);

	QObject::connect(m_pasteAction, SIGNAL(triggered()), this, SLOT(paste()));
	QObject::connect(m_deleteAction, SIGNAL(triggered()), this, SLOT(deleteRange()));
}

/********************************************************************/
//ճ����ctrl+v�����Ҽ�ճ����
/********************************************************************/
void MyTableWidgetRemoveBadPoints::paste()
{
	if (NULL == qApp->clipboard()->mimeData() || getLockOperation())
	{
		return;
	}
	else
	{
		QString selected_text = qApp->clipboard()->text();
		if (selected_text == "")	return;

		QStringList cells = selected_text.split('\n');
		while (!cells.empty() && cells.back().size() == 0)
		{
			cells.pop_back(); // strip empty trailing tokens
		}

		QList<QTableWidgetSelectionRange> selectRange = this->selectedRanges();
		if (selectRange.size() == 0) return;

		unsigned int topPos = selectRange[0].topRow();
		unsigned int leftPos = selectRange[0].leftColumn();
		unsigned int rightPos = selectRange[0].rightColumn();
		unsigned int bottomPos = selectRange[0].bottomRow();
		unsigned int tempRowCount = rowCount();
		//unsigned int tempColCount = columnCount();
		unsigned int tempColCount = columnCount()-1;	//���һ�в�����ճ���¼�
		unsigned int data_y = 0;

		for (unsigned int y = topPos; y < tempRowCount; y++)
		{
			if (data_y >= cells.size())
			{
				break;
			}

			std::stringstream ss(cells.at(data_y).toStdString());
			std::string str = "";
			data_y++;

			for (unsigned int x = leftPos; x < tempColCount; x++)
			{
				if (ss >> str)
				{
					removeCellWidget(y, x);
					setItem(y, x, new QTableWidgetItem(QString::fromStdString(str)));
				}
			}
		}
	}
}

/********************************************************************/
//��д����¼�
/********************************************************************/
void MyTableWidgetRemoveBadPoints::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton && !getLockOperation())
	{
		shared_ptr<QMenu> popMenu = shared_ptr<QMenu>(new QMenu(this));
		popMenu->addAction(m_pasteAction);
		popMenu->addAction(m_deleteAction);
		popMenu->exec(QCursor::pos());
	}
	QTableWidget::mousePressEvent(event);
}

void MyTableWidgetRemoveBadPoints::updateTableData(int row, double text)
{
	removeCellWidget(row, 5);
	setItem(row, 5, new QTableWidgetItem(QString::number(text)));
}