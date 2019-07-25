#include "detectData/detectData.h"

/****************************************************************************************************************************************************/
//FUNCTION:��ʼ������
void detectData::initDetectData(int xMin, int xMax, int yMin, int yMax,
	int zMin, int zMax, float minSpeed, float maxSpeed, osg::ref_ptr<osg::Vec4dArray> vPointArray)
{
	//��������ǰ������������
	m_pAllDetectPointsArray->clear();
	m_maxPoinsSpeed = maxSpeed;
	m_minPointsSpeed = minSpeed;
	m_xMinPos = xMin;
	m_xMaxPos = xMax;
	m_yMinPos = yMin;
	m_yMaxPos = yMax;
	m_zMinPos = zMin;
	m_zMaxPos = zMax;
	for (unsigned int i = 0; i < vPointArray->size(); i++)
	{
		m_pAllDetectPointsArray->push_back((*vPointArray)[i]);
	}
}

/****************************************************************************************************************************************************/
//FUNCTION:
osg::Vec4d detectData::getPointsColor(double valSpeed, double vMinSpeed, double vMaxSpeed)
{
	// �ٶȵĿ�ȣ���ɫ��Ҫ�ֳɶ��ٷ�
	double spanSpeed = (vMaxSpeed - vMinSpeed);
	// һ���ٶ��ܹ�ռ�е���ɫ����
	// ��ɫ��Χ��255-0-255
	// ���磬��ɫ���Էֳ� 511�ݣ���ôһ���ٶ��ܹ��ֵõ���ɫ����Ϊ 511/spanSpeed
	double speedRate = (255 + 255) / spanSpeed;

	// ��ǰ�ٶȱ���С�ٶ� ƫ�Ƶ���ɫ����
	double subtract = (valSpeed - vMinSpeed) * speedRate;

	// BLUE
	double blueVal;
	// ��ɫ���� subtract��[0, 255)
	if (subtract < 255)
	{
		// ��ɫ������[1��0)
		blueVal = (255 - subtract) / 255;
	}
	else
	{
		// ��ɫ����
		blueVal = 0;
	}
	// GREEN
	double greenVal;
	// ��ɫ���� subtract��[0, 255)
	if (subtract < 255)
	{
		// ��ɫ������[0��1)
		greenVal = subtract / 255;
	}
	else if (subtract < 510)
	{
		// ��ɫ������[1��0)
		greenVal = (510 - subtract) / 255;
	}
	else
	{
		greenVal = 0;
	}

	// RED
	double redVal;
	// ��ɫ���� subtract��[0, 255)
	if (subtract < 255)
	{
		redVal = 0;
	}
	else if (subtract < 510)
	{
		// ��ɫ������[0��1)
		redVal = (subtract - 255) / 255;
	}
	else
	{
		// subtract��510
		redVal = 1;
	}
	// ���ݼ������RGB����������ɫ����
	// ���ص����ɫ����
	return osg::Vec4d(redVal, greenVal, blueVal, 1.0);
}
