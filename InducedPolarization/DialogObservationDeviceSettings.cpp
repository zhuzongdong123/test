#include "DialogObservationDeviceSettings.h"
#include "GlobalClass\GlobalParam.h"
#include <osgGA/TrackballManipulator>
#include <osgGA/CameraManipulator>

DialogObservationDeviceSettings::DialogObservationDeviceSettings(QWidget *parent /*= nullptr*/) : QDialog(parent)
{
    m_ui.setupUi(this);

    _defaultHeight = 100;
	m_measurePointNum = 0;

    if (!initTables())
    {
        return;
    }

    if (!importDatasFromGlobal())
    {
        return;
    }

	setValidator();

    QObject::connect(m_ui.update_param, SIGNAL(clicked()), this, SLOT(onTunnelParamUpdate()));
    QObject::connect(m_ui.lineEditFaceWidth, SIGNAL(editingFinished()), this, SLOT(onFaceWidthEditFinished()));
    QObject::connect(m_ui.lineEditFaceHeight, SIGNAL(editingFinished()), this, SLOT(onFaceHeightEditFinished()));
    QObject::connect(m_ui.lineEditFaceX, SIGNAL(editingFinished()), this, SLOT(onFaceXEditFinished()));
    QObject::connect(m_ui.lineEditFaceY, SIGNAL(editingFinished()), this, SLOT(onFaceYEditFinished()));
    QObject::connect(m_ui.lineEditFaceZ, SIGNAL(editingFinished()), this, SLOT(onFaceZEditFinished()));
	QObject::connect(m_ui.lineEditMileageNum, SIGNAL(editingFinished()), this, SLOT(onMileageNumberEditFinished()));

	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowMinMaxButtonsHint;
	flags |= Qt::WindowCloseButtonHint;

	m_ui.radioButton_tunnelGrid_3->setChecked(true);

    setWindowFlags(flags);

    m_measuringEdit = false;
    m_supplyEdit    = false;

    m_ui.pushButton_supply_edit->setEnabled(true);
    m_ui.pushButton_supply_update->setEnabled(false);

    m_ui.pushButton_measuring_edit->setEnabled(true);
    m_ui.pushButton_measuring_update->setEnabled(false);

    m_ui.tableWidgetSupply->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_ui.tableWidgetNew->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_ui.tableWidgetMeasuring->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

DialogObservationDeviceSettings::~DialogObservationDeviceSettings()
{
}

bool DialogObservationDeviceSettings::initTables()
{
    initTable(m_ui.tableWidgetSupply, 120, tr("供电点编号"));
    initTable(m_ui.tableWidgetMeasuring, 150, tr("测量点编号"));

    if (!initNewTable())
    {
        return false;
    }
    //currentIndexChanged
    QObject::connect(m_ui.pushButton_measuring_edit, SIGNAL(clicked()), this, SLOT(onMeasuringEditClick()));
    QObject::connect(m_ui.pushButton_supply_edit, SIGNAL(clicked()), this, SLOT(onSupplyEditClick()));
    QObject::connect(m_ui.pushButton_measuring_update, SIGNAL(clicked()), this, SLOT(onMesasuringUpdateClick()));
    QObject::connect(m_ui.pushButton_supply_update, SIGNAL(clicked()), this, SLOT(onSupplyUpdateClick()));
    QObject::connect(m_ui.comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxChanged(int)));
	QObject::connect(m_ui.comboBox_ExcavationDir, SIGNAL(currentIndexChanged(int)), this, SLOT(onExcavationDirChanged(int)));

    return true;
}

