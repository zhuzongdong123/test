#include "detectData/detectData.h"

/****************************************************************************************************************************************************/
//FUNCTION:初始化数据
void detectData::initDetectData(int xMin, int xMax, int yMin, int yMax,
	int zMin, int zMax, float minSpeed, float maxSpeed, osg::ref_ptr<osg::Vec4dArray> vPointArray)
{
	//导入数据前首先清理数据
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
	// 根据计算出的RGB分量生成颜色对象
	// 返回点的颜色对象
	return osg::Vec4d(redVal, greenVal, blueVal, 1.0);
}
