/*
*
*/

#ifndef FORWARDANDINVERSEPROCESS_H
#define FORWARDANDINVERSEPROCESS_H

#include <QThread>
#include <QReadWriteLock>
#include "stdio.h"
#include "stdlib.h"
#include "memory"
#include "QtCore\QObject"
#include "QtWidgets\QWidget"
#include "ModelingSubdivision.h"
#pragma execution_character_set("utf-8")
using namespace std;

namespace IP
{

typedef void(_stdcall *DPCGRC)(int *NRO, int *Ner, long double *Delta_M, long double *Pinv, long double *Rinv, long double *ZZinv, long double *JPCG_RELERR, int *JPCG_ITMAX);

class ForwardAndInverseProcess : public QThread
{
    Q_OBJECT
  public:
    enum ProcessType
    {
        simuforward,
        forward,
        invert,
        auto_gen_forward,
        auto_gen_invert,
        none
    };

    typedef struct ArrayIndex
    {
        ArrayIndex(int vFirst, int vTwo)
        {
            first = vFirst;
            two   = vTwo;
        }

        int first;
        int two;
    } ArrayIndexType;

    ForwardAndInverseProcess(QWidget *parent = nullptr);
    virtual ~ForwardAndInverseProcess();

    void processMultiThread(IP::ForwardAndInverseProcess::ProcessType vType);

    void stopThread();

    long double *MatmulOne(long double aa[9][3], unsigned int vCol, unsigned int vRow, long double bb[3], unsigned int vRow2);

    bool loadDPCGRCLibrary();
    bool unloadDPCGRCLibrary();
	void clearLocalVars();

    void setReselectedDialogOver(bool value) { m_isReselectDialogOver = value; }

    unsigned int getDNum() { return d_num; }
    unsigned int getDCNum() { return dc_num; }
    unsigned int getCircleNum() { return DATA_NUM / d_num; }

    ProcessType getPreOperationTyep() { return m_preOperationType; }
    ProcessType getCurrentOperationType() { return m_currentOperationType; }

  signals:

    void reselectCount();
    void onInvertCompleted(long double ***vData, unsigned int vZLen, unsigned int vYLen, unsigned int vXLen);
    void onInvertCompleted(osg::ref_ptr<osg::Vec4dArray> vPointArray, unsigned int vZLen, unsigned int vYLen, unsigned int vXLen);
    void setProgressValue(int);
    void creatForwardResult();
    void creatInversionResult();
    void creatSimuForwardResult();
    void autoGenForwardProcessFinished(bool result);
    void onInvertCompleted();

  protected:
    virtual void run() override;

  public:
    //初始化正演结果保存数据
    void initForwardData();
	void releaseMemory();

    bool initProcessData(); //初始化正演反演模型数据
    void setINVMAX(int value);

    void Model(unsigned int NX, unsigned int NY, unsigned int NZ, long double *X, long double *Y, long double *Z, unsigned int ND, unsigned int NE, long double **XY, int **I4);

    std::vector<double> &getForwardResult() { return m_forwardResult; };

    void setDat(std::vector<double> result);

    void process(ProcessType vType);
    void onResize();

    void autoGenForwardMulti();
    void autoGenInvertMulti();
    void autoGenForward();   //自动化正演
    void autoGenInversion(); //自动化反演

    void setModelSubdi(ModelingSubdivision *pModelSubdivison) { m_pModelSubdivison = pModelSubdivison; }
    ModelingSubdivision *getModelSubdi() { return m_pModelSubdivison; }
    bool getFirstInitData() { return m_firstInitData; }
	void setFirstInitData(bool flag) { m_firstInitData = flag; }

	void setForwardProcessSuccess(bool isSuccess) { m_forwardProcessSuccess = isSuccess; }
	bool getForwardProcessSuccess() {return m_forwardProcessSuccess;}
  public slots:

    void inducedPolariAutoGenProcess();

  protected:
    /*******************************************************************************************************/
    //function:正演函数
    void doForwardProcess(); //开始正演

    void Kzong();

    /**************************************************************************************************/
    //function:
    //SGM1:正常电阻率，SGM2异常电阻率
    void kE_2(long double a, long double b, long double c, long double SGM1, long double SGM2, long double KEB1[8][8], long double KEB2[8][8], int FLAG, long double H, long double L);

    void UU0(int I_NUM, long double *U0);

