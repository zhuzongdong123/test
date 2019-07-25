//������άά���ӻ��Ļ���
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
	osg::ref_ptr<osg::Geode> makeCoordinate(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);//�������ݵ�������
	osg::ref_ptr<osg::Geode> drawBoundLineBox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);//���ɰ�Χ��
	osg::ref_ptr<osg::Geode> drawTextFlag(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);//����������̶ȳ�
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
		//����һ��Ƕ�봰�ڵı�����ֻҪ���д��ڱ���ʹ�ô˶����������
		osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
		traits->windowDecoration = false;//�Ƿ���ʾ���ڵ�������Ĭ��Ϊfalse����ʾ 
		traits->x = 0;//������ʾ��x����
		traits->y = 0;//������ʾ��y����
		traits->width = this->width();//���ô��ڵĿ��
		traits->height = this->height();//���ô��ڵĸ߶�
		traits->doubleBuffer = true;//�����µ�ͼ�δ����Ƿ�ʹ��˫�������� 
		m_pCamera = new osg::Camera;
		//����ͼ����ϵͳ�ĳ����ӿڣ����ṩ��ͳһ��ͼ���豸��������������ʵ����Ⱦ����͵ײ��豸�Ľ���
		m_pCamera->setGraphicsContext(new osgQt::GraphicsWindowQt(traits.get()));
		//������Ⱦ�����ɫ
		m_pCamera->setClearColor(osg::Vec4(0.51, 0.588, 0.667, 0.5));
		//ͼ��������õ�ǰ�ӿ�
		m_pCamera->setViewport(0, 0, traits->width, traits->height);
		//��ʶ���������������ϵ�µ�λ��
		m_pCamera->setProjectionMatrixAsPerspective(
			30.0f, static_cast<double>(traits->width) /
			static_cast<double>(traits->height), 0.0001f, 100000.0f);
		m_pCamera->setViewMatrix(osg::Matrix::identity());
		//�����Ȼ���
		m_pCamera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//�����������Ⱦ˳����������֮ǰ��PRE_RENDER������֮��POST_RENDER����
		m_pCamera->setRenderOrder(osg::Camera::POST_RENDER);
		m_pCamera->setAllowEventFocus(false);
		m_pCamera->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);

		m_pViewer = new osgViewer::Viewer;
		m_pViewer->setCamera(m_pCamera.get());   //�������ӵ���Ⱦ����
		//�����Ǵ�������Ⱦ����һЩ����
		m_pViewer->setCameraManipulator(new osgGA::TrackballManipulator);
		m_pViewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);//����Ϊ���߳�    

	    //���ڴ�С�仯�¼�
		m_pViewer->addEventHandler(new osgViewer::WindowSizeHandler);
		//���һЩ����״̬����
		m_pViewer->addEventHandler(new osgViewer::StatsHandler);
		
		m_pickHandlerEvent = new PickHandler;
		m_pViewer->addEventHandler(m_pickHandlerEvent);
		m_pViewer->addEventHandler(new osgGA::StateSetManipulator(m_pViewer->getCamera()->getOrCreateStateSet()));

		connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
		_timer.start(40);//������ʱ�������źź���Ӧ�Ĳۺ���m_pBoxLayout = NULL;

		m_SceneGroup = new osg::Group;
		m_SceneGroup->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);//������Ȳ���

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
	osg::ref_ptr<osgViewer::Viewer> m_pViewer;//����һ����Ⱦ��
	osg::ref_ptr<osg::Group> m_SceneGroup;
	
	QTimer _timer;//����һ����ʱ��
	QVBoxLayout* m_layout;
	osg::ref_ptr<PickHandler> m_pickHandlerEvent;

private:
	QLabel *m_hideLabel;
	osg::ref_ptr<osg::Camera> m_pCamera;
public:
};