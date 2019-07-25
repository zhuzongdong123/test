#include "tool/light.h"

// 光源相关的工具
namespace LightTool
{
	//**********************************************************************************************************************
	//FUNCTION: 创建光源
	void LocalLight::createLocalLight(osg::Vec3f& vLightPos)
	{
		/*if (m_pLightNode != NULL)
		{*/
				//const osg::BoundingSphere LightNodeBS = m_pLightNode->getBound();
				 
				//osg::Vec3f pos = LightNodeBS.center();
				 
				setPosition(osg::Vec4f(vLightPos,1.0f));  //光照位置

				//const osg::BoundingSphere LightNodeBS = m_pLightNode->getBound();
				//osg::BoundingBox bb;
			// bb.expandBy(LightNodeBS);

				//float nodeSize = bb.radius();

				setConstantAttenuation(0.000005f);//光的衰减值
				setLinearAttenuation(0.0000005f);//设置线性衰减
				setQuadraticAttenuation(0.00000005f);

				//setConstantAttenuation(1.0f);//光的衰减值
				//setLinearAttenuation(2.0f/nodeSize);//设置线性衰减
				//setQuadraticAttenuation(2.0f/osg::square(nodeSize));
		//}
            
	}

	//**********************************************************************************************************************
	//FUNCTION: 初始化局部光源
	void LocalLight::initLocalLight(unsigned int vLightNum)
	{
		m_Diffuse  = osg::Vec4(1.0f,1.0f,1.0f,1.0f);
		m_Ambinent = osg::Vec4(1.0f,0.0f,0.0f,1.0f);
		m_LightPos = osg::Vec4(1000.0f,1000.0f,3000.0f,1.0f);

		setLightNum(vLightNum);   //Light对象设置一个ID
		//setPosition(osg::Vec4(2000,2000,2000,1.0));  //位置
			
		setAmbient(m_Ambinent);//光强
		setDiffuse(m_Diffuse);
		setSpotCutoff(50.0f);
		setSpotExponent(80.0f);
	}
}