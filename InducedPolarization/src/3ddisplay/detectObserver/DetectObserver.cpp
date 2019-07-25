#include "DetectObserv/DetectObserver.h"
#include "GlobalClass/GlobalParam.h"

DetectObserver::DetectObserver(QWidget* parent /*= nullptr*/) : ViewerWidget3d(parent)
{
	m_pTunnelGroup = NULL;
	m_pMeasureGroup = NULL;
	m_pElectGroup = NULL;

	m_isTunnelGrid = false;
	m_isTunnelEntity = false;

	m_walkTracker = new osgEngine::WalkTrackerManipulator;
	getViewer()->setCameraManipulator(m_walkTracker.get());
}

DetectObserver::~DetectObserver()
{

}

/***************************************************************************************/
//function:
void DetectObserver::initScene()
{
	GlobalParam::ObservationSystemSetting obserSysParam = GlobalParam::instance()->getObservationSystemSetting();
}

/*******************************************************************************************/
//function:���Ƶ缫�㼰������
void DetectObserver::drawMeasurePointLine(std::vector<osg::Vec3d> measurePoint)
{
	if (NULL == m_pMeasureGroup)
	{
		m_pMeasureGroup = new osg::Group;
		getSceneGroup()->addChild(m_pMeasureGroup.get());
	}
	else
		m_pMeasureGroup->removeChildren(0, m_pMeasureGroup->getNumChildren());

	//��ȡ��������������
	osg::Vec3d facePosition = GlobalParam::instance()->getObservationSystemSetting().facePosition;

	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	osg::ref_ptr<osg::Vec3dArray> pPointNormalArray = new osg::Vec3dArray;
	osg::ref_ptr<osg::Vec3dArray> pointArray = new osg::Vec3dArray;
	for (unsigned int i = 0; i < measurePoint.size(); i++)
	{
		//pointArray->push_back(measurePoint[i]);
		pointArray->push_back(osg::Vec3d(measurePoint[i].x() + facePosition.x(), measurePoint[i].y() + facePosition.y(), measurePoint[i].z() + facePosition.z()));
	}

	osg::ref_ptr<osg::Geometry> gm = new osg::Geometry;
	osg::ref_ptr<osg::Vec4dArray> color = new osg::Vec4dArray;
	color->push_back(osg::Vec4d(1.0, 0, 0, 1.0));
	gm->setVertexArray(pointArray); // points may have been modified in order by triangulation.
	gm->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP, 0, pointArray->size())); //���ù�����ʽ
	gm->setColorArray(color.get());
	gm->setColorBinding(osg::Geometry::BIND_OVERALL);
	geode->addDrawable(gm.get());


	//����������
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
	geometry->setVertexArray(pointArray.get());
	geometry->setColorArray(color.get());
	geometry->setColorBinding(osg::Geometry::BIND_OVERALL);

	osg::Vec3dArray *normals = new osg::Vec3dArray;
	normals->push_back(osg::Vec3d(1.0f, 1.0f, 0.0f));
	geometry->setNormalArray(normals);
	geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);
	geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, pointArray->size())); //���ù�����ʽ
																									   //��ӵ�Ҷ�ڵ�
	osg::ref_ptr<osg::Geode> pointGeode = new osg::Geode();
	//set the point size
	osg::ref_ptr <osg::Point> ptSize = new osg::Point;
	ptSize->setSize(5);
	pointGeode->getOrCreateStateSet()->setAttributeAndModes(ptSize.get(), osg::StateAttribute::ON);
	pointGeode->addDrawable(geometry.get());

	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);//�رչ���
	pointGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	//m_pMeasureGroup->addChild(geode.get());		//���ӵ�֮�������ʱ���ε�
	m_pMeasureGroup->addChild(pointGeode.get());
	getSceneGroup()->addChild(m_pMeasureGroup.get());
}


