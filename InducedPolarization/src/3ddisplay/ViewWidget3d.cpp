#include "3ddisplay/ViewerWidget3d.h"
#include "osgGA/TrackballManipulator"
#include <osgGA/StateSetManipulator>
#include "GlobalClass/GlobalParam.h"
#include <QtWidgets/QMenu>
#include "QTextCodec"
#include <osgDB/WriteFile>


/****************************************************************************************************************************************************/
//FUNCTION:
osg::Vec4d BaseDraw::getPointsColor(double valSpeed, double vMinSpeed, double vMaxSpeed)
{
	// 速度的跨度：颜色需要分成多少份
	double spanSpeed = (vMaxSpeed - vMinSpeed);
	// 一份速度能够占有的颜色比率
	// 颜色范围：255-0-255
	// 比如，颜色可以分成 511份，那么一份速度能够分得的颜色比率为 511/spanSpeed
	double speedRate = (255 + 255) / spanSpeed;

	// 当前速度比最小速度 偏移的颜色数量
	double subtract = (valSpeed - vMinSpeed) * speedRate;

	// BLUE
	double blueVal;
	// 蓝色分量 subtract：[0, 255)
	if (subtract < 255)
	{
		// 蓝色分量：[1，0)
		blueVal = (255 - subtract) / 255;
	}
	else
	{
		// 蓝色分量
		blueVal = 0;
	}
	// GREEN
	double greenVal;
	// 绿色分量 subtract：[0, 255)
	if (subtract < 255)
	{
		// 绿色分量：[0，1)
		greenVal = subtract / 255;
	}
	else if (subtract < 510)
	{
		// 绿色分量：[1，0)
		greenVal = (510 - subtract) / 255;
	}
	else
	{
		greenVal = 0;
	}

	// RED
	double redVal;
	// 红色分量 subtract：[0, 255)
	if (subtract < 255)
	{
		redVal = 0;
	}
	else if (subtract < 510)
	{
		// 红色分量：[0，1)
		redVal = (subtract - 255) / 255;
	}
	else
	{
		// subtract：510
		redVal = 1;
	}

	if (m_pointColorVec.size() > 0)
	{
		if (valSpeed < (m_minValue-0.5) || valSpeed > (m_maxValue+0.5))
		{
			return osg::Vec4d(1,1,1,1.0);
		}

		unsigned int colorSize = m_pointColorVec.size();
		//unsigned int colorIndex = floor((valSpeed - m_minValue - vMinSpeed)*colorSize / spanSpeed);
		unsigned int colorIndex = ( (colorSize/(m_maxValue- m_minValue)) * (valSpeed- m_minValue) );
		if (colorIndex >= colorSize)
			colorIndex = colorSize - 1;

		redVal = m_pointColorVec[colorIndex].red() / 255.0;
		greenVal = m_pointColorVec[colorIndex].green() / 255.0;
		blueVal = m_pointColorVec[colorIndex].blue() / 255.0;

		return osg::Vec4d(redVal, greenVal, blueVal, 1.0);
	}
	else
	{
		// 根据计算出的RGB分量生成颜色对象
		// 返回点的颜色对象
		return osg::Vec4d(redVal, greenVal, blueVal, 1.0);
	}
}

void BaseDraw::changePointColor(std::vector<QColor>& vPointColorVec, float minValue, float maxValue)
{
	m_pointColorVec.clear();
	std::vector<QColor>().swap(m_pointColorVec);
	for (unsigned int i = 0; i < vPointColorVec.size(); i++)
	{
		m_pointColorVec.push_back(vPointColorVec[i]);
	}

	m_maxValue = maxValue;
	m_minValue = minValue;
}

