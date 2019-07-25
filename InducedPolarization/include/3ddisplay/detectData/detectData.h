#pragma once
#include <string>
#include <osg/Array>
#include <fstream>
#include <memory>

//对探测数据的导入和分析(包括数据密度处理)
class detectData
{
public:
	detectData()
	{
		
	}

	~detectData()
	{
		m_pAllDetectPointsArray->clear();
		m_pAllDetectPointsArray = NULL;
	}

	//初始化数据
	void initDetectData(int xMin, int xMax, int yMin, int yMax,
		int zMin, int zMax, float minSpeed, float maxSpeed, osg::ref_ptr<osg::Vec4dArray> vPointArray);

	osg::ref_ptr<osg::Vec4dArray> getDetectPointArray() { return m_pAllDetectPointsArray.get(); }
	osg::Vec4d getPointsColor(double valSpeed, double vMinSpeed = 0.0, double vMaxSpeed = 0.0);
	float getMinSpeed() const { return m_minPointsSpeed; }
	float getMaxSpeed() const { return m_maxPoinsSpeed; }
	float getXMin() { return m_xMinPos; }
	float getXMax() { return m_xMaxPos; }
	float getYMin() { return m_yMinPos; }
	float getYMax() { return m_yMaxPos; }
	float getZMin() { return m_zMinPos; }
	float getZMax() { return m_zMaxPos; }

private:
	bool  m_isChangeColor; //色度条更新
	float m_maxPoinsSpeed;//用于计算顶点的颜色值
	float m_minPointsSpeed;//用于计算顶点的颜色值
	float m_xMinPos;
	float m_xMaxPos;
	float m_yMinPos;
	float m_yMaxPos;
	float m_zMinPos;
	float m_zMaxPos;
	//保存每个文件所有的探测顶点数据
	osg::ref_ptr<osg::Vec4dArray> m_pAllDetectPointsArray;
};
