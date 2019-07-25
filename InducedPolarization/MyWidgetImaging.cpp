#include "MyWidgetImaging.h"
#include <QtCore/QTextCodec>

#include "GlobalClass/DataManager.h"
#include "osgGA/TrackballManipulator"

MyWidgetImaging::MyWidgetImaging(QWidget* parent) : ViewerWidget3d(parent)
{
	this->initialization();

	m_pBaseDraw = new BaseDraw;
	m_minSpeed = 100000000.0;
	m_maxSpeed = -10000000.0;
	m_displayRangeValue = 0;
	m_compareRangeValue = -1;
	m_pPointsDataArray = NULL;

	m_waterPointsGroup = NULL;
	m_sliceBodyGroup = NULL;
	m_orthoCamera = NULL;
	m_geode = NULL;
	m_detectPointsGroup = new osg::Group;
	m_SliceGroup = new osg::Group;
	m_surfaceUpGroup = new osg::Group;
	m_surfaceDownGroup = new osg::Group;
	m_lineFlagGroup = new osg::Group;
	m_textGeodeGroup = NULL;
	m_equivalentPointValueDown = 0.0;
	m_equivalentPointValueUp = 0.0;
	
	m_repo = 1.0;
	m_detectImageDisplay = NULL;
	m_CMarchingCube = NULL;
	m_isSliceBodyGroup = false;
	m_boundBoxLineX = false;
	m_boundBoxLineY = false;
	m_boundBoxLineZ = false;
}

MyWidgetImaging::~MyWidgetImaging() 
{
	if (NULL != m_detectImageDisplay)
	{
		delete m_detectImageDisplay;
		m_detectImageDisplay = NULL;
	}
}

/********************************************************************/
//������ʼ��
/********************************************************************/
void MyWidgetImaging::initialization()
{
	//���еĳ�Ա�����ĳ�ʼ��
	m_sliceDrection_x = false;
	m_sliceDrection_y = false;
	m_sliceDrection_z = false;
	m_compareRangeValue = -1;

	m_xMin = 0;
	m_yMin = 0; 
	m_zMin = 0;
	m_xMax = 0;
	m_yMax = 0;
	m_zMax = 0;

	//����osg��group����node��ʼ�������

}

/****************************************************************************************************************/
//function : ��ʼ������,��������ϵ
void MyWidgetImaging::initScene()
{
	getSceneGroup()->removeChildren(0, getSceneGroup()->getNumChildren());
	if (NULL == m_pPointsDataArray || m_pPointsDataArray->size() == 0)
	{
		QMessageBox::warning(this, QStringLiteral("���ݼ��"), QStringLiteral("���ݲ�����"));
		return;
	}
	
    makeCoordinate(m_xMin, m_xMax, m_yMin, m_yMax, m_zMin, m_zMax, 5, false);
	drawBoundLineBox(m_xMin, m_xMax, m_yMin, m_yMax, m_zMin, m_zMax);
	//drawTextFlag(m_xMin, m_xMax, m_yMin, m_yMax, m_zMin, m_zMax);
	drawXAxis(m_xMin, m_xMax, m_yMin, m_yMax, m_zMin, m_zMax, 4);
	drawYAxis(m_xMin, m_xMax, m_yMin, m_yMax, m_zMin, m_zMax, 4);
	drawZAxis(m_xMin, m_xMax, m_yMin, m_yMax, m_zMin, m_zMax, 4);

	getSceneGroup()->addChild(m_detectPointsGroup.get());
	getSceneGroup()->addChild(m_SliceGroup.get());
	getSceneGroup()->addChild(m_surfaceUpGroup.get());
	getSceneGroup()->addChild(m_surfaceDownGroup.get());
	getSceneGroup()->addChild(m_lineFlagGroup.get());

	m_detectPointsGroup->removeChildren(0, m_detectPointsGroup->getNumChildren());
	m_SliceGroup->removeChildren(0, m_SliceGroup->getNumChildren());
	m_surfaceUpGroup->removeChildren(0, m_surfaceUpGroup->getNumChildren());
	m_surfaceDownGroup->removeChildren(0, m_surfaceDownGroup->getNumChildren());
	m_lineFlagGroup->removeChildren(0, m_lineFlagGroup->getNumChildren());

	if (NULL != m_orthoCamera)
	{
		m_orthoCamera->removeChildren(0, m_orthoCamera->getNumChildren());
		getSceneGroup()->addChild(m_orthoCamera.get());
	}

	if (NULL != m_sliceBodyGroup)
	{
		m_sliceBodyGroup->removeChildren(0, m_sliceBodyGroup->getNumChildren());
		getSceneGroup()->addChild(m_sliceBodyGroup.get());
	}

	float boundRadius = getSceneGroup()->getBound().radius();
	osg::Vec3d boundCenter = getSceneGroup()->getBound().center();

	osg::Vec3d eyeCenterboundCenter = boundCenter;
	eyeCenterboundCenter.x() += 2 * boundRadius;
	eyeCenterboundCenter.z() += 2 * boundRadius;
	eyeCenterboundCenter.y() += 2 * boundRadius;

	osg::Vec3d lookCenter = boundCenter;
	osg::ref_ptr<osgGA::TrackballManipulator> pTrackMani = new osgGA::TrackballManipulator;
	pTrackMani->setHomePosition(eyeCenterboundCenter, lookCenter, osg::Vec3d(0, 0, 1), false);
	getViewer()->setCameraManipulator(pTrackMani.get());
}

/***********************************************************************************************************/
//function:չʾ�����������ʼ����
void MyWidgetImaging::initSliceBody()
{
	if (NULL != m_detectPointsGroup)
	    m_detectPointsGroup->setNodeMask(0);

	if (NULL == m_sliceBodyGroup)
	{
		m_sliceBodyGroup = new osg::Group;
		getSceneGroup()->addChild(m_sliceBodyGroup.get());
		m_sliceBodyGroup->setNodeMask(1);
	}
	else
	{
		m_sliceBodyGroup->setNodeMask(1);
		m_sliceBodyGroup->removeChildren(0, m_sliceBodyGroup->getNumChildren());
	}

	if (NULL == m_pPointsDataArray || m_pPointsDataArray->size() == 0)
		return;

	if (m_detectImageDisplay == NULL)
	{
		m_detectImageDisplay = new osgEngine::CImageCreate();
	}

	////////x��
	osg::ref_ptr<osg::Geode> m_pNodeXMin = m_detectImageDisplay->createBodyImage(osgEngine::CImageCreate::xdirect, m_xMin, this);
	osg::StateSet* geodStatesetXMin = m_pNodeXMin->getOrCreateStateSet();
	geodStatesetXMin->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
	m_sliceBodyGroup->addChild(m_pNodeXMin.get());

	osg::ref_ptr<osg::Geode> m_pNodeXMax = m_detectImageDisplay->createBodyImage(osgEngine::CImageCreate::xdirect, m_xMax, this);
	osg::StateSet* geodStatesetXMax = m_pNodeXMax->getOrCreateStateSet();
	geodStatesetXMax->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
	m_sliceBodyGroup->addChild(m_pNodeXMax.get());

	////////y��
	osg::ref_ptr<osg::Geode> m_pNodeYMin = m_detectImageDisplay->createBodyImage(osgEngine::CImageCreate::ydirect, m_yMin, this);
	osg::StateSet* geodStatesetYMin = m_pNodeYMin->getOrCreateStateSet();
	geodStatesetYMin->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
	m_sliceBodyGroup->addChild(m_pNodeYMin.get());

	osg::ref_ptr<osg::Geode> m_pNodeYMax = m_detectImageDisplay->createBodyImage(osgEngine::CImageCreate::ydirect, m_yMax, this);
	osg::StateSet* geodStatesetYMax = m_pNodeYMax->getOrCreateStateSet();
	geodStatesetYMax->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
	m_sliceBodyGroup->addChild(m_pNodeYMax.get());

	////////z��
	osg::ref_ptr<osg::Geode> m_pNodeZMin = m_detectImageDisplay->createBodyImage(osgEngine::CImageCreate::zdirect, m_zMin, this);
	osg::StateSet* geodStatesetZMin = m_pNodeZMin->getOrCreateStateSet();
	geodStatesetZMin->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
	m_sliceBodyGroup->addChild(m_pNodeZMin.get());

	osg::ref_ptr<osg::Geode> m_pNodeZMax = m_detectImageDisplay->createBodyImage(osgEngine::CImageCreate::zdirect, m_zMax, this);
	osg::StateSet* geodStatesetZMax = m_pNodeZMax->getOrCreateStateSet();
	geodStatesetZMax->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
	m_sliceBodyGroup->addChild(m_pNodeZMax.get());
	m_isSliceBodyGroup = true;
}

