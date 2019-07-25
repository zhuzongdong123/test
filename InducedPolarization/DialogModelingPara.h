#pragma once

#include <QtWidgets/QDialog>
#include "GeneratedFiles/ui_DialogModelingPara.h"

class DialogModelingPara : public QDialog
{
	Q_OBJECT
public:
	/**
	* @brief 构造函数
	*
	* @param [in] parent 父窗口句柄，默认空
	*/
	DialogModelingPara(QWidget *parent = nullptr);
	void closeEvent(QCloseEvent *e);
	void showEvent(QShowEvent *e);

	bool getChanged() { return m_isChanged; }
	void saveDialogData();

private:
	Ui::DialogModelingPara m_ui; ///< UI文件

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