bool DialogObservationDeviceSettings::importDatasFromGlobal()
{
	float xMin = 0.0, xMax = 0.0, yMin = 0.0, yMax = 0.0, zMin = 0.0, zMax = 0.0;
	std::set<float> xSet,ySet;
	std::set<float>::iterator xSetIte, ySetIte;
    for (unsigned int i = 0; i < _defaultHeight; i++)
    {
        if (i >= GlobalParam::instance()->getObservationSystemSetting().powerSupplyPointData.size())
        {
            m_ui.tableWidgetSupply->item(i, 0)->setText("");
            m_ui.tableWidgetSupply->item(i, 1)->setText("");
            m_ui.tableWidgetSupply->item(i, 2)->setText("");
            m_ui.tableWidgetSupply->item(i, 3)->setText("");
        }
        else
        {
            osg::Vec3d &v = GlobalParam::instance()->getObservationSystemSetting().powerSupplyPointData[i];

            m_ui.tableWidgetSupply->item(i, 0)->setText(tr("编号") + QString::number(i + 1));
            m_ui.tableWidgetSupply->item(i, 1)->setText(QString::number(GlobalParam::instance()->getObservationSystemSetting().powerSupplyPointData[i].x()));
            m_ui.tableWidgetSupply->item(i, 2)->setText(QString::number(GlobalParam::instance()->getObservationSystemSetting().powerSupplyPointData[i].y()));
            m_ui.tableWidgetSupply->item(i, 3)->setText(QString::number(GlobalParam::instance()->getObservationSystemSetting().powerSupplyPointData[i].z()));

			xSet.insert(GlobalParam::instance()->getObservationSystemSetting().powerSupplyPointData[i].x());
			ySet.insert(GlobalParam::instance()->getObservationSystemSetting().powerSupplyPointData[i].y());
			zMax = GlobalParam::instance()->getObservationSystemSetting().powerSupplyPointData[i].z();
        }
    }

	if (xSet.size() != 0)
	{
		xMin = *xSet.begin();
		xSetIte = xSet.end();
		xMax = *(--xSetIte);
	}

	if (ySet.size() != 0)
	{
		yMin = *ySet.begin();
		ySetIte = ySet.end();
		yMax = *(--ySetIte);
	}	

	double circleDis = 0;
	int elecCircleSize = GlobalParam::instance()->getObservationSystemSetting().elecCircleDisVec.size();

	m_drawFaceDistance.clear();
    for (unsigned int i = 0; i < _defaultHeight; i++)
    {
        if (i >= GlobalParam::instance()->getObservationSystemSetting().elecCircleDisVec.size())
        {
            m_ui.tableWidgetNew->item(i, 0)->setText("");
            m_ui.tableWidgetNew->item(i, 1)->setText("");
        }
        else
        {
            double v = GlobalParam::instance()->getObservationSystemSetting().elecCircleDisVec[elecCircleSize - i - 1];
			double tableV = GlobalParam::instance()->getObservationSystemSetting().elecCircleDisVec[i];
            m_ui.tableWidgetNew->item(i, 0)->setText(tr("编号") + QString::number(i + 1));
            m_ui.tableWidgetNew->item(i, 1)->setText(QString::number(tableV));

			circleDis += v;
			m_drawFaceDistance.push_back(circleDis);
        }
    }

	m_drawFaceDistance.insert(m_drawFaceDistance.begin(), 0);

	m_measurePointNum = 0;
    for (unsigned int i = 0; i < _defaultHeight; i++)
    {
        if (i >= GlobalParam::instance()->getObservationSystemSetting().measuringPointData.size())
        {
            m_ui.tableWidgetMeasuring->item(i, 0)->setText("");
            m_ui.tableWidgetMeasuring->item(i, 1)->setText("");
            m_ui.tableWidgetMeasuring->item(i, 2)->setText("");
            m_ui.tableWidgetMeasuring->item(i, 3)->setText("");
        }
        else
        {
            osg::Vec3d &v = GlobalParam::instance()->getObservationSystemSetting().measuringPointData[i];
            m_ui.tableWidgetMeasuring->item(i, 0)->setText(tr("编号") + QString::number(i + 1));
            m_ui.tableWidgetMeasuring->item(i, 1)->setText(QString::number(GlobalParam::instance()->getObservationSystemSetting().measuringPointData[i].x()));
            m_ui.tableWidgetMeasuring->item(i, 2)->setText(QString::number(GlobalParam::instance()->getObservationSystemSetting().measuringPointData[i].y()));
            m_ui.tableWidgetMeasuring->item(i, 3)->setText(QString::number(GlobalParam::instance()->getObservationSystemSetting().measuringPointData[i].z()));
			m_measurePointNum++;
		}
    }

    m_ui.lineEditFaceWidth->setText(QString::number(GlobalParam::instance()->getObservationSystemSetting().faceWidth));
    m_ui.lineEditFaceHeight->setText(QString::number(GlobalParam::instance()->getObservationSystemSetting().faceHeight));
    m_ui.lineEditFaceX->setText(QString::number(GlobalParam::instance()->getObservationSystemSetting().facePosition.x()));
    m_ui.lineEditFaceY->setText(QString::number(GlobalParam::instance()->getObservationSystemSetting().facePosition.y()));
    m_ui.lineEditFaceZ->setText(QString::number(GlobalParam::instance()->getObservationSystemSetting().facePosition.z()));
    m_ui.comboBox->setCurrentIndex(int(GlobalParam::instance()->getObservationSystemSetting().deviceType));
	m_ui.comboBox_ExcavationDir->setCurrentIndex(int(GlobalParam::instance()->getObservationSystemSetting().excavationDir));
	m_ui.lineEditMileageNum->setText(GlobalParam::instance()->getObservationSystemSetting().mileageNumber);
	saveMileageNumber();

	//清空模型
	m_ui.widget_device->getSceneGroup()->removeChildren(0, m_ui.widget_device->getSceneGroup()->getNumChildren());

	//绘制供电点位置数据
	vector<osg::Vec3d>& pointsData = GlobalParam::instance()->getObservationSystemSetting().powerSupplyPointData;
	m_ui.widget_device->drawElectroPoints(pointsData, m_drawFaceDistance);

	//绘制测量点位置数据
	vector<osg::Vec3d>& lineData = GlobalParam::instance()->getObservationSystemSetting().measuringPointData;
	m_ui.widget_device->drawMeasurePointLine(lineData);

	//绘制隧道
	float elecFaceDis = m_drawFaceDistance[m_drawFaceDistance.size() - 1];
	int tunnelCircleCount = (int)elecFaceDis / 5 + 1;
	int eachCircleLen = 5;

	float faceWidth = GlobalParam::instance()->getObservationSystemSetting().faceWidth;
	float faceHeight = GlobalParam::instance()->getObservationSystemSetting().faceHeight;

	m_ui.widget_device->drawTunnel(eachCircleLen, tunnelCircleCount);
	zMin = -(tunnelCircleCount*eachCircleLen) + zMax;
	m_ui.widget_device->makeCoordinate(xMin, xMax, yMin, yMax, zMin, zMin + (tunnelCircleCount*eachCircleLen)/2);
	m_ui.widget_device->drawElecMesureTextFlag(m_drawFaceDistance, xMax, yMin, zMax);

	osg::ref_ptr<osgGA::TrackballManipulator> pCameraMani = new osgGA::TrackballManipulator;
	m_ui.widget_device->getViewer()->setCameraManipulator(pCameraMani.get());
	
	return true;
}