void MyWidgetImaging::clearData()
{
	//���еĳ�Ա�����ĳ�ʼ��
	m_sliceDrection_x = false;
	m_sliceDrection_y = false;
	m_sliceDrection_z = false;
	m_compareRangeValue = -1;

	m_xMin = 0;
	m_yMin = 0;
	m_zMin = 0;
	m_xMax = 0;
	m_yMax = 0;
	m_zMax = 0;

	if (NULL != m_detectImageDisplay)
	{
		delete m_detectImageDisplay;
		m_detectImageDisplay = NULL;
	}		

	if (m_pPointsDataArray)
	{
		m_pPointsDataArray->clear();
	}

	//if (m_detectPointsGroup)
	//{
	//	m_detectPointsGroup->removeChildren(0, m_detectPointsGroup->getNumChildren());
	//}

	getSceneGroup()->removeChildren(0, getSceneGroup()->getNumChildren());
	m_detectPointsGroup->removeChildren(0, m_detectPointsGroup->getNumChildren());
	m_SliceGroup->removeChildren(0, m_SliceGroup->getNumChildren());
	m_surfaceUpGroup->removeChildren(0, m_surfaceUpGroup->getNumChildren());
	m_surfaceDownGroup->removeChildren(0, m_surfaceDownGroup->getNumChildren());
	m_lineFlagGroup->removeChildren(0, m_lineFlagGroup->getNumChildren());
	if (NULL != m_orthoCamera)
	{
		m_orthoCamera->removeChildren(0, m_orthoCamera->getNumChildren());
	}
	if (NULL != m_sliceBodyGroup)
	{
		m_sliceBodyGroup->removeChildren(0, m_sliceBodyGroup->getNumChildren());
	}
}

extern double*** NRO; //ÿ����Ԫ�ĵ�����ֵ

void MyWidgetImaging::initPointsToScene(double ***vPoints, unsigned int vZLen, unsigned int vYLen, unsigned int vXLen)
{
	osg::ref_ptr<osg::Vec4dArray> vPointsArray = new osg::Vec4dArray;
	for (size_t z = 1; z < vZLen; z++)
	{
		for (size_t y = 1; y < vYLen; y++)
		{
			for (size_t x = 1; x < vXLen; x++)
			{
				//double result = vPoints[x][y][z];
				double result = vPoints[z][y][x];
				vPointsArray->push_back(osg::Vec4d(x,y,z, result));
			}
		}
	}

	initPointsToScene(vPointsArray, vZLen-1, vYLen-1, vXLen-1);
}

void MyWidgetImaging::initNROPointsToScene(double ***vPoints, int vZBegLen, int vYBegLen, 
	int vXBegLen, int vZEndLen, int vYEndLen, int vXEndLen)
{
	osg::ref_ptr<osg::Vec4dArray> vPointsArray = new osg::Vec4dArray;
	for (size_t z = vZBegLen; z <= vZEndLen; z++)
	{
		for (size_t y = vYBegLen; y <= vYEndLen; y++)
		{
			for (size_t x = vXBegLen; x <= vXEndLen; x++)
			{
				double result = vPoints[z][y][x];
				vPointsArray->push_back(osg::Vec4d(x, y, z, result));
			}
		}
	}

	initPointsToScene(vPointsArray, vZEndLen - vZBegLen + 1, vYEndLen - vYBegLen + 1, vXEndLen - vXBegLen + 1);
}

/********************************************************************/
//��ʼ����
/********************************************************************/
void MyWidgetImaging::initPointsToScene(osg::ref_ptr<osg::Vec4dArray> vPointsArray, unsigned int vZLen, unsigned int vYLen, unsigned int vXLen)
{	
	m_xMin = 1000000;
	m_yMin = 1000000;
	m_zMin = 1000000;

	m_xMax = -100000;
	m_yMax = -100000;
	m_zMax = -100000;

	m_minSpeed = 100000000.0;
	m_maxSpeed = -10000000.0;

	if (NULL != m_pPointsDataArray)
		m_pPointsDataArray->clear();
	else
		m_pPointsDataArray = new osg::Vec4dArray;

	for (unsigned int i = 0; i < vPointsArray->size(); i++)
	{
		double waveSpeed = (*vPointsArray)[i].w();
		double xTmpValue = (*vPointsArray)[i].x();
		double yTmpValue = (*vPointsArray)[i].y();
		double zTmpValue = (*vPointsArray)[i].z();

		if (m_minSpeed > waveSpeed)
		{
			m_minSpeed = waveSpeed;
		}

		if (m_maxSpeed < waveSpeed)
		{
			m_maxSpeed = waveSpeed;
		}

		if (m_xMin > xTmpValue)
		{
			m_xMin = xTmpValue;
		}
		if (m_xMax < xTmpValue)
		{
			m_xMax = xTmpValue;
		}

		if (m_yMin > yTmpValue)
		{
			m_yMin = yTmpValue;
		}
		if (m_yMax < yTmpValue)
		{
			m_yMax = yTmpValue;
		}

		if (m_zMin > zTmpValue)
		{
			m_zMin = zTmpValue;
		}
		if (m_zMax < zTmpValue)
		{
			m_zMax = zTmpValue;
		}

		m_xPointValue.insert(xTmpValue); //x����ķֲ�ֵ
		m_yPointValue.insert(yTmpValue); //y����ķֲ�ֵ
		m_zPointValue.insert(zTmpValue); //z����ķֲ�ֵ

		m_pPointsDataArray->push_back(osg::Vec4d((*vPointsArray)[i].x(), (*vPointsArray)[i].y(), (*vPointsArray)[i].z(), waveSpeed));
	}
	emit changeRange(m_minSpeed, m_maxSpeed);
	
	m_sizeX = m_xMax - m_xMin + 1;
	m_sizeY = m_yMax - m_yMin + 1;
	m_sizeZ = m_zMax - m_zMin + 1;

	initScene();
}

