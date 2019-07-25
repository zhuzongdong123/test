/*
*
*/

#ifndef DIALOGDATAPREPROCESSING_H
#define DIALOGDATAPREPROCESSING_H

#include "GeneratedFiles/ui_DialogDataPreprocessing.h"
#include "QDialog"

class DialogDataPreprocessing : public QDialog
{
    Q_OBJECT
  public:
    DialogDataPreprocessing(QWidget *parent = Q_NULLPTR);
    ~DialogDataPreprocessing();

    void updateForwardDataTable(std::vector<double> vecResult);
    void resetData();

	void setMeasurePointNum(unsigned int vMeasurePointNum, unsigned int circleNum) 
	{ 
		m_measurePointNum = vMeasurePointNum; 
		m_circleNum = circleNum;
	}
    std::vector<double> &getAdjustmentData() { return m_adjustmentDataVec; }
	std::vector<double> getMeasureDataVec() { return m_measureTableDataVec; }
	std::vector<double> getSimuPointDataVec() { return m_simuPointTableDataVec; }

  protected:
    bool initRemovePointsTable();
    bool initDataExtractionTable();
	void saveSupplyTableData();

    Ui::DialogDataPreprocessing m_ui;

  public slots:
    void onSupplyEditClick();
    void onSupplyUpdateClick();
	void onObserveDataLoaded();
	void updateAdjustData();
	void importAllData();

  signals:
    void updateDatData();

  private:
    void searchPoints(std::vector<double> resultSet, double &effectiveStartValue, double &effectiveEndValue);

    std::vector<double> getMeasuredDataTranslationValue(std::vector<double> vector1, std::vector<double> vector2);

    std::vector<double> m_measureTableDataVec;
    std::vector<double> m_simuPointTableDataVec;
    std::vector<double> m_adjustmentDataVec;
	double m_maxValue;
	unsigned int m_measurePointNum; //测量电极的个数
	unsigned int m_circleNum; //供电电极的圈数
    unsigned int m_defaultTableHeight;
};

#endif