/*******************************************************************************************/
//function:���ƹ����ֲ�
void DetectObserver::drawElectroPoints(std::vector<osg::Vec3d> electroPoint, std::vector<double> disVec)
{
	if (NULL == m_pElectGroup)
	{
		m_pElectGroup = new osg::Group;
		getSceneGroup()->addChild(m_pElectGroup.get());
	}
	else
		m_pElectGroup->removeChildren(0, m_pElectGroup->getNumChildren());

	osg::ref_ptr<osg::Vec3dArray> pointArray = new osg::Vec3dArray;
	std::vector<osg::ref_ptr<osg::Vec3dArray>> pointLineVec;

	for (unsigned int k = 0; k < disVec.size(); k++)
	{
		osg::ref_ptr<osg::Vec3dArray> eachPointLine = new osg::Vec3dArray;

		for (unsigned int i = 0; i < electroPoint.size(); i++)
		{
			osg::Vec3d pointPos(electroPoint[i].x(), electroPoint[i].y(), electroPoint[i].z());
			pointPos.z() -= disVec[k];
			pointArray->push_back(pointPos);
			eachPointLine->push_back(pointPos);
		}
		pointLineVec.push_back(eachPointLine.get());
	}
	
	osg::ref_ptr<osg::Vec4dArray> color = new osg::Vec4dArray;
	color->push_back(osg::Vec4d(0, 0, 1.0, 1.0));

	for (unsigned int i = 0; i < pointLineVec.size(); i ++)
	{
		osg::ref_ptr<osg::Geode> geode = new osg::Geode();
		osg::ref_ptr<osg::Geometry> gm = new osg::Geometry;

		gm->setVertexArray(pointLineVec[i].get()); // points may have been modified in order by triangulation.
		gm->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, 0, pointLineVec[i]->size())); //���ù�����ʽ
		gm->setColorArray(color.get());
		gm->setColorBinding(osg::Geometry::BIND_OVERALL);
		geode->addDrawable(gm.get());

		geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
		m_pElectGroup->addChild(geode.get());
	}
	
	//����������
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
	geometry->setVertexArray(pointArray.get());
	geometry->setColorArray(color.get());
	geometry->setColorBinding(osg::Geometry::BIND_OVERALL);

	osg::Vec3dArray *normals = new osg::Vec3dArray;
	normals->push_back(osg::Vec3d(1.0f, 1.0f, 0.0f));
	geometry->setNormalArray(normals);
	geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);
	//���ù�����ʽ
	geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, pointArray->size()));
  
	osg::ref_ptr<osg::Geode> pointGeode = new osg::Geode();
	//set the point size
	osg::ref_ptr <osg::Point> ptSize = new osg::Point;
	ptSize->setSize(8);
	pointGeode->getOrCreateStateSet()->setAttributeAndModes(ptSize.get(), osg::StateAttribute::ON);
	pointGeode->addDrawable(geometry.get());

	pointGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	
	m_pElectGroup->addChild(pointGeode.get());
	getSceneGroup()->addChild(m_pElectGroup.get());
}

/*****************************************************************************************************/
//function : ������ʼ�����Բ����
osg::ref_ptr<osg::MatrixTransform> DetectObserver::createCylinder(osg::Vec3 &from,osg::Vec3 &to, float radius)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();	
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();	
	osg::ref_ptr<osg::ShapeDrawable> cylinder = new osg::ShapeDrawable();	
	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints(); 	
	hints->setDetailRatio(0.8f);	
	osg::Vec3 cylCenter = (to + from) / 2;		//�õ�����	
	float height = (to - from).length();		//�õ�����	
	cylinder = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(0.0, 0.0, 0.0), radius, height),hints.get());
	cylinder->setColor(osg::Vec4(255.0/255, 228.0/255, 181.0/255, 1.0f));//¹ƤЬɫ	
	geode->addDrawable(cylinder.get());	
	osg::Matrix mRotate, mTrans;
	mRotate.makeRotate(osg::Vec3f(0.0f, 0.0f, 1.0f), to - from);	
	mTrans.makeTranslate(cylCenter);	
	mt->setMatrix(mRotate*mTrans);	
	mt->addChild(geode.get());	
	return mt.get();
}

void DetectObserver::drawElecMesureTextFlag(std::vector<double> vFaceDistanceVec, float xPos, float yPos, float zPos /*= 0.0*/)
{
	//Z�������ÿ��Ȧ��Ӧ��λ��
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	geode->getOrCreateStateSet()->setAttribute(new osg::LineWidth(5.0), osg::StateAttribute::ON);
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	geode->getOrCreateStateSet()->setAttribute(new osg::LineWidth(1.5), osg::StateAttribute::ON);

	float textSize = 1.0;
	for (int i = 0; i < vFaceDistanceVec.size(); i++)
	{
		osg::ref_ptr<osgText::Text> pTextXAuxis = new osgText::Text;
		char buf[64];
		sprintf(buf, "%4.1fm\n", vFaceDistanceVec[i]);
		pTextXAuxis->setText(buf);
		pTextXAuxis->setFont("Fonts/simhei.ttf");
		pTextXAuxis->setAxisAlignment(osgText::Text::SCREEN);
		pTextXAuxis->setCharacterSize(textSize);
		pTextXAuxis->setPosition(osg::Vec3(xPos, yPos, -vFaceDistanceVec[i] + zPos));
		pTextXAuxis->setColor(osg::Vec4(1.0, 0, 0, 1.0));
		geode->addDrawable(pTextXAuxis.get());
	}
	m_pElectGroup->addChild(geode.get());
}