    /**
	  * @brief 将矩阵GA与向量X相乘，得到向量Y
	  *
	  * @param [in] ND 每个单元的电阻率值
	  * @param [in] X 有限元网格x方向边长
	  * @param [out] Y 有限元网格y方向边长
	  * @param [in] ID 有限元网格y方向边长
	  * @param [in] NUM x方向
	  */
    void MULTIPLY(int ND, long double *GA, long double *X, long double *Y, int NUM);

    /**************************************************************************************************/
    //function:
    //SGM1:正常电阻率，SGM2异常电阻率
    void kE_1(long double a, long double b, long double c, long double SGM1, long double SGM2);

    //以下是CHOLESKY法矩阵计算子程序
    //该子程序为乔里斯基法求解对称正定矩阵，其存储量相对较小，且可一次求解多组右端向量的方程
    void CHOLESKY(long double *A, int N, int M, int *IDOFA);
    void ID_GENERATOR(unsigned int NX, unsigned int NY, unsigned int NZ, unsigned int ND, unsigned int NE, int *IDID, unsigned int &NUM);
    void A_GENERATE(long double *A, int *IDOFA);
    /////////////////////////////////////
    void JA_generator(int ner, int z1, int z2, int x1, int x2, int y1, int y2, int ArrayType);
    /**
	  * @brief 最小二乘反演法的形状约束矩阵计算子程序
	  *
	  * @param [in] NRO 每个单元的电阻率值
	  * @param [in] NX 有限元网格x方向边长
	  * @param [in] NY 有限元网格y方向边长
	  * @param [in] NZ 有限元网格y方向边长
	  * @param [in] X1 x方向
	  * @param [in] Y1 y方向
	  * @param [in] Z1 z方向
	  * @param [in] X2 x方向
	  * @param [in] Y2 y方向
	  * @param [in] Z2 z方向
	  * @param [in] MIU 不知道
	  * @param [in] SHM 不知道
	  * @param [out] IDOFSHM 不知道
	  * @param [out] NUMOFSHM 不知道
	  */
    void SHM_OP(unsigned int NER, unsigned int Z1, unsigned int Z2, unsigned int X1, unsigned int X2, unsigned int Y1, unsigned int Y2,
                long double MIU, long double *SHM, int **IDOFSHM);

    /*******************************************************************************************/
    //function:
    //PARAMETER:ner:为反演的网格单元总数
    //long double PRECISION SM(7 * NER), SM_X(7 * NER), SM_Y(7 * NER), SM_Z(7 * NER)!光滑度矩阵
    //long double PRECISION SFM(7 * NER)!等式约束矩阵
    //INTEGER IDOFSFM(2, 7 * NER), NUMOFSFM !等式约束矩阵索引
    void SM_OPERATOR(unsigned int ner, int z1, int z2, int x1, int x2, int y1, int y2, int SM_TYPE);
    void diriv0fA(long double a, long double b, long double c);

    //函数说明:一维非零元素压缩光滑度矩阵SM与列向量的乘的子程序
    //NER应该是y向量的个数
    //SM是一个已知的一维数组
    //X是一个已知的一维数组
    //Y是一个已知的一维数组,并且在此函数中被重新初始化后，赋值。
    //IDOFSM是一个已知的二维数组，应该是全局变量
    //NUMOFSM代表光滑度矩阵的一维存储模式的计数器
    //IPATH代表计算方程的右端项
    void MultiplySM(int NER, long double *SM, long double *X, long double *Y, int **IDOFSM, int NUMOFSM, int IPATH);

    //函数说明：ax=z!!!!!!矩阵乘以向量
    //nra是矩阵的行数
    //nca是矩阵的列数
    //a是一个已知矩阵(nra和nca代表行列)
    //nx是向量x的个数，即大小
    //x是一个已知向量
    //nz代表返回值向量z的个数
    //z代表返回值向量，放的是乘的结果【可以在内部new】
    //ipath代表计算方程的右端项
    void DMURRv1(int nra, int nca, long double **a, int nx, long double *x, int nz, long double *z, int ipath);

  private:
    void createProcessBar();
    void initProcessBar();
    void setProcessBarValue(int value);
    void initialization();
    void reset();

  private:
    bool m_isReselectDialogOver;
    bool m_firstInitData; //正反演数据是否初始化
	bool m_forwardProcessSuccess; //正演成功标记，决定是否进行反演

    ProcessType m_currentOperationType;
    ProcessType m_preOperationType;

    double **M_RESULT; //(4, DATA_NUM*L_NUM)!实测视电阻率数据和装置系数向量
    double ***NRO;     //每个单元的电阻率值
    int **IDOFSM;      //INTEGER IDOFSFM(2, 7 * NER), NUMOFSFM !等式约束矩阵索引
    long double **D;  //在cholesky程序中输入时为多组方程的右端项, 输出时为方程的解
    int **I4;    //所有单元对用的顶点索引
    long double **JA; // JA(DATA_NUM*L_NUM, NER)!分别存储视电阻率和观测电位对模参的偏导数

    long double *W_A; //偏导数矩阵的权重
    long double **XY; //每个节点的三个坐标
    long double *X;   //x方向所有节点坐标
    long double *Y;   //y方向所有节点坐标
    long double *Z;   //z方向所有节点坐标
    long double *XL;  //模型在X方向所有单元的边长
    long double *YL;  //模型在Y方向所有单元的边长
    long double *ZL;  //存储模型在Z方向所有单元的边长

    long double *RINV;
    long double *RINV2;
    long double *BINV;
    long double *PINV;
    long double *YINV1;
    long double *YINV2;
    long double *ZINV;
    long double *ZINV2;
    long double *ZZINV;
    long double *ZZINV1;
    long double *ZZINV2;

    long double ***BoundU1; //每个单元的电阻率值
    long double *SM;
    long double **KE1 = NULL; //待定
    long double **KE2 = NULL; //待定
    long double **DA  = NULL; //待定
    long double *SHM;
    int **IDOFSHM;

    unsigned int P_DIST; //测量电极之间的间距（隔了多少个边长）
    unsigned int L_DIST; //测量电极之间的间距（隔了多少个边长）
    unsigned int I_NUMX; //供电电源点的‘X坐标’
    unsigned int I_NUMY; //供电电源点的‘Y坐标’
    unsigned int I_NUMZ; //供电电源点的‘Z坐标’
    unsigned int NUM;    //GA数组的实际大小、A数组的实际大小
    unsigned int INVMAX;
    unsigned int ND;       //节点总数
    unsigned int NX;       //有限元网格x方向边长
    unsigned int NY;       //有限元网格y方向边长
    unsigned int NZ;       //有限元网格z方向边长
    unsigned int NE;       //单元总数
    unsigned int dc_num;   //环形屏蔽电极(圈×电极数)
    unsigned int d_num;    //高密度电法的电极总数
    int DATA_NUM; //对高密度电法数据点的总数的估计
    int L_NUM;    //测线数

    int *IDID;      //GA和GA1的二级索引数组
    int *D_POINT;   //存储测量点和观测点的节点号
    int ARRAY_TYPE; //装置类型标记
    int m_ner;
    int I_num;  //供电电源点的节点编号及编号的‘坐标’
    int band;   //用来存储半带宽
    int numofa; //A数组的实际大小
    int NUMOFSM;
    int JPCG_ITMAX; //PCG法解方程时的迭代次数上限
    int SM_TYPE;
    int ITER_NUM;
    int NUMOFSHM;
    int INV_METHOD;
    int DATA_WEIGHT;         //数据加权
    int potentialDeviceType; ///< 电位装置选择开关

    float m_forwardTimeProportion;
    float m_increaseDensity;
    float m_currentProgress;
    long double LAMDA;       //阻尼因子
    long double BoundU;      ///< 参数取值的上限
    long double BoundL;      ///< 参数取值的下限
    long double II;          //电流的大小
    long double C_II;        //电流的大小
    long double JPCG_RELERR; //PCG法解方程时的收敛容许误差
    long double JPCG_EPS;    //PCG法解方程时的均方差
    long double EPS;         //最小二乘反演中的收敛容许误差
    long double EPS_RSM;     //最小二乘中收敛的容许误差
    long double SGM0;        //供电电极附近的电阻率值
    long double MN;          //存储最小电极间距

    long double *DAT; //保存实测数据与模拟数据的插值
    long double *GA;  //总体系数的一维非零元素存储数组GA
    long double *GA1; //总体系数的一维非零元素存储数组GA

	long double* DELTA_D;
	long double* delta_m;

    ModelingSubdivision *m_pModelSubdivison; //模型剖分类
    QWidget *m_parent;

    std::vector<double> m_forwardResult;
    vector<ArrayIndex> ID_vector;
    osg::ref_ptr<osg::Vec4dArray> m_resultPointArray; //保存反演结果的反演区域值

    HINSTANCE m_DPCGRCInstance;
    DPCGRC m_funcDPCGRC;

	vector<long double*> m_localVars;
	vector<int*> m_localIntVars;

	QReadWriteLock _lock;
};
}

#endif