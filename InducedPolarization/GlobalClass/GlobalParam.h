#pragma once
//单实例类，只存放对话框中设置的数据
#include <QtCore/QObject>
#include "osg/Vec3d"
#include <vector>
#include "../osg/Vec4d"
#include "QString"

using namespace std;

class GlobalParam : public QObject
{
    Q_OBJECT

  public:
    //装置类型
    enum DeviceType
    {
        NType1 = 0,
        NType2,
        NType3,
        NType4,
        NType5,
        NType6,
        NType7,
        NType8,
        NType9,
        NType10,
        ESCAN,
        FocusingSounding
    };

    /*
	* @brief 掘进方向
	*/
    enum ExcavationDir
    {
        GreaterMileage,
        LessMileage
    };

    //电位装置选择开关
    enum PotentialDeviceSelectionSwitch
    {
        Schlumberger = 0,
        AMNB
    };

    //反演方法选择开关
    enum InversionMethodSelection
    {
        GA = 0,      //GA
        leastSquare, //最小二乘
        united,      //联合
        antColony    //蚁群
    };

    //光滑度矩阵的计算方法
    enum ComputingMethodOfSmoothnessMatrix
    {
        distanceFactor   = 1, //含距离因子
        noDistanceFactor = 2  //不含距离因子
    };

    //数据加权
    enum DataWeighting
    {
        linear = 0, //线性
        index,      //指数
        secondary,  //二次
        noWeighting //无加权
    };

    static GlobalParam *instance();

    struct DataPreProcessInfo
    {
        vector<osg::Vec4d> badPointsList;
        vector<double> observeDataList;
    };

    /********************************************************************/
    //工具设置对话框结构体
    /********************************************************************/
    struct CommonSetting
    {
        bool DPCGRCLog = true;
        bool debugLog  = true;
        bool NROLog    = true;

        bool writeFile = true;

        unsigned int maxLineForShowLog = 5000;
    };

    /********************************************************************/
    //观测系统装置对话框的结构体
    /********************************************************************/
    struct ObservationSystemSetting
    {
        float faceWidth;         //掌子面宽度
        float faceHeight;        //掌子面高度
        osg::Vec3d facePosition; //掌子面坐标

        std::vector<osg::Vec3d> powerSupplyPointData; //供电点位置数据
        std::vector<osg::Vec3d> measuringPointData;   //测量点位置数据
        std::vector<double> elecCircleDisVec;         //每圈电极的偏移距，以掌子面为中心

        DeviceType deviceType;
        ExcavationDir excavationDir;
        QString mileageNumber;
        int mileage_left;
        int mileage_right;

        //保存观测装置标签下的数据
        void saveObservationDeviceSettingData(float width, float height, osg::Vec3d position, DeviceType type)
        {
            faceWidth    = width;
            faceHeight   = height;
            facePosition = position;
            deviceType   = type;
        }

        //保存供电点位置标签下的数据
        void savePowerSupplyPointDataData(std::vector<osg::Vec3d> data)
        {
            std::sort(begin(data), end(data), [](const osg::Vec3d &lhs, const osg::Vec3d &rhs)
                      {
                          return lhs.z() < rhs.z();
                      });

            powerSupplyPointData = data;
        }

        //保存测量点位置标签下的数据
        void saveMeasuringPointData(std::vector<osg::Vec3d> data)
        {
            std::sort(begin(data), end(data), [](const osg::Vec3d &lhs, const osg::Vec3d &rhs)
                      {
                          return lhs.x() < rhs.x();
                      });

            measuringPointData = data;
        }

        //保存每圈供电电极距离掌子面的延伸方向
        void saveCircleDis(std::vector<double> data)
        {
            std::sort(begin(data), end(data));

            elecCircleDisVec = data;
        }

        void clearData()
        {
            powerSupplyPointData.clear();
            measuringPointData.clear();
            elecCircleDisVec.clear();

            faceWidth  = 0.0f;
            faceHeight = 0.0f;
            facePosition.x() = 0;
            facePosition.y() = 0;
            facePosition.z() = 0;
            mileageNumber = "";
            mileage_left  = 0;
            mileage_right = 0;
        }
    };

