#include "detecImage/imageAnalysis.h"
#include <math.h>
#include "MyWidgetImaging.h"

namespace osgEngine
{
	/***************************************************************************************************************************************************************************/
	//function
	void CImageCreate::getImgePointColor(int vImagePos, imageDirType vDirType, MyWidgetImaging* pWidgetImage)
	{
		osg::ref_ptr<osg::Vec4dArray> pPointsArray = pWidgetImage->getPointsArray();
		
		if (NULL != m_facePointsColor)
		{
			for (int i = 0; i < m_currentImageHeight; i++)
			{
				delete[]m_facePointsColor[i];

			}
			delete m_facePointsColor;
			m_facePointsColor = NULL;
		}
		
		switch (vDirType)
		{
		case xdirect:
			m_currentImageWidth = pWidgetImage->getYMax() - pWidgetImage->getYMin();
			m_currentImageHeight = pWidgetImage->getZMax() - pWidgetImage->getZMin();
			break;
		case ydirect:
			m_currentImageWidth = pWidgetImage->getXMax() - pWidgetImage->getXMin();
			m_currentImageHeight = pWidgetImage->getZMax() - pWidgetImage->getZMin();
			break;
		case zdirect:
			m_currentImageWidth = pWidgetImage->getYMax() - pWidgetImage->getYMin();
			m_currentImageHeight = pWidgetImage->getXMax() - pWidgetImage->getXMin();
			break;
		default:
			break;
		}

		m_facePointsColor = new osg::Vec4d*[m_currentImageHeight];
		for (int i = 0; i < m_currentImageHeight; i++)
		{
			m_facePointsColor[i] = new osg::Vec4d[m_currentImageWidth];
			memset(m_facePointsColor[i],0, m_currentImageWidth*sizeof(osg::Vec4d));
		}

		int xImageMinPos = pWidgetImage->getXMin();
		int yImageMinPos = pWidgetImage->getYMin();
		int zImageMinPos = pWidgetImage->getZMin();

		if (vDirType == xdirect)
		{
			for (int m = 0; m < pPointsArray->size(); m++)
			{
				if (fabs((*pPointsArray)[m].x() - vImagePos) < 0.01)
				{
					osg::Vec4d color = pWidgetImage->getBaseDraw()->getPointsColor((*pPointsArray)[m].w(),
						pWidgetImage->getMinSpeed(), 1000);
					
					int yImagePos = (*pPointsArray)[m].y();
					int zImagePos = (*pPointsArray)[m].z();

					if (zImagePos - (int)zImageMinPos >= m_currentImageHeight || yImagePos - (int)yImageMinPos >= m_currentImageWidth)
					{
						continue;
					}
					m_facePointsColor[zImagePos - (int)zImageMinPos][yImagePos - (int)yImageMinPos] = color;
				}
			}
		}
		else if (vDirType == ydirect)
		{
			for (int m = 0; m < pPointsArray->size(); m++)
			{
				if (fabs((*pPointsArray)[m].y() - vImagePos) < 0.01)
				{
					osg::Vec4d color = pWidgetImage->getBaseDraw()->getPointsColor((*pPointsArray)[m].w(), 
						pWidgetImage->getMinSpeed(), 1000);

					int xImagePos = (*pPointsArray)[m].x();
					int zImagePos = (*pPointsArray)[m].z();

					if (zImagePos - (int)zImageMinPos >= m_currentImageHeight || xImagePos - (int)xImageMinPos >= m_currentImageWidth)
					{
						continue;
					}
					m_facePointsColor[zImagePos - (int)zImageMinPos][xImagePos - (int)xImageMinPos] = color;
				}
			}
		}
		else if (vDirType == zdirect)
		{
			for (int m = 0; m < pPointsArray->size(); m++)
			{
				if (fabs((*pPointsArray)[m].z() - vImagePos) < 0.01)
				{
					osg::Vec4d color = pWidgetImage->getBaseDraw()->getPointsColor((*pPointsArray)[m].w(), 
						pWidgetImage->getMinSpeed(), 1000);

					int yImagePos = (*pPointsArray)[m].y();
					int xImagePos = (*pPointsArray)[m].x();

					if (yImagePos - (int)yImageMinPos >= m_currentImageWidth || xImagePos - (int)xImageMinPos >= m_currentImageHeight)
					{
						continue;
					}
					m_facePointsColor[xImagePos - (int)xImageMinPos][yImagePos - (int)yImageMinPos] = color;
				}
			}
		}		
	}

