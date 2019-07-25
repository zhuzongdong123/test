#include "ProjectManager.h"
#include <fstream>
#include <sstream>
#include "QtCore\QTextCodec"
#include "QFile"
#include "QFileInfo"
#include "QDir"
#include "GlobalClass\GlobalParam.h"
#include "GlobalClass\DataManager.h"
#include "..\3ddisplay\Common.h"
#include "qDebug.h"

shared_ptr<ProjectManager> ProjectManager::_instance = 0;

void Deleter(DataManager::DataInfo* obj)
{
	for (unsigned int i = 0;i < obj->row;i++)
	{
		SAFE_DELETE_ARRAY(obj->data[i]);
	}

	SAFE_DELETE_ARRAY(obj->data);
}

ProjectManager::ProjectManager()
{
    _projectInfo     = nullptr;
    _isLoadedProject = false;
    _projExt         = ".proj";
    _textCode        = QTextCodec::codecForName("GB2312");
}

ProjectManager::~ProjectManager()
{
}

shared_ptr<ProjectManager> ProjectManager::instance()
{
    if (0 == _instance)
    {
        _instance = shared_ptr<ProjectManager>(new ProjectManager);
    }

    return _instance;
}

bool ProjectManager::initProject(const QString projPath, const QString projName)
{
    cleanAllData();

    _proName = "";
	_fileName = "";
    if (nullptr == _projectInfo)
    {
        _projectInfo = shared_ptr<pb::ProjectInfo>(new pb::ProjectInfo);
    }

    _projPath = projPath;
    _projectInfo->mutable_projectbaseinfo()->set_projectname(projName.toStdString());
    _isLoadedProject = true;

	_proName = projName;
	_fileName = projName + _projExt;

    saveProject();
    return true;
}

void ProjectManager::resetProject()
{
    _projectInfo.reset();

    _projectInfo = shared_ptr<pb::ProjectInfo>(new pb::ProjectInfo);
	_projectInfo->mutable_projectbaseinfo()->set_projectname(_proName.toStdString());
}

bool ProjectManager::saveProject()
{
	resetProject();

    if (!_isLoadedProject)
    {
        return false;
    }

    updateAllDataFromGlobal();

    _projectInfo->mutable_projectbaseinfo()->set_projectversion("0.0.1");

    string dataString = "";

    if (!_projectInfo->SerializeToString(&dataString))
    {
        return false;
    }

    shared_ptr<QByteArray> dataBytes = shared_ptr<QByteArray>(new QByteArray(dataString.c_str(), dataString.size()));

	if (_fileName == "")	return false;

    //QFile file(_projPath + "/" + _projectInfo->mutable_projectbaseinfo()->projectname().c_str() + _projExt);
	QFile file(_projPath + "/" + _fileName);
	if (file.open(QIODevice::WriteOnly))
	{
		file.write(*(dataBytes.get()));
	}
	else
	{
		qDebug() << QObject::tr("open file failed") << endl;
	}
    file.close();

	_projectInfo = nullptr;

    return true;
}

bool ProjectManager::loadProject(const QString &filename)
{
	resetProject();

    _proName = "";
	_fileName = "";
    if (0 >= filename.length())
    {
        return false;
    }

    resetProject();

    QFileInfo projFileInfo(filename);

    if (!projFileInfo.exists())
    {
        return false;
    }

    QString projPath = projFileInfo.absolutePath();

    _projPath        = projPath;
    _isLoadedProject = true;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        return false;
    }
    QByteArray a = file.readAll();
    file.close();

    if (!_projectInfo->ParseFromString(a.toStdString()))
    {
        return false;
    }

    QString name = _projectInfo->projectbaseinfo().projectname().c_str();
    QString ver  = _projectInfo->projectbaseinfo().projectversion().c_str();

    updateAllDataToGlobal();

    _proName = name;
	_fileName = projFileInfo.fileName();

    //cleanData();

    return true;
}

void ProjectManager::updateAllDataFromGlobal()
{
    cleanProjData();

    updateObInfoFromGlobal();
    updateDataPreprocessInfoFromDataMgr();
    updateModelingParamFromGlobal();
    updateInversionProcessDataFromDataMgr();
    updateHalfLifeCurveDataFromDataMgr();
    updateSimForwardParamsFromGlobal();
}

void ProjectManager::updateAllDataToGlobal()
{
    updateObInfoToGlobal();
    updateDataPreprocessInfoToDataMgr();
    updateModelingParamToGlobal();
    updateInversionProcessDataToDataMgr();
    updateHalfLifeCurveDataToDataMgr();
    updateSimForwardParamsToGlobal();

    cleanProjData();
}

