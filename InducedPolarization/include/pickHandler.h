#pragma once

#include <osgGA/GUIEventHandler>
#include <QtCore/QObject>

class PickHandler : public QObject, public osgGA::GUIEventHandler
{
	Q_OBJECT
public:
	PickHandler(void);
	~PickHandler(void);

	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
	void setOrhtoCamera(osg::Camera* pOrthoCamera) { m_orthoCamera = pOrthoCamera; }
	void updatePickDragPoint();
	osg::Vec3d screen2World(osg::Vec3d& screenPoint, osg::Camera* vCamera)//将屏幕坐标转换到世界坐标
	{
		osg::Vec3d vec3;
		osg::Matrix mVPW = vCamera->getViewMatrix() * vCamera->getProjectionMatrix() * vCamera->getViewport()->computeWindowMatrix();
		osg::Matrix invertVPW;
		invertVPW.invert(mVPW);
		vec3 = screenPoint * invertVPW;
		return vec3;
	}
	
	std::vector<float> getAdjustPointYVec() {return m_adjustPointYVec;}

protected:
	void pick(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

signals:
	void updateAdjustData();
	void addPopMenu();
private:
	bool mEnableDragger;
	int m_currentPointIndex;
	float mX;
	float mY;

	osg::Vec3d m_pickDragPoint;
	std::vector<float> m_adjustPointYVec;
	osg::Camera* m_orthoCamera;
};