bool DialogObservationDeviceSettings::initTable(MyTableWidget *table, unsigned int width, QString indexName)
{
    table->setRowCount(_defaultHeight);
    table->setColumnCount(4);
    table->setWindowTitle(QString::fromUtf8("网格大小设置"));

    QStringList header;
    header << indexName
           << "XPos"
           << "YPos"
           << "ZPos";

    table->setHorizontalHeaderLabels(header);
    table->verticalHeader()->setVisible(false);

    QFont font = table->horizontalHeader()->font();
    font.setBold(true);
    table->horizontalHeader()->setFont(font);

    table->horizontalHeader()->setStretchLastSection(true);
    table->verticalHeader()->setDefaultSectionSize(20);
    table->setSelectionMode(QAbstractItemView::ExtendedSelection);
    table->horizontalHeader()->resizeSection(0, width);
    table->horizontalHeader()->resizeSection(1, width);
    table->horizontalHeader()->resizeSection(2, width);
    table->horizontalHeader()->setFixedHeight(25);

    table->setAutoComplete(tr("编号"));
    table->setStyleSheet("selection-background-color:lightblue;");

    for (unsigned int i = 0; i < _defaultHeight; i++)
    {
        for (unsigned int j = 0; j < 4; j++)
        {
            auto p = new QTableWidgetItem("");
            table->setItem(i, j, p);
        }
    }

    return true;
}

