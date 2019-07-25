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

//��ʼ������
void ProjectManagementList::initialization()
{
	m_itemFolder = NULL;

	m_action_deleteAll = new QAction(QString::fromUtf8("ɾ��"), this);
	QObject::connect(m_action_deleteAll, SIGNAL(triggered()), this, SLOT(deletePro()));

	m_action_deleteCurrent = new QAction(QString::fromUtf8("ɾ��"), this);
	QObject::connect(m_action_deleteCurrent, SIGNAL(triggered()), this, SLOT(deleteCurrentItem()));
}

/*******************************************************************/
//������ࡾ��Ŀ������������ʾ������
/*******************************************************************/
void ProjectManagementList::createItem(bool is_folder, bool is_level_2, QString item_name)
{
	if (is_folder)
	{
		//�������ڵ�
		if (NULL != m_itemFolder)
		{
			deletePro();
		}
		m_itemFolder = new QTreeWidgetItem(itemLevel_1);
		m_itemFolder->setText(0, item_name);
		m_itemFolder->setData(itemLevel, Qt::UserRole, "itemLevel_1");
		m_itemFolder->setIcon(0, QIcon(QStringLiteral(":/InducedPolarization/buttonImages/btn_�ļ���.png")));
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
		item->setIcon(0, QIcon(QStringLiteral(":/InducedPolarization/buttonImages/btn_�ļ�.png")));

		//��ӵ����ڵ�
		m_itemFolder->addChild(item);
		item->setExpanded(false);
	}

	this->update();
}

//ɾ������
void ProjectManagementList::deletePro()
{
	if (NULL != m_itemFolder)
	{
		int childCount = m_itemFolder->childCount();
		for (int i = 0; i < childCount; i++)
		{
			QTreeWidgetItem* childItem = m_itemFolder->child(0);	//ע�⣺������±���0
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
			QTreeWidgetItem* childItem = currentItem->child(0);	//ע�⣺������±���0
			delete childItem;
			childItem = NULL;
		}

		delete currentItem;
		currentItem = NULL;

		//ɾ���󣬹�궨λ�����һ������
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
		if (QStringLiteral("��ģ") == item_name)
		{
			return false;
		}
	}

	return true;
}