/**********************************************************************************************/
//function:չʾ���ж������Ϣ
void MyWidgetImaging::displayAllPoints()
{
	if (NULL != m_sliceBodyGroup)
	    m_sliceBodyGroup->setNodeMask(0);
	m_detectPointsGroup->setNodeMask(1);
	m_detectPointsGroup->removeChildren(0, m_detectPointsGroup->getNumChildren());
	osg::ref_ptr<osg::Geode> pGeode = m_pBaseDraw->drawPoints(m_pPointsDataArray.get(),2,m_minSpeed, m_maxSpeed);
	m_detectPointsGroup->addChild(pGeode.get());
	m_isSliceBodyGroup = false;
}

/********************************************************************/
//�����������
/********************************************************************/
void MyWidgetImaging::saveData()
{
	if (NULL == m_pPointsDataArray || m_pPointsDataArray->size() == 0)
	{
		QMessageBox::warning(this, QStringLiteral("��������"), QStringLiteral("���ݲ�����"));
		return;
	}

	//ϵͳ����Ի���
	QString file_name = QFileDialog::getSaveFileName(this,
		QStringLiteral("��������"), "", QStringLiteral("��������(*.txt)"));

	if (file_name != "")
	{
		ofstream outFile;
		QTextCodec *code = QTextCodec::codecForName("GB2312");//�������·������
		std::string filePath = code->fromUnicode(file_name).data();
		outFile.open(filePath.c_str(), ios::out);

		for (unsigned int i = 0; i < m_pPointsDataArray->size(); i ++)
		{
			outFile << (*m_pPointsDataArray)[i].x() << ',' << (*m_pPointsDataArray)[i].y() << ',' << (*m_pPointsDataArray)[i].z() << ',' << (*m_pPointsDataArray)[i].w() << endl;
		}
		outFile.close();
		QMessageBox::information(this, QStringLiteral("��������"), QStringLiteral("����ɹ�"));
	}
}

/********************************************************************/
//�л���ǩ
/********************************************************************/
void MyWidgetImaging::changeTabIndex(int index)
{
	m_currentTabIndex = index;
	m_compareRangeValue = -1;

	if (index == DATA_VOLUME_VISUALIZATION)
	{	
		if (m_isSliceBodyGroup)
		{
			if (NULL != m_sliceBodyGroup)
			{
				m_sliceBodyGroup->setNodeMask(1);
			}		
			m_detectPointsGroup->setNodeMask(0);	//����ͼ����ʾ
		}
		else
		{
			//if (NULL != m_sliceBodyGroup)
			//{
			//	m_sliceBodyGroup->setNodeMask(1);
			//}
			m_detectPointsGroup->setNodeMask(1);	//����ͼ����ʾ
		}
		m_SliceGroup->setNodeMask(0);			//��Ƭͼ����ʾ
		m_surfaceDownGroup->setNodeMask(0);	//��ֵ��ͼ����ʾ
		m_surfaceUpGroup->setNodeMask(0);	//��ֵ��ͼ����ʾ
		if (NULL != m_lineFlagGroup)
			m_lineFlagGroup->setNodeMask(0);
	}
	else if (index == SLICE_EXTRACTION)
	{
		m_detectPointsGroup->setNodeMask(0);	//����ͼ����ʾ
		m_SliceGroup->setNodeMask(1);			//��Ƭͼ����ʾ
		m_surfaceDownGroup->setNodeMask(0);	//��ֵ��ͼ����ʾ
		m_surfaceUpGroup->setNodeMask(0);	//��ֵ��ͼ����ʾ
		if(NULL != m_sliceBodyGroup)
		  m_sliceBodyGroup->setNodeMask(0);
		if (NULL != m_lineFlagGroup)
			m_lineFlagGroup->setNodeMask(0);
	}
	else if (index == EQUIVALENT_SURFACE_EXTRACTION)
	{
		m_detectPointsGroup->setNodeMask(0);	//����ͼ����ʾ
		m_SliceGroup->setNodeMask(0);			//��Ƭͼ����ʾ
		m_surfaceDownGroup->setNodeMask(1);	//��ֵ��ͼ����ʾ
		m_surfaceUpGroup->setNodeMask(1);	//��ֵ��ͼ����ʾ
		if (NULL != m_lineFlagGroup)
		    m_lineFlagGroup->setNodeMask(1);
		if (NULL != m_sliceBodyGroup)
		    m_sliceBodyGroup->setNodeMask(0);
	}
	else if (index == DATA_SHOW_ALL)
	{
		m_detectPointsGroup->setNodeMask(0);	//����ͼ����ʾ
		m_SliceGroup->setNodeMask(1);			//��Ƭͼ����ʾ
		m_surfaceDownGroup->setNodeMask(1);	//��ֵ��ͼ����ʾ
		m_surfaceUpGroup->setNodeMask(1);	//��ֵ��ͼ����ʾ
		if (NULL != m_sliceBodyGroup)
		   m_sliceBodyGroup->setNodeMask(0);
		if (NULL != m_lineFlagGroup)
			m_lineFlagGroup->setNodeMask(1);
	}
}

/***********************************************************************************/
//function: ����image������Ƭ
void MyWidgetImaging::createAndSliceImage()
{
	if (NULL == m_pPointsDataArray || m_pPointsDataArray->size() == 0)
		return;

	if (m_detectImageDisplay == NULL)
	{
		m_detectImageDisplay = new osgEngine::CImageCreate();
	}
	
	if ((m_displayRangeValue != m_compareRangeValue))
	{
		m_compareRangeValue = m_displayRangeValue;
		m_SliceGroup->removeChildren(0, m_SliceGroup->getNumChildren());

		////////x��
		if (m_sliceDrection_x == true)
		{
			float moveValue = float((m_xMax - m_xMin)*m_displayRangeValue) / 100.0;
			double posValue = moveValue + m_xMin;
			
			osg::ref_ptr<osg::Geode> m_pNodeX = m_detectImageDisplay->createImage(osgEngine::CImageCreate::xdirect, posValue, this);
			osg::StateSet* geodStatesetX = m_pNodeX->getOrCreateStateSet();
			geodStatesetX->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
			geodStatesetX->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
			m_SliceGroup->addChild(m_pNodeX.get());
		}

		////////y��
		if (m_sliceDrection_y == true)
		{
			float moveValue = float((m_yMax - m_yMin)*m_displayRangeValue) / 100;
			double posValue = moveValue + m_yMin;
			osg::ref_ptr<osg::Geode> m_pNodeY = m_detectImageDisplay->createImage(osgEngine::CImageCreate::ydirect, posValue,this);
			osg::StateSet* geodStatesetY = m_pNodeY->getOrCreateStateSet();
			geodStatesetY->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
			geodStatesetY->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
			m_SliceGroup->addChild(m_pNodeY.get());
		}

		////////z��
		if (m_sliceDrection_z == true)
		{
			float moveValue = float((m_zMax - m_zMin)*m_displayRangeValue) / 100;
			double posValue = moveValue + m_zMin;

			osg::ref_ptr<osg::Geode> m_pNodeZ = m_detectImageDisplay->createImage(osgEngine::CImageCreate::zdirect, moveValue+m_zMin,this);
			osg::StateSet* geodStatesetY = m_pNodeZ->getOrCreateStateSet();
			geodStatesetY->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
			geodStatesetY->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
			m_SliceGroup->addChild(m_pNodeZ.get());
		}
	}
}

