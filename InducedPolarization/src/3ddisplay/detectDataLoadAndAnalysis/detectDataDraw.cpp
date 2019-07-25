#include "detectData/detectDataDraw.h"
#include <osg/Geode>
#include <osg/Geometry>
#include <osgText/Text>
#include <osg/LineWidth>

/*************************************************************************************************************************************************************************************/
//function: draw the axis cone
osg::ref_ptr<osg::ShapeDrawable> detectDataDraw::drawAxisCone(float xPos, float yPos, float zPos, osg::Quat vQuat, osg::Vec4& vColor)
{
	osg::ref_ptr<osg::Cone> pConeZ = new osg::Cone;
	osg::ref_ptr<osg::ShapeDrawable> pShapeZ = new osg::ShapeDrawable(pConeZ);
	pShapeZ->setColor(vColor);
	pConeZ->setHeight(4);
	pConeZ->setCenter(osg::Vec3f(xPos,yPos,zPos));
	
	pConeZ->setRadius(1.2);
	pConeZ->setRotation(vQuat);
	return pShapeZ.release();
}

/****************************************************************************************************************************************************************************************/
//绘制探测数据的坐标轴
osg::Geode* detectDataDraw::drawBoundingBox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
{
	//创建保存几何信息的对象
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	//创建四个顶点
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	
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
	c->push_back(osg::Vec4(0.2f, 0.2f, 0.2f, 1.0f)); //坐标原点为灰色
	
	geom->setColorArray(c.get());
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);

	//三个轴
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, v->size())); //X
	
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	//geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	geode->getOrCreateStateSet()->setAttribute(new osg::LineWidth(3.0), osg::StateAttribute::ON);

	geode->addDrawable(geom.get());

	return geode.release();
}

/****************************************************************************************************************************************************************************************/
//绘制探测数据的坐标轴数据标尺
osg::Geode* detectDataDraw::drawTextFlag(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
{
	//创建保存几何信息的对象
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	//创建四个顶点
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	unsigned int tapTextCount = 10;
	int tap = 10;//暂定10个刻度为一个距离
	float lineLen = 2;
	float textSize = 2;
	char buf[64];

	tapTextCount = (zMax - zMin) / tap + 1;
	//绘制z轴刻度及显示值
	for (unsigned int i = 0; i < tapTextCount; i++)
	{
		v->push_back(osg::Vec3(xMin, yMin, zMin+i*tap));
		v->push_back(osg::Vec3(xMin, yMin - lineLen, zMin + i*tap));
		itoa(i * tap + zMin, buf, 10);
		osg::ref_ptr<osgText::Text> pTextZAuxis = new osgText::Text;
		pTextZAuxis->setColor(osg::Vec4(0.2f, 0.2f, 0.2f, 1.0));
		pTextZAuxis->setText(buf);

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
	tapTextCount = (xMax - xMin) / tap + 1;
	for (unsigned int i = 0; i < tapTextCount; i++)
	{
		v->push_back(osg::Vec3(xMin + i*tap, yMin, zMin));
		v->push_back(osg::Vec3(xMin + i*tap, yMin - lineLen, zMin));

		itoa(i * tap + xMin, buf, 10);
		osg::ref_ptr<osgText::Text> pTextXAuxis = new osgText::Text;
		pTextXAuxis->setColor(osg::Vec4(0.2f, 0.2f, 0.2f, 1.0));
		pTextXAuxis->setText(buf);
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
	tapTextCount = (yMax - yMin) / tap + 1;
	for (unsigned int i = 0; i < tapTextCount; i++)
	{
		v->push_back(osg::Vec3(xMax, yMin + i*tap, zMin ));
		v->push_back(osg::Vec3(xMax + lineLen, yMin + i*tap, zMin));
		itoa(i * tap + yMin, buf, 10);
		osg::ref_ptr<osgText::Text> pTextYAuxis = new osgText::Text;
		pTextYAuxis->setColor(osg::Vec4(0.2f, 0.2f, 0.2f, 1.0));
		pTextYAuxis->setText(buf);
		pTextYAuxis->setAxisAlignment(osgText::Text::SCREEN);
		pTextYAuxis->setCharacterSize(textSize);
		pTextYAuxis->setPosition(osg::Vec3(xMax + lineLen + textSize, yMin + i*tap, zMin));
		geode->addDrawable(pTextYAuxis.get());
		
		//最大绘制刻度的坐标大于当前图像绘制方向的最大值坐标时，结束绘制
		if ((yMin + i*tap) > (yMax))
		{
			break;
		}
	}
	
	//为每个顶点指定一种颜色
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();
	c->push_back(osg::Vec4(0.2f, 0.2f, 0.2f, 1.0f)); //坐标原点为红色
	geom->setVertexArray(v.get());
	geom->setColorArray(c.get());
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);
	
	osg::ref_ptr<osgText::Text> pTextXAuxis = new osgText::Text;
	pTextXAuxis->setText(L"X轴");
	pTextXAuxis->setColor(osg::Vec4(0.2f, 0.2f, 0.2f, 1.0f));
	pTextXAuxis->setFont("Fonts/simhei.ttf");
	pTextXAuxis->setAxisAlignment(osgText::Text::SCREEN);
	pTextXAuxis->setCharacterSize(4);
	pTextXAuxis->setPosition(osg::Vec3(xMax + tap, yMin, zMin));

	osg::ref_ptr<osgText::Text> pTextYAuxis = new osgText::Text;
	pTextYAuxis->setText(L"Y轴");
	pTextYAuxis->setColor(osg::Vec4(0.2f, 0.2f, 0.2f, 1.0f));
	pTextYAuxis->setFont("Fonts/simhei.ttf");
	pTextYAuxis->setAxisAlignment(osgText::Text::SCREEN);
	pTextYAuxis->setCharacterSize(4);

	pTextYAuxis->setPosition(osg::Vec3(xMin, yMax + tap, zMin));
	osg::ref_ptr<osgText::Text> pTextZAuxis = new osgText::Text;
	pTextZAuxis->setText(L"Z轴");
	pTextZAuxis->setFont("Fonts/simhei.ttf");
	pTextZAuxis->setAxisAlignment(osgText::Text::SCREEN);
	pTextZAuxis->setColor(osg::Vec4(0.2f, 0.2f, 0.2f, 1.0f));
	pTextZAuxis->setCharacterSize(4);
	pTextZAuxis->setPosition(osg::Vec3(xMin, yMin, zMax + tap));

	//三个轴
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, v->size())); //X	
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	geode->getOrCreateStateSet()->setAttribute(new osg::LineWidth(1.5), osg::StateAttribute::ON);
	geode->addDrawable(geom.get());
	geode->addDrawable(pTextXAuxis.get());
	geode->addDrawable(pTextYAuxis.get());
	geode->addDrawable(pTextZAuxis.get());
	return geode.release();
}

