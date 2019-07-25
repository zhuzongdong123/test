#include "ModelingSubdivision.h"
#include "GlobalClass/GlobalParam.h"
#include <set>

ModelingSubdivision::ModelingSubdivision(QWidget* parent) : ViewerWidget3d(parent)
{
	m_XY = NULL; //ÿ���ڵ����������
	m_I4 = NULL; //���е�Ԫ���õĶ�������

	m_nodeXCount = 0; //ģ��x����Ľڵ㳤��
	m_nodeYCount = 0; //ģ��y����Ľڵ㳤��
	m_nodeZCount = 0; //ģ��z����Ľڵ㳤��

	m_xDirEdgeCount = 0; //x����߳�����
	m_yDirEdgeCount = 0; //y����߳�����
	m_zDirEdgeCount = 0; //z����߳�����

	m_gridNum = 0;//����Ԫ����
	m_ND = 0;//����ڵ�����
	m_tunnelCavityXBegin = 0; //�����ǻx���
	m_tunnelCavityXEnd = 0; //�����ǻx�յ�
	m_tunnelCavityYBegin = 0; //�����ǻy���
	m_tunnelCavityYEnd = 0; //�����ǻy�յ�

	m_inverXBeg = 0; //��������x���
	m_inverXEnd = 0; //��������x�յ�
	m_inverYBeg = 0; //��������y���
	m_inverYEnd = 0; //��������y�յ�

	
	m_XElectrodCount = 0; //x��������缫�ĸ���
	m_YElectrodCount = 0; //y��������缫�ĸ���

	m_tunnelForZBegin = 0; //���Ԥ������Z���
	m_tunnelForZEnd = 0; //���Ԥ������Z�յ�

	m_isCreate = false;

	m_pointLineGroup = new osg::Group; //��������
	m_subBodyGroup = new osg::Group; //������Χ��
	getSceneGroup()->addChild(m_pointLineGroup.get());
	getSceneGroup()->addChild(m_subBodyGroup.get());
}

bool compareVec3d(osg::Vec3d a, osg::Vec3d b)
{
	if (a.x() < b.x())
		return true;
	else if (fabs(a.x() - b.x()) < 1e-10)
	{
		if (a.y() < b.y())
			return true;
	}
	return false;
}

bool compareDouble(double a, double b)
{
	if (a < b)
		return true;
	else
		return false;
}

bool compareDescendXVec2(osg::Vec2 a, osg::Vec2 b)
{
	if (a.x() > b.x())
		return true;
	else
		return false;
}

