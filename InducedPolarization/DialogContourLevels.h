#pragma once
#include "GeneratedFiles/ui_DialogContourLevels.h"

class DialogContourLevels : public QDialog
{
	Q_OBJECT
public:
	/**
	* @brief 构造函数
	*
	* @param [in] parent 父窗口句柄，默认空
	*/
	DialogContourLevels(QWidget *parent = nullptr);
	void accept();

	int getlevelCreationMode() { return m_levelCreationMode; }
	int	getRangeDistribution(){ return m_rangeDistribution; }
	float getMinLevel() { return m_minLevel; }
	float getMaxLevel() { return m_maxLevel; }
	float getNumberOfLevel() { return m_numberOfLevel; }
	float getDelta() { return m_delta; }
	void setValue(float minLevel, float maxLevel, float numberOfLevels, float delta);
	void setValue(float minLevel, float maxLevel);

public slots:
	void onClickExactLevels();
	void onClickApproximateLevels();
	void onClickRangeDistribution0();
	void onClickRangeDistribution1();
	void onClickRangeDistribution2();
	void resetRange();
	void onClickOK();

signals:

private:

private:
	Ui::DialogContourLevels m_ui; ///< UI文件

	int m_levelCreationMode;
	int m_rangeDistribution;
	float m_minLevel;
	float m_maxLevel;
	float m_defaultMinLevel;
	float m_defaultMaxLevel;
	float m_numberOfLevel;
	float m_delta;
};