bool DialogObservationDeviceSettings::initNewTable()
{
    m_ui.tableWidgetNew->setRowCount(_defaultHeight);
    m_ui.tableWidgetNew->setColumnCount(2);
    m_ui.tableWidgetNew->setWindowTitle(QString::fromUtf8("网格大小设置"));
    m_ui.tableWidgetNew->setAutoComplete(tr("编号"));

    QStringList header;
    header << tr("电极圈编号")
           << tr("圈距离掌子面的距离");

    m_ui.tableWidgetNew->setHorizontalHeaderLabels(header);
    m_ui.tableWidgetNew->verticalHeader()->setVisible(false);

    QFont font = m_ui.tableWidgetNew->horizontalHeader()->font();
    font.setBold(true);
    m_ui.tableWidgetNew->horizontalHeader()->setFont(font);

    m_ui.tableWidgetNew->horizontalHeader()->setStretchLastSection(true);
    m_ui.tableWidgetNew->verticalHeader()->setDefaultSectionSize(20);
    m_ui.tableWidgetNew->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_ui.tableWidgetNew->horizontalHeader()->resizeSection(0, 130);
    m_ui.tableWidgetNew->horizontalHeader()->setFixedHeight(25);

    m_ui.tableWidgetNew->setStyleSheet("selection-background-color:lightblue;");

    for (unsigned int i = 0; i < _defaultHeight; i++)
    {
        for (unsigned int j = 0; j < 2; j++)
        {
            auto p = new QTableWidgetItem("");
            m_ui.tableWidgetNew->setItem(i, j, p);
        }
    }

    return true;
}

//void DialogObservationDeviceSettings::showEvent(QShowEvent *)
//{
//	m_ui.label_text->setGeometry(m_ui.widget_device->width() - 120, 2, m_ui.label_text->width(), m_ui.label_text->height());
//}

void DialogObservationDeviceSettings::onMileageNumberEditFinished()
{
	GlobalParam::instance()->getObservationSystemSetting().mileageNumber = m_ui.lineEditMileageNum->text();
}

void DialogObservationDeviceSettings::onTunnelParamUpdate()
{
    GlobalParam::instance()->getObservationSystemSetting().deviceType = (GlobalParam::DeviceType)m_ui.comboBox->currentIndex();
    GlobalParam::instance()->getObservationSystemSetting().faceHeight = m_ui.lineEditFaceHeight->text().toDouble();
    GlobalParam::instance()->getObservationSystemSetting().faceWidth = m_ui.lineEditFaceWidth->text().toDouble();
    GlobalParam::instance()->getObservationSystemSetting().facePosition.x() = m_ui.lineEditFaceX->text().toDouble();
    GlobalParam::instance()->getObservationSystemSetting().facePosition.y() = m_ui.lineEditFaceY->text().toDouble();
    GlobalParam::instance()->getObservationSystemSetting().facePosition.z() = m_ui.lineEditFaceZ->text().toDouble();
	saveMileageNumber();

    m_ui.widget_device->drawTunnel(5,10);

	textChanged();
	emit setAutoModeling(true);
}