/*************************************************************************************************************/
//function:�Զ�����ģ
void ModelingSubdivision::doModel()
{
	if (NULL != m_I4)
	{
		for (int i = 0; i < m_gridNum; i++)
		{
			delete[] m_I4[i];
			m_I4[i] = NULL;
		}
		delete[] m_I4;
		m_I4 = NULL;
	}
	
	if (NULL != m_XY)
	{
		for (int i = 0; i < m_ND; i++)
		{
			delete[] m_XY[i];
			m_XY[i] = NULL;
		}
		delete[] m_XY;
		m_XY = NULL;
	}

	m_isCreate = false;

	m_XL.clear();
	m_YL.clear();
	m_ZL.clear();
	m_XVec.clear();
	m_YVec.clear();
	m_ZVec.clear();
	
	//Ԥ�����򳤶�
	float forecastLength = GlobalParam::instance()->getModeling().forecastLength;
	//Ԥ��������
	float interForcastSpace = GlobalParam::instance()->getModeling().predictionCellSpacing;
	//�����ǻX����
	float tunnelCavityRangeX = GlobalParam::instance()->getModeling().tunnelCavityRangeX;
	//�����ǻY����
	float tunnelCavityRangeY = GlobalParam::instance()->getModeling().tunnelCavityRangeY;
	//����X��������
	float inversionAreaRangeX = GlobalParam::instance()->getModeling().inversionAreaRangeX;
	//����Y��������
	float inversionAreaRangeY = GlobalParam::instance()->getModeling().inversionAreaRangeY;

	//������λ������
	std::vector<osg::Vec3d> measuringPointData = GlobalParam::instance()->getObservationSystemSetting().measuringPointData;
	//ÿȦ�����Դ�����������ƫ�ƾ�
	std::vector<double> elecCircleDisVec = GlobalParam::instance()->getObservationSystemSetting().elecCircleDisVec;
	
	std::vector<double> arrayRever;
	arrayRever.reserve(elecCircleDisVec.size());
	vector<double>::reverse_iterator riter;
	for (riter = elecCircleDisVec.rbegin(); riter != elecCircleDisVec.rend(); riter++)
	{
		arrayRever.push_back(*riter);
	}
	
	m_electroCircleNum = arrayRever.size()+1; //��ȡ����缫��Ȧ��

	//������缫Ȧ�����밴�վ����������Զ������
	//sort(elecCircleDisVec.begin(), elecCircleDisVec.end(), compareDouble);
	
	//���������Ȱ���x�����ٰ���y����
	sort(measuringPointData.begin(), measuringPointData.end(), compareVec3d);

	m_inverXBeg = 0; //��������x���
	m_inverXEnd = 0; //��������x�յ�
	m_inverYBeg = 0; //��������y���
	m_inverYEnd = 0; //��������y�յ�

	//X����
	std::vector<double> xDirValue;
	std::vector<double> yDirValue;
	for (int i = 0; i < measuringPointData.size(); i ++)
	{
		bool nearInterValSame = false;
		for (int j = 0; j < xDirValue.size(); j++)
		{
			if (fabs(xDirValue[j] - measuringPointData[i].x()) < 0.01)
				nearInterValSame = true;
		}

		if (!nearInterValSame)
		{
			xDirValue.push_back(measuringPointData[i].x());
		}

		nearInterValSame = false;
		for (int j = 0; j < yDirValue.size(); j++)
		{
			if (fabs(yDirValue[j] - measuringPointData[i].y()) < 0.01)
				nearInterValSame = true;
		}

		if (!nearInterValSame)
		{
			yDirValue.push_back(measuringPointData[i].y());
		}
	}

	if (yDirValue.size() == 0)	return;

	//���ݰ�˳������
	sort(xDirValue.begin(), xDirValue.end(), compareDouble);
	//���ݰ�˳������
	sort(yDirValue.begin(), yDirValue.end(), compareDouble);
	
	m_MeaPointXYIndexVec.clear();
	m_MeaPointXYIndexVec.resize(measuringPointData.size());
	for (unsigned int i = 0; i < measuringPointData.size(); i++)
	{
		osg::Vec2d tmpPoint = osg::Vec2d(measuringPointData[i].x(), measuringPointData[i].y());
		m_MeaPointXYIndexVec[i].x() = 1;
		m_MeaPointXYIndexVec[i].y() = 1;
		for (int j = 0; j < xDirValue.size(); j++)
		{
			if (tmpPoint.x() > xDirValue[j])
				m_MeaPointXYIndexVec[i].x() += 1;
		}

		for (int j = 0; j < yDirValue.size(); j++)
		{
			if (tmpPoint.y() > yDirValue[j])
				m_MeaPointXYIndexVec[i].y() += 1;
		}
	}
		
	std::set<double> tmpSet;
	//����Y����������ǻ�ڷָ�
	tmpSet.clear();
	double totalLen = 0.0;

	for (unsigned int i = 0; i < yDirValue.size()-1; i++)
	{
		double nearInterYVal = yDirValue[i + 1] - yDirValue[i];
		totalLen += nearInterYVal;
		m_YL.push_back(nearInterYVal);
		tmpSet.insert(nearInterYVal);
	}

	//�����缫�������������������д���ʽTBM�������ʷ�
	double measElectrInter = 1;
	for (unsigned int i = 0; i < m_YL.size(); i++)
	{
		double middleDis = m_YL[i];
		bool isSubdivison = false;

		while (middleDis > measElectrInter)
		{
			middleDis /= 2;
			m_YL.erase(m_YL.begin()+i);
			m_YL.insert(m_YL.begin()+i,middleDis);
			m_YL.insert(m_YL.begin()+i,middleDis);
			tmpSet.insert(middleDis);
			for (unsigned int k = 0; k < m_MeaPointXYIndexVec.size(); k++)
			{
				if (m_MeaPointXYIndexVec[k].y() > i+1)
				    m_MeaPointXYIndexVec[k].y() += 1;
			}
			isSubdivison = true;
		}

		if (isSubdivison)
		{
			i --;
			isSubdivison = false;
		}
	}
	
	float yLeftInterDis = yDirValue[0]+ tunnelCavityRangeY / 2;
	float yRightInterDis = tunnelCavityRangeY/2 - (yDirValue[0] + totalLen);

	if (yLeftInterDis < 0)
		printf("the left x pos is error!\n");
	if (yRightInterDis < 0)
		printf("the right x pos is error!\n");

	std::set<double>::iterator it = tmpSet.begin();
	int leftSubCount = 0;
	int leftYAddNum = 0;
	int leftXAddNum = 0;
	if (yLeftInterDis > 2 * (*it))
	{
		m_YL.insert(m_YL.begin(), yLeftInterDis / 2);
		m_YL.insert(m_YL.begin(), yLeftInterDis / 2);
		leftSubCount = 2;
		leftYAddNum = 2;
	}
	else
	{
		m_YL.insert(m_YL.begin(), yLeftInterDis);
		leftSubCount = 1;
		leftYAddNum = 1;
	}
    
	int rightSubCount = 0;
	if (yRightInterDis > 2 * (*it))
	{
		m_YL.push_back(yRightInterDis / 2);
		m_YL.push_back(yRightInterDis / 2);
		rightSubCount = m_YL.size() - 2;
	}
	else
	{
		m_YL.push_back(yRightInterDis);
		rightSubCount = m_YL.size() - 1;
	}

	double maxYDis = 0.0;
	double minYDis = (*it);
	for (int k = leftSubCount-1; k >= 0; k--)
	{
		if (m_YL[k] > 2 * minYDis)
		{
			double tmpValue = m_YL[k];
			m_YL.erase(m_YL.begin() + k);
			m_YL.insert(m_YL.begin() + k, tmpValue / 2);
			m_YL.insert(m_YL.begin() + k, tmpValue / 2);
			leftYAddNum++;
			rightSubCount++;
			minYDis = tmpValue / 2;
		}
	}

	minYDis = (*it);
	for (int k = rightSubCount; k < m_YL.size(); k ++)
	{
		if (m_YL[k] > 2 * minYDis)
		{
			double tmpValue = m_YL[k];
			m_YL.erase(m_YL.begin() + k);
			m_YL.insert(m_YL.begin() + k, tmpValue / 2);
			m_YL.insert(m_YL.begin() + k, tmpValue / 2);
			minYDis = tmpValue / 2;
		}
	}
	maxYDis = m_YL[m_YL.size()-1];
	int electroYDirCount = m_YL.size();
	
	//Y������������չ
	double inverYLeft = (inversionAreaRangeY - tunnelCavityRangeY) / 2;
	double inverYRight = (inversionAreaRangeY - tunnelCavityRangeY) / 2;
	double totalYLen = 0.0;
	for (int i = 0; i < 10; i++)
	{
		double tmpPowValue = pow(2,i);
		if (tmpPowValue > maxYDis)
		{
			totalYLen += tmpPowValue;
			if (totalYLen < inverYRight)
			{
				m_YL.insert(m_YL.begin(), tmpPowValue);
				leftYAddNum++;
				m_YL.push_back(tmpPowValue);
			}
			else
			{
				totalYLen -= pow(2,i);		
				double tmpRLastValue = inverYRight - totalYLen;
				if (tmpRLastValue > pow(2, i - 1))
				{
					m_YL.insert(m_YL.begin(), tmpRLastValue);
					leftYAddNum++;
					m_YL.push_back(tmpRLastValue);
				}
				else
				{
					double LastPowValue = (pow(2, i - 1) + tmpRLastValue)/2;
					m_YL.erase(m_YL.end() - 1);
					m_YL.erase(m_YL.begin());
					m_YL.insert(m_YL.begin(), LastPowValue);
					m_YL.push_back(LastPowValue);
					m_YL.insert(m_YL.begin(), LastPowValue);
					m_YL.push_back(LastPowValue);
					
					leftYAddNum++;
				}
				break;
			}
		}
	}
	
	//����������ͷ�Գ�
	int inverYNodeCount = (m_YL.size() - electroYDirCount)/2;
	
	//����X����������ǻ�ڷָ�
	tmpSet.clear();
	totalLen = 0.0;
	int electroXDirCount = 0;
	for (unsigned int i = 0; i < xDirValue.size()-1; i++)
	{
		double nearInterXVal = xDirValue[i + 1] - xDirValue[i];
		totalLen += nearInterXVal;
		m_XL.push_back(nearInterXVal);
		tmpSet.insert(nearInterXVal);
	}

	for (unsigned int i = 0; i < m_XL.size(); i++)
	{
		double middleDis = m_XL[i];
		bool isSubdivison = false;

		while (middleDis > measElectrInter)
		{
			middleDis /= 2;
			m_XL.erase(m_XL.begin() + i);
			m_XL.insert(m_XL.begin() + i, middleDis);
			m_XL.insert(m_XL.begin() + i, middleDis);
			tmpSet.insert(middleDis);
			for (unsigned int k = 0; k < m_MeaPointXYIndexVec.size(); k++)
			{
				if (m_MeaPointXYIndexVec[k].x() > i + 1)
					m_MeaPointXYIndexVec[k].x() += 1;
			}
			isSubdivison = true;
		}

		if (isSubdivison)
		{
			i--;
			isSubdivison = false;
		}
	}
	
	float xLeftInterDis = xDirValue[0] + tunnelCavityRangeX / 2;
	float xRightInterDis = tunnelCavityRangeX/2 - (xDirValue[0] + totalLen);
	
	if (xLeftInterDis < 0)
		printf("the left x pos is error!\n");
	if (xRightInterDis < 0)
		printf("the right x pos is error!\n");

	std::set<double>::iterator itX = tmpSet.begin();
	leftSubCount = 0;
	if (xLeftInterDis > 2 * (*itX))
	{
		m_XL.insert(m_XL.begin(), xLeftInterDis / 2);
		m_XL.insert(m_XL.begin(), xLeftInterDis / 2);
		leftXAddNum = 2;
		leftSubCount = 2;
	}
	else
	{
		m_XL.insert(m_XL.begin(), xLeftInterDis);
		leftXAddNum = 1;
		leftSubCount = 1;
	}

	rightSubCount = 0;
	if (xRightInterDis > 2 * (*itX))
	{
		m_XL.push_back(xRightInterDis / 2);
		m_XL.push_back(xRightInterDis / 2);
		rightSubCount = 2;
	}
	else
	{
		m_XL.push_back(xRightInterDis);
		rightSubCount = 1;
	}

	double maxXDis = 0.0;
	double minXDis = (*itX);
	for (int k = leftSubCount - 1; k >= 0; k--)
	{
		if (m_XL[k] > 2 * minXDis)
		{
			double tmpValue = m_XL[k];
			m_XL.erase(m_XL.begin() + k);
			m_XL.insert(m_XL.begin() + k, tmpValue / 2);
			m_XL.insert(m_XL.begin() + k, tmpValue / 2);
			leftXAddNum++;
			rightSubCount++;
			minXDis = tmpValue / 2;
		}
	}

	minXDis = (*itX);
	for (int k = rightSubCount; k < m_XL.size(); k++)
	{
		if (m_XL[k] > 2 * minXDis)
		{
			double tmpValue = m_XL[k];
			m_XL.erase(m_XL.begin() + k);
			m_XL.insert(m_XL.begin() + k, tmpValue / 2);
			m_XL.insert(m_XL.begin() + k, tmpValue / 2);
			minXDis = tmpValue / 2;
		}
	}
	maxXDis = m_XL[m_XL.size() - 1];
	electroXDirCount = m_XL.size();

	//X������������չ
	double inverXLeft = (inversionAreaRangeX - tunnelCavityRangeX) / 2;
	double totalXLen = 0.0;
	for (int i = 0; i <= 8; i++)
	{
		double tmpPowValue = pow(2, i);
		if (tmpPowValue > maxXDis)
		{
			totalXLen += tmpPowValue;
			if (totalXLen < inverXLeft)
			{
				m_XL.insert(m_XL.begin(), tmpPowValue);
				m_XL.push_back(tmpPowValue);
				leftXAddNum++;
			}
			else
			{
				totalXLen -= pow(2, i);
				double tmpRLastValue = inverXLeft - totalXLen;
				if (tmpRLastValue > pow(2, i - 1))
				{
					m_XL.insert(m_XL.begin(), tmpRLastValue);
					m_XL.push_back(tmpRLastValue);
					leftXAddNum++;
				}
				else
				{
					double LastPowValue = (pow(2, i - 1) + tmpRLastValue)/2 ;

					m_XL.erase(m_XL.end()-1);
					m_XL.erase(m_XL.begin());
					m_XL.insert(m_XL.begin(), LastPowValue);
					m_XL.push_back(LastPowValue);
					m_XL.insert(m_XL.begin(), LastPowValue);
					m_XL.push_back(LastPowValue);
					leftXAddNum++;
				}
				break;
			}
		}
	}

	int inverXNodeCount = (m_XL.size() - electroXDirCount) / 2;

	int tmpXBeg = 0;
	int tmpYBeg = 0;
	int tmpZBeg = 0;
	int tmpXInverCount = m_XL.size();
	int tmpYInverCount = m_YL.size();
	int tmpZInverCount = 0;
	for (int i = 0; i <= 8; i++)
	{
		double tmpPowValue = pow(2, i);
		if (tmpPowValue > m_XL[m_XL.size()-1])
		{
			m_XL.insert(m_XL.begin(), tmpPowValue);
			tmpXBeg++;
			leftXAddNum++;
			m_XL.push_back(tmpPowValue);
		}

		if (tmpPowValue > m_YL[m_YL.size() - 1])
		{
			m_YL.insert(m_YL.begin(), tmpPowValue);
			tmpYBeg++;
			leftYAddNum++;
			m_YL.push_back(tmpPowValue);
		}
	}
	
	for (unsigned int i = 0; i < m_MeaPointXYIndexVec.size(); i++)
	{
		m_MeaPointXYIndexVec[i].x() += leftXAddNum;
		m_MeaPointXYIndexVec[i].y() += leftYAddNum;
	}

	m_inverXBeg = tmpXBeg; //�����������x���
	m_inverXEnd = tmpXBeg + tmpXInverCount - 1; //�����������x�յ�
	m_inverYBeg = tmpYBeg; //�����������y���
	m_inverYEnd = tmpYBeg + tmpYInverCount - 1; //�����������y�յ�

	m_tunnelCavityXBegin = m_inverXBeg + inverXNodeCount;
	m_tunnelCavityXEnd = m_inverXEnd - inverXNodeCount ;

	m_tunnelCavityYBegin = m_inverYBeg + inverYNodeCount;
	m_tunnelCavityYEnd = m_inverYEnd - inverYNodeCount;

    //z�����������ʷ�
	for (int i = 0; i < arrayRever.size(); i++)
	{
		m_ZL.insert(m_ZL.begin(), arrayRever[i]);
	}

	for (int i = 0; i <= 8; i++)
	{
		if (m_ZL.size() == 0)
			break;
		double tmpValue = pow(2,i);
		if (m_ZL[0] < tmpValue)
			m_ZL.insert(m_ZL.begin(), tmpValue);
	}
	
	int predictInterCount = forecastLength/ interForcastSpace;
	m_tunnelForZBegin = m_ZL.size();
	GlobalParam::instance()->getForwardModelingParaSetting().setForwardValue(m_tunnelForZBegin+1);
	for (int i = 0; i < predictInterCount; i ++)
	{
		m_ZL.push_back(interForcastSpace);
	}
	m_tunnelForZEnd = m_tunnelForZBegin + predictInterCount - 1;
	
	for (int i = 0; i <= 8; i++)
	{
		double tmpValue = pow(2,i);
		if (tmpValue > interForcastSpace)
			m_ZL.push_back(tmpValue);
	}

	m_nodeXCount = m_XL.size() + 1; //ģ��x����Ľڵ����
	m_nodeYCount = m_YL.size() + 1; //ģ��y����Ľڵ����
	m_nodeZCount = m_ZL.size() + 1; //ģ��z����Ľڵ㳤��

	m_xDirEdgeCount = m_XL.size(); //x����߳�����
	m_yDirEdgeCount = m_YL.size(); //y����߳�����
	m_zDirEdgeCount = m_ZL.size(); //z����߳�����

	m_XVec.push_back(0.0);
	for (int i = 1; i < m_nodeXCount; i++)
	{
		double tmpValue = m_XVec[i - 1] + m_XL[i - 1];
		m_XVec.push_back(tmpValue);
	}

	m_YVec.resize(m_nodeYCount);
	m_YVec[m_nodeYCount-1] = 0.0;
	for (int i = 1; i < m_nodeYCount; i++)
	{
		double tmpValue = m_YVec[i - 1] + m_YL[i - 1];
		m_YVec[m_nodeYCount - i - 1] = m_YVec[m_nodeYCount + 1 - i - 1] + m_YL[i - 1];
	}

	m_ZVec.push_back(0.0);
	for (int i = 1; i < m_nodeZCount; i++)
	{
		double tmpValue = m_ZVec[i - 1] + m_ZL[i - 1];
		m_ZVec.push_back(tmpValue);
	}

	m_pointLineGroup->removeChildren(0, m_pointLineGroup->getNumChildren());
	m_subBodyGroup->removeChildren(0, m_subBodyGroup->getNumChildren());
	
	modelBuilding();

	drawSubdivisionGridPoints();
	drawSubdivisionGridLine();
	
	getViewer()->setSceneData(getSceneGroup());

	//ģ�ʹ����ɹ�
	m_isCreate = true;
	//�Բ����缫��Ҫ��������
	sort(m_MeaPointXYIndexVec.begin(), m_MeaPointXYIndexVec.end(), compareDescendXVec2);
}

