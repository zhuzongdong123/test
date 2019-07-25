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

	void doModel();  //建模剖分
	void clearModel();
	void updateModel();//更新建模模型结构
	void drawSubdivisionGridPoints();//绘制剖分点
	void drawSubdivisionGridLine(); //绘制剖分线
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
		m_inverXBeg = inverXBeg; //隧道反演区域x起点
		m_inverXEnd = inverXEnd; //隧道反演区域x终点
		m_inverYBeg = inverYBeg; //隧道反演区域y起点
		m_inverYEnd = inverYEnd; //隧道反演区域y终点

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

	std::vector<osg::Vec2> getMeasXYIndexVec() { return m_MeaPointXYIndexVec; } //测量点坐标对应的X方向的模型索引

	int getElectroCircleNum() { return m_electroCircleNum; } //供电电极圈数
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

	int getTunnelCavityXBegin() { return m_tunnelCavityXBegin; } //隧道空腔x起点
	int getTunnelCavityXEnd() { return m_tunnelCavityXEnd; } //隧道空腔x终点
	int getTunnelCavityYBegin() { return m_tunnelCavityYBegin; } //隧道空腔y起点
	int getTunnelCavityYEnd() { return m_tunnelCavityYEnd; }//隧道空腔y终点
	
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

	std::vector<double> m_XL;//模型x方向的边长信息
	std::vector<double> m_YL;//模型y方向的边长信息
	std::vector<double> m_ZL;//模型z方向的边长信息
	std::vector<double> m_XVec;//x方向顶点的位置
	std::vector<double> m_YVec;//y方向顶点的位置
	std::vector<double> m_ZVec;//z方向顶点的位置
	std::vector<osg::Vec2> m_MeaPointXYIndexVec; //测量点坐标对应的X方向的模型索引
	
    //前半部分保存测量电极的节点对应在剖分网格的索引，
	//后半部分保存每一圈供电电极的位置所对应的剖分网格的索引
	
	double** m_XY; //每个节点的三个坐标
	int** m_I4; //所有单元对用的顶点索引

	int m_nodeXCount; //模型x方向的节点长度
	int m_nodeYCount; //模型y方向的节点长度
	int m_nodeZCount; //模型z方向的节点长度

	int m_xDirEdgeCount; //x方向边长个数
	int m_yDirEdgeCount; //y方向边长个数
	int m_zDirEdgeCount; //z方向边长个数

	int m_electroCircleNum; //供电电极的圈数
	int m_gridNum;//网格单元总数
	int m_ND;//网格节点总数
	int m_tunnelCavityXBegin; //隧道空腔x起点
	int m_tunnelCavityXEnd; //隧道空腔x终点
	int m_tunnelCavityYBegin; //隧道空腔y起点
	int m_tunnelCavityYEnd; //隧道空腔y终点

	int m_inverXBeg; //反演区域x起点
	int m_inverXEnd; //反演区域x终点
	int m_inverYBeg; //反演区域y起点
	int m_inverYEnd; //反演区域y终点

	int m_XElectrodCount; //x方向测量电极的个数
	int m_YElectrodCount; //y方向测量电极的个数

	int m_tunnelForZBegin; //隧道预报区域Z起点
	int m_tunnelForZEnd; //隧道预报区域Z终点

	osg::ref_ptr<osg::Group> m_pointLineGroup;
	osg::ref_ptr<osg::Group> m_subBodyGroup;
};
