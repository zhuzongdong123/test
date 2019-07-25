#pragma once
//三维成像
#include "3ddisplay/ViewerWidget3d.h"
#include "3ddisplay/detectIrresurface/detectIrreSurface.h"
#include "detecImage/imageAnalysis.h"
#include "3ddisplay/detectIrresurface/shading.h"
#include "GlobalClass/GlobalParam.h"

class MyWidgetImaging :public ViewerWidget3d
{
	Q_OBJECT
public:
	MyWidgetImaging(QWidget* parent = nullptr);

	virtual ~MyWidgetImaging();

	/**
	* @brief 初始化场景,建立坐标系
	*/
	virtual void initScene();
	void clearData();

	void createAndSliceImage();
	void createAndSliceIrresurface();
	void resizeEvent(QResizeEvent *e);

	int getXMax() { return m_xMax; }
	int getYMax() { return m_yMax; }
	int getZMax() { return m_zMax; }
	int getXMin() { return m_xMin; }
	int getYMin() { return m_yMin; }
	int getZMin() { return m_zMin; }
	BaseDraw* getBaseDraw() { return m_pBaseDraw; }
	double getMinSpeed() { return m_minSpeed; }
	double getMaxSpeed() { return m_maxSpeed; }
	osg::ref_ptr<osg::Vec4dArray> getPointsArray() { return m_pPointsDataArray; }

	enum TAB_ID
	{
		DATA_VOLUME_VISUALIZATION = 0, //数据体可视化
		SLICE_EXTRACTION, //切片提取
		EQUIVALENT_SURFACE_EXTRACTION, //等值面提取
		DATA_SHOW_ALL	//显示切片，等值面，隧道
	};

	enum SliceDir
	{
		X = 0,
		Y,
		Z
	};

signals:
	void setDisplayRangeValue(QString text);
	void setEquivalentSurfaceValueDown(QString text);
	void setEquivalentSurfaceValueUp(QString text);
	void setWaterVolume(QString text);
	void setPredictionOfWaterVolume(QString text);
	void setSurfaceArea(QString text);
	void setPorosityEditorValue(QString text);
	void changeDisplayWidgetSize();
	void setCheckBox(bool value);
	void changeRange(float minValue,float maxValue);

public slots:
	/**
	* @brief 按钮-开始成像
	*/
	void initPointsToScene(osg::ref_ptr<osg::Vec4dArray> vPointsArray, unsigned int vZLen, unsigned int vYLen, unsigned int vXLen);	//开始成像
	void initPointsToScene(double ***vPoints, unsigned int vZLen, unsigned int vYLen, unsigned int vXLen);	//开始成像
	void initNROPointsToScene(double ***vPoints, int vZBegLen, int vYBegLen, int vXBegLen, int vZEndLen, int vYEndLen, int vXEndLen);
	void changePointsTab(int vTabIndex);
	/**
	*@brief 开始成像，成像展示顶点数据
	*/
	void displayAllPoints();

	/**
	* @brief 按钮-保存数据
	*/
	void saveData();			

	/**
	* @brief 切换标签
	*/
	void changeTabIndex(int index);

	//切片提取tab下的槽事件
	void changeDisplayRangeValue(int displayRangeValue);	//获取[切片提取-显示范围]的值
	void onStateChangedX(int state);						//checkBox-X轴
	void onStateChangedY(int state);						//checkBox-Y轴
	void onStateChangedZ(int state);						//checkBox-Z轴

	void onStateBoundBoxLineX(int state);
	void onStateBoundBoxLineY(int state);
	void onStateBoundBoxLineZ(int state);

	void boundBoxCheckLine();

	//异常体提取tab下的槽事件
	void changeEquivalentSurfaceValueUp(int equivalentSurfaceValue);	//获取上边[等值面]的值
	void changeEquivalentSurfaceValueDown(int equivalentSurfaceValue);	//获取下边[等值面]的值
	
	double getWaterVolume() { return 1.0; };
	void changeEquivalentPointUp(int equivalentSurfaceValue);
	void changeEquivalentPointDown(int equivalentSurfaceValue);

	void initSliceBody();
	void createLegend(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);
	void createLegendDown();

	void removeText();

	void showData();
	void showNROData();
protected:
		void paintEvent(QPaintEvent* event)
		{
			ViewerWidget3d::paintEvent(event);
			GlobalParam::InversionParaSetting& setting = GlobalParam::instance()->getInversionParaSetting();
			if (!setting.showLegend)
				removeText();
		}
private:
	/**
	* @brief 初始化
	*/
	void initialization();
	
private:
	bool m_sliceDrection_x;
	bool m_sliceDrection_y;
	bool m_sliceDrection_z;

	bool m_boundBoxLineX;
	bool m_boundBoxLineY;
	bool m_boundBoxLineZ;

	bool m_isSliceBodyGroup;
	
	unsigned int m_currentTabIndex;

	//切片提取
	int m_displayRangeValue;
	int m_compareRangeValue;

	//等值点提取
	int m_equivalentPointValueUp;
	int m_equivalentPointValueDown;

	QString m_currentPath;

	int m_xMin;//x为掌子面宽度
	int m_yMin;//y为掌子面高度
	int m_zMin;//z为轴向
	int m_xMax;
	int m_yMax;
	int m_zMax;
	int m_sizeX;
	int m_sizeY;
	int m_sizeZ;
	float m_repo;
	double m_minSpeed;
	double m_maxSpeed;
	/********************************************求取含水体体积相关参数Begin*************************************************/
	double m_waterVolume; //水体体积
	/********************************************求取含水体体积相关参数End*************************************************/

	osg::ref_ptr<osg::Vec4dArray> m_pPointsDataArray;
	osg::ref_ptr<osg::Group> m_detectPointsGroup;
	osg::ref_ptr<osg::Group> m_SliceGroup;
	osg::ref_ptr<osg::Group> m_surfaceUpGroup;
	osg::ref_ptr<osg::Group> m_surfaceDownGroup;
	osg::ref_ptr<osg::Group> m_lineFlagGroup;
	osg::ref_ptr<osg::Group> m_waterPointsGroup; //含水体顶点
	osg::ref_ptr<osg::Group> m_sliceBodyGroup; //展示整个体的六个初始切面
	osg::ref_ptr<osg::Geode> m_geode;
	std::set<double> m_xPointValue; //x方向的分布值
	std::set<double> m_yPointValue; //y方向的分布值
	std::set<double> m_zPointValue; //z方向的分布值
	osgEngine::CImageCreate*   m_detectImageDisplay;
	osgEngine::marchingCubeDraw* m_CMarchingCube;
	osg::ref_ptr<osg::Camera> m_orthoCamera;//二维相机
	BaseDraw* m_pBaseDraw;

	osg::ref_ptr<osg::Group> m_textGeodeGroup;

};