	/*******************************************************************************************************************************************************************************/
	//function : 显示每个切面的展示图片
	osg::ref_ptr<osg::Geode> CImageCreate::createImage(imageDirType vDirType, int imagePos, MyWidgetImaging* pWidgetImage)
	{
		getImgePointColor(imagePos, vDirType, pWidgetImage);
		
		osg::ref_ptr<osg::Geode> geode = new osg::Geode();
		osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
		osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
		
		int xMin = pWidgetImage->getXMin();
		int yMin = pWidgetImage->getYMin();
		int zMin = pWidgetImage->getZMin();
		int xMax = pWidgetImage->getXMax();
		int yMax = pWidgetImage->getYMax();
		int zMax = pWidgetImage->getZMax();
		
		int imageSizeX = xMax - xMin;
		int imageSizeY = yMax - yMin;
		int imageSizeZ = zMax - zMin;
		
		osg::Vec4* dataPtr = NULL;
		switch(vDirType)
		{
		case xdirect:
			if (NULL == m_pXImage)
			{
				m_pXImage = new osg::Image;
				m_pXImage->setDataVariance(osg::Object::DYNAMIC);
				m_pXImage->setInternalTextureFormat(GL_RGBA);
				m_pXImage->allocateImage(imageSizeY, imageSizeZ, 1, GL_RGBA, GL_FLOAT/*GL_UNSIGNED_BYTE*/);
			}
			else
			{
				m_pXImage->setDataVariance(osg::Object::DYNAMIC);
				m_pXImage->setInternalTextureFormat(GL_RGBA);
				m_pXImage->allocateImage(imageSizeY, imageSizeZ, 1, GL_RGBA, GL_FLOAT/*GL_UNSIGNED_BYTE*/);
			}
			dataPtr = (osg::Vec4*)(m_pXImage->data());
			
			for (int i = 0; i < imageSizeZ; i++)
			{
				for(int j = 0; j < imageSizeY; j++)
				{			  
					osg::Vec4d color = m_facePointsColor[i][j];
					*dataPtr++ = color;
				}
			}
			
			vertices->push_back(osg::Vec3(imagePos,yMin,zMin));
			vertices->push_back(osg::Vec3(imagePos,yMin,zMax));
			vertices->push_back(osg::Vec3(imagePos,yMax,zMax));
			vertices->push_back(osg::Vec3(imagePos,yMax,zMin));
			break;
		case ydirect:
			if (NULL == m_pYImage)
			{
				m_pYImage = new osg::Image;
				m_pYImage->setDataVariance(osg::Object::DYNAMIC);
				m_pYImage->setInternalTextureFormat(GL_RGBA);
				m_pYImage->allocateImage(imageSizeX, imageSizeZ, 1, GL_RGBA, GL_FLOAT/*GL_UNSIGNED_BYTE*/);
			}
			else
			{
				m_pYImage->setDataVariance(osg::Object::DYNAMIC);
				m_pYImage->setInternalTextureFormat(GL_RGBA);
				m_pYImage->allocateImage(imageSizeX, imageSizeZ, 1, GL_RGBA, GL_FLOAT/*GL_UNSIGNED_BYTE*/);
			}
			
			dataPtr = (osg::Vec4*)(m_pYImage->data());

			for (int i = 0; i < imageSizeZ; i++)
			{
				for (int j = 0; j < imageSizeX; j++)
				{
					osg::Vec4d color = m_facePointsColor[i][j];
					*dataPtr++ = color;
				}
			}

			vertices->push_back(osg::Vec3(xMin,imagePos,zMin));
			vertices->push_back(osg::Vec3(xMin,imagePos,zMax));
			vertices->push_back(osg::Vec3(xMax,imagePos,zMax));
			vertices->push_back(osg::Vec3(xMax,imagePos,zMin));
			break;
		case zdirect:
			if (NULL == m_pZImage)
			{
				m_pZImage = new osg::Image;
				m_pZImage->setDataVariance(osg::Object::DYNAMIC);
				m_pZImage->setInternalTextureFormat(GL_RGBA);
				m_pZImage->allocateImage(imageSizeY, imageSizeX, 1, GL_RGBA, GL_FLOAT/*GL_UNSIGNED_BYTE*/);
			}
			else
			{
				m_pZImage->setDataVariance(osg::Object::DYNAMIC);
				m_pZImage->setInternalTextureFormat(GL_RGBA);
				m_pZImage->allocateImage(imageSizeY, imageSizeX, 1, GL_RGBA, GL_FLOAT/*GL_UNSIGNED_BYTE*/);
			}
			
			dataPtr = (osg::Vec4*)(m_pZImage->data());

			for (int i = 0; i < imageSizeX; i++)
			{
				for (int j = 0; j < imageSizeY; j++)
				{
					osg::Vec4d color = m_facePointsColor[i][j];
					*dataPtr++ = color;
				}
			}

			vertices->push_back(osg::Vec3(xMin, yMin, imagePos));
			vertices->push_back(osg::Vec3(xMax, yMin, imagePos));
			vertices->push_back(osg::Vec3(xMax, yMax, imagePos));
			vertices->push_back(osg::Vec3(xMin, yMax, imagePos));
			break;
		default:
			break;
		}

		//设置二维纹理的参数和WRAP方式
		osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
		texture->setWrap(osg::Texture2D::WRAP_S,osg::Texture2D::REPEAT);
		texture->setWrap(osg::Texture2D::WRAP_T,osg::Texture2D::REPEAT);
		texture->setWrap(osg::Texture2D::WRAP_R,osg::Texture2D::REPEAT);
		texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
		texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
		texture->setSourceType(GL_FLOAT);
		texture->setShadowComparison(true);
		texture->setShadowTextureMode(osg::Texture2D::LUMINANCE);
		
		switch(vDirType)
		{
		case xdirect:
			texture->setImage(m_pXImage);
			break;
		case ydirect:
			texture->setImage(m_pYImage);
			break;
		case zdirect:
			texture->setImage(m_pZImage);
			break;
		}
		
		osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();//定义一个颜色数组颜色
		c->push_back(osg::Vec4(1.0, 1.0, 1.0, 1.0));//数组的四个参数分别为RGBA，其中A表示透明度		
		//osg::ref_ptr<osg::Vec4Array> normalArray = new osg::Vec4Array();//定义一个颜色数组颜色
		//normalArray->push_back(osg::Vec4(-1.0, 0.0, 0.0,1.0));//
		//normalArray->push_back(osg::Vec4(-1.0, 0.0, 0.0,1.0));//
		//normalArray->push_back(osg::Vec4(-1.0, 0.0, 0.0,1.0));//
		//normalArray->push_back(osg::Vec4(-1.0, 0.0, 0.0,1.0));//

		osg::ref_ptr<osg::Vec2Array> texcoords =new osg::Vec2Array;
		texcoords->push_back(osg::Vec2(0,0));
		texcoords->push_back(osg::Vec2(0,1));
		texcoords->push_back(osg::Vec2(1,1));
		texcoords->push_back(osg::Vec2(1,0));
		geom->setVertexArray(vertices.get());
		geom->setColorArray(c.get());
		geom->setColorBinding(osg::Geometry::BIND_OVERALL);
		geom->setTexCoordArray(0,texcoords.get());
		/*geom->setNormalArray(normalArray.get());
		geom->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);*/

		geom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS,0,4));
		geode->addDrawable(geom.get());
		osg::StateSet* stateset = geom->getOrCreateStateSet();
		
		stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
		/*stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);*/
		stateset->setTextureAttribute(0,texture.get(),osg::StateAttribute::OVERRIDE);
		stateset->setTextureMode(0,GL_TEXTURE_2D,osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE);
		return geode.release();
	}

	/*******************************************************************************************************************************************************************************/
	//function : 显示体切面整体展示
	osg::ref_ptr<osg::Geode> CImageCreate::createBodyImage(imageDirType vDirType, int imagePos, MyWidgetImaging* pWidgetImage)
	{
		getImgePointColor(imagePos, vDirType, pWidgetImage);

		osg::ref_ptr<osg::Geode> geode = new osg::Geode();
		osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
		osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;

		osg::ref_ptr<osg::Image> pImage = NULL; //展示x切面方向图像切面信息

		int xMin = pWidgetImage->getXMin();
		int yMin = pWidgetImage->getYMin();
		int zMin = pWidgetImage->getZMin();
		int xMax = pWidgetImage->getXMax();
		int yMax = pWidgetImage->getYMax();
		int zMax = pWidgetImage->getZMax();

		int imageSizeX = xMax - xMin;
		int imageSizeY = yMax - yMin;
		int imageSizeZ = zMax - zMin;

		osg::Vec4* dataPtr = NULL;
		switch (vDirType)
		{
		case xdirect:
			if (NULL == pImage)
			{
				pImage = new osg::Image;
				pImage->setDataVariance(osg::Object::DYNAMIC);
				pImage->setInternalTextureFormat(GL_RGBA);
				pImage->allocateImage(imageSizeY, imageSizeZ, 1, GL_RGBA, GL_FLOAT/*GL_UNSIGNED_BYTE*/);
			}
			dataPtr = (osg::Vec4*)(pImage->data());

			for (int i = 0; i < imageSizeZ; i++)
			{
				for (int j = 0; j < imageSizeY; j++)
				{
					osg::Vec4d color = m_facePointsColor[i][j];
					*dataPtr++ = color;
				}
			}

			vertices->push_back(osg::Vec3(imagePos, yMin, zMin));
			vertices->push_back(osg::Vec3(imagePos, yMin, zMax));
			vertices->push_back(osg::Vec3(imagePos, yMax, zMax));
			vertices->push_back(osg::Vec3(imagePos, yMax, zMin));
			break;
		case ydirect:
			if (NULL == pImage)
			{
				pImage = new osg::Image;
				pImage->setDataVariance(osg::Object::DYNAMIC);
				pImage->setInternalTextureFormat(GL_RGBA);
				pImage->allocateImage(imageSizeX, imageSizeZ, 1, GL_RGBA, GL_FLOAT/*GL_UNSIGNED_BYTE*/);
			}

			dataPtr = (osg::Vec4*)(pImage->data());

			for (int i = 0; i < imageSizeZ; i++)
			{
				for (int j = 0; j < imageSizeX; j++)
				{
					osg::Vec4d color = m_facePointsColor[i][j];
					*dataPtr++ = color;
				}
			}

			vertices->push_back(osg::Vec3(xMin, imagePos, zMin));
			vertices->push_back(osg::Vec3(xMin, imagePos, zMax));
			vertices->push_back(osg::Vec3(xMax, imagePos, zMax));
			vertices->push_back(osg::Vec3(xMax, imagePos, zMin));
			break;
		case zdirect:
			if (NULL == pImage)
			{
				pImage = new osg::Image;
				pImage->setDataVariance(osg::Object::DYNAMIC);
				pImage->setInternalTextureFormat(GL_RGBA);
				pImage->allocateImage(imageSizeY, imageSizeX, 1, GL_RGBA, GL_FLOAT/*GL_UNSIGNED_BYTE*/);
			}

			dataPtr = (osg::Vec4*)(pImage->data());

			for (int i = 0; i < imageSizeX; i++)
			{
				for (int j = 0; j < imageSizeY; j++)
				{
					osg::Vec4d color = m_facePointsColor[i][j];
					*dataPtr++ = color;
				}
			}

			vertices->push_back(osg::Vec3(xMin, yMin, imagePos));
			vertices->push_back(osg::Vec3(xMax, yMin, imagePos));
			vertices->push_back(osg::Vec3(xMax, yMax, imagePos));
			vertices->push_back(osg::Vec3(xMin, yMax, imagePos));
			break;
		default:
			break;
		}

		//设置二维纹理的参数和WRAP方式
		osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
		texture->setWrap(osg::Texture2D::WRAP_S, osg::Texture2D::REPEAT);
		texture->setWrap(osg::Texture2D::WRAP_T, osg::Texture2D::REPEAT);
		texture->setWrap(osg::Texture2D::WRAP_R, osg::Texture2D::REPEAT);
		texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
		texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
		texture->setSourceType(GL_FLOAT);
		texture->setShadowComparison(true);
		texture->setShadowTextureMode(osg::Texture2D::LUMINANCE);
		texture->setImage(pImage);

		osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();//定义一个颜色数组颜色
		c->push_back(osg::Vec4(1.0, 1.0, 1.0, 1.0));//数组的四个参数分别为RGBA，其中A表示透明度
	    //osg::ref_ptr<osg::Vec4Array> normalArray = new osg::Vec4Array();//定义一个颜色数组颜色
	    //normalArray->push_back(osg::Vec4(-1.0, 0.0, 0.0,1.0));//
	    //normalArray->push_back(osg::Vec4(-1.0, 0.0, 0.0,1.0));//
	    //normalArray->push_back(osg::Vec4(-1.0, 0.0, 0.0,1.0));//
	    //normalArray->push_back(osg::Vec4(-1.0, 0.0, 0.0,1.0));//

		osg::ref_ptr<osg::Vec2Array> texcoords = new osg::Vec2Array;
		texcoords->push_back(osg::Vec2(0, 0));
		texcoords->push_back(osg::Vec2(0, 1));
		texcoords->push_back(osg::Vec2(1, 1));
		texcoords->push_back(osg::Vec2(1, 0));
		geom->setVertexArray(vertices.get());
		geom->setColorArray(c.get());
		geom->setColorBinding(osg::Geometry::BIND_OVERALL);
		geom->setTexCoordArray(0, texcoords.get());
		/*geom->setNormalArray(normalArray.get());
		geom->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);*/

		geom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));
		geode->addDrawable(geom.get());
		osg::StateSet* stateset = geom->getOrCreateStateSet();

		stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
		stateset->setTextureAttribute(0, texture.get(), osg::StateAttribute::OVERRIDE);
		stateset->setTextureMode(0, GL_TEXTURE_2D, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
		return geode.release();
	}
}