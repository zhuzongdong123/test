#include "DialogInversionParaSetting.h"
#include "GlobalClass/GlobalParam.h"

DialogInversionParaSetting::DialogInversionParaSetting(QWidget *parent /*= nullptr*/) : QDialog(parent)
{
    m_ui.setupUi(this);

    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowCloseButtonHint;
    setWindowFlags(flags);

    QIntValidator *validator = new QIntValidator(this);
    validator->setRange(0, 10000);

    m_ui.lineEdit_PCGITMAX->setValidator(validator);

	setValidator();

    saveDialogData();
}

DialogInversionParaSetting::~DialogInversionParaSetting()
{

}

/********************************************************************/
//窗口关闭事件
/********************************************************************/
void DialogInversionParaSetting::closeEvent(QCloseEvent *e)
{
    saveDialogData();

    QDialog::closeEvent(e);
}

void DialogInversionParaSetting::showEvent(QShowEvent *)
{
	GlobalParam::InversionParaSetting& setting = GlobalParam::instance()->getInversionParaSetting();

	m_ui.checkBox_compare->setChecked(setting.showLegend);
}

void DialogInversionParaSetting::setValidator()
{
	m_ui.lineEdit_INVMAX->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_BoundU->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_BoundL->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_PCGITMAX->setValidator(new QIntValidator(0, 999999, this));

	QRegExp double_rx("100|([0-9]{0,2}[\.][0-9]{1,8})");

	m_ui.lineEdit_EPS->setValidator(new QRegExpValidator(double_rx, this));
	m_ui.lineEdit_EPSRMS->setValidator(new QRegExpValidator(double_rx, this));
	m_ui.lineEdit_PCGEPS->setValidator(new QRegExpValidator(double_rx, this));
	m_ui.lineEdit_PCGRELERR->setValidator(new QRegExpValidator(double_rx, this));
}

/********************************************************************/
//保存画面数据
/********************************************************************/
void DialogInversionParaSetting::saveDialogData()
{
    GlobalParam::InversionMethodSelection selectionSwitch;
    GlobalParam::ComputingMethodOfSmoothnessMatrix computingMethod;
    GlobalParam::DataWeighting dataWeighting;

    //取得反演方法选择开关的值
    if (m_ui.comboBox_selectionSwitch->currentText() == QStringLiteral("GA"))
    {
        selectionSwitch = GlobalParam::InversionMethodSelection::GA;
    }
    else if (m_ui.comboBox_selectionSwitch->currentText() == QStringLiteral("最小二乘"))
    {
        selectionSwitch = GlobalParam::InversionMethodSelection::leastSquare;
    }
    else if (m_ui.comboBox_selectionSwitch->currentText() == QStringLiteral("联合"))
    {
        selectionSwitch = GlobalParam::InversionMethodSelection::united;
    }
    else if (m_ui.comboBox_selectionSwitch->currentText() == QStringLiteral("蚁群"))
    {
        selectionSwitch = GlobalParam::InversionMethodSelection::antColony;
    }

    //取得光滑度矩阵的计算方法的值
    if (m_ui.comboBox_computingMethod->currentText() == QStringLiteral("含距离因子"))
    {
        computingMethod = GlobalParam::ComputingMethodOfSmoothnessMatrix::distanceFactor;
    }
    else if (m_ui.comboBox_computingMethod->currentText() == QStringLiteral("不含距离因子"))
    {
        computingMethod = GlobalParam::ComputingMethodOfSmoothnessMatrix::noDistanceFactor;
    }

    //取得数据加权的值
    if (m_ui.comboBox_dataWeighting->currentText() == QStringLiteral("线性"))
    {
        dataWeighting = GlobalParam::DataWeighting::linear;
    }
    else if (m_ui.comboBox_dataWeighting->currentText() == QStringLiteral("指数"))
    {
        dataWeighting = GlobalParam::DataWeighting::index;
    }
    else if (m_ui.comboBox_dataWeighting->currentText() == QStringLiteral("二次"))
    {
        dataWeighting = GlobalParam::DataWeighting::secondary;
    }
    else if (m_ui.comboBox_dataWeighting->currentText() == QStringLiteral("无加权"))
    {
        dataWeighting = GlobalParam::DataWeighting::noWeighting;
    }

    double lamda  = 0.0;
    bool useLamda = false;

    if (m_ui.lineEdit_Lamda->isEnabled())
    {
        useLamda = true;
        lamda    = m_ui.lineEdit_Lamda->text().toDouble();
    }

    ////数据保存
    GlobalParam::instance()->getInversionParaSetting().saveSettingValue(selectionSwitch, computingMethod, dataWeighting, m_ui.lineEdit_INVMAX->text().toInt(),
                                                                        m_ui.lineEdit_EPS->text().toDouble(), m_ui.lineEdit_EPSRMS->text().toDouble(), m_ui.lineEdit_BoundU->text().toDouble(), m_ui.lineEdit_BoundL->text().toDouble(), m_ui.lineEdit_PCGITMAX->text().toInt(), m_ui.lineEdit_PCGRELERR->text().toDouble(),
                                                                        m_ui.lineEdit_PCGEPS->text().toDouble(), lamda, useLamda,m_ui.checkBox_compare->isChecked());
}

void DialogInversionParaSetting::onClickedNotUseLAMDA()
{
    m_ui.lineEdit_Lamda->setEnabled(false);
}
void DialogInversionParaSetting::onClickedUseLAMDA()
{
    m_ui.lineEdit_Lamda->setEnabled(true);
}