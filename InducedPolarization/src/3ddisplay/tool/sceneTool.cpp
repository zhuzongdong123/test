#include "tool/sceneTool.h"

namespace StateTool
{
	/****************************************************************************************************************************************************/
	//FUNCTION: �ַ���ȥ���ո�
	std::string trimString(const std::string& vInput)
	{
		if (vInput == "") return "";

		std::string strOutput;
		std::string::size_type SpacePos;

		strOutput = vInput;
		SpacePos = strOutput.find_first_not_of(' ', 0);
		if ((SpacePos != 0) && (SpacePos < strOutput.size()))
			strOutput.erase(strOutput.begin(), strOutput.begin() + SpacePos);

		SpacePos = strOutput.find_last_not_of(' ', strOutput.size());
		if (SpacePos < strOutput.size())
			strOutput.erase(strOutput.begin() + SpacePos + 1, strOutput.end());

		return strOutput;
	}

	/****************************************************************************************************************************************************/
	//FUNCTION: �ָ��ַ���
	void splitLine(const std::string& vInput, char vDelimiter, std::string& vLeftStr, std::string& vRightStr)
	{
		std::string::size_type SplitPos;

		SplitPos = vInput.find_first_of(vDelimiter, 0);
		if ((std::string::npos == SplitPos) || (SplitPos == vInput.length() - 1))
		{
			vLeftStr = vInput;
			vRightStr = "";
		}
		else
		{
			vLeftStr = trimString(vInput.substr(0, SplitPos));
			vRightStr = trimString(vInput.substr(SplitPos + 1, vInput.length() - SplitPos));
		}
	}

	//�ָ��ַ���(�������ʶ���ָ�)
	vector<string> split(const string& str, const string& delim)
	{
		vector<string> res;
		if ("" == str) return res;
		//�Ƚ�Ҫ�и���ַ�����string����ת��Ϊchar*����
		char * strs = new char[str.length() + 1]; //��Ҫ����
		strcpy(strs, str.c_str());

		char * d = new char[delim.length() + 1];
		strcpy(d, delim.c_str());

		char *p = strtok(strs, d);
		while (p) {
			string s = p; //�ָ�õ����ַ���ת��Ϊstring����
			res.push_back(s); //����������
			p = strtok(NULL, d);
		}

		return res;
	}

	void unicodeToUTF8(const wstring &src, string& result)
	{
		int n = WideCharToMultiByte(CP_UTF8, 0, src.c_str(), -1, 0, 0, 0, 0);
		result.resize(n);
		::WideCharToMultiByte(CP_UTF8, 0, src.c_str(), -1, (char*)result.c_str(), result.length(), 0, 0);
	}

	void gb2312ToUnicode(const string& src, wstring& result)
	{
		int n = MultiByteToWideChar(CP_ACP, 0, src.c_str(), -1, NULL, 0);
		result.resize(n);
		::MultiByteToWideChar(CP_ACP, 0, src.c_str(), -1, (LPWSTR)result.c_str(), result.length());
	}

	void gb2312ToUtf8(const string& src, string& result)
	{
		wstring strWideChar;
		gb2312ToUnicode(src, strWideChar);

		unicodeToUTF8(strWideChar, result);
	}

