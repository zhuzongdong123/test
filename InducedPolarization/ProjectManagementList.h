#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QWidget>
#include <QtGui/QStandardItemModel>
#include <memory>
#pragma execution_character_set("utf-8")
class ProjectManagementList : public QTreeWidget
{
	Q_OBJECT

public:
	ProjectManagementList(QWidget *parent = NULL);

signals:
	void closeProject();

public slots:
	void createItem(bool is_folder, bool is_level_2, QString item_name);

	void deletePro();			//删除工程
	void deleteCurrentItem();	//删除当前节点

	void onItemChanged(QTreeWidgetItem* item, int row);

private:	
	void initialization();
	bool checkItemName(QString item_name);

private:
	QTreeWidgetItem *m_itemFolder;
	QTreeWidgetItem *m_itemLevel_2;
	unsigned int m_groupNumber;

	QAction *m_action_deleteAll;
	QAction *m_action_deleteCurrent;

	enum treeItemType
	{
		itemLevel_1 = 1001,
		itemLevel_2,
		itemLevel_3
	};

	enum dataColumn
	{
		itemLevel = 0,
		groupNumberOrCannonNumber
	};

};