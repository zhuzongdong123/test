#pragma once
#include <string>
#include <osg/Array>
#include <fstream>
#include <memory>

//��̽�����ݵĵ���ͷ���(���������ܶȴ���)
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

	//��ʼ������
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
	bool  m_isChangeColor; //ɫ��������
	float m_maxPoinsSpeed;//���ڼ��㶥�����ɫֵ
	float m_minPointsSpeed;//���ڼ��㶥�����ɫֵ
	float m_xMinPos;
	float m_xMaxPos;
	float m_yMinPos;
	float m_yMaxPos;
	float m_zMinPos;
	float m_zMaxPos;
	//����ÿ���ļ����е�̽�ⶥ������
	osg::ref_ptr<osg::Vec4dArray> m_pAllDetectPointsArray;
};
