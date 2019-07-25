/*****************************************************************************
*  主窗口类																     *
*  Copyright (C) 山东大学岩土与结构工程研究中心                              *
*                                                                            *
*  这个文件是UI模块的一部分                                                  *
*                                                                            *
*                                                                            *
*  @file     InducedPolarization.h                                           *
*  @brief    是InducedPolarization类的头文件                                 *
*																			 *
*****************************************************************************/

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_InducedPolarization.h"
#include "DialogDisplayImage.h"
#include "3ddisplay/ViewerWidget3d.h"

/*
* @brief 创建工程对话框类
*/
class InducedPolarization : public QMainWindow
{
    Q_OBJECT

  public:
    /**
	* @brief 构造函数
	*
	* @param [in] parent 父窗口句柄，默认空
	*/
    InducedPolarization(QWidget *parent = Q_NULLPTR);


	/**
	* @brief 析构函数
	**/
	~InducedPolarization();

public slots:
	void onActionShowMax(QString objectName, QString osgFilePath);
	void openOSGFile1();
	void openOSGFile2();

  private:
    Ui::InducedPolarization m_ui; ///< UI文件
	DialogDisplayImage* m_dialogLeftUpper;
	DialogDisplayImage* m_dialogLeftDown;
	DialogDisplayImage* m_dialogRightDown;
	DialogDisplayImage* m_dialogRightUpper;
	QAction *m_openFile;
	QAction *m_showMax;
	QString m_osgFilePath;
};
