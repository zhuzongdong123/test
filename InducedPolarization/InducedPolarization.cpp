#include "InducedPolarization.h"
#include <QtWidgets/QMenu>
#include "QTextCodec"
using namespace std;

InducedPolarization::InducedPolarization(QWidget *parent)
    : QMainWindow(parent)
{
    m_ui.setupUi(this);

	QObject::connect(m_ui.widget_leftUpper, SIGNAL(showMax(QString,QString)), this, SLOT(onActionShowMax(QString, QString)));
	QObject::connect(m_ui.widget_leftDown, SIGNAL(showMax(QString, QString)), this, SLOT(onActionShowMax(QString, QString)));
	QObject::connect(m_ui.widget_rightDown, SIGNAL(showMax(QString, QString)), this, SLOT(onActionShowMax(QString, QString)));
	QObject::connect(m_ui.widget_rightUpper, SIGNAL(showMax(QString, QString)), this, SLOT(onActionShowMax(QString, QString)));

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
	if (objectName == m_ui.widget_leftUpper->objectName())
	{
		if (!m_dialogLeftUpper->isHidden())
		{
			m_dialogLeftUpper->hide();
			m_dialogLeftUpper->show(); 
			return;
		}

		m_dialogLeftUpper->setWindowTitle(objectName);
		m_dialogLeftUpper->setOsgFilePath(osgFilePath);
		m_dialogLeftUpper->show();
	}
	else if (objectName == m_ui.widget_leftDown->objectName())
	{
		if (!m_dialogLeftDown->isHidden())
		{
			m_dialogLeftDown->hide();
			m_dialogLeftDown->show();
			return;
		}

		m_dialogLeftDown->setWindowTitle(objectName);
		m_dialogLeftDown->setOsgFilePath(osgFilePath);
		m_dialogLeftDown->show();
	}
	else if (objectName == m_ui.widget_rightDown->objectName())
	{
		if (!m_dialogRightDown->isHidden())
		{
			m_dialogRightDown->hide();
			m_dialogRightDown->show();
			return;
		}

		m_dialogRightDown->setWindowTitle(objectName);
		m_dialogRightDown->setOsgFilePath(osgFilePath);
		m_dialogRightDown->show();
	}
	else if (objectName == m_ui.widget_rightUpper->objectName())
	{
		if (!m_dialogRightUpper->isHidden())
		{
			m_dialogRightUpper->hide();
			m_dialogRightUpper->show();
			return;
		}

		m_dialogRightUpper->setWindowTitle(objectName);
		m_dialogRightUpper->setOsgFilePath(osgFilePath);
		m_dialogRightUpper->show();
	}
}

void InducedPolarization::openOSGFile1()
{
	//打开文件
	QString file_name = QFileDialog::getOpenFileName(
		this,
		QStringLiteral("请选择导入文件"),					//对话框的标题
		QDir::currentPath(),								//默认打开路径
		QStringLiteral("文件类型(*.osg)"),					//打开文件的格式
		0);													//默认选择的过滤器

	if (file_name != "")
	{
		osg::Node* cessnaNode = NULL;

		QTextCodec *code = QTextCodec::codecForName("GB2312"); //解决中文路径问题
		std::string filePath = code->fromUnicode(file_name).data();
		cessnaNode = osgDB::readNodeFile(filePath);

		if (cessnaNode != NULL)
		{
			m_ui.widget_leftDown->getViewer()->setSceneData(cessnaNode); //将模型添加到渲染器中
			m_ui.widget_leftDown->setOsgFilePath(file_name);
		}
	}

}
void InducedPolarization::openOSGFile2()
{
	//打开文件
	QString file_name = QFileDialog::getOpenFileName(
		this,
		QStringLiteral("请选择导入文件"),					//对话框的标题
		QDir::currentPath(),								//默认打开路径
		QStringLiteral("文件类型(*.osg)"),					//打开文件的格式
		0);													//默认选择的过滤器

	if (file_name != "")
	{
		osg::Node* cessnaNode = NULL;

		QTextCodec *code = QTextCodec::codecForName("GB2312"); //解决中文路径问题
		std::string filePath = code->fromUnicode(file_name).data();
		cessnaNode = osgDB::readNodeFile(filePath);

		if (cessnaNode != NULL)
		{
			m_ui.widget_rightDown->getViewer()->setSceneData(cessnaNode); //将模型添加到渲染器中
			m_ui.widget_rightDown->setOsgFilePath(file_name);
		}
	}
}