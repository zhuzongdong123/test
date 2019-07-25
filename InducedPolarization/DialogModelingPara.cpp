#include "DialogModelingPara.h"
#include "GlobalClass/GlobalParam.h"

DialogModelingPara::DialogModelingPara(QWidget *parent):QDialog(parent)
{
	m_ui.setupUi(this);

	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);

	setValidator();

	saveDialogData();

	GlobalParam::instance()->getModeling().saveDefaultParamData(m_ui.lineEdit_grid_size_x->text().toFloat(), m_ui.lineEdit_grid_size_y->text().toFloat(),
		m_ui.lineEdit_tunnel_cavity_range_x->text().toFloat(), m_ui.lineEdit_tunnel_cavity_range_y->text().toFloat(),
		m_ui.lineEdit_inversion_area_x->text().toFloat(), m_ui.lineEdit_inversion_area_y->text().toFloat());

}

void DialogModelingPara::closeEvent(QCloseEvent *e)
{
	saveDialogData();
	QDialog::closeEvent(e);
}

void DialogModelingPara::showEvent(QShowEvent *e)
{
	const GlobalParam::Modeling& param = GlobalParam::instance()->getModeling();
	m_forecastLength = param.forecastLength;
	m_predictionCellSpacing = param.predictionCellSpacing;
	m_inversionAreaRangeX = param.inversionAreaRangeX;
	m_inversionAreaRangeY = param.inversionAreaRangeY;
	m_ui.lineEdit_grid_size_x->setText(QString::number(m_forecastLength));
	m_ui.lineEdit_grid_size_y->setText(QString::number(m_predictionCellSpacing));
	m_ui.lineEdit_inversion_area_x->setText(QString::number(m_inversionAreaRangeX));
	m_ui.lineEdit_inversion_area_y->setText(QString::number(m_inversionAreaRangeY));

	const GlobalParam::ObservationSystemSetting& observationSystemSetting = GlobalParam::instance()->getObservationSystemSetting();
	m_tunnelCavityRangeX = observationSystemSetting.faceWidth;
	m_tunnelCavityRangeY = observationSystemSetting.faceHeight;
	m_ui.lineEdit_tunnel_cavity_range_x->setText(QString::number(m_tunnelCavityRangeX));
	m_ui.lineEdit_tunnel_cavity_range_y->setText(QString::number(m_tunnelCavityRangeY));
	QDialog::showEvent(e);
}

void DialogModelingPara::saveDialogData() 
{
	m_isChanged = false;

	GlobalParam::instance()->getModeling().saveLeftParamData(m_ui.lineEdit_grid_size_x->text().toFloat(), m_ui.lineEdit_grid_size_y->text().toFloat(),
		m_ui.lineEdit_tunnel_cavity_range_x->text().toFloat(), m_ui.lineEdit_tunnel_cavity_range_y->text().toFloat(),
		m_ui.lineEdit_inversion_area_x->text().toFloat(), m_ui.lineEdit_inversion_area_y->text().toFloat());

	if (m_forecastLength != m_ui.lineEdit_grid_size_x->text().toFloat() || m_predictionCellSpacing != m_ui.lineEdit_grid_size_y->text().toFloat() ||
		m_tunnelCavityRangeX != m_ui.lineEdit_tunnel_cavity_range_x->text().toFloat() || m_tunnelCavityRangeY != m_ui.lineEdit_tunnel_cavity_range_y->text().toFloat() ||
		m_inversionAreaRangeX != m_ui.lineEdit_inversion_area_x->text().toFloat() || m_inversionAreaRangeY != m_ui.lineEdit_inversion_area_y->text().toFloat())
	{
		m_isChanged = true;
		m_forecastLength = m_ui.lineEdit_grid_size_x->text().toFloat();
		m_predictionCellSpacing = m_ui.lineEdit_grid_size_y->text().toFloat();
		m_tunnelCavityRangeX = m_ui.lineEdit_tunnel_cavity_range_x->text().toFloat();
		m_tunnelCavityRangeY = m_ui.lineEdit_tunnel_cavity_range_y->text().toFloat();
		m_inversionAreaRangeX = m_ui.lineEdit_inversion_area_x->text().toFloat();
		m_inversionAreaRangeY = m_ui.lineEdit_inversion_area_y->text().toFloat();
	}
}

void DialogModelingPara::setValidator()
{
	m_ui.lineEdit_grid_size_x->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_grid_size_y->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_inversion_area_x->setValidator(new QIntValidator(0, 999999, this));
	m_ui.lineEdit_inversion_area_y->setValidator(new QIntValidator(0, 999999, this));

	QRegExp double_rx("1000|([0-9]{0,3}[\.][0-9]{1,4})");

	m_ui.lineEdit_tunnel_cavity_range_x->setValidator(new QRegExpValidator(double_rx, this));
	m_ui.lineEdit_tunnel_cavity_range_y->setValidator(new QRegExpValidator(double_rx, this));
}
