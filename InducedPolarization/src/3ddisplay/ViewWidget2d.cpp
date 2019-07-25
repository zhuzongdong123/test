#include "3ddisplay/ViewerWidget2d.h"
#include <osgText/Text>
#include <osg/LineWidth>
#include "drawAxis.h"
#include <QScrollArea>
#include "Timer.h"

/*************************************************************************************************************************************************************************************/
//function: draw the axis cone
osg::ref_ptr<osg::ShapeDrawable> axisBaseDraw::drawAxisCone(float xPos, float yPos, float zPos,
	osg::Quat vQuat, osg::Vec4& vColor, float coneRadius, float coneHeight)
{
	osg::ref_ptr<osg::Cone> pConeZ = new osg::Cone;
	osg::ref_ptr<osg::ShapeDrawable> pShapeZ = new osg::ShapeDrawable(pConeZ);
	pShapeZ->setColor(vColor);
	pConeZ->setHeight(coneHeight);
	pConeZ->setCenter(osg::Vec3f(xPos, yPos, zPos));

	pConeZ->setRadius(coneRadius);
	pConeZ->setRotation(vQuat);
	return pShapeZ.release();
}
/****************************************************************************************************************************************************************************************/
//绘制探测数据的坐标轴
osg::ref_ptr<osg::Geode> axisBaseDraw::drawBoundLineBox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
{
	//创建保存几何信息的对象
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	//创建四个顶点
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	v->push_back(osg::Vec3(xMin, yMin, zMin));
	v->push_back(osg::Vec3(xMin, yMax, zMin));

	v->push_back(osg::Vec3(xMin, yMin, zMin));
	v->push_back(osg::Vec3(xMin, yMin, zMax));

	v->push_back(osg::Vec3(xMin, yMin, zMin));
	v->push_back(osg::Vec3(xMax, yMin, zMin));

	v->push_back(osg::Vec3(xMin, yMin, zMax));
	v->push_back(osg::Vec3(xMax, yMin, zMax));

	v->push_back(osg::Vec3(xMin, yMin, zMax));
	v->push_back(osg::Vec3(xMin, yMax, zMax));

	v->push_back(osg::Vec3(xMax, yMax, zMax));
	v->push_back(osg::Vec3(xMax, yMin, zMax));

	v->push_back(osg::Vec3(xMax, yMax, zMax));
	v->push_back(osg::Vec3(xMin, yMax, zMax));

	v->push_back(osg::Vec3(xMax, yMax, zMax));
	v->push_back(osg::Vec3(xMax, yMax, zMin));

	v->push_back(osg::Vec3(xMax, yMin, zMax));
	v->push_back(osg::Vec3(xMax, yMin, zMin));

	v->push_back(osg::Vec3(xMax, yMin, zMin));
	v->push_back(osg::Vec3(xMax, yMax, zMin));

	v->push_back(osg::Vec3(xMax, yMax, zMin));
	v->push_back(osg::Vec3(xMin, yMax, zMin));

	v->push_back(osg::Vec3(xMin, yMax, zMin));
	v->push_back(osg::Vec3(xMin, yMax, zMax));

	geom->setVertexArray(v.get());

	//为每个顶点指定一种颜色
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();
	c->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f)); //坐标原点为红色

	geom->setColorArray(c.get());
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);

	//三个轴
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, v->size())); //X

	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	geode->getOrCreateStateSet()->setAttribute(new osg::LineWidth(1.5), osg::StateAttribute::ON);

	geode->addDrawable(geom.get());

	return geode.release();
}


