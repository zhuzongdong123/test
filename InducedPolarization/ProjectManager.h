/*****************************************************************************
*  项目工程管理类		                                                     *
*  Copyright (C) 山东大学岩土与结构工程研究中心                              *
*                                                                            *
*  这个文件是项目工程管理类功能的一部分	     	                             *
*                                                                            *
*                                                                            *
*  @file     ProjectManager.h					                             *
*  @brief    是ProjectManager类的头文件						                 *
*                                                                            *
*  @author   郭浩                                                            *
*  @email    korman@qq.com                                                   *
*  @version  1.0.0                                                           *
*  @date     2019/01/11                                                      *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*----------------------------------------------------------------------------*
*  2019/01/11 | 1.0.0   | 郭浩  | 创建文件                                   *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#ifndef TEMPDATA_H
#define TEMPDATA_H

#include <string>
#include <vector>
#include <memory>
#include <QString>
#include "osg\Vec3d"
#include "pb\Project.pb.pb.h"
//#include "pb\Project.pb.pb.h"

using namespace std;

/**
* @brief 临时保存文件读写类
*/
class ProjectManager
{
  public:
    /**
	* @brief 二进制数据信息
	*/
    struct BinDataInfo
    {
        double *data;          ///< 二进制数据体
        unsigned __int64 size; ///< 二进制数据长度
    };

    enum TunnelType
    {
        Circular,
        HorseShoe
    };

    /**
	* @brief 析构函数
	*/
    ~ProjectManager();

    /**
	* @brief 实例获得
	*
	* @return 返回实例指针
	*/
    static shared_ptr<ProjectManager> instance();

    /**
	* @brief 初始化工程信息
	*
	* @param [in] projPath 工程路径
	* @param [in] projName 工程名
	*
	* @return bool 返回初始化的结果
	* @retval true 成功
	* @retval false 失败
	*/
    bool initProject(const QString projPath, const QString projName);

    /**
	* @brief 清空工程
	*/
    void resetProject();

    /**
	* @brief 保存工程
	*
	* @return bool 返回保存的结果
	* @retval true 保存成功
	* @retval false 保存失败
	*/
    bool saveProject();

    /**
	* @brief 读取json文件
	*
	* @param [in] filename 要读取的工程文件路径
	*
	* @return bool 读取的结果
	* @retval true 读取成功
	* @retval false 读取失败
	*/
    bool loadProject(const QString &filename);

    bool isLoadedProject() { return _isLoadedProject; }

    QString getProName() { return _proName; }

  protected:
    /**
	* @brief 构造函数
	*/
    ProjectManager();

    void updateAllDataFromGlobal();
    void updateAllDataToGlobal();

    void updateObInfoToGlobal();
    void updateObInfoFromGlobal();

    void updateDataPreprocessInfoFromDataMgr();
    void updateDataPreprocessInfoToDataMgr();

    void updateModelingParamFromGlobal();
    void updateModelingParamToGlobal();

    void updateInversionProcessDataFromDataMgr();
    void updateInversionProcessDataToDataMgr();

    void updateHalfLifeCurveDataFromDataMgr();
    void updateHalfLifeCurveDataToDataMgr();

    void updateSimForwardParamsFromGlobal();
    void updateSimForwardParamsToGlobal();

    void cleanAllData();
    void cleanProjData();

  private:
    static shared_ptr<ProjectManager> _instance;

    shared_ptr<pb::ProjectInfo> _projectInfo;

    QString _projPath;
    QString _projExt;
    QString _proName;
	QString _fileName;

    string _tmpString;

    QTextCodec *_textCode;

    bool _isLoadedProject;
};

#endif