/***********************************************************************************/
//function: ����image������Ƭ
void MyWidgetImaging::createAndSliceIrresurface()
{
	if (NULL == m_pPointsDataArray || m_pPointsDataArray->size() == 0)
		return;

	if (m_CMarchingCube == NULL)
	{
		//������ֵ��
		m_CMarchingCube = new osgEngine::marchingCubeDraw(m_repo);
		m_CMarchingCube->setFirstValue(m_minSpeed);
		m_CMarchingCube->setTwoValue(m_minSpeed);
		if (NULL != m_pBaseDraw)
		    m_CMarchingCube->setBaseDraw(m_pBaseDraw);
		m_CMarchingCube->initData(m_xMin,m_xMax,m_yMin,m_yMax,m_zMin,m_zMax,m_minSpeed, m_maxSpeed,this->getPointsArray());
	}
	else
	{
		m_CMarchingCube->setFirstValue(m_minSpeed);
		m_CMarchingCube->setTwoValue(m_minSpeed);
		if (NULL != m_pBaseDraw)
			m_CMarchingCube->setBaseDraw(m_pBaseDraw);
		m_CMarchingCube->initData(m_xMin, m_xMax, m_yMin, m_yMax, m_zMin, m_zMax, m_minSpeed, m_maxSpeed, this->getPointsArray());
	}

	osg::ref_ptr<osg::Light> pLight = new osg::Light;
	//���û�����
	pLight->setAmbient(osg::Vec4(0.85f, 0.85f, 0.85f, 1.0f));
	//����ɢ������ɫ
	pLight->setDiffuse(osg::Vec4(0.75f, 0.75f, 0.75f, 1.0f));
	pLight->setSpecular(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));

	osg::ref_ptr<osg::LightSource> lightSource = new osg::LightSource;
	lightSource->setLight(pLight.get());
	m_surfaceUpGroup->addChild(lightSource.get());
	m_surfaceDownGroup->addChild(lightSource.get());
	osg::ref_ptr<osgEngine::CShadingLight> pShadingLight = new osgEngine::CShadingLight();
	pShadingLight->createLocalShaderLight(0, m_surfaceUpGroup.get());
	pShadingLight->createLocalShaderLight(0, m_surfaceDownGroup.get());

	getSceneGroup()->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);//����Ȳ���
	getSceneGroup()->getOrCreateStateSet()->setMode(GL_LIGHT0, osg::StateAttribute::ON);
	getSceneGroup()->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);//����Ȳ���
	getSceneGroup()->getOrCreateStateSet()->setMode(GL_FRONT_AND_BACK, osg::StateAttribute::ON);//˫�����
}

/********************************************************************/
//function:������Ƭ��չʾ
void MyWidgetImaging::changeDisplayRangeValue(int displayRangeValue)
{
	emit setDisplayRangeValue(QString::number(displayRangeValue));
	m_displayRangeValue = displayRangeValue;
	if (m_currentTabIndex == TAB_ID::SLICE_EXTRACTION || m_currentTabIndex == TAB_ID::DATA_SHOW_ALL)
	{
	    createAndSliceImage();
	}
	//else if (m_currentTabIndex == 2)
	//{
	//    createAndSliceIrresurface();
	//}
}

void MyWidgetImaging::onStateChangedX(int state)
{
	if (state == Qt::Checked) // "ѡ��"
	{
		m_sliceDrection_x = true;
	}
	else // δѡ�� - Qt::Unchecked
	{
		m_sliceDrection_x = false;
	}
	m_compareRangeValue = -1;
	createAndSliceImage();
}

/**********************************************************************************************************************/
//function:
void MyWidgetImaging::onStateChangedY(int state)
{
	if (state == Qt::Checked) // "ѡ��"
	{
		m_sliceDrection_y = true;
	}
	else // δѡ�� - Qt::Unchecked
	{
		m_sliceDrection_y = false;
	}
	m_compareRangeValue = -1;
	createAndSliceImage();
}

/**********************************************************************************************************************/
//function:
void MyWidgetImaging::onStateChangedZ(int state)
{
	if (state == Qt::Checked) // "ѡ��"
	{
		m_sliceDrection_z = true;
	}
	else // δѡ�� - Qt::Unchecked
	{
		m_sliceDrection_z = false;
	}
	m_compareRangeValue = -1;
	createAndSliceImage();
}


void MyWidgetImaging::onStateBoundBoxLineX(int state)
{
	if (state == Qt::Checked) // "ѡ��"
	{
		m_boundBoxLineX = true;
	}
	else // δѡ�� - Qt::Unchecked
	{
		m_boundBoxLineX = false;
	}
	boundBoxCheckLine();
}

void MyWidgetImaging::onStateBoundBoxLineY(int state)
{
	if (state == Qt::Checked) // "ѡ��"
	{
		m_boundBoxLineY = true;
	}
	else // δѡ�� - Qt::Unchecked
	{
		m_boundBoxLineY = false;
	}
	boundBoxCheckLine();
}

void MyWidgetImaging::onStateBoundBoxLineZ(int state)
{
	if (state == Qt::Checked) // "ѡ��"
	{
		m_boundBoxLineZ = true;
	}
	else // δѡ�� - Qt::Unchecked
	{
		m_boundBoxLineZ = false;
	}
	boundBoxCheckLine();
}


