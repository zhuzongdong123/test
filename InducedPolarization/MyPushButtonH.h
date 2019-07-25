#pragma once

#include <QtWidgets/QPushButton>
#include <QtGui/QPainter>

class MyPushButtonH : public QPushButton
{
	Q_OBJECT
public:
	MyPushButtonH(QWidget *parent = 0);

	void mousePressEvent(QMouseEvent *e) { return; }
	void mouseReleaseEvent(QMouseEvent *e) { return; }

	void paintEvent(QPaintEvent* event);

	//void setDialogName(QString name) { m_dialogName = name; }

	void reDraw(unsigned int text){ m_endChannelIndex = text; }

	void setOperationName(QString name) { m_operationName = name; }

public slots:
	void redrawCoordinateVText(float begChannelDis, float endChannelDis,QString name);

	void redrawCoordinateVText(bool isChanged, int begChannelIndex, int endChannelIndex, int waveNumber);

private:
	bool m_isChanged;
	int m_fixedWidth;
	int m_begChannelIndex;
	int m_endChannelIndex;
	float m_begChannelDis;
	float m_endChannelDis;
	QFont m_font;
	QFont m_fontText;
	QString m_dialogName;
	QString m_operationName;
};