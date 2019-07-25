#pragma once
//纵向坐标轴
//#include "matlab/osg/leftViewWidget.h"
#include <QtWidgets/QPushButton>
#include <QtGui/QPainter>

class MyPushButtonV : public QPushButton
{
	Q_OBJECT
public:
	MyPushButtonV(QWidget *parent = 0) : QPushButton(parent) 
	{
		setParent(parent);
		m_fixedWidth = 40;	//纵轴的固定宽度
		this->setMinimumSize(QSize(m_fixedWidth, 0));
		this->setMaximumSize(QSize(m_fixedWidth, 16777215));
		m_fontText.setFamily("Microsoft YaHei");
		m_font.setFamily("Microsoft YaHei");
		m_font.setPointSize(12);
		m_maxValue = 0.0;
		m_minValue = 0.0;
	}

	void mousePressEvent(QMouseEvent *e) { return; }
	void mouseReleaseEvent(QMouseEvent *e) { return; }

	void paintEvent(QPaintEvent* event)
	{
		if (fabs(m_maxValue) < 1e-15)
		{
			/*if (!isHidden())
			{
				this->hide();
			}*/	
			return;
		}
		/*else
		{
			if (isHidden())
			{
				show();
			}
		}*/

		QPushButton::paintEvent(event);
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);
		painter.setPen(QPen(Qt::black, 1));
		painter.setFont(m_fontText);
		char buf[64];
		unsigned int textNum;
		if (this->height() >= 490)
		{
			textNum = 10;
		}
		else if (this->height() < 490 && this->height() > 260)
		{
			textNum = 5;
		}
		else
		{
			textNum = 3;
		}

		for (int i = textNum-1; i >0; i--)
		{				
			painter.translate(0, this->height());    // 第1步：变换旋转中心到所绘制文字左下角
			painter.rotate(-90);                    // 第2步： 旋转一定角度
			if (m_operationName == "MyWidgetHalfLifeCurve")
			{
				sprintf(buf, "%0.1f", m_minValue + (textNum - i)*((m_maxValue - m_minValue) / textNum));
			}
			else
			{
				sprintf(buf, "%0.4f", m_minValue + (textNum - i)*((m_maxValue - m_minValue) / textNum));
			}		
			painter.drawText((this->height() / textNum)*(textNum - i)-10, m_fixedWidth - 5, buf);
			painter.resetMatrix();                  // 第4步： 恢复坐标旋转
			painter.drawLine(QPoint(width() - 3, (float(this->height()) / textNum)*(textNum - i)), QPoint(width(), (float(this->height()) / textNum)*(textNum - i)));
		}

		//绘制坐标轴名称
		painter.translate(0, this->height());    // 第1步：变换旋转中心到所绘制文字左下角
		painter.rotate(-90);
		painter.setFont(m_font);
		painter.setPen(QPen(Qt::black, 5));
		painter.drawText(this->height() / 2, m_fixedWidth / 2, "Time(S)");
		painter.resetMatrix();                  // 第4步： 恢复坐标旋转
	}


	void setOperationName(QString name) { m_operationName = name; }

public slots:
void reDraw(double minValue, double maxValue, QString name) { m_maxValue = maxValue; m_minValue = minValue; m_operationName = name; }

private:
	int m_fixedWidth;
	QFont m_font;
	QFont m_fontText;
	double m_maxValue;
	double m_minValue;
	QString m_operationName;
};