    /********************************************************************/
    //模型对话框的结构体
    /********************************************************************/
    struct Modeling
    {
        float forecastLength;        //预报区域长度
        float predictionCellSpacing; //预报间隔
        float tunnelCavityRangeX;    //隧道空腔X区域
        float tunnelCavityRangeY;    //隧道空腔Y区域
        float inversionAreaRangeX;   //反演X区域设置
        float inversionAreaRangeY;   //反演Y区域设置

		float defaultForecastLength;        
		float defaultPredictionCellSpacing;
		float defaultTunnelCavityRangeX;
		float defaultTunnelCavityRangeY;
		float defaultInversionAreaRangeX;
		float defaultInversionAreaRangeY;

        //保存左侧参数数据
        void saveLeftParamData(float forecastLengthPara, float predictionCellSpacingPara, float tunnelCavityRangeXPara,
                               float tunnelCavityRangeYPara, float inversionAreaRangeXPara, float inversionAreaRangeYPara)
        {
            forecastLength        = forecastLengthPara;
            predictionCellSpacing = predictionCellSpacingPara;
            tunnelCavityRangeX    = tunnelCavityRangeXPara;
            tunnelCavityRangeY    = tunnelCavityRangeYPara;
            inversionAreaRangeX   = inversionAreaRangeXPara;
            inversionAreaRangeY   = inversionAreaRangeYPara;
        }

		//设置默认值
		void saveDefaultParamData(float forecastLengthPara, float predictionCellSpacingPara, float tunnelCavityRangeXPara,
			float tunnelCavityRangeYPara, float inversionAreaRangeXPara, float inversionAreaRangeYPara)
		{
			defaultForecastLength   =  forecastLengthPara;
			defaultPredictionCellSpacing = predictionCellSpacingPara;
			defaultTunnelCavityRangeX = tunnelCavityRangeXPara;
			defaultTunnelCavityRangeY = tunnelCavityRangeYPara;
			defaultInversionAreaRangeX = inversionAreaRangeXPara;
			defaultInversionAreaRangeY = inversionAreaRangeYPara;
		}

        void clearData()
        {
            forecastLength      = defaultForecastLength;      
			predictionCellSpacing = defaultPredictionCellSpacing;
            tunnelCavityRangeX    = defaultTunnelCavityRangeX;
            tunnelCavityRangeY    = defaultTunnelCavityRangeY;
            inversionAreaRangeX   = defaultInversionAreaRangeX;
            inversionAreaRangeY   = defaultInversionAreaRangeY;
        }
    };

    /********************************************************************/
    //正演参数对话框的结构体
    /********************************************************************/
    struct ForwardModelingParaSetting
    {
        PotentialDeviceSelectionSwitch potentialDeviceSelectionSwitch = PotentialDeviceSelectionSwitch::Schlumberger; //电位装置选择开关
        unsigned int currentINumX                                     = 0;                                            //供电电源在有限网格中X位置
        unsigned int currentINumY                                     = 0;                                            //供电电源在有限网格中Y位置
        unsigned int currentINumZ                                     = 0;                                            //供电电源在有限网格中Z位置
        double II                                                     = 1.0;                                          //电流大小
        double CII                                                    = 1.0;                                          //电流大小
        double sgM0Value                                              = 1000.0;                                       //供电电极附近的电阻率

        unsigned int inverX1 = 7, inverX2 = 12, inverY1 = 12, inverY2 = 15, inverZ1 = 0, inverZ2 = 20;
        float actual_begin_x = 0.0, actual_end_x = 0.0, actual_begin_y = 0.0, actual_end_y = 0.0, actual_begin_z = 0.0, actual_end_z = 0.0;
        unsigned int faceZInModel = 0;
        void saveSettingValue(PotentialDeviceSelectionSwitch selectionSwitch, double value, double cii, double ii, unsigned int X, unsigned int Y, unsigned int Z)
        {
            potentialDeviceSelectionSwitch = selectionSwitch;
            sgM0Value                      = value;
            CII                            = cii;
            II                             = ii;
            currentINumX                   = X;
            currentINumY                   = Y;
            currentINumZ                   = Z;
        }

        void clearData()
        {
            potentialDeviceSelectionSwitch = PotentialDeviceSelectionSwitch::AMNB;
            sgM0Value                      = 0;
            CII                            = 0;
            II                             = 0;
            currentINumX                   = 0;
            currentINumY                   = 0;
            currentINumZ                   = 0;
            actual_begin_x                 = 0.0;
            actual_end_x                   = 0.0;
            actual_begin_y                 = 0.0;
            actual_end_y                   = 0.0;
            actual_begin_z                 = 0.0;
            actual_end_z                   = 0.0;
        }

