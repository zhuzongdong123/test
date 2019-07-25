#include "DialogForwardModelingParaSetting.h"
#include "GlobalClass/GlobalParam.h"

DialogForwardModelingParaSetting::DialogForwardModelingParaSetting(QWidget *parent /*= nullptr*/) : QDialog(parent)
{
    m_ui.setupUi(this);

    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowCloseButtonHint;
    setWindowFlags(flags);

    setValidator();

    saveDialogData();
}

DialogForwardModelingParaSetting::~DialogForwardModelingParaSetting()
{
}

//文字输入限制
void DialogForwardModelingParaSetting::setValidator()
{
	m_ui.lineEdit_sgM0Value->setValidator(new QIntValidator(0, 999999, this));
	QRegExp double_rx("1000|([0-9]{0,3}[\.][0-9]{1,2})");

	m_ui.lineEdit_CII->setValidator(new QRegExpValidator(double_rx, this));
	m_ui.lineEdit_II->setValidator(new QRegExpValidator(double_rx, this));
	m_ui.lineEdit_currentINumX->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_currentINumY->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_currentINumZ->setValidator(new QIntValidator(0, 999999, this));
}

/********************************************************************/
//窗口关闭事件
/********************************************************************/
void DialogForwardModelingParaSetting::closeEvent(QCloseEvent *e)
{
    saveDialogData();

    QDialog::closeEvent(e);
}

/********************************************************************/
//保存画面数据
/********************************************************************/
void DialogForwardModelingParaSetting::saveDialogData()
{
    GlobalParam::PotentialDeviceSelectionSwitch selectionSwitch;

    if (m_ui.comboBox_selectionSwitch->currentText() == "Schlumberger")
    {
        selectionSwitch = GlobalParam::PotentialDeviceSelectionSwitch::Schlumberger;
    }
    else if (m_ui.comboBox_selectionSwitch->currentText() == "AMNB")
    {
        selectionSwitch = GlobalParam::PotentialDeviceSelectionSwitch::AMNB;
    }

    //数据保存
    GlobalParam::instance()->getForwardModelingParaSetting().saveSettingValue(selectionSwitch, m_ui.lineEdit_sgM0Value->text().toDouble(), m_ui.lineEdit_CII->text().toDouble(), m_ui.lineEdit_II->text().toDouble(),
                                                                              m_ui.lineEdit_currentINumX->text().toInt(), m_ui.lineEdit_currentINumY->text().toInt(), m_ui.lineEdit_currentINumZ->text().toInt());
}
