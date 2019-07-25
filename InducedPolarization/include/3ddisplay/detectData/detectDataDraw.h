#pragma once
#include <osg/Camera>
#include <osg/Point>
#include <osg/ShapeDrawable>
#include <QtWidgets/QDialog>

class detectDataDraw : public QObject
{
public:
	
	detectDataDraw()
	{
		m_isChangeColor = false;
	}
	~detectDataDraw(){}
	osg::ref_ptr<osg::ShapeDrawable> drawAxisCone(float xPos, float yPos, float zPos, osg::Quat vQuat, osg::Vec4& vColor);
	osg::Geode* makeCoordinate(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);//生成数据的坐标轴
	osg::Geode* drawBoundingBox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);//生成包围盒
	osg::Geode* drawTextFlag(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);//绘制坐标轴刻度尺
private:
	bool m_isChangeColor; //色度条更新
	std::vector<QColor> m_pointColorVec;
};