//绘制所有顶点信息
osg::Geode* BaseDraw::drawPoints(osg::Vec4dArray* vPointArray, int pointSize, float minSpeed, float maxSpeed)
{
	if (NULL == vPointArray || vPointArray->size() < 3)
		return NULL;

	//绘制异常体所有顶点
	osg::ref_ptr<osg::Vec4dArray> allPointsColor = new osg::Vec4dArray; //保存异常体所有顶点颜色值
	for (int m = 0; m < vPointArray->size(); m++)
	{
		osg::Vec4d color = getPointsColor((*vPointArray)[m].w(), minSpeed, maxSpeed);
		allPointsColor->push_back(color);
	}

	osg::ref_ptr<osg::Vec4dArray> pointFaceArray = new osg::Vec4dArray;
	//绘制每个面
	for (int j = 0; j < vPointArray->size(); j++)
	{
		pointFaceArray->push_back(osg::Vec4d((*vPointArray)[j].x(), (*vPointArray)[j].y(), (*vPointArray)[j].z(), 1.0));
	}

	//创建几何体
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
	geometry->setVertexArray(pointFaceArray.get());
	geometry->setColorArray(allPointsColor);
	geometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	osg::Vec3dArray *normals = new osg::Vec3dArray;
	normals->push_back(osg::Vec3d(1.0f, 1.0f, 0.0f));
	geometry->setNormalArray(normals);
	geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);
	geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, vPointArray->size())); //设置关联方式
																									   //添加到叶节点
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	//set the point size
	osg::ref_ptr <osg::Point> ptSize = new osg::Point;
	ptSize->setSize(2);
	geode->getOrCreateStateSet()->setAttributeAndModes(ptSize.get(), osg::StateAttribute::ON);
	geode->addDrawable(geometry.get());
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	return geode.release();
}

ViewerWidget3d::ViewerWidget3d(QWidget* parent) :QWidget(parent)
{
	setParent(parent);

	osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
	//声明一个嵌入窗口的变量，只要是有窗口必须使用此对象进行设置
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->windowDecoration = false;//是否显示窗口的描述，默认为false不显示 
	traits->x = 0;//设置显示的x坐标
	traits->y = 0;//设置显示的y坐标
	traits->width = this->width();//设置窗口的宽度
	traits->height = this->height();//设置窗口的高度
	traits->doubleBuffer = true;//创建新的图形窗口是否使用双缓冲特性 
	m_pCamera = new osg::Camera;
	//任意图形子系统的抽象层接口，它提供了统一的图形设备操作函数，用来实现渲染结果和底层设备的交互
	m_pCamera->setGraphicsContext(new osgQt::GraphicsWindowQt(traits.get()));
	//设置渲染器清除色
	m_pCamera->setClearColor(osg::Vec4(0.51, 0.588, 0.667, 0.5));
	//图形输出设置当前视口
	m_pCamera->setViewport(0, 0, traits->width, traits->height);
	//标识摄像机在世界坐标系下的位置
	m_pCamera->setProjectionMatrixAsPerspective(
		30.0f, static_cast<double>(traits->width) /
		static_cast<double>(traits->height), 0.0001f, 100000.0f);
	m_pCamera->setViewMatrix(osg::Matrix::identity());
	//清除深度缓存
	m_pCamera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//设置相机的渲染顺序，在主场景之前（PRE_RENDER）还是之后（POST_RENDER）。
	m_pCamera->setRenderOrder(osg::Camera::POST_RENDER);
	m_pCamera->setAllowEventFocus(false);
	m_pCamera->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);

	m_pViewer = new osgViewer::Viewer;
	m_pViewer->setCamera(m_pCamera.get());   //将相机添加到渲染器中
    //以下是创建了渲染器的一些操作
	osg::ref_ptr<osgGA::TrackballManipulator> pTrackMani = new osgGA::TrackballManipulator;
	pTrackMani->setAutoComputeHomePosition(true);
	m_pViewer->setCameraManipulator(pTrackMani.get());
	m_pViewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);//创建为单线程    

	//窗口大小变化事件
	m_pViewer->addEventHandler(new osgViewer::WindowSizeHandler);
	//添加一些常用状态设置
	m_pViewer->addEventHandler(new osgViewer::StatsHandler);
	m_pViewer->addEventHandler(new osgGA::StateSetManipulator(m_pViewer->getCamera()->getOrCreateStateSet()));
	m_pViewer->setKeyEventSetsDone(0);
	connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
	_timer.start(40);//关联定时器计满信号和响应的槽函数m_pBoxLayout = NULL;
	m_pickHandlerEvent = new PickHandler;
	m_pViewer->addEventHandler(m_pickHandlerEvent);
	QObject::connect(m_pickHandlerEvent, SIGNAL(doubleClicked()), this, SLOT(onActionShowMax()));

	m_SceneGroup = new osg::Group;
	m_SceneGroup->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);//开启深度测试
	
	setVBox();

	//onActionOpenFile();
	
	m_step = 2;
}

