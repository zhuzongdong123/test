/*****************************************************************************
*  创建工程窗口类                                                            *
*  Copyright (C) 山东大学岩土与结构工程研究中心                              *
*                                                                            *
*  这个文件是UI模块的一部分                                                  *
*                                                                            *
*                                                                            *
*  @file     DialogCreateProject.h                                           *
*  @brief    是DialogCreateProject类的头文件                                 *
*                                                                            *
*  @author   郭浩                                                            *
*  @email    korman@qq.com                                                   *
*  @version  1.0.0                                                           *
*  @date     2019/04/16                                                      *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*----------------------------------------------------------------------------*
*  2019/04/16 | 1.0.0   | 郭浩  | 创建文件                                   *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#ifndef DIALOGCREATEPROJECT_H
#define DIALOGCREATEPROJECT_H
#pragma execution_character_set("utf-8")
#include "GeneratedFiles/ui_DialogCreateProject.h"
#include "QDialog"

/*
* @brief 创建工程对话框类
*/
class DialogCreateProject : public QDialog
{
    Q_OBJECT

  public:
    /**
	* @brief 构造函数
	*
	* @param [in] parent 父窗口句柄，默认空
	*/
    DialogCreateProject(QWidget *parent = nullptr);

    /**
	* @brief 析构函数
	*/
    ~DialogCreateProject();

    /**
	* @brief 获取工程名
	*
	* @return const QString 获取的结果
	*/
    const QString getProjectName() { return m_projcetName; }

    /**
	* @brief 获取工程路径
	*
	* @return const QString 获取的结果
	*/
    const QString getProjectPath() { return m_currentProjPath; }

  protected:
    /**
	* @brief 创建文件
	*
	* @param [in] filePath 文件路径
	* @param [in] fileName 文件名
	*/
    void createFile(QString filePath, QString fileName);

  private slots:

    void onActionOpenFileDialog();

    /**
	* @brief 重载父类的accept接口，关闭创建工程对话框之前要进行目录创建等工作
	*/
    virtual void accept();

  private:

    Ui_DialogCreateProject m_ui; ///< UI文件
    QString m_currentProjPath;   ///< 当前工程路径
    QString m_projcetName;       ///< 工程名
};

#endif