/**********************************************************************************************************/
//function : �����쳣��߽���Ϣ����Ļչʾ
void MyWidgetImaging::createLegend(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
{
	//ͼ��
	osg::ref_ptr<osgText::Text> text = new osgText::Text;
	//����������ʾ��λ��
	float textXPos = 20;
	float textYPos = this->height() - 20;
	char buf[64];

	text->setPosition(osg::Vec3(textXPos, textYPos, 0.0f));
	text->setColor(osg::Vec4(0, 0, 1, 1));
	text->setText(L"WaterBody XYZ Edge : ");//������ʾ������
	text->setCharacterSize(14);  //���������С
	
	osg::ref_ptr<osgText::Text> text1 = new osgText::Text;
	text1->setPosition(osg::Vec3(textXPos, textYPos-20, 0.0f));//����������ʾ��λ��
	text1->setColor(osg::Vec4(0, 0, 1, 1));
	sprintf(buf," xmin postion:%.2fm",xMin);
	text1->setText(buf);//������ʾ������
	text1->setCharacterSize(12);  //���������С
	
	osg::ref_ptr<osgText::Text> text2 = new osgText::Text;
	text2->setPosition(osg::Vec3(textXPos, textYPos-40, 0.0f));//����������ʾ��λ��
	text2->setColor(osg::Vec4(0, 0, 1, 1));
	sprintf(buf, " xmax postion:%.2fm",xMax);
	text2->setText(buf);//������ʾ������
	text2->setCharacterSize(12);  //���������С
	
	osg::ref_ptr<osgText::Text> text3 = new osgText::Text;
	text3->setPosition(osg::Vec3(textXPos, textYPos - 60, 0.0f));//����������ʾ��λ��
	text3->setColor(osg::Vec4(0, 0, 1, 1));
	sprintf(buf, " ymin postion:%.2fm",yMin);
	text3->setText(buf);//������ʾ������
	text3->setCharacterSize(12);  //���������С

	osg::ref_ptr<osgText::Text> text4 = new osgText::Text;
	text4->setPosition(osg::Vec3(textXPos, textYPos - 80, 0.0f));//����������ʾ��λ��
	text4->setColor(osg::Vec4(0, 0, 1, 1));
	sprintf(buf, " ymax postion:%.2fm", yMax);
	text4->setText(buf);//������ʾ������
	text4->setCharacterSize(12);  //���������С

	osg::ref_ptr<osgText::Text> text5 = new osgText::Text;
	text5->setPosition(osg::Vec3(textXPos, textYPos - 100, 0.0f));//����������ʾ��λ��
	text5->setColor(osg::Vec4(0, 0, 1, 1));
	sprintf(buf, " zmin postion:%.2fm", zMin);
	text5->setText(buf);//������ʾ������
	text5->setCharacterSize(12);  //���������С

	osg::ref_ptr<osgText::Text> text6 = new osgText::Text;
	text6->setPosition(osg::Vec3(textXPos, textYPos - 120, 0.0f));//����������ʾ��λ��
	text6->setColor(osg::Vec4(0, 0, 1, 1));
	sprintf(buf, " zmax postion:%.2fm", zMax);
	text6->setText(buf);//������ʾ������
	text6->setCharacterSize(12);  //���������С
	
	//������ڵ�
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	//������Text����drawable���뵽Geode�ڵ���
	geode->addDrawable(text.get()); //ͼ��
	geode->addDrawable(text1.get()); //������Text����drawable���뵽Geode�ڵ���
	geode->addDrawable(text2.get()); //������Text����drawable���뵽Geode�ڵ���
	geode->addDrawable(text3.get()); //������Text����drawable���뵽Geode�ڵ���
	geode->addDrawable(text4.get()); //������Text����drawable���뵽Geode�ڵ���
	geode->addDrawable(text5.get()); //������Text����drawable���뵽Geode�ڵ���
	geode->addDrawable(text6.get()); //������Text����drawable���뵽Geode�ڵ���

    //����״̬
	osg::StateSet* stateset = geode->getOrCreateStateSet();
	stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);//�رյƹ�
	stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);//�ر���Ȳ���
	 //��GL_BLEND���ģʽ���Ա�֤Alpha������ȷ��
	stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
	if (NULL == m_orthoCamera)
	{
		m_orthoCamera = new osg::Camera;
		//����͸�Ӿ���
		m_orthoCamera->setProjectionMatrix(osg::Matrix::ortho2D(0, this->width(), 0, this->height()));//����ͶӰ
        //���þ��Բο�����ϵ��ȷ����ͼ���󲻻ᱻ�ϼ��ڵ�ı任����Ӱ��
		m_orthoCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
		//��ͼ����ΪĬ�ϵ�
		m_orthoCamera->setViewMatrix(osg::Matrix::identity());
		//���ñ���Ϊ͸��������Ļ���������ClearColor
		m_orthoCamera->setClearMask(GL_DEPTH_BUFFER_BIT);
		m_orthoCamera->setAllowEventFocus(false);//����Ӧ�¼���ʼ�յò�������
		//������Ⱦ˳�򣬱����������Ⱦ
		m_orthoCamera->setRenderOrder(osg::Camera::POST_RENDER);
		if (NULL != m_textGeodeGroup)
		{
			m_textGeodeGroup->removeChildren(0, m_textGeodeGroup->getNumChildren());
			m_textGeodeGroup->addChild(geode.get());
		}
		else
		{
			m_textGeodeGroup = new osg::Group;
			m_textGeodeGroup->addChild(geode.get());
			m_orthoCamera->addChild(m_textGeodeGroup.get());//��Ҫ��ʾ��Geode�ڵ���뵽���
		}
		
		getSceneGroup()->addChild(m_orthoCamera.get());
	}
	else
	{
		if (NULL != m_textGeodeGroup)
		{
			m_textGeodeGroup->removeChildren(0, m_textGeodeGroup->getNumChildren());
			m_textGeodeGroup->addChild(geode.get());
		}
		else
		{
			m_textGeodeGroup = new osg::Group;
			m_textGeodeGroup->addChild(geode.get());
			m_orthoCamera->addChild(m_textGeodeGroup.get());//��Ҫ��ʾ��Geode�ڵ���뵽���
		}
	}
}

