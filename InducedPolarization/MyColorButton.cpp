#include "MyColorButton.h"

MyColorButton::MyColorButton(QWidget *parent) : QPushButton(parent)
{
	setParent(parent);
	m_multiColoringDetails = new DialogMultiColoringDetails(this);
	connect(m_multiColoringDetails, SIGNAL(setTextRange(float, float, int)), this, SLOT(setTextRange(float, float, int)));	//显示当前选中颜色的效果
	connect(m_multiColoringDetails, SIGNAL(setColorGroupName(QString)), this, SLOT(setColorGroupName(QString)));			//选定颜色组
	//m_linearGradient = QLinearGradient(this->width() / 2, 0, this->width() / 2, this->height());
	//m_linearGradient.setColorAt(1, QColor(255, 255, 255));

	//初始化
	m_startPosX = 8;
	m_startPosY = 30;
	m_maxValue = 1600;
	m_minValue = 200;
	m_numberOfLevels = 20;
	m_colorGroupName = "jetColor";
	creatJetColor(m_numberOfLevels * 20, m_colorVector);
}

MyColorButton::~MyColorButton()
{
	if (NULL != m_multiColoringDetails)
	{
		delete m_multiColoringDetails;
		m_multiColoringDetails = NULL;
	}
}

void MyColorButton::paintEvent(QPaintEvent* event)
{
	//变量声明
	QPushButton::paintEvent(event);
	QPainter *painter = new QPainter(this);
	painter->setPen(QPen(Qt::black, 1));
	int ave, maxHeight,maxWidth = 83;
	char buf[64];
	QColor color;

	if (m_colorVector.size() == 0)	return;

	//取得颜色
	ave = m_colorVector.size() / m_numberOfLevels;

	//开始绘制颜色和文字
	float aveVlaue = (m_maxValue - m_minValue) / m_numberOfLevels;
	for (int i = 0; i < m_numberOfLevels; i++)
	{
		if ((i*ave) > m_colorVector.size()) break;

		if (m_numberOfLevels == 2)
		{
			if (i == 0) color = m_colorVector[m_colorVector.size() - 1];
			
			else if (i == 1) color = m_colorVector[0];
		}
		else if (m_numberOfLevels == 3)
		{
			if (i == 0) color = m_colorVector[m_colorVector.size() - 1];

			else if (i == 1) color = m_colorVector[m_colorVector.size()/2];

			else if (i == 2) color = m_colorVector[0];
		}
		else
		{
			color = m_colorVector[m_colorVector.size() - (i*ave) - 1];
		}
	
		painter->setBrush(QBrush(color));
		painter->drawRect(m_startPosX, m_startPosY + i*ave, this->width() / 2 - m_startPosX, ave);
		maxHeight = m_startPosY + i*ave + ave +10;

		//小数点超过3位的时候，保留3位小数
		float outValue = m_maxValue - aveVlaue*i;
		if (fabs(outValue-int(outValue)) > 1e-15)
		{
			sprintf(buf, "%0.3f", outValue);
			painter->drawText(this->width() / 2 + 3, m_startPosY + i*ave + 5, buf);
			maxWidth = 110;
		}
		else
		{
			painter->drawText(this->width() / 2 + 3, m_startPosY + i*ave + 5, QString::number(outValue));
		}
		
	}
	painter->drawText(this->width() / 2 + 3, m_startPosY + ave*m_numberOfLevels + 5, QString::number(m_minValue));
	painter->drawText(5, m_startPosY / 2, "Resisitivity");

	//重新计算宽高
	this->setFixedHeight(maxHeight);
	this->setFixedWidth(maxWidth);

	delete painter;
	painter = NULL;
}

void MyColorButton::mouseDoubleClickEvent(QMouseEvent* e)
{
	m_multiColoringDetails->getContourLevels()->setValue(m_minValue, m_maxValue, m_numberOfLevels,10);
	m_multiColoringDetails->hide();
	m_multiColoringDetails->show();
	QPushButton::mouseDoubleClickEvent(e);
}

void MyColorButton::setTextRange(float minValue, float maxValue, int number)
{
	m_maxValue = maxValue;
	m_minValue = minValue;
	m_numberOfLevels = number;

	if (m_colorGroupName == "jetColor")
	{
		creatJetColor(m_numberOfLevels * 20, m_colorVector);
	}
	else if (m_colorGroupName == "customColor")
	{
		creatCustomColor(m_numberOfLevels * 20, m_colorVector);
	}
	else if (m_colorGroupName == "largeRainbow")
	{
		creatLargeRainbow(m_numberOfLevels * 20, m_colorVector);
	}
	
	update();
	emit colorChanged();
}

void MyColorButton::setColorGroupName(QString name)
{ 
	m_colorGroupName = name; 

	if (m_colorGroupName == "jetColor")
	{
		creatJetColor(m_numberOfLevels * 20, m_colorVector);
	}
	else if (m_colorGroupName == "customColor")
	{
		creatCustomColor(m_numberOfLevels * 20, m_colorVector);
	}
	else if (m_colorGroupName == "largeRainbow")
	{
		creatLargeRainbow(m_numberOfLevels * 20, m_colorVector);
	}

	update();
	emit colorChanged();
}