void ModelingSubdivision::clearModel()
{
	if (NULL != m_I4)
	{
		for (int i = 0; i < m_gridNum; i++)
		{
			delete[] m_I4[i];
			m_I4[i] = NULL;
		}
		delete[] m_I4;
		m_I4 = NULL;
	}

	if (NULL != m_XY)
	{
		for (int i = 0; i < m_ND; i++)
		{
			delete[] m_XY[i];
			m_XY[i] = NULL;
		}
		delete[] m_XY;
		m_XY = NULL;
	}

	m_isCreate = false;

	m_XL.clear();
	m_YL.clear();
	m_ZL.clear();
	m_XVec.clear();
	m_YVec.clear();
	m_ZVec.clear();
	m_MeaPointXYIndexVec.clear();
}


/*************************************************************************************************************/
//function:�Զ�����ģ
void ModelingSubdivision::updateModel()
{
	if (NULL != m_I4)
	{
		for (int i = 0; i < m_gridNum; i++)
		{
			delete[] m_I4[i];
			m_I4[i] = NULL;
		}
		delete[] m_I4;
		m_I4 = NULL;
	}

	if (NULL != m_XY)
	{
		for (int i = 0; i < m_ND; i++)
		{
			delete[] m_XY[i];
			m_XY[i] = NULL;
		}
		delete[] m_XY;
		m_XY = NULL;
	}

	m_isCreate = false;
	m_XVec.clear();
	m_YVec.clear();
	m_ZVec.clear();

	m_nodeXCount = m_XL.size() + 1; //ģ��x����Ľڵ����
	m_nodeYCount = m_YL.size() + 1; //ģ��y����Ľڵ����
	m_nodeZCount = m_ZL.size() + 1; //ģ��z����Ľڵ㳤��

	m_xDirEdgeCount = m_XL.size(); //x����߳�����
	m_yDirEdgeCount = m_YL.size(); //y����߳�����
	m_zDirEdgeCount = m_ZL.size(); //z����߳�����

	m_XVec.push_back(0.0);
	for (int i = 1; i < m_nodeXCount; i++)
	{
		double tmpValue = m_XVec[i - 1] + m_XL[i - 1];
		m_XVec.push_back(tmpValue);
	}

	m_YVec.resize(m_nodeYCount);
	m_YVec[m_nodeYCount - 1] = 0.0;
	for (int i = 1; i < m_nodeYCount; i++)
	{
		double tmpValue = m_YVec[i - 1] + m_YL[i - 1];
		m_YVec[m_nodeYCount - i - 1] = m_YVec[m_nodeYCount + 1 - i - 1] + m_YL[i - 1];
	}

	m_ZVec.push_back(0.0);
	for (int i = 1; i < m_nodeZCount; i++)
	{
		double tmpValue = m_ZVec[i - 1] + m_ZL[i - 1];
		m_ZVec.push_back(tmpValue);
	}

	m_pointLineGroup->removeChildren(0, m_pointLineGroup->getNumChildren());
	m_subBodyGroup->removeChildren(0, m_subBodyGroup->getNumChildren());

	modelBuilding();

	drawSubdivisionGridPoints();
	drawSubdivisionGridLine();

	getViewer()->setSceneData(getSceneGroup());

	//ģ�ʹ����ɹ�
	m_isCreate = true;
}

