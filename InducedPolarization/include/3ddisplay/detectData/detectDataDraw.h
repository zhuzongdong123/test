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
	osg::Geode* makeCoordinate(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);//�������ݵ�������
	osg::Geode* drawBoundingBox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);//���ɰ�Χ��
	osg::Geode* drawTextFlag(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);//����������̶ȳ�
private:
	bool m_isChangeColor; //ɫ��������
	std::vector<QColor> m_pointColorVec;
};