/****************************************************************************************************************************************************************************************/
//绘制探测数据的坐标轴数据标尺
osg::ref_ptr<osg::Geode> axisBaseDraw::drawTextFlag(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
{
	//创建保存几何信息的对象
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	//创建四个顶点
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	unsigned int tapTextCount = 100;
	int tap = 5;//暂定5个刻度为一个距离
	float lineLen = 2;
	float textSize = 2;
	char buf[64];

	//绘制z轴刻度及显示值
	for (unsigned int i = 0; i <= tapTextCount; i++)
	{
		v->push_back(osg::Vec3(xMin, yMin, zMin + i*tap));
		v->push_back(osg::Vec3(xMin, yMin - lineLen, zMin + i*tap));
		itoa(i * tap+zMin, buf, 10);
		osg::ref_ptr<osgText::Text> pTextZAuxis = new osgText::Text;
		pTextZAuxis->setText(buf);
		pTextZAuxis->setColor(osg::Vec4(0, 0, 0, 1.0));
		
		pTextZAuxis->setAxisAlignment(osgText::Text::SCREEN);
		pTextZAuxis->setCharacterSize(textSize);
		pTextZAuxis->setPosition(osg::Vec3(xMin, yMin - lineLen - textSize, zMin + i*tap));
		geode->addDrawable(pTextZAuxis.get());

		//最大绘制刻度的坐标大于当前图像绘制方向的最大值坐标时，结束绘制
		if ((zMin + i*tap) > (zMax))
		{
			break;
		}
	}

	//绘制x轴刻度及显示值
	for (unsigned int i = 0; i <= tapTextCount; i++)
	{
		v->push_back(osg::Vec3(xMin + i*tap, yMin, zMin));
		v->push_back(osg::Vec3(xMin + i*tap, yMin - lineLen, zMin));

		itoa(i * tap+xMin, buf, 10);
		osg::ref_ptr<osgText::Text> pTextXAuxis = new osgText::Text;
		pTextXAuxis->setText(buf);
		pTextXAuxis->setColor(osg::Vec4(0, 0, 0, 1.0));
		
		pTextXAuxis->setAxisAlignment(osgText::Text::SCREEN);
		pTextXAuxis->setCharacterSize(textSize);
		pTextXAuxis->setPosition(osg::Vec3(xMin + i*tap, yMin - lineLen - textSize, zMin));
		geode->addDrawable(pTextXAuxis.get());

		//最大绘制刻度的坐标大于当前图像绘制方向的最大值坐标时，结束绘制
		if ((xMin + i*tap) > (xMax))
		{
			break;
		}
	}

	//绘制y轴刻度及显示值
	for (unsigned int i = 0; i <= tapTextCount; i++)
	{
		v->push_back(osg::Vec3(xMin, yMin + i*tap, zMin));
		v->push_back(osg::Vec3(xMin - lineLen, yMin + i*tap, zMin));
		itoa(i * tap+yMin, buf, 10);
		osg::ref_ptr<osgText::Text> pTextYAuxis = new osgText::Text;
		pTextYAuxis->setText(buf);
		pTextYAuxis->setColor(osg::Vec4(0,0,0,1.0));
		
		pTextYAuxis->setAxisAlignment(osgText::Text::SCREEN);
		pTextYAuxis->setCharacterSize(textSize);
		pTextYAuxis->setPosition(osg::Vec3(xMin - lineLen - textSize, yMin + i*tap, zMin));
		geode->addDrawable(pTextYAuxis.get());

		//最大绘制刻度的坐标大于当前图像绘制方向的最大值坐标时，结束绘制
		if ((yMin + i*tap) > (yMax))
		{
			break;
		}
	}
	geom->setVertexArray(v.get());

	//为每个顶点指定一种颜色
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();
	c->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f)); //坐标原点为红色

	geom->setColorArray(c.get());
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);

	//三个轴
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, v->size())); //X
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	geode->getOrCreateStateSet()->setAttribute(new osg::LineWidth(1.5), osg::StateAttribute::ON);

	geode->addDrawable(geom.get());

	return geode.release();
}