void DialogObservationDeviceSettings::onSupplyEditClick()
{
    m_ui.pushButton_supply_edit->setEnabled(false);
    m_ui.pushButton_supply_update->setEnabled(true);

    m_ui.tableWidgetSupply->setLockState(false);
    m_ui.tableWidgetNew->setLockState(false);

	m_ui.tableWidgetSupply->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
	m_ui.tableWidgetNew->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);

    m_supplyEdit = true;
}

void DialogObservationDeviceSettings::onMeasuringEditClick()
{
    m_ui.pushButton_measuring_edit->setEnabled(false);
    m_ui.pushButton_measuring_update->setEnabled(true);

    m_ui.tableWidgetMeasuring->setLockState(false);
	m_ui.tableWidgetMeasuring->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);

    m_measuringEdit = true;
}

void DialogObservationDeviceSettings::onSupplyUpdateClick()
{
    m_ui.pushButton_supply_edit->setEnabled(true);
    m_ui.pushButton_supply_update->setEnabled(false);
    m_ui.tableWidgetSupply->setLockState(true);
    m_ui.tableWidgetNew->setLockState(true);

    m_ui.tableWidgetSupply->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_ui.tableWidgetNew->setEditTriggers(QAbstractItemView::NoEditTriggers);

    vector<osg::Vec3d> &pointsData = GlobalParam::instance()->getObservationSystemSetting().powerSupplyPointData;
    pointsData.clear();

    for (int i = 0; i < m_ui.tableWidgetSupply->rowCount(); i++)
    {
        osg::Vec3d v;
        bool bSet = false;

        for (int j = 0; j < m_ui.tableWidgetSupply->columnCount(); j++)
        {
			if (nullptr == m_ui.tableWidgetSupply->item(i, 0) ||
				nullptr == m_ui.tableWidgetSupply->item(i, 1) || 
				nullptr == m_ui.tableWidgetSupply->item(i, 2) || 
				nullptr == m_ui.tableWidgetSupply->item(i, 3))
			{
				continue;
			}

            if (m_ui.tableWidgetSupply->item(i, 0)->text() == "" && m_ui.tableWidgetSupply->item(i + 1 >= m_ui.tableWidgetSupply->columnCount() ? i : i + 1, 1)->text() != "")
            {
                m_ui.tableWidgetSupply->item(i, 0)->setText(tr("编号") + QString::number(i));
            }

            if (m_ui.tableWidgetSupply->item(i, j) == NULL || m_ui.tableWidgetSupply->item(i, j)->text() == "")
            {
                break;
            }

            if (0 == j)
            {
                continue;
            }
            else if (1 == j)
            {
                v.x() = m_ui.tableWidgetSupply->item(i, j)->text().toDouble();
            }
            else if (2 == j)
            {
                v.y() = m_ui.tableWidgetSupply->item(i, j)->text().toDouble();
            }
            else if (3 == j)
            {
                v.z() = m_ui.tableWidgetSupply->item(i, j)->text().toDouble();
            }

            bSet = true;
        }

        if (bSet)
        {
            pointsData.push_back(v);
        }
    }

    vector<double> &faceDistance = GlobalParam::instance()->getObservationSystemSetting().elecCircleDisVec;
    faceDistance.clear();
	m_drawFaceDistance.clear();

	unsigned rowCount = 0;

	bool isZeroOmega = false;
	bool bLast = true;
	double circleDis = 0;
    for (int i = m_ui.tableWidgetNew->rowCount() - 1 ; i >= 0 ; i--)
    {
        double v;
        bool bSet = false;

        for (int j = 0; j < m_ui.tableWidgetNew->columnCount(); j++)
        {
			if (nullptr == m_ui.tableWidgetNew->item(i, 0) ||
				nullptr == m_ui.tableWidgetNew->item(i, 1))
			{
				continue;
			}

            if (m_ui.tableWidgetNew->item(i, 0)->text() == "" && m_ui.tableWidgetNew->item(i + 1 >= m_ui.tableWidgetNew->columnCount() ? i : i + 1, 1)->text() != "")
            {
                m_ui.tableWidgetNew->item(i, 0)->setText(tr("编号") + QString::number(i));
            }

            if (m_ui.tableWidgetNew->item(i, 1) == NULL || m_ui.tableWidgetNew->item(i, 1)->text() == "")
            {
                break;
            }

            if (0 == j)
            {
                continue;
            }
            else if (1 == j)
            {
                v = m_ui.tableWidgetNew->item(i, j)->text().toDouble();
            }

			if (0 == v && bLast)
			{
				isZeroOmega = true;
				bLast = false;
			}

            bSet = true;
        }

        if (bSet)
        {
			rowCount++;

			circleDis += v;
			m_drawFaceDistance.push_back(circleDis);
			faceDistance.insert(faceDistance.begin(), v);
        }
    }

	if (!isZeroOmega)
	{
		circleDis += 0;
		m_drawFaceDistance.insert(m_drawFaceDistance.begin(), 0);
	}

    m_supplyEdit = false;

    //m_ui.widget_device->drawElectroPoints(pointsData, m_drawFaceDistance);
	//float faceWidth = GlobalParam::instance()->getObservationSystemSetting().faceWidth;
	//float faceHeight = GlobalParam::instance()->getObservationSystemSetting().faceHeight;
	//m_ui.widget_device->drawElecMesureTextFlag(m_drawFaceDistance, faceWidth / 2, -faceHeight / 2);

	importDatasFromGlobal();
	emit setAutoModeling(true);
}

