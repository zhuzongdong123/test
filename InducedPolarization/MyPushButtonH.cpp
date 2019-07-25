#include "MyPushButtonH.h"

MyPushButtonH::MyPushButtonH(QWidget *parent /*= 0*/) : QPushButton(parent)
{
	setParent(parent);
	m_fixedWidth = 40;	//纵轴的固定宽度
	this->setMinimumSize(QSize(0, m_fixedWidth));
	this->setMaximumSize(QSize(16777215, m_fixedWidth));
	m_isChanged = true;
	m_endChannelDis = 0.0;
	m_endChannelIndex = 0;
	m_dialogName = "";

	m_begChannelIndex = 0;
	m_endChannelIndex = 0;

	m_fontText.setFamily("Microsoft YaHei");
	m_font.setFamily("Microsoft YaHei");
	m_font.setPointSize(12);
	//m_font.setItalic(true);
	//m_font.setBold(true);
	//m_font.setLetterSpacing(QFont::AbsoluteSpacing, 1);
}

void MyPushButtonH::paintEvent(QPaintEvent* event)
{
	if (m_operationName == "")
	{
		if (m_endChannelIndex == 0)
		{
			return;
		}

		float thisWidth = this->width() - 1;

		QPushButton::paintEvent(event);

		if (m_isChanged)
		{
			m_begChannelIndex = 0;
		}

		if (m_endChannelIndex == 0)
		{
			return;
		}

		int channelSpace = m_endChannelIndex - m_begChannelIndex + 1;
		int space = 1;
		if (channelSpace > 11 || this->width() < 300)	space = 5;
		QPainter painter(this);
		painter.setFont(m_fontText);

		float averageValue = float(thisWidth - m_fixedWidth) / channelSpace;
		int begChannelIndex = m_begChannelIndex;
		for (int i = m_begChannelIndex; i < m_endChannelIndex; i += space)
		{
			painter.setPen(QPen(Qt::black, 4));
			painter.drawText(averageValue*(i - begChannelIndex) + m_fixedWidth, this->height() / 2 + 10, QString::number(i));
		}

		//坐标轴名称
		painter.setFont(m_font);
		painter.setPen(QPen(Qt::black, 5));
		painter.drawText(width() / 2, this->height() / 2 - 5, "Trace");
	}
	else if (m_operationName == "MyWidgetHalfLifeCurve")
	{
		if (fabs(m_endChannelDis) < 1e-15)
		{
			return;
		}

		QPushButton::paintEvent(event);
		QPainter painter(this);
		painter.setFont(m_fontText);
		painter.setPen(QPen(Qt::black, 4));
		//默认从0开始
		float averageValue = float(width() - m_fixedWidth) / (m_endChannelDis);

		int space = 1;
		if (m_endChannelDis > 11 || width() < 300)	space = 5;
		for (int i = m_begChannelIndex; i < m_endChannelDis; i += space)
		{
			painter.drawText(averageValue*(i)+m_fixedWidth, this->height() / 2 + 10, QString::number(i));
		}

		//坐标轴名称
		painter.setFont(m_font);
		painter.setPen(QPen(Qt::black, 5));
		painter.drawText(width() / 2, this->height() / 2 - 5, "Trace");
	}
}

void MyPushButtonH::redrawCoordinateVText(float begChannelDis, float endChannelDis, QString name)
{
	m_begChannelDis = begChannelDis;
	m_endChannelDis = endChannelDis;
	m_operationName = name;
	update();
}

void MyPushButtonH::redrawCoordinateVText(bool isChanged, int begChannelIndex, int endChannelIndex, int waveNumber)
{
	m_isChanged = isChanged;
	if (begChannelIndex > endChannelIndex)
	{
		//交换
		int temp;
		temp = begChannelIndex;
		begChannelIndex = endChannelIndex;
		endChannelIndex = temp;
	}
	m_begChannelIndex = begChannelIndex;
	m_endChannelIndex = endChannelIndex;

	if (isChanged)
	{
		m_endChannelIndex = waveNumber;
	}
	update();
}
