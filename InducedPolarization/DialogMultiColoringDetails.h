#pragma once
#include "GeneratedFiles/ui_DialogMultiColoringDetails.h"
#include "DialogContourLevels.h"

class DialogMultiColoringDetails : public QDialog
{
	Q_OBJECT
public:
	/**
	* @brief ���캯��
	*
	* @param [in] parent �����ھ����Ĭ�Ͽ�
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
	Ui::DialogMultiColoringDetails m_ui; ///< UI�ļ�

	DialogContourLevels *m_contourLevels;

	//����DialogContourLevels�еĲ���
	int m_levelCreationMode;
	int m_rangeDistribution;
	float m_minLevel;
	float m_maxLevel;
	float m_numberOfLevel;
	float m_delta;
};