void DialogObservationDeviceSettings::onMesasuringUpdateClick()
{
    m_ui.pushButton_measuring_edit->setEnabled(true);
    m_ui.pushButton_measuring_update->setEnabled(false);

    m_ui.tableWidgetMeasuring->setLockState(true);

    m_ui.tableWidgetMeasuring->setEditTriggers(QAbstractItemView::NoEditTriggers);

    vector<osg::Vec3d> &pointsData = GlobalParam::instance()->getObservationSystemSetting().measuringPointData;
    pointsData.clear();

    for (int i = 0; i < m_ui.tableWidgetMeasuring->rowCount(); i++)
    {
        osg::Vec3d v;
        bool bSet = false;

        for (int j = 0; j < m_ui.tableWidgetMeasuring->columnCount(); j++)
        {
			if (nullptr == m_ui.tableWidgetMeasuring->item(i, 0) ||
				nullptr == m_ui.tableWidgetMeasuring->item(i, 1) ||
				nullptr == m_ui.tableWidgetMeasuring->item(i, 2) ||
				nullptr == m_ui.tableWidgetMeasuring->item(i, 3))
			{
				continue;
			}

            if (m_ui.tableWidgetMeasuring->item(i, 0)->text() == "" && m_ui.tableWidgetMeasuring->item(i + 1 >= m_ui.tableWidgetMeasuring->columnCount() ? i : i + 1, 1)->text() != "")
            {
                m_ui.tableWidgetMeasuring->item(i, 0)->setText(tr("编号") + QString::number(i));
            }

            if (m_ui.tableWidgetMeasuring->item(i, j) == NULL || m_ui.tableWidgetMeasuring->item(i, j)->text() == "")
            {
                break;
            }

            if (0 == j)
            {
                continue;
            }
            else if (1 == j)
            {
                v.x() = m_ui.tableWidgetMeasuring->item(i, j)->text().toDouble();
            }
            else if (2 == j)
            {
                v.y() = m_ui.tableWidgetMeasuring->item(i, j)->text().toDouble();
            }
            else if (3 == j)
            {
                v.z() = m_ui.tableWidgetMeasuring->item(i, j)->text().toDouble();
            }

            bSet = true;
        }

        if (bSet)
        {
            pointsData.push_back(v);
        }
    }

    m_measuringEdit = false;

    //m_ui.widget_device->drawMeasurePointLine(pointsData);
	importDatasFromGlobal();
	emit setAutoModeling(true);
}

