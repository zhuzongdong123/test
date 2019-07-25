//创建二维维可视化的基类
#pragma once
#include "QtWidgets/QApplication"
#include "osg/Camera"
#include "osg/Group"
#include "osg/ShapeDrawable"
#include "osgWidget/WindowManager"
#include "osgGA/TrackballManipulator"
#include "WalkManipulator.h"
#include "QtWidgets/QVBoxLayout"
#include "QtWidgets/QWidget"
#include "detectIrresurface/shading.h"
#include <QtWidgets/QLabel>
#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/Viewer>
#include <osgQt/GraphicsWindowQt>
#include <QtCore/QTimer>
#include <QGLWidget>
#include <osgGA/StateSetManipulator>
#include "pickHandler.h"

class axisBaseDraw : public QWidget
{
public:

	enum AxisDir{xdir, ydir, zdir};

	axisBaseDraw(QWidget* parent = nullptr) : QWidget(parent) { setParent(parent); }
	~axisBaseDraw() {}

	osg::ref_ptr<osg::ShapeDrawable> drawAxisCone(float xPos, float yPos, float zPos, osg::Quat vQuat, osg::Vec4& vColor, float coneRadius, float coneHeight);
	osg::ref_ptr<osg::Geode> makeCoordinate(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);//生成数据的坐标轴
	osg::ref_ptr<osg::Geode> drawBoundLineBox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);//生成包围盒
	osg::ref_ptr<osg::Geode> drawTextFlag(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);//绘制坐标轴刻度尺
private:

};

//class ViewerWidget : public QGLWidget, public osgViewer::Viewer
class ViewerWidget :public QWidget
{
	Q_OBJECT

public:
	
	ViewerWidget(QWidget *parent = nullptr)	
		:QWidget(parent)
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
		m_pViewer->setCameraManipulator(new osgGA::TrackballManipulator);
		m_pViewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);//创建为单线程    

	    //窗口大小变化事件
		m_pViewer->addEventHandler(new osgViewer::WindowSizeHandler);
		//添加一些常用状态设置
		m_pViewer->addEventHandler(new osgViewer::StatsHandler);
		
		m_pickHandlerEvent = new PickHandler;
		m_pViewer->addEventHandler(m_pickHandlerEvent);
		m_pViewer->addEventHandler(new osgGA::StateSetManipulator(m_pViewer->getCamera()->getOrCreateStateSet()));

		connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
		_timer.start(40);//关联定时器计满信号和响应的槽函数m_pBoxLayout = NULL;

		m_SceneGroup = new osg::Group;
		m_SceneGroup->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);//开启深度测试

		setVBox();

		creatHideLabel();
	}

	virtual ~ViewerWidget() 
	{
		if (NULL != m_layout)
			delete m_layout;
		m_layout = NULL;
		
	}

	virtual void resizeEvent(QResizeEvent *e) 
	{	
		QWidget::resizeEvent(e); 
		m_hideLabel->setGeometry(QRect(0, 0, 1, this->height()));

		if (NULL == getOrthoCamera())	return;

		osg::Viewport* viewPort = m_pViewer->getCamera()->getViewport();
		float width = viewPort->width();
		float height = viewPort->height();
		float thisWidth = this->width();
		float thisHeight = this->height();

		double radio_x = thisWidth / width;
		double radio_y = thisHeight / height;
		m_pViewer->getCamera()->setViewport(0, 0, this->width(), this->height());
		m_pViewer->getCamera()->setProjectionMatrix(osg::Matrix::scale(radio_x, radio_y, 1));
		m_orthoCamera->setViewport(0, 0, this->width(), this->height());
	}
	
	void setVBox()
	{
		osgQt::GraphicsWindowQt* gw = dynamic_cast<osgQt::GraphicsWindowQt*>(m_pViewer->getCamera()->getGraphicsContext());
		if (gw)
		{
			m_layout = new QVBoxLayout(this);
			m_layout->setContentsMargins(1, 0, 0, 0);
			m_layout->addWidget(gw->getGLWidget());
		}
	}

	
	void createOrthoCamera(unsigned int width, unsigned int height);
		
	osg::ref_ptr<osg::Camera> getOrthoCamera() { return m_orthoCamera.get(); }
	
	void changeCameraToOrtho2D()
	{
		m_pViewer->realize();
		m_pViewer->getCamera()->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_pViewer->getCamera()->setClearColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
		int a = this->width();
		int b = this->height();
		m_pViewer->getCamera()->setViewport(0, 0, this->width(), this->height());
		m_pViewer->getCamera()->setProjectionMatrix(osg::Matrix::ortho2D(0.0, this->width(), 0.0, this->height()));
	}

	osg::ref_ptr<osgViewer::Viewer> getMyViewer() { return m_pViewer.get(); }
	osg::ref_ptr<osg::Group> getSceneRoot() { return m_SceneGroup.get(); }

	void creatHideLabel();
	
	PickHandler* getPickHandle() { return m_pickHandlerEvent; }
public slots:
	

protected:
	virtual void paintEvent(QPaintEvent* event);

	osg::ref_ptr<osg::Camera> m_orthoCamera;
	osg::ref_ptr<osgViewer::Viewer> m_pViewer;//创建一个渲染器
	osg::ref_ptr<osg::Group> m_SceneGroup;
	
	QTimer _timer;//创建一个定时器
	QVBoxLayout* m_layout;
	osg::ref_ptr<PickHandler> m_pickHandlerEvent;

private:
	QLabel *m_hideLabel;
	osg::ref_ptr<osg::Camera> m_pCamera;
public:
};