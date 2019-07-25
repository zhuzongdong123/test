#include "3ddisplay/WalkManipulator.h"
#include <osg/PolygonMode>
#include <3ddisplay/tunnelDraw/tunnelDraw.h>
#include <osgViewer/Renderer>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

namespace osgEngine
{
/****************************************************************************************************************************************************/
//FUNCTION: handle GUI events
//NOTE:     In the distributed environment, this function does not repond to the GUI events, it directly
//          receive the viewer information from server
bool WalkTrackerManipulator::handle(const osgGA::GUIEventAdapter &vEventAdapter, osgGA::GUIActionAdapter &vActionAdapter)
{
    static float angle = 0;
    switch (vEventAdapter.getEventType())
    {
    case osgGA::GUIEventAdapter::PUSH:
        if (osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON == vEventAdapter.getButton())
        {
            addMouseEvent(vEventAdapter);
            vActionAdapter.requestContinuousUpdate(true);
            if (updateRotation())
                return true;
        }
        vActionAdapter.requestRedraw();
    case osgGA::GUIEventAdapter::DRAG:
    {
        addMouseEvent(vEventAdapter);
        vActionAdapter.requestContinuousUpdate(true);
        if (updateRotation())
            return true;
        vActionAdapter.requestRedraw();
    }
    case osgGA::GUIEventAdapter::RELEASE:
    {
        //clear the mouse event stack when the mouse button is released
        //this step is necessary, otherwise, click mouse twice in different places will move the camera
        flushMouseEventStack();
        return true;
    }
    case osgGA::GUIEventAdapter::KEYDOWN:
    {
        switch (vEventAdapter.getKey())
        {
        case osgGA::GUIEventAdapter::KEY_Up:
            moveForward();
            vActionAdapter.requestRedraw();
            return true;
        case osgGA::GUIEventAdapter::KEY_Down:
            moveBackward();
            vActionAdapter.requestRedraw();
            return true;
        case osgGA::GUIEventAdapter::KEY_Left:
            moveLeft();
            vActionAdapter.requestRedraw();
            return true;
        case osgGA::GUIEventAdapter::KEY_Right:
            moveRight();
            vActionAdapter.requestRedraw();
            return true;
        case osgGA::GUIEventAdapter::KEY_Home:
            moveUp();
            break;
        case osgGA::GUIEventAdapter::KEY_End:
            moveDown();
            break;

        default:
            return false;
        }
    }
    case osgGA::GUIEventAdapter::FRAME:
    {
        vActionAdapter.requestRedraw();
        break;
    }
    case osgGA::GUIEventAdapter::SCROLL:
    {
        const int moveSpeed = 10;
        osg::Vec3f Eye, Lookat, Up, MoveDir, NewPos;
        if (vEventAdapter.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_UP)
        {
            // mouse scroll up event
            getInverseMatrix().getLookAt(Eye, Lookat, Up);
            MoveDir = (Lookat - Eye);
            MoveDir.normalize();

            NewPos.x() = m_Eye.x() + MoveDir.x() * moveSpeed;
            NewPos.y() = m_Eye.y() + MoveDir.y() * moveSpeed;
            NewPos.z() = m_Eye.z() + MoveDir.z() * moveSpeed;
            //if (!isClision(NewPos,m_Eye))
            {
                m_Eye = NewPos;
            }
            vActionAdapter.requestRedraw();
        }
        else
        {
            // mouse scroll up event
            getInverseMatrix().getLookAt(Eye, Lookat, Up);
            MoveDir = (Lookat - Eye);
            MoveDir.normalize();

            NewPos.x() = m_Eye.x() - MoveDir.x() * moveSpeed;
            NewPos.y() = m_Eye.y() - MoveDir.y() * moveSpeed;
            NewPos.z() = m_Eye.z() - MoveDir.z() * moveSpeed;
            //if (!isClision(NewPos,m_Eye))
            {
                m_Eye = NewPos;
            }
            vActionAdapter.requestRedraw();
        }
        break;
    }
        return false;
    }

    //add by zhu
    return false;
}

/****************************************************************************************************************************************************/
//FUNCTION: move the eye forward
void WalkTrackerManipulator::moveForward()
{
    osg::Vec3f Eye, Lookat, Up, MoveDir, NodeDir, NewPos, NodePos;
    osg::Quat modelRota;

    getInverseMatrix().getLookAt(Eye, Lookat, Up);
    MoveDir = (Lookat - Eye);
    MoveDir.normalize();
    NewPos = m_Eye;
    NewPos.x() += MoveDir.x() * (m_EyeMoveSpeed + 5);
    NewPos.y() += MoveDir.y() * (m_EyeMoveSpeed + 5);

    if (MoveDir.x() > 0)
    {
        NewPos.x() += 35;
    }
    else
        NewPos.x() -= 35;

    //if (!isClision(NewPos,m_Eye))
    {
        m_Eye.x() += MoveDir.x() * m_EyeMoveSpeed;
        m_Eye.y() += MoveDir.y() * m_EyeMoveSpeed;

        return;
    }
}

/****************************************************************************************************************************************************/
//FUNCTION: move the eye backward
void WalkTrackerManipulator::moveBackward()
{
    osg::Vec3f Eye, Lookat, Up, MoveDir, NewPos, NodePos;

    getInverseMatrix().getLookAt(Eye, Lookat, Up);
    MoveDir = Eye - Lookat;
    MoveDir.normalize();
    NewPos = m_Eye;
    NewPos.x() += MoveDir.x() * (m_EyeMoveSpeed + 5);
    NewPos.y() += MoveDir.y() * (m_EyeMoveSpeed + 5);
    //if (!isClision(NewPos,m_Eye))
    //{
    m_Eye.x() += MoveDir.x() * m_EyeMoveSpeed;
    m_Eye.y() += MoveDir.y() * m_EyeMoveSpeed;
    //}
}

/****************************************************************************************************************************************************/
//FUNCTION: move the eye left
void WalkTrackerManipulator::moveLeft()
{
    osg::Vec3f Eye, Lookat, Up, MoveDir, NewPos;
    getInverseMatrix().getLookAt(Eye, Lookat, Up);
    MoveDir = Up ^ (Lookat - Eye);

    MoveDir.normalize();
    NewPos = m_Eye + MoveDir * (m_EyeMoveSpeed + 5);
    //if (!isClision(NewPos,m_Eye))
    {
        m_Rotation.z() += m_RotationSpeed * 0.02;
        m_Eye.x() += MoveDir.x() * m_EyeMoveSpeed;
    }
    /*else
		{
			m_Rotation.z() += m_RotationSpeed*0.02;
		}*/
}

/****************************************************************************************************************************************************/
//FUNCTION: move the eye right
void WalkTrackerManipulator::moveRight()
{
    osg::Vec3f Eye, Lookat, Up, MoveDir, NodeDir, NewPos;
    getInverseMatrix().getLookAt(Eye, Lookat, Up);
    MoveDir = (Lookat - Eye) ^ Up;
    MoveDir.normalize();
    NewPos = m_Eye + MoveDir * (m_EyeMoveSpeed + 5);
    //if (!isClision(NewPos,m_Eye))
    {
        m_Rotation.z() -= m_RotationSpeed * 0.02;
        m_Eye.x() += MoveDir.x() * m_EyeMoveSpeed;
    }
    /*else
		{
			m_Rotation.z() -= m_RotationSpeed*0.02;
		}*/
}

/****************************************************************************************************************************************************/
//FUNCTION: move the eye up
void WalkTrackerManipulator::moveUp()
{
    osg::Vec3f Eye, Lookat, Up, MoveDir, NewPos;

    getInverseMatrix().getLookAt(Eye, Lookat, Up);
    MoveDir = -Up;
    MoveDir.normalize();
    NewPos = m_Eye + MoveDir * (m_EyeMoveSpeed + 5);
    //if (!isClision(NewPos,m_Eye))
    {
        m_Eye += MoveDir * m_EyeMoveSpeed;
    }
}

/****************************************************************************************************************************************************/
//FUNCTION: move the eye up
void WalkTrackerManipulator::moveDown()
{
    osg::Vec3f Eye, Lookat, Up, MoveDir, NewPos;
    getInverseMatrix().getLookAt(Eye, Lookat, Up);
    MoveDir = Up;
    MoveDir.normalize();
    NewPos = m_Eye + MoveDir * (m_EyeMoveSpeed + 5);

    m_Eye += MoveDir * m_EyeMoveSpeed;
}

/****************************************************************************************************************************************************/
//FUNCTION: for the give mouse movement recorded in the internal mouse event stack, calculate the rotation matrix
bool WalkTrackerManipulator::updateRotation()
{
    // return if less than two mouse events have been added.
    if ((NULL == m_Mouse_t0.get()) || (NULL == m_Mouse_t1.get()))
        return false;

    // rotate camera.
    double px0 = m_Mouse_t0->getXnormalized();
    double py0 = m_Mouse_t0->getYnormalized();
    double px1 = m_Mouse_t1->getXnormalized();
    double py1 = m_Mouse_t1->getYnormalized();
    //旋转方向判断
    double dx = px1 - px0;
    double dy = py1 - py0;

    if (m_Mouse_t1->getButtonMask() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
    {
        double angle = osg::RadiansToDegrees(atan2(dy, dx));
        if ((angle > 45.0 && angle < 135.0) || (angle > -135.0 && angle < -45.0))
        {
            dx = 0.0;
        }
        else
        {
            dy = 0.0;
        }
        m_Rotation.y() += dx * m_RotationSpeed * 0.3;
        m_Rotation.x() += dy * m_RotationSpeed * 0.1;

        //幅度控制
//         if (m_Rotation.x() > osg::PI_2 + osg::PI_4)
//         {
//             m_Rotation.x() = osg::PI_2 + osg::PI_4;
//         }
//         else if (m_Rotation.x() < osg::PI_2 - osg::PI_4)
//         {
//             m_Rotation.x() = osg::PI_2 - osg::PI_4;
//         }
    }
    else if (m_Mouse_t1->getButtonMask() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
    {
        const int moveXSpeed = 3000;
        const int moveZSpeed = 1000;

        osg::Vec3f Eye, Lookat, Up, MoveDir;
        getInverseMatrix().getLookAt(Eye, Lookat, Up);
        MoveDir = Up ^ (Lookat - Eye);
        MoveDir.normalize();

        osg::Vec3f NewPos = m_Eye;
        NewPos.z() += dy * moveZSpeed;
        NewPos.y() -= dx * moveXSpeed * MoveDir.y();
        NewPos.x() -= dx * moveXSpeed * MoveDir.x();
        //if (!isClision(NewPos,m_Eye))
        {
            m_Eye.z() += dy * moveZSpeed;
            m_Eye.y() -= dx * moveXSpeed * MoveDir.y();
            m_Eye.x() -= dx * moveXSpeed * MoveDir.x();
        }
    }
    return true;
}

/****************************************************************************************************************************************************/
//FUNCTION: clear the mouse event stack
void WalkTrackerManipulator::flushMouseEventStack()
{
    m_Mouse_t0 = NULL;
    m_Mouse_t1 = NULL;
}

/****************************************************************************************************************************************************/
//FUNCTION: Add the current mouse GUIEvent to internal stack
void WalkTrackerManipulator::addMouseEvent(const osgGA::GUIEventAdapter &vEventAdapter)
{
    m_Mouse_t1 = m_Mouse_t0;
    m_Mouse_t0 = &vEventAdapter;
}

WalkTrackerManipulator::WalkTrackerManipulator(osg::Vec3d &vEyePos /*=osg::Vec3d(30,-100,0)*/)
{
    reset(vEyePos);
}

WalkTrackerManipulator::~WalkTrackerManipulator()
{
}

void WalkTrackerManipulator::setByMatrix(const osg::Matrixd &vMatrix)
{
}

osg::Matrixd WalkTrackerManipulator::getMatrix() const
{
    osg::Matrixd mat;
    mat.makeRotate(m_Rotation.x(), osg::Vec3(1, 0, 0),
                   m_Rotation.y(), osg::Vec3(0, 1, 0),
                   m_Rotation.z(), osg::Vec3(0, 0, 1));

    return mat * osg::Matrixd::translate(m_Eye);
}

/****************************************************************************************************************************************************/
//FUNCTION: get the position of the manipulator as a inverse matrix of the manipulator, typically used as a model view matrix.
osg::Matrixd WalkTrackerManipulator::getInverseMatrix() const
{
    osg::Matrixd mat;
    mat.makeRotate(m_Rotation.x(), osg::Vec3(1, 0, 0),
                   m_Rotation.y(), osg::Vec3(0, 1, 0),
                   m_Rotation.z(), osg::Vec3(0, 0, 1));
    return osg::Matrixd::inverse(mat * osg::Matrixd::translate(m_Eye));
}

/****************************************************************************************************************************************************/
//FUNCTION: set the initial information of the manipulator
void WalkTrackerManipulator::reset(osg::Vec3d &vEyePos)
{
    m_Eye           = vEyePos;                    //osg::Vec3(30, -100, 0);
    m_Rotation      = osg::Vec3(osg::PI_2, 0, 0); //一般让相机绕x轴旋转90度，否则相机会从上空看模型
    m_EyeMoveSpeed  = 2.0;
    m_RotationSpeed = 2.0;
}

void WalkTrackerManipulator::setEyePos(osg::Vec3f vEye)
{
    m_Eye           = vEye;
    m_Rotation      = osg::Vec3(osg::PI_2, 0, 0); //一般让相机绕x轴旋转90度，否则相机会从上空看模型
    m_EyeMoveSpeed  = 2.0;
    m_RotationSpeed = 2.0;
}
}