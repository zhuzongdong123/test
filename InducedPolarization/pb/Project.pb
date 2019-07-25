/*****************************************************************************
*  激发极化工程文件                                                            *
*  Copyright (C) 郭浩                                                        *
*                                                                            *
*  这个文件是全部的激发极化工程文件           		                             *
*                                                                            *
*                                                                            *
*  @file     Project.pb	                                                     *
*  @brief    Project.pb是序列化二进制工程文件                                  *
*                                                                            *
*  @author   郭浩                                                            *
*  @email    korman@qq.com                                                   *
*  @version  v0.1.0                                                          *
*  @date     2019/05/28                                                      *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*----------------------------------------------------------------------------*
*  2019/05/28 | v0.1.0   | 郭浩  | 创建文件                                   *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

syntax = "proto3";

package pb;

/*
* @brief 装置类型
*/
enum DeviceType
{
	NType1 = 0;
	NType2 = 1;
	NType3 = 2;
	NType4 = 3;
	NType5 = 4;
	NType6 = 5;
	NType7 = 6;
	NType8 = 7;
	NType9 = 8;
	NType10 = 9;
	ESCAN = 10;
	FocusingSounding = 11;
}

//电位装置选择开关
enum PotentialDeviceSelectionSwitch
{
	Schlumberger = 0;
	AMNB = 1;
};

/*
* @brief 掘进方向
*/
enum ExcavationDir
{
	GreaterMileage = 0;
	LessMileage = 1;
}

/*
* @brief 3D结构体
*/
message Vec3d
{
	double x = 1;									///< X
	double y = 2;									///< Y
	double z = 3;									///< Z
}

/*
* @brief 2D结构体
*/
message Vec2d
{
	double x = 1;
	double y = 2;
}

/*
* @brief 1维压缩数组
*/
message Data1d
{
	repeated double data = 1;						///< 数据1维数组
	uint32 rows = 2;								///< 数据行数
}

/*
* @brief 1维压缩数组3d版
*/
message Data3d
{
	repeated double data = 1;						///< 数据1维数组
	uint32 x = 2;									///< x
	uint32 y = 3;									///< x
	uint32 z = 4;									///< x
}

/*
* @brief 观测系统数据
*/
message ObservationSystemSetting
{
    float faceWidth = 1;  							///< 掌子面宽度
	float faceHeight = 2;							///< 掌子面高度
	Vec3d facePosition = 3;							///< 掌子面坐标
    repeated Vec3d powerSupplyPointData = 4; 		///< 供电点位置数据
	repeated Vec3d measuringPointData = 5;			///< 测量点位置数据
	repeated float elecCircleDisVec = 6;			///< 每圈电极的偏移距，以掌子面为中心
	DeviceType deviceType = 7;						///< 设备类型
	string mileageNumber = 8;						///< 里程号
	ExcavationDir excavationDir = 9;				///< 掘进方向
}

/*
* @brief 正演参数对话框的结构体
*/
message ForwardModelingParaSetting
{
	PotentialDeviceSelectionSwitch potentialDeviceSelectionSwitch = 1;  ///< 电位装置选择开关
	uint32 currentINumX = 2;                                     		///< 供电电源在有限网格中X位置
	uint32 currentINumY = 3;                                     		///< 供电电源在有限网格中Y位置
	uint32 currentINumZ = 4;                                     		///< 供电电源在有限网格中Z位置
	double II = 5;														///< 电流大小
	double CII = 6;														///< 电流大小
	double sgM0Value = 7;												///< 供电电极附近的电阻率
	uint32 inverX1 = 8;
	uint32 inverX2 = 9;
	uint32 inverY1 = 10;
	uint32 inverY2 = 11;
	uint32 inverZ1 = 12;
	uint32 inverZ2 = 13;
	float actual_begin_x = 14;
	float actual_end_x = 15;
	float actual_begin_y = 16;
	float actual_end_y = 17;
	float actual_begin_z = 18;
	float actual_end_z = 19;
}

/*
* @brief 数据预处理信息
*/
message DataPreprocessInfo
{
	Data1d badPoints = 1;
	repeated double observeDataList = 2;
	repeated double adjustmentDataVec = 3;
}

/*
* @brief 建模参数
*/
message ModelingParam
{
	float forecastLength = 1; 						///< 预报区域长度
	float predictionCellSpacing = 2; 				///< 预报间隔
	float tunnelCavityRangeX = 3;  					///< 隧道空腔X区域
	float tunnelCavityRangeY = 4;  					///< 隧道空腔Y区域
	float inversionAreaRangeX = 5; 					///< 反演X区域设置
	float inversionAreaRangeY = 6; 					///< 反演Y区域设置
}

/*
* @brief 工程基本信息
*/
message ProjectBaseInfo
{
	string projectName = 1;							///< 工程名
	string projectVersion = 2;						///< 工程版本
}

/*
* @brief 工程文件总的信息
*/
message ProjectInfo
{
	ProjectBaseInfo projectBaseInfo = 1;			///< 工程基本信息
	ObservationSystemSetting obSystemSetting = 2;	///< 观测系统数据
	DataPreprocessInfo dataPreprocess = 3;			///< 数据预处理
	ModelingParam modelingParam = 4;				///< 建模参数
	Data3d inversionProcessResult = 5;				///< 反演结果
	repeated Vec2d halfLifeCurveDataList = 6;		///< 半衰时表
	ForwardModelingParaSetting simForwardParams = 7;///< 模拟正演对话框的参数
}