void DetectObserver::setTunnelGrid(bool isTunnelGrid)
{
	m_isTunnelGrid = isTunnelGrid;

	if (m_isTunnelGrid == true)
	{
		osg::Vec3d tunnelCenter = GlobalParam::instance()->getObservationSystemSetting().facePosition;
		if (NULL != m_walkTracker)
		{
			tunnelCenter.y() -= 100;
			m_walkTracker->setEye(tunnelCenter);
			m_walkTracker->setRotation(osg::Vec3f(1.57079632679489661923f, 0, 0));
		}
	}
}

void DetectObserver::setTunnelEntity(bool isTunnelEntity)
{
	m_isTunnelEntity = isTunnelEntity;
	getViewer()->setCameraManipulator(m_walkTracker.get());
	//���ʵ��ĳ���
	if (isTunnelEntity == true)
	{
		osg::Vec3d tunnelCenter = GlobalParam::instance()->getObservationSystemSetting().facePosition;
		if (NULL != m_walkTracker)
		{
			tunnelCenter.z() -= (m_tunnelLen + 40);
			m_walkTracker->setEye(tunnelCenter);
			m_walkTracker->setRotation(osg::Vec3f(3.1415926535898f, 0, 1.57079632679489661923f));
		}

		m_SceneGroup->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);//����Ȳ���
		m_SceneGroup->getOrCreateStateSet()->setMode(GL_LIGHT0, osg::StateAttribute::ON);
		m_SceneGroup->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);//����Ȳ���
		m_SceneGroup->getOrCreateStateSet()->setMode(GL_FRONT_AND_BACK, osg::StateAttribute::ON);//˫�����
		m_SceneGroup->getOrCreateStateSet()->setMode(GL_FLAT, osg::StateAttribute::ON);//ƽ����������
	}
}

void DetectObserver::setTunnelView(bool value)
{
	osg::ref_ptr<osgGA::TrackballManipulator> pCameraMani = new osgGA::TrackballManipulator;
	m_pViewer->setCameraManipulator(pCameraMani.release());
}

/***************************************************************************************/
//function:
void DetectObserver::drawTunnel(float circleLen, unsigned int circleCount)
{
	GlobalParam::ObservationSystemSetting obserSysParam = GlobalParam::instance()->getObservationSystemSetting();
	
	drawTunnel(obserSysParam.facePosition, circleLen, circleCount, obserSysParam.faceHeight/2);
	
	osg::Vec3 pos = osg::Vec3(obserSysParam.facePosition.x(), obserSysParam.facePosition.y(), obserSysParam.facePosition.z()+0.05);
	osg::ref_ptr<osg::Group> pCylinder = createCylinder(pos, osg::Vec3(pos.x(),pos.y(),pos.z()+10), obserSysParam.faceHeight/2);
	getSceneGroup()->addChild(m_pTunnelGroup.get());
	getSceneGroup()->addChild(pCylinder.get());
	getViewer()->setSceneData(getSceneGroup());
}


/************************************************************************************************************/
/****************************************************************************************************************************************************/
//FUNCTION: �������Բ��
void DetectObserver::Init_Circle(float circle1[36][2], float Radius, int &vCircleNum) //�������αƽ���Բ
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