void ViewerWidget3d::setVBox()
{
	osgQt::GraphicsWindowQt* gw = dynamic_cast<osgQt::GraphicsWindowQt*>(m_pCamera->getGraphicsContext());
	if (gw)
	{
		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->addWidget(gw->getGLWidget());
		layout->setMargin(1);
		setLayout(layout);
	}
}

void ViewerWidget3d::paintEvent(QPaintEvent* event)
{
	m_pCamera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(this->width()) /
		static_cast<double>(this->height()), 0.0001f, 100000.0f);
	
	m_pViewer->frame();//实时进行渲染
	//QWidget::paintEvent(event);
}

/*************************************************************************************************************************************************************************************/
//function: draw the axis cone
osg::ref_ptr<osg::ShapeDrawable> ViewerWidget3d::drawAxisCone(float xPos, float yPos, float zPos,
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
void ViewerWidget3d::drawBoundLineBox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
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
	m_SceneGroup->addChild(geode.get());
}

/****************************************************************************************************************************************************************************************/
//绘制探测数据的坐标轴数据标尺
void ViewerWidget3d::drawTextFlag(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
{
	//创建保存几何信息的对象
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	//创建四个顶点
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	unsigned int tapTextCount = 0;
	int tap = 5;//暂定5个刻度为一个距离
	float lineLen = 2;
	float textSize = 2;
	char buf[64];

	//绘制z轴刻度及显示值
	tapTextCount = (zMax - zMin)/tap;
	for (unsigned int i = 0; i <= tapTextCount; i++)
	{
		v->push_back(osg::Vec3(xMin, yMin, zMin + i*tap));
		v->push_back(osg::Vec3(xMin, yMin - lineLen, zMin + i*tap));
		itoa(i * tap + zMin, buf, 10);
		osg::ref_ptr<osgText::Text> pTextZAuxis = new osgText::Text;
		pTextZAuxis->setText(buf);
		pTextZAuxis->setColor(osg::Vec4(0, 0, 0, 1.0));

		pTextZAuxis->setAxisAlignment(osgText::Text::SCREEN);
		pTextZAuxis->setCharacterSize(textSize);
		pTextZAuxis->setPosition(osg::Vec3(xMin, yMin - lineLen - textSize, zMin + i*tap));
		geode->addDrawable(pTextZAuxis.get());
	}

	//绘制x轴刻度及显示值
	tapTextCount = (xMax - xMin) / tap;
	for (unsigned int i = 0; i <= tapTextCount; i++)
	{
		v->push_back(osg::Vec3(xMin + i*tap, yMin, zMin));
		v->push_back(osg::Vec3(xMin + i*tap, yMin - lineLen, zMin));

		itoa(i * tap + xMin, buf, 10);
		osg::ref_ptr<osgText::Text> pTextXAuxis = new osgText::Text;
		pTextXAuxis->setText(buf);
		pTextXAuxis->setColor(osg::Vec4(0, 0, 0, 1.0));

		pTextXAuxis->setAxisAlignment(osgText::Text::SCREEN);
		pTextXAuxis->setCharacterSize(textSize);
		pTextXAuxis->setPosition(osg::Vec3(xMin + i*tap, yMin - lineLen - textSize, zMin));
		geode->addDrawable(pTextXAuxis.get());
	}

	//绘制y轴刻度及显示值
	tapTextCount = (yMax - yMin) / tap;
	for (unsigned int i = 0; i <= tapTextCount; i++)
	{
		v->push_back(osg::Vec3(xMin, yMin + i*tap, zMin));
		v->push_back(osg::Vec3(xMin - lineLen, yMin + i*tap, zMin));
		itoa(i * tap + yMin, buf, 10);
		osg::ref_ptr<osgText::Text> pTextYAuxis = new osgText::Text;
		pTextYAuxis->setText(buf);
		pTextYAuxis->setColor(osg::Vec4(0, 0, 0, 1.0));

		pTextYAuxis->setAxisAlignment(osgText::Text::SCREEN);
		pTextYAuxis->setCharacterSize(textSize);
		pTextYAuxis->setPosition(osg::Vec3(xMin - lineLen - textSize, yMin + i*tap, zMin));
		geode->addDrawable(pTextYAuxis.get());
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
	m_SceneGroup->addChild(geode.get());
}

/******************************************************************************/
//function:
void ViewerWidget3d::drawXAxis(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax,float vTap)
{
	//几何模型的基类，用来描述一个三维模型的所有必要数据
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	//线条颜色是棕色
	osg::ref_ptr<osg::Vec4dArray> colorArray = new osg::Vec4dArray;
	float colorValue = 0.4;
	colorArray->push_back(osg::Vec4d(colorValue, colorValue, colorValue, 1.0));

	yMax += vTap;
	zMax += vTap;
	xMax += vTap;
	bool isOddNumber;
	if (int(zMax- zMin) %2 != 0)
	{
		isOddNumber = true;
	}
	else
	{
		isOddNumber = false;
	}
	//用来保存模型中所有顶点位置的数组
	osg::ref_ptr<osg::Vec3dArray> pPointArray = new osg::Vec3dArray;
	int stepYLength = (int)((yMax - yMin) / m_step);
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	for (int i = 0; i <= stepYLength; i++)
	{
		if (!isOddNumber)
		{
			pPointArray->push_back(osg::Vec3d(xMin, yMin + i*m_step, zMin));
			pPointArray->push_back(osg::Vec3d(xMin, yMin + i*m_step, zMax));
		}
		else
		{
			pPointArray->push_back(osg::Vec3d(xMin, yMin + i*m_step, zMin));
			pPointArray->push_back(osg::Vec3d(xMin, yMin + i*m_step, zMax - 1));
		}	

		float tap = 0.5;
		osg::Vec3 textPos = osg::Vec3(xMax, yMin + i*m_step, zMin);
		osgText::Text* text = new osgText::Text;
		text->setCharacterSize(0.7);
		text->setAxisAlignment(osgText::Text::SCREEN);
		text->setPosition(textPos);

		char buf[20];
		text->setColor(osg::Vec4f(1.0, 0.0, 0.0, 1.0));
		int content = (int)yMin + i*m_step;
		sprintf(buf, "%d\0", content+1);
		text->setText(buf);
		geode->addDrawable(text);
	}
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
	m_SceneGroup->addChild(geode.get());
	
	if (int(yMax - yMin) % 2 != 0)
	{
		isOddNumber = true;
	}
	else
	{
		isOddNumber = false;
	}

	int stepZLength = (int)((zMax - zMin) / m_step);
	for (int i = 0; i <= stepZLength; i++)
	{
		if (!isOddNumber)
		{
			pPointArray->push_back(osg::Vec3d(xMin, yMin, zMin + i*m_step));
			pPointArray->push_back(osg::Vec3d(xMin, yMax, zMin + i*m_step));
		}
		else
		{
			pPointArray->push_back(osg::Vec3d(xMin, yMin, zMin + i*m_step));
			pPointArray->push_back(osg::Vec3d(xMin, yMax - 1, zMin + i*m_step));
		}	
	}

	osg::ref_ptr<osg::Geode> axisGeode = new osg::Geode;
	geom->setVertexArray(pPointArray.get());
	geom->setColorArray(colorArray);
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);
	geom->addPrimitiveSet(new osg::DrawArrays(GL_LINES, 0, pPointArray->size()));
	axisGeode->addDrawable(geom.get());
	axisGeode->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
	axisGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);

	{
		osg::Vec3 textPos = osg::Vec3(xMax + 3, yMin + (stepYLength / 2)*m_step, zMin);
		osg::ref_ptr<osgText::Text> pTextYAuxis = new osgText::Text;
		pTextYAuxis->setText(L"y/m");
		pTextYAuxis->setFont("Fonts/simhei.ttf");
		pTextYAuxis->setAxisAlignment(osgText::Text::SCREEN);
		pTextYAuxis->setCharacterSize(1);
		pTextYAuxis->setPosition(textPos);
		pTextYAuxis->setColor(osg::Vec4(1, 0, 0, 1.0));
		axisGeode->addDrawable(pTextYAuxis.get());
	}

	m_SceneGroup->addChild(axisGeode.get());
}
/******************************************************************************/
//function:
void ViewerWidget3d::drawYAxis(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, float vTap)
{
	//几何模型的基类，用来描述一个三维模型的所有必要数据
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	//线条颜色是棕色
	osg::ref_ptr<osg::Vec4dArray> colorArray = new osg::Vec4dArray;
	float colorValue = 0.4;
	colorArray->push_back(osg::Vec4d(colorValue, colorValue, colorValue, 1.0));
	
	yMax += vTap;
	zMax += vTap;
	xMax += vTap;

	bool isOddNumber;
	if (int(zMax - zMin) % 2 != 0)
	{
		isOddNumber = true;
	}
	else
	{
		isOddNumber = false;
	}

	//用来保存模型中所有顶点位置的数组
	osg::ref_ptr<osg::Vec3dArray> pPointArray = new osg::Vec3dArray;
	int stepXLength = (int)((xMax - xMin) / m_step);
	for (int i = 0; i <= stepXLength; i++)
	{
		if (!isOddNumber)
		{
			pPointArray->push_back(osg::Vec3d(xMin + i*m_step, yMin, zMin));
			pPointArray->push_back(osg::Vec3d(xMin + i*m_step, yMin, zMax));
		}
		else
		{
			pPointArray->push_back(osg::Vec3d(xMin + i*m_step, yMin, zMin));
			pPointArray->push_back(osg::Vec3d(xMin + i*m_step, yMin, zMax - 1));
		}
	}

	if (int(xMax - xMin) % 2 != 0)
	{
		isOddNumber = true;
	}
	else
	{
		isOddNumber = false;
	}

	int stepZLength = (int)((zMax - zMin) / m_step);
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	for (int i = 0; i <= stepZLength; i++)
	{
		if (!isOddNumber)
		{
			pPointArray->push_back(osg::Vec3d(xMin, yMin, zMin + i*m_step));
			pPointArray->push_back(osg::Vec3d(xMax, yMin, zMin + i*m_step));
		}
		else
		{
			pPointArray->push_back(osg::Vec3d(xMin, yMin, zMin + i*m_step));
			pPointArray->push_back(osg::Vec3d(xMax - 1, yMin, zMin + i*m_step));
		}	

		float tap = 0.5;
		osg::Vec3 textPos = osg::Vec3(xMin - 2 * tap, yMax, zMin + i*m_step);
		osgText::Text* text = new osgText::Text;
		text->setCharacterSize(0.7);
		text->setAxisAlignment(osgText::Text::SCREEN);
		text->setPosition(textPos);

		char buf[64];
		text->setColor(osg::Vec4f(1.0, 0.0, 0.0, 1.0));
		int mValue = GlobalParam::instance()->getObservationSystemSetting().mileage_left;
		int content = (int)mValue + i*m_step*2;
		if (i == 0)
		{
			int kValue = GlobalParam::instance()->getObservationSystemSetting().mileage_right;
			sprintf(buf, "k%d+%dm\0", mValue, kValue);
		}
		else
			sprintf(buf, "%d\0", content + 1);
		text->setText(buf);
		geode->addDrawable(text);
	}
	geode->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
	m_SceneGroup->addChild(geode.get());
	osg::ref_ptr<osg::Geode> axisGeode = new osg::Geode;
	geom->setVertexArray(pPointArray.get());
	geom->setColorArray(colorArray);
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);

	geom->addPrimitiveSet(new osg::DrawArrays(GL_LINES, 0, pPointArray->size()));
	axisGeode->addDrawable(geom.get());
	axisGeode->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
	axisGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);

	{
		osg::Vec3 textPos = osg::Vec3(xMin, yMax + 3, zMin + (stepZLength / 2)*m_step);
		osg::ref_ptr<osgText::Text> pTextZAuxis = new osgText::Text;
		pTextZAuxis->setText(L"z/m");
		pTextZAuxis->setFont("Fonts/simhei.ttf");
		pTextZAuxis->setAxisAlignment(osgText::Text::SCREEN);
		pTextZAuxis->setCharacterSize(1);
		pTextZAuxis->setPosition(textPos);
		pTextZAuxis->setColor(osg::Vec4(1, 0, 0, 1.0));
		axisGeode->addDrawable(pTextZAuxis.get());
	}

	m_SceneGroup->addChild(axisGeode.get());
}

