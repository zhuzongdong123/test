#pragma once
#include "3ddisplay/ViewerWidget2d.h"
#include <memory>

using namespace std;

enum DataType
{
	measuredData = 0,	//ʵ������
	simulationData,		//ģ������
	ajustData			//����ƫ��ֵ
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
	
	//���Ʊ�������
	void drawBackgroundLine(float windWidth, float windHeight);
	void resizeEvent(QResizeEvent *e);

	//���ƶ���
	void drawPreDataPoints(osg::ref_ptr<osg::Vec2dArray> pPointsArray, osg::Vec4d vColor, DataType type);
	//���ƶ�ά����
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