/*********************************************************************************************************************/
//function ��ģ��������
void ModelingSubdivision::modelSubBodyHidden()
{
	m_subBodyGroup->setNodeMask(0);
}

/*********************************************************************************************************************/
//function ��ģ��������
void ModelingSubdivision::modelSubBodyDisplay()
{
	m_subBodyGroup->setNodeMask(1);
}

/*********************************************************************************************************************/
//function ����������ϵ�����ÿ���ڵ��λ�ü���Ԫ�ڵ���
void ModelingSubdivision::modelBuilding()
{
	int NZ = m_nodeZCount-1;
	int NY = m_nodeYCount-1;
	int NX = m_nodeXCount-1;

	m_gridNum = NX*NY*NZ;
	m_ND = m_nodeZCount*m_nodeYCount*m_nodeXCount;
	
	if (NULL == m_I4)
	{
		m_I4 = new int*[m_gridNum];
		for (unsigned int i = 0; i < m_gridNum; i++)
		{
			m_I4[i] = new int[8];
			memset(m_I4[i], 0, sizeof(int) * 8);
		}
	}
	
	if (NULL == m_XY)
	{
		m_XY = new double*[m_ND];
		for (unsigned int i = 0; i < m_ND; i++)
		{
			m_XY[i] = new double[3];
			memset(m_XY[i], 0.0, sizeof(double) * 3);
		}
	}
	
	float magniTimes = 3.0;
	for (unsigned int IZ = 0; IZ < NZ+1; IZ++)
	{
		for (unsigned int IX = 0; IX < NX + 1; IX++)
		{
			for (unsigned int IY = 0; IY < NY + 1; IY++)
			{
				unsigned int N = (IZ) * (NX + 1) * (NY + 1) + (IX) * (NY + 1) + IY;

				m_XY[N][0] = m_XVec[IX];//��N���ڵ��X����
				m_XY[N][1] = m_YVec[IY];//��N���ڵ��Y����
				m_XY[N][2] = m_ZVec[IZ];//��N���ڵ��Z����
			}
		}
	}

	osg::ref_ptr<osg::Geode> sameGeode = new osg::Geode;
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	osg::ref_ptr<osg::Vec3dArray> pPointArray = new osg::Vec3dArray;
	osg::ref_ptr<osg::Vec4Array> normalArray = new osg::Vec4Array();//����һ����ɫ������ɫ
	
	for (unsigned int IZ = 0; IZ < NZ; IZ++)
	{
		for (unsigned int IX = 0; IX < NX; IX++)
		{
			for (unsigned int IY = 0; IY < NY; IY++)
			{
				unsigned int N = (IZ)*NX*NY + (IX)*NY + IY;
				unsigned int N1 = (IZ)*(NX + 1)*(NY + 1) + (IX)*(NY + 1) + IY;

				m_I4[N][0] = N1;
				m_I4[N][1] = N1 + 1; //����X����Ϊ����߶ȷ����ڳ�ʼ�ڵ���Ϸ�
				m_I4[N][2] = N1 + NY + 2; //����Y����Ϊ�����ȣ���XY��������Ͻ�
				m_I4[N][3] = N1 + NY + 1; //����Y����Ϊ�����ȣ���XY��������½�
				m_I4[N][4] = N1 + (NX + 1) * (NY + 1);
				m_I4[N][5] = N1 + (NX + 1) * (NY + 1) + 1;
				m_I4[N][6] = N1 + (NX + 1)*(NY + 1) + NY + 2;
				m_I4[N][7] = N1 + (NX + 1)*(NY + 1) + NY + 1;

				if (IZ == 0)
				{
					//ǰһ����
					pPointArray->push_back(osg::Vec3d(m_XY[m_I4[N][0]][0], m_XY[m_I4[N][0]][1], m_XY[m_I4[N][0]][2]));
					pPointArray->push_back(osg::Vec3d(m_XY[m_I4[N][1]][0], m_XY[m_I4[N][1]][1], m_XY[m_I4[N][1]][2]));
					pPointArray->push_back(osg::Vec3d(m_XY[m_I4[N][2]][0], m_XY[m_I4[N][2]][1], m_XY[m_I4[N][2]][2]));
					pPointArray->push_back(osg::Vec3d(m_XY[m_I4[N][3]][0], m_XY[m_I4[N][3]][1], m_XY[m_I4[N][3]][2]));
				    
					normalArray->push_back(osg::Vec4(0.0, 0, -1.0, 1.0));
					normalArray->push_back(osg::Vec4(0.0, 0, -1.0, 1.0));
					normalArray->push_back(osg::Vec4(0.0, 0, -1.0, 1.0));
					normalArray->push_back(osg::Vec4(0.0, 0, -1.0, 1.0));
				}
				
				if (IZ == NZ - 1)
				{
					//��һ����
					pPointArray->push_back(osg::Vec3d(m_XY[m_I4[N][4]][0], m_XY[m_I4[N][4]][1], m_XY[m_I4[N][4]][2]));
					pPointArray->push_back(osg::Vec3d(m_XY[m_I4[N][5]][0], m_XY[m_I4[N][5]][1], m_XY[m_I4[N][5]][2]));
					pPointArray->push_back(osg::Vec3d(m_XY[m_I4[N][6]][0], m_XY[m_I4[N][6]][1], m_XY[m_I4[N][6]][2]));
					pPointArray->push_back(osg::Vec3d(m_XY[m_I4[N][7]][0], m_XY[m_I4[N][7]][1], m_XY[m_I4[N][7]][2]));

					normalArray->push_back(osg::Vec4(0.0, 0.0, 1.0, 1.0));
					normalArray->push_back(osg::Vec4(0.0, 0.0, 1.0, 1.0));
					normalArray->push_back(osg::Vec4(0.0, 0.0, 1.0, 1.0));
					normalArray->push_back(osg::Vec4(0.0, 0.0, 1.0, 1.0));
				}
				
				if (IY == NY -1)
				{
					//��һ����
					pPointArray->push_back(osg::Vec3d(m_XY[m_I4[N][1]][0], m_XY[m_I4[N][1]][1], m_XY[m_I4[N][1]][2]));
					pPointArray->push_back(osg::Vec3d(m_XY[m_I4[N][2]][0], m_XY[m_I4[N][2]][1], m_XY[m_I4[N][2]][2]));
					pPointArray->push_back(osg::Vec3d(m_XY[m_I4[N][6]][0], m_XY[m_I4[N][6]][1], m_XY[m_I4[N][6]][2]));
					pPointArray->push_back(osg::Vec3d(m_XY[m_I4[N][5]][0], m_XY[m_I4[N][5]][1], m_XY[m_I4[N][5]][2]));

					normalArray->push_back(osg::Vec4(0.0, 1.0, 0.0, 1.0));
					normalArray->push_back(osg::Vec4(0.0, 1.0, 0.0, 1.0));
					normalArray->push_back(osg::Vec4(0.0, 1.0, 0.0, 1.0));
					normalArray->push_back(osg::Vec4(0.0, 1.0, 0.0, 1.0));
				}
				
				if (IY == 0)
				{
					//��һ����
					pPointArray->push_back(osg::Vec3d(m_XY[m_I4[N][0]][0], m_XY[m_I4[N][0]][1], m_XY[m_I4[N][0]][2]));
					pPointArray->push_back(osg::Vec3d(m_XY[m_I4[N][3]][0], m_XY[m_I4[N][3]][1], m_XY[m_I4[N][3]][2]));
					pPointArray->push_back(osg::Vec3d(m_XY[m_I4[N][7]][0], m_XY[m_I4[N][7]][1], m_XY[m_I4[N][7]][2]));
					pPointArray->push_back(osg::Vec3d(m_XY[m_I4[N][4]][0], m_XY[m_I4[N][4]][1], m_XY[m_I4[N][4]][2]));

					normalArray->push_back(osg::Vec4(0.0, -1.0, 0.0, 1.0));
					normalArray->push_back(osg::Vec4(0.0, -1.0, 0.0, 1.0));
					normalArray->push_back(osg::Vec4(0.0, -1.0, 0.0, 1.0));
					normalArray->push_back(osg::Vec4(0.0, -1.0, 0.0, 1.0));
				}
				
				if (IX == 0)
				{
					//��һ����
					pPointArray->push_back(osg::Vec3d(m_XY[m_I4[N][0]][0], m_XY[m_I4[N][0]][1], m_XY[m_I4[N][0]][2]));
					pPointArray->push_back(osg::Vec3d(m_XY[m_I4[N][1]][0], m_XY[m_I4[N][1]][1], m_XY[m_I4[N][1]][2]));
					pPointArray->push_back(osg::Vec3d(m_XY[m_I4[N][5]][0], m_XY[m_I4[N][5]][1], m_XY[m_I4[N][5]][2]));
					pPointArray->push_back(osg::Vec3d(m_XY[m_I4[N][4]][0], m_XY[m_I4[N][4]][1], m_XY[m_I4[N][4]][2]));

					normalArray->push_back(osg::Vec4(-1.0, 0.0, 0.0, 1.0));
					normalArray->push_back(osg::Vec4(-1.0, 0.0, 0.0, 1.0));
					normalArray->push_back(osg::Vec4(-1.0, 0.0, 0.0, 1.0));
					normalArray->push_back(osg::Vec4(-1.0, 0.0, 0.0, 1.0));
				}
				
				if (IX == NX-1)
				{
					//��һ����
					pPointArray->push_back(osg::Vec3d(m_XY[m_I4[N][2]][0], m_XY[m_I4[N][2]][1], m_XY[m_I4[N][2]][2]));
					pPointArray->push_back(osg::Vec3d(m_XY[m_I4[N][3]][0], m_XY[m_I4[N][3]][1], m_XY[m_I4[N][3]][2]));
					pPointArray->push_back(osg::Vec3d(m_XY[m_I4[N][7]][0], m_XY[m_I4[N][7]][1], m_XY[m_I4[N][7]][2]));
					pPointArray->push_back(osg::Vec3d(m_XY[m_I4[N][6]][0], m_XY[m_I4[N][6]][1], m_XY[m_I4[N][6]][2]));

					normalArray->push_back(osg::Vec4(1.0, 0.0, 0.0, 1.0));
					normalArray->push_back(osg::Vec4(1.0, 0.0, 0.0, 1.0));
					normalArray->push_back(osg::Vec4(1.0, 0.0, 0.0, 1.0));
					normalArray->push_back(osg::Vec4(1.0, 0.0, 0.0, 1.0));
				}				
			}
		}
	}
	
	osg::ref_ptr<osg::Vec4dArray> pointColorArray = new osg::Vec4dArray;
	pointColorArray->push_back(osg::Vec4d(1.0, 1.0, 1.0, 1.0));

	geom->setVertexArray(pPointArray.get());
	geom->setColorArray(pointColorArray.get());
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);
	geom->setNormalArray(normalArray.get());
	geom->setNormalBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);

	geom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, pPointArray->size()));
	sameGeode->addDrawable(geom.get());

	sameGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);
	sameGeode->getOrCreateStateSet()->setMode(GL_LIGHT0, osg::StateAttribute::ON);

	//������Դ
	osg::ref_ptr<osg::LightSource> ls = new osg::LightSource();
	//���������
	osg::ref_ptr<osg::Light> lt = new osg::Light();
	lt->setLightNum(0);
	//���÷���
	lt->setDirection(osg::Vec3(1.0, 1.0, 1.0));
	//����λ��
	osg::Vec3d lightPos = sameGeode->getBoundingBox().center();
	lightPos.z() = lightPos.z() + sameGeode->getBoundingBox().radius();
	lt->setPosition(osg::Vec4(lightPos, 1.0));
	//���ù����ɫ
	lt->setDiffuse(osg::Vec4(1.0, 1.0, 1.0, 1.0));//��ɫ�Ĺ�
	ls->setLight(lt);
	
	sameGeode->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
	sameGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	osg::PolygonMode *pLolyTotalMode = new osg::PolygonMode();
	pLolyTotalMode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::FILL);
	sameGeode->getOrCreateStateSet()->setAttribute(pLolyTotalMode);
	sameGeode->getOrCreateStateSet()->setAttributeAndModes(pLolyTotalMode, osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON);

	osg::ref_ptr<osg::MatrixTransform> pTran = new osg::MatrixTransform;
	pTran->setMatrix(osg::Matrix::translate(osg::Vec3d(0.2,0.2,0.2))* osg::Matrix::scale(osg::Vec3(0.9995, 0.9995, 0.9995)));
	pTran->addChild(sameGeode);

	m_subBodyGroup->addChild(ls.get());
	m_subBodyGroup->addChild(pTran.get());
}

