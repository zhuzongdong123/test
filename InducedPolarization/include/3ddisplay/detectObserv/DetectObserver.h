#pragma once
#include "3ddisplay/ViewerWidget3d.h"
#include "WalkManipulator.h"
#include <memory>

using namespace std;

class DetectObserver : public ViewerWidget3d
{
	Q_OBJECT
public:
	DetectObserver(QWidget* parent = nullptr);
	~DetectObserver();

	void initScene();
	void drawTunnel(float circleLen, unsigned int circleCount);
	//用三角形逼近画圆
	void Init_Circle(float circle1[36][2], float Radius, int &vCircleNum);
	void drawTunnel(osg::Vec3d& circlePos, float eachTunelCircleLen, int tunelSegmentNum, float Radius);
	void drawMeasurePointLine(std::vector<osg::Vec3d> measurePoint);
	void drawElectroPoints(std::vector<osg::Vec3d> electroPoint, std::vector<double> disVec);
	osg::ref_ptr<osg::MatrixTransform> createCylinder(osg::Vec3 &from, osg::Vec3 &to, float radius);
	/****************************************************************************************************************************************************************************************/
	//绘制探测数据的坐标轴
	void drawElecMesureTextFlag(std::vector<double> vFaceDistanceVec,float xPos, float yPos, float zPos = 0.0);

public slots:
	void setTunnelGrid(bool isTunnelGrid);
	void setTunnelEntity(bool isTunnelEntity);
	void setTunnelView(bool value);//隧道360度旋转

private:

	osg::ref_ptr<osg::Group> m_pTunnelGroup;
	osg::ref_ptr<osg::Group> m_pMeasureGroup;
	osg::ref_ptr<osg::Group> m_pElectGroup;
	osg::ref_ptr<osgEngine::WalkTrackerManipulator> m_walkTracker;

	float m_tunnelLen = 0.0f;

	bool m_isTunnelGrid;
	bool m_isTunnelEntity;
};
