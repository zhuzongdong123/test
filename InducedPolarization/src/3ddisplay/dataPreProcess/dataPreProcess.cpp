#include "dataPreProcess/dataPreProcess.h"
#include <osg/Point>
#include <osg/LineWidth>


DataPreprocess::DataPreprocess(QWidget *parent) :ViewerWidget(parent)
{
	changeCameraToOrtho2D();
	createOrthoCamera(this->width(), this->height());
	m_pViewer->setSceneData(m_SceneGroup); //将模型添加到渲染器中

	m_maxValue = 0.0;
	m_maxWidth = 100;

	QSize picSize(100, 79);
	_originPixmap = shared_ptr<QPixmap>(new QPixmap(":/InducedPolarization/buttonImages/Legend.png"));
	QPixmap fitpixmap = _originPixmap->scaled(parent->width() / 7.0f, parent->width() / 7.0f / 1.266903914590747f, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	//QPixmap p2 = pix.scaled(picSize);
	m_legendLabel = shared_ptr<QLabel>(new QLabel(this));
	m_legendLabel->setPixmap(fitpixmap);
	m_legendLabel->setFixedSize(fitpixmap.size());
	int wdit = parent->width();
	m_isReDraw = false;
}

/******************************************************************************************************************/
//function:绘制背景虚线
void DataPreprocess::drawBackgroundLine(float windWidth, float windHeight)
{
	//取得y轴方向每个横线之间的间隔距离<注:设定10个间隔>
	unsigned int interTextNum = 10;

	//创建保存几何信息的对象
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	geode->getOrCreateStateSet()->setAttribute(new osg::LineWidth(2.0), osg::StateAttribute::ON);

	//创建虚线顶点
	osg::ref_ptr<osg::Vec2dArray> dotted_line = new osg::Vec2dArray();
	
	float distance_y = (float)(windHeight) / interTextNum;
	for (int i = 1; i <= interTextNum; i++)
	{
		dotted_line->push_back(osg::Vec2d(0, distance_y*i));
		dotted_line->push_back(osg::Vec2d(windWidth + interTextNum, distance_y*i));
	}

	//设置虚线的颜色和粗细
	osg::ref_ptr<osg::Geometry> geomDottedLine = new osg::Geometry();
	geomDottedLine->setVertexArray(dotted_line.get());

	//三个轴
	geomDottedLine->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, dotted_line->size()));

	//设置坐标颜色
	osg::ref_ptr<osg::Vec3Array> pColor = new osg::Vec3Array;
	pColor->push_back(osg::Vec3d(0.5, 0.5, 0.5));
	geomDottedLine->setColorArray(pColor.get());
	geomDottedLine->setColorBinding(osg::Geometry::BIND_OVERALL);

	geomDottedLine->getOrCreateStateSet()->setAttribute(new osg::LineWidth(0.5), osg::StateAttribute::ON);
	geode->addDrawable(geomDottedLine.get());	//添加虚线

	getOrthoCamera()->addChild(geode);
}

void DataPreprocess::resizeEvent(QResizeEvent *e)
{
	unsigned int width2 = m_legendLabel->width();
	m_legendLabel->move(width() - m_legendLabel->width(), 0);

	if (this->height() > 100 && !m_isReDraw)
	{
		emit reDraw();
		m_isReDraw = true;
	}

	ViewerWidget::resizeEvent(e);
	//m_legendLabel->move(((ViewerWidget*)parent())->width() + 50, 0);
}

/******************************************************************************************************************/
//function:绘制顶点
void DataPreprocess::drawPreDataPoints(osg::ref_ptr<osg::Vec2dArray> pPointsArray, osg::Vec4d vColor, DataType type)
{
	osg::ref_ptr<osg::Vec3dArray> normalArray = new osg::Vec3dArray;
	normalArray->push_back(osg::Vec3d(0, 1, 0));
	osg::ref_ptr<osg::Vec4dArray> pColorArray = new osg::Vec4dArray;
	pColorArray->push_back(vColor);

	osg::ref_ptr<osg::Geometry> geomPoints = new osg::Geometry;
	geomPoints->setVertexArray(pPointsArray.get());
	geomPoints->setNormalArray(normalArray.get());
	geomPoints->setNormalBinding(osg::Geometry::BIND_OVERALL);
	geomPoints->setColorArray(pColorArray.get());
	geomPoints->setColorBinding(osg::Geometry::BIND_OVERALL);
	geomPoints->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, pPointsArray->size()));

	osg::ref_ptr<osg::Geode> sameGeode = new osg::Geode;
	if (type == DataType::ajustData)
		sameGeode->setName("adjustPointGeode");
	sameGeode->addDrawable(geomPoints.get());

	//set the point size
	osg::ref_ptr <osg::Point> ptSize = new osg::Point;
	ptSize->setSize(8);
	
	osg::StateSet* geodStateset = sameGeode->getOrCreateStateSet();
	geodStateset->setAttributeAndModes(ptSize.get(), osg::StateAttribute::ON);
	geodStateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);//取消深度测试
	geodStateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);

	getOrthoCamera()->addChild(sameGeode.get());
	
}