/*******************************************************************************************************************/
//function:����������
void ModelingSubdivision::drawSubdivisionGridLine()
{
	osg::ref_ptr<osg::Geode> sameGeode = new osg::Geode;
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	osg::ref_ptr<osg::Vec3dArray> pPointArray = new osg::Vec3dArray;

	for (unsigned int i = 0; i < m_gridNum; i++)
	{
		int nodeIndex0 = m_I4[i][0];
		int nodeIndex1 = m_I4[i][1];
		int nodeIndex2 = m_I4[i][2];
		int nodeIndex3 = m_I4[i][3];
		int nodeIndex4 = m_I4[i][4];
		int nodeIndex5 = m_I4[i][5];
		int nodeIndex6 = m_I4[i][6];
		int nodeIndex7 = m_I4[i][7];
		
		//ǰһ����
		pPointArray->push_back(osg::Vec3d(m_XY[nodeIndex0][0], m_XY[nodeIndex0][1], m_XY[nodeIndex0][2]));
		pPointArray->push_back(osg::Vec3d(m_XY[nodeIndex1][0], m_XY[nodeIndex1][1], m_XY[nodeIndex1][2]));
		pPointArray->push_back(osg::Vec3d(m_XY[nodeIndex2][0], m_XY[nodeIndex2][1], m_XY[nodeIndex2][2]));
		pPointArray->push_back(osg::Vec3d(m_XY[nodeIndex3][0], m_XY[nodeIndex3][1], m_XY[nodeIndex3][2]));

		//��һ����
		pPointArray->push_back(osg::Vec3d(m_XY[nodeIndex4][0], m_XY[nodeIndex4][1], m_XY[nodeIndex4][2]));
		pPointArray->push_back(osg::Vec3d(m_XY[nodeIndex5][0], m_XY[nodeIndex5][1], m_XY[nodeIndex5][2]));
		pPointArray->push_back(osg::Vec3d(m_XY[nodeIndex6][0], m_XY[nodeIndex6][1], m_XY[nodeIndex6][2]));
		pPointArray->push_back(osg::Vec3d(m_XY[nodeIndex7][0], m_XY[nodeIndex7][1], m_XY[nodeIndex7][2]));

		//��һ����
		pPointArray->push_back(osg::Vec3d(m_XY[nodeIndex1][0], m_XY[nodeIndex1][1], m_XY[nodeIndex1][2]));
		pPointArray->push_back(osg::Vec3d(m_XY[nodeIndex2][0], m_XY[nodeIndex2][1], m_XY[nodeIndex2][2]));
		pPointArray->push_back(osg::Vec3d(m_XY[nodeIndex6][0], m_XY[nodeIndex6][1], m_XY[nodeIndex6][2]));
		pPointArray->push_back(osg::Vec3d(m_XY[nodeIndex5][0], m_XY[nodeIndex5][1], m_XY[nodeIndex5][2]));

		//��һ����
		pPointArray->push_back(osg::Vec3d(m_XY[nodeIndex0][0], m_XY[nodeIndex0][1], m_XY[nodeIndex0][2]));
		pPointArray->push_back(osg::Vec3d(m_XY[nodeIndex3][0], m_XY[nodeIndex3][1], m_XY[nodeIndex3][2]));
		pPointArray->push_back(osg::Vec3d(m_XY[nodeIndex7][0], m_XY[nodeIndex7][1], m_XY[nodeIndex7][2]));
		pPointArray->push_back(osg::Vec3d(m_XY[nodeIndex4][0], m_XY[nodeIndex4][1], m_XY[nodeIndex4][2]));

		//��һ����
		pPointArray->push_back(osg::Vec3d(m_XY[nodeIndex0][0], m_XY[nodeIndex0][1], m_XY[nodeIndex0][2]));
		pPointArray->push_back(osg::Vec3d(m_XY[nodeIndex1][0], m_XY[nodeIndex1][1], m_XY[nodeIndex1][2]));
		pPointArray->push_back(osg::Vec3d(m_XY[nodeIndex5][0], m_XY[nodeIndex5][1], m_XY[nodeIndex5][2]));
		pPointArray->push_back(osg::Vec3d(m_XY[nodeIndex4][0], m_XY[nodeIndex4][1], m_XY[nodeIndex4][2]));

		//��һ����
		pPointArray->push_back(osg::Vec3d(m_XY[nodeIndex2][0], m_XY[nodeIndex2][1], m_XY[nodeIndex2][2]));
		pPointArray->push_back(osg::Vec3d(m_XY[nodeIndex3][0], m_XY[nodeIndex3][1], m_XY[nodeIndex3][2]));
		pPointArray->push_back(osg::Vec3d(m_XY[nodeIndex7][0], m_XY[nodeIndex7][1], m_XY[nodeIndex7][2]));
		pPointArray->push_back(osg::Vec3d(m_XY[nodeIndex6][0], m_XY[nodeIndex6][1], m_XY[nodeIndex6][2]));
	}

	osg::ref_ptr<osg::Vec4dArray> pointColorArray = new osg::Vec4dArray;
	pointColorArray->push_back(osg::Vec4d(0.2, 0.2, 0.2, 1.0));

	geom->setVertexArray(pPointArray.get());
	geom->setColorArray(pointColorArray.get());
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);

	geom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, pPointArray->size()));
	sameGeode->addDrawable(geom.get());

	sameGeode->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
	sameGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
	osg::PolygonMode *pLolyTotalMode = new osg::PolygonMode();
	pLolyTotalMode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
	sameGeode->getOrCreateStateSet()->setAttribute(pLolyTotalMode);
	sameGeode->getOrCreateStateSet()->setAttributeAndModes(pLolyTotalMode, osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON);

	m_pointLineGroup->addChild(sameGeode);
}

