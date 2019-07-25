#pragma once
#include <osg/Light>

// ��Դ��صĹ���
namespace LightTool
{
	class LocalLight : public osg::Light
	{
	public:
		LocalLight(unsigned int vLightNum,/*osg::Node* vLightNode,*/osg::Vec3f& vLightPos)
		{
			//m_pLightNode = vLightNode;
			initLocalLight(vLightNum);
			createLocalLight(vLightPos);
		}

		~LocalLight(){}

		void initLocalLight(unsigned int vLightNum);
		void createLocalLight(osg::Vec3f& vLightPos);

		inline void setLocalAmbient(osg::Vec4f& vAmbient)
		{
			m_Ambinent = vAmbient;
			setAmbient(m_Ambinent);//������
		}

		inline void setLocalDiffuse(osg::Vec4f& vDifusse)
		{
			m_Diffuse = vDifusse;
            setDiffuse(m_Diffuse);//ɢ���
		}

		inline void setLocalSpecular(osg::Vec4f& vSpecular)
		{
			m_Specular = vSpecular;
			setSpecular(m_Specular);//�����
		}

		inline void setLightPos(osg::Vec4f& vLightPos){m_LightPos = vLightPos;}

	protected:

	private:
		osg::Node* m_pLightNode;
		osg::Vec4f m_Diffuse;
		osg::Vec4f m_Ambinent;
		osg::Vec4f m_Specular;
        osg::Vec4f m_LightPos;
	};

}