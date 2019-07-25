#pragma once
#define GLUT_DISABLE_ATEXIT_HACK 
#include <stdlib.h>
#include <string.h>
#include "stdio.h"
#include "math.h"
#include <osg/Geode>
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Array>
#include "3ddisplay/ViewerWidget3d.h"

namespace osgEngine
{
	//a2fVertexOffset lists the positions, relative to vertex0, of each of the 8 vertices of a cube      立方体8个顶点
	//  立方体8个顶点
	static const float a2fVertexOffset[8][3] =
	{
		{0.0, 0.0, 0.0},{1.0, 0.0, 0.0},{1.0, 1.0, 0.0},{0.0, 1.0, 0.0},
		{0.0, 0.0, 1.0},{1.0, 0.0, 1.0},{1.0, 1.0, 1.0},{0.0, 1.0, 1.0}
	};
 
	//a2iEdgeConnection lists the index of the endpoint vertices for each of the 12 edges of the cube    立方体12个边
	static const int a2iEdgeConnection[12][2] = 
	{
		{0,1}, {1,2}, {2,3}, {3,0},
		{4,5}, {5,6}, {6,7}, {7,4},
		{0,4}, {1,5}, {2,6}, {3,7}
	};
 
	//a2fEdgeDirection lists the direction vector (vertex1-vertex0) for each edge in the cube    立方体 12个边的方向向量
	static const float a2fEdgeDirection[12][3] =
	{
		{1.0, 0.0, 0.0},{0.0, 1.0, 0.0},{-1.0, 0.0, 0.0},{0.0, -1.0, 0.0},
		{1.0, 0.0, 0.0},{0.0, 1.0, 0.0},{-1.0, 0.0, 0.0},{0.0, -1.0, 0.0},
		{0.0, 0.0, 1.0},{0.0, 0.0, 1.0},{ 0.0, 0.0, 1.0},{0.0,  0.0, 1.0}
	};

	class marchingCubeDraw
	{
	public:
		marchingCubeDraw(float vStepRepo)
		{
			m_pBaseDraw = NULL;
			m_detectData = NULL;
			m_samePointArray = new osg::Vec3dArray;
			m_samePointNormalArray = new osg::Vec3dArray;
			m_samePointColorArray = new osg::Vec4dArray;
					
			m_Nx = 0;
			m_Ny = 0;
			m_Nz = 0;
			m_xMin = 0;
			m_yMin = 0;
			m_zMin = 0;
			m_xMax = 0;
			m_yMax = 0;
			m_zMax = 0;

			m_minSpeed = 0.0;
			m_maxSpeed = 0.0;

			m_stepRepo = vStepRepo;
			m_firstValue = 0.0;
			m_twoValue = 0.0;
		}
		~marchingCubeDraw()
		{
			if (NULL != m_detectData)
			{
				deleteArray3(m_detectData, m_Nx, m_Ny, m_Nz);
			}
		}

		void clearData()
		{
			
		}

