#pragma once
#include <osg/Geode>
#include <osgUtil/PolytopeIntersector>
#include <osgViewer/View>
#include <osg/BlendColor>
#include <osg/BlendFunc>
#include <osg/MatrixTransform>
#include <osg/PolygonMode>

namespace osgEngine
{
	namespace DrawFunc
	{

		//��ȡ����֮��ľ���
		float getTwoPointsDistance(osg::Vec3f res, osg::Vec3f des);
		//��ǩ
		osg::Node* createLabel(const osg::Vec3& pos, const std::string& label, const osg::Vec4 color, std::string font, float size);
		//ֱ��
		osg::Node* drawLine(const osg::Vec3 startPoint, const osg::Vec3 endPoint, const osg::Vec4 color, float width = 3.0f);
		osg::Node* drawLine(const osg::Vec3 startPoint, const osg::Vec3 endPoint, float width = 3.0f);

		//����λ��ƣ����Զ��պ�
		osg::Node* drawPolygon(osg::Vec3Array* vertexs, const osg::Vec4 color, float width = 3.0f);

		//��
		osg::Node* drawPoint(const osg::Vec3 pos, const osg::Vec4 color, float size);

		//Բ׶��ͷ
		osg::Node* coneArrow(const float dia, const float height);

		//���Ǽ�ͷ
		osg::Node* triangleArrow(const float dia, const float height, const float width);

		//ʮ�ּ�ͷ
		osg::Node* crossArrow(const float width, const float scale, const osg::Vec4 color);

		//���ƾ���
		osg::Node* drawQuads(osg::Vec4dArray* pColorArray, osg::Vec3Array* pVertexArray);
		//������ɫ
		void seNodeColor(const osg::Vec4& color, osg::Node* node);

		//�������ཻ����
		osg::Polytope getPolytope(float x, float y, float rad, size_t num = 3);

		osg::Node* DrawTriFlag();
		void createMatrial(osg::Geode* vGeode);//���ڵ�Ӳ���
		void createMatrial(osg::Group* vGroupNode);
		void createMatrial(osg::MatrixTransform* vTransNode);
		//function: ����͸������
		void drawForDiaphaneity(osg::MatrixTransform* vTranNode, float vRatio = 0.35);
		void drawForDiaphaneity(osg::Geode* vGeode);//����͸������
		void drawForDiaphaneity(osg::Node* vNode, float ratio);//����͸������

		void drawNodeForLine(osg::Node* vNode); //ʵ��������������
		void drawNodeForFill(osg::Node* vNode); //ʵ�����������������
	} //namespace CommFunc
} //namespace osgEngine
