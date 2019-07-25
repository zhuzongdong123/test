#include "drawAxis.h"
#include <osg/geometry>
#include <osg/Geode>
#include <osg/MatrixTransform>
#include "tool/sceneTool.h"
#include <osg/LineWidth>

namespace osgEngine
{
	/******************************************************************************/
	//function:
	void cDrawAxis::drawXAxis(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
	{
		//几何模型的基类，用来描述一个三维模型的所有必要数据
		osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

		//线条颜色是棕色
		osg::ref_ptr<osg::Vec4dArray> colorArray = new osg::Vec4dArray;
		colorArray->push_back(osg::Vec4d(1.0, 1.0, 1.0, 1.0));


		//用来保存模型中所有顶点位置的数组
		osg::ref_ptr<osg::Vec3dArray> pPointArray = new osg::Vec3dArray;
		int stepYLength = (int)((yMax - yMin) / step);
		osg::ref_ptr<osg::Geode> geode = new osg::Geode;
		for (int i = 0; i <= stepYLength; i++)
		{
			pPointArray->push_back(osg::Vec3d(xMax, yMin+i*step, zMin));
			pPointArray->push_back(osg::Vec3d(xMax, yMin+i*step, zMax));

			float tap = 0.5;
			
			osg::Vec3 textPos = osg::Vec3(xMin-tap, yMin + i*step, zMin);
			
			osgText::Text* text = new osgText::Text;
			text->setFont(std::string("detectDataAnalysis//fonts//arial.ttf"));
			text->setCharacterSize(0.7);
			text->setAxisAlignment(osgText::Text::XZ_PLANE);
			text->setPosition(textPos);

			char buf[20];
			text->setColor(osg::Vec4f(1.0, 0.0, 0.0, 1.0));
			int content = (int)yMin + i*step;
			sprintf(buf, "%d\0", content);
			text->setText(buf);
			geode->addDrawable(text);
		}
		geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
		m_AxisNode->addChild(geode.get());
		int stepZLength = (int)((zMax - zMin) / step);
		for (int i = 0; i <= stepZLength; i++)
		{
			pPointArray->push_back(osg::Vec3d(xMax, yMin, zMin + i*step));
			pPointArray->push_back(osg::Vec3d(xMax, yMax, zMin + i*step));
		}

		osg::ref_ptr<osg::Geode> axisGeode = new osg::Geode;

		geom->setVertexArray(pPointArray.get());
		geom->setColorArray(colorArray);
		geom->setColorBinding(osg::Geometry::BIND_OVERALL);

		geom->addPrimitiveSet(new osg::DrawArrays(GL_LINES, 0, pPointArray->size()));
		//axisGeode->addDrawable(geom.get());
		axisGeode->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
		axisGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
		m_AxisNode->addChild(axisGeode.get());
	}
	/******************************************************************************/
	//function:
	void cDrawAxis::drawYAxis(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
	{
		//几何模型的基类，用来描述一个三维模型的所有必要数据
		osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

		//线条颜色是棕色
		osg::ref_ptr<osg::Vec4dArray> colorArray = new osg::Vec4dArray;
		colorArray->push_back(osg::Vec4d(1.0, 1.0, 1.0, 1.0));


		//用来保存模型中所有顶点位置的数组
		osg::ref_ptr<osg::Vec3dArray> pPointArray = new osg::Vec3dArray;
		int stepXLength = (int)((xMax - xMin) / step);
		for (int i = 0; i <= stepXLength; i++)
		{
			pPointArray->push_back(osg::Vec3d(xMin + i*step, yMax, zMin));
			pPointArray->push_back(osg::Vec3d(xMin + i*step, yMax, zMax));
		}

		int stepZLength = (int)((zMax - zMin) / step);
		osg::ref_ptr<osg::Geode> geode = new osg::Geode;
		
		for (int i = 0; i <= stepZLength; i++)
		{
			pPointArray->push_back(osg::Vec3d(xMin, yMax, zMin+i*step));
			pPointArray->push_back(osg::Vec3d(xMax, yMax, zMin+i*step));
						
			float tap = 0.5;
			osg::Vec3 textPos = osg::Vec3(xMin-2*tap, yMax, zMin+i*step);
			/*StateTool::createText(sameGeode, "R1", textPos, 10);*/
			osgText::Text* text = new osgText::Text;
			text->setFont(std::string("detectDataAnalysis//fonts//arial.ttf"));
			text->setCharacterSize(0.7);
			text->setAxisAlignment(osgText::Text::XZ_PLANE);
			text->setPosition(textPos);

			char buf[20];
			text->setColor(osg::Vec4f(1.0, 0.0, 0.0, 1.0));
			int content = (int)zMin + i*step;
			sprintf(buf, "%d\0", content);
			text->setText(buf);
			geode->addDrawable(text);
			
		}
		geode->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
		geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
		m_AxisNode->addChild(geode.get());

		osg::ref_ptr<osg::Geode> axisGeode = new osg::Geode;

		geom->setVertexArray(pPointArray.get());
		geom->setColorArray(colorArray);
		geom->setColorBinding(osg::Geometry::BIND_OVERALL);

		geom->addPrimitiveSet(new osg::DrawArrays(GL_LINES, 0, pPointArray->size()));
		//axisGeode->addDrawable(geom.get());
		axisGeode->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
		axisGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
		m_AxisNode->addChild(axisGeode.get());
	}

	void cDrawAxis::drawQuard(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
	{
		//几何模型的基类，用来描述一个三维模型的所有必要数据
		osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
		osg::ref_ptr<osg::Vec3dArray> normalArray = new osg::Vec3dArray;

		//线条颜色是棕色
		osg::ref_ptr<osg::Vec4dArray> colorArray = new osg::Vec4dArray;
		colorArray->push_back(osg::Vec4d(0.4, 0.4, 0.4, 1.0));
		
		//用来保存模型中所有顶点位置的数组
		osg::ref_ptr<osg::Vec3dArray> pPointArray = new osg::Vec3dArray;
		osg::ref_ptr<osg::Geode> axisGeode = new osg::Geode;
		float tapValue = 0.1;
		pPointArray->push_back(osg::Vec3d(xMin, yMax + tapValue,zMin));
		pPointArray->push_back(osg::Vec3d(xMax, yMax + tapValue, zMin));
		pPointArray->push_back(osg::Vec3d(xMax, yMax + tapValue, zMax));
		pPointArray->push_back(osg::Vec3d(xMin, yMax + tapValue, zMax));
		normalArray->push_back(osg::Vec3d(1, 0, 0));
		normalArray->push_back(osg::Vec3d(1, 0, 0));
		normalArray->push_back(osg::Vec3d(1, 0, 0));
		normalArray->push_back(osg::Vec3d(1, 0, 0));

		pPointArray->push_back(osg::Vec3d(xMin, yMin, zMin - tapValue));
		pPointArray->push_back(osg::Vec3d(xMax, yMin, zMin - tapValue));
		pPointArray->push_back(osg::Vec3d(xMax, yMax, zMin - tapValue));
		pPointArray->push_back(osg::Vec3d(xMin, yMax, zMin - tapValue));
		normalArray->push_back(osg::Vec3d(1, 0, 1));
		normalArray->push_back(osg::Vec3d(1, 0, 1));
		normalArray->push_back(osg::Vec3d(1, 0, 1));
		normalArray->push_back(osg::Vec3d(1, 0, 1));

		geom->setVertexArray(pPointArray.get());
		geom->setColorArray(colorArray);
		geom->setColorBinding(osg::Geometry::BIND_OVERALL);
		geom->setNormalArray(normalArray.get());
		geom->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
		geom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, pPointArray->size()));

		

		axisGeode->addDrawable(geom.get());
		osg::PolygonMode *pLolyTotalMode = new osg::PolygonMode();
		pLolyTotalMode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
		axisGeode->getOrCreateStateSet()->setAttribute(pLolyTotalMode);
		axisGeode->getOrCreateStateSet()->setAttributeAndModes(pLolyTotalMode, osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON);
		axisGeode->getOrCreateStateSet()->setAttribute(new osg::LineWidth(2.0), osg::StateAttribute::ON);


		axisGeode->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
		axisGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
		axisGeode->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);//开启深度测试
		m_AxisNode->addChild(axisGeode.get());
	}
	/******************************************************************************/
	//function:
	void cDrawAxis::drawZAxis(float xMin, float xMax, float yMin, float yMax,float zMin, float zMax)
	{
		//几何模型的基类，用来描述一个三维模型的所有必要数据
		osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

		//线条颜色是棕色
		osg::ref_ptr<osg::Vec4dArray> colorArray = new osg::Vec4dArray;
		colorArray->push_back(osg::Vec4d(1.0, 1.0, 1.0, 1.0));
				
		//用来保存模型中所有顶点位置的数组
		osg::ref_ptr<osg::Vec3dArray> pPointArray = new osg::Vec3dArray;
		int stepXLength = (int)((xMax - xMin) / step);
		osg::ref_ptr<osg::Geode> geode = new osg::Geode;
		for (int i = 0; i <= stepXLength; i++)
		{
			pPointArray->push_back(osg::Vec3d(xMin+i*step,yMin,zMin));
			pPointArray->push_back(osg::Vec3d(xMin+i*step,yMax,zMin));

			float tap = 0.5;
			osg::Vec3 textPos = osg::Vec3(xMin + i*step, yMax, zMax+tap);
			/*StateTool::createText(sameGeode, "R1", textPos, 10);*/
			osgText::Text* text = new osgText::Text;
			//text->setFont(std::string("detectDataAnalysis//fonts//arial.ttf"));
			text->setCharacterSize(0.7);
			text->setAxisAlignment(osgText::Text::XZ_PLANE);
			text->setPosition(textPos);

			char buf[20];
			text->setColor(osg::Vec4f(1.0, 0.0, 0.0, 1.0));
			int content = (int)xMin + i*step;
			sprintf(buf, "%d\0", content);
			text->setText(buf);
			geode->addDrawable(text);
		}
		geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
		m_AxisNode->addChild(geode.get());
		int stepYLength = (int)((yMax - yMin) / step);
		for (int i = 0; i <= stepYLength; i++)
		{
			pPointArray->push_back(osg::Vec3d(xMin, yMin+i*step, zMin));
			pPointArray->push_back(osg::Vec3d(xMax, yMin+i*step, zMin));
		}
		
		osg::ref_ptr<osg::Geode> axisGeode = new osg::Geode;

		geom->setVertexArray(pPointArray.get());
		geom->setColorArray(colorArray);
		geom->setColorBinding(osg::Geometry::BIND_OVERALL);

		geom->addPrimitiveSet(new osg::DrawArrays(GL_LINES, 0, pPointArray->size()));
		//axisGeode->addDrawable(geom.get());
		axisGeode->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
		axisGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
		m_AxisNode->addChild(axisGeode.get());
	}
};

