#pragma once

#include <QtWidgets/QDialog>
#include "GeneratedFiles/ui_DialogSimuForward.h"
#include <vector>

using namespace std;

class DialogSimuForward : public QDialog
{
	Q_OBJECT
public:
	/**
	* @brief 构造函数
	*
	* @param [in] parent 父窗口句柄，默认空
	*/
	DialogSimuForward(QWidget *parent = nullptr);
	void showEvent(QShowEvent *e) ;
	void closeEvent(QCloseEvent *e);
	void saveData();
	void importData();
	void clearData();
	void setData();
	void setXL(const vector<double>& l) { m_xlVector = l; }
	void setYL(const vector<double>& l) { m_ylVector = l; }
	void setZL(const vector<double>& l) { m_zlVector = l; }

	void setInvertBeginX(unsigned int v) { m_invertBeginX = v; }
	void setInvertEndX(unsigned int v) { m_invertEndX = v;}

	void setInvertBeginY(unsigned int v) { m_invertBeginY = v; }
	void setInvertEndY(unsigned int v) { m_invertEndY = v; }

	void setInvertBeginZ(unsigned int v) { m_invertBeginZ = v; }
	void setInvertEndZ(unsigned int v) { m_invertEndZ = v; }

	

public slots:
	void onActualLocationXMaxChanged();
	void onActualLocationYMaxChanged();
	void onActualLocationZMaxChanged();
	void onActualLocationXMinChanged();
	void onActualLocationYMinChanged();
	void onActualLocationZMinChanged();

signals:
	void textChanged();

private:
	float getActualLocationValue(const vector<double>& l, unsigned int begin, unsigned int end);

	Ui::DialogSimuForward m_ui; ///< UI文件

	vector<double> m_xlVector;
	vector<double> m_ylVector;
	vector<double> m_zlVector;

	unsigned int m_invertBeginX;
	unsigned int m_invertEndX;

	unsigned int m_invertBeginY;
	unsigned int m_invertEndY;

	unsigned int m_invertBeginZ;
	unsigned int m_invertEndZ;

private:

	void setValidator();
};
