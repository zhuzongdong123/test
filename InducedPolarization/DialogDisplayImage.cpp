#include "DialogDisplayImage.h"
#include "QTextCodec"
#include <osgDB/WriteFile>

DialogDisplayImage::DialogDisplayImage(QWidget *parent)
{
	m_ui.setupUi(this);

	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowMinMaxButtonsHint;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);
}

void DialogDisplayImage::setOsgFilePath(QString fileName)
{
	osg::Node* cessnaNode = NULL;

	QTextCodec *code = QTextCodec::codecForName("GB2312"); //解决中文路径问题
	std::string filePath = code->fromUnicode(fileName).data();
	cessnaNode = osgDB::readNodeFile(filePath);

	if (cessnaNode != NULL)
	{
		m_ui.widget_show->getViewer()->setSceneData(cessnaNode); //将模型添加到渲染器中
	}
}
