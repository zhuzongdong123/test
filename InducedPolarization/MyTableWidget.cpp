#include "MyTableWidget.h"

MyTableWidget::MyTableWidget(QWidget *parent) : QTableWidget(parent)
{
	m_copyAction = new QAction(QString::fromUtf8("复制"), this);
	m_pasteAction = new QAction(QString::fromUtf8("粘贴"), this);
	m_deleteAction = new QAction(QString::fromUtf8("删除"), this);

	m_lockOperation = true;

	QObject::connect(m_pasteAction, SIGNAL(triggered()), this, SLOT(paste()));
	QObject::connect(m_deleteAction, SIGNAL(triggered()), this, SLOT(deleteRange()));
	QObject::connect(m_copyAction, SIGNAL(triggered()), this, SLOT(copy()));

	QObject::connect(this, &QTableWidget::itemDoubleClicked, [=](QTableWidgetItem *item)
	{
		if (m_lockOperation)
		{
			return;
		}

		openPersistentEditor(item); //打开编辑项
		editItem(item);
	});

	QObject::connect(this, &QTableWidget::currentItemChanged, [=](QTableWidgetItem *current, QTableWidgetItem *previous)
	{
		closePersistentEditor(previous);
	});
}

MyTableWidget::~MyTableWidget() {}

/********************************************************************/
//粘贴【ctrl+v或者右键粘贴】
/********************************************************************/
void MyTableWidget::paste()
{
	if (NULL == qApp->clipboard()->mimeData() || m_lockOperation)
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
		if (selectRange.size() == 0) return ;

		unsigned int topPos = selectRange[0].topRow();
		unsigned int leftPos = selectRange[0].leftColumn();
		if (leftPos == 0)	leftPos = 1;
		unsigned int rightPos = selectRange[0].rightColumn();
		unsigned int bottomPos = selectRange[0].bottomRow();
		unsigned int tempRowCount = rowCount();
		unsigned int tempColCount = columnCount();
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

			if ("" != m_autoPreWord)
			{
				if (nullptr == item(y, 0))
				{
					setItem(y, 0, new QTableWidgetItem(m_autoPreWord + QString::number(y + 1)));
				}
				else if ("" == item(y, 0)->text())
				{
					item(y, 0)->setText(m_autoPreWord + QString::number(y));
				}
			}
		}
	}
}

/********************************************************************/
//复制【ctrl+c】
/********************************************************************/
void MyTableWidget::copy()
{
	QItemSelectionModel * selection = selectionModel();
	QModelIndexList indexes = selection->selectedIndexes();

	if (indexes.size() < 1)
		return;

	qSort(indexes);

	QModelIndex previous = indexes.first();
	indexes.removeFirst();
	QString selected_text_as_html;
	QString selected_text;
	selected_text_as_html.prepend("<html><style>br{mso-data-placement:same-cell;}</style><table><tr><td>");
	QModelIndex current;
	Q_FOREACH(current, indexes)
	{
		QVariant data = model()->data(previous);
		QString text = data.toString();
		selected_text.append(text);
		text.replace("\n", "<br>");
		selected_text_as_html.append(text);

		if (current.row() != previous.row())
		{
			selected_text_as_html.append("</td></tr><tr><td>");
			selected_text.append(QLatin1Char('\n'));
		}
		else
		{
			selected_text_as_html.append("</td><td>");
			selected_text.append(QLatin1Char('\t'));
		}
		previous = current;
	}

	if (indexes.size() < 1)
	{
		selected_text_as_html.append(model()->data(previous).toString());
		selected_text.append(model()->data(previous).toString());
	}
	else
	{
		selected_text_as_html.append(model()->data(current).toString());
		selected_text.append(model()->data(current).toString());
	}
	selected_text_as_html.append("</td></tr>");
	QMimeData * md = new QMimeData;
	md->setHtml(selected_text_as_html);
	md->setText(selected_text);
	qApp->clipboard()->setMimeData(md);
}

/********************************************************************/
//delete键
/********************************************************************/
void MyTableWidget::deleteText()
{
	deleteRange();
}

/********************************************************************/
//Backspace键,删除选择区域第一个单元格
/********************************************************************/
void MyTableWidget::backspace()
{
	QList<QTableWidgetSelectionRange> selectRange = this->selectedRanges();
	if (selectRange.size() == 0)	return;

	unsigned int topPos = selectRange[0].topRow();
	unsigned int leftPos = selectRange[0].leftColumn();
	if (leftPos == 0)	leftPos = 1;
	removeCellWidget(topPos, leftPos);
	setItem(topPos, leftPos, new QTableWidgetItem(QString::fromStdString("")));
}

/********************************************************************/
//删除选中区域
/********************************************************************/
void MyTableWidget::deleteRange()
{
	QList<QTableWidgetSelectionRange> selectRange = this->selectedRanges();
	if (selectRange.size() == 0)	return;
	unsigned int topPos = selectRange[0].topRow();
	unsigned int leftPos = selectRange[0].leftColumn();
//	if (leftPos == 0)	leftPos = 1;
	unsigned int rightPos = selectRange[0].rightColumn();
	unsigned int bottomPos = selectRange[0].bottomRow();

	unsigned int rowCount = this->rowCount();
	unsigned int colCount = this->columnCount();

	for (unsigned int y = topPos; y <= bottomPos; y++)
	{
		for (unsigned int x = leftPos; x <= rightPos; x++)
		{
			removeCellWidget(y, x);
			setItem(y, x, new QTableWidgetItem(QString::fromStdString("")));
		}
	}
}

/********************************************************************/
//重写键盘事件
/********************************************************************/
void MyTableWidget::keyPressEvent(QKeyEvent * event)
{
	//Ctrl+C键
	if (event->matches(QKeySequence::Copy))
	{
		copy();
	}
	//Ctrl+V键
	else if (event->matches(QKeySequence::Paste))
	{
		paste();
	}
	//delete键
	else if (event->matches(QKeySequence::Delete))
	{
		deleteText();
	}
	//backspace键
	else if (event->matches(QKeySequence::Back))
	{
		backspace();
	}
	//回车键
	else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
	{
		focusNextPrevChild(true);
	}
	else
	{
		QTableWidget::keyPressEvent(event);
	}

}

/********************************************************************/
//重写鼠标事件
/********************************************************************/
void MyTableWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton && !m_lockOperation)
	{
		shared_ptr<QMenu> popMenu = shared_ptr<QMenu>(new QMenu(this));
		popMenu->addAction(m_copyAction);
		popMenu->addAction(m_pasteAction);
		popMenu->addAction(m_deleteAction);
		popMenu->exec(QCursor::pos());
	}
	QTableWidget::mousePressEvent(event);
}

void MyTableWidget::setLockState(bool lock)
{
	m_lockOperation = lock;
}
