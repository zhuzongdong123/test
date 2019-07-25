#pragma once
#include <3ddisplay/tunnelDraw/DrawFunc.h>
#include <osgUtil/Optimizer>
#include <osg/MatrixTransform>
#include <osg/PolygonMode>
#include <osg/Point>
#include <osg/TexGen>
#include <iostream>
#include <limits>
#include <vector>
#include <osg/LineWidth>
#include <osg/Point>
#include <osgDB/ReadFile>
#include "3ddisplay/detectIrresurface/shading.h"

namespace osgEngine
{
	class CTunnelDraw :public osg::MatrixTransform
	{
	public:

		enum tunnelAxis
		{
			XAxes = 0,//坐标轴的走向，隧道沿着X轴
			YAxes  //隧道沿着Y轴
		};
		CTunnelDraw()
		{
			m_tunnelCenterPos = osg::Vec3d(0,0,0);
			m_pShadingLight = NULL;
			//整个隧道的绘制
			m_circleNode = new osg::Geode;
			m_TunnelGroupOnline = new osg::Group;
			m_TunnelGroupInline = new osg::Group;
			m_beginMile = 200180;
			m_tunnelDia = 0.0;
			m_TunnelTextGroup = new osg::Group;
			m_tunnelSRGroup = new osg::Group;
			m_inlinePointArray = new osg::Vec3dArray; //生成隧道的起始位置的内环形顶点
			m_onlinePointArray = new osg::Vec3dArray; //生成隧道的起始位置的外环形顶点
		}

		~CTunnelDraw()
		{
			for (int i = 0; i < this->getNumChildren(); i++)
			{
				this->removeChild(i);
			}
		}

		void Init_Circle(float circle1[36][2], float Radius, int &vCircleNum);
		
		osg::ref_ptr<osg::Node> getCircleNode() { return m_circleNode.get(); }//获取隧道开始处的环形体面
		osg::ref_ptr<osg::Node> createCircleTunnel();//创建隧道环形柱体
		osg::ref_ptr<osg::Group> getInlineTunnel() { return m_TunnelGroupInline.get(); } //获取隧道外环节点组合
		osg::ref_ptr<osg::Group> getOnlineTunnel() { return m_TunnelGroupOnline.get(); } //获取隧道内环形节点组合
		osg::ref_ptr<osg::Group> getSRTunnel() { return m_tunnelSRGroup.get(); }
		osg::ref_ptr<osg::Group> getTextGroup() { return m_TunnelTextGroup.get(); }
		osg::ref_ptr<osg::Geode> createTunnelTextFlag(osg::Vec3d tunnelCenter, float tunnelRadius, float vTextPos, float textSize=0.7);
		osg::Node* tunnelDisplayLine(bool isInlineTunnel); //隧道线状显示
		osg::Node* tunnelDisplayFill(bool isInlineTunnel); //隧道填充显示
		osg::Vec3d getTunnelCenter() { return m_tunnelCenterPos; }
		osg::ref_ptr<osg::Geode> drawTextFlagLine(osg::Vec3d& vTunnelCenter, unsigned int segNum, float segLen, float vTunnelRadius);

		inline int round(const float a) { return (int)(a + 0.5f); };
		
		osg::MatrixTransform* createHorseShoeTunnel(osg::Vec3d circlePos, float eachCircleTunnelLen, float tunnelSegNum, float Radius);
		osg::ref_ptr<osg::Group> createHorseShoeCirlineBySRPoint(osg::Vec3d& circlePos, float eachTunelCircleLen, int tunelSegmentNum, float Radius, bool isInsideTunnel);
		osg::ref_ptr<osg::Group> drawHorseShoeTunnelLine(osg::Vec3d circlePos, float eachTunelCircleLen, float tunnelSegNum, float Radius, bool isInsideTunnel);
		osg::ref_ptr<osg::Group> createCirlineBySRPoint(osg::Vec3d& circlePos, float eachTunelCircleLen, int tunelSegmentNum, float Radius, bool isInsideTunnel);
		osg::ref_ptr<osg::Group> createCirlineByQuards(osg::Vec3d& circlePos, float eachTunelCircleLen, int tunelSegmentNum, float Radius, bool isInsideTunnel);
		osg::MatrixTransform* drawQuardsTunnel(osg::Vec3d circlePos, float eachCircleTunnelLen, float tunnelSegNum, float Radius);
		void changetunnelDiaphaneity(float vDiaphanerityRatio);//改变隧道的透明度
		
		osg::ref_ptr<osgEngine::CShadingLight> getShaderLight() {return m_pShadingLight.get();}

		void setBeginMile(double vBeginMile) { m_beginMile = vBeginMile; }
		float getTunnelDia() { return m_tunnelDia; } //获取隧道直径

	private:
		
		double m_beginMile; //掌子面的起始里程号
		float m_tunnelDia; //隧道直径

		osg::Vec3d m_tunnelCenterPos;
		osg::ref_ptr<osg::Geode> m_circleNode;//隧道最外边的环形柱体
		osg::ref_ptr<osg::Group> m_TunnelGroupInline; //隧道的内环，每条隧道由两段组成
		osg::ref_ptr<osg::Group> m_TunnelGroupOnline; //隧道的外环，每条隧道由两段组成
		osg::ref_ptr<osg::Group> m_tunnelSRGroup;//保存隧道和S、R数据分布
		osg::ref_ptr<osg::Group> m_TunnelTextGroup; //隧道文字
		osg::ref_ptr<osgEngine::CShadingLight> m_pShadingLight;
				
		osg::ref_ptr<osg::Vec3dArray> m_inlinePointArray; //内环形顶点
		osg::ref_ptr<osg::Vec3dArray> m_onlinePointArray; //外环形顶点
	};
}
