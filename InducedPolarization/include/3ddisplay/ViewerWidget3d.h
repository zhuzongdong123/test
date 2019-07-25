//创建三维可视化的基类
#pragma once
#include "QtWidgets/QApplication"
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/Viewer>
#include "osg/Camera"
#include "osg/Group"
#include "osgWidget/WindowManager"
#include <QtCore/QTimer>
#include <QGLWidget>
#include <QtWidgets/QMainWindow>
#include <osgQt/GraphicsWindowQt>
#include "QtWidgets/QVBoxLayout"
#include "QtWidgets/QWidget"
#include "detectData/detectDataDraw.h"
#include "osg/LightModel"
#include <QtCore/QObject>
#include "QProgressBar"
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <3ddisplay/tunnelDraw/tunnelDraw.h>
#include "Timer.h"
#include "pickHandler.h"
#include <QtWidgets/QAction>

class BaseDraw
{
public:
	BaseDraw(){}
	~BaseDraw() {}

	osg::Geode* drawPoints(osg::Vec4dArray* vPointArray, int pointSize, float minSpeed, float maxSpeed);
	osg::Vec4d getPointsColor(double valSpeed, double vMinSpeed, double vMaxSpeed);
	
	//更换标尺颜色值
	void changePointColor(std::vector<QColor>& vPointColorVec, float minValue, float maxValue);

private:
	std::vector<QColor> m_pointColorVec;
	float m_maxValue;
	float m_minValue;
	
};


class ViewerWidget3d : public QWidget
{
	Q_OBJECT
public:
	ViewerWidget3d(QWidget* parent = nullptr);

	virtual ~ViewerWidget3d() {}

	virtual void initScene() {}//初始化场景

	osg::ref_ptr<osg::Group> getSceneGroup() { return m_SceneGroup.get(); }
	osg::ref_ptr<osgViewer::Viewer> getViewer() { return m_pViewer.get(); }
	void makeCoordinate(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, float vTap = 10, bool drawXYZ = true);//生成数据的坐标轴
	PickHandler* getPickHandle() { return m_pickHandlerEvent; }

protected:
	virtual void paintEvent(QPaintEvent* event);

	osg::ref_ptr<osg::ShapeDrawable> drawAxisCone(float xPos, float yPos, float zPos, 
		osg::Quat vQuat, osg::Vec4& vColor, float coneRadius, float coneHeight);
	void drawBoundLineBox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);//生成包围盒
	void drawTextFlag(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);//绘制坐标轴刻度尺

	void drawXAxis(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax,float vTap=10);
	void drawYAxis(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax,float vTap=10);
	void drawZAxis(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax,float vTap=10);
	void drawXYZTitle(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, float vTap = 10);

	osg::ref_ptr<osgViewer::Viewer> m_pViewer;//创建一个渲染器
	osg::ref_ptr<osg::Group> m_SceneGroup;

public slots:
	void addPopMenu();
	void onActionOpenFile();
	void onActionShowMax();

signals:
	void showMax(QString objectName, QString osgFilePath);

private:
	void setVBox();
	void createAction();
	
private:
	osg::ref_ptr<osg::Camera> m_pCamera;
	float m_step;//坐标线的距离间隔步长
	QTimer _timer;//创建一个定时器
	osg::ref_ptr<PickHandler> m_pickHandlerEvent;
	QAction *m_openFile;
	QAction *m_showMax;
	QString m_osgFilePath;
};