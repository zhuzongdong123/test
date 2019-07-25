#pragma once
#include "3ddisplay/ViewerWidget2d.h"
#include <memory>

using namespace std;

enum DataType
{
	measuredData = 0,	//实测数据
	simulationData,		//模拟数据
	ajustData			//数据偏移值
};

class DataPreprocess : public ViewerWidget
{
	Q_OBJECT
public:
	DataPreprocess(QWidget *parent = nullptr);
	~DataPreprocess() {}

	void clearLinesData();
	void draw(std::vector<double> resultDataVec, osg::Vec4d vColor, DataType type);
	double getMaxValue() { return m_maxValue; }
	void setMaxValue(double value) { m_maxValue = value; }
	unsigned int getMaxWidth() { return m_maxWidth; }
	void setMaxWidth(unsigned int value) { m_maxWidth = value; }
	
	//绘制背景虚线
	void drawBackgroundLine(float windWidth, float windHeight);
	void resizeEvent(QResizeEvent *e);

	//绘制顶点
	void drawPreDataPoints(osg::ref_ptr<osg::Vec2dArray> pPointsArray, osg::Vec4d vColor, DataType type);
	//绘制二维曲线
	void drawPointsLine(osg::ref_ptr<osg::Vec2dArray> pPointsArray, osg::Vec4d vColor, DataType type);

	double getVariance(std::vector<double> resultVec);
	std::vector<float> adjustPointYValue();

signals:
	void reDraw();

private:
	double m_maxValue;
	unsigned int m_maxWidth;
	bool m_isReDraw;

	shared_ptr<QPixmap> _originPixmap;

	shared_ptr<QLabel> m_legendLabel;
};