/**********************************************************************************************************/
//function : �����쳣��߽���Ϣ����Ļչʾ
void MyWidgetImaging::createLegendDown()
{
	if (NULL == m_orthoCamera || m_orthoCamera->getNumChildren() == 0)
	{
		return;
	}

	float xMin = GlobalParam::instance()->getForwardModelingParaSetting().actual_begin_x;
	float xMax = GlobalParam::instance()->getForwardModelingParaSetting().actual_end_x;
	float yMin = GlobalParam::instance()->getForwardModelingParaSetting().actual_begin_y;
	float yMax = GlobalParam::instance()->getForwardModelingParaSetting().actual_end_y;
	float zMin = GlobalParam::instance()->getForwardModelingParaSetting().actual_begin_z;
	float zMax = GlobalParam::instance()->getForwardModelingParaSetting().actual_end_z;

	if (fabs(xMin) < 1e-15 || fabs(xMax) < 1e-15 || fabs(yMin) < 1e-15 || fabs(yMax) < 1e-15 || fabs(zMin) < 1e-15 || fabs(zMax) < 1e-15)
	{
		//return;
	}

	//ͼ��
	osg::ref_ptr<osgText::Text> text = new osgText::Text;
	//����������ʾ��λ��
	float textXPos = 20;
	float textYPos = this->height() - 180;
	char buf[64];

	text->setPosition(osg::Vec3(textXPos, textYPos, 0.0f));
	text->setColor(osg::Vec4(0, 0, 1, 1));
	text->setText(L"SimulaBody Real XYZ: ");//������ʾ������
	text->setCharacterSize(14);  //���������С

	osg::ref_ptr<osgText::Text> text1 = new osgText::Text;
	text1->setPosition(osg::Vec3(textXPos, textYPos - 18, 0.0f));//����������ʾ��λ��
	text1->setColor(osg::Vec4(0, 0, 1, 1));
	sprintf(buf, " xmin postion:%.2fm", xMin);
	text1->setText(buf);//������ʾ������
	text1->setCharacterSize(12);  //���������С

	osg::ref_ptr<osgText::Text> text2 = new osgText::Text;
	text2->setPosition(osg::Vec3(textXPos, textYPos - 40, 0.0f));//����������ʾ��λ��
	text2->setColor(osg::Vec4(0, 0, 1, 1));
	sprintf(buf, " xmax postion:%.2fm", xMax);
	text2->setText(buf);//������ʾ������
	text2->setCharacterSize(12);  //���������С

	osg::ref_ptr<osgText::Text> text3 = new osgText::Text;
	text3->setPosition(osg::Vec3(textXPos, textYPos - 60, 0.0f));//����������ʾ��λ��
	text3->setColor(osg::Vec4(0, 0, 1, 1));
	sprintf(buf, " ymin postion:%.2fm", yMin);
	text3->setText(buf);//������ʾ������
	text3->setCharacterSize(12);  //���������С

	osg::ref_ptr<osgText::Text> text4 = new osgText::Text;
	text4->setPosition(osg::Vec3(textXPos, textYPos - 80, 0.0f));//����������ʾ��λ��
	text4->setColor(osg::Vec4(0, 0, 1, 1));
	sprintf(buf, " ymax postion:%.2fm", yMax);
	text4->setText(buf);//������ʾ������
	text4->setCharacterSize(12);  //���������С

	osg::ref_ptr<osgText::Text> text5 = new osgText::Text;
	text5->setPosition(osg::Vec3(textXPos, textYPos - 100, 0.0f));//����������ʾ��λ��
	text5->setColor(osg::Vec4(0, 0, 1, 1));
	sprintf(buf, " zmin postion:%.2fm", zMin);
	text5->setText(buf);//������ʾ������
	text5->setCharacterSize(12);  //���������С

	osg::ref_ptr<osgText::Text> text6 = new osgText::Text;
	text6->setPosition(osg::Vec3(textXPos, textYPos - 120, 0.0f));//����������ʾ��λ��
	text6->setColor(osg::Vec4(0, 0, 1, 1));
	sprintf(buf, " zmax postion:%.2fm", zMax);
	text6->setText(buf);//������ʾ������
	text6->setCharacterSize(12);  //���������С

	//������ڵ�
	if (NULL == m_geode)
	{
		m_geode = new osg::Geode();
	}

	m_geode->removeChildren(0, m_geode->getNumChildren());
	m_orthoCamera->removeChild(m_geode.get());

	//������Text����drawable���뵽Geode�ڵ���
	m_geode->addDrawable(text.get()); //ͼ��
	m_geode->addDrawable(text1.get()); //������Text����drawable���뵽Geode�ڵ���
	m_geode->addDrawable(text2.get()); //������Text����drawable���뵽Geode�ڵ���
	m_geode->addDrawable(text3.get()); //������Text����drawable���뵽Geode�ڵ���
	m_geode->addDrawable(text4.get()); //������Text����drawable���뵽Geode�ڵ���
	m_geode->addDrawable(text5.get()); //������Text����drawable���뵽Geode�ڵ���
	m_geode->addDrawable(text6.get()); //������Text����drawable���뵽Geode�ڵ���

	//����״̬
	osg::StateSet* stateset = m_geode->getOrCreateStateSet();
	stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);//�رյƹ�
	stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);//�ر���Ȳ���
	//��GL_BLEND���ģʽ���Ա�֤Alpha������ȷ��
	stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
	//��Ҫ��ʾ��Geode�ڵ���뵽���
	m_textGeodeGroup->addChild(m_geode.get());
}

void MyWidgetImaging::removeText()
{
	m_textGeodeGroup->removeChildren(0, m_textGeodeGroup->getNumChildren());
}

void MyWidgetImaging::boundBoxCheckLine()
{
	if (m_surfaceDownGroup->getNumChildren() == 0)	return;

	osg::Geode* pNodeOne = dynamic_cast<osg::Geode*>(m_surfaceDownGroup->getChild(0));
	if (NULL == pNodeOne)
		return;

	m_lineFlagGroup->removeChildren(0, m_lineFlagGroup->getNumChildren());

	osg::Vec3d radiusCenter = pNodeOne->getBoundingBox().center();
	double xBoundMin = pNodeOne->getBoundingBox().xMin();
	double xBoundMax = pNodeOne->getBoundingBox().xMax();
	double yBoundMin = pNodeOne->getBoundingBox().yMin();
	double yBoundMax = pNodeOne->getBoundingBox().yMax();
	double zBoundMin = pNodeOne->getBoundingBox().zMin();
	double zBoundMax = pNodeOne->getBoundingBox().zMax();

	//�������漸����Ϣ�Ķ���
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	geode->getOrCreateStateSet()->setAttribute(new osg::LineWidth(1.5), osg::StateAttribute::ON);
	
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
	float textSize = 1.0;
	char buf[64];
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	if (m_boundBoxLineY)
	{
		v->push_back(osg::Vec3(radiusCenter.x(), yBoundMin, radiusCenter.z()));
		v->push_back(osg::Vec3(m_xMin, yBoundMin, radiusCenter.z()));
		sprintf(buf, "ymin:%.2fm", yBoundMin);
		osg::ref_ptr<osgText::Text> pTextXMinAuxis = new osgText::Text;
		pTextXMinAuxis->setText(buf);
		pTextXMinAuxis->setFont("Fonts/simhei.ttf");
		pTextXMinAuxis->setAxisAlignment(osgText::Text::XZ_PLANE);
		pTextXMinAuxis->setCharacterSize(textSize);
		pTextXMinAuxis->setPosition(osg::Vec3(radiusCenter.x() / 4, yBoundMin, radiusCenter.z()));
		pTextXMinAuxis->setColor(osg::Vec4(0, 0, 0, 1.0));

		v->push_back(osg::Vec3(radiusCenter.x(), yBoundMax, radiusCenter.z()));
		v->push_back(osg::Vec3(m_xMin, yBoundMax, radiusCenter.z()));
		osg::ref_ptr<osgText::Text> pTextXMaxAuxis = new osgText::Text;
		sprintf(buf, "ymax:%.2fm", yBoundMax);
		pTextXMaxAuxis->setText(buf);
		pTextXMaxAuxis->setFont("Fonts/simhei.ttf");
		pTextXMaxAuxis->setAxisAlignment(osgText::Text::XZ_PLANE);
		pTextXMaxAuxis->setCharacterSize(textSize);
		pTextXMaxAuxis->setColor(osg::Vec4(0, 0, 0, 1.0));
		pTextXMaxAuxis->setPosition(osg::Vec3(radiusCenter.x() / 4, yBoundMax, radiusCenter.z()));
		geode->addDrawable(pTextXMinAuxis.get());
		geode->addDrawable(pTextXMaxAuxis.get());
		
	}
	
	if (m_boundBoxLineX)
	{
		v->push_back(osg::Vec3(xBoundMin, radiusCenter.y(), radiusCenter.z()));
		v->push_back(osg::Vec3(xBoundMin, m_yMin, radiusCenter.z()));
		osg::ref_ptr<osgText::Text> pTextYMinAuxis = new osgText::Text;
		sprintf(buf, "xmin:%.2fm", xBoundMin);
		pTextYMinAuxis->setText(buf);
		pTextYMinAuxis->setFont("Fonts/simhei.ttf");
		pTextYMinAuxis->setAxisAlignment(osgText::Text::YZ_PLANE);
		pTextYMinAuxis->setCharacterSize(textSize);
		pTextYMinAuxis->setColor(osg::Vec4(0, 0, 0, 1.0));
		pTextYMinAuxis->setPosition(osg::Vec3(xBoundMin, radiusCenter.y() / 4, radiusCenter.z()));

		v->push_back(osg::Vec3(xBoundMax, radiusCenter.y(), radiusCenter.z()));
		v->push_back(osg::Vec3(xBoundMax, m_yMin, radiusCenter.z()));
		osg::ref_ptr<osgText::Text> pTextYMaxAuxis = new osgText::Text;
		sprintf(buf, "xmax:%.2fm", xBoundMax);
		pTextYMaxAuxis->setText(buf);
		pTextYMaxAuxis->setFont("Fonts/simhei.ttf");
		pTextYMaxAuxis->setAxisAlignment(osgText::Text::YZ_PLANE);
		pTextYMaxAuxis->setCharacterSize(textSize);
		pTextYMaxAuxis->setColor(osg::Vec4(0, 0, 0, 1.0));
		pTextYMaxAuxis->setPosition(osg::Vec3(xBoundMax, radiusCenter.y() / 4, radiusCenter.z()));
		
		geode->addDrawable(pTextYMinAuxis.get());
		geode->addDrawable(pTextYMaxAuxis.get());
	}
	
	if (m_boundBoxLineZ)
	{
		v->push_back(osg::Vec3(radiusCenter.x(), radiusCenter.y(), zBoundMin));
		v->push_back(osg::Vec3(radiusCenter.x(), m_yMin, zBoundMin));
		osg::ref_ptr<osgText::Text> pTextZMinAuxis = new osgText::Text;
		sprintf(buf, "zmin:%.2fm", (zBoundMin));
		pTextZMinAuxis->setText(buf);
		pTextZMinAuxis->setFont("Fonts/simhei.ttf");
		pTextZMinAuxis->setAxisAlignment(osgText::Text::YZ_PLANE);
		pTextZMinAuxis->setCharacterSize(textSize);
		pTextZMinAuxis->setColor(osg::Vec4(0, 0, 0, 1.0));
		pTextZMinAuxis->setPosition(osg::Vec3(radiusCenter.x(), radiusCenter.y() / 4, zBoundMin));


		v->push_back(osg::Vec3(radiusCenter.x(), radiusCenter.y(), zBoundMax));
		v->push_back(osg::Vec3(radiusCenter.x(), m_yMin, zBoundMax));
		osg::ref_ptr<osgText::Text> pTextZMaxAuxis = new osgText::Text;
		sprintf(buf, "zmax:%.2fm", zBoundMax);
		pTextZMaxAuxis->setText(buf);
		pTextZMaxAuxis->setFont("Fonts/simhei.ttf");
		pTextZMaxAuxis->setAxisAlignment(osgText::Text::YZ_PLANE);
		pTextZMaxAuxis->setCharacterSize(textSize);
		pTextZMaxAuxis->setColor(osg::Vec4(0, 0, 0, 1.0));
		pTextZMaxAuxis->setPosition(osg::Vec3(radiusCenter.x(), radiusCenter.y() / 4, zBoundMax));
		
		geode->addDrawable(pTextZMinAuxis.get());
		geode->addDrawable(pTextZMaxAuxis.get());
	}
	geom->setVertexArray(v.get());
	//Ϊÿ������ָ��һ����ɫ
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();
	c->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f)); //����ԭ��Ϊ��ɫ
	geom->setColorArray(c.get());
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);

	//������
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, v->size())); //X	
	geode->addDrawable(geom.get());
	m_lineFlagGroup->addChild(geode.get());
}