void ProjectManager::updateObInfoToGlobal()
{
    pb::ObservationSystemSetting *setting = _projectInfo->mutable_obsystemsetting();

    GlobalParam::ObservationSystemSetting &param = GlobalParam::instance()->getObservationSystemSetting();

    param.faceWidth  = setting->facewidth();
    param.faceHeight = setting->faceheight();
    param.deviceType = GlobalParam::DeviceType(setting->devicetype());

    param.facePosition.x() = setting->faceposition().x();
    param.facePosition.y() = setting->faceposition().y();
    param.facePosition.z() = setting->faceposition().z();

    param.mileageNumber = QString::fromUtf8(setting->mileagenumber().c_str());
    param.excavationDir = GlobalParam::ExcavationDir((int)setting->excavationdir());

    param.elecCircleDisVec.clear();

    for (auto v : *(setting->mutable_eleccircledisvec()))
    {
        param.elecCircleDisVec.push_back(v);
    }

    param.measuringPointData.clear();

    for (auto v : *(setting->mutable_measuringpointdata()))
    {
        osg::Vec3d v3(v.x(), v.y(), v.z());

        param.measuringPointData.push_back(v3);
    }

    param.powerSupplyPointData.clear();

    for (auto v : *(setting->mutable_powersupplypointdata()))
    {
        osg::Vec3d v3(v.x(), v.y(), v.z());

        param.powerSupplyPointData.push_back(v3);
    }
}

void ProjectManager::updateObInfoFromGlobal()
{
    //QTextCodec *code = QTextCodec::codecForName("GB2312");

    pb::ObservationSystemSetting *setting = _projectInfo->mutable_obsystemsetting();

    GlobalParam::ObservationSystemSetting &param = GlobalParam::instance()->getObservationSystemSetting();

    setting->set_facewidth(param.faceWidth);
    setting->set_faceheight(param.faceHeight);
    setting->set_devicetype(pb::DeviceType(param.deviceType));

    pb::Vec3d *v3d = setting->mutable_faceposition();
    v3d->set_x(param.facePosition.x());
    v3d->set_y(param.facePosition.y());
    v3d->set_z(param.facePosition.z());

    //std::string convertMsg = code->fromUnicode(param.mileageNumber).data();

    setting->set_excavationdir(pb::ExcavationDir((int)param.excavationDir));
    setting->set_mileagenumber(param.mileageNumber.toStdString());

    for (auto x : param.elecCircleDisVec)
    {
        setting->add_eleccircledisvec(x);
    }

    for (auto x : param.measuringPointData)
    {
        pb::Vec3d *v = setting->add_measuringpointdata();
        v->set_x(x.x());
        v->set_y(x.y());
        v->set_z(x.z());
    }

    for (auto x : param.powerSupplyPointData)
    {
        pb::Vec3d *v = setting->add_powersupplypointdata();
        v->set_x(x.x());
        v->set_y(x.y());
        v->set_z(x.z());
    }
}

void ProjectManager::updateDataPreprocessInfoFromDataMgr()
{
    pb::DataPreprocessInfo *preInfo = _projectInfo->mutable_datapreprocess();

    DataManager::DataList &badPoints = DataManager::instance()->getDataListRef();
    vector<double> &adjustDataVec    = DataManager::instance()->getAdjustmentDataVecRef();
    vector<double> &obDataVec        = DataManager::instance()->getObserveDataListRef();

    pb::Data1d *bad = preInfo->mutable_badpoints();

    unsigned int rows = 0;

    for (auto v : badPoints)
    {
        for (unsigned int i = 0; i < v->row; i++)
        {
            rows++;

            for (unsigned j = 0; j < v->col; j++)
            {
                bad->add_data(v->data[i][j]);
            }
        }
    }

    bad->set_rows(rows);

    for (auto v : adjustDataVec)
    {
        preInfo->add_adjustmentdatavec(v);
    }

    for (auto v : obDataVec)
    {
        preInfo->add_observedatalist(v);
    }
}

