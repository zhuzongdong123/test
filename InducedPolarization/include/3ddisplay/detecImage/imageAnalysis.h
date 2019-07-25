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

		  imageDirType m_imageDirType; //�������ֲ�ͬ�ķ������Ƭ��Ϣչʾ����
		  
		  int m_currentImageWidth;
		  int m_currentImageHeight;
	      
		  osg::Vec4d** m_facePointsColor; //����ÿ��ͼƬ������������Ϣ
		  osg::ref_ptr<osg::Image> m_pXImage; //չʾx���淽��ͼ��������Ϣ
		  osg::ref_ptr<osg::Image> m_pYImage; //չʾy���淽��ͼ��������Ϣ
		  osg::ref_ptr<osg::Image> m_pZImage; //չʾz���淽��ͼ��������Ϣ
	};
}

