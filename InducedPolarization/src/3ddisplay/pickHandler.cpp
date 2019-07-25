#include "pickHandler.h"
#include <osgViewer/Viewer>

PickHandler::PickHandler(void)
{
}


PickHandler::~PickHandler(void)
{
}

bool PickHandler::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	osgViewer::View* view = dynamic_cast<osgViewer::View*> (&aa);
	if (NULL == view)
	{
		return false;
	}

	switch (ea.getEventType())
	{
	case osgGA::GUIEventAdapter::DOUBLECLICK:
	{
		//右键的场合
		if (osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON == ea.getButton())
		{
			emit doubleClicked();
		}
		aa.requestRedraw();
		break;
	}
	break;
	case osgGA::GUIEventAdapter::KEYDOWN:
	{
	}
	case osgGA::GUIEventAdapter::DRAG:
		aa.requestRedraw();
		break;
	case osgGA::GUIEventAdapter::RELEASE:
		aa.requestRedraw();
		break;
		break;

	default:
		break;
	}

	return false;
}

void PickHandler::updatePickDragPoint()
{
	m_adjustPointYVec.clear();
	osg::Geode* pPointsGeode = NULL;
	for (unsigned int i = 0; i < m_orthoCamera->getNumChildren(); i++)
	{
		pPointsGeode = dynamic_cast<osg::Geode*>(m_orthoCamera->getChild(i));
		if (NULL != pPointsGeode && strcmp(pPointsGeode->getName().c_str(), "adjustPointGeode") == 0)
		{
			osg::ref_ptr<osg::Geometry> geomPoints = dynamic_cast<osg::Geometry*>(pPointsGeode->getChild(0));
			if (NULL != geomPoints)
			{
				osg::Vec2dArray* pPointsArray = dynamic_cast<osg::Vec2dArray*>(geomPoints->getVertexArray());
				osg::Vec4dArray* pPointColorArray = dynamic_cast<osg::Vec4dArray*>(geomPoints->getColorArray());

				if (NULL != pPointColorArray && pPointColorArray->size() >= 1)
				{
					pPointColorArray->clear();
					for (unsigned int j = 0; j < pPointsArray->size(); j++)
					{
						pPointColorArray->push_back(osg::Vec4d(0, 1, 0, 1.0));
					}
				}

				if (NULL != pPointsArray)
				{
					(*pPointsArray)[m_currentPointIndex].y() = m_pickDragPoint.y();
					geomPoints->setVertexArray(pPointsArray);
					geomPoints->setColorArray(pPointColorArray);
					geomPoints->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
				}

				for (unsigned int j = 0; j < pPointsArray->size(); j++)
				{
					m_adjustPointYVec.push_back((*pPointsArray)[j].y());
				}
			}
		}

		if (NULL != pPointsGeode && strcmp(pPointsGeode->getName().c_str(), "adjustLineGeode") == 0)
		{
			osg::ref_ptr<osg::Geometry> geomPoints = dynamic_cast<osg::Geometry*>(pPointsGeode->getChild(0));
			if (NULL != geomPoints)
			{
				osg::Vec2dArray* pPointsArray = dynamic_cast<osg::Vec2dArray*>(geomPoints->getVertexArray());

				osg::Vec4dArray* pPointColorArray = dynamic_cast<osg::Vec4dArray*>(geomPoints->getColorArray());

				if (NULL != pPointColorArray && pPointColorArray->size() >= 1)
				{
					pPointColorArray->clear();
					for (unsigned int j = 0; j < pPointsArray->size(); j++)
					{
						pPointColorArray->push_back(osg::Vec4d(0, 1, 0, 1.0));
					}
				}

				if (NULL != pPointsArray)
				{
					(*pPointsArray)[m_currentPointIndex].y() = m_pickDragPoint.y();
					geomPoints->setVertexArray(pPointsArray);
					geomPoints->setColorArray(pPointColorArray);
					geomPoints->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
				}
			}
		}
	}
}

void PickHandler::pick(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	osgViewer::View* view = dynamic_cast<osgViewer::View*> (&aa);
	osgUtil::LineSegmentIntersector::Intersections hits;

	double currentPickXPos = ea.getX();
	double currentPickYPos = ea.getY();

	osg::Vec3d orthPointPos = screen2World(osg::Vec3d(currentPickXPos, currentPickYPos, -1), m_orthoCamera);//将屏幕坐标转换到世界坐标

	osg::Geode* pPointsGeode = NULL;
	for (unsigned int i = 0; i < m_orthoCamera->getNumChildren(); i++)
	{
		pPointsGeode = dynamic_cast<osg::Geode*>(m_orthoCamera->getChild(i));
		if (NULL != pPointsGeode && strcmp(pPointsGeode->getName().c_str(), "adjustPointGeode") == 0)
		{
			osg::ref_ptr<osg::Geometry> geomPoints = dynamic_cast<osg::Geometry*>(pPointsGeode->getChild(0));
			if (NULL != geomPoints)
			{
				osg::Vec2dArray* pPointsArray = dynamic_cast<osg::Vec2dArray*>(geomPoints->getVertexArray());

				osg::Vec4dArray* pPointColorArray = dynamic_cast<osg::Vec4dArray*>(geomPoints->getColorArray());

				if (NULL != pPointColorArray && pPointColorArray->size() >= 1)
				{
					osg::Vec4d colorValue = (*pPointColorArray)[0];
					pPointColorArray->clear();
					for (unsigned int j = 0; j < pPointsArray->size(); j++)
					{
						pPointColorArray->push_back(colorValue);
					}
				}

				if (NULL != pPointsArray)
				{
					for (unsigned int j = 0; j < pPointsArray->size(); j++)
					{
						if (fabs((*pPointsArray)[j].x() - orthPointPos.x()) < 2.5 &&
							fabs((*pPointsArray)[j].y() - orthPointPos.y()) < 2.5)
						{
							(*pPointColorArray)[j].x() = 0.1;
							(*pPointColorArray)[j].y() = 0.1;
							(*pPointColorArray)[j].z() = 0.1;
							geomPoints->setColorArray(pPointColorArray);
							geomPoints->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
							m_currentPointIndex = j;
						}
					}
				}
			}
		}
	}
}