#pragma once
#include <osg/Group>
#include <osg/Geode>
#include <osg/Material>
#include <osg/Texture2D>
#include <osg/PolygonMode>
#include <osg/Light>
#include <osg/LightSource>
#include "tool/light.h"
#include <osgText/Text>
#include <string>
#include <windows.h>

using namespace std;

//
namespace StateTool
{
	//字符串处理
	std::string trimString(const std::string& vInput);
	void splitLine(const std::string& vInput, char vDelimiter, std::string& vLeftStr, std::string& vRightStr);
	vector<string> split(const string& str, const string& delim);
	//文字处理
	void unicodeToUTF8(const wstring &src, string& result);
	void gb2312ToUnicode(const string& src, wstring& result);
	void gb2312ToUtf8(const string& src, string& result);
	void createText(osg::Geode* geode, const char* vStr, osg::Vec3 vec3, float fontSize);
	void createLight(osg::Group* sceneGroup);

	void setNodeDiaphaneity( osg::Node * inNode, float inDiaphaneity, bool inOverride=false );
	void createLightSource(unsigned int vLightIndex, osg::Vec3f& vLightPos,osg::Group* vSceneGroup);
	void createGlobalLightSource(unsigned int vLightIndex, osg::Vec3f& vLightPos,osg::Group* vSceneGroup);
	void setNodeLine(osg::Geode* vGeode);//设置节点为线性形状
}