/******************************************************************************************************************/
//function:绘制二维曲线
void DataPreprocess::drawPointsLine(osg::ref_ptr<osg::Vec2dArray> pPointsArray,osg::Vec4d vColor, DataType type)
{
	osg::ref_ptr<osg::Vec3dArray> normalArray = new osg::Vec3dArray;
	normalArray->push_back(osg::Vec3d(0, 1, 0));
	osg::ref_ptr<osg::Vec4dArray> pColorArray = new osg::Vec4dArray;
	pColorArray->push_back(vColor);
    
	osg::ref_ptr<osg::Geometry> geomLine = new osg::Geometry;
	geomLine->setVertexArray(pPointsArray.get());
	geomLine->setNormalArray(normalArray.get());
	geomLine->setNormalBinding(osg::Geometry::BIND_OVERALL);
	geomLine->setColorArray(pColorArray.get());
	geomLine->setColorBinding(osg::Geometry::BIND_OVERALL);
	geomLine->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP, 0, pPointsArray->size()));

	osg::ref_ptr<osg::Geode> sameGeode = new osg::Geode;
	if (type == DataType::ajustData)
		sameGeode->setName("adjustLineGeode");
	sameGeode->addDrawable(geomLine.get());

	osg::StateSet* geodStateset = sameGeode->getOrCreateStateSet();
	geodStateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);//取消深度测试
	geodStateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
	geodStateset->setAttribute(new osg::LineWidth(1.5), osg::StateAttribute::ON);
	getOrthoCamera()->addChild(sameGeode.get());
}

double DataPreprocess::getVariance(std::vector<double> resultVec)
{
	double sumPre = std::accumulate(std::begin(resultVec), std::end(resultVec), 0.0);
	double meanPre = sumPre / resultVec.size(); //均值  
	double accumPre = 0.0;
	std::for_each(std::begin(resultVec), std::end(resultVec), [&](const double d) {
		accumPre += (d - meanPre)*(d - meanPre);
	});
	double stdev = sqrt(accumPre / (resultVec.size() - 1)); //方差
	return stdev;
}

void DataPreprocess::clearLinesData()
{
	getOrthoCamera()->removeChildren(0, getOrthoCamera()->getNumChildren());
}

std::vector<float> DataPreprocess::adjustPointYValue()
{
	std::vector<float> yValueVec = this->getPickHandle()->getAdjustPointYVec();
	int windHeight = this->height();
	float radioY = float(m_maxValue) / float(windHeight);
	for (int i = 0; i < yValueVec.size(); i ++)
	{
		yValueVec[i] *= radioY;
	}
	return yValueVec;
}

void DataPreprocess::draw(std::vector<double> resultDataVec, osg::Vec4d vColor, DataType type)
{
	if (resultDataVec.size() == 0)	return;

	int windWidth = this->width();
	int windHeight = this->height();
	m_pViewer->getCamera()->setViewport(0, 0, windWidth, windHeight);
	m_pViewer->getCamera()->setProjectionMatrix(osg::Matrix::ortho2D(0.0, windWidth, 0.0, windHeight));
	getOrthoCamera()->setViewport(0, 0, windWidth, windHeight);
	getOrthoCamera()->setProjectionMatrix(osg::Matrix::ortho2D(0, windWidth, 0, windHeight));
	//getOrthoCamera()->removeChildren(0, getOrthoCamera()->getNumChildren());

	osg::ref_ptr<osg::Vec2dArray> dataPointsArray = new osg::Vec2dArray;
	float raidoX = float(windWidth) / float(m_maxWidth);
	float raidoY = float(windHeight) / float(m_maxValue);

	for (size_t i = 0; i < resultDataVec.size(); i++)
	{
		float value = resultDataVec[i] * raidoY;
		dataPointsArray->push_back(osg::Vec2d(i*raidoX, value));
	}

	drawPointsLine(dataPointsArray.get(), vColor, type);
	drawPreDataPoints(dataPointsArray.get(), vColor,type);
	drawBackgroundLine(windWidth, windHeight);
}
