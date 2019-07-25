#pragma once
#include <osgDB/ReadFile>
#include <osg/Image>
#include <osgText/Text>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <osg/MatrixTransform>

class MyWidgetImaging;

namespace osgEngine
{
	class CImageCreate : public osg::MatrixTransform
	{
	public:
		enum imageDirType{xdirect, ydirect, zdirect};

		CImageCreate()
		{
			m_currentImageWidth = 0;
			m_currentImageHeight = 0;

			m_pXImage = NULL;
			m_pYImage = NULL;
			m_pZImage = NULL;
			m_facePointsColor = NULL;
		}

		~CImageCreate()
		{
			if (NULL != m_facePointsColor)
			{
				for (int i = 0; i < m_currentImageHeight; i++)
				{
					delete []m_facePointsColor[i];
				}
				delete m_facePointsColor;
			}
		}

		osg::ref_ptr<osg::Geode> createImage(imageDirType vDirType, int imagePos, MyWidgetImaging* pWidgetImage);
		osg::ref_ptr<osg::Geode> createBodyImage(imageDirType vDirType, int imagePos, MyWidgetImaging* pWidgetImage);
		void getImgePointColor(int vImagePos, imageDirType vDirType, MyWidgetImaging* pWidgetImage);
		
	private:

		  imageDirType m_imageDirType; //用于区分不同的方向的切片信息展示功能
		  
		  int m_currentImageWidth;
		  int m_currentImageHeight;
	      
		  osg::Vec4d** m_facePointsColor; //保存每张图片的切面数据信息
		  osg::ref_ptr<osg::Image> m_pXImage; //展示x切面方向图像切面信息
		  osg::ref_ptr<osg::Image> m_pYImage; //展示y切面方向图像切面信息
		  osg::ref_ptr<osg::Image> m_pZImage; //展示z切面方向图像切面信息
	};
}