/****************************************************************************************************************************************************************************************/
//绘制探测数据的坐标轴
osg::ref_ptr<osg::Geode> axisBaseDraw::makeCoordinate(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
{
	float tap = 1;
	osg::Quat yQuat;
	yQuat.makeRotate(-osg::PI_2, osg::X_AXIS);
	osg::Quat xQuat;
	xQuat.makeRotate(osg::PI_2, osg::Y_AXIS);
	osg::Quat zQuat;
	zQuat.makeRotate(-osg::PI_2, osg::Z_AXIS);

	osg::ref_ptr<osg::ShapeDrawable> pShapeDrawY = drawAxisCone(xMin, yMax + tap, zMin, yQuat, osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f),0.4,1.0);
	osg::ref_ptr<osg::ShapeDrawable> pShapeDrawX = drawAxisCone(xMax + tap, yMin, zMin, xQuat, osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f),0.4,1.0);
	osg::ref_ptr<osg::ShapeDrawable> pShapeDrawZ = drawAxisCone(xMin, yMin, zMax + tap, zQuat, osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f),0.4,1.0);

	//创建保存几何信息的对象
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	//创建四个顶点
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	v->push_back(osg::Vec3(xMin, yMin, zMin));
	v->push_back(osg::Vec3(xMax + tap, yMin, zMin));
	v->push_back(osg::Vec3(xMin, yMin, zMin));
	v->push_back(osg::Vec3(xMin, yMax + tap, zMin));
	v->push_back(osg::Vec3(xMin, yMin, zMin));
	v->push_back(osg::Vec3(xMin, yMin, zMax + tap));
	geom->setVertexArray(v.get());

	//为每个顶点指定一种颜色
	float colorValue = 0.2;
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();
	c->push_back(osg::Vec4(colorValue, colorValue, colorValue, 1.0f)); //坐标原点为红色
	c->push_back(osg::Vec4(colorValue, colorValue, colorValue, 1.0f)); //x red
	c->push_back(osg::Vec4(colorValue, colorValue, colorValue, 1.0f)); //坐标原点为绿色
	c->push_back(osg::Vec4(colorValue, colorValue, colorValue, 1.0f)); //y green
	c->push_back(osg::Vec4(colorValue, colorValue, colorValue, 1.0f)); //坐标原点为蓝色
	c->push_back(osg::Vec4(colorValue, colorValue, colorValue, 1.0f)); //z blue
	//如果没指定颜色则会变为黑色
	geom->setColorArray(c.get());
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	//三个轴
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2)); //X
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 2, 2)); //Y
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 4, 2)); //Z

	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	geode->getOrCreateStateSet()->setAttribute(new osg::LineWidth(5.0), osg::StateAttribute::ON);

	geode->addDrawable(pShapeDrawY.get());
	geode->addDrawable(pShapeDrawX.get());
	geode->addDrawable(pShapeDrawZ.get());
	
	float textSize = 1.0;
	osg::ref_ptr<osgText::Text> pTextXAuxis = new osgText::Text;
	pTextXAuxis->setText(L"X轴");
	pTextXAuxis->setFont("Fonts/simhei.ttf");
	pTextXAuxis->setAxisAlignment(osgText::Text::SCREEN);
	pTextXAuxis->setCharacterSize(textSize);
	pTextXAuxis->setPosition(osg::Vec3(xMax + tap, yMin, zMin));
	pTextXAuxis->setColor(osg::Vec4(0, 0, 0, 1.0));

	osg::ref_ptr<osgText::Text> pTextYAuxis = new osgText::Text;
	pTextYAuxis->setText(L"Y轴");
	pTextYAuxis->setFont("Fonts/simhei.ttf");
	pTextYAuxis->setAxisAlignment(osgText::Text::SCREEN);
	pTextYAuxis->setCharacterSize(textSize);
	pTextYAuxis->setColor(osg::Vec4(0, 0, 0, 1.0));
	pTextYAuxis->setPosition(osg::Vec3(xMin, yMax + tap, zMin));
	osg::ref_ptr<osgText::Text> pTextZAuxis = new osgText::Text;
	pTextZAuxis->setText(L"Z轴");
	pTextZAuxis->setFont("Fonts/simhei.ttf");
	pTextZAuxis->setAxisAlignment(osgText::Text::SCREEN);
	pTextZAuxis->setCharacterSize(textSize);
	pTextZAuxis->setPosition(osg::Vec3(xMin, yMin, zMax + tap));
	pTextZAuxis->setColor(osg::Vec4(0, 0, 0, 1.0));
	//三个轴
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, v->size())); //X	
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	geode->getOrCreateStateSet()->setAttribute(new osg::LineWidth(1.5), osg::StateAttribute::ON);
	geode->addDrawable(geom.get());
	geode->addDrawable(pTextXAuxis.get());
	geode->addDrawable(pTextYAuxis.get());
	geode->addDrawable(pTextZAuxis.get());

	geode->addDrawable(geom.get());

	return geode.release();
}

/*******************************************************************************************************************************************/
//function : 创建二维相机
void ViewerWidget::createOrthoCamera(unsigned int width, unsigned int height)
{
	if (NULL == m_orthoCamera)
	{
		//创建相机节点
		m_orthoCamera = new osg::Camera;
		////图形输出设置当前视口
		m_orthoCamera->setViewport(0, 0, width, height);
		//直接设置/获取投影矩阵的内容--平行投影
		m_orthoCamera->setProjectionMatrix(osg::Matrix::ortho2D(0, width, 0, height));
		//设置/获取该相机的参考系。使用ABSOLUTE_RF绝对参考系表示该相机将不受父节点任何变换的影响
		m_orthoCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
		//直接设置/获取观察矩阵的内容
		m_orthoCamera->setViewMatrix(osg::Matrix::identity());
		//清除深度缓存
		m_orthoCamera->setClearMask(GL_DEPTH_BUFFER_BIT);
		//设置相机的渲染顺序，在主场景之前（PRE_RENDER）还是之后（POST_RENDER）。
		m_orthoCamera->setRenderOrder(osg::Camera::POST_RENDER);
		m_orthoCamera->setAllowEventFocus(false);
		m_orthoCamera->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);
		m_orthoCamera->setClearColor(osg::Vec4(1.0, 1.0, 1.0, 0.5));
		m_SceneGroup->addChild(m_orthoCamera.get());
		//m_pickHandlerEvent->setOrhtoCamera(m_orthoCamera.get());
	}
	else
	{
		m_orthoCamera->setViewport(0, 0, width, height);
		//直接设置/获取投影矩阵的内容--平行投影
		m_orthoCamera->setProjectionMatrix(osg::Matrix::ortho2D(0, width, 0, height));
	}
}



/*************************************************************************************************************/
//QT实时渲染技术
void ViewerWidget::paintEvent(QPaintEvent* event)
{
	m_pViewer->frame();//实时进行渲染
}

void ViewerWidget::creatHideLabel()
{
	m_hideLabel = new QLabel(this);
	m_hideLabel->setGeometry(QRect(0, 0, 1, 2000));
}