	void createText(osg::Geode* geode, const char* vStr, osg::Vec3 vec3, float fontSize)
	{
		setlocale(LC_ALL, ".936");//�����õ�����Ϣ
		osg::ref_ptr<osgText::Text> text = new osgText::Text;
		//osg::ref_ptr<osgText::Font> font = osgText::readFontFile("C:/Windows/Fonts/Arial.ttf");
		
		osgText::Font* fontHei = osgText::readFontFile(std::string("C://WINDOWS//Fonts//simhei.ttf"));
		text->setFont(std::string("C://WINDOWS//Fonts//simhei.ttf"));
		text->setCharacterSize(fontSize);
		text->setAxisAlignment(osgText::Text::SCREEN);
		text->setPosition(vec3);
		text->setText(vStr);
		text->setColor(osg::Vec4f(0.5, 0.5, 0.5, 1.0));
		//std::string labelWideName;
		//gb2312ToUtf8(vStr, labelWideName);
		geode->addDrawable(text.get());
	}
	// ���ýڵ�͸����(0-100)
	void setNodeDiaphaneity( osg::Node * inNode, float inDiaphaneity, bool inOverride)
	{
		if ( NULL == inNode )
		{
			return;
		}

		osg::ref_ptr<osg::StateSet> stateset = inNode->getOrCreateStateSet();
		osg::ref_ptr<osg::Material> mat = dynamic_cast<osg::Material*>(stateset->getAttribute(osg::StateAttribute::MATERIAL));
		if ( NULL == mat )
		{
			mat = new osg::Material;
		}

		osg::Vec4 oldColor = mat->getDiffuse(osg::Material::FRONT_AND_BACK);
		mat->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(oldColor.r(), oldColor.g(), oldColor.b(), inDiaphaneity));

		if ( inOverride )
		{
			stateset->setAttributeAndModes(mat, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
		}
		else 
		{
			stateset->setAttributeAndModes(mat, osg::StateAttribute::ON); 
		}

		osg::ref_ptr<osg::Program> pProgram = new osg::Program;
		stateset->setAttributeAndModes(pProgram, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
		stateset->setMode(GL_BLEND,osg::StateAttribute::ON);
		stateset->setMode(GL_DEPTH_TEST,osg::StateAttribute::ON);
		stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	}

	void createLight(osg::Group* sceneGroup)
	{
		osg::ref_ptr<osg::Light> light = new osg::Light();
		light->setLightNum(0); //��������ĵ�һ����Դ��GL_LIGHT0
		light->setDirection(osg::Vec3(1.0f, 1.0f, 1.0f));

		light->setPosition(osg::Vec4(10, 10, 10, 1.0));
		light->setAmbient(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));//��ǿ
		//light->setDiffuse(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
		//�������õƹ���������
		//������Դ
		osg::ref_ptr<osg::LightSource> lightSource = new osg::LightSource();
		lightSource->setLight(light.get());
		sceneGroup->addChild(lightSource.get());
	}
	/**********************************************************************************************************************************************************************************/
	//������Դ
	void createLightSource(unsigned int vLightIndex, osg::Vec3f& vLightPos,osg::Group* vSceneGroup)
	{
		osg::ref_ptr<osg::Light> pLight = new LightTool::LocalLight(vLightIndex,vLightPos);
		osg::ref_ptr<osg::LightSource> pLightSource = new osg::LightSource;
		pLightSource->setLight(pLight.get());
		vSceneGroup->addChild(pLightSource.get());
	}

	/**********************************************************************************************************************************************************************************/
	//����ȫ�ֹ�Դ
	void createGlobalLightSource(unsigned int vLightIndex, osg::Vec3f& vLightPos,osg::Group* vSceneGroup)
	{
		osg::ref_ptr<osg::Light> pLight = new  LightTool::LocalLight(vLightIndex,vLightPos);

		//���û�����
		pLight->setAmbient(osg::Vec4(0.85f,0.87f,0.8f,1.0f));
		//����ɢ������ɫ
		pLight->setDiffuse(osg::Vec4(0.75f,0.75f,0.75f,1.0f));
		pLight->setSpecular(osg::Vec4(1.0f,1.0f,1.0f,1.0f));
		pLight->setPosition(osg::Vec4(vLightPos.x(),vLightPos.y(),vLightPos.z(),1.0));
		osg::ref_ptr<osg::LightSource> lightSource=new osg::LightSource;
		lightSource->setLight(pLight.get());
		vSceneGroup->addChild(lightSource.get());
	}

	void setNodeLine(osg::Geode* vGeode)
	{
		osg::PolygonMode *pLolyTotalMode = new osg::PolygonMode();			  
		pLolyTotalMode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
		vGeode->getOrCreateStateSet()->setAttribute(pLolyTotalMode);
		vGeode->getOrCreateStateSet()->setAttributeAndModes(pLolyTotalMode, osg::StateAttribute::OVERRIDE|osg::StateAttribute::ON);
	}
}