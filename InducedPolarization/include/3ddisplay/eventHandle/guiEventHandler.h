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

		osg::Vec3d screen2World(osg::Vec3d& screenPoint, osg::Camera* vCamera)//����Ļ����ת������������
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
				////��������ڵ�
				m_orthoCamera = new osg::Camera;
				////ͼ��������õ�ǰ�ӿ�
				m_orthoCamera->setViewport(0, 0, width, height);
				//ֱ������/��ȡͶӰ���������--ƽ��ͶӰ
				m_orthoCamera->setProjectionMatrix(osg::Matrix::ortho2D(0, width, 0, height));
				//����/��ȡ������Ĳο�ϵ��ʹ��ABSOLUTE_RF���Բο�ϵ��ʾ����������ܸ��ڵ��κα任��Ӱ��
				m_orthoCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
				//ֱ������/��ȡ�۲���������
				m_orthoCamera->setViewMatrix(osg::Matrix::identity());
				//�����Ȼ���
				m_orthoCamera->setClearMask(GL_DEPTH_BUFFER_BIT);
				//�����������Ⱦ˳����������֮ǰ��PRE_RENDER������֮��POST_RENDER����
				m_orthoCamera->setRenderOrder(osg::Camera::POST_RENDER);
				m_orthoCamera->setAllowEventFocus(false);
				m_orthoCamera->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);
				m_orthoCamera->setClearColor(osg::Vec4(1.0, 1.0, 1.0, 0.5));

			}
			m_orthoCamera->getViewport()->setViewport(0, 0, width, height);
			//m_orthoCamera->setViewport(new osg::Viewport(0, 0, width, height));
			//ֱ������/��ȡͶӰ���������--ƽ��ͶӰ
			m_orthoCamera->setProjectionMatrix(osg::Matrix::ortho2D(0, width, 0, height));
		}

		virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
		
		
	signals:
		

	private:
		osg::ref_ptr<osg::Camera> m_orthoCamera;
	};
};