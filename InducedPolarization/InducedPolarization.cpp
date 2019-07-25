#include "InducedPolarization.h"
#include <QtWidgets/QMenu>
#include "QTextCodec"
using namespace std;

InducedPolarization::InducedPolarization(QWidget *parent)
    : QDialog(parent)
{
    m_ui.setupUi(this);

	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowMinMaxButtonsHint;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);

	QObject::connect(m_ui.widget_leftUpper, SIGNAL(showMax(QString,QString)), this, SLOT(onActionShowMax(QString, QString)));
	QObject::connect(m_ui.widget_leftDown, SIGNAL(showMax(QString, QString)), this, SLOT(onActionShowMax(QString, QString)));
	QObject::connect(m_ui.widget_rightDown, SIGNAL(showMax(QString, QString)), this, SLOT(onActionShowMax(QString, QString)));
	QObject::connect(m_ui.widget_rightUpper, SIGNAL(showMax(QString, QString)), this, SLOT(onActionShowMax(QString, QString)));


	//QObject::connect(m_ui.widget_leftUpper->getPickHandle(), SIGNAL(addPopMenu()), this, SLOT(showMax()));
	
	//右键菜单
	//m_openFile = new QAction(QString::fromLocal8Bit("打开文件"), this);
	//QObject::connect(m_openFile, SIGNAL(triggered()), this, SLOT(onActionOpenFile()));

	//m_showMax = new QAction(QString::fromLocal8Bit("最大化显示"), this);
	//QObject::connect(m_showMax, SIGNAL(triggered()), this, SLOT(onActionShowMax()));


	m_dialogLeftUpper = new DialogDisplayImage(this);
	m_dialogLeftDown = new DialogDisplayImage(this);
	m_dialogRightDown = new DialogDisplayImage(this);
	m_dialogRightUpper = new DialogDisplayImage(this);

	//this->showMaximized();
}

InducedPolarization::~InducedPolarization()
{
}

void InducedPolarization::onActionShowMax(QString objectName, QString osgFilePath)
{
	//if (objectName == m_ui.widget_leftUpper->objectName())
	//{
	//	m_dialogLeftUpper->setOsgFilePath(osgFilePath);
	//	m_dialogLeftUpper->showMaximized();
	//}
	//else if (objectName == m_ui.widget_leftDown->objectName())
	//{
	//	m_dialogLeftDown->setOsgFilePath(osgFilePath);
	//	m_dialogLeftUpper->showMaximized();
	//}
	//else if (objectName == m_ui.widget_rightDown->objectName())
	//{
	//	m_dialogRightDown->setOsgFilePath(osgFilePath);
	//	m_dialogLeftUpper->showMaximized();
	//}
	//else if (objectName == m_ui.widget_rightUpper->objectName())
	//{
	//	m_dialogRightUpper->setOsgFilePath(osgFilePath);
	//	m_dialogLeftUpper->showMaximized();
	//}
}

//void InducedPolarization::showMax()
//{
//	//QMenu *menu = new QMenu();
//	//menu->addAction(m_openFile);
//	//menu->exec(QCursor::pos());
//	//delete menu;
//}
//
//void InducedPolarization::onActionOpenFile()
//{
//	//打开文件
//	QString file_name = QFileDialog::getOpenFileName(
//		this,
//		QStringLiteral("请选择导入文件"),					//对话框的标题
//		QDir::currentPath(),								//默认打开路径
//		QStringLiteral("文件类型(*.osg)"),					//打开文件的格式
//		0);													//默认选择的过滤器
//
//	if (file_name != "")
//	{
//		osg::Node* cessnaNode = NULL;
//
//		QTextCodec *code = QTextCodec::codecForName("GB2312"); //解决中文路径问题
//		std::string filePath = code->fromUnicode(file_name).data();
//		cessnaNode = osgDB::readNodeFile(filePath);
//
//		if (cessnaNode != NULL)
//		{
//			m_ui.widget_leftUpper->getViewer()->setSceneData(cessnaNode); //将模型添加到渲染器中
//			m_osgFilePath = file_name;
//		}
//	}
//}