/******************************************************************************/
//function:
void ViewerWidget3d::drawZAxis(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, float vTap)
{
	//几何模型的基类，用来描述一个三维模型的所有必要数据
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	//线条颜色是棕色
	osg::ref_ptr<osg::Vec4dArray> colorArray = new osg::Vec4dArray;
	float colorValue = 0.4;
	colorArray->push_back(osg::Vec4d(colorValue, colorValue, colorValue, 1.0));
	yMax += vTap;
	zMax += vTap;
	xMax += vTap;

	bool isOddNumber;
	if (int(yMax - yMin) % 2 != 0)
	{
		isOddNumber = true;
	}
	else
	{
		isOddNumber = false;
	}

	//用来保存模型中所有顶点位置的数组
	osg::ref_ptr<osg::Vec3dArray> pPointArray = new osg::Vec3dArray;
	int stepXLength = (int)((xMax - xMin) / m_step);
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	for (int i = 0; i <= stepXLength; i++)
	{
		if (!isOddNumber)
		{
			pPointArray->push_back(osg::Vec3d(xMin + i*m_step, yMin, zMin));
			pPointArray->push_back(osg::Vec3d(xMin + i*m_step, yMax, zMin));
		}
		else
		{
			pPointArray->push_back(osg::Vec3d(xMin + i*m_step, yMin, zMin));
			pPointArray->push_back(osg::Vec3d(xMin + i*m_step, yMax - 1, zMin));
		}	

		float tap = 0.5;
		osg::Vec3 textPos = osg::Vec3(xMin + i*m_step, yMin, zMax + tap);
		osgText::Text* text = new osgText::Text;
		text->setCharacterSize(0.7);
		text->setAxisAlignment(osgText::Text::SCREEN);
		text->setPosition(textPos);

		char buf[20];
		text->setColor(osg::Vec4f(1.0, 0.0, 0.0, 1.0));
		int content = (int)xMin + i*m_step;
		sprintf(buf, "%d\0", content+1);
		text->setText(buf);
		geode->addDrawable(text);
	}
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
	m_SceneGroup->addChild(geode.get());

	if (int(xMax - xMin) % 2 != 0)
	{
		isOddNumber = true;
	}
	else
	{
		isOddNumber = false;
	}

	int stepYLength = (int)((yMax - yMin) / m_step);
	for (int i = 0; i <= stepYLength; i++)
	{
		if (!isOddNumber)
		{
			pPointArray->push_back(osg::Vec3d(xMin, yMin + i*m_step, zMin));
			pPointArray->push_back(osg::Vec3d(xMax, yMin + i*m_step, zMin));
		}
		else
		{
			pPointArray->push_back(osg::Vec3d(xMin, yMin + i*m_step, zMin));
			pPointArray->push_back(osg::Vec3d(xMax - 1, yMin + i*m_step, zMin));
		}		
	}

	osg::ref_ptr<osg::Geode> axisGeode = new osg::Geode;
	geom->setVertexArray(pPointArray.get());
	geom->setColorArray(colorArray);
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);
	geom->addPrimitiveSet(new osg::DrawArrays(GL_LINES, 0, pPointArray->size()));
	axisGeode->addDrawable(geom.get());
	axisGeode->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
	axisGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);

	{
		osg::Vec3 textPos = osg::Vec3(xMin + (stepXLength / 2)*m_step, yMin, zMax + 3);
		osg::ref_ptr<osgText::Text> pTextXAuxis = new osgText::Text;
		pTextXAuxis->setText(L"x/m");
		pTextXAuxis->setFont("Fonts/simhei.ttf");
		pTextXAuxis->setAxisAlignment(osgText::Text::SCREEN);
		pTextXAuxis->setCharacterSize(1);
		pTextXAuxis->setPosition(textPos);
		pTextXAuxis->setColor(osg::Vec4(1, 0, 0, 1.0));
		axisGeode->addDrawable(pTextXAuxis.get());
	}

	m_SceneGroup->addChild(axisGeode.get());
}

