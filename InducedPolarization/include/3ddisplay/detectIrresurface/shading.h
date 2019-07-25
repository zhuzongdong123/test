#pragma once
#include "3ddisplay/detectIrresurface/ShaderProgram.h"
#include "osg/Light"
#include "osg/LightSource"

namespace osgEngine
{
	class CShadingLight : public osg::Referenced
	{
	public:
		enum ShadingMode
		{
			SHADING_UNDEFINED = 0,
			DEFERRED_SHADING,
			PERFRAGMENT_SHADING,
		};

	public:
		CShadingLight(void);
		virtual ~CShadingLight(void);
		void createLocalShaderLight(unsigned int vLightSource, osg::Node* vSceneNode);
		void updateShaderViewPos(osg::Vec3f vViewPos, osg::StateSet* vStateSet);
	protected:

	private:
		osg::Vec3f   m_LightDirection;
		osg::Vec3f   m_MaterialAmbient;
		osg::Vec3f   m_MaterialSpecular;
		osg::Vec3f   m_ViewPos;
		osg::Vec3f   m_LightPos;
		ShadingMode  m_ShadingMode;
		std::string  m_ShaderPath;

		osg::Vec3f   m_LightAmbient;
		osg::Vec3f   m_LightDiffuse;
		osg::Vec3f   m_CurrentLightDiffuse;
		osg::Vec3f   m_CurrentLightAmbient;
		
		CShaderProgram* m_pShaderProgram;
	};
}
