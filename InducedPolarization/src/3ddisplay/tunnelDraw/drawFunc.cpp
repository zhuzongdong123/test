#include <3ddisplay/tunnelDraw/DrawFunc.h>
#include <osg/LineWidth>
#include <osg/Point>
#include <osgText/Text>
#include <osg/AutoTransform>
#include <osg/ShapeDrawable>
#include <osg/Material>

namespace osgEngine
{
	namespace DrawFunc
	{

		//������֮��ľ���
		float getTwoPointsDistance(osg::Vec3f res, osg::Vec3f des)
		{
			float xx = (res.x() - des.x())*(res.x() - des.x());
			float yy = (res.y() - des.y())*(res.y() - des.y());
			float zz = (res.z() - des.z())*(res.z() - des.z());
			float distant = sqrt(xx + yy + zz);
			return distant;
		}

		//��ǩ
		osg::Node* createLabel(const osg::Vec3& pos, const std::string& label, const osg::Vec4 color, std::string font, float size)
		{
			//��������
			osgText::Text* text = new osgText::Text;
			text->setCharacterSize(size);
			text->setFont(font);
			text->setText(label);
			text->setAlignment(osgText::Text::CENTER_BOTTOM);
			text->setColor(color);

			osg::Geode* geode = new osg::Geode;
			geode->addDrawable(text);
			geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

			//�Զ�������ת
			osg::AutoTransform* at = new osg::AutoTransform;
			at->addChild(geode);
			at->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_SCREEN);
			at->setAutoScaleToScreen(true);
			at->setMinimumScale(0.0);
			at->setMaximumScale(FLT_MAX);
			at->setPosition(pos);

			return at;
		}

		//ֱ�߻���
		osg::Node* drawLine(const osg::Vec3 startPoint, const osg::Vec3 endPoint, const osg::Vec4 color, float width)
		{
			osg::Geode * lineGeode = new osg::Geode;
			osg::Geometry * line = new osg::Geometry;
			osg::Vec3Array * vertices = new osg::Vec3Array;
			osg::Vec4Array * colors = new osg::Vec4Array;

			vertices->push_back(startPoint);
			vertices->push_back(endPoint);
			colors->push_back(color);

			line->setVertexArray(vertices);
			line->setColorArray(colors);
			line->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

			line->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
			osg::LineWidth * linewidth = new osg::LineWidth;
			linewidth->setWidth(width);
			line->getOrCreateStateSet()->setAttributeAndModes(linewidth, osg::StateAttribute::ON);//�����߿�

			line->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, vertices->size()));
			lineGeode->addDrawable(line);
			return lineGeode;
		}

		osg::Node* drawLine(const osg::Vec3 startPoint, const osg::Vec3 endPoint, float width)
		{
			osg::Geode * lineGeode = new osg::Geode;
			osg::Geometry * line = new osg::Geometry;
			osg::Vec3Array * vertices = new osg::Vec3Array;

			vertices->push_back(startPoint);
			vertices->push_back(endPoint);
			line->setVertexArray(vertices);

			line->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
			osg::LineWidth * linewidth = new osg::LineWidth;
			linewidth->setWidth(width);
			line->getOrCreateStateSet()->setAttributeAndModes(linewidth, osg::StateAttribute::ON);//�����߿�

			line->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, vertices->size()));
			lineGeode->addDrawable(line);
			return lineGeode;
		}

		//�����
		//ע�⣺��Ҫ��ֹviewer�����С����ü�������ʾ
		osg::Node* drawPoint(const osg::Vec3 pos, const osg::Vec4 color, float size)
		{
			osg::Geode * pointGeode = new osg::Geode;
			osg::Geometry * point = new osg::Geometry;
			osg::Vec3Array * vertices = new osg::Vec3Array;
			osg::Vec4Array * colors = new osg::Vec4Array;
			osg::Point * pointObj = new osg::Point();
			pointObj->setSize(size);

			vertices->push_back(pos);
			colors->push_back(color);

			point->setVertexArray(vertices);
			point->setColorArray(colors);
			point->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

			point->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
			point->getOrCreateStateSet()->setAttributeAndModes(pointObj, osg::StateAttribute::ON);//���õ����

			point->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, vertices->size()));
			pointGeode->addDrawable(point);
			return pointGeode;
		}

		//���ƾ��νڵ�
		osg::Node* drawQuads(osg::Vec4dArray* pColorArray, osg::Vec3Array* pVertexArray)
		{
			osg::ref_ptr<osg::Geode> geode = new osg::Geode();
			osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

			geom->setVertexArray(pVertexArray);
			/*osg::ref_ptr<osg::Vec4dArray> colorArray = new osg::Vec4dArray;
			colorArray->push_back(osg::Vec4d(169.0/255,169.0/255,169.0/255,1.0));*/
			geom->setColorArray(pColorArray);
			geom->setColorBinding(osg::Geometry::BIND_OVERALL);
			geom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, pVertexArray->size()));
			geode->addDrawable(geom.get());
			geode->setName("quadtunnel"); //��������ɽ�������������,Ϊƽ��������
			return geode.release();
		}

		//Բ׶��ͷ
		//ԭ����Բ׶���㣬Z���ɵ�������ָ�򶥵�
		osg::Node* coneArrow(const float radius, const float height)
		{
			//�����������ԭ��
			osg::Cone* cone = new osg::Cone(osg::Vec3(0.0f, 0.0f, 0.0f), radius, height);
			float baseOffset = cone->getBaseOffsetFactor()*height;
			cone->setCenter(osg::Vec3(0.0f, 0.0f, -(height - baseOffset)));

			//����Բ׶
			osg::Geode* geode = new osg::Geode();
			geode->addDrawable(new osg::ShapeDrawable(cone));
			geode->getOrCreateStateSet()->setMode(GL_NORMALIZE, osg::StateAttribute::ON | osg::StateAttribute::PROTECTED);
			return geode;
		}

		//���Ǽ�ͷ
		osg::Node* triangleArrow(const float radius, const float height, const float width)
		{
			//����������
			osg::Group* tri = new osg::Group();
			tri->addChild(drawLine(osg::Vec3(radius, 0, -height), osg::Vec3(-radius, 0, -height), width*0.5f));
			tri->addChild(drawLine(osg::Vec3(radius, 0, -height), osg::Vec3(0, 0, 0), width*0.5f));
			tri->addChild(drawLine(osg::Vec3(-radius, 0, -height), osg::Vec3(0, 0, 0), width*0.5f));

			//�Զ�����
			osg::AutoTransform* at = new osg::AutoTransform;
			at->addChild(tri);
			at->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_AXIS);
			at->setAxis(osg::Z_AXIS);
			at->setAutoScaleToScreen(true);
			at->setMinimumScale(0.0);
			at->setMaximumScale(FLT_MAX);
			return at;
		}

		//ʮ�ּ�ͷ
		osg::Node* crossArrow(const float width, const float scale, const osg::Vec4 color)
		{
			float len = width*scale;
			osg::Group* cross = new osg::Group();
			cross->addChild(drawLine(osg::Vec3(len, len, 0), osg::Vec3(-len, -len, 0), width));
			cross->addChild(drawLine(osg::Vec3(-len, len, 0), osg::Vec3(len, -len, 0), width));

			//�Զ�����
			osg::AutoTransform* at = new osg::AutoTransform;
			at->addChild(cross);
			at->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_SCREEN);
			//at->setAxis(osg::Z_AXIS);
			at->setAutoScaleToScreen(true);
			at->setMinimumScale(0.0);
			at->setMaximumScale(FLT_MAX);
			return cross;
		}

		void seNodeColor(const osg::Vec4& color, osg::Node* node)
		{
			osg::Material* mat = dynamic_cast<osg::Material*>(node->getOrCreateStateSet()->getAttribute(osg::StateAttribute::MATERIAL));
			if (!mat)
			{
				mat = new osg::Material;
				mat->setDataVariance(osg::Object::DYNAMIC);
				node->getOrCreateStateSet()->setAttribute(mat);
			}
			mat->setDiffuse(osg::Material::FRONT_AND_BACK, color);
		}

		//���������
		osg::Polytope getPolytope(float x, float y, float rad, size_t num)
		{
			osg::Polytope pt;
			float angleDelta = osg::PI*2.0f / (float)num;
			float angle = 0.0f;
			for (size_t bodyi = 0; bodyi < num; ++bodyi, angle += angleDelta)
			{
				float c = cosf(angle);
				float s = sinf(angle);
				float d = -osg::Vec3(x + c*rad, y + s*rad, 0)*osg::Vec3(-c, -s, 0.0f);
				pt.add(osg::Plane(-c, -s, 0.0f, d));
			}
			pt.add(osg::Plane(0.0, 0.0, 1.0, 0));
			return pt;
		}

		osg::Node* drawPolygon(osg::Vec3Array* vertexs, const osg::Vec4 color, float width /*= 3.0f*/)
		{
			osg::ref_ptr<osg::Geode> geode = new osg::Geode;
			osg::Geometry * geom = new osg::Geometry;
			osg::Vec4Array * colorArray = new osg::Vec4Array;
			colorArray->push_back(color);

			geom->setVertexArray(vertexs);
			geom->setColorArray(colorArray);
			geom->setColorBinding(osg::Geometry::BIND_OVERALL);

			geom->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
			osg::LineWidth * linewidth = new osg::LineWidth;
			linewidth->setWidth(width);
			geom->getOrCreateStateSet()->setAttributeAndModes(linewidth, osg::StateAttribute::ON);//�����߿�
			geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP, 0, vertexs->size()));
			geode->addDrawable(geom);
			return geode.release();
		}

		osg::Node* DrawTriFlag()
		{
			osg::ref_ptr<osg::Geometry> triangle = new osg::Geometry;
			osg::ref_ptr<osg::Geode> geode = new osg::Geode;

			osg::ref_ptr<osg::Vec3Array> Tvertex = new osg::Vec3Array;
			triangle->setVertexArray(Tvertex.get());
			Tvertex->push_back(osg::Vec3(-20.0, 0.0, -10.0));
			Tvertex->push_back(osg::Vec3(0.0, 0.0, -10.0));
			Tvertex->push_back(osg::Vec3(-10.0, 0.0, 10.0));

			/** set the color */
			osg::ref_ptr<osg::Vec3Array> Tcolor = new osg::Vec3Array;
			triangle->setColorArray(Tcolor.get());
			triangle->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
			Tcolor->push_back(osg::Vec3(1.0, 0.0, 0.0));
			Tcolor->push_back(osg::Vec3(1.0, 0.0, 0.0));
			Tcolor->push_back(osg::Vec3(1.0, 0.0, 0.0));

			/** set the normal*/
			osg::ref_ptr<osg::Vec3Array> Tnormal = new osg::Vec3Array;
			Tnormal->push_back(osg::Vec3(0.0, -1.0, 0.0));
			triangle->setNormalArray(Tnormal.get());
			triangle->setNormalBinding(osg::Geometry::BIND_OVERALL);

			/** set the Primitive use GL_TRIANGLES*/
			osg::ref_ptr<osg::PrimitiveSet> Tprimitive = new osg::DrawArrays(GL_TRIANGLES, 0, 3);
			triangle->addPrimitiveSet(Tprimitive.get());
			geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
			geode->addDrawable(triangle.get());
			return geode.release();
		}


		/*************************************************************************************************************************************************************************************************/
		//function: ����͸������
		void drawForDiaphaneity(osg::MatrixTransform* vTranNode, float vRatio)
		{
			//�򿪻���ں�ģʽ
			vTranNode->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
			vTranNode->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
			vTranNode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
			vTranNode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
			vTranNode->getOrCreateStateSet()->setRenderBinDetails(11, "RenderBin");
			//ʹ��BlendFuncʵ��͸��Ч��
			osg::BlendColor* bc = new osg::BlendColor(osg::Vec4(1.0, 1.0, 1.0, 0.0));
			osg::BlendFunc*bf = new osg::BlendFunc();
			vTranNode->getOrCreateStateSet()->setAttributeAndModes(bf, osg::StateAttribute::ON);
			vTranNode->getOrCreateStateSet()->setAttributeAndModes(bc, osg::StateAttribute::ON);
			bf->setSource(osg::BlendFunc::CONSTANT_ALPHA);
			bf->setDestination(osg::BlendFunc::ONE_MINUS_CONSTANT_ALPHA);
			bc->setConstantColor(osg::Vec4(1, 1, 1, vRatio));
		}

		/**************************************************************************************************************************************************************************/
		//function ��create?white?material
		void createMatrial(osg::Geode* vGeode)
		{
			osg::Material *material = new osg::Material();
			material->setDiffuse(osg::Material::FRONT, osg::Vec4(240.0 / 255, 230.0 / 255.0, 140.0 / 255.0, 1.0));
			//material->setDiffuse(osg::Material::FRONT_AND_BACK,vColor);
			material->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 1.0, 1.0, 1.0));
			//material->setAmbient(osg::Material::FRONT_AND_BACK,vColor);
			material->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(240.0 / 255, 230.0 / 255.0, 140.0 / 255.0, 1.0));
			material->setEmission(osg::Material::FRONT_AND_BACK, osg::Vec4(0.8, 0.8, 0.8, 1.0));
			material->setShininess(osg::Material::FRONT_AND_BACK, 50.0);
			//assign the material to irregular (�쳣��)
			vGeode->getOrCreateStateSet()->setAttribute(material);
		}

		/**************************************************************************************************************************************************************************/
		//function ��create?white?material
		void createMatrial(osg::Group* vGroupNode)
		{
			osg::Material *material = new osg::Material();
			material->setDiffuse(osg::Material::FRONT, osg::Vec4(240.0 / 255, 230.0 / 255.0, 140.0 / 255.0, 1.0));
			//material->setDiffuse(osg::Material::FRONT_AND_BACK,vColor);
			material->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 1.0, 1.0, 1.0));
			//material->setAmbient(osg::Material::FRONT_AND_BACK,vColor);
			material->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(245.0 / 255, 245.0 / 255, 245.0 / 255, 1.0));
			material->setEmission(osg::Material::FRONT_AND_BACK, osg::Vec4(0.8, 0.8, 0.8, 1.0));
			material->setShininess(osg::Material::FRONT_AND_BACK, 50.0);
			//assign the material to irregular (�쳣��)
			vGroupNode->getOrCreateStateSet()->setAttribute(material);
		}

		/**************************************************************************************************************************************************************************/
		//function ��create?white?material
		void createMatrial(osg::MatrixTransform* vTransNode)
		{
			osg::Material *material = new osg::Material();
			//material->setDiffuse(osg::Material::FRONT,osg::Vec4(240.0/255, 230.0/255.0, 140.0/255.0,1.0));
			material->setDiffuse(osg::Material::FRONT, osg::Vec4(1.0, 1.0, 1.0, 1.0));
			//material->setDiffuse(osg::Material::FRONT_AND_BACK,vColor);
			material->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 1.0, 1.0, 1.0));
			//material->setAmbient(osg::Material::FRONT_AND_BACK,vColor);
			material->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(245.0 / 255, 245.0 / 255, 245.0 / 255, 1.0));
			material->setEmission(osg::Material::FRONT_AND_BACK, osg::Vec4(0.8, 0.8, 0.8, 1.0));
			material->setShininess(osg::Material::FRONT_AND_BACK, 50.0);
			//assign the material to irregular (�쳣��)
			vTransNode->getOrCreateStateSet()->setAttribute(material);
		}

		/*************************************************************************************************************************************************************************************************/
		//function: ����͸������
		void  drawForDiaphaneity(osg::Geode* vGeode)
		{
			//�򿪻���ں�ģʽ
			vGeode->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
			//vGeode->getOrCreateStateSet()->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
			vGeode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

			vGeode->getOrCreateStateSet()->setRenderBinDetails(11, "RenderBin");

			//ʹ��BlendFuncʵ��͸��Ч��
			osg::BlendColor* bc = new osg::BlendColor(osg::Vec4(1.0, 1.0, 1.0, 0.0));
			osg::BlendFunc*bf = new osg::BlendFunc();
			vGeode->getOrCreateStateSet()->setAttributeAndModes(bf, osg::StateAttribute::ON);
			vGeode->getOrCreateStateSet()->setAttributeAndModes(bc, osg::StateAttribute::ON);
			bf->setSource(osg::BlendFunc::CONSTANT_ALPHA);
			bf->setDestination(osg::BlendFunc::ONE_MINUS_CONSTANT_ALPHA);
			bc->setConstantColor(osg::Vec4(1, 1, 1, 0.5));
		}

		/*************************************************************************************************************************************************************************************************/
		//function: ����͸������
		void  drawForDiaphaneity(osg::Node* vNode, float ratio)
		{
			osg::BlendColor* bc = NULL;
			osg::Group* pNodeGroup = dynamic_cast<osg::Group*>(vNode);
			if (NULL != pNodeGroup)
			{
				for (int i = 0; i < pNodeGroup->getNumChildren(); i++)
				{
					osg::Node* pDiapNode = pNodeGroup->getChild(i);

					bc = static_cast<osg::BlendColor*>(pDiapNode->getOrCreateStateSet()->getAttribute(osg::StateAttribute::BLENDCOLOR, 0));
					if (NULL != bc)
					{
						bc->setConstantColor(osg::Vec4(1, 1, 1, ratio));
						continue;
					}
					//�򿪻���ں�ģʽ
					pDiapNode->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
					pDiapNode->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
					pDiapNode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

					pDiapNode->getOrCreateStateSet()->setRenderBinDetails(11, "RenderBin");

					//ʹ��BlendFuncʵ��͸��Ч��
					bc = new osg::BlendColor(osg::Vec4(1.0, 1.0, 1.0, ratio));
					osg::BlendFunc*bf = new osg::BlendFunc();
					pDiapNode->getOrCreateStateSet()->setAttributeAndModes(bf, osg::StateAttribute::ON);
					pDiapNode->getOrCreateStateSet()->setAttributeAndModes(bc, osg::StateAttribute::ON);
					bf->setSource(osg::BlendFunc::CONSTANT_ALPHA);
					bf->setDestination(osg::BlendFunc::ONE_MINUS_CONSTANT_ALPHA);
					bc->setConstantColor(osg::Vec4(1.0, 1.0, 1.0, ratio));
				}
			}
			else
			{
				bc = static_cast<osg::BlendColor*>(vNode->getOrCreateStateSet()->getAttribute(osg::StateAttribute::BLENDCOLOR, 0));
				if (NULL != bc)
				{
					bc->setConstantColor(osg::Vec4(1, 1, 1, ratio));
					return;
				}
				//�򿪻���ں�ģʽ
				vNode->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
				vNode->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
				vNode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
				vNode->getOrCreateStateSet()->setRenderBinDetails(11, "RenderBin");

				//ʹ��BlendFuncʵ��͸��Ч��
				bc = new osg::BlendColor(osg::Vec4(1.0, 1.0, 1.0, ratio));
				osg::BlendFunc*bf = new osg::BlendFunc();
				vNode->getOrCreateStateSet()->setAttributeAndModes(bf, osg::StateAttribute::ON);
				vNode->getOrCreateStateSet()->setAttributeAndModes(bc, osg::StateAttribute::ON);
				bf->setSource(osg::BlendFunc::CONSTANT_ALPHA);
				bf->setDestination(osg::BlendFunc::ONE_MINUS_CONSTANT_ALPHA);
				bc->setConstantColor(osg::Vec4(1.0, 1.0, 1.0, ratio));
			}
		}

		/*************************************************************************************************************************************************************************************************/
		//function: ʵ��������������
		void drawNodeForLine(osg::Node* vNode)
		{
			osg::PolygonMode *pLolyTotalMode = static_cast<osg::PolygonMode *>(vNode->getOrCreateStateSet()->getAttribute(osg::StateAttribute::POLYGONMODE, 0));
			if (NULL != pLolyTotalMode)
			{
				pLolyTotalMode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
			}
			else
			{
				osg::PolygonMode *pLolyTotalMode = new osg::PolygonMode();
				pLolyTotalMode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
				vNode->getOrCreateStateSet()->setAttribute(pLolyTotalMode);
				vNode->getOrCreateStateSet()->setAttributeAndModes(pLolyTotalMode, osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON);
			}
		}

		/*************************************************************************************************************************************************************************************************/
		//function: ʵ�����������������
		void drawNodeForFill(osg::Node* vNode)
		{
			osg::PolygonMode *pLolyTotalMode = static_cast<osg::PolygonMode *>(vNode->getOrCreateStateSet()->getAttribute(osg::StateAttribute::POLYGONMODE, 0));
			if (NULL != pLolyTotalMode)
			{
				pLolyTotalMode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::FILL);
			}
			else
			{
				osg::PolygonMode *pLolyTotalMode = new osg::PolygonMode();
				pLolyTotalMode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::FILL);
				vNode->getOrCreateStateSet()->setAttribute(pLolyTotalMode);
				vNode->getOrCreateStateSet()->setAttributeAndModes(pLolyTotalMode, osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON);
			}
		}

	} //namespace CommFunc
} //namespace osgEngine