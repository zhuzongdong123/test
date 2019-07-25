#include "eventHandle/guiEventHandler.h"
#include "tool/sceneTool.h"
#include <osg/MatrixTransform>
#include <osg/LineWidth>


namespace osgEngine
{
	bool cGuiEventHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	{
		osgViewer::View * myView = dynamic_cast<osgViewer::View*>(&aa);

		if (!myView) return false;

		switch (ea.getEventType())
		{
		case osgGA::GUIEventAdapter::PUSH:
			if (osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON == ea.getButton())
			{

			}
			//右键的场合
			else if (osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON == ea.getButton())
			{
				screen2World(osg::Vec3d(ea.getX(), ea.getY(), -1), m_orthoCamera);

			}
			aa.requestRedraw();
			break;
		case osgGA::GUIEventAdapter::DRAG:
			//if (osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON == ea.getButton())

			aa.requestRedraw();
			break;
		case osgGA::GUIEventAdapter::RELEASE:
			if (osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON == ea.getButton())
			{

			}

			aa.requestRedraw();
			break;
		case osgGA::GUIEventAdapter::KEYDOWN:
		{
			switch (ea.getKey())
			{
			case 'f':
			case 'F':
				//aa.requestRedraw();
				break;

			default:
				break;
			}
		}
		case osgGA::GUIEventAdapter::FRAME:
		{

			aa.requestRedraw();
		}
		break;
		case osgGA::GUIEventAdapter::DOUBLECLICK:
			if (osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON == ea.getButton())
			{
				aa.requestRedraw();
			}
			break;
			//滚动事件ctrl+SCROLL_UP/SCROLL_DOWN
		case osgGA::GUIEventAdapter::SCROLL:
		{

		}
		break;
		default:
			break;
			return false;
		}

		//add by zhu
		return false;
	}

}