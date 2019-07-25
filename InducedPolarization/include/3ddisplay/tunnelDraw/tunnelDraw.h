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
			XAxes = 0,//������������������X��
			YAxes  //�������Y��
		};
		CTunnelDraw()
		{
			m_tunnelCenterPos = osg::Vec3d(0,0,0);
			m_pShadingLight = NULL;
			//��������Ļ���
			m_circleNode = new osg::Geode;
			m_TunnelGroupOnline = new osg::Group;
			m_TunnelGroupInline = new osg::Group;
			m_beginMile = 200180;
			m_tunnelDia = 0.0;
			m_TunnelTextGroup = new osg::Group;
			m_tunnelSRGroup = new osg::Group;
			m_inlinePointArray = new osg::Vec3dArray; //�����������ʼλ�õ��ڻ��ζ���
			m_onlinePointArray = new osg::Vec3dArray; //�����������ʼλ�õ��⻷�ζ���
		}

		~CTunnelDraw()
		{
			for (int i = 0; i < this->getNumChildren(); i++)
			{
				this->removeChild(i);
			}
		}

		void Init_Circle(float circle1[36][2], float Radius, int &vCircleNum);
		
		osg::ref_ptr<osg::Node> getCircleNode() { return m_circleNode.get(); }//��ȡ�����ʼ���Ļ�������
		osg::ref_ptr<osg::Node> createCircleTunnel();//���������������
		osg::ref_ptr<osg::Group> getInlineTunnel() { return m_TunnelGroupInline.get(); } //��ȡ����⻷�ڵ����
		osg::ref_ptr<osg::Group> getOnlineTunnel() { return m_TunnelGroupOnline.get(); } //��ȡ����ڻ��νڵ����
		osg::ref_ptr<osg::Group> getSRTunnel() { return m_tunnelSRGroup.get(); }
		osg::ref_ptr<osg::Group> getTextGroup() { return m_TunnelTextGroup.get(); }
		osg::ref_ptr<osg::Geode> createTunnelTextFlag(osg::Vec3d tunnelCenter, float tunnelRadius, float vTextPos, float textSize=0.7);
		osg::Node* tunnelDisplayLine(bool isInlineTunnel); //�����״��ʾ
		osg::Node* tunnelDisplayFill(bool isInlineTunnel); //��������ʾ
		osg::Vec3d getTunnelCenter() { return m_tunnelCenterPos; }
		osg::ref_ptr<osg::Geode> drawTextFlagLine(osg::Vec3d& vTunnelCenter, unsigned int segNum, float segLen, float vTunnelRadius);

		inline int round(const float a) { return (int)(a + 0.5f); };
		
		osg::MatrixTransform* createHorseShoeTunnel(osg::Vec3d circlePos, float eachCircleTunnelLen, float tunnelSegNum, float Radius);
		osg::ref_ptr<osg::Group> createHorseShoeCirlineBySRPoint(osg::Vec3d& circlePos, float eachTunelCircleLen, int tunelSegmentNum, float Radius, bool isInsideTunnel);
		osg::ref_ptr<osg::Group> drawHorseShoeTunnelLine(osg::Vec3d circlePos, float eachTunelCircleLen, float tunnelSegNum, float Radius, bool isInsideTunnel);
		osg::ref_ptr<osg::Group> createCirlineBySRPoint(osg::Vec3d& circlePos, float eachTunelCircleLen, int tunelSegmentNum, float Radius, bool isInsideTunnel);
		osg::ref_ptr<osg::Group> createCirlineByQuards(osg::Vec3d& circlePos, float eachTunelCircleLen, int tunelSegmentNum, float Radius, bool isInsideTunnel);
		osg::MatrixTransform* drawQuardsTunnel(osg::Vec3d circlePos, float eachCircleTunnelLen, float tunnelSegNum, float Radius);
		void changetunnelDiaphaneity(float vDiaphanerityRatio);//�ı������͸����
		
		osg::ref_ptr<osgEngine::CShadingLight> getShaderLight() {return m_pShadingLight.get();}

		void setBeginMile(double vBeginMile) { m_beginMile = vBeginMile; }
		float getTunnelDia() { return m_tunnelDia; } //��ȡ���ֱ��

	private:
		
		double m_beginMile; //���������ʼ��̺�
		float m_tunnelDia; //���ֱ��

		osg::Vec3d m_tunnelCenterPos;
		osg::ref_ptr<osg::Geode> m_circleNode;//�������ߵĻ�������
		osg::ref_ptr<osg::Group> m_TunnelGroupInline; //������ڻ���ÿ��������������
		osg::ref_ptr<osg::Group> m_TunnelGroupOnline; //������⻷��ÿ��������������
		osg::ref_ptr<osg::Group> m_tunnelSRGroup;//���������S��R���ݷֲ�
		osg::ref_ptr<osg::Group> m_TunnelTextGroup; //�������
		osg::ref_ptr<osgEngine::CShadingLight> m_pShadingLight;
				
		osg::ref_ptr<osg::Vec3dArray> m_inlinePointArray; //�ڻ��ζ���
		osg::ref_ptr<osg::Vec3dArray> m_onlinePointArray; //�⻷�ζ���
	};
}
