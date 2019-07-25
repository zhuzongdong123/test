#pragma once
#include "GeneratedFiles/ui_DialogMultiColoringDetails.h"
#include "DialogContourLevels.h"

class DialogMultiColoringDetails : public QDialog
{
	Q_OBJECT
public:
	/**
	* @brief 构造函数
	*
	* @param [in] parent 父窗口句柄，默认空
	*/
	DialogMultiColoringDetails(QWidget *parent = nullptr);
	~DialogMultiColoringDetails();

	DialogContourLevels* getContourLevels() { return m_contourLevels; }

public slots:
	void enterNewLevel();
	void colorGroupChanged(QString text) { emit setColorGroupName(text); }

signals:
	void setTextRange(float minLevel, float maxLevel, int numberOfLevel);
	void setColorGroupName(QString name);

private:

private:
	Ui::DialogMultiColoringDetails m_ui; ///< UI文件

	DialogContourLevels *m_contourLevels;

	//保存DialogContourLevels中的参数
	int m_levelCreationMode;
	int m_rangeDistribution;
	float m_minLevel;
	float m_maxLevel;
	float m_numberOfLevel;
	float m_delta;
};
