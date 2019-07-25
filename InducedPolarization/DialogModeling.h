#ifndef DIALOGMODELING_H
#define DIALOGMODELING_H

#include <QtWidgets/QDialog>
#include "GeneratedFiles/ui_DialogModeling.h"
#include "ModelingSubdivision.h"

class DialogModeling : public QDialog
{
    Q_OBJECT
  public:
    /**
	* @brief 构造函数
	*
	* @param [in] parent 父窗口句柄，默认空
	*/
    DialogModeling(QWidget *parent = nullptr);

	~DialogModeling();
	//开始建模
	void doModel();
	void clearModel();
	void updateParaData();
	void resizeEvent(QResizeEvent *e);
	void showEvent(QShowEvent *e);
	ModelingSubdivision* getModelSubdi() { return m_ui.widget; }

	const vector<double>& getXLVector() const { return m_XLVector; }
	const vector<double>& getYLVector() const { return m_YLVector; }
	const vector<double>& getZLVector() const { return m_ZLVector; }

	unsigned int getInvertBeginAreaX();
	unsigned int getInvertEndAreaX();

	unsigned int getInvertBeginAreaY();
	unsigned int getInvertEndAreaY();

	unsigned int getInvertBeginAreaZ();
	unsigned int getInvertEndAreaZ();

	void setAutoModeling(bool isAutoModeling) { m_isAutoModeling = isAutoModeling; }
	bool getAutoModeling() { return m_isAutoModeling; }
signals:
	void creatModelData(bool is_folder, bool is_level_2, QString item_name);

public slots:
	void editData();
	void updateData();
	void invertBeginZTextChanged(QString text);

private:
	void initTable();
	void importData(std::vector<double> vectorX, std::vector<double> vectorY, std::vector<double> vectorZ);//导入表格内容
	void importPara();//导入建模参数设置内容
private:
	void setValidator();

    Ui::DialogModeling m_ui; ///< UI文件

	vector<double> m_XLVector;
	vector<double> m_YLVector;
	vector<double> m_ZLVector;
	bool m_isAutoModeling;
};

#endif