/****************************************************************************************************************************************************************************************/
//绘制探测数据的坐标轴
osg::Geode* detectDataDraw::makeCoordinate(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
{
    osg::ref_ptr<osg::Sphere> pSphereShape = new osg::Sphere(osg::Vec3(xMin,yMin,zMin), 1.0f);
	
	float tap = 10;
	osg::Quat yQuat;
	yQuat.makeRotate(-osg::PI_2,osg::X_AXIS);
	osg::Quat xQuat;
	xQuat.makeRotate(osg::PI_2,osg::Y_AXIS);
	osg::Quat zQuat;
	zQuat.makeRotate(-osg::PI_2,osg::Z_AXIS);
	
	osg::ref_ptr<osg::ShapeDrawable> pShapeDrawY = drawAxisCone(xMin, yMax+tap, zMin, yQuat, osg::Vec4(0.2f, 0.2f, 0.2f, 1.0f));
	osg::ref_ptr<osg::ShapeDrawable> pShapeDrawX = drawAxisCone(xMax+tap,yMin,zMin,xQuat, osg::Vec4(0.2f, 0.2f, 0.2f, 1.0f));
	osg::ref_ptr<osg::ShapeDrawable> pShapeDrawZ = drawAxisCone(xMin,yMin,zMax + tap,zQuat, osg::Vec4(0.2f, 0.2f, 0.2f, 1.0f));

    osg::ref_ptr<osg::ShapeDrawable> pShapeDrawable = new osg::ShapeDrawable(pSphereShape.get());
    pShapeDrawable->setColor(osg::Vec4(0.0, 0.0, 0.0, 1.0));

    //创建保存几何信息的对象
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
	
    //创建四个顶点
    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
    v->push_back(osg::Vec3(xMin, yMin, zMin));
    v->push_back(osg::Vec3(xMax+tap, yMin, zMin));
    v->push_back(osg::Vec3(xMin, yMin, zMin));
    v->push_back(osg::Vec3(xMin, yMax+tap, zMin));
    v->push_back(osg::Vec3(xMin, yMin, zMin));
    v->push_back(osg::Vec3(xMin, yMin, zMax+tap));
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
    geom->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2)); //X
    geom->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, 2, 2)); //Y
    geom->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, 4, 2)); //Z

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    geode->getOrCreateStateSet()->setAttribute(new osg::LineWidth(3),  osg::StateAttribute::ON);
	
	geode->addDrawable(pShapeDrawY.get());
	geode->addDrawable(pShapeDrawX.get());
	geode->addDrawable(pShapeDrawZ.get());
	
    geode->addDrawable(pShapeDrawable.get());
    geode->addDrawable(geom.get());
    return geode.release();
}