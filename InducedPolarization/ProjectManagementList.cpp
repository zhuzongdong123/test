#include "ProjectManagementList.h"
#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QMenu>
#include <QtGui/QKeyEvent>
#include <QtGui/QGuiApplication>
#include <QtCore/QFile>
#include <stdio.h>  
#include <time.h>
#include <QtWidgets/QMessageBox>
#include "ProjectManager.h"
#include "GlobalClass/DataManager.h"

ProjectManagementList::ProjectManagementList(QWidget *parent) :QTreeWidget(parent)
{
	initialization();
}

//初始化函数
void ProjectManagementList::initialization()
{
	m_itemFolder = NULL;

	m_action_deleteAll = new QAction(QString::fromUtf8("删除"), this);
	QObject::connect(m_action_deleteAll, SIGNAL(triggered()), this, SLOT(deletePro()));

	m_action_deleteCurrent = new QAction(QString::fromUtf8("删除"), this);
	QObject::connect(m_action_deleteCurrent, SIGNAL(triggered()), this, SLOT(deleteCurrentItem()));
}

/*******************************************************************/
//创建左侧【项目管理栏】的显示数据名
/*******************************************************************/
void ProjectManagementList::createItem(bool is_folder, bool is_level_2, QString item_name)
{
	if (is_folder)
	{
		//创建父节点
		if (NULL != m_itemFolder)
		{
			deletePro();
		}
		m_itemFolder = new QTreeWidgetItem(itemLevel_1);
		m_itemFolder->setText(0, item_name);
		m_itemFolder->setData(itemLevel, Qt::UserRole, "itemLevel_1");
		m_itemFolder->setIcon(0, QIcon(QStringLiteral(":/InducedPolarization/buttonImages/btn_文件夹.png")));
		this->addTopLevelItem(m_itemFolder);
		m_itemFolder->setExpanded(true);

		m_groupNumber = 0;
	}
	else if (is_level_2)
	{	
		if (NULL == m_itemFolder)	return;

		//if (!checkItemName(item_name))
		//{
		//	return;
		//}

		QTreeWidgetItem* item = new QTreeWidgetItem(itemLevel_2);
		item->setText(0, item_name);
		item->setData(itemLevel, Qt::UserRole, "itemLevel_2");
		item->setData(groupNumberOrCannonNumber, Qt::UserRole, m_groupNumber);
		m_groupNumber++;
		item->setIcon(0, QIcon(QStringLiteral(":/InducedPolarization/buttonImages/btn_文件.png")));

		//添加到父节点
		m_itemFolder->addChild(item);
		item->setExpanded(false);
	}

	this->update();
}

//删除工程
void ProjectManagementList::deletePro()
{
	if (NULL != m_itemFolder)
	{
		int childCount = m_itemFolder->childCount();
		for (int i = 0; i < childCount; i++)
		{
			QTreeWidgetItem* childItem = m_itemFolder->child(0);	//注意：这里的下标是0
			delete childItem;
			childItem = NULL;
		}

		delete m_itemFolder;
		m_itemFolder = NULL;
	}

	emit closeProject();
}

void ProjectManagementList::deleteCurrentItem()
{
	QTreeWidgetItem* currentItem = this->currentItem();
	if (NULL != currentItem)
	{
		int childCount = currentItem->childCount();
		for (int i = 0; i < childCount; i++)
		{
			QTreeWidgetItem* childItem = currentItem->child(0);	//注意：这里的下标是0
			delete childItem;
			childItem = NULL;
		}

		delete currentItem;
		currentItem = NULL;

		//删除后，光标定位到最后一条数据
		childCount = m_itemFolder->childCount();
		if (childCount > 0)
		{
			this->setCurrentItem(m_itemFolder->child(childCount - 1));
		}
		else
		{
			this->setCurrentItem(m_itemFolder);
		}	
	}
}

void ProjectManagementList::onItemChanged(QTreeWidgetItem* item, int row)
{
	if (item->data(itemLevel, Qt::UserRole).toString() == "itemLevel_1"
		&& (QGuiApplication::mouseButtons() & Qt::RightButton))
	{
		m_action_deleteAll->setEnabled(true);
		QMenu* menu = new QMenu();
		menu->addAction(m_action_deleteAll);
		menu->exec(QCursor::pos());
		delete menu;
		return;
	}
	else if (item->data(itemLevel, Qt::UserRole).toString() == "itemLevel_2"
		&& (QGuiApplication::mouseButtons() & Qt::RightButton))
	{
		m_action_deleteCurrent->setEnabled(true);
		QMenu* menu = new QMenu();
		menu->addAction(m_action_deleteCurrent);
		menu->exec(QCursor::pos());
		delete menu;
		return;
	}
}

bool ProjectManagementList::checkItemName(QString item_name)
{
	for (size_t i = 0; i < m_itemFolder->childCount(); i++)
	{
		//QTreeWidgetItem* childItem = m_itemFolder->child(i);
		//QString currentItemName = childItem->text(0);
		if (QStringLiteral("建模") == item_name)
		{
			return false;
		}
	}

	return true;
}