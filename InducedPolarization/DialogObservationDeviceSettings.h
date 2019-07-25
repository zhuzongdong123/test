/*
* 你好
*/

#ifndef DIALOGOBSERVATIONSETTINGS_H
#define DIALOGOBSERVATIONSETTINGS_H

#include "GeneratedFiles/ui_DialogObservationDeviceSettings.h"
#include "QDialog"

class DialogObservationDeviceSettings : public QDialog
{
    Q_OBJECT
  public:
    enum UpdateType
    {
        UD_ALL,
        UD_SUPPLY,
        UD_MEASURING,
    };

    DialogObservationDeviceSettings(QWidget *parent = nullptr);
    ~DialogObservationDeviceSettings();
    void closeEvent(QCloseEvent *e);
    bool importDatasFromGlobal();
	void resizeEvent(QResizeEvent *e);

	int getDNum() { return m_drawFaceDistance.size(); }
	int getMeasurePointNum() { return m_measurePointNum; }

  public slots:

    void onMileageNumberEditFinished();
    void onTunnelParamUpdate();
    void onSupplyEditClick();
    void onMeasuringEditClick();
    void onSupplyUpdateClick();
    void onMesasuringUpdateClick();
    void onFaceWidthEditFinished();
    void onFaceHeightEditFinished();
    void onFaceXEditFinished();
    void onFaceYEditFinished();
    void onFaceZEditFinished();
    void onComboBoxChanged(int pos);
	void onExcavationDirChanged(int pos);
	void textChanged();
signals:
	void setAutoModeling(bool isAutoModeling);

  protected:
    bool initTables();

    bool initTable(MyTableWidget *table, unsigned int width, QString indexName);
    bool initNewTable();

    Ui::DialogObservationDevice m_ui;

    bool m_supplyEdit;
    bool m_measuringEdit;


	//virtual void showEvent(QShowEvent *) override;

private:
	void setValidator();
    void saveDialogData();
	void saveMileageNumber();
	vector<double> m_drawFaceDistance;
	int m_measurePointNum;

    unsigned int _defaultHeight;
};

#endif