#pragma once
//��ά����
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
	* @brief ��ʼ������,��������ϵ
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
		DATA_VOLUME_VISUALIZATION = 0, //��������ӻ�
		SLICE_EXTRACTION, //��Ƭ��ȡ
		EQUIVALENT_SURFACE_EXTRACTION, //��ֵ����ȡ
		DATA_SHOW_ALL	//��ʾ��Ƭ����ֵ�棬���
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
	* @brief ��ť-��ʼ����
	*/
	void initPointsToScene(osg::ref_ptr<osg::Vec4dArray> vPointsArray, unsigned int vZLen, unsigned int vYLen, unsigned int vXLen);	//��ʼ����
	void initPointsToScene(double ***vPoints, unsigned int vZLen, unsigned int vYLen, unsigned int vXLen);	//��ʼ����
	void initNROPointsToScene(double ***vPoints, int vZBegLen, int vYBegLen, int vXBegLen, int vZEndLen, int vYEndLen, int vXEndLen);
	void changePointsTab(int vTabIndex);
	/**
	*@brief ��ʼ���񣬳���չʾ��������
	*/
	void displayAllPoints();

	/**
	* @brief ��ť-��������
	*/
	void saveData();			

	/**
	* @brief �л���ǩ
	*/
	void changeTabIndex(int index);

	//��Ƭ��ȡtab�µĲ��¼�
	void changeDisplayRangeValue(int displayRangeValue);	//��ȡ[��Ƭ��ȡ-��ʾ��Χ]��ֵ
	void onStateChangedX(int state);						//checkBox-X��
	void onStateChangedY(int state);						//checkBox-Y��
	void onStateChangedZ(int state);						//checkBox-Z��

	void onStateBoundBoxLineX(int state);
	void onStateBoundBoxLineY(int state);
	void onStateBoundBoxLineZ(int state);

	void boundBoxCheckLine();

	//�쳣����ȡtab�µĲ��¼�
	void changeEquivalentSurfaceValueUp(int equivalentSurfaceValue);	//��ȡ�ϱ�[��ֵ��]��ֵ
	void changeEquivalentSurfaceValueDown(int equivalentSurfaceValue);	//��ȡ�±�[��ֵ��]��ֵ
	
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
	* @brief ��ʼ��
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

	//��Ƭ��ȡ
	int m_displayRangeValue;
	int m_compareRangeValue;

	//��ֵ����ȡ
	int m_equivalentPointValueUp;
	int m_equivalentPointValueDown;

	QString m_currentPath;

	int m_xMin;//xΪ��������
	int m_yMin;//yΪ������߶�
	int m_zMin;//zΪ����
	int m_xMax;
	int m_yMax;
	int m_zMax;
	int m_sizeX;
	int m_sizeY;
	int m_sizeZ;
	float m_repo;
	double m_minSpeed;
	double m_maxSpeed;
	/********************************************��ȡ��ˮ�������ز���Begin*************************************************/
	double m_waterVolume; //ˮ�����
	/********************************************��ȡ��ˮ�������ز���End*************************************************/

	osg::ref_ptr<osg::Vec4dArray> m_pPointsDataArray;
	osg::ref_ptr<osg::Group> m_detectPointsGroup;
	osg::ref_ptr<osg::Group> m_SliceGroup;
	osg::ref_ptr<osg::Group> m_surfaceUpGroup;
	osg::ref_ptr<osg::Group> m_surfaceDownGroup;
	osg::ref_ptr<osg::Group> m_lineFlagGroup;
	osg::ref_ptr<osg::Group> m_waterPointsGroup; //��ˮ�嶥��
	osg::ref_ptr<osg::Group> m_sliceBodyGroup; //չʾ�������������ʼ����
	osg::ref_ptr<osg::Geode> m_geode;
	std::set<double> m_xPointValue; //x����ķֲ�ֵ
	std::set<double> m_yPointValue; //y����ķֲ�ֵ
	std::set<double> m_zPointValue; //z����ķֲ�ֵ
	osgEngine::CImageCreate*   m_detectImageDisplay;
	osgEngine::marchingCubeDraw* m_CMarchingCube;
	osg::ref_ptr<osg::Camera> m_orthoCamera;//��ά���
	BaseDraw* m_pBaseDraw;

	osg::ref_ptr<osg::Group> m_textGeodeGroup;

};