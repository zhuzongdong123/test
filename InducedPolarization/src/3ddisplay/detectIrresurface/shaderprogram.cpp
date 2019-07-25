#include "3ddisplay/detectIrresurface/shaderprogram.h"


namespace osgEngine
{
	CShaderProgram::~CShaderProgram()
	{

	}
	//*********************************************************************************************************************************************************************
	//FUNCTION: 
	osg::ref_ptr<osg::Shader> CShaderProgram::createShader(osg::Shader::Type vType, const std::string &vName, const std::string &vSourceFile)
	{
		osg::Shader* pShader;
		pShader = new osg::Shader(vType);
		pShader->setName(vName);
		bool success = pShader->loadShaderSourceFromFile(vSourceFile);
		if (true != success)
		{
			return NULL;
		}

		return pShader;

	}

	void CShaderProgram::attachShader(osg::Node* vNode, std::string& vVertFile, std::string& vFragFile)
	{
		osg::StateSet* shaderState = vNode->getOrCreateStateSet();

		m_shaderProgramObject = new osg::Program;
		m_shaderVertexObject = createShader(osg::Shader::VERTEX, "Vertex", vVertFile);
		m_shaderFragmentObject = createShader(osg::Shader::FRAGMENT, "Fragment", vFragFile);
		m_shaderProgramObject->addShader(m_shaderVertexObject.get());
		m_shaderProgramObject->addShader(m_shaderFragmentObject.get());
		shaderState->setName("ShaderLight");
		shaderState->setAttributeAndModes(m_shaderProgramObject, osg::StateAttribute::ON);
	}
}
