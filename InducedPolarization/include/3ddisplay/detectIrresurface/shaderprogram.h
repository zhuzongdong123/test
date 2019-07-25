#pragma once
#include "osg/Shader"
#include "osg/Node"
#include "osg/Program"

using namespace std;

namespace osgEngine
{
	class CShaderProgram
	{
	public:
		CShaderProgram() :m_shaderProgramObject(NULL), m_shaderVertexObject(NULL){}
		~CShaderProgram();

		osg::ref_ptr<osg::Shader> createShader(osg::Shader::Type vType, const std::string &vName, const std::string &vSourceFile);
		void attachShader(osg::Node* vNode, std::string& vVertFile, std::string& vFragFile);
	protected:

	private:
		osg::ref_ptr<osg::Program> m_shaderProgramObject;
		osg::ref_ptr<osg::Shader>  m_shaderVertexObject;
		osg::ref_ptr<osg::Shader>  m_shaderFragmentObject;
	};
}