/*******************************************************************************************************************/
//function:���������ʷֵ�
void ModelingSubdivision::drawSubdivisionGridPoints()
{
	osg::ref_ptr<osg::Geode> sameGeode = new osg::Geode;
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	osg::ref_ptr<osg::Vec3dArray> pPointArray = new osg::Vec3dArray;
			
	for (int k = 0; k < m_ZVec.size(); k++)
	{
		for (int i = 0; i < m_XVec.size(); i++)
		{
			for (int j = 0; j < m_YVec.size(); j++)
			{
				pPointArray->push_back(osg::Vec3d(m_XVec[i], m_YVec[j], m_ZVec[k]));
			}
		}
	}
	
	osg::ref_ptr<osg::Vec4dArray> pointColorArray = new osg::Vec4dArray;
	pointColorArray->push_back(osg::Vec4d(1,0,0,1.0));

	geom->setVertexArray(pPointArray.get());
	geom->setColorArray(pointColorArray.get());
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);
	
	geom->addPrimitiveSet(new osg::DrawArrays(GL_POINTS, 0, pPointArray->size()));
	sameGeode->addDrawable(geom.get());

	osg::ref_ptr <osg::Point> ptSize = new osg::Point;
	ptSize->setSize(2);
	sameGeode->getOrCreateStateSet()->setAttributeAndModes(ptSize.get(), osg::StateAttribute::ON);
	sameGeode->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
	sameGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);

	m_pointLineGroup->addChild(sameGeode);
}