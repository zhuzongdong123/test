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
//���ڹر��¼�
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
//���滭������
/********************************************************************/
void DialogInversionParaSetting::saveDialogData()
{
    GlobalParam::InversionMethodSelection selectionSwitch;
    GlobalParam::ComputingMethodOfSmoothnessMatrix computingMethod;
    GlobalParam::DataWeighting dataWeighting;

    //ȡ�÷��ݷ���ѡ�񿪹ص�ֵ
    if (m_ui.comboBox_selectionSwitch->currentText() == QStringLiteral("GA"))
    {
        selectionSwitch = GlobalParam::InversionMethodSelection::GA;
    }
    else if (m_ui.comboBox_selectionSwitch->currentText() == QStringLiteral("��С����"))
    {
        selectionSwitch = GlobalParam::InversionMethodSelection::leastSquare;
    }
    else if (m_ui.comboBox_selectionSwitch->currentText() == QStringLiteral("����"))
    {
        selectionSwitch = GlobalParam::InversionMethodSelection::united;
    }
    else if (m_ui.comboBox_selectionSwitch->currentText() == QStringLiteral("��Ⱥ"))
    {
        selectionSwitch = GlobalParam::InversionMethodSelection::antColony;
    }

    //ȡ�ù⻬�Ⱦ���ļ��㷽����ֵ
    if (m_ui.comboBox_computingMethod->currentText() == QStringLiteral("����������"))
    {
        computingMethod = GlobalParam::ComputingMethodOfSmoothnessMatrix::distanceFactor;
    }
    else if (m_ui.comboBox_computingMethod->currentText() == QStringLiteral("������������"))
    {
        computingMethod = GlobalParam::ComputingMethodOfSmoothnessMatrix::noDistanceFactor;
    }

    //ȡ�����ݼ�Ȩ��ֵ
    if (m_ui.comboBox_dataWeighting->currentText() == QStringLiteral("����"))
    {
        dataWeighting = GlobalParam::DataWeighting::linear;
    }
    else if (m_ui.comboBox_dataWeighting->currentText() == QStringLiteral("ָ��"))
    {
        dataWeighting = GlobalParam::DataWeighting::index;
    }
    else if (m_ui.comboBox_dataWeighting->currentText() == QStringLiteral("����"))
    {
        dataWeighting = GlobalParam::DataWeighting::secondary;
    }
    else if (m_ui.comboBox_dataWeighting->currentText() == QStringLiteral("�޼�Ȩ"))
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

    ////���ݱ���
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