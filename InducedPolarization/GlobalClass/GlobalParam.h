#pragma once
//��ʵ���ֻ࣬��ŶԻ��������õ�����
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
    //װ������
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
	* @brief �������
	*/
    enum ExcavationDir
    {
        GreaterMileage,
        LessMileage
    };

    //��λװ��ѡ�񿪹�
    enum PotentialDeviceSelectionSwitch
    {
        Schlumberger = 0,
        AMNB
    };

    //���ݷ���ѡ�񿪹�
    enum InversionMethodSelection
    {
        GA = 0,      //GA
        leastSquare, //��С����
        united,      //����
        antColony    //��Ⱥ
    };

    //�⻬�Ⱦ���ļ��㷽��
    enum ComputingMethodOfSmoothnessMatrix
    {
        distanceFactor   = 1, //����������
        noDistanceFactor = 2  //������������
    };

    //���ݼ�Ȩ
    enum DataWeighting
    {
        linear = 0, //����
        index,      //ָ��
        secondary,  //����
        noWeighting //�޼�Ȩ
    };

    static GlobalParam *instance();

    struct DataPreProcessInfo
    {
        vector<osg::Vec4d> badPointsList;
        vector<double> observeDataList;
    };

    /********************************************************************/
    //�������öԻ���ṹ��
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
    //�۲�ϵͳװ�öԻ���Ľṹ��
    /********************************************************************/
    struct ObservationSystemSetting
    {
        float faceWidth;         //��������
        float faceHeight;        //������߶�
        osg::Vec3d facePosition; //����������

        std::vector<osg::Vec3d> powerSupplyPointData; //�����λ������
        std::vector<osg::Vec3d> measuringPointData;   //������λ������
        std::vector<double> elecCircleDisVec;         //ÿȦ�缫��ƫ�ƾ࣬��������Ϊ����

        DeviceType deviceType;
        ExcavationDir excavationDir;
        QString mileageNumber;
        int mileage_left;
        int mileage_right;

        //����۲�װ�ñ�ǩ�µ�����
        void saveObservationDeviceSettingData(float width, float height, osg::Vec3d position, DeviceType type)
        {
            faceWidth    = width;
            faceHeight   = height;
            facePosition = position;
            deviceType   = type;
        }

        //���湩���λ�ñ�ǩ�µ�����
        void savePowerSupplyPointDataData(std::vector<osg::Vec3d> data)
        {
            std::sort(begin(data), end(data), [](const osg::Vec3d &lhs, const osg::Vec3d &rhs)
                      {
                          return lhs.z() < rhs.z();
                      });

            powerSupplyPointData = data;
        }

        //���������λ�ñ�ǩ�µ�����
        void saveMeasuringPointData(std::vector<osg::Vec3d> data)
        {
            std::sort(begin(data), end(data), [](const osg::Vec3d &lhs, const osg::Vec3d &rhs)
                      {
                          return lhs.x() < rhs.x();
                      });

            measuringPointData = data;
        }

        //����ÿȦ����缫��������������췽��
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
    //ģ�ͶԻ���Ľṹ��
    /********************************************************************/
    struct Modeling
    {
        float forecastLength;        //Ԥ�����򳤶�
        float predictionCellSpacing; //Ԥ�����
        float tunnelCavityRangeX;    //�����ǻX����
        float tunnelCavityRangeY;    //�����ǻY����
        float inversionAreaRangeX;   //����X��������
        float inversionAreaRangeY;   //����Y��������

		float defaultForecastLength;        
		float defaultPredictionCellSpacing;
		float defaultTunnelCavityRangeX;
		float defaultTunnelCavityRangeY;
		float defaultInversionAreaRangeX;
		float defaultInversionAreaRangeY;

        //��������������
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

		//����Ĭ��ֵ
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
    //���ݲ����Ի���Ľṹ��
    /********************************************************************/
    struct ForwardModelingParaSetting
    {
        PotentialDeviceSelectionSwitch potentialDeviceSelectionSwitch = PotentialDeviceSelectionSwitch::Schlumberger; //��λװ��ѡ�񿪹�
        unsigned int currentINumX                                     = 0;                                            //�����Դ������������Xλ��
        unsigned int currentINumY                                     = 0;                                            //�����Դ������������Yλ��
        unsigned int currentINumZ                                     = 0;                                            //�����Դ������������Zλ��
        double II                                                     = 1.0;                                          //������С
        double CII                                                    = 1.0;                                          //������С
        double sgM0Value                                              = 1000.0;                                       //����缫�����ĵ�����

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
    //���ݲ����Ի���Ľṹ��
    /********************************************************************/
    struct InversionParaSetting
    {
        InversionMethodSelection selectionSwitch;          //���ݷ�����ѡ�񿪹�
        ComputingMethodOfSmoothnessMatrix computingMethod; //�⻬�Ⱦ���ļ��㷽��
        DataWeighting dataWeighting;                       //���ݼ�Ȩ
        unsigned int INVMAX;                               //���ݴ�������
        double EPS;                                        //���ݵ����е��������ֵ
        double EPSRMS;                                     //�����ϲ����������
        double BoundU;                                     //����ģ���е���������
        double BoundL;                                     //����ģ���е���������
        double Lamda;                                      //��������
        double PCGRELERR;                                  //PCG���ⷽ��ʱ�������������
        double PCGEPS;                                     //PCG���ⷽ��ʱ�ľ�����
        int PCGITMAX;                                      //PCG������������
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

    //��ȡ����Ԥ����Ի���Ľṹ��
    DataPreProcessInfo &getDataPreProcessInfo() { return m_dataPreProcessInfo; }

    //��ȡ�۲�ϵͳװ�öԻ���Ľṹ��
    ObservationSystemSetting &getObservationSystemSetting() { return m_observationSystemSetting; }

    //��ȡģ�ͶԻ���Ľṹ��
    Modeling &getModeling() { return m_modeling; }

    //��ȡ���ݲ���װ�öԻ���Ľṹ��
    ForwardModelingParaSetting &getForwardModelingParaSetting() { return m_forwardModelingParaSetting; }

    //��ȡ���ݲ���װ�öԻ���Ľṹ��
    InversionParaSetting &getInversionParaSetting() { return m_inversionParaSetting; }

    //��ȡװ�öԻ���Ľṹ��
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