/***************************************************************************************************************/
//FUNCTION: �������
void DetectObserver::drawTunnel(osg::Vec3d& circlePos,
	float eachTunelCircleLen, int tunelSegmentNum, float Radius)
{
	//�����������飬ע�ⶥ������˳������ʱ���
	float circle[36][2] = { 0 };
	int circleNumFace = 0;
	Init_Circle(circle, Radius, circleNumFace);
	if (NULL == m_pTunnelGroup)
	{
		m_pTunnelGroup = new osg::Group;
	}
	else
	{
		m_pTunnelGroup->removeChildren(0, m_pTunnelGroup->getNumChildren());
	}
	
	const int step = eachTunelCircleLen; //�������ÿ�εĳ���

	osg::ref_ptr<osg::Vec3dArray> pPointNormalArray = new osg::Vec3dArray;
	osg::ref_ptr<osg::Vec3dArray> pointArray = new osg::Vec3dArray;
	for (int i = 0; i < circleNumFace; i++)
	{
		pointArray->push_back(osg::Vec3d(circle[i][0] + circlePos.x(), circlePos.y()+ circle[i][1],circlePos.z()));
		osg::Vec3d tmpPoint = osg::Vec3d(circle[i][0], circle[i][1], 0);
		tmpPoint.normalize();
		pPointNormalArray->push_back(tmpPoint);
	}

	osg::ref_ptr<osg::Vec3dArray> pNormalArray = new osg::Vec3dArray;
	int jj = -1, kk = 0, mm = 0;
	float textScale = 1.2;
	unsigned int faceVecOneNorNum = circleNumFace - 1;

	m_tunnelLen = tunelSegmentNum * (float)step;

	for (int tunnelStep = 0; tunnelStep < tunelSegmentNum; tunnelStep++)
	{
		osg::ref_ptr<osg::Geometry> gmFour = new osg::Geometry;
		osg::ref_ptr<osg::Geode> geodeFour = new osg::Geode;
		osg::ref_ptr<osg::Vec4dArray> color = new osg::Vec4dArray;
		color->push_back(osg::Vec4d(1.0,1.0,1.0,1.0));
		osg::ref_ptr<osg::Vec3Array> pointArray = new osg::Vec3Array;

		for (int i = 0; i < circleNumFace - 1; i++)
		{
			pointArray->push_back(osg::Vec3d(circle[i][0] + circlePos.x(), circle[i][1] + circlePos.y(), circlePos.z() - ((tunnelStep)* (step))));
			pNormalArray->push_back((*pPointNormalArray)[i]);
			pointArray->push_back(osg::Vec3d(circle[i][0] + circlePos.x(), circle[i][1] + circlePos.y(), circlePos.z() - ((tunnelStep + 1)* (step))));
			pNormalArray->push_back((*pPointNormalArray)[i]);
			pointArray->push_back(osg::Vec3d(circle[i + 1][0] + circlePos.x(), circle[i + 1][1] + circlePos.y(), circlePos.z() - ((tunnelStep + 1)* (step))));
			pNormalArray->push_back((*pPointNormalArray)[i + 1]);
			pointArray->push_back(osg::Vec3d(circle[i + 1][0] + circlePos.x(), circle[i + 1][1] + circlePos.y(), circlePos.z() - ((tunnelStep)* (step))));
			pNormalArray->push_back((*pPointNormalArray)[i + 1]);
		}
		pointArray->push_back(osg::Vec3(circle[circleNumFace - 1][0] + circlePos.x(), circle[circleNumFace - 1][1] + circlePos.y(), circlePos.z() - ((tunnelStep)* (step))));
		pNormalArray->push_back((*pPointNormalArray)[circleNumFace - 1]);
		pointArray->push_back(osg::Vec3(circle[circleNumFace - 1][0] + circlePos.x(), circle[circleNumFace - 1][1] + circlePos.y(), circlePos.z() - ((tunnelStep + 1) * (step))));
		pNormalArray->push_back((*pPointNormalArray)[circleNumFace - 1]);
		pointArray->push_back(osg::Vec3d(circle[0][0] + circlePos.x(), circle[0][1] + circlePos.y(), circlePos.z() - ((tunnelStep + 1)* (step))));
		pNormalArray->push_back((*pPointNormalArray)[0]);
		pointArray->push_back(osg::Vec3d(circle[0][0] + circlePos.x(), circle[0][1] + circlePos.y(), circlePos.z() - ((tunnelStep)* (step))));
		pNormalArray->push_back((*pPointNormalArray)[0]);

		gmFour->setVertexArray(pointArray); // points may have been modified in order by triangulation.
		gmFour->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, pointArray->size())); //���ù�����ʽ

		gmFour->setNormalArray(pNormalArray.get());
		gmFour->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
		gmFour->setColorArray(color.get());
		gmFour->setColorBinding(osg::Geometry::BIND_OVERALL);

		osg::PolygonMode *pLolyTotalMode = new osg::PolygonMode();
		pLolyTotalMode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
		geodeFour->getOrCreateStateSet()->setAttribute(pLolyTotalMode);
		geodeFour->getOrCreateStateSet()->setAttributeAndModes(pLolyTotalMode, osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON);

		osg::LineWidth * linewidth = new osg::LineWidth;
		linewidth->setWidth(1.5);
		geodeFour->getOrCreateStateSet()->setAttributeAndModes(linewidth, osg::StateAttribute::ON);//�����߿�
		geodeFour->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
		geodeFour->addDrawable(gmFour.get());

		geodeFour->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
		m_pTunnelGroup->addChild(geodeFour.get());
	}
}