/****************************************************************************************************/
//function:��ֵ����㷶Χ
void MyWidgetImaging::changeEquivalentPointUp(int equivalentSurfaceValue)
{
	m_equivalentPointValueUp = equivalentSurfaceValue;

	if (NULL == m_pPointsDataArray || m_pPointsDataArray->size() == 0)
	{
		return;
	}

	if (NULL == m_waterPointsGroup)
	{
		m_waterPointsGroup = new osg::Group;
		m_detectPointsGroup->removeChildren(0, m_detectPointsGroup->getNumChildren());
		getSceneGroup()->addChild(m_waterPointsGroup.get());
	}
	else
	{
		m_detectPointsGroup->removeChildren(0, m_detectPointsGroup->getNumChildren());
		m_waterPointsGroup->removeChildren(0, m_waterPointsGroup->getNumChildren());
	}
	osg::ref_ptr<osg::Vec4dArray> pointsArray = new osg::Vec4dArray;

	//float ratio = 100 / (1000 - m_minSpeed);
	float ratio = 100 / (m_maxSpeed - m_minSpeed);
	float moveValueBegin = m_equivalentPointValueUp / ratio + m_minSpeed;
	float moveValueEnd = m_equivalentPointValueDown / ratio + m_minSpeed;

	if (moveValueBegin > moveValueEnd)
		return;

	for (int i = 0; i < m_pPointsDataArray->size(); i++)
	{
		if ((*m_pPointsDataArray)[i].w() <= moveValueEnd &&
			(*m_pPointsDataArray)[i].w() >= moveValueBegin)
		{
			pointsArray->push_back(osg::Vec4d((*m_pPointsDataArray)[i].x(), (*m_pPointsDataArray)[i].y()
				, (*m_pPointsDataArray)[i].z(), (*m_pPointsDataArray)[i].w()));
		}
	}

	//osg::ref_ptr<osg::Geode> pGeode = m_pBaseDraw->drawPoints(pointsArray.get(), 2, m_minSpeed, 1000);
	osg::ref_ptr<osg::Geode> pGeode = m_pBaseDraw->drawPoints(pointsArray.get(), 2, m_minSpeed, m_maxSpeed);
	m_waterPointsGroup->addChild(pGeode.get());
	double totalVolume = m_sizeX * m_sizeY *m_sizeZ;
	double calculateVolume = ((double)pointsArray->size() / (double)(m_pPointsDataArray->size())) * totalVolume;

	//TODO emit calculateVolume
	emit setWaterVolume(QString::number(calculateVolume));
	getViewer()->setSceneData(getSceneGroup());

}

/****************************************************************************************************/
//function:��ֵ����ֹ��Χ
void MyWidgetImaging::changeEquivalentPointDown(int equivalentSurfaceValue)
{
	if (NULL == m_pPointsDataArray || m_pPointsDataArray->size() == 0)
	{
		return;
	}

	if (NULL == m_waterPointsGroup)
	{
		m_waterPointsGroup = new osg::Group;
		m_detectPointsGroup->removeChildren(0, m_detectPointsGroup->getNumChildren());
		getSceneGroup()->addChild(m_waterPointsGroup.get());
	}
	else
	{
		m_detectPointsGroup->removeChildren(0, m_detectPointsGroup->getNumChildren());
		m_waterPointsGroup->removeChildren(0, m_waterPointsGroup->getNumChildren());
	}
	osg::ref_ptr<osg::Vec4dArray> pointsArray = new osg::Vec4dArray;

	float ratio = 100 / (m_maxSpeed - m_minSpeed);
	m_equivalentPointValueDown = equivalentSurfaceValue;

	float moveValueBegin = m_equivalentPointValueUp / ratio + m_minSpeed;
	float moveValueEnd = equivalentSurfaceValue / ratio + m_minSpeed;
	
	if (moveValueBegin > moveValueEnd)
		return;

	for (int i = 0; i < m_pPointsDataArray->size(); i++)
	{
		if ((*m_pPointsDataArray)[i].w() <= moveValueEnd && 
			    (*m_pPointsDataArray)[i].w() >= moveValueBegin)
		{
			pointsArray->push_back(osg::Vec4d((*m_pPointsDataArray)[i].x(), (*m_pPointsDataArray)[i].y()
				,(*m_pPointsDataArray)[i].z(), (*m_pPointsDataArray)[i].w()));
		}
	}

	//osg::ref_ptr<osg::Geode> pGeode = m_pBaseDraw->drawPoints(pointsArray.get(), 2, m_minSpeed, 1000);
	osg::ref_ptr<osg::Geode> pGeode = m_pBaseDraw->drawPoints(pointsArray.get(), 2, m_minSpeed, m_maxSpeed);
	m_waterPointsGroup->addChild(pGeode.get());

	double totalVolume = m_sizeX * m_sizeY *m_sizeZ;
	double calculateVolume = ((double)pointsArray->size() / (double)(m_pPointsDataArray->size())) * totalVolume;

	//TODO emit calculateVolume
	emit setWaterVolume(QString::number(calculateVolume));
	getViewer()->setSceneData(getSceneGroup());
}

