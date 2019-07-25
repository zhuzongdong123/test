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

		//获取两点之间的距离
		float getTwoPointsDistance(osg::Vec3f res, osg::Vec3f des);
		//标签
		osg::Node* createLabel(const osg::Vec3& pos, const std::string& label, const osg::Vec4 color, std::string font, float size);
		//直线
		osg::Node* drawLine(const osg::Vec3 startPoint, const osg::Vec3 endPoint, const osg::Vec4 color, float width = 3.0f);
		osg::Node* drawLine(const osg::Vec3 startPoint, const osg::Vec3 endPoint, float width = 3.0f);

		//多边形绘制，不自动闭合
		osg::Node* drawPolygon(osg::Vec3Array* vertexs, const osg::Vec4 color, float width = 3.0f);

		//点
		osg::Node* drawPoint(const osg::Vec3 pos, const osg::Vec4 color, float size);

		//圆锥箭头
		osg::Node* coneArrow(const float dia, const float height);

		//三角箭头
		osg::Node* triangleArrow(const float dia, const float height, const float width);

		//十字箭头
		osg::Node* crossArrow(const float width, const float scale, const osg::Vec4 color);

		//绘制矩形
		osg::Node* drawQuads(osg::Vec4dArray* pColorArray, osg::Vec3Array* pVertexArray);
		//设置颜色
		void seNodeColor(const osg::Vec4& color, osg::Node* node);

		//多面体相交测试
		osg::Polytope getPolytope(float x, float y, float rad, size_t num = 3);

		osg::Node* DrawTriFlag();
		void createMatrial(osg::Geode* vGeode);//各节点加材质
		void createMatrial(osg::Group* vGroupNode);
		void createMatrial(osg::MatrixTransform* vTransNode);
		//function: 绘制透明物体
		void drawForDiaphaneity(osg::MatrixTransform* vTranNode, float vRatio = 0.35);
		void drawForDiaphaneity(osg::Geode* vGeode);//绘制透明物体
		void drawForDiaphaneity(osg::Node* vNode, float ratio);//绘制透明物体

		void drawNodeForLine(osg::Node* vNode); //实现物体的网格绘制
		void drawNodeForFill(osg::Node* vNode); //实现物体的网格填充绘制
	} //namespace CommFunc
} //namespace osgEngine
