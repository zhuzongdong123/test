#include "myColorButtonV.h"

myColorButtonV::myColorButtonV(QWidget *parent /*= 0*/) : QPushButton(parent)
{
	setParent(parent);
	m_linearGradient = QLinearGradient(0, this->height() / 2, this->width(), this->height() / 2);
	m_linearGradient.setColorAt(1, QColor(255, 255, 255));
	m_space = 10;	//初始时，固定10个间隔,可以随时调整
	m_isBY = false;
}

void myColorButtonV::paintEvent(QPaintEvent* event)
{
	QPushButton::paintEvent(event);

	QPainter painter(this);
	if (!m_isBY)
	{
		//创建了一个QLinearGradient对象实例，参数为起点和终点坐标，可作为颜色渐变的方向
		m_linearGradient.setStart(0, this->height() / 2);
		m_linearGradient.setFinalStop(this->width(), this->height() / 2);
		painter.setBrush(QBrush(m_linearGradient));
		painter.drawRect(0, 0, this->width(), this->height());
	}
	else
	{
		for (int i = 0; i < m_colorVector.size(); i++)
		{
			QColor color = m_colorVector[i];
			painter.setBrush(QBrush(color));
			if (i == 0)
			{
				painter.drawRect(0, 0, this->width() / 2, this->height());
			}
			else
			{
				painter.drawRect(this->width() / 2, 0, this->width() / 2, this->height());
			}
		}
	}
}

void myColorButtonV::mousePressEvent(QMouseEvent *event)
{
	WId winId = NULL;
	winId = this->winId();
	if (NULL != winId)
	{
		int x = event->x();
		int y = event->y();
		QScreen *screen = qApp->primaryScreen(); //主屏
		QPixmap pixmap = screen->grabWindow(winId, x, y, 1, 1);//截窗口

		if (!pixmap.isNull()) //如果像素图不为NULL
		{
			QImage image = pixmap.toImage();//将像素图转换为QImage
			if (!image.isNull()) //如果image不为空
			{
				if (image.valid(0, 0)) //坐标位置有效
				{
					QColor color = image.pixel(0, 0);
					int red = color.red();
					int green = color.green();
					int blue = color.blue();

					emit setColorValue(red, green, blue);
				}
			}
		}
	}
	return;
}

void myColorButtonV::changeColor(std::vector<QColor> colorVector)
{
	m_isBY = false;
	QColor color;
	int vectorSize = colorVector.size();
	if (vectorSize == 0)
	{
		return;
	}
	else if (vectorSize == 2)
	{
		m_isBY = true;
		m_colorVector = colorVector;
	}
	else
	{
		float radio = float(0.1 * m_space) / vectorSize;
		for (int i = 1; i <= vectorSize; i++)
		{
			color = colorVector[i - 1];
			float f = radio*i;
			m_linearGradient.setColorAt(f, color);
		}
	}
	update();
}