void MyColorButton::setTextRange(float minValue, float maxValue)
{
	m_maxValue = maxValue;
	m_minValue = minValue;
	update();
	m_multiColoringDetails->getContourLevels()->setValue(m_minValue, m_maxValue);
	emit colorChanged();
}

void MyColorButton::creatJetColor(float colorBarLength, std::vector<QColor>& colorVector)
{
	QColor color;
	QRect section;
	colorVector.clear();

	//------设置为jet颜色条---------//
	float tempLength = colorBarLength / 4;
	for (int i = 0; i<tempLength / 2; i++)// jet
	{
		color.setRgbF(0, 0, (tempLength / 2 + i) / tempLength);
		colorVector.push_back(color);
	}
	for (int i = tempLength / 2 + 1; i<tempLength / 2 + tempLength; i++)// jet
	{
		color.setRgbF(0, (i - tempLength / 2) / tempLength, 1);
		colorVector.push_back(color);
	}
	for (int i = tempLength / 2 + tempLength + 1; i<tempLength / 2 + 2 * tempLength; i++)// jet
	{
		color.setRgbF((i - tempLength - tempLength / 2) / tempLength, 1, (tempLength * 2 + tempLength / 2 - i) / tempLength);
		colorVector.push_back(color);
	}
	for (int i = tempLength / 2 + 2 * tempLength + 1; i<tempLength / 2 + 3 * tempLength; i++)// jet
	{
		color.setRgbF(1, (tempLength * 3 + tempLength / 2 - i) / tempLength, 0);
		colorVector.push_back(color);
	}
	for (int i = tempLength / 2 + 3 * tempLength + 1; i<colorBarLength; i++)// jet
	{
		color.setRgbF((colorBarLength - i + tempLength / 2) / (tempLength), 0, 0);
		colorVector.push_back(color);
	}
}

void MyColorButton::creatCustomColor(float colorBarLength, std::vector<QColor>& colorVector)
{
	QColor color;
	QRect section;
	colorVector.clear();

	for (int i = 0; i <= colorBarLength; i++)// jet
	{
		color.setRgbF(0.5, i/ colorBarLength, 0.5);
		colorVector.push_back(color);
	}
}

void MyColorButton::creatLargeRainbow(float colorBarLength, std::vector<QColor>& colorVector)
{
	QColor color;
	QRect section;
	colorVector.clear();

	//------设置为jet颜色条---------//
	float tempLength = colorBarLength / 8;
	for (int i = 0; i<tempLength; i++)// jet
	{
		color.setRgbF(0, i/(tempLength*2), 1);
		colorVector.push_back(color);
	}
	for (int i = tempLength + 1; i<tempLength*2; i++)// jet
	{
		color.setRgbF(0, i/(tempLength*2), 1.25- i/(tempLength * 4));
		colorVector.push_back(color);
	}
	for (int i = tempLength * 2+1; i<tempLength * 3; i++)// jet
	{
		color.setRgbF(0, 1, 1 - i / (tempLength * 4));
		colorVector.push_back(color);
	}
	for (int i = tempLength * 3 + 1; i<tempLength * 4; i++)// jet
	{
		color.setRgbF(i / (tempLength * 3)-1, 1, 1 - i / (tempLength*4));
		colorVector.push_back(color);
	}
	for (int i = tempLength * 4 + 1; i<tempLength * 5; i++)// jet
	{
		color.setRgbF(i / (tempLength * 2.5) - 1, 1- (i- tempLength * 4) / (tempLength * 1.6), 0);
		colorVector.push_back(color);
	}
	for (int i = tempLength * 5 + 1; i<tempLength * 6; i++)// jet
	{
		color.setRgbF(1, (tempLength * 6- i) / (tempLength * 2.5), (i- tempLength * 5) / (tempLength * 12));
		colorVector.push_back(color);
	}
	for (int i = tempLength * 6 + 1; i<tempLength * 7; i++)// jet
	{
		color.setRgbF(1, 0, (i - tempLength * 6)/ (tempLength*1.5));
		colorVector.push_back(color);
	}
	for (int i = tempLength * 7 + 1; i<tempLength; i++)	// jet
	{
		color.setRgbF(1, i / (tempLength * 7) - 1, i / (tempLength * 4) - 1);
		colorVector.push_back(color);
	}
	//for (int i = tempLength / 2 + tempLength + 1; i<tempLength / 2 + 2 * tempLength; i++)// jet
	//{
	//	color.setRgbF((i - tempLength - tempLength / 2) / tempLength, 1, (tempLength * 2 + tempLength / 2 - i) / tempLength);
	//	colorVector.push_back(color);
	//}
	//for (int i = tempLength / 2 + 2 * tempLength + 1; i<tempLength / 2 + 3 * tempLength; i++)// jet
	//{
	//	color.setRgbF(1, (tempLength * 3 + tempLength / 2 - i) / tempLength, 0);
	//	colorVector.push_back(color);
	//}
	//for (int i = tempLength / 2 + 3 * tempLength + 1; i<colorBarLength; i++)// jet
	//{
	//	color.setRgbF((colorBarLength - i + tempLength / 2) / (tempLength), 0, 0);
	//	colorVector.push_back(color);
	//}

}