/****************************************************************************************************************************************************************************************/
//绘制探测数据的坐标轴
void ViewerWidget3d::makeCoordinate(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax,float vTap, bool drawXYZ)
{
	osg::Quat yQuat;
	yQuat.makeRotate(-osg::PI_2, osg::X_AXIS);
	osg::Quat xQuat;
	xQuat.makeRotate(osg::PI_2, osg::Y_AXIS);
	osg::Quat zQuat;
	zQuat.makeRotate(-osg::PI_2, osg::Z_AXIS);

	osg::ref_ptr<osg::ShapeDrawable> pShapeDrawY = drawAxisCone(xMin, yMax + vTap, zMin, yQuat, osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f), 0.4, 1.0);
	osg::ref_ptr<osg::ShapeDrawable> pShapeDrawX = drawAxisCone(xMax + vTap, yMin, zMin, xQuat, osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f), 0.4, 1.0);
	osg::ref_ptr<osg::ShapeDrawable> pShapeDrawZ = drawAxisCone(xMin, yMin, zMax + vTap, zQuat, osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f), 0.4, 1.0);

	//创建保存几何信息的对象
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	//创建四个顶点
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	v->push_back(osg::Vec3(xMin, yMin, zMin));
	v->push_back(osg::Vec3(xMax + vTap, yMin, zMin));
	v->push_back(osg::Vec3(xMin, yMin, zMin));
	v->push_back(osg::Vec3(xMin, yMax + vTap, zMin));
	v->push_back(osg::Vec3(xMin, yMin, zMin));
	v->push_back(osg::Vec3(xMin, yMin, zMax + vTap));
	geom->setVertexArray(v.get());

	//为每个顶点指定一种颜色
	float colorValue = 0.9;
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();
	c->push_back(osg::Vec4(colorValue, 0, 0, 1.0f)); //坐标原点为红色
	c->push_back(osg::Vec4(colorValue, 0, 0, 1.0f)); //x red
	c->push_back(osg::Vec4(colorValue, 0, 0, 1.0f)); //坐标原点为绿色
	c->push_back(osg::Vec4(colorValue, 0, 0, 1.0f)); //y green
	c->push_back(osg::Vec4(colorValue, 0, 0, 1.0f)); //坐标原点为蓝色
	c->push_back(osg::Vec4(colorValue, 0, 0, 1.0f)); //z blue
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
	pTextXAuxis->setPosition(osg::Vec3(xMax + vTap, yMin, zMin));
	pTextXAuxis->setColor(osg::Vec4(0, 0, 0, 1.0));

	osg::ref_ptr<osgText::Text> pTextYAuxis = new osgText::Text;
	pTextYAuxis->setText(L"Y轴");
	pTextYAuxis->setFont("Fonts/simhei.ttf");
	pTextYAuxis->setAxisAlignment(osgText::Text::SCREEN);
	pTextYAuxis->setCharacterSize(textSize);
	pTextYAuxis->setColor(osg::Vec4(0, 0, 0, 1.0));
	pTextYAuxis->setPosition(osg::Vec3(xMin, yMax + vTap, zMin));
	osg::ref_ptr<osgText::Text> pTextZAuxis = new osgText::Text;
	pTextZAuxis->setText(L"Z轴");
	pTextZAuxis->setFont("Fonts/simhei.ttf");
	pTextZAuxis->setAxisAlignment(osgText::Text::SCREEN);
	pTextZAuxis->setCharacterSize(textSize);
	pTextZAuxis->setPosition(osg::Vec3(xMin, yMin, zMax + vTap));
	pTextZAuxis->setColor(osg::Vec4(0, 0, 0, 1.0));

	//三个轴
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, v->size())); //X	
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	geode->getOrCreateStateSet()->setAttribute(new osg::LineWidth(1.5), osg::StateAttribute::ON);
	geode->addDrawable(geom.get());
	if (drawXYZ)
	{
		geode->addDrawable(pTextXAuxis.get());
		geode->addDrawable(pTextYAuxis.get());
		geode->addDrawable(pTextZAuxis.get());
	}
	
	m_SceneGroup->addChild(geode.get());
	m_pViewer->setSceneData(m_SceneGroup); //将模型添加到渲染器中
}

void ViewerWidget3d::onActionShowMax()
{
	//m_dialogDisplayImage->showMaximized();
	emit showMax(this->objectName(), m_osgFilePath);
}