		inline void deleteArray3(float ***p3, int row, int col, int cha) {
			if (p3 == NULL)
				return;
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					delete[]p3[i][j];
					p3[i][j] = NULL;
				}
				delete[]p3[i];
				p3[i] = NULL;
			}
			delete[]p3;
			p3 = NULL;
		}

		void initData(int xMin, int xMax, int yMin, int yMax, 
			int zMin, int zMax,double minSpeed,double maxSpeed, osg::Vec4dArray* tmpAllPointsArray)
		{
			if (NULL != m_detectData)
			{
				deleteArray3(m_detectData, m_Nz, m_Ny, m_Nx);
			}
			m_xMin = xMin;
			m_yMin = yMin;
			m_zMin = zMin;

			m_xMax = xMax;
			m_yMax = yMax;
			m_zMax = zMax;
			
			m_minSpeed = minSpeed;
			m_maxSpeed = maxSpeed;

			int xRow = (m_xMax - m_xMin) / m_stepRepo+1;
			int yRow = (m_yMax - m_yMin) / m_stepRepo+1;
			int zRow = (m_zMax - m_zMin) / m_stepRepo+1;

			if (xRow < 0 || yRow < 0 || zRow < 0)
			{
				m_stepRepo = 1.0;
				printf("the display detect data load not success!");
				return ;
			}
			m_Nx = xRow /*+ 2*/; //加2为了将边界的值也包含到等值面中
			m_Ny = yRow/* + 2*/; //加2为了将边界的值也包含到等值面中
			m_Nz = zRow/* + 2*/; //加2为了将边界的值也包含到等值面中
			
			m_detectData = new float**[m_Nz];
			for (int i = 0; i < m_Nz; i++)
			{
				m_detectData[i] = new float*[m_Ny];
				for (int j = 0; j < m_Ny; j++)
				{
					m_detectData[i][j] = new float[m_Nx];
					memset(m_detectData[i][j],0,sizeof(float)*m_Nx);
				}
			}
			
			for (int i = 0; i < tmpAllPointsArray->size(); i++)
			{
				float xPos = (*tmpAllPointsArray)[i].x();
				float yPos = (*tmpAllPointsArray)[i].y();
				float zPos = (*tmpAllPointsArray)[i].z();
				int xStep = (int)((xPos - m_xMin) / m_stepRepo) /*+ 1*/;//等值面展示，体展示再启用+1
				int yStep = (int)((yPos - m_yMin) / m_stepRepo)/* + 1*/;
				int zStep = (int)((zPos - m_zMin) / m_stepRepo)/* + 1*/;
				m_detectData[zStep][yStep][xStep] = (*tmpAllPointsArray)[i].w();
			}
		}
		
		//fGetOffset finds the approximate point of intersection of the surface
		// between two points with the values fValue1 and fValue2
		float fGetOffset(float fValue1, float fValue2, float fValueDesired)    
		{
			GLdouble fDelta = fValue2 - fValue1;
			if(fDelta == 0.0)
			{
				return 0.5;
			}
			return (fValueDesired - fValue1)/fDelta;
		}
 
		//向量标准化
		void vNormalizeVector(osg::Vec3d &rfVectorResult, osg::Vec3d &rfVectorSource)  
		{
			float fOldLength;
			float fScale;
 
			fOldLength = sqrtf((rfVectorSource.x() * rfVectorSource.x()) + (rfVectorSource.y() * rfVectorSource.y()) + (rfVectorSource.z() * rfVectorSource.z()) );
			if(fOldLength == 0.0)
			{
				rfVectorResult.x() = rfVectorSource.x();
				rfVectorResult.y() = rfVectorSource.y();
				rfVectorResult.z() = rfVectorSource.z();
			}
			else
			{
				fScale = 1.0/fOldLength;
				rfVectorResult.x() = rfVectorSource.x() * fScale;
				rfVectorResult.y() = rfVectorSource.y() * fScale;
				rfVectorResult.z() = rfVectorSource.z() * fScale;
			}
		}
 
		//vGetNormal() finds the gradient of the scalar field at a point
		//This gradient can be used as a very accurate vertx normal for lighting calculations
		void vGetNormal(osg::Vec3d &rfNormal, float fX, float fY, float fZ)                   // 计算 数据场一点的梯度
		{
			  if (  fX > 1 && fX < m_Nx-1 && fY>1 && fY< m_Ny-1  &&  fZ > 1 && fZ < m_Nz-1 )
			  {
				rfNormal.x() = (float)m_detectData[(int)fZ-1][ (int)fY][ (int)fX] - (float)m_detectData[(int)fZ+1][ (int)fY] [(int)fX];
				rfNormal.y() = (float)m_detectData[(int)fZ] [(int)fY-1] [(int)fX] - (float)m_detectData[(int)fZ][(int) fY+1][(int)fX];
				rfNormal.z() = (float)m_detectData[(int)fZ][(int)fY][(int) fX-1] - (float)m_detectData[(int)fZ][ (int)fY][ (int)fX+1];
				
				vNormalizeVector(rfNormal, rfNormal);
			  }
			  else if (fX>=0 && fX < m_Nx - 1 && fY>=0 && fY< m_Ny - 1 && fZ >= 0 && fZ < m_Nz - 1)
			  {
				  rfNormal.x() = (float)m_detectData[(int)fZ][(int)fY][(int)fX] - (float)m_detectData[(int)fZ + 1][(int)fY][(int)fX];
				  rfNormal.y() = (float)m_detectData[(int)fZ][(int)fY][(int)fX] - (float)m_detectData[(int)fZ][(int)fY + 1][(int)fX];
				  rfNormal.z() = (float)m_detectData[(int)fZ][(int)fY][(int)fX] - (float)m_detectData[(int)fZ][(int)fY][(int)fX + 1];
				  vNormalizeVector(rfNormal, rfNormal);
			  }
		}

		void clearLastPoints()
		{
			if (NULL != m_samePointArray)
			    m_samePointArray->clear();
			if (NULL != m_samePointNormalArray)
			    m_samePointNormalArray->clear();
			if (NULL != m_samePointColorArray)
			    m_samePointColorArray->clear();
		}

		void clearProjectScene()
		{
			clearLastPoints();
			if (NULL == m_detectData)
				return;
			for (int i = 0; i < m_Nz; i++)
			{
				for (int j = 0; j < m_Ny; j++)
				{
					delete[]m_detectData[i][j];
					m_detectData[i][j] = NULL;
				}
				delete[]m_detectData[i];
				m_detectData[i] = NULL;
			}
			delete[]m_detectData;
			m_detectData = NULL;
		}

		void setBaseDraw(BaseDraw* pBaseDraw)
		{
			m_pBaseDraw = pBaseDraw;
		}
		void MarchingCubes(float vTargetSpeed);
        void MarchCube(float vTargetSpeed);
		void setStepRepo(float vStepRepo) { m_stepRepo = vStepRepo; }
		void setFirstValue(float vFirstValue) {m_firstValue = vFirstValue;}
		void setTwoValue(float vTwoValue){ m_twoValue = vTwoValue; }
		float getCurrentFirstValue() {return m_firstValue;}
		float getCurrentTwoValue(){ return m_twoValue; }
		osg::ref_ptr<osg::Geode> drawSamesurface();

	private:
		
		unsigned int m_Nx;
		unsigned int m_Ny;
		unsigned int m_Nz;
		int m_xMin;
		int m_yMin;
		int m_zMin;
		int m_xMax;
		int m_yMax;
		int m_zMax;

		float m_stepRepo;
		float m_firstValue;
		float m_twoValue;
		double m_minSpeed;
		double m_maxSpeed;

		BaseDraw* m_pBaseDraw;

		float ***m_detectData;//保存探测数据
		osg::ref_ptr<osg::Vec3dArray> m_samePointArray;
		osg::ref_ptr<osg::Vec3dArray> m_samePointNormalArray;
		osg::ref_ptr<osg::Vec4dArray> m_samePointColorArray;
	};
}
