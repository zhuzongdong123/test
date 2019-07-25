#pragma once
#include <QtWidgets/QWidget>
#include "3ddisplay/ViewerWidget3d.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include <QDebug>
#include <set>

class ModelingSubdivision : public ViewerWidget3d
{
	Q_OBJECT
public:
	ModelingSubdivision(QWidget* parent);
	~ModelingSubdivision() 
	{
		m_XL.clear();
		m_YL.clear();
		m_ZL.clear();
		m_XVec.clear();
		m_YVec.clear();
		m_ZVec.clear();

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
	}

	void doModel();  //��ģ�ʷ�
	void clearModel();
	void updateModel();//���½�ģģ�ͽṹ
	void drawSubdivisionGridPoints();//�����ʷֵ�
	void drawSubdivisionGridLine(); //�����ʷ���
	void modelBuilding();
	bool getCreatFlag() { return m_isCreate; }

	std::vector<double> getXLVector() { return m_XL; }
	std::vector<double> getYLVector() { return m_YL; }
	std::vector<double> getZLVector() { return m_ZL; }

	void setXLVector(std::vector<double> vXLVec)
	{
		m_XL.clear();
		for (unsigned int i = 0; i < vXLVec.size(); i++)
		{
			m_XL.push_back(vXLVec[i]);
		}
	}

	void setYLVector(std::vector<double> vYLVec)
	{
		m_YL.clear();
		for (unsigned int i = 0; i < vYLVec.size(); i++)
		{
			m_YL.push_back(vYLVec[i]);
		}
	}

	void setZLVector(std::vector<double> vZLVec)
	{
		m_ZL.clear();
		for (unsigned int i = 0; i < vZLVec.size(); i++)
		{
			m_ZL.push_back(vZLVec[i]);
		}
	}

	void initModelParameter(int inverXBeg, int inverXEnd, int inverYBeg, int inverYEnd, int tunnelCaviXBeg,
		int tunnelCaviXEnd, int tunnelCaviYBeg, int tunnelCaviYEnd, int tunnelZBeg, int tunnelZEnd)
	{
		m_inverXBeg = inverXBeg; //�����������x���
		m_inverXEnd = inverXEnd; //�����������x�յ�
		m_inverYBeg = inverYBeg; //�����������y���
		m_inverYEnd = inverYEnd; //�����������y�յ�

		m_tunnelCavityXBegin = tunnelCaviXBeg;
		m_tunnelCavityXEnd = tunnelCaviXEnd;

		m_tunnelCavityYBegin = tunnelCaviYBeg;
		m_tunnelCavityYEnd = tunnelCaviYEnd;

		m_tunnelForZBegin = tunnelZBeg;
		m_tunnelForZEnd = tunnelZEnd;
	}

	void initMeasurePointParam(int xMeasureBeg, int xMeasureEnd, int yMeasureBeg, int yMeasureEnd)
	{
		m_MeaPointXYIndexVec.clear();
		
		bool invertPointPosIndex = false;
		for (int i = xMeasureEnd; i >= xMeasureBeg; i --)
		{
			if (!invertPointPosIndex)
			{
				for (int j = yMeasureBeg; j <= yMeasureEnd; j++)
				{
					m_MeaPointXYIndexVec.push_back(osg::Vec2(i, j));
				}
				invertPointPosIndex = true;
			}
			else
			{
				for (int j = yMeasureEnd; j >= yMeasureBeg; j--)
				{
					m_MeaPointXYIndexVec.push_back(osg::Vec2(i, j));
				}
				invertPointPosIndex = false;
			}
		}
	}

	std::vector<osg::Vec2> getMeasXYIndexVec() { return m_MeaPointXYIndexVec; } //�����������Ӧ��X�����ģ������

	int getElectroCircleNum() { return m_electroCircleNum; } //����缫Ȧ��
	int getXDirNodeCount() { return m_nodeXCount; }
	int getYDirNodeCount() { return m_nodeYCount; }
	int getZDirNodeCount() { return m_nodeZCount; }

	int getXDirEdgeCount(){return m_xDirEdgeCount;}
	int getYDirEdgeCount(){return m_yDirEdgeCount;}
	int getZDirEdgeCount(){return m_zDirEdgeCount;}

	int getTotalNodeCount() { return m_ND; }
	int getTotalGridCount() { return m_gridNum; }
	int** getTotalGridIndex() { return m_I4; }
	double** getTotalNodePos() { return m_XY; }

	int getTunnelCavityXBegin() { return m_tunnelCavityXBegin; } //�����ǻx���
	int getTunnelCavityXEnd() { return m_tunnelCavityXEnd; } //�����ǻx�յ�
	int getTunnelCavityYBegin() { return m_tunnelCavityYBegin; } //�����ǻy���
	int getTunnelCavityYEnd() { return m_tunnelCavityYEnd; }//�����ǻy�յ�
	
	int getInvertionXBeg(){return m_inverXBeg;}
	int getInvertionXEnd(){return m_inverXEnd;}
	int getInvertionYBeg(){return m_inverYBeg;}
	int getInvertionYEnd(){return m_inverYEnd;}

	int getTunnelForZBeg() { return m_tunnelForZBegin; }
	int getTunnelForZEnd() { return m_tunnelForZEnd; }

public slots:
       void modelSubBodyHidden();
	   void modelSubBodyDisplay();
private:
	bool m_isCreate;

	std::vector<double> m_XL;//ģ��x����ı߳���Ϣ
	std::vector<double> m_YL;//ģ��y����ı߳���Ϣ
	std::vector<double> m_ZL;//ģ��z����ı߳���Ϣ
	std::vector<double> m_XVec;//x���򶥵��λ��
	std::vector<double> m_YVec;//y���򶥵��λ��
	std::vector<double> m_ZVec;//z���򶥵��λ��
	std::vector<osg::Vec2> m_MeaPointXYIndexVec; //�����������Ӧ��X�����ģ������
	
    //ǰ�벿�ֱ�������缫�Ľڵ��Ӧ���ʷ������������
	//��벿�ֱ���ÿһȦ����缫��λ������Ӧ���ʷ����������
	
	double** m_XY; //ÿ���ڵ����������
	int** m_I4; //���е�Ԫ���õĶ�������

	int m_nodeXCount; //ģ��x����Ľڵ㳤��
	int m_nodeYCount; //ģ��y����Ľڵ㳤��
	int m_nodeZCount; //ģ��z����Ľڵ㳤��

	int m_xDirEdgeCount; //x����߳�����
	int m_yDirEdgeCount; //y����߳�����
	int m_zDirEdgeCount; //z����߳�����

	int m_electroCircleNum; //����缫��Ȧ��
	int m_gridNum;//����Ԫ����
	int m_ND;//����ڵ�����
	int m_tunnelCavityXBegin; //�����ǻx���
	int m_tunnelCavityXEnd; //�����ǻx�յ�
	int m_tunnelCavityYBegin; //�����ǻy���
	int m_tunnelCavityYEnd; //�����ǻy�յ�

	int m_inverXBeg; //��������x���
	int m_inverXEnd; //��������x�յ�
	int m_inverYBeg; //��������y���
	int m_inverYEnd; //��������y�յ�

	int m_XElectrodCount; //x��������缫�ĸ���
	int m_YElectrodCount; //y��������缫�ĸ���

	int m_tunnelForZBegin; //���Ԥ������Z���
	int m_tunnelForZEnd; //���Ԥ������Z�յ�

	osg::ref_ptr<osg::Group> m_pointLineGroup;
	osg::ref_ptr<osg::Group> m_subBodyGroup;
};