void ProjectManager::updateDataPreprocessInfoToDataMgr()
{
    pb::DataPreprocessInfo *preInfo = _projectInfo->mutable_datapreprocess();

    DataManager::DataList &badPoints = DataManager::instance()->getDataListRef();
    vector<double> &adjustDataVec    = DataManager::instance()->getAdjustmentDataVecRef();
    vector<double> &obDataVec        = DataManager::instance()->getObserveDataListRef();

    badPoints.clear();
    adjustDataVec.clear();
    obDataVec.clear();

    pb::Data1d *bad = preInfo->mutable_badpoints();

    unsigned int rows = bad->rows();
    unsigned int cols = 0;

    if (0 < bad->data().size())
    {
        cols = bad->data().size() / rows;
    }

    shared_ptr<DataManager::DataInfo> dataInfo = shared_ptr<DataManager::DataInfo>(new DataManager::DataInfo, Deleter);
    memset(dataInfo.get(), 0, sizeof(DataManager::DataInfo));

    dataInfo->data = new double *[rows];
    memset(dataInfo->data, 0, sizeof(double *) * (rows));

    for (unsigned int i = 0; i < rows; i++)
    {
        dataInfo->data[i] = new double[4];
        memset(dataInfo->data[i], 0, sizeof(double) * 4);
    }

    dataInfo->col = cols;
    dataInfo->row = rows;

    for (unsigned int i = 0; i < rows; i++)
    {
        for (unsigned int j = 0; j < cols; j++)
        {
            double v = bad->data(i * cols + j);

            dataInfo->data[i][j] = v;
        }
    }

    badPoints.push_back(dataInfo);

    for (auto v : preInfo->adjustmentdatavec())
    {
        adjustDataVec.push_back(v);
    }

    for (auto v : preInfo->observedatalist())
    {
        obDataVec.push_back(v);
    }

    size_t t = DataManager::instance()->getDataList().size();
}

void ProjectManager::updateModelingParamFromGlobal()
{
    GlobalParam::Modeling &model = GlobalParam::instance()->getModeling();

    pb::ModelingParam *modelingParam = _projectInfo->mutable_modelingparam();

    modelingParam->set_forecastlength(model.forecastLength);
    modelingParam->set_predictioncellspacing(model.predictionCellSpacing);
    modelingParam->set_tunnelcavityrangex(model.tunnelCavityRangeX);
    modelingParam->set_tunnelcavityrangey(model.tunnelCavityRangeY);
    modelingParam->set_inversionarearangex(model.inversionAreaRangeX);
    modelingParam->set_inversionarearangey(model.inversionAreaRangeY);
}

void ProjectManager::updateModelingParamToGlobal()
{
    GlobalParam::Modeling &model = GlobalParam::instance()->getModeling();

    pb::ModelingParam *modelingParam = _projectInfo->mutable_modelingparam();

    model.forecastLength        = modelingParam->forecastlength();
    model.predictionCellSpacing = modelingParam->predictioncellspacing();
    model.tunnelCavityRangeX    = modelingParam->tunnelcavityrangex();
    model.tunnelCavityRangeY    = modelingParam->tunnelcavityrangey();
    model.inversionAreaRangeX   = modelingParam->inversionarearangex();
    model.inversionAreaRangeY   = modelingParam->inversionarearangey();
}

void ProjectManager::updateInversionProcessDataFromDataMgr()
{
    pb::Data3d *data3d = _projectInfo->mutable_inversionprocessresult();
    data3d->set_x(DataManager::instance()->getInversionProcessDataXLen());
    data3d->set_y(DataManager::instance()->getInversionProcessDataYLen());
    data3d->set_z(DataManager::instance()->getInversionProcessDataZLen());

    double ***resultData = DataManager::instance()->getInversionProcessData();

    if (nullptr != resultData)
    {
        for (unsigned int z = 0; z < DataManager::instance()->getInversionProcessDataZLen(); z++)
        {
            for (unsigned int y = 0; y < DataManager::instance()->getInversionProcessDataYLen(); y++)
            {
                for (unsigned int x = 0; x < DataManager::instance()->getInversionProcessDataXLen(); x++)
                {
                    data3d->add_data(resultData[z][y][x]);
                }
            }
        }
    }
}

void ProjectManager::updateInversionProcessDataToDataMgr()
{
    pb::Data3d *data3d = _projectInfo->mutable_inversionprocessresult();

    shared_ptr<double> data = DataManager::instance()->makeData<double>(data3d->data().size());

    for (unsigned int i = 0; i < data3d->data().size(); i++)
    {
        data.get()[i] = data3d->data()[i];
    }

    DataManager::instance()->setInversionData(data, data3d->x(), data3d->y(), data3d->z());
}

void ProjectManager::updateHalfLifeCurveDataFromDataMgr()
{
    osg::ref_ptr<osg::Vec2dArray> list = DataManager::instance()->getHalfLifeCurveDataList();

    for (auto x : *(list.get()))
    {
        pb::Vec2d *v = _projectInfo->add_halflifecurvedatalist();
        v->set_x(x.x());
        v->set_y(x.y());
    }
}

