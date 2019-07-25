#include "DialogSetup.h"
#include "GlobalClass\GlobalParam.h"

DialogSetup::DialogSetup(QWidget *parent) : QDialog(parent)
{
    _ui.setupUi(this);
}

DialogSetup::~DialogSetup()
{
}

void DialogSetup::onOkButton()
{
    GlobalParam::CommonSetting &setting = GlobalParam::instance()->getCommonSetting();

    setting.debugLog          = _ui.checkBox_debugLog->isChecked();
    setting.DPCGRCLog         = _ui.checkBox_DPCGRCLog->isChecked();
    setting.NROLog            = _ui.checkBox_NroLog->isChecked();
    setting.writeFile         = _ui.checkBox_isWriteFile->isChecked();
    //setting.maxLineForShowLog = _ui.lineEdit_maxLine->text().toUInt();
}

void DialogSetup::showEvent(QShowEvent *)
{
    GlobalParam::CommonSetting &setting = GlobalParam::instance()->getCommonSetting();

    _ui.checkBox_isWriteFile->setChecked(setting.writeFile);
    //_ui.lineEdit_maxLine->setText(QString::number(setting.maxLineForShowLog));

    _ui.checkBox_debugLog->setChecked(setting.debugLog);
    _ui.checkBox_DPCGRCLog->setChecked(setting.DPCGRCLog);
    _ui.checkBox_NroLog->setChecked(setting.NROLog);
}

void DialogSetup::setValidator()
{
   // _ui.lineEdit_maxLine->setValidator(new QIntValidator(1, 9999, this));
}
