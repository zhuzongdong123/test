#pragma once

//颜色列表
#include <QtWidgets/QPushButton>
#include <QtWidgets/QColorDialog>
#include <QtGui/QPixmap>
#include <QtGui/QLinearGradient>
#include <QtGui/QPainter>
#include <QtGui/QScreen>
#include <QtGui/QGuiApplication>
#include <QtGui/QMouseEvent>


class myColorButtonV : public QPushButton
{
	Q_OBJECT
public:
	myColorButtonV(QWidget *parent = 0);

	void paintEvent(QPaintEvent* event);

	void mousePressEvent(QMouseEvent *event);

	void changeColor(std::vector<QColor> colorVector);

signals:
	void setColorValue(int red,int green, int blue);

private:
	int m_space;	//间隔
	bool m_isBY;
	std::vector<QColor> m_colorVector;
	QLinearGradient m_linearGradient;
};