        void saveSimuForwardSettingValue(unsigned int X1, unsigned int X2, unsigned int Y1, unsigned int Y2, unsigned int Z1, unsigned int Z2)
        {
            inverX1 = X1;
            inverX2 = X2;
            inverY1 = Y1;
            inverY2 = Y2;
            inverZ1 = Z1;
            inverZ2 = Z2;
        }

        void saveSimuForwardSettingInverZ1Value(unsigned int Z1)
        {
            faceZInModel = Z1;
        }

        void saveSimuForwardSettingActualValue(float X1, float X2, float Y1, float Y2, float Z1, float Z2)
        {
            actual_begin_x = X1;
            actual_end_x   = X2;
            actual_begin_y = Y1;
            actual_end_y   = Y2;
            actual_begin_z = Z1;
            actual_end_z   = Z2;
        }

        void setForwardValue(unsigned int vCurrentINumZ)
        {
            currentINumZ = vCurrentINumZ;
        }
    };

    /********************************************************************/
    //反演参数对话框的结构体
    /********************************************************************/
    struct InversionParaSetting
    {
        InversionMethodSelection selectionSwitch;          //反演方法的选择开关
        ComputingMethodOfSmoothnessMatrix computingMethod; //光滑度矩阵的计算方法
        DataWeighting dataWeighting;                       //数据加权
        unsigned int INVMAX;                               //反演次数上限
        double EPS;                                        //反演迭代中的误差容许值
        double EPSRMS;                                     //相对拟合差的收敛数据
        double BoundU;                                     //反演模型中电阻率上限
        double BoundL;                                     //反演模型中电阻率下限
        double Lamda;                                      //阻尼因子
        double PCGRELERR;                                  //PCG法解方程时的收敛容许误差
        double PCGEPS;                                     //PCG法解方程时的均方差
        int PCGITMAX;                                      //PCG迭代次数上限
        bool UseLamda;
        bool showLegend = true;
        bool isSim      = true;

        void saveSettingValue(InversionMethodSelection selSwitch, ComputingMethodOfSmoothnessMatrix method, DataWeighting dataWeight,
                              unsigned int invMax, double eps, double epsRms, double boundU, double boundL, unsigned int pcgITMAX,
                              double pcgRELERR, double pcgEPS, double lamda, bool useLamda, bool s)
        {
            PCGITMAX        = pcgITMAX;
            PCGRELERR       = pcgRELERR;
            PCGEPS          = pcgEPS;
            selectionSwitch = selSwitch;
            computingMethod = method;
            dataWeighting   = dataWeight;
            INVMAX          = invMax;
            EPS             = eps;
            EPSRMS          = epsRms;
            BoundU          = boundU;
            BoundL          = boundL;
            Lamda           = lamda;
            UseLamda        = useLamda;
            showLegend      = s;
        }
    };

    //获取数据预处理对话框的结构体
    DataPreProcessInfo &getDataPreProcessInfo() { return m_dataPreProcessInfo; }

    //获取观测系统装置对话框的结构体
    ObservationSystemSetting &getObservationSystemSetting() { return m_observationSystemSetting; }

    //获取模型对话框的结构体
    Modeling &getModeling() { return m_modeling; }

    //获取正演参数装置对话框的结构体
    ForwardModelingParaSetting &getForwardModelingParaSetting() { return m_forwardModelingParaSetting; }

    //获取正演参数装置对话框的结构体
    InversionParaSetting &getInversionParaSetting() { return m_inversionParaSetting; }

    //获取装置对话框的结构体
    CommonSetting &getCommonSetting() { return m_commonSetting; }

    void resetData();

  signals:

  private:
    GlobalParam();
    ~GlobalParam();

    bool initialize();

  private:
    DataPreProcessInfo m_dataPreProcessInfo;
    ObservationSystemSetting m_observationSystemSetting;
    Modeling m_modeling;
    ForwardModelingParaSetting m_forwardModelingParaSetting;
    InversionParaSetting m_inversionParaSetting;
    CommonSetting m_commonSetting;
};