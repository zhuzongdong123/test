#include "tool/light.h"

// ��Դ��صĹ���
namespace LightTool
{
	//**********************************************************************************************************************
	//FUNCTION: ������Դ
	void LocalLight::createLocalLight(osg::Vec3f& vLightPos)
	{
		/*if (m_pLightNode != NULL)
		{*/
				//const osg::BoundingSphere LightNodeBS = m_pLightNode->getBound();
				 
				//osg::Vec3f pos = LightNodeBS.center();
				 
				setPosition(osg::Vec4f(vLightPos,1.0f));  //����λ��

				//const osg::BoundingSphere LightNodeBS = m_pLightNode->getBound();
				//osg::BoundingBox bb;
			// bb.expandBy(LightNodeBS);

				//float nodeSize = bb.radius();

				setConstantAttenuation(0.000005f);//���˥��ֵ
				setLinearAttenuation(0.0000005f);//��������˥��
				setQuadraticAttenuation(0.00000005f);

				//setConstantAttenuation(1.0f);//���˥��ֵ
				//setLinearAttenuation(2.0f/nodeSize);//��������˥��
				//setQuadraticAttenuation(2.0f/osg::square(nodeSize));
		//}
            
	}

	//**********************************************************************************************************************
	//FUNCTION: ��ʼ���ֲ���Դ
	void LocalLight::initLocalLight(unsigned int vLightNum)
	{
		m_Diffuse  = osg::Vec4(1.0f,1.0f,1.0f,1.0f);
		m_Ambinent = osg::Vec4(1.0f,0.0f,0.0f,1.0f);
		m_LightPos = osg::Vec4(1000.0f,1000.0f,3000.0f,1.0f);

		setLightNum(vLightNum);   //Light��������һ��ID
		//setPosition(osg::Vec4(2000,2000,2000,1.0));  //λ��
			
		setAmbient(m_Ambinent);//��ǿ
		setDiffuse(m_Diffuse);
		setSpotCutoff(50.0f);
		setSpotExponent(80.0f);
	}
}