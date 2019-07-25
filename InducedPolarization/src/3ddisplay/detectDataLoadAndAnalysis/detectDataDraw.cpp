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
//����̽�����ݵ�������
osg::Geode* detectDataDraw::drawBoundingBox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
{
	//�������漸����Ϣ�Ķ���
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	//�����ĸ�����
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

	//Ϊÿ������ָ��һ����ɫ
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();
	c->push_back(osg::Vec4(0.2f, 0.2f, 0.2f, 1.0f)); //����ԭ��Ϊ��ɫ
	
	geom->setColorArray(c.get());
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);

	//������
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, v->size())); //X
	
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	//geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	geode->getOrCreateStateSet()->setAttribute(new osg::LineWidth(3.0), osg::StateAttribute::ON);

	geode->addDrawable(geom.get());

	return geode.release();
}

/****************************************************************************************************************************************************************************************/
//����̽�����ݵ����������ݱ��
osg::Geode* detectDataDraw::drawTextFlag(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
{
	//�������漸����Ϣ�Ķ���
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	//�����ĸ�����
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	unsigned int tapTextCount = 10;
	int tap = 10;//�ݶ�10���̶�Ϊһ������
	float lineLen = 2;
	float textSize = 2;
	char buf[64];

	tapTextCount = (zMax - zMin) / tap + 1;
	//����z��̶ȼ���ʾֵ
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

		//�����ƿ̶ȵ�������ڵ�ǰͼ����Ʒ�������ֵ����ʱ����������
		if ((zMin + i*tap) > (zMax))
		{
			break; 
		}
	}

	//����x��̶ȼ���ʾֵ
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
		
		//�����ƿ̶ȵ�������ڵ�ǰͼ����Ʒ�������ֵ����ʱ����������
		if ((xMin + i*tap) > (xMax))
		{
			break;
		}
	}

	//����y��̶ȼ���ʾֵ
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
		
		//�����ƿ̶ȵ�������ڵ�ǰͼ����Ʒ�������ֵ����ʱ����������
		if ((yMin + i*tap) > (yMax))
		{
			break;
		}
	}
	
	//Ϊÿ������ָ��һ����ɫ
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();
	c->push_back(osg::Vec4(0.2f, 0.2f, 0.2f, 1.0f)); //����ԭ��Ϊ��ɫ
	geom->setVertexArray(v.get());
	geom->setColorArray(c.get());
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);
	
	osg::ref_ptr<osgText::Text> pTextXAuxis = new osgText::Text;
	pTextXAuxis->setText(L"X��");
	pTextXAuxis->setColor(osg::Vec4(0.2f, 0.2f, 0.2f, 1.0f));
	pTextXAuxis->setFont("Fonts/simhei.ttf");
	pTextXAuxis->setAxisAlignment(osgText::Text::SCREEN);
	pTextXAuxis->setCharacterSize(4);
	pTextXAuxis->setPosition(osg::Vec3(xMax + tap, yMin, zMin));

	osg::ref_ptr<osgText::Text> pTextYAuxis = new osgText::Text;
	pTextYAuxis->setText(L"Y��");
	pTextYAuxis->setColor(osg::Vec4(0.2f, 0.2f, 0.2f, 1.0f));
	pTextYAuxis->setFont("Fonts/simhei.ttf");
	pTextYAuxis->setAxisAlignment(osgText::Text::SCREEN);
	pTextYAuxis->setCharacterSize(4);

	pTextYAuxis->setPosition(osg::Vec3(xMin, yMax + tap, zMin));
	osg::ref_ptr<osgText::Text> pTextZAuxis = new osgText::Text;
	pTextZAuxis->setText(L"Z��");
	pTextZAuxis->setFont("Fonts/simhei.ttf");
	pTextZAuxis->setAxisAlignment(osgText::Text::SCREEN);
	pTextZAuxis->setColor(osg::Vec4(0.2f, 0.2f, 0.2f, 1.0f));
	pTextZAuxis->setCharacterSize(4);
	pTextZAuxis->setPosition(osg::Vec3(xMin, yMin, zMax + tap));

	//������
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
//����̽�����ݵ�������
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

    //�������漸����Ϣ�Ķ���
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
	
    //�����ĸ�����
    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
    v->push_back(osg::Vec3(xMin, yMin, zMin));
    v->push_back(osg::Vec3(xMax+tap, yMin, zMin));
    v->push_back(osg::Vec3(xMin, yMin, zMin));
    v->push_back(osg::Vec3(xMin, yMax+tap, zMin));
    v->push_back(osg::Vec3(xMin, yMin, zMin));
    v->push_back(osg::Vec3(xMin, yMin, zMax+tap));
    geom->setVertexArray(v.get());
  
    //Ϊÿ������ָ��һ����ɫ
	float colorValue = 0.2;
    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();
    c->push_back(osg::Vec4(colorValue, colorValue, colorValue, 1.0f)); //����ԭ��Ϊ��ɫ
    c->push_back(osg::Vec4(colorValue, colorValue, colorValue, 1.0f)); //x red
    c->push_back(osg::Vec4(colorValue, colorValue, colorValue, 1.0f)); //����ԭ��Ϊ��ɫ
    c->push_back(osg::Vec4(colorValue, colorValue, colorValue, 1.0f)); //y green
    c->push_back(osg::Vec4(colorValue, colorValue, colorValue, 1.0f)); //����ԭ��Ϊ��ɫ
    c->push_back(osg::Vec4(colorValue, colorValue, colorValue, 1.0f)); //z blue
    //���ûָ����ɫ����Ϊ��ɫ
    geom->setColorArray(c.get());
    geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX); 
 
    //������
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