void ProjectManager::updateHalfLifeCurveDataToDataMgr()
{
    osg::ref_ptr<osg::Vec2dArray> list = DataManager::instance()->getHalfLifeCurveDataList();
    list->clear();

    for (auto v : _projectInfo->halflifecurvedatalist())
    {
        list->push_back(osg::Vec2d(v.x(), v.y()));
    }
}

void ProjectManager::updateSimForwardParamsFromGlobal()
{
    pb::ForwardModelingParaSetting *sim              = _projectInfo->mutable_simforwardparams();
    GlobalParam::ForwardModelingParaSetting &setting = GlobalParam::instance()->getForwardModelingParaSetting();

    sim->set_currentinumx(setting.currentINumX);
    sim->set_currentinumy(setting.currentINumY);
    sim->set_currentinumz(setting.currentINumZ);
    sim->set_ii(setting.II);
    sim->set_cii(setting.CII);
    sim->set_sgm0value(setting.sgM0Value);
    sim->set_inverx1(setting.inverX1);
    sim->set_inverx2(setting.inverX2);
    sim->set_invery1(setting.inverY1);
    sim->set_invery2(setting.inverY2);
    sim->set_inverz1(setting.inverZ1);
    sim->set_inverz2(setting.inverZ2);
    sim->set_actual_begin_x(setting.actual_begin_x);
    sim->set_actual_begin_y(setting.actual_begin_y);
    sim->set_actual_begin_z(setting.actual_begin_z);
    sim->set_actual_end_x(setting.actual_end_x);
    sim->set_actual_end_y(setting.actual_end_y);
    sim->set_actual_end_z(setting.actual_end_z);
    sim->set_potentialdeviceselectionswitch(pb::PotentialDeviceSelectionSwitch((int)setting.potentialDeviceSelectionSwitch));
}

void ProjectManager::updateSimForwardParamsToGlobal()
{
    if (!_projectInfo->has_simforwardparams())
    {
        return;
    }

    const pb::ForwardModelingParaSetting &sim        = _projectInfo->simforwardparams();
    GlobalParam::ForwardModelingParaSetting &setting = GlobalParam::instance()->getForwardModelingParaSetting();

    setting.potentialDeviceSelectionSwitch = GlobalParam::PotentialDeviceSelectionSwitch((int)sim.potentialdeviceselectionswitch());
    setting.currentINumX                   = sim.currentinumx();
    setting.currentINumY                   = sim.currentinumy();
    setting.currentINumZ                   = sim.currentinumz();
    setting.II                             = sim.ii();
    setting.CII                            = sim.cii();
    setting.sgM0Value                      = sim.sgm0value();
    setting.inverX1                        = sim.inverx1();
    setting.inverX2                        = sim.inverx2();
    setting.inverY1                        = sim.invery1();
    setting.inverY2                        = sim.invery2();
    setting.inverZ1                        = sim.inverz1();
    setting.inverZ2                        = sim.inverz2();
    setting.actual_begin_x                 = sim.actual_begin_x();
    setting.actual_begin_y                 = sim.actual_begin_y();
    setting.actual_begin_z                 = sim.actual_begin_z();
    setting.actual_end_x                   = sim.actual_end_x();
    setting.actual_end_y                   = sim.actual_end_y();
    setting.actual_end_z                   = sim.actual_end_z();
}

void ProjectManager::cleanAllData()
{
    DataManager::instance()->cleanData();
    GlobalParam::instance()->resetData();

    cleanProjData();
}

void ProjectManager::cleanProjData()
{
    _projectInfo->release_obsystemsetting();
    pb::ObservationSystemSetting *obInfo = new pb::ObservationSystemSetting;
    _projectInfo->set_allocated_obsystemsetting(obInfo);

    _projectInfo->release_datapreprocess();
    pb::DataPreprocessInfo *dpInfo = new pb::DataPreprocessInfo;
    _projectInfo->set_allocated_datapreprocess(dpInfo);

    _projectInfo->release_modelingparam();
    pb::ModelingParam *mpInfo = new pb::ModelingParam;
    _projectInfo->set_allocated_modelingparam(mpInfo);

    _projectInfo->clear_halflifecurvedatalist();

    _projectInfo->release_inversionprocessresult();

    _projectInfo->release_simforwardparams();
    pb::ForwardModelingParaSetting *fmInfo = new pb::ForwardModelingParaSetting;
    _projectInfo->set_allocated_simforwardparams(fmInfo);
}
