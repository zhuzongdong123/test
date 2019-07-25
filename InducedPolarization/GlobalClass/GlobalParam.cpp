#include "GlobalClass/GlobalParam.h"

GlobalParam *GlobalParam::instance()
{
    static GlobalParam globalParam;

    return &globalParam;
}

void GlobalParam::resetData()
{
    m_observationSystemSetting.clearData();
    m_modeling.clearData();
}

GlobalParam::GlobalParam()
{
    this->initialize();
}

GlobalParam::~GlobalParam()
{
}

bool GlobalParam::initialize()
{
    m_observationSystemSetting.deviceType = FocusingSounding;

    return true;
}
