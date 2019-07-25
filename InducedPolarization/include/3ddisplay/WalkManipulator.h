#pragma once

#include <osgGA/TrackballManipulator>
#include <osg/Quat>
#include <osgUtil/IntersectVisitor>
#include <osg/ComputeBoundsVisitor>
#include <osgViewer/Viewer>
#include <osgGA/CameraManipulator>
#include <QtCore/QObject>

namespace osgEngine
{
class WalkTrackerManipulator : public QObject, public osgGA::CameraManipulator
{
    Q_OBJECT
  public:
    WalkTrackerManipulator(osg::Vec3d &vEyePos = osg::Vec3d(30, -100, 0));

    ~WalkTrackerManipulator();

    virtual void setByMatrix(const osg::Matrixd &vMatrix);
    virtual void setByInverseMatrix(const osg::Matrixd &vMatrix) { setByMatrix(osg::Matrixd::inverse(vMatrix)); }
    virtual osg::Matrixd getMatrix() const;
    virtual osg::Matrixd getInverseMatrix() const;

    virtual bool handle(const osgGA::GUIEventAdapter &vEventAdapter, osgGA::GUIActionAdapter &vActionAdapter);

    void reset(osg::Vec3d &vEyePos);
    void setEyePos(osg::Vec3f vEye);
    void setEye(osg::Vec3f eye) { m_Eye = eye; }
    void setRotation(osg::Vec3f rotation) { m_Rotation = rotation; }
    void setTabIndex(int index) { m_currentTabIndex = index; }

  protected:
    void addMouseEvent(const osgGA::GUIEventAdapter &vEventAdapter);
    void flushMouseEventStack();

    virtual bool updateRotation();

    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    osg::Vec3 m_Rotation;
    osg::Vec3f m_Eye;
    osg::Vec3f m_CurrentEye;
    osg::Vec3f m_HomeEye;

  private:
    bool m_pickDrag;
    unsigned int m_currentTabIndex; //用于保存图片
    osg::ref_ptr<const osgGA::GUIEventAdapter> m_Mouse_t2;
    osg::ref_ptr<const osgGA::GUIEventAdapter> m_Mouse_t1;
    osg::ref_ptr<const osgGA::GUIEventAdapter> m_Mouse_t0;
    float m_RotationSpeed;
    float m_EyeMoveSpeed;
};
}