void DialogObservationDeviceSettings::onFaceWidthEditFinished()
{
    double value = m_ui.lineEditFaceWidth->text().toDouble();

    GlobalParam::instance()->getObservationSystemSetting().faceWidth = static_cast<float>(value);
}

void DialogObservationDeviceSettings::onFaceHeightEditFinished()
{
    double value = m_ui.lineEditFaceHeight->text().toDouble();

    GlobalParam::instance()->getObservationSystemSetting().faceHeight = static_cast<float>(value);
}

void DialogObservationDeviceSettings::onFaceXEditFinished()
{
    double value = m_ui.lineEditFaceX->text().toDouble();

    osg::Vec3d &v = GlobalParam::instance()->getObservationSystemSetting().facePosition;

    v = osg::Vec3d(value, v.y(), v.z());
}

void DialogObservationDeviceSettings::onFaceYEditFinished()
{
    double value = m_ui.lineEditFaceY->text().toDouble();

    osg::Vec3d &v = GlobalParam::instance()->getObservationSystemSetting().facePosition;

    v = osg::Vec3d(v.x(), value, v.z());
}

void DialogObservationDeviceSettings::onFaceZEditFinished()
{
    double value = m_ui.lineEditFaceZ->text().toDouble();

    osg::Vec3d &v = GlobalParam::instance()->getObservationSystemSetting().facePosition;

    v = osg::Vec3d(v.x(), v.y(), value);
}

void DialogObservationDeviceSettings::onComboBoxChanged(int pos)
{
    GlobalParam::instance()->getObservationSystemSetting().deviceType = (GlobalParam::DeviceType)pos;
}

void DialogObservationDeviceSettings::onExcavationDirChanged(int pos)
{
	GlobalParam::instance()->getObservationSystemSetting().excavationDir = GlobalParam::ExcavationDir(pos);
}

/********************************************************************/
//窗口关闭事件
/********************************************************************/
void DialogObservationDeviceSettings::closeEvent(QCloseEvent *e)
{
    saveDialogData();

    QDialog::closeEvent(e);
}

void DialogObservationDeviceSettings::setValidator()
{
// 	m_ui.lineEdit_grid_size_x->setValidator(new QIntValidator(0, 999999, this));
// 	m_ui.lineEdit_grid_size_y->setValidator(new QIntValidator(0, 999999, this));
// 	m_ui.lineEdit_inversion_area_x->setValidator(new QIntValidator(0, 999999, this));
// 	m_ui.lineEdit_inversion_area_y->setValidator(new QIntValidator(0, 999999, this));

	QRegExp double_rx("1000|([0-9]{0,3}[\.][0-9]{1,4})");

	m_ui.lineEditFaceWidth->setValidator(new QRegExpValidator(double_rx, this));
	m_ui.lineEditFaceHeight->setValidator(new QRegExpValidator(double_rx, this));
	m_ui.lineEditFaceX->setValidator(new QRegExpValidator(double_rx, this));
	m_ui.lineEditFaceY->setValidator(new QRegExpValidator(double_rx, this));
	m_ui.lineEditFaceZ->setValidator(new QRegExpValidator(double_rx, this));
}

/********************************************************************/
//保存画面数据
/********************************************************************/
void DialogObservationDeviceSettings::saveDialogData()
{
    // 	GlobalParam::instance()->getObservationSystemSetting().saveObservationDeviceSettingData(m_ui.lineEditFaceWidth->text().toFloat(), m_ui.lineEditFaceHeight->text().toFloat(),
    // 		osg::Vec3d(m_ui.lineEditFaceX->text().toDouble(), m_ui.lineEditFaceY->text().toDouble(), m_ui.lineEditFaceZ->text().toDouble()),
    // 		GlobalParam::DeviceType::FocusingSounding);
}

