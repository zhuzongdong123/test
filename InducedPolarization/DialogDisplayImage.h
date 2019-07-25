#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DialogDisplayImage.h"

/*
* @brief 创建工程对话框类
*/
class DialogDisplayImage : public QDialog
{
	Q_OBJECT

public:
	/**
	* @brief 构造函数
	*
	* @param [in] parent 父窗口句柄，默认空
	*/
	DialogDisplayImage(QWidget *parent = Q_NULLPTR);

	/**
	* @brief 析构函数
	**/
	~DialogDisplayImage() {}

	void setOsgFilePath(QString fileName);

private:
	Ui::DialogDisplayImage m_ui; ///< UI文件

};