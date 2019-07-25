#pragma once

#include <QtWidgets/QDialog>
#include "GeneratedFiles/ui_DialogModelingPara.h"

class DialogModelingPara : public QDialog
{
	Q_OBJECT
public:
	/**
	* @brief ���캯��
	*
	* @param [in] parent �����ھ����Ĭ�Ͽ�
	*/
	DialogModelingPara(QWidget *parent = nullptr);
	void closeEvent(QCloseEvent *e);
	void showEvent(QShowEvent *e);

	bool getChanged() { return m_isChanged; }
	void saveDialogData();

private:
	Ui::DialogModelingPara m_ui; ///< UI�ļ�

private:

	void setValidator();

	float m_forecastLength;			
	float m_predictionCellSpacing;	
	float m_tunnelCavityRangeX;		
	float m_tunnelCavityRangeY;		
	float m_inversionAreaRangeX;	
	float m_inversionAreaRangeY;	
	bool m_isChanged;

};
