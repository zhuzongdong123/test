#pragma once

//颜色列表
#include <QtWidgets/QPushButton>
#include <QtWidgets/QColorDialog>
#include <QtGui/QPalette>
#include <QtGui/QLinearGradient>
#include <QtGui/QPainter>
#include <myColorMapEditor.h>
#include "DialogMultiColoringDetails.h"

class MyColorButton : public QPushButton
{
	Q_OBJECT
public:
	MyColorButton(QWidget *parent = 0);
	~MyColorButton();

	void paintEvent(QPaintEvent* event);
	void mouseDoubleClickEvent(QMouseEvent* e);
	std::vector<QColor> getColorVec() { return m_colorVector; }
	float getColorMinValue() { return m_minValue; };
	float getColorMaxValue() { return m_maxValue; };

private slots:
	//重新设置文本显示范围
	void setTextRange(float minValue, float maxValue, int number);
	void setTextRange(float minValue, float maxValue);
	void setColorGroupName(QString name);

signals:
	void colorChanged();

private:
	void creatJetColor(float colorBarLength, std::vector<QColor>& colorVector);
	void creatCustomColor(float colorBarLength, std::vector<QColor>& colorVector);
	void creatLargeRainbow(float colorBarLength, std::vector<QColor>& colorVector);

private:
	int m_numberOfLevels;	//等级数量
	int m_startPosX;
	int m_startPosY;
	float m_maxValue;
	float m_minValue;
	std::vector<QColor> m_colorVector;
	QString m_colorGroupName;

	QLinearGradient m_linearGradient;
	DialogMultiColoringDetails* m_multiColoringDetails;
};