//��ȡ�ϱ�[��ֵ��]��ֵ
void MyWidgetImaging::changeEquivalentSurfaceValueUp(int equivalentSurfaceValue)
{
	emit setEquivalentSurfaceValueUp(QString::number(equivalentSurfaceValue));
	emit setCheckBox(false);

	if (NULL == m_pPointsDataArray || m_pPointsDataArray->size() == 0)
		return;

	createAndSliceIrresurface();

	float ratio = 100 / (m_maxSpeed - m_minSpeed);
	float moveValue = equivalentSurfaceValue / ratio;
	m_CMarchingCube->setFirstValue(m_minSpeed + moveValue);
	m_CMarchingCube->clearLastPoints();//ɾ����һ���Ķ���
	m_surfaceUpGroup->removeChild(0, m_surfaceUpGroup->getNumChildren());
	m_lineFlagGroup->removeChild(0, m_lineFlagGroup->getNumChildren());
	m_CMarchingCube->MarchingCubes(m_minSpeed + moveValue);

	osg::ref_ptr<osg::Geode> pNodeOne = m_CMarchingCube->drawSamesurface();
	osg::StateSet* geodStateset = pNodeOne->getOrCreateStateSet();
	geodStateset->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
	geodStateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
	m_surfaceUpGroup->addChild(pNodeOne.get());	
}

/*************************************************************************************************/
//function:
void MyWidgetImaging::changePointsTab(int vTabIndex)
{
	if (vTabIndex == 2)
	{
		displayAllPoints();
	}
}

//��ȡ�±�[��ֵ��]��ֵ
void MyWidgetImaging::changeEquivalentSurfaceValueDown(int equivalentSurfaceValue)
{
	emit setEquivalentSurfaceValueDown(QString::number(equivalentSurfaceValue));
	emit setCheckBox(false);

	if (NULL == m_pPointsDataArray || m_pPointsDataArray->size() == 0)
		return;

	createAndSliceIrresurface();
	//float ratio = 100 / (1000 - m_minSpeed);
	float ratio = 100 / (m_maxSpeed - m_minSpeed);
	float moveValue = equivalentSurfaceValue / ratio;

	m_CMarchingCube->clearLastPoints();//ɾ����һ���Ķ���
	m_surfaceDownGroup->removeChild(0, m_surfaceDownGroup->getNumChildren());
	m_lineFlagGroup->removeChild(0, m_lineFlagGroup->getNumChildren());
	m_CMarchingCube->MarchingCubes(m_minSpeed + moveValue);
	m_CMarchingCube->setTwoValue(m_minSpeed + moveValue);

	osg::ref_ptr<osg::Geode> pNodeTwo = m_CMarchingCube->drawSamesurface();
	osg::StateSet* geodStatesetTwo = pNodeTwo->getOrCreateStateSet();
	geodStatesetTwo->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
	geodStatesetTwo->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
	
	double xBoundMin = pNodeTwo->getBoundingBox().xMin();
	double xBoundMax = pNodeTwo->getBoundingBox().xMax();
	double yBoundMin = pNodeTwo->getBoundingBox().yMin();
	double yBoundMax = pNodeTwo->getBoundingBox().yMax();
	double zBoundMin = pNodeTwo->getBoundingBox().zMin();
	double zBoundMax = pNodeTwo->getBoundingBox().zMax();

	if (fabs(xBoundMin) > 100000)
	{
		xBoundMin = 0;
		xBoundMax =	0;
		yBoundMin =	0;
		yBoundMax =	0;
		zBoundMin =	0;
		zBoundMax =	0;
	}

	GlobalParam::InversionParaSetting& setting = GlobalParam::instance()->getInversionParaSetting();

	if (setting.showLegend && setting.isSim)
	{
		createLegend(xBoundMin, xBoundMax, yBoundMin, yBoundMax, zBoundMin, zBoundMax);
		createLegendDown();
	}
	
	m_surfaceDownGroup->addChild(pNodeTwo.get());
}

void MyWidgetImaging::resizeEvent(QResizeEvent *e)
{
	ViewerWidget3d::resizeEvent(e);

	emit changeDisplayWidgetSize();

	if (NULL != m_orthoCamera)
	{
		m_orthoCamera->setProjectionMatrix(osg::Matrix::ortho2D(0, this->width(), 0, this->height()));//����ͶӰ																									  //���þ��Բο�����ϵ��ȷ����ͼ���󲻻ᱻ�ϼ��ڵ�ı任����Ӱ��
		m_orthoCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
		m_orthoCamera->setViewMatrix(osg::Matrix::identity());
	}
}

void MyWidgetImaging::showData()
{
	double *** data;
	int x, y, z;

	data = DataManager::instance()->getInversionProcessData();
	x = DataManager::instance()->getInversionProcessDataXLen();
	y = DataManager::instance()->getInversionProcessDataYLen();
	z = DataManager::instance()->getInversionProcessDataZLen();
	//���µ�������
	initPointsToScene(data, z, y, x);
}
void MyWidgetImaging::showNROData()
{
	double *** data;
	int x, y, z;

	data = DataManager::instance()->getInversionProcessNROData();
	x = DataManager::instance()->getInversionProcessNRODataXBegLen();
	y = DataManager::instance()->getInversionProcessNRODataYBegLen();
	z = DataManager::instance()->getInversionProcessNRODataZBegLen();

	int xEnd, yEnd, zEnd;
	xEnd = DataManager::instance()->getInversionProcessNRODataXEndLen();
	yEnd = DataManager::instance()->getInversionProcessNRODataYEndLen();
	zEnd = DataManager::instance()->getInversionProcessNRODataZEndLen();

	if (NULL == data)
	{
		if (NULL != m_pPointsDataArray)
			m_pPointsDataArray->clear();

		getSceneGroup()->removeChildren(0, getSceneGroup()->getNumChildren());
		QMessageBox::warning(this, QStringLiteral("���ݼ��"), QStringLiteral("���ݲ�����"));
		return;
	}
	//���µ�������
	initNROPointsToScene(data, z, y, x, zEnd, yEnd, xEnd);
}