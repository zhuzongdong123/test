#include "3ddisplay/detectIrresurface/shading.h"

namespace osgEngine
{
	CShadingLight::CShadingLight(void) : m_ShadingMode(SHADING_UNDEFINED), m_pShaderProgram(NULL)
	{
		m_LightDirection = osg::Vec3f(0, 0, -1);
		m_MaterialAmbient = osg::Vec3f(0.6, 0.6, 0.6);
		m_MaterialSpecular = osg::Vec3f(0.5, 0.5, 0.5);
		m_LightAmbient = osg::Vec3(0.5, 0.5, 0.5);
		m_LightDiffuse = osg::Vec3(0.5, 0.5, 0.5);
		
		m_LightPos = osg::Vec3f(0, 0, 12);
		m_ViewPos = osg::Vec3f(0,0,6);
		m_pShaderProgram = new CShaderProgram;
	}

	CShadingLight::~CShadingLight(void)
	{
		if (NULL != m_pShaderProgram)
			delete m_pShaderProgram;
	}

	//**********************************************************************************************************************
	//FUNCTION:
	void CShadingLight::createLocalShaderLight(unsigned int vLightSource, osg::Node* vSceneNode)
	{
		std::string vertFileName = "./Shader/vertLocalShaderLight.glsl";
		std::string fragFileName = "./Shader/fragLocalShadingByLight.glsl";

		m_pShaderProgram->attachShader(vSceneNode, vertFileName, fragFileName);

		osg::StateSet* shaderState = vSceneNode->getOrCreateStateSet();		
		shaderState->addUniform(new osg::Uniform("uViewPos", m_ViewPos));
		shaderState->addUniform(new osg::Uniform("uLightPos", m_LightPos));
	}

	//**********************************************************************************************************************
	//FUNCTION:更新视点位置
	void CShadingLight::updateShaderViewPos(osg::Vec3f vViewPos, osg::StateSet* vStateSet)
	{
		//printf("antai test: vLightPos:x:%f,y:%f,z:%f",vViewPos.x(),vViewPos.y(),vViewPos.z());
		
		vStateSet->addUniform(new osg::Uniform("uViewPos", vViewPos));
	}
};