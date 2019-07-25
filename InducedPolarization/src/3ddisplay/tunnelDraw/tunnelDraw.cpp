#include <3ddisplay/tunnelDraw/tunnelDraw.h>
#include <string>
#include <windows.h>
#include <math.h>
#include <ctime>
#include <osgText/Text>
#include <osg/ShapeDrawable>
#include <3ddisplay/tool/sceneTool.h>
#include "Timer.h"

using namespace std;

namespace osgEngine
{
	/****************************************************************************************************************************************************/
	//FUNCTION: 绘制隧道圆形
	void CTunnelDraw::Init_Circle(float circle1[36][2], float Radius, int &vCircleNum) //用三角形逼近画圆
	{
		float angle = 0;
		vCircleNum = 36;
		for (int i = 0; i < vCircleNum; i++)
		{
			circle1[i][0] = Radius*cos(angle);
			circle1[i][1] = Radius*sin(angle);
			angle += 2.0*3.1415926 / (float)vCircleNum;
		}
	}

	/****************************************************************************************************************************************************/
	//FUNCTION: 创建隧道环形体
	osg::ref_ptr<osg::Node> CTunnelDraw::createCircleTunnel()
	{
		double ration = 0.4;
		int circleNumFace = m_onlinePointArray->size();
		m_circleNode->removeDrawables(0, m_circleNode->getNumDrawables());
		
		//将内环形和外环形连成体
		int j = -1, k = 0, m = 0;
		osg::ref_ptr<osg::Geometry> gmFour = new osg::Geometry;
		osg::ref_ptr<osg::Vec4dArray> color = new osg::Vec4dArray;
		osg::ref_ptr<osg::Vec3Array> pointCircleArray = new osg::Vec3Array;
		for (int i = 0; i < 2 * circleNumFace - 2; i++)
		{
			if (i % 2 == 0)
			{
				j += 1;
				m += 1;
				pointCircleArray->push_back((*m_inlinePointArray)[j]);
				pointCircleArray->push_back((*m_onlinePointArray)[k]);
				pointCircleArray->push_back((*m_onlinePointArray)[m]);
			}
			else
			{
				k += 1;
				pointCircleArray->push_back((*m_inlinePointArray)[j]);
				pointCircleArray->push_back((*m_onlinePointArray)[m]);
				pointCircleArray->push_back((*m_inlinePointArray)[k]);
			}
		}

		int inlinePointSize = m_inlinePointArray->size();
		int onlinePointSize = m_onlinePointArray->size();

		pointCircleArray->push_back((*m_inlinePointArray)[inlinePointSize - 1]);
		pointCircleArray->push_back((*m_onlinePointArray)[0]);
		pointCircleArray->push_back((*m_onlinePointArray)[onlinePointSize - 1]);

		pointCircleArray->push_back((*m_inlinePointArray)[0]);
		pointCircleArray->push_back((*m_onlinePointArray)[0]);
		pointCircleArray->push_back((*m_inlinePointArray)[inlinePointSize - 1]);

		gmFour->setVertexArray(pointCircleArray.get()); // points may have been modified in order by triangulation.
		gmFour->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, pointCircleArray->size())); //设置关联方式

		m_circleNode->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
		m_circleNode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
		m_circleNode->addDrawable(gmFour.get());
		return m_circleNode.get();
	}

	/***************************************************************************************************************************************/
	//function:创建隧道文字标记信息
	osg::ref_ptr<osg::Geode> CTunnelDraw::createTunnelTextFlag(osg::Vec3d tunnelCenter, float tunnelRadius, float vTextPos, float textSize)
	{
		osg::ref_ptr<osg::Geode> geode = new osg::Geode;
		float tap = 1.5;

		osg::ref_ptr<osgText::Text> text = new osgText::Text;
		text->setCharacterSize(textSize);
		text->setAxisAlignment(osgText::Text::YZ_PLANE);

		char buf[64];
		text->setColor(osg::Vec4f(0.2, 0.2, 0.2, 1.0));

		unsigned int kmValue = (unsigned int)(m_beginMile) / 1000;
		float mValue = m_beginMile - kmValue * 1000;
		mValue += vTextPos;
		sprintf(buf, "%3dk+%3.2fm\0", kmValue, mValue);

		unsigned int strLen = strlen(buf);
		osg::Vec3 textPos = osg::Vec3(tunnelCenter.x(), tunnelCenter.y() + vTextPos - strLen / 2, tunnelCenter.z() + tunnelRadius + tap);

		text->setPosition(textPos);
		text->setText(buf);
		geode->addDrawable(text.get());
		geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);

		return geode.release();
	}

	/****************************************************************************************************************************************************/
	//FUNCTION: 绘制隧道
	osg::ref_ptr<osg::Group> CTunnelDraw::createCirlineBySRPoint(osg::Vec3d& circlePos, float eachTunelCircleLen, int tunelSegmentNum, float Radius, bool isInsideTunnel)
	{
		//创建顶点数组，注意顶点的添加顺序是逆时针的
		float circle[36][2];
		int circleNumFace = 0;
		Init_Circle(circle, Radius, circleNumFace);

		const int step = eachTunelCircleLen; //定义隧道每段的长度
		osg::ref_ptr<osg::Vec3dArray> pPointNormalArray = new osg::Vec3dArray;
		if (!isInsideTunnel)
		{
			for (int i = 0; i < circleNumFace; i++)
			{
				osg::Vec3d tmpPoint = osg::Vec3d(circle[i][0], 0, circle[i][1]);
				tmpPoint.normalize();
				pPointNormalArray->push_back(tmpPoint);
			}
		}

		m_tunnelSRGroup->removeChildren(0, m_tunnelSRGroup->getNumChildren());
		
		osg::ref_ptr<osg::Vec3dArray> pNormalArray = new osg::Vec3dArray;
		int jj = -1, kk = 0, mm = 0;
		unsigned int faceVecOneNorNum = circleNumFace - 1;

		BEGIN_TIMER;
		for (int tunnelStep = 0; tunnelStep < tunelSegmentNum; tunnelStep++)
		{
			osg::ref_ptr<osg::Geometry> gmFour = new osg::Geometry;
			osg::ref_ptr<osg::Geode> geodeFour = new osg::Geode;
			osg::ref_ptr<osg::Vec4dArray> color = new osg::Vec4dArray;
			osg::ref_ptr<osg::Vec3Array> pointArray = new osg::Vec3Array;
			float ranColor = 0.8;
			color->push_back(osg::Vec4d(ranColor, ranColor, ranColor, 1.0));
			for (int i = 0; i < circleNumFace - 1; i++)
			{
				pointArray->push_back(osg::Vec3d(circle[i][0] + circlePos.x(), circlePos.y() - ((tunnelStep)* (step)), circle[i][1] + circlePos.z()));
				pNormalArray->push_back((*pPointNormalArray)[i]);
				pointArray->push_back(osg::Vec3d(circle[i][0] + circlePos.x(), circlePos.y() - ((tunnelStep + 1)* (step)), circle[i][1] + circlePos.z()));
				pNormalArray->push_back((*pPointNormalArray)[i]);
				pointArray->push_back(osg::Vec3d(circle[i + 1][0] + circlePos.x(), circlePos.y() - ((tunnelStep + 1)* (step)), circle[i + 1][1] + circlePos.z()));
				pNormalArray->push_back((*pPointNormalArray)[i + 1]);
				pointArray->push_back(osg::Vec3d(circle[i + 1][0] + circlePos.x(), circlePos.y() - ((tunnelStep)* (step)), circle[i + 1][1] + circlePos.z()));
				pNormalArray->push_back((*pPointNormalArray)[i + 1]);
			}
			pointArray->push_back(osg::Vec3(circle[circleNumFace - 1][0] + circlePos.x(), circlePos.y() - ((tunnelStep)* (step)), circle[circleNumFace - 1][1] + circlePos.z()));
			pNormalArray->push_back((*pPointNormalArray)[circleNumFace - 1]);
			pointArray->push_back(osg::Vec3(circle[circleNumFace - 1][0] + circlePos.x(), circlePos.y() - ((tunnelStep + 1) * (step)), circle[circleNumFace - 1][1] + circlePos.z()));
			pNormalArray->push_back((*pPointNormalArray)[circleNumFace - 1]);
			pointArray->push_back(osg::Vec3d(circle[0][0] + circlePos.x(), circlePos.y() - ((tunnelStep + 1)* (step)), circle[0][1] + circlePos.z()));
			pNormalArray->push_back((*pPointNormalArray)[0]);
			pointArray->push_back(osg::Vec3d(circle[0][0] + circlePos.x(), circlePos.y() - ((tunnelStep)* (step)), circle[0][1] + circlePos.z()));
			pNormalArray->push_back((*pPointNormalArray)[0]);

			gmFour->setVertexArray(pointArray.get()); // points may have been modified in order by triangulation.
			gmFour->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, pointArray->size())); //设置关联方式
			gmFour->setNormalArray(pNormalArray.get());
			gmFour->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
			gmFour->setColorArray(color.get());
			gmFour->setColorBinding(osg::Geometry::BIND_OVERALL);

			osg::PolygonMode *pLolyTotalMode = new osg::PolygonMode();
			pLolyTotalMode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
			geodeFour->getOrCreateStateSet()->setAttribute(pLolyTotalMode);
			geodeFour->getOrCreateStateSet()->setAttributeAndModes(pLolyTotalMode, osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON);

			osg::LineWidth * linewidth = new osg::LineWidth;
			linewidth->setWidth(1.2);
			geodeFour->getOrCreateStateSet()->setAttributeAndModes(linewidth, osg::StateAttribute::ON);//设置线宽
			geodeFour->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
			geodeFour->addDrawable(gmFour.get());
			geodeFour->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
			//osgEngine::DrawFunc::drawForDiaphaneity(geodeFour, 0.5);

			m_TunnelGroupOnline->addChild(geodeFour.get());
			m_tunnelSRGroup->addChild(geodeFour.get());
		}
		END_TIMER;
		TIMER_LOG("For tunelSegmentNum");

		//隧道探测已挖部分
		std::string detectName = "Detect Area";
		float tapHeight = 1;
		float textZPos = circlePos.z() + Radius + 0.5;
		float textYPos = circlePos.y();
		osg::Vec4 textColor = osg::Vec4(0.4, 0.4, 0.4, 1);
		float textSize = 3;
		osg::ref_ptr<osgText::Text> pTextDiged = new osgText::Text;
		pTextDiged->setText(detectName);
		pTextDiged->setAxisAlignment(osgText::Text::YZ_PLANE);
		pTextDiged->setPosition(osg::Vec3(0, textYPos - tunelSegmentNum * 0.85 * eachTunelCircleLen, textZPos + tapHeight * 4));
		pTextDiged->setCharacterSize(textSize);
		pTextDiged->setColor(textColor);
		osg::ref_ptr<osg::Geode> pTextGeode = new osg::Geode;
		pTextGeode->addDrawable(pTextDiged.get());

		std::string predictName = "Tunnel Forcast Area";
		osg::ref_ptr<osgText::Text> pTextZeroAuxis = new osgText::Text;
		pTextZeroAuxis->setText(predictName.c_str());
		pTextZeroAuxis->setAxisAlignment(osgText::Text::YZ_PLANE);
		pTextZeroAuxis->setPosition(osg::Vec3(0, textYPos + tunelSegmentNum * eachTunelCircleLen, textZPos + tapHeight * 4));
		pTextZeroAuxis->setCharacterSize(textSize);
		pTextZeroAuxis->setColor(textColor);
		pTextGeode->addDrawable(pTextZeroAuxis.get());

		m_TunnelGroupOnline->addChild(pTextGeode.get());
		return m_tunnelSRGroup.get();
	}

	/***************************************************************************************************************************************************/
	//function:绘制预测区文字及标尺
	osg::ref_ptr<osg::Geode> CTunnelDraw::drawTextFlagLine(osg::Vec3d& vTunnelCenter, unsigned int segNum, float segLen, float vTunnelRadius)
	{
		float deviation = 20;
		float interTextNum = 10;
		float tapHeight = 1;
		//创建保存几何信息的对象
		osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

		float textZPos = vTunnelCenter.z() + vTunnelRadius + 0.5;
		float textYPos = vTunnelCenter.y();
		//创建四个顶点
		osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
		v->push_back(osg::Vec3(vTunnelCenter.x(), vTunnelCenter.y(), textZPos));
		v->push_back(osg::Vec3(vTunnelCenter.x(), vTunnelCenter.y() + segLen*segNum, textZPos));

		//取得x轴方向每个竖线之间的间隔距离<注:设定10个间隔>
		for (int i = 0; i <= segNum; i++)
		{
			v->push_back(osg::Vec3(vTunnelCenter.x(), textYPos + i*segLen, textZPos));
			v->push_back(osg::Vec3(vTunnelCenter.x(), textYPos + i*segLen, textZPos + tapHeight));
		}

		geom->setVertexArray(v.get());
		geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, v->size()));

		//设置坐标颜色
		osg::ref_ptr<osg::Vec3Array> pColor = new osg::Vec3Array;
		pColor->push_back(osg::Vec3d(0.2, 0.2, 0.2));
		geom->setColorArray(pColor.get());
		geom->setColorBinding(osg::Geometry::BIND_OVERALL);

		osg::ref_ptr<osg::Geode> geode = new osg::Geode();
		geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
		geode->getOrCreateStateSet()->setAttribute(new osg::LineWidth(2.0), osg::StateAttribute::ON);

		
		geode->addDrawable(geom.get());
		return geode.release();
	}

	/****************************************************************************************************************************************************/
	//FUNCTION: 绘制隧道
	osg::ref_ptr<osg::Group> CTunnelDraw::createCirlineByQuards(osg::Vec3d& circlePos, float eachTunelCircleLen, int tunelSegmentNum, float Radius, bool isInsideTunnel)
	{
		//创建顶点数组，注意顶点的添加顺序是逆时针的
		float circle[36][2];
		int circleNumFace = 0;
		Init_Circle(circle, Radius, circleNumFace);

		const int step = eachTunelCircleLen; //定义隧道每段的长度

		osg::ref_ptr<osg::Vec3dArray> pPointNormalArray = new osg::Vec3dArray;
		if (isInsideTunnel)
		{
			m_inlinePointArray->clear();
			m_TunnelGroupInline->removeChildren(0, m_TunnelGroupInline->getNumChildren());
			for (int i = 0; i < circleNumFace; i++)
			{
				m_inlinePointArray->push_back(osg::Vec3d(circle[i][0] + circlePos.x(), circlePos.y(), circle[i][1] + circlePos.z()));
				osg::Vec3d tmpPoint = osg::Vec3d(circle[i][0], 0, circle[i][1]);
				tmpPoint.normalize();
				pPointNormalArray->push_back(tmpPoint);
			}
		}
		if (!isInsideTunnel)
		{
			m_onlinePointArray->clear();
			m_TunnelGroupOnline->removeChildren(0, m_TunnelGroupOnline->getNumChildren());
			m_TunnelTextGroup->removeChildren(0, m_TunnelTextGroup->getNumChildren());
			for (int i = 0; i < circleNumFace; i++)
			{
				m_onlinePointArray->push_back(osg::Vec3d(circle[i][0] + circlePos.x(), circlePos.y(), circle[i][1] + circlePos.z()));
				osg::Vec3d tmpPoint = osg::Vec3d(circle[i][0], 0, circle[i][1]);
				tmpPoint.normalize();
				pPointNormalArray->push_back(tmpPoint);
			}
		}

		osg::ref_ptr<osg::Vec3dArray> pNormalArray = new osg::Vec3dArray;
		int jj = -1, kk = 0, mm = 0;
		float textScale = 1.2;
		unsigned int faceVecOneNorNum = circleNumFace - 1;
		srand((unsigned)time(0));

		osg::ref_ptr<osg::Vec3Array> pointLineTextArray = new osg::Vec3Array;

		osg::ref_ptr<osg::Geode> tunnelTextLine = drawTextFlagLine(circlePos, tunelSegmentNum, eachTunelCircleLen, Radius);
		for (int tunnelStep = 0; tunnelStep < tunelSegmentNum; tunnelStep++)
		{
			osg::ref_ptr<osg::Geometry> gmFour = new osg::Geometry;

			osg::ref_ptr<osg::Geode> geodeFour = new osg::Geode;
			osg::ref_ptr<osg::Vec4dArray> color = new osg::Vec4dArray;
			osg::ref_ptr<osg::Vec3Array> pointArray = new osg::Vec3Array;

			for (int i = 0; i < circleNumFace - 1; i++)
			{
				pointArray->push_back(osg::Vec3d(circle[i][0] + circlePos.x(), circlePos.y() + ((tunnelStep)* (step)), circle[i][1] + circlePos.z()));
				float ranColor1 = (rand() % 30) / 100;
				ranColor1 += 0.6;
				color->push_back(osg::Vec4d(ranColor1, ranColor1, ranColor1, 1.0));
				pNormalArray->push_back((*pPointNormalArray)[i]);
				pointArray->push_back(osg::Vec3d(circle[i][0] + circlePos.x(), circlePos.y() + ((tunnelStep + 1)* (step)), circle[i][1] + circlePos.z()));
				float ranColor2 = (rand() % 30) / 100;
				ranColor2 += 0.6;
				color->push_back(osg::Vec4d(ranColor2, ranColor2, ranColor2, 1.0));
				pNormalArray->push_back((*pPointNormalArray)[i]);
				pointArray->push_back(osg::Vec3d(circle[i + 1][0] + circlePos.x(), circlePos.y() + ((tunnelStep + 1)* (step)), circle[i + 1][1] + circlePos.z()));
				float ranColor3 = (rand() % 30) / 100;
				ranColor3 += 0.6;
				color->push_back(osg::Vec4d(ranColor3, ranColor3, ranColor3, 1.0));
				pNormalArray->push_back((*pPointNormalArray)[i + 1]);
				pointArray->push_back(osg::Vec3d(circle[i + 1][0] + circlePos.x(), circlePos.y() + ((tunnelStep)* (step)), circle[i + 1][1] + circlePos.z()));
				float ranColor4 = (rand() % 30) / 100;
				ranColor4 += 0.6;
				color->push_back(osg::Vec4d(ranColor4, ranColor4, ranColor4, 1.0));
				pNormalArray->push_back((*pPointNormalArray)[i + 1]);
			}
			pointArray->push_back(osg::Vec3(circle[circleNumFace - 1][0] + circlePos.x(), circlePos.y() + ((tunnelStep)* (step)), circle[circleNumFace - 1][1] + circlePos.z()));
			float ranColor = (rand() % 30) / 100;
			ranColor += 0.6;
			color->push_back(osg::Vec4d(ranColor, ranColor, ranColor, 1.0));
			pNormalArray->push_back((*pPointNormalArray)[circleNumFace - 1]);
			pointArray->push_back(osg::Vec3(circle[circleNumFace - 1][0] + circlePos.x(), circlePos.y() + ((tunnelStep + 1) * (step)), circle[circleNumFace - 1][1] + circlePos.z()));
			color->push_back(osg::Vec4d(ranColor, ranColor, ranColor, 1.0));
			pNormalArray->push_back((*pPointNormalArray)[circleNumFace - 1]);
			pointArray->push_back(osg::Vec3d(circle[0][0] + circlePos.x(), circlePos.y() + ((tunnelStep + 1)* (step)), circle[0][1] + circlePos.z()));
			color->push_back(osg::Vec4d(ranColor, ranColor, ranColor, 1.0));
			pNormalArray->push_back((*pPointNormalArray)[0]);
			pointArray->push_back(osg::Vec3d(circle[0][0] + circlePos.x(), circlePos.y() + ((tunnelStep)* (step)), circle[0][1] + circlePos.z()));
			color->push_back(osg::Vec4d(ranColor, ranColor, ranColor, 1.0));
			pNormalArray->push_back((*pPointNormalArray)[0]);

			gmFour->setVertexArray(pointArray); // points may have been modified in order by triangulation.
			gmFour->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, pointArray->size())); //设置关联方式

			gmFour->setNormalArray(pNormalArray.get());
			gmFour->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
			gmFour->setColorArray(color.get());
			gmFour->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

			osg::PolygonMode *pLolyTotalMode = new osg::PolygonMode();
			pLolyTotalMode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
			geodeFour->getOrCreateStateSet()->setAttribute(pLolyTotalMode);
			geodeFour->getOrCreateStateSet()->setAttributeAndModes(pLolyTotalMode, osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON);

			osg::LineWidth * linewidth = new osg::LineWidth;
			linewidth->setWidth(1.5);
			geodeFour->getOrCreateStateSet()->setAttributeAndModes(linewidth, osg::StateAttribute::ON);//设置线宽
			geodeFour->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
			geodeFour->addDrawable(gmFour.get());

			geodeFour->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
			if (isInsideTunnel)
			{
				m_TunnelGroupInline->addChild(geodeFour.get());
			}
			else
			{
				osg::ref_ptr<osg::Geode> pTextFlag = createTunnelTextFlag(circlePos, Radius, tunnelStep*step, textScale);
				m_TunnelTextGroup->addChild(pTextFlag.get());
				m_TunnelGroupOnline->addChild(geodeFour.get());
			}
		}

		if (isInsideTunnel)
		   return m_TunnelGroupInline.get();
		else
		{
			osg::ref_ptr<osg::Geode> pTextFlag = createTunnelTextFlag(circlePos, Radius, tunelSegmentNum*step, textScale);
			m_TunnelTextGroup->addChild(pTextFlag.get());
			m_TunnelTextGroup->addChild(tunnelTextLine.get());
			return m_TunnelGroupOnline.get();
		}
	}

	/****************************************************************************************************************************************************/
	//FUNCTION: 绘制马蹄形隧道
	osg::MatrixTransform* CTunnelDraw::createHorseShoeTunnel(osg::Vec3d circlePos, float eachCircleTunnelLen, float tunnelSegNum, float Radius)
	{
		m_tunnelDia = Radius * 2;//隧道直径
		m_tunnelCenterPos = circlePos;
		drawHorseShoeTunnelLine(circlePos, eachCircleTunnelLen, tunnelSegNum, Radius, false);
		drawHorseShoeTunnelLine(circlePos, eachCircleTunnelLen, tunnelSegNum, (Radius - Radius*0.1), true);

		//创建隧道最开始处的环形体
		createCircleTunnel();

		this->setName("tunnel");
		this->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);

		return this;
	}

	/****************************************************************************************************************************************************/
	//FUNCTION: 绘制隧道
	osg::ref_ptr<osg::Group> CTunnelDraw::createHorseShoeCirlineBySRPoint(osg::Vec3d& circlePos, float eachTunelCircleLen, int tunelSegmentNum, float Radius, bool isInsideTunnel)
	{
		//创建顶点数组，注意顶点的添加顺序是逆时针的
		float circle[25][2];
		unsigned int circleNumFace = 25;
		float angle = 0;

		for (int i = 0; i < circleNumFace - 2; i++)
		{
			circle[i][0] = Radius*cos(angle);
			circle[i][1] = Radius*sin(angle);
			angle += 3.1415926 / (float)(circleNumFace - 3);
		}

		circle[circleNumFace - 2][0] = circle[circleNumFace - 3][0];
		circle[circleNumFace - 2][1] = circle[circleNumFace - 3][1] - Radius;

		circle[circleNumFace - 1][0] = circle[circleNumFace - 2][0] + 2 * Radius;
		circle[circleNumFace - 1][1] = circle[circleNumFace - 2][1];

		const int step = eachTunelCircleLen; //定义隧道每段的长度
		osg::ref_ptr<osg::Vec3dArray> pPointNormalArray = new osg::Vec3dArray;
		if (!isInsideTunnel)
		{
			for (int i = 0; i < circleNumFace; i++)
			{
				osg::Vec3d tmpPoint = osg::Vec3d(circle[i][0], 0, circle[i][1]);
				tmpPoint.normalize();
				pPointNormalArray->push_back(tmpPoint);
			}
		}

		m_tunnelSRGroup->removeChildren(0, m_tunnelSRGroup->getNumChildren());

		osg::ref_ptr<osg::Vec3dArray> pNormalArray = new osg::Vec3dArray;
		int jj = -1, kk = 0, mm = 0;
		unsigned int faceVecOneNorNum = circleNumFace - 1;
		for (int tunnelStep = 0; tunnelStep < tunelSegmentNum; tunnelStep++)
		{
			osg::ref_ptr<osg::Geometry> gmFour = new osg::Geometry;
			osg::ref_ptr<osg::Geode> geodeFour = new osg::Geode;
			osg::ref_ptr<osg::Vec4dArray> color = new osg::Vec4dArray;
			osg::ref_ptr<osg::Vec3Array> pointArray = new osg::Vec3Array;
			float ranColor = 0.8;
			color->push_back(osg::Vec4d(ranColor, ranColor, ranColor, 1.0));
			for (int i = 0; i < circleNumFace - 1; i++)
			{
				pointArray->push_back(osg::Vec3d(circle[i][0] + circlePos.x(), circlePos.y() - ((tunnelStep)* (step)), circle[i][1] + circlePos.z()));
				pNormalArray->push_back((*pPointNormalArray)[i]);
				pointArray->push_back(osg::Vec3d(circle[i][0] + circlePos.x(), circlePos.y() - ((tunnelStep + 1)* (step)), circle[i][1] + circlePos.z()));
				pNormalArray->push_back((*pPointNormalArray)[i]);
				pointArray->push_back(osg::Vec3d(circle[i + 1][0] + circlePos.x(), circlePos.y() - ((tunnelStep + 1)* (step)), circle[i + 1][1] + circlePos.z()));
				pNormalArray->push_back((*pPointNormalArray)[i + 1]);
				pointArray->push_back(osg::Vec3d(circle[i + 1][0] + circlePos.x(), circlePos.y() - ((tunnelStep)* (step)), circle[i + 1][1] + circlePos.z()));
				pNormalArray->push_back((*pPointNormalArray)[i + 1]);
			}
			pointArray->push_back(osg::Vec3(circle[circleNumFace - 1][0] + circlePos.x(), circlePos.y() - ((tunnelStep)* (step)), circle[circleNumFace - 1][1] + circlePos.z()));
			pNormalArray->push_back((*pPointNormalArray)[circleNumFace - 1]);
			pointArray->push_back(osg::Vec3(circle[circleNumFace - 1][0] + circlePos.x(), circlePos.y() - ((tunnelStep + 1) * (step)), circle[circleNumFace - 1][1] + circlePos.z()));
			pNormalArray->push_back((*pPointNormalArray)[circleNumFace - 1]);
			pointArray->push_back(osg::Vec3d(circle[0][0] + circlePos.x(), circlePos.y() - ((tunnelStep + 1)* (step)), circle[0][1] + circlePos.z()));
			pNormalArray->push_back((*pPointNormalArray)[0]);
			pointArray->push_back(osg::Vec3d(circle[0][0] + circlePos.x(), circlePos.y() - ((tunnelStep)* (step)), circle[0][1] + circlePos.z()));
			pNormalArray->push_back((*pPointNormalArray)[0]);

			gmFour->setVertexArray(pointArray.get()); // points may have been modified in order by triangulation.
			gmFour->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, pointArray->size())); //设置关联方式
			gmFour->setNormalArray(pNormalArray.get());
			gmFour->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
			gmFour->setColorArray(color.get());
			gmFour->setColorBinding(osg::Geometry::BIND_OVERALL);

			osg::PolygonMode *pLolyTotalMode = new osg::PolygonMode();
			pLolyTotalMode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
			geodeFour->getOrCreateStateSet()->setAttribute(pLolyTotalMode);
			geodeFour->getOrCreateStateSet()->setAttributeAndModes(pLolyTotalMode, osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON);

			osg::LineWidth * linewidth = new osg::LineWidth;
			linewidth->setWidth(1.2);
			geodeFour->getOrCreateStateSet()->setAttributeAndModes(linewidth, osg::StateAttribute::ON);//设置线宽
			geodeFour->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
			geodeFour->addDrawable(gmFour.get());
			geodeFour->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
			//osgEngine::DrawFunc::drawForDiaphaneity(geodeFour, 0.5);

			m_TunnelGroupOnline->addChild(geodeFour.get());
			m_tunnelSRGroup->addChild(geodeFour.get());
		}

		//隧道探测已挖部分
		std::string detectName = "Detect Area";
		float tapHeight = 1;
		float textZPos = circlePos.z() + Radius + 0.5;
		float textYPos = circlePos.y();
		osg::Vec4 textColor = osg::Vec4(0.4, 0.4, 0.4, 1);
		float textSize = 3;
		osg::ref_ptr<osgText::Text> pTextDiged = new osgText::Text;
		pTextDiged->setText(detectName);
		pTextDiged->setAxisAlignment(osgText::Text::YZ_PLANE);
		pTextDiged->setPosition(osg::Vec3(0, textYPos - tunelSegmentNum * 0.85 * eachTunelCircleLen, textZPos + tapHeight * 4));
		pTextDiged->setCharacterSize(textSize);
		pTextDiged->setColor(textColor);
		osg::ref_ptr<osg::Geode> pTextGeode = new osg::Geode;
		pTextGeode->addDrawable(pTextDiged.get());

		std::string predictName = "Tunnel Forcast Area";
		osg::ref_ptr<osgText::Text> pTextZeroAuxis = new osgText::Text;
		pTextZeroAuxis->setText(predictName.c_str());
		pTextZeroAuxis->setAxisAlignment(osgText::Text::YZ_PLANE);
		pTextZeroAuxis->setPosition(osg::Vec3(0, textYPos + tunelSegmentNum * eachTunelCircleLen, textZPos + tapHeight * 4));
		pTextZeroAuxis->setCharacterSize(textSize);
		pTextZeroAuxis->setColor(textColor);
		pTextGeode->addDrawable(pTextZeroAuxis.get());

		m_TunnelGroupOnline->addChild(pTextGeode.get());
		return m_tunnelSRGroup.get();
	}

	/*********************************************************************************************/
	//FUNCTION: 绘制马蹄形隧道
	osg::ref_ptr<osg::Group> CTunnelDraw::drawHorseShoeTunnelLine(osg::Vec3d circlePos, float eachTunelCircleLen, float tunnelSegNum, float Radius, bool isInsideTunnel)
	{
		float circle[25][2];
		unsigned int circleNumFace = 25;
		float angle = 0;

		for (int i = 0; i < circleNumFace-2; i++)
		{
			circle[i][0] = Radius*cos(angle);
			circle[i][1] = Radius*sin(angle);
			angle += 3.1415926 / (float)(circleNumFace - 3);
		}

		circle[circleNumFace-2][0] = circle[circleNumFace-3][0];
		circle[circleNumFace-2][1] = circle[circleNumFace-3][1]- Radius;

		circle[circleNumFace - 1][0] = circle[circleNumFace - 2][0] + 2 * Radius;
		circle[circleNumFace - 1][1] = circle[circleNumFace - 2][1];
		
		const int step = eachTunelCircleLen; //定义隧道每段的长度

		osg::ref_ptr<osg::Vec3dArray> pPointNormalArray = new osg::Vec3dArray;
		if (isInsideTunnel)
		{
			m_inlinePointArray->clear();
			m_TunnelGroupInline->removeChildren(0, m_TunnelGroupInline->getNumChildren());
			for (int i = 0; i < circleNumFace; i++)
			{
				m_inlinePointArray->push_back(osg::Vec3d(circle[i][0] + circlePos.x(), circlePos.y(), circle[i][1] + circlePos.z()));
				osg::Vec3d tmpPoint = osg::Vec3d(circle[i][0], 0, circle[i][1]);
				tmpPoint.normalize();
				pPointNormalArray->push_back(tmpPoint);
			}
		}
		if (!isInsideTunnel)
		{
			m_onlinePointArray->clear();
			m_TunnelGroupOnline->removeChildren(0, m_TunnelGroupOnline->getNumChildren());
			m_TunnelTextGroup->removeChildren(0, m_TunnelTextGroup->getNumChildren());
			for (int i = 0; i < circleNumFace; i++)
			{
				m_onlinePointArray->push_back(osg::Vec3d(circle[i][0] + circlePos.x(), circlePos.y(), circle[i][1] + circlePos.z()));
				osg::Vec3d tmpPoint = osg::Vec3d(circle[i][0], 0, circle[i][1]);
				tmpPoint.normalize();
				pPointNormalArray->push_back(tmpPoint);
			}
		}

		osg::ref_ptr<osg::Vec3dArray> pNormalArray = new osg::Vec3dArray;
		int jj = -1, kk = 0, mm = 0;
		float textScale = 1.2;
		unsigned int faceVecOneNorNum = circleNumFace - 1;
		srand((unsigned)time(0));

		osg::ref_ptr<osg::Vec3Array> pointLineTextArray = new osg::Vec3Array;

		osg::ref_ptr<osg::Geode> tunnelTextLine = drawTextFlagLine(circlePos, tunnelSegNum, eachTunelCircleLen, Radius);
		for (int tunnelStep = 0; tunnelStep < tunnelSegNum; tunnelStep++)
		{
			osg::ref_ptr<osg::Geometry> gmFour = new osg::Geometry;

			osg::ref_ptr<osg::Geode> geodeFour = new osg::Geode;
			osg::ref_ptr<osg::Vec4dArray> color = new osg::Vec4dArray;
			osg::ref_ptr<osg::Vec3Array> pointArray = new osg::Vec3Array;
			float ranColor = 0.8;
			for (int i = 0; i < circleNumFace - 1; i++)
			{
				pointArray->push_back(osg::Vec3d(circle[i][0] + circlePos.x(), circlePos.y() + ((tunnelStep)* (step)), circle[i][1] + circlePos.z()));
				
				color->push_back(osg::Vec4d(ranColor, ranColor, ranColor, 1.0));
				pNormalArray->push_back((*pPointNormalArray)[i]);
				pointArray->push_back(osg::Vec3d(circle[i][0] + circlePos.x(), circlePos.y() + ((tunnelStep + 1)* (step)), circle[i][1] + circlePos.z()));
				color->push_back(osg::Vec4d(ranColor, ranColor, ranColor, 1.0));
				pNormalArray->push_back((*pPointNormalArray)[i]);
				pointArray->push_back(osg::Vec3d(circle[i + 1][0] + circlePos.x(), circlePos.y() + ((tunnelStep + 1)* (step)), circle[i + 1][1] + circlePos.z()));
				color->push_back(osg::Vec4d(ranColor, ranColor, ranColor, 1.0));
				pNormalArray->push_back((*pPointNormalArray)[i + 1]);
				pointArray->push_back(osg::Vec3d(circle[i + 1][0] + circlePos.x(), circlePos.y() + ((tunnelStep)* (step)), circle[i + 1][1] + circlePos.z()));
				color->push_back(osg::Vec4d(ranColor, ranColor, ranColor, 1.0));
				pNormalArray->push_back((*pPointNormalArray)[i + 1]);
			}
			pointArray->push_back(osg::Vec3(circle[circleNumFace - 1][0] + circlePos.x(), circlePos.y() + ((tunnelStep)* (step)), circle[circleNumFace - 1][1] + circlePos.z()));
			
			color->push_back(osg::Vec4d(ranColor, ranColor, ranColor, 1.0));
			pNormalArray->push_back((*pPointNormalArray)[circleNumFace - 1]);
			pointArray->push_back(osg::Vec3(circle[circleNumFace - 1][0] + circlePos.x(), circlePos.y() + ((tunnelStep + 1) * (step)), circle[circleNumFace - 1][1] + circlePos.z()));
			color->push_back(osg::Vec4d(ranColor, ranColor, ranColor, 1.0));
			pNormalArray->push_back((*pPointNormalArray)[circleNumFace - 1]);
			pointArray->push_back(osg::Vec3d(circle[0][0] + circlePos.x(), circlePos.y() + ((tunnelStep + 1)* (step)), circle[0][1] + circlePos.z()));
			color->push_back(osg::Vec4d(ranColor, ranColor, ranColor, 1.0));
			pNormalArray->push_back((*pPointNormalArray)[0]);
			pointArray->push_back(osg::Vec3d(circle[0][0] + circlePos.x(), circlePos.y() + ((tunnelStep)* (step)), circle[0][1] + circlePos.z()));
			color->push_back(osg::Vec4d(ranColor, ranColor, ranColor, 1.0));
			pNormalArray->push_back((*pPointNormalArray)[0]);

			gmFour->setVertexArray(pointArray); // points may have been modified in order by triangulation.
			gmFour->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, pointArray->size())); //设置关联方式

			gmFour->setNormalArray(pNormalArray.get());
			gmFour->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
			gmFour->setColorArray(color.get());
			gmFour->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

			osg::PolygonMode *pLolyTotalMode = new osg::PolygonMode();
			pLolyTotalMode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
			geodeFour->getOrCreateStateSet()->setAttribute(pLolyTotalMode);
			geodeFour->getOrCreateStateSet()->setAttributeAndModes(pLolyTotalMode, osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON);

			osg::LineWidth * linewidth = new osg::LineWidth;
			linewidth->setWidth(1.2);
			geodeFour->getOrCreateStateSet()->setAttributeAndModes(linewidth, osg::StateAttribute::ON);//设置线宽
			geodeFour->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
			geodeFour->addDrawable(gmFour.get());

			geodeFour->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
			if (isInsideTunnel)
			{
				m_TunnelGroupInline->addChild(geodeFour.get());
			}
			else
			{
				osg::ref_ptr<osg::Geode> pTextFlag = createTunnelTextFlag(circlePos, Radius, tunnelStep*step, textScale);
				m_TunnelTextGroup->addChild(pTextFlag.get());
				m_TunnelGroupOnline->addChild(geodeFour.get());
			}
		}

		if (isInsideTunnel)
			return m_TunnelGroupInline.get();
		else
		{
			osg::ref_ptr<osg::Geode> pTextFlag = createTunnelTextFlag(circlePos, Radius, tunnelSegNum*step, textScale);
			m_TunnelTextGroup->addChild(pTextFlag.get());
			m_TunnelTextGroup->addChild(tunnelTextLine.get());
			return m_TunnelGroupOnline.get();
		}
    }
	
	/****************************************************************************************************************************************************/
	//FUNCTION: 绘制隧道
	osg::MatrixTransform* CTunnelDraw::drawQuardsTunnel(osg::Vec3d circlePos, float eachCircleTunnelLen, float tunnelSegNum, float Radius)
	{
		m_tunnelDia = Radius * 2;//隧道直径
		m_tunnelCenterPos = circlePos;
		createCirlineByQuards(circlePos, eachCircleTunnelLen, tunnelSegNum, Radius, false);
		createCirlineByQuards(circlePos, eachCircleTunnelLen, tunnelSegNum, (Radius - Radius*0.1), true);

		//创建隧道最开始处的环形体
		createCircleTunnel();

		this->setName("tunnel");
		this->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);

		return this;
	}

	/****************************************************************************************************************************************************/
	//FUNCTION: 获取隧道的分段，每部分隧道由两段组成，index不能大于1
	osg::Node* CTunnelDraw::tunnelDisplayFill(bool isInlineTunnel)
	{
		if (NULL == m_pShadingLight)
			m_pShadingLight = new osgEngine::CShadingLight();
		osg::ref_ptr<osg::Light> pLight = new osg::Light;
		//设置环境光
		pLight->setAmbient(osg::Vec4(0.95f, 0.95f, 0.95f, 1.0f));
		//设置散射光的颜色
		pLight->setDiffuse(osg::Vec4(0.95f, 0.95f, 0.95f, 1.0f));
		pLight->setSpecular(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));

		osg::ref_ptr<osg::LightSource> lightSource = new osg::LightSource;
		lightSource->setLight(pLight.get());
		if (!isInlineTunnel)
		{
			for (int i = 0; i < m_TunnelGroupOnline->getNumChildren(); i++)
			{
				osg::Node* pNodeInline = m_TunnelGroupOnline->getChild(i);
				DrawFunc::drawNodeForFill(pNodeInline);
			}

			m_TunnelGroupOnline->addChild(lightSource.get());

			m_pShadingLight->createLocalShaderLight(0, m_TunnelGroupOnline);

			m_TunnelGroupOnline->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);//打开深度测试
			m_TunnelGroupOnline->getOrCreateStateSet()->setMode(GL_LIGHT0, osg::StateAttribute::ON);
			m_TunnelGroupOnline->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);//打开深度测试
			m_TunnelGroupOnline->getOrCreateStateSet()->setMode(GL_FRONT_AND_BACK, osg::StateAttribute::ON);//双面绘制
		}
		else
		{
			for (int i = 0; i < m_TunnelGroupInline->getNumChildren(); i++)
			{
				osg::Node* pNode = m_TunnelGroupInline->getChild(i);
				DrawFunc::drawNodeForFill(pNode);
			}

			m_TunnelGroupInline->addChild(lightSource.get());

			m_pShadingLight->createLocalShaderLight(0, m_TunnelGroupInline);

			m_TunnelGroupInline->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);//打开深度测试
			m_TunnelGroupInline->getOrCreateStateSet()->setMode(GL_LIGHT0, osg::StateAttribute::ON);
			m_TunnelGroupInline->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);//打开深度测试
			m_TunnelGroupInline->getOrCreateStateSet()->setMode(GL_FRONT_AND_BACK, osg::StateAttribute::ON);//双面绘制
		}
		return NULL;
	}

	/****************************************************************************************************************************************************/
	//FUNCTION: 隧道网格后退显示
	osg::Node* CTunnelDraw::tunnelDisplayLine(bool isInlineTunnel)
	{
		if (isInlineTunnel)
		{
			for (int i = 0; i < m_TunnelGroupInline->getNumChildren(); i++)
			{
				osg::Node* pNodeInline = m_TunnelGroupInline->getChild(i);
				DrawFunc::drawNodeForLine(pNodeInline);
			}
		}
		else
		{
			for (int i = 0; i < m_TunnelGroupOnline->getNumChildren(); i++)
			{
				osg::Node* pNode = m_TunnelGroupOnline->getChild(i);
				DrawFunc::drawNodeForLine(pNode);
			}
		}
		return NULL;
	}

	/****************************************************************************************************************************************************/
	//FUNCTION: 改变隧道的透明度
	void  CTunnelDraw::changetunnelDiaphaneity(float vDiaphanerityRatio)//改变隧道的透明度
	{
		for (int i = 0; i < m_TunnelGroupInline->getNumChildren(); i++)
		{
			osg::Node* pNode = m_TunnelGroupInline->getChild(i);
			osg::PolygonMode *pLolyTotalMode = static_cast<osg::PolygonMode *>(pNode->getOrCreateStateSet()->getAttribute(osg::StateAttribute::POLYGONMODE, 0));
			if (pLolyTotalMode->getMode(osg::PolygonMode::FRONT_AND_BACK) == osg::PolygonMode::FILL)
			{
				osgEngine::DrawFunc::drawForDiaphaneity(pNode, vDiaphanerityRatio);
			}
		}
		for (int i = 0; i < m_TunnelGroupOnline->getNumChildren(); i++)
		{
			osg::Node* pNode = m_TunnelGroupOnline->getChild(i);
			osg::PolygonMode *pLolyTotalMode = static_cast<osg::PolygonMode *>(pNode->getOrCreateStateSet()->getAttribute(osg::StateAttribute::POLYGONMODE, 0));
			if (NULL != pLolyTotalMode && pLolyTotalMode->getMode(osg::PolygonMode::FRONT_AND_BACK) == osg::PolygonMode::FILL)
			{
				osgEngine::DrawFunc::drawForDiaphaneity(pNode, vDiaphanerityRatio);
			}
		}
	}
}