/********************************************************************/
//观测装置参数改变的时候
/********************************************************************/
void DialogObservationDeviceSettings::textChanged()
{
	if (m_ui.lineEditFaceWidth->text() == "" || m_ui.lineEditFaceHeight->text() == "" || 
		m_ui.lineEditFaceX->text() == "" || m_ui.lineEditFaceY->text() == "" || m_ui.lineEditFaceZ->text() == "")
	{
		QMessageBox::critical(this, "error", QString::fromUtf8("不允许空值存在！"));
		return;
	}

	vector<osg::Vec3d> &pointsData = GlobalParam::instance()->getObservationSystemSetting().powerSupplyPointData;
	pointsData.clear();

	osg::Vec3d vLeftUpper;
	osg::Vec3d vRightUpper;
	osg::Vec3d vRightLower;
	osg::Vec3d vLeftLower;

	vLeftUpper.x() = m_ui.lineEditFaceX->text().toDouble() - m_ui.lineEditFaceWidth->text().toDouble()/2;
	vLeftUpper.y() = m_ui.lineEditFaceY->text().toDouble() + m_ui.lineEditFaceHeight->text().toDouble() / 2;
	vLeftUpper.z() = m_ui.lineEditFaceZ->text().toDouble();

	vRightUpper.x() = m_ui.lineEditFaceX->text().toDouble() + m_ui.lineEditFaceWidth->text().toDouble() / 2;
	vRightUpper.y() = m_ui.lineEditFaceY->text().toDouble() + m_ui.lineEditFaceHeight->text().toDouble() / 2;
	vRightUpper.z() = m_ui.lineEditFaceZ->text().toDouble();

	vRightLower.x() = m_ui.lineEditFaceX->text().toDouble() + m_ui.lineEditFaceWidth->text().toDouble() / 2;
	vRightLower.y() = m_ui.lineEditFaceY->text().toDouble() - m_ui.lineEditFaceHeight->text().toDouble() / 2;
	vRightLower.z() = m_ui.lineEditFaceZ->text().toDouble();

	vLeftLower.x() = m_ui.lineEditFaceX->text().toDouble() - m_ui.lineEditFaceWidth->text().toDouble() / 2;
	vLeftLower.y() = m_ui.lineEditFaceY->text().toDouble() - m_ui.lineEditFaceHeight->text().toDouble() / 2;
	vLeftLower.z() = m_ui.lineEditFaceZ->text().toDouble();

	pointsData.push_back(vLeftUpper);
	pointsData.push_back(vRightUpper);
	pointsData.push_back(vRightLower);
	pointsData.push_back(vLeftLower);

	importDatasFromGlobal();
}

void DialogObservationDeviceSettings::resizeEvent(QResizeEvent *e)
{
	if (m_ui.widget_device->width() > 300)
	{
		m_ui.label_text->setGeometry(m_ui.widget_device->width() - 120, 2, m_ui.label_text->width(), m_ui.label_text->height());
	}
	QDialog::resizeEvent(e);
}

void DialogObservationDeviceSettings::saveMileageNumber()
{
	GlobalParam::instance()->getObservationSystemSetting().mileageNumber = m_ui.lineEditMileageNum->text();
	QString splitZK = m_ui.lineEditMileageNum->text();
	QStringList string_list = splitZK.split("+");

	if (string_list.size() >= 2)
	{
		splitZK = string_list[0];
		QStringList string_list_k = splitZK.split("k");
		if (string_list_k.size() >= 2)
		{
			GlobalParam::instance()->getObservationSystemSetting().mileage_left = string_list_k[0].toInt();
		}
		else
		{
			GlobalParam::instance()->getObservationSystemSetting().mileage_left = 0;
		}

		splitZK = string_list[1];
		QStringList string_list_m = splitZK.split("m");
		if (string_list_m.size() >= 2)
		{
			GlobalParam::instance()->getObservationSystemSetting().mileage_right = string_list_m[0].toInt();
		}
		else
		{
			GlobalParam::instance()->getObservationSystemSetting().mileage_right = 0;
		}
	}
	else
	{
		GlobalParam::instance()->getObservationSystemSetting().mileage_left = 0;
		GlobalParam::instance()->getObservationSystemSetting().mileage_right = 0;
	}
}