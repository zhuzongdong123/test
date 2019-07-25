#pragma once
#include <osgGA/GUIEventHandler>
#include <osgViewer/View>
#include <QtCore/QObject>

namespace osgEngine
{
	class cGuiEventHandler :public QObject, public osgGA::GUIEventHandler
	{
		Q_OBJECT
	public:
		cGuiEventHandler()
		{
			
		}

		~cGuiEventHandler()
		{
		}

		void setCameraToScene(osg::Group* pSceneGroup)
		{
			
		}

		osg::Vec3d screen2World(osg::Vec3d& screenPoint, osg::Camera* vCamera)//将屏幕坐标转换到世界坐标
		{
			osg::Vec3d vec3;
			osg::Matrix mVPW = vCamera->getViewMatrix() * vCamera->getProjectionMatrix() * vCamera->getViewport()->computeWindowMatrix();
			osg::Matrix invertVPW;
			invertVPW.invert(mVPW);
			vec3 = screenPoint * invertVPW;
			return vec3;
		}
		
		void createOrhoCamera(int beginXPos, int beginYPos, int width, int height)
		{
			if (NULL == m_orthoCamera)
			{
				////创建相机节点
				m_orthoCamera = new osg::Camera;
				////图形输出设置当前视口
				m_orthoCamera->setViewport(0, 0, width, height);
				//直接设置/获取投影矩阵的内容--平行投影
				m_orthoCamera->setProjectionMatrix(osg::Matrix::ortho2D(0, width, 0, height));
				//设置/获取该相机的参考系。使用ABSOLUTE_RF绝对参考系表示该相机将不受父节点任何变换的影响
				m_orthoCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
				//直接设置/获取观察矩阵的内容
				m_orthoCamera->setViewMatrix(osg::Matrix::identity());
				//清除深度缓存
				m_orthoCamera->setClearMask(GL_DEPTH_BUFFER_BIT);
				//设置相机的渲染顺序，在主场景之前（PRE_RENDER）还是之后（POST_RENDER）。
				m_orthoCamera->setRenderOrder(osg::Camera::POST_RENDER);
				m_orthoCamera->setAllowEventFocus(false);
				m_orthoCamera->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);
				m_orthoCamera->setClearColor(osg::Vec4(1.0, 1.0, 1.0, 0.5));

			}
			m_orthoCamera->getViewport()->setViewport(0, 0, width, height);
			//m_orthoCamera->setViewport(new osg::Viewport(0, 0, width, height));
			//直接设置/获取投影矩阵的内容--平行投影
			m_orthoCamera->setProjectionMatrix(osg::Matrix::ortho2D(0, width, 0, height));
		}

		virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
		
		
	signals:
		

	private:
		osg::ref_ptr<osg::Camera> m_orthoCamera;
	};
};