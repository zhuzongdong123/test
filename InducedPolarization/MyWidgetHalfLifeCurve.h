#pragma once
//半衰时成像
#include "3ddisplay/ViewerWidget2d.h"
#include <osg/Point>
#include <osg/LineWidth>

class MyWidgetHalfLifeCurve :public ViewerWidget
{
	Q_OBJECT
public:
	MyWidgetHalfLifeCurve(QWidget* parent = nullptr) :ViewerWidget(parent) 
	{
		m_freqPointArray = new osg::Vec2dArray;
	}

	void setPointArray(osg::ref_ptr<osg::Vec2dArray> vArray) 
	{
		m_freqPointArray->clear();
		m_freqPointArray = vArray; 

		create();
	}

	/****************************************************************************************************/
	//function: draw the dat data wave 
	void drawWave(osg::ref_ptr<osg::Vec2dArray> vPointArray, double vYValue)
	{
		osg::ref_ptr<osg::Vec3dArray> normalArray = new osg::Vec3dArray;
		normalArray->push_back(osg::Vec3d(0, 1, 0));
		osg::ref_ptr<osg::Vec4dArray> pColorArray = new osg::Vec4dArray;
		pColorArray->push_back(osg::Vec4d(1.0, 0, 0.0, 1.0));

		osg::ref_ptr<osg::Geode> sameGeode = new osg::Geode;
		osg::ref_ptr<osg::Geometry> geomLine = new osg::Geometry;
		geomLine->setVertexArray(vPointArray.get());
		geomLine->setNormalArray(normalArray.get());
		geomLine->setNormalBinding(osg::Geometry::BIND_OVERALL);
		geomLine->setColorArray(pColorArray);
		geomLine->setColorBinding(osg::Geometry::BIND_OVERALL);
		geomLine->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP, 0, vPointArray->size()));
		sameGeode->addDrawable(geomLine.get());

		osg::ref_ptr<osg::Geometry> geometryPoints = new osg::Geometry();
		geometryPoints->setVertexArray(vPointArray.get());
		geometryPoints->setColorArray(pColorArray.get());
		geometryPoints->setColorBinding(osg::Geometry::BIND_OVERALL);
		geometryPoints->setNormalArray(normalArray.get());
		geometryPoints->setNormalBinding(osg::Geometry::BIND_OVERALL);
		geometryPoints->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, vPointArray->size())); //设置关联方式

		//set the point size
		osg::ref_ptr <osg::Point> ptSize = new osg::Point;
		ptSize->setSize(2);
		sameGeode->getOrCreateStateSet()->setAttributeAndModes(ptSize.get(), osg::StateAttribute::ON);
		sameGeode->addDrawable(geometryPoints.get());
		sameGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
		
		osg::ref_ptr<osg::Vec4dArray> pFillColorArray = new osg::Vec4dArray;
		pFillColorArray->push_back(osg::Vec4d(0, 0, 1, 1.0));
		int startPos = 0;
		int endPos = 0;
		osg::ref_ptr<osg::Vec2dArray> pTriangleArray = new osg::Vec2dArray;

		double testAntai = vYValue;
		for (int j = 0; j < vPointArray->size(); j++)
		{
			if ((*vPointArray)[j].y() > testAntai)
			{
				if (endPos == (vPointArray->size() - 1) || (j == vPointArray->size()-1 && endPos > 0))
				{
					double x0 = (*vPointArray)[j].x();
					double y0 = (*vPointArray)[j].y();

					double x1 = (*vPointArray)[j - 1].x();
					double y1 = (*vPointArray)[j - 1].y();

					double b0 = y1 - ((y1 - y0) / (x1 - x0))*x1;

					double xTmpOne = ((testAntai)-b0) / ((y1 - y0) / (x1 - x0));
					
					pTriangleArray->push_back((*vPointArray)[j - 1]);
					pTriangleArray->push_back((*vPointArray)[j]);
					pTriangleArray->push_back(osg::Vec2d((*vPointArray)[j].x(), testAntai));

					pTriangleArray->push_back((*vPointArray)[j - 1]);
					pTriangleArray->push_back(osg::Vec2d((*vPointArray)[j - 1].x(), testAntai));
					pTriangleArray->push_back(osg::Vec2d((*vPointArray)[j].x(), testAntai));

					if (j > endPos)
					{
						double x2 = (*vPointArray)[j - endPos].x();
						double y2 = (*vPointArray)[j - endPos].y();

						double x3 = (*vPointArray)[j - endPos - 1].x();
						double y3 = (*vPointArray)[j - endPos - 1].y();

						double b1 = y3 - ((y3 - y2) / (x3 - x2))*x3;
						double xTmpTwo = ((testAntai)-b1) / ((y3 - y2) / (x3 - x2));

						pTriangleArray->push_back(osg::Vec2d(xTmpTwo, testAntai));
						pTriangleArray->push_back((*vPointArray)[j - endPos]);
						pTriangleArray->push_back(osg::Vec2d((*vPointArray)[j - endPos].x(), testAntai));
					}

					for (unsigned int mm = endPos - 1; mm > 0; mm--)
					{
						pTriangleArray->push_back((*vPointArray)[j - mm - 1]);
						pTriangleArray->push_back(osg::Vec2d((*vPointArray)[j - mm - 1].x(), testAntai));
						pTriangleArray->push_back(osg::Vec2d((*vPointArray)[j - mm].x(), testAntai));

						pTriangleArray->push_back((*vPointArray)[j - mm]);
						pTriangleArray->push_back(osg::Vec2d((*vPointArray)[j - mm].x(), testAntai));
						pTriangleArray->push_back((*vPointArray)[j - mm - 1]);
					}
					startPos = 0;
					endPos = 0;
				}
				endPos++;
			}
			else if (endPos >= 2)
			{
				double x0 = (*vPointArray)[j].x();
				double y0 = (*vPointArray)[j].y();

				double x1 = (*vPointArray)[j - 1].x();
				double y1 = (*vPointArray)[j - 1].y();

				double b0 = y1 - ((y1 - y0) / (x1 - x0))*x1;

				double xTmpOne = ((testAntai)-b0) / ((y1 - y0) / (x1 - x0));

				pTriangleArray->push_back(osg::Vec2d((*vPointArray)[j-1].x(), testAntai));
				pTriangleArray->push_back((*vPointArray)[j - 1]);
				pTriangleArray->push_back(osg::Vec2d(xTmpOne, testAntai));

				if (j > endPos)
				{
					double x2 = (*vPointArray)[j - endPos].x();
					double y2 = (*vPointArray)[j - endPos].y();

					double x3 = (*vPointArray)[j - endPos - 1].x();
					double y3 = (*vPointArray)[j - endPos - 1].y();
					double b1 = y3 - ((y3 - y2) / (x3 - x2))*x3;

					double xTmpTwo = ((testAntai)-b1) / ((y3 - y2) / (x3 - x2));

					pTriangleArray->push_back(osg::Vec2d(xTmpTwo, testAntai));
					pTriangleArray->push_back((*vPointArray)[j - endPos]);
					pTriangleArray->push_back(osg::Vec2d((*vPointArray)[j - endPos].x(), testAntai));
				}


				for (unsigned int mm = endPos - 1; mm > 0; mm--)
				{
					pTriangleArray->push_back((*vPointArray)[j - mm - 1]);
					pTriangleArray->push_back(osg::Vec2d((*vPointArray)[j - mm - 1].x(), testAntai));
					pTriangleArray->push_back(osg::Vec2d((*vPointArray)[j - mm].x(), testAntai));

					pTriangleArray->push_back((*vPointArray)[j - mm]);
					pTriangleArray->push_back(osg::Vec2d((*vPointArray)[j - mm].x(), testAntai));
					pTriangleArray->push_back((*vPointArray)[j - mm - 1]);
				}
				startPos = 0;
				endPos = 0;
			}
			else if (endPos == 1 && j >= 2)
			{
				double x0 = (*vPointArray)[j - 2].x();
				double y0 = (*vPointArray)[j - 2].y();

				double x1 = (*vPointArray)[j - 1].x();
				double y1 = (*vPointArray)[j - 1].y();

				double x2 = (*vPointArray)[j].x();
				double y2 = (*vPointArray)[j].y();

				double b0 = y1 - ((y1 - y0) / (x1 - x0))*x1;
				double b1 = y2 - ((y2 - y1) / (x2 - x1))*x2;

				double xTmpOne = ((testAntai)-b0) / ((y1 - y0) / (x1 - x0));
				double xTmpTwo = ((testAntai)-b1) / ((y2 - y1) / (x2 - x1));
				
				pTriangleArray->push_back(osg::Vec2d(xTmpOne, testAntai));
				pTriangleArray->push_back((*vPointArray)[j-1]);
				pTriangleArray->push_back(osg::Vec2d(xTmpTwo, testAntai));

				startPos = 0;
				endPos = 0;
			}
			else if (endPos == 1 && j == 1)
			{
				double x1 = (*vPointArray)[j - 1].x();
				double y1 = (*vPointArray)[j - 1].y();

				double x2 = (*vPointArray)[j].x();
				double y2 = (*vPointArray)[j].y();

				double b1 = y2 - ((y2 - y1) / (x2 - x1))*x2;

				double xTmp = ((testAntai) - b1) / ((y2 - y1) / (x2 - x1));

				pTriangleArray->push_back(osg::Vec2d(xTmp, testAntai));
				pTriangleArray->push_back((*vPointArray)[j]);
				pTriangleArray->push_back(osg::Vec2d(x2, testAntai));

				startPos = 0;
				endPos = 0;
			}
		}

		osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
		geom->setVertexArray(pTriangleArray.get());
		geom->setNormalArray(normalArray.get());
		geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
		geom->setColorArray(pFillColorArray);
		geom->setColorBinding(osg::Geometry::BIND_OVERALL);
		geom->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLES, 0, pTriangleArray->size()));
		sameGeode->addDrawable(geom.get());
		osg::StateSet* textStateset = sameGeode->getOrCreateStateSet();
		textStateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);

		if (pTriangleArray->size() >= 3)
		{
			double halfDeclineArea = calculateHalfDeclineArea(pTriangleArray.get());
			emit setHalfDeclineAreaValue(QString::number(halfDeclineArea));
		}
		
		m_orthoCamera->addChild(sameGeode.get());
	}

	//计算半衰时断面面积
	double calculateHalfDeclineArea(osg::ref_ptr<osg::Vec2dArray> triangleArray)
	{
		double area = 0;
		for (unsigned int i = 0; i < triangleArray->size()-3; i+=3)
		{
			double side[3];//存储三条边的长度;
			osg::Vec2d a = (*triangleArray)[i];
			osg::Vec2d b = (*triangleArray)[i+1];
			osg::Vec2d c = (*triangleArray)[i+2];

			side[0] = sqrt(pow((a.x() - b.x()) / m_wRatio, 2) + pow((a.y() - b.y()) / m_hRatio, 2));
			side[1] = sqrt(pow((a.x() - c.x()) / m_wRatio, 2) + pow((a.y() - c.y()) / m_hRatio, 2));
			side[2] = sqrt(pow((c.x() - b.x()) / m_wRatio, 2) + pow((c.y() - b.y()) / m_hRatio, 2));
			
			//不能构成三角形;
			if (side[0] + side[1] <= side[2] || side[0] + side[2] <= side[1] || side[1] + side[2] <= side[0])
				return area;

			//利用海伦公式。double s = sqrt(p*(p - a)(p - b)(p - c));
			double p = (side[0] + side[1] + side[2]) / 2; //半周长;	
			area += sqrt(p*(p - side[0])*(p - side[1])*(p - side[2]));
		}
		return area;
	}

	virtual void resizeEvent(QResizeEvent *e)
	{
		ViewerWidget::resizeEvent(e);
	}

	virtual ~MyWidgetHalfLifeCurve() {}

	public slots:

private:
	/**
	* @brief 初始化
	*/
	void initialization() {}

	void create()
	{
		createOrthoCamera(this->width(), this->height());
		changeCameraToOrtho2D();
		m_orthoCamera->removeChild(0, m_orthoCamera->getNumChildren());

		if (m_freqPointArray->size() == 0) return;

		float yAxisMaxValue = -10000000;
		float yAxisMinValue = 10000000;
		int width = this->width();
		int height = this->height();
		//取得x轴的最大值
		float freqXMax = (*m_freqPointArray)[m_freqPointArray->size() - 1].x();
		float freqXMin = (*m_freqPointArray)[0].x();
		for (int j = 0; j < m_freqPointArray->size(); j++)
		{
			if (yAxisMaxValue < (*m_freqPointArray)[j].y())
				yAxisMaxValue = (*m_freqPointArray)[j].y();
			if (yAxisMinValue >(*m_freqPointArray)[j].y())
				yAxisMinValue = (*m_freqPointArray)[j].y();
		}

		freqXMin = 0;

		m_hRatio = (height*0.9) / (yAxisMaxValue - yAxisMinValue);
		m_wRatio = (width*0.9) / (freqXMax - freqXMin);
		if (yAxisMaxValue - yAxisMinValue > freqXMax - freqXMin)
		{
			m_wRatio = m_hRatio;
		}
		else 
		{
			m_hRatio = m_wRatio;
		}
		
		osg::ref_ptr<osg::Vec2dArray> axisPointArray = new osg::Vec2dArray;
		axisPointArray->push_back(osg::Vec2d(0, (0 - yAxisMinValue)*m_hRatio));
		axisPointArray->push_back(osg::Vec2d(width, (0 - yAxisMinValue)*m_hRatio));

		double xBegin = 0.05 * width;
		double yBegin = 0.05 * height;
		xBegin = 0;
		yBegin = 0;

		double yValue = ((0 - yAxisMinValue)*m_hRatio);
		for (int j = 0; j < m_freqPointArray->size(); j++)
		{
			(*m_freqPointArray)[j].x() = xBegin + ((*m_freqPointArray)[j].x() - freqXMin)*m_wRatio;
			(*m_freqPointArray)[j].y() = yBegin + ((*m_freqPointArray)[j].y() - yAxisMinValue)*m_hRatio;
		}

		osg::ref_ptr<osg::Vec3dArray> normalArray = new osg::Vec3dArray;
		normalArray->push_back(osg::Vec3d(0, 1, 0));
		osg::ref_ptr<osg::Vec4dArray> pColorArray = new osg::Vec4dArray;
		pColorArray->push_back(osg::Vec4d(1.0, 0, 0.0, 1.0));

		osg::ref_ptr<osg::Geode> sameGeode = new osg::Geode;
		osg::ref_ptr<osg::Geometry> geomLine = new osg::Geometry;
		geomLine->setVertexArray(axisPointArray.get());
		geomLine->setNormalArray(normalArray.get());
		geomLine->setNormalBinding(osg::Geometry::BIND_OVERALL);
		geomLine->setColorArray(pColorArray);
		geomLine->setColorBinding(osg::Geometry::BIND_OVERALL);
		geomLine->addPrimitiveSet(new osg::DrawArrays(GL_LINES, 0, axisPointArray->size()));
		sameGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
		sameGeode->addDrawable(geomLine.get());
		m_orthoCamera->addChild(sameGeode.get());

		drawWave(m_freqPointArray.get(), yValue);
		getMyViewer()->setSceneData(getSceneRoot());

		float maxValue;
		if (yValue > (height/ 2))
		{
			maxValue = fabs(yAxisMinValue) - (yValue - float(height) / 2) * 2 * (fabs(yAxisMinValue) * 2 / float(height));
		}
		else
		{
			maxValue = fabs(yAxisMinValue) + (fabs(yAxisMinValue)/ yValue)*(height- yValue*2);
		}
		emit reDraw(yAxisMinValue, maxValue,"MyWidgetHalfLifeCurve");

		float xMaxPos = freqXMax*m_wRatio;
		maxValue = (width*freqXMax) / xMaxPos;
		emit redrawCoordinateVText(0, maxValue,"MyWidgetHalfLifeCurve");
	}

signals:
	void setHalfDeclineAreaValue(QString text);

	void reDraw(double minValue, double maxValue,QString name);
	void redrawCoordinateVText(float begChannelDis, float endChannelDis, QString name);

private:
	double m_hRatio;
	double m_wRatio;
	osg::ref_ptr<osg::Vec2dArray> m_freqPointArray;
};