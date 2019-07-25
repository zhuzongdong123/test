#include "ForwardAndInverseProcess.h"
#include "LogSystem.h"
#include "DialogReselectCountOfIterations.h"
#include "GlobalClass/DataManager.h"
#include "3ddisplay/Common.h"
#include "GlobalClass/GlobalParam.h"
#include <QMessageBox>
#include "QTextCodec"
#include <stdlib.h>
#include <stdio.h>

namespace IP
{
ForwardAndInverseProcess::ForwardAndInverseProcess(QWidget *parent) : QThread(parent)
{
    potentialDeviceType = 0;
    JA                  = nullptr;
    m_ner               = 0;
    m_DPCGRCInstance    = 0;
    m_funcDPCGRC        = nullptr;

    m_currentOperationType = ProcessType::none;

    LAMDA = 0.0;
    MN    = 0.5;

	m_parent               = parent;
    DATA_NUM               = 0;
    L_NUM                  = 0;

    P_DIST = 1;
    L_DIST = 2;

    JPCG_ITMAX  = 800000;
    JPCG_RELERR = 0.1;
    JPCG_EPS    = 0.3;
    GA1         = nullptr;
    GA          = nullptr;

	DELTA_D = nullptr;
	delta_m = nullptr;

    m_forwardTimeProportion = 0.6f;
    m_increaseDensity       = 0.3f;
    m_currentProgress       = 0.0f;
    m_currentOperationType  = ProcessType::none;

    initialization();
}

ForwardAndInverseProcess::~ForwardAndInverseProcess()
{
    releaseMemory();

    unloadDPCGRCLibrary();
}

void ForwardAndInverseProcess::processMultiThread(IP::ForwardAndInverseProcess::ProcessType vType)
{
    if (this->isRunning())
        this->stopThread();
    m_currentOperationType = vType;
	
    start(QThread::HighestPriority);
}

void ForwardAndInverseProcess::stopThread()
{
// 	requestInterruption();
// 	quit();
	terminate();
	wait();
    reset();
}

long double *ForwardAndInverseProcess::MatmulOne(long double aa[9][3], unsigned int vCol, unsigned int vRow, long double bb[3], unsigned int vRow2)
{
    if (vCol != vRow2)
        return NULL;

    long double *resultData = new long double[vRow];

    for (unsigned int i = 0; i < vRow; i++)
    {
        resultData[i] = 0;
        for (unsigned int j = 0; j < vRow2; j++)
        {
            resultData[i] += aa[i][j] * bb[j];
        }
    }
    return resultData;
}

bool ForwardAndInverseProcess::loadDPCGRCLibrary()
{
    QString strUrl = QCoreApplication::applicationDirPath();

    strUrl = QDir::toNativeSeparators(strUrl);

    strUrl += "\\DPCGRC.dll";

    QTextCodec *code     = QTextCodec::codecForName("GB2312"); //解决中文路径问题
    std::string filePath = code->fromUnicode(strUrl).data();

	QLog("导入路径:%s", filePath.c_str());
    m_DPCGRCInstance = LoadLibraryA((filePath.c_str()));

    if (0 == m_DPCGRCInstance)
    {
		QLog("导入DPCGRC DLL失败");
        return false;
    }

    m_funcDPCGRC = (DPCGRC)GetProcAddress(m_DPCGRCInstance, "DPCGRC_EX");

    if (nullptr == m_funcDPCGRC)
    {
        return false;
    }

    return true;
}

bool ForwardAndInverseProcess::unloadDPCGRCLibrary()
{
    if (0 == m_DPCGRCInstance)
    {
        return false;
    }

    if (FALSE == FreeLibrary(m_DPCGRCInstance))
    {
        return false;
    }

    m_DPCGRCInstance = 0;

    m_funcDPCGRC = nullptr;

    return true;
}

void ForwardAndInverseProcess::clearLocalVars()
{
	//_lock.lockForWrite();

	for (auto x : m_localVars)
	{
		SAFE_DELETE_ARRAY(x);
	}

	m_localVars.clear();

	for (auto x : m_localIntVars)
	{
		SAFE_DELETE_ARRAY(x);
	}

	m_localIntVars.clear();

	//_lock.unlock();
}

void ForwardAndInverseProcess::run()
{
    ProcessType t = m_currentOperationType;

    if (ProcessType::auto_gen_forward == m_currentOperationType)
    {
        autoGenForward(); //自动化正演
    }
    else if (ProcessType::auto_gen_invert == m_currentOperationType)
    {
        autoGenInversion(); //自动化反演
    }
    else
    {
        process(m_currentOperationType);
    }
    QThread::run();
}

void ForwardAndInverseProcess::initForwardData()
{
}

void ForwardAndInverseProcess::setDat(std::vector<double> result)
{
    if (result.size() == 0 || (DATA_NUM * L_NUM) < result.size())
        return;

    if (NULL == DAT)
    {
        DAT = new long double[DATA_NUM * L_NUM]; // !用于存储理论数据与实际数据的差向量
    }
    memset(DAT, 0.0, sizeof(long double) * (DATA_NUM * L_NUM));
    for (unsigned int i = 0; i < result.size(); i++)
    {
        DAT[i] = result[i];
    }
}

void ForwardAndInverseProcess::Model(unsigned int NX, unsigned int NY, unsigned int NZ, long double *X, long double *Y, long double *Z, unsigned int ND, unsigned int NE, long double **XY, int **I4)
{
    for (unsigned int IZ = 0; IZ < NZ + 1; IZ++)
    {
        for (unsigned int IX = 0; IX < NX + 1; IX++)
        {
            for (unsigned int IY = 0; IY < NY + 1; IY++)
            {
                unsigned int N = (IZ) * (NX + 1) * (NY + 1) + (IX) * (NY + 1) + IY;

                XY[N][0] = X[IX]; //第N个节点的X坐标
                XY[N][1] = Y[IY]; //第N个节点的Y坐标
                XY[N][2] = Z[IZ]; //第N个节点的Z坐标
            }
        }
    }

    for (unsigned int IZ = 0; IZ < NZ; IZ++)
    {
        for (unsigned int IX = 0; IX < NX; IX++)
        {
            for (unsigned int IY = 0; IY < NY; IY++)
            {
                unsigned int N  = (IZ)*NX * NY + (IX)*NY + IY;
                unsigned int N1 = (IZ) * (NX + 1) * (NY + 1) + (IX) * (NY + 1) + IY;

                I4[N][0] = N1;
                I4[N][1] = N1 + 1;      //按照X方向为隧道高度方向，在初始节点的上方
                I4[N][2] = N1 + NY + 2; //按照Y方向为隧道宽度，在XY界面的右上角
                I4[N][3] = N1 + NY + 1; //按照Y方向为隧道宽度，在XY截面的右下角
                I4[N][4] = N1 + (NX + 1) * (NY + 1);
                I4[N][5] = N1 + (NX + 1) * (NY + 1) + 1;
                I4[N][6] = N1 + (NX + 1) * (NY + 1) + NY + 2;
                I4[N][7] = N1 + (NX + 1) * (NY + 1) + NY + 1;
            }
        }
    }
}

/**************************************************************************************************************/
//function  :  初始化正演反演模型数据
bool ForwardAndInverseProcess::initProcessData()
{
    releaseMemory();
    //if (m_firstInitData == false)
    {
        GlobalParam::ForwardModelingParaSetting &setting = GlobalParam::instance()->getForwardModelingParaSetting();

        const int electroNodeEachCir = 4; //每圈供电电极的个数，目前默认为四个

        I_NUMX = setting.currentINumX;
        I_NUMY = setting.currentINumY;
        I_NUMZ = setting.currentINumZ;
        I_num  = 0;
        SGM0   = setting.sgM0Value;
        C_II   = setting.CII;
        II     = setting.II;

        if (NULL == m_pModelSubdivison || m_pModelSubdivison->getMeasXYIndexVec().size() == 0)
        {
            QMessageBox::warning(nullptr, QString::fromUtf8("警告"), QString::fromUtf8("请进行数据隧洞建模"));
            return false;
        }
        std::vector<osg::Vec2> meaPointXYIndexVec = m_pModelSubdivison->getMeasXYIndexVec();
        int circleNum                             = m_pModelSubdivison->getElectroCircleNum(); //获取供电电极的圈数
        NX                                        = m_pModelSubdivison->getXDirEdgeCount();
        NY                                        = m_pModelSubdivison->getYDirEdgeCount();
        NZ                                        = m_pModelSubdivison->getZDirEdgeCount();

        ND       = (NX + 1) * (NY + 1) * (NZ + 1); //单元节点总数
        NE       = NX * NY * NZ;                   //单元总数
        d_num    = meaPointXYIndexVec.size();
        dc_num   = circleNum * electroNodeEachCir;
        L_NUM    = 1;
        DATA_NUM = circleNum * d_num;
        IDID     = new int[ND + 1]; //GA和GA1的一级和二级索引数组

        I4 = new int *[NE];
        for (unsigned int i = 0; i < NE; i++)
        {
            I4[i] = new int[8];
            memset(I4[i], 0, sizeof(int) * 8);
        }

        X = new long double[NX + 1];
        memset(X, 0, sizeof(long double) * (NX + 1));
        Y = new long double[NY + 1];
        memset(Y, 0, sizeof(long double) * (NY + 1));
        Z = new long double[NZ + 1];
        memset(Z, 0, sizeof(long double) * (NZ + 1));

        XY = new long double *[ND];
        for (unsigned int i = 0; i < ND; i++)
        {
            XY[i] = new long double[3];
            memset(XY[i], 0.0, sizeof(long double) * 3);
        }

        NRO = new double **[NZ];
        for (unsigned int i = 0; i < NZ; i++)
        {
            NRO[i] = new double *[NY];
            for (unsigned int j = 0; j < NY; j++)
            {
                NRO[i][j] = new double[NX];
                memset(NRO[i][j], 0.0, sizeof(double) * NX);
            }
        }

        BoundU1 = new long double **[NZ];
        for (unsigned int i = 0; i < NZ; i++)
        {
            BoundU1[i] = new long double *[NY];
            for (unsigned int j = 0; j < NY; j++)
            {
                BoundU1[i][j] = new long double[NX];
                memset(BoundU1[i][j], 0.0, sizeof(long double) * NX);
            }
        }

        M_RESULT = new double *[DATA_NUM * L_NUM];
        for (unsigned int i = 0; i < DATA_NUM * L_NUM; i++)
        {
            M_RESULT[i] = new double[4];
            memset(M_RESULT[i], 0, sizeof(double) * 4);
        }

        XL = new long double[NX];
        memset(XL, 0.0, sizeof(long double) * (NX));

        std::vector<double> XLVec = m_pModelSubdivison->getXLVector();
        for (int i = 0; i < XLVec.size(); i++)
        {
            XL[i] = XLVec[i];
        }

        YL = new long double[NY];
        memset(YL, 0.0, sizeof(long double) * (NY));
        std::vector<double> YLVec = m_pModelSubdivison->getYLVector();
        for (int i = 0; i < YLVec.size(); i++)
        {
            YL[i] = YLVec[i];
        }

        ZL = new long double[NZ];
        memset(ZL, 0.0, sizeof(long double) * (NZ));
        std::vector<double> ZLVec = m_pModelSubdivison->getZLVector();
        for (int i = 0; i < ZLVec.size(); i++)
        {
            ZL[i] = ZLVec[i];
        }

        D_POINT = new int[d_num * L_NUM + dc_num + 1];

        unsigned int X1 = m_pModelSubdivison->getInvertionXBeg();
        unsigned int X2 = m_pModelSubdivison->getInvertionXEnd();
        unsigned int Y1 = m_pModelSubdivison->getInvertionYBeg();
        unsigned int Y2 = m_pModelSubdivison->getInvertionYEnd();
        unsigned int Z1 = m_pModelSubdivison->getTunnelForZBeg();
        unsigned int Z2 = m_pModelSubdivison->getTunnelForZEnd();

        unsigned int xCavityBeg = m_pModelSubdivison->getTunnelCavityXBegin();
        unsigned int xCavityEnd = m_pModelSubdivison->getTunnelCavityXEnd();
        unsigned int yCavityBeg = m_pModelSubdivison->getTunnelCavityYBegin();
        unsigned int yCavityEnd = m_pModelSubdivison->getTunnelCavityYEnd();

        unsigned int ner = (X2 - X1 + 1) * (Y2 - Y1 + 1) * (Z2 - Z1 + 1);
        m_ner            = ner;
        SM = new long double[7 * ner];
        memset(SM, 0.0, sizeof(long double) * (7 * ner));
        IDOFSM = new int *[7 * ner];
        for (unsigned int i = 0; i < 7 * ner; i++)
        {
            IDOFSM[i]    = new int[2];
            IDOFSM[i][0] = 0;
            IDOFSM[i][1] = 0;
        }

        KE1 = new long double *[8];
        for (unsigned int i = 0; i < 8; i++)
        {
            KE1[i] = new long double[8];
            memset(KE1[i], 0, sizeof(long double) * 8);
        }

        KE2 = new long double *[8];
        for (unsigned int i = 0; i < 8; i++)
        {
            KE2[i] = new long double[8];
            memset(KE2[i], 0, sizeof(long double) * 8);
        }

        DA = new long double *[8];
        for (unsigned int i = 0; i < 8; i++)
        {
            DA[i] = new long double[8];
            memset(DA[i], 0, sizeof(long double) * 8);
        }

        //下面计算电源点的坐标
        I_num = (I_NUMZ - 1) * (NX + 1) * (NY + 1) + (I_NUMX) * (NY + 1) + I_NUMY;

        //下面定义各方向的坐标数组
        X[0] = 0.00;
        for (unsigned int i = 1; i < NX + 1; i++)
        {
            X[i] = X[i - 1] + XL[i - 1]; //形成X数组
        }

        Y[NY] = 0.00;
        for (unsigned int i = 1; i < NY + 1; i++)
        {
            Y[NY - i] = Y[NY + 1 - i] + YL[i - 1]; //形成Y数组
        }

        Z[0] = 0.00;
        for (unsigned int i = 1; i < NZ + 1; i++)
        {
            Z[i] = Z[i - 1] + ZL[i - 1]; //形成Z数组
        }

        //建立模型，形成节点坐标，单元编号、节点编号等
        int **tmpI4    = m_pModelSubdivison->getTotalGridIndex();
        double **tmpXY = m_pModelSubdivison->getTotalNodePos();
        if (NULL == tmpXY)
        {
            QMessageBox::warning(nullptr, QString::fromUtf8("警告"), QString::fromUtf8("节点坐标为空"));
            return false;
        }

        for (unsigned int i = 0; i < NE; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                I4[i][j] = tmpI4[i][j];
            }
        }

        for (unsigned int i = 0; i < ND; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                XY[i][j] = tmpXY[i][j];
            }
        }

        memset(D_POINT, 0, sizeof(int) * (d_num * L_NUM + dc_num + 1));
        ////定义测量电极坐标
        /*D_POINT[0] = (13 - 1)*(NX + 1)*(NY + 1) + 11 * (NY + 1) + 10 - 1;
		D_POINT[1] = (13 - 1)*(NX + 1)*(NY + 1) + 11 * (NY + 1) + 11 - 1;
		D_POINT[2] = (13 - 1)*(NX + 1)*(NY + 1) + 11 * (NY + 1) + 12 - 1;
		D_POINT[3] = (13 - 1)*(NX + 1)*(NY + 1) + 11 * (NY + 1) + 13 - 1;
		D_POINT[4] = (13 - 1)*(NX + 1)*(NY + 1) + 11 * (NY + 1) + 14 - 1;

		D_POINT[5] = (13 - 1)*(NX + 1)*(NY + 1) + 10 * (NY + 1) + 14 - 1;
		D_POINT[6] = (13 - 1)*(NX + 1)*(NY + 1) + 10 * (NY + 1) + 13 - 1;
		D_POINT[7] = (13 - 1)*(NX + 1)*(NY + 1) + 10 * (NY + 1) + 12 - 1;
		D_POINT[8] = (13 - 1)*(NX + 1)*(NY + 1) + 10 * (NY + 1) + 11 - 1;
		D_POINT[9] = (13 - 1)*(NX + 1)*(NY + 1) + 10 * (NY + 1) + 10 - 1;

		for (unsigned int i = 0; i < 10; i++)
		{
			D_POINT[d_num*L_NUM + i] = (13 - (i + 1))*(NX + 1)*(NY + 1) + 8 * (NY + 1) + 8 - 1;
			D_POINT[d_num*L_NUM + circleNum + i] = (13 - (i + 1))*(NX + 1)*(NY + 1) + 8 * (NY + 1) + 16 - 1;
			D_POINT[d_num*L_NUM + circleNum * 2 + i] = (13 - (i + 1))*(NX + 1)*(NY + 1) + 14 * (NY + 1) + 8 - 1;
			D_POINT[d_num*L_NUM + circleNum * 3 + i] = (13 - (i + 1))*(NX + 1)*(NY + 1) + 14 * (NY + 1) + 16 - 1;
		}*/

        for (int i = 0; i < meaPointXYIndexVec.size(); i++)
        {
            //定义测量电极坐标
            D_POINT[i] = Z1 * (NX + 1) * (NY + 1) + meaPointXYIndexVec[i].x() * (NY + 1) + meaPointXYIndexVec[i].y() - 1;
            //D_POINT[i] = Z1 * (NX + 1) * (NY + 1) + (meaPointXYIndexVec[i].x()+1) * (NY + 1) + meaPointXYIndexVec[i].y();
        }

        for (unsigned int i = 0; i < circleNum; i++)
        {
            D_POINT[d_num * L_NUM + i]                 = (Z1 - i) * (NX + 1) * (NY + 1) + (xCavityBeg + 1) * (NY + 1) + yCavityBeg - 1 + 1;
            D_POINT[d_num * L_NUM + circleNum + i]     = (Z1 - i) * (NX + 1) * (NY + 1) + (xCavityBeg + 1) * (NY + 1) + yCavityEnd - 1 + 2;
            D_POINT[d_num * L_NUM + circleNum * 2 + i] = (Z1 - i) * (NX + 1) * (NY + 1) + (xCavityEnd + 2) * (NY + 1) + yCavityBeg - 1 + 1;
            D_POINT[d_num * L_NUM + circleNum * 3 + i] = (Z1 - i) * (NX + 1) * (NY + 1) + (xCavityEnd + 2) * (NY + 1) + yCavityEnd - 1 + 2;
        }

        //形成一维压缩数组GA和GA1
        ID_GENERATOR(NX, NY, NZ, ND, NE, IDID, NUM);
        m_firstInitData = true;
    }

    return true;
}

void ForwardAndInverseProcess::setINVMAX(int value)
{
    INVMAX += value;
    //	_mutex.unlock();
}

void ForwardAndInverseProcess::process(ProcessType vType)
{
    if (NULL == m_pModelSubdivison)
        return;

    if (vType == ProcessType::invert && m_firstInitData == false)
        return;

    m_currentOperationType = vType;

    unsigned int X1 = m_pModelSubdivison->getInvertionXBeg();
    unsigned int X2 = m_pModelSubdivison->getInvertionXEnd();
    unsigned int Y1 = m_pModelSubdivison->getInvertionYBeg();
    unsigned int Y2 = m_pModelSubdivison->getInvertionYEnd();
    unsigned int Z1 = m_pModelSubdivison->getTunnelForZBeg();
    unsigned int Z2 = m_pModelSubdivison->getTunnelForZEnd();

    unsigned int ner = (X2 - X1 + 1) * (Y2 - Y1 + 1) * (Z2 - Z1 + 1);

    if (vType == ProcessType::forward)
    {
		GlobalParam::instance()->getInversionParaSetting().isSim = false;
        QLog("开始进行三维电阻率层析成像法的数值正演");
        QLog("正演流程开始:\n");
    }
    else if (vType == ProcessType::simuforward)
    {
		GlobalParam::instance()->getInversionParaSetting().isSim = true;
        QLog("模拟正演流程开始:\n");
    }
    else if (vType == ProcessType::invert)
    {
        QLog("反演流程开始:\n");
    }

    GlobalParam::InversionMethodSelection inverSwitch;
    if (inverSwitch == GlobalParam::InversionMethodSelection::GA)
    {
        QLog("待定\n");
    }

    unsigned int INV_NUM = 0;

    if (NULL == DAT)
    {
        DAT = new long double[DATA_NUM * L_NUM]; // !用于存储理论数据与实际数据的差向量
        memset(DAT, 0.0, sizeof(long double) * (DATA_NUM * L_NUM));
    }
    long double RES, RMS, EPS_RMS; //计算实测值与理论值之间的均方差，相对拟合差以及相对拟合差的收敛判据

    //下面判断反演次数是否达到上限，若达到上限是继续还是终止？
    GlobalParam::InversionParaSetting &inversionParam = GlobalParam::instance()->getInversionParaSetting();
    INVMAX                                            = inversionParam.INVMAX;
    unsigned int FLAG                                 = 0;

    JPCG_ITMAX  = inversionParam.PCGITMAX;  //PCG法解方程时的迭代次数上限
    JPCG_RELERR = inversionParam.PCGRELERR; //PCG法解方程时的收敛容许误差
    JPCG_EPS    = inversionParam.PCGEPS;
    BoundL      = inversionParam.BoundL;
    BoundU      = inversionParam.BoundU;

    //下面定义各单元的电阻率值
    for (unsigned int i = 0; i < NZ; i++)
    {
        for (unsigned int j = 0; j < NY; j++)
        {
            for (unsigned int k = 0; k < NX; k++)
            {
                BoundU1[i][j][k] = 1550;
                NRO[i][j][k]     = 1000.0;
            }
        }
    }

    //以下定义隧道空腔
    unsigned int xCavityBeg = m_pModelSubdivison->getTunnelCavityXBegin();
    unsigned int xCavityEnd = m_pModelSubdivison->getTunnelCavityXEnd();
    unsigned int yCavityBeg = m_pModelSubdivison->getTunnelCavityYBegin();
    unsigned int yCavityEnd = m_pModelSubdivison->getTunnelCavityYEnd();

    for (unsigned int k = 0; k < Z1; k++)
    {
        for (unsigned int j = yCavityBeg; j <= yCavityEnd; j++)
        {
            for (unsigned int i = xCavityBeg; i <= xCavityEnd; i++)
            {
                NRO[k][j][i] = 10000000.00;
            }
        }
    }

    //建立模型，形成节点坐标，单元编号、节点编号等
    int **tmpI4    = m_pModelSubdivison->getTotalGridIndex();
    double **tmpXY = m_pModelSubdivison->getTotalNodePos();
    for (unsigned int i = 0; i < NE; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            I4[i][j] = tmpI4[i][j];
        }
    }

    for (unsigned int i = 0; i < ND; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            XY[i][j] = tmpXY[i][j];
        }
    }

    if (ProcessType::invert == m_currentOperationType)
    {
        setProcessBarValue(0);
    }
    else
    {
        setProcessBarValue(0);
    }

	if (nullptr == DELTA_D)
	{
		DELTA_D = new long double[DATA_NUM * L_NUM]; // !用于存储理论数据与实际数据的差向量
	}

	memset(DELTA_D, 0.0, sizeof(long double) * (DATA_NUM * L_NUM));

    INVMAX = inversionParam.INVMAX;

    if (ProcessType::invert == vType)
    {
        m_forwardTimeProportion = 0.6f;

        if (INVMAX == 0)
        {
            INVMAX = 1;
        }
    }
    else
    {
        m_forwardTimeProportion = 1.0f;
        INVMAX                  = 1;
    }

    if (INV_NUM > INVMAX)
    {
        QLog("反演次数达到设定的上限\n");
        QLog("此时反演次数为%d,均方差为%f\n", INV_NUM, RES);
    }

    if (vType == ProcessType::simuforward)
    {
        QLog("计算目的:数值模拟正演\n");
        //模拟异常体,反演范围区域
        unsigned int inverX1, inverX2, inverY1, inverY2, inverZ1, inverZ2;
        GlobalParam::ForwardModelingParaSetting &setting = GlobalParam::instance()->getForwardModelingParaSetting();
        inverX1                                          = setting.inverX1;
        inverX2                                          = setting.inverX2;
        inverY1                                          = setting.inverY1;
        inverY2                                          = setting.inverY2;
        inverZ1                                          = setting.inverZ1;
        inverZ2                                          = setting.inverZ2;

        for (unsigned int k = inverZ1; k <= inverZ2; k++)
        {
            for (unsigned int j = inverY1; j <= inverY2; j++)
            {
                for (unsigned int i = inverX1; i <= inverX2; i++)
                {
                    //BoundU1(I, kk, j) = 1500
                    //Charg(I, kk, j) = 0.0
                    NRO[k][j][i] = 10.00;
                }
            }
        }

        doForwardProcess();
        for (unsigned int i = 0; i < DATA_NUM * L_NUM; i++)
        {
            DAT[i] = M_RESULT[i][3];
        }

        QLog("模拟正演结束");
        m_preOperationType = ProcessType::simuforward;
        emit creatSimuForwardResult();
		setForwardProcessSuccess(true);
    }
    else if (vType == ProcessType::forward)
    {
		QLog("数值正演开始");
        doForwardProcess();
        m_preOperationType = ProcessType::forward;
        emit creatForwardResult();
		QLog("数值正演结束");
		setForwardProcessSuccess(true);
    }
    else if (vType == ProcessType::invert)
    {
        INV_METHOD = (int)inversionParam.selectionSwitch;

        switch (inversionParam.selectionSwitch)
        {
        case GlobalParam::GA:
        {
            QLog("反演方法：GA反演");
            QLog("未实现");
        }
        break;
        case GlobalParam::antColony:
        {
            QLog("反演方法：蚁群反演");
            QLog("未实现");
        }
        break;
        case GlobalParam::united:
        {
            QLog("反演方法：联合反演");
            QLog("未实现");
        }
        break;
        case GlobalParam::leastSquare:
        {
            QLog("反演方法：光滑约束的最小二乘反演");
        }
        break;
        default:
            break;
        }

        DATA_WEIGHT = (int)inversionParam.dataWeighting;

        switch (inversionParam.dataWeighting)
        {
        case GlobalParam::linear:
            QLog("当前数据加权方式: 线性");
            break;
        case GlobalParam::index:
            QLog("当前数据加权方式: 指数");
            break;
        case GlobalParam::secondary:
            QLog("当前数据加权方式: 二次");
            break;
        case GlobalParam::noWeighting:
            QLog("当前数据加权方式: 无加权");
            break;
        default:
            break;
        }

        QLog("计算目的:数值反演\n");
        INV_NUM = 0;

        EPS     = inversionParam.EPS;
        EPS_RSM = inversionParam.EPSRMS;

        float everytimeProgressValue = (100.0f) / float(INVMAX) * (1.0f - m_increaseDensity);

		if (nullptr == delta_m)
		{
			delta_m = new long double[ner];
		}

		memset(delta_m, 0, sizeof(long double) * ner);

        do
        {
            if (INV_NUM >= INVMAX)
            {
                emit reselectCount();

                while (!m_isReselectDialogOver)
                {
                    msleep(10);
                }

                m_isReselectDialogOver = false;

                if (INV_NUM >= INVMAX)
                {
                    QLog("本次反演结束\n");
                    m_preOperationType = ProcessType::invert;
                    break;
                }

                m_currentProgress = (float)INV_NUM / (float)INVMAX * 100.0f * (1.0f - m_increaseDensity);
				everytimeProgressValue = (100.0f) / float(INVMAX) * (1.0f - m_increaseDensity);
                setProcessBarValue(m_currentProgress);
            }

            doForwardProcess();

            QLog("供电电流为:   %f", II);
            QLog("反演迭代次数上限为:   %d", INVMAX);
            QLog("反演迭代收敛容许公差为: %f", EPS);
            QLog("反演迭代收敛的相对拟合误差收敛判据为:  %f", EPS_RMS);
            QLog("利用JPCG法求解反演方程时的迭代次数上限: %d", (int)JPCG_ITMAX);
            QLog("利用JPCG法求解反演方程时的收敛容许公差:   %f", JPCG_RELERR);

            QLog("形成总体系数矩阵的一维非零元素压缩存储模式GA和GA1");
            QLog("'计算方程的右端向量：GA1*U0'");

			//检验反演是否收敛
            for (unsigned int i = 0; i < DATA_NUM * L_NUM; i++)
            {
                DELTA_D[i] = DAT[i] - M_RESULT[i][3];
            }

            RES = 0.0;
            RMS = 0.0;
            for (unsigned int i = 0; i < DATA_NUM * L_NUM; i++)
            {
                RES = RES + DELTA_D[i] * DELTA_D[i];
                if (fabs(DAT[i]) > 1e-15)
                    RMS = RMS + pow((DELTA_D[i] / DAT[i]), 2.0);
            }
            RES = sqrt(RES / (long double)(DATA_NUM * L_NUM)); //计算均方差
            RMS = sqrt(RMS / (long double)(DATA_NUM * L_NUM)); //计算相对拟合差

            //计算实测数据与理论数据的对数值的差向量，使反演计算更加稳定
            for (unsigned int i = 0; i < DATA_NUM * L_NUM; i++)
            {
                if (fabs(M_RESULT[i][3]) > 1e-15)
                    DELTA_D[i] = log((DAT[i] / M_RESULT[i][3]));
            }

            //下面判断均方差是否小于容许公差
            if (RES < EPS || RMS < EPS_RSM)
            {
                QLog("均方差或相对拟合差达到收敛判据，是否继续反演?");
                QLog("此时反演次数为:%d，均方差为:%f,拟合差为:%f\n", INV_NUM, RES, RMS);

                //TODO 需要弹出对话窗口控制决定
                //如果继续请输入1，再定义RES或RMS，如果终止反演请输入0
                if (FLAG == 0)
                {
                    QLog("反演结束\n"); //反演结束
                    break;
                }
                else if (FLAG == 1)
                {
                    QLog("请重新定义收敛判据RES和RMS\n");
                    //TODO : 录入 RES 和 RMS
                }
                m_preOperationType = ProcessType::invert;
            }

            QLog("敏感度矩阵开始求解");

            setProcessBarValue(m_currentProgress + (10.0f * (1.0f - m_forwardTimeProportion - m_increaseDensity) + 100.0f * m_forwardTimeProportion) / (float)INVMAX);

            //下面计算形成雅克比（敏感度）矩阵
            JA_generator(ner, Z1, Z2, X1, X2, Y1, Y2, ARRAY_TYPE);

            setProcessBarValue(m_currentProgress + (30.0f * (1.0f - m_forwardTimeProportion - m_increaseDensity) + 100.0f * m_forwardTimeProportion) / (float)INVMAX);

            QLog("敏感度矩阵求解完毕");

            //下面计算形成光滑度矩阵
            long double MIU = 0.005;

            if (NULL == W_A)
            {
                W_A = new long double[DATA_NUM * L_NUM]; //偏导数矩阵的权重
                for (int i = 0; i < DATA_NUM * L_NUM; i++)
                {
                    W_A[i] = 1.0;
                }
            }

            SM_TYPE = inversionParam.computingMethod; //从界面读入
            NUMOFSM = 0;
            //光滑度矩阵求解
            QLog("光滑度矩阵求解开始");
            SM_OPERATOR(ner, Z1, Z2, X1, X2, Y1, Y2, SM_TYPE);
            QLog("光滑度矩阵求解完毕");
            //光滑度矩阵求解完毕
            if (NULL == SHM)
            {
                SHM = new long double[14 * ner];
                memset(SHM, 0.0, sizeof(long double) * (14 * ner));
            }

            NUMOFSHM = 0;
            if (NULL == IDOFSHM)
            {
                IDOFSHM = new int *[14 * ner];
                for (unsigned int i = 0; i < 14 * ner; i++)
                {
                    IDOFSHM[i] = new int[4];
                    memset(IDOFSHM[i], 0, sizeof(int) * (4));
                }
            }

            QLog("形状约束矩阵求解开始");
            SHM_OP(ner, Z1, Z2, X1, X2, Y1, Y2, MIU, SHM, IDOFSHM);
            setProcessBarValue(m_currentProgress + (40.0f * (1.0f - m_forwardTimeProportion - m_increaseDensity) + 100.0f * m_forwardTimeProportion) / (float)INVMAX);
            QLog("形状约束矩阵求解完毕");

			////计算方程的右端项
			int IPATH1 = 1;
			int IPATH2 = 2;
			long double *diag1, *diag2, *diag3;
			diag1 = new long double[ner];
			memset(diag1, 0.0, sizeof(long double) * ner);
			diag2 = new long double[ner];
			memset(diag2, 0.0, sizeof(long double) * ner);
			diag3 = new long double[ner];
			memset(diag3, 0.0, sizeof(long double) * ner);

			for (int i = 0; i < m_ner; i ++)
			{
				for (int j = 0; j < DATA_NUM*L_NUM; j ++)
				{
					diag1[i] = diag1[i] + W_A[j] * JA[j][i] * W_A[j] * JA[j][i];
				}
			}

			//计算TRANS(SM)*SM的对角矩阵,下列的计算方法很巧妙的运用了一维压缩存储模式的特点
			for (unsigned int i = 0; i <= NUMOFSM; i++)
			{
				diag2[IDOFSM[i][1] - 1] = diag2[IDOFSM[i][1] - 1] + SM[i] * SM[i];
				//QLog("diag2 Index, Value: %d,%d,%lf\n", i, IDOFSM[i][1] - 1, diag2[IDOFSM[i][1] - 1]);
			}

			for (unsigned int i = 0; i < m_ner; i++)
			{
				diag3[i] = diag1[i] + diag2[i];
				//QLog("diag3 Index, Value: %d,%lf\n", i, diag3[i]);
			}
			
			for (int iii = 0; iii < DATA_NUM * L_NUM; iii++)
			{
				DELTA_D[iii] = DELTA_D[iii] * W_A[iii] * W_A[iii];
			}

			if (NULL == BINV)
			{
				BINV = new long double[ner];
				memset(BINV, 0, sizeof(long double) * ner);
			}

			if (NULL == PINV)
			{
				PINV = new long double[ner];
				memset(PINV, 0, sizeof(long double) * ner);
			}

			if (NULL == RINV)
			{
				RINV = new long double[ner];
				memset(RINV, 0, sizeof(long double) * ner);
			}

			if (NULL == ZZINV)
			{
				ZZINV = new long double[ner];
				memset(ZZINV, 0, sizeof(long double) * ner);
			}

			if (NULL == YINV1)
			{
				YINV1 = new long double[DATA_NUM];
				memset(YINV1, 0, sizeof(long double) * DATA_NUM);
			}

			if (NULL == ZZINV1)
			{
				ZZINV1 = new long double[ner];
				memset(ZZINV1, 0, sizeof(long double) * ner);
			}

			if (NULL == YINV2)
			{
				YINV2 = new long double[ner];
				memset(YINV2, 0, sizeof(long double) * ner);
			}

			if (NULL == ZZINV2)
			{
				ZZINV2 = new long double[ner];
				memset(ZZINV2, 0, sizeof(long double) * ner);
			}

			for (int zi = 0; zi < ner; zi++)
			{
				BINV[zi] = 0.0;
				PINV[zi] = 0.0;
				ZZINV1[zi] = 0.0;
				YINV2[zi] = 0.0;
				ZZINV2[zi] = 0.0;
				RINV[zi] = 0.0;
				ZZINV[zi] = 0.0;
			}

			for (int ii = 0; ii < DATA_NUM; ii ++)
			{
				YINV1[ii] = 0.0;
			}

			DMURRv1(DATA_NUM, ner, JA, DATA_NUM, DELTA_D, ner, BINV, IPATH2);
			
			int IDO = 0;
			int ITER_NUM = 0;

			JPCG_ITMAX = inversionParam.PCGITMAX;  //PCG法解方程时的迭代次数上限
			JPCG_RELERR = inversionParam.PCGRELERR; //PCG法解方程时的收敛容许误差
			JPCG_EPS = inversionParam.PCGEPS;

			BoundL = inversionParam.BoundL;
			BoundU = inversionParam.BoundU;

			//设置解向量U的初值为0，则初始R=B
			for (unsigned int i = 0; i < ner; i++)
			{
				RINV[i] = BINV[i];
				delta_m[i] = BINV[i];
				//QLog("BINV Index, Value: %d,%lf\n", i, BINV[i]);
			}

			QString jpcgString = "";
			
			do
			{
				m_funcDPCGRC(&IDO, &m_ner, delta_m, PINV, RINV, ZZINV, &JPCG_RELERR, &JPCG_ITMAX);
				ITER_NUM = ITER_NUM + 1;
				//QLog("PCG法求解电阻率反演方程的迭代次数 : %d\n", ITER_NUM);
				
				long double JPCG_RES = 0.0;
				for (int i = 0; i < m_ner; i ++)
				{
					JPCG_RES = JPCG_RES + RINV[i]* RINV[i];
				}
				JPCG_RES = sqrt(JPCG_RES);

				QString numStr = QString::number(JPCG_RES, 'f', 10);

				jpcgString += QString::fromUtf8("PCG收敛值 : ") + numStr + "\n";

				if (IDO == 1)
				{
					DMURRv1(DATA_NUM, ner, JA, ner, PINV, DATA_NUM, YINV1, IPATH1);
					for (int jj = 0; jj < DATA_NUM*L_NUM; jj ++)
					{
						YINV1[jj] = YINV1[jj] * W_A[jj] * W_A[jj];
					}
					DMURRv1(DATA_NUM, ner, JA, DATA_NUM, YINV1, ner, ZZINV1, IPATH2);
					//计算TRANS(SM)*SM*P   光滑约束项
					MultiplySM(ner, SM, PINV, YINV2, IDOFSM, NUMOFSM, IPATH1);
					MultiplySM(ner, SM, YINV2, ZZINV2, IDOFSM, NUMOFSM, IPATH2);

					for (int jj = 0; jj < ner; jj ++)
					{
						//这两行选择形状约束
						ZZINV[jj] = ZZINV1[jj] + ZZINV2[jj];
					}
				}
				else if (IDO == 2)
				{
					for (int ii = 0; ii < ner; ii ++)
					{
						ZZINV[ii] = RINV[ii]/diag3[ii];
					}
				}
				else if (IDO == 3)
				{
					break;
				}
			} while (true);

			QStrDPCGRC(jpcgString);

			/************下面是PCG法的自检验程序，也就是将计算结果代入原方程，看左端项与右端项是否一致**************/
			QLog("JPCG求解结果自检查开始\n");
			DMURRv1(DATA_NUM, ner, JA, ner, PINV, DATA_NUM, YINV1, IPATH1);
			DMURRv1(DATA_NUM, ner, JA, DATA_NUM, YINV1, ner, ZZINV1, IPATH2);

			//计算TRANS(SM)*SM*P
			MultiplySM(ner, SM, delta_m, YINV2, IDOFSM, NUMOFSM, IPATH1);
			MultiplySM(ner, SM, YINV2, ZZINV2, IDOFSM, NUMOFSM, IPATH2);

			for (int ii = 0; ii < ner; ii ++)
			{
				//将左端项的计算结果方法ZZINV数组
				ZZINV[ii] = ZZINV1[ii] + ZZINV2[ii];
			}
		
			bool PCG_FLAG2 = 1;
			for (int ii = 0; ii < ner; ii ++)
			{
				if (fabs(ZZINV[ii] - BINV[ii]) > 0.00001)
				{
					//QLog("第%d个数据存在异常:\n",ii);
					PCG_FLAG2 = 0;
				}
			}
			if (PCG_FLAG2 == 1)
			{
				QLog("反演方程求解结果满足要求");
			}
			else if (PCG_FLAG2 == 0)
			{
				QLog("反演方程求解结果不能满足要求");
			}
            
			BoundL = inversionParam.BoundL;
			BoundU = inversionParam.BoundU;
			setProcessBarValue(m_currentProgress + (80.0f * (1.0f - m_forwardTimeProportion - m_increaseDensity) + 100.0f * m_forwardTimeProportion) / (float)INVMAX);

            QLog("本次迭代得到的新的电阻率值模型参数如下:");
            QLog("IX   IY   IZ  网格电阻率值");

            QString logString = "";

            int I = -1;
            for (unsigned int IZ = Z1; IZ <= Z2; IZ++)
            {
                for (unsigned int IX = X1; IX <= X2; IX++)
                {
                    for (unsigned int IY = Y1; IY <= Y2; IY++)
                    {
                        I = I + 1;
                        //对数型计算方式
						long double nroTest = NRO[IZ][IY][IX];
						long double expValue = exp(delta_m[I]);
						long double nroResult = NRO[IZ][IY][IX] * exp(delta_m[I]);

                        NRO[IZ][IY][IX] = NRO[IZ][IY][IX] * exp(delta_m[I]);

                        if (NRO[IZ][IY][IX] - BoundU1[IZ][IY][IX] > 0.00000001)
                        {
                            NRO[IZ][IY][IX] = BoundU1[IZ][IY][IX] - 1.000;
                        }

                        if (10.0 - NRO[IZ][IY][IX] > 0.00000001)
                        {
                            NRO[IZ][IY][IX] = 10.0;
                        }

                        logString += QString("%1   %2   %3   %4\n").arg(IX).arg(IY).arg(IZ).arg(NRO[IZ][IY][IX]);
                        ///QLog("%d   %d   %d   %f\n", IX, IY, IZ, NRO[IZ][IY][IX]);
                    }
                }
            }

            QStrNRO(logString);

            //  setProcessBarValue(m_currentProgress + (100.0f * (1.0f - m_forwardTimeProportion - m_increaseDensity) + 100.0f * m_forwardTimeProportion) / (float)INVMAX);
            QLog("第%d反演迭代结束", INV_NUM + 1);

            //反演计数器工作
            INV_NUM = INV_NUM + 1;

            m_currentProgress += everytimeProgressValue;

            QLog("此时反演次数为:%d\n", INV_NUM);
            QLog("本次反演正演数据与实测数据的均方差为:%f\n", RES);
            QLog("本次反演正演数据与实测数据的拟合精度为:%f\n", RMS);

            setProcessBarValue(m_currentProgress);

            if (NULL != diag1)
            {
                delete[] diag1;
                diag1 = NULL;
            }

            if (NULL != diag2)
            {
                delete[] diag2;
                diag2 = NULL;
            }
        } while (true);

        if (NULL == m_resultPointArray)
            m_resultPointArray = new osg::Vec4dArray;
        else
            m_resultPointArray->clear();

        std::set<double> xPointValue; //x方向的分布值
        std::set<double> yPointValue; //y方向的分布值
        std::set<double> zPointValue; //z方向的分布值

        DataManager::instance()->setInversionNROData(NRO, X1, X2, Y1, Y2, Z1, Z2);

		QLog("正在进行反演数据结果的数据密度插值，请等待...");
        /***********************************此情况针对超前预报预测单元间隔为2的情况**************************************/
		for (unsigned int IZ = Z1; IZ <= Z2 + 1; IZ++)
		{
			float value = float(IZ - Z1) / float(Z2 - Z1) * 12.0f;
			setProcessBarValue((1.0f - m_increaseDensity) * 100.0f + value);
			for (unsigned int IY = Y1; IY <= Y2 + 1; IY++)
			{
				for (unsigned int IX = X1; IX <= X2 + 1; IX++)
				{
					unsigned int N = (IZ) * (NX + 1) * (NY + 1) + (IX) * (NY + 1) + IY;
					unsigned int startN = (Z1) * (NX + 1) * (NY + 1) + (X1) * (NY + 1) + Y1;

					long double xValue = (XY[N][0] - XY[startN][0]);
					long double yValue = (XY[startN][1] - XY[N][1]);
					long double zValue = (XY[N][2] - XY[startN][2]);

					if (IZ > Z1)
					{
						unsigned int NBefore = (IZ - 1) * (NX + 1) * (NY + 1) + (IX) * (NY + 1) + IY;
						long double zBeforeValue = (XY[NBefore][2] - XY[startN][2]);
						long double zMiddleIndex = (zBeforeValue + zValue) / 2;
						long double zMiddleValue = (NRO[IZ - 1][IY][IX] + NRO[IZ][IY][IX]) / 2;
						m_resultPointArray->push_back(osg::Vec4d(xValue, yValue, zMiddleIndex, zMiddleValue));
						zPointValue.insert(zMiddleIndex); //z方向的分布值
					}

					xPointValue.insert(xValue); //x方向的分布值
					yPointValue.insert(yValue); //y方向的分布值
					zPointValue.insert(zValue); //z方向的分布值
					m_resultPointArray->push_back(osg::Vec4d(xValue, yValue, zValue, NRO[IZ][IY][IX]));
				}
			}
		}

		osg::ref_ptr<osg::Vec4dArray> pTmpPointArray = new osg::Vec4dArray;
		for (unsigned int iz = 1; iz < 30; iz++)
		{
			float value = float(iz - 1) / float(30 - 1) * 18.0f;

			setProcessBarValue((1.0f - m_increaseDensity) * 100.0f + value);

			for (unsigned int iy = 1; iy < 30; iy++)
			{
				for (unsigned int ix = 1; ix < 30; ix++)
				{
					long double xLow = 0.0;
					long double xHigh = 0.0;
					long double yLow = 0.0;
					long double yHigh = 0.0;
					long double zLow = 0.0;
					long double zHigh = 0.0;

					std::set<double>::iterator itorXLow = xPointValue.begin();
					std::set<double>::iterator itorYLow = yPointValue.begin();
					std::set<double>::iterator itorZLow = zPointValue.begin();

					std::set<double>::iterator itorXHigh = xPointValue.begin();
					std::set<double>::iterator itorYHigh = yPointValue.begin();
					std::set<double>::iterator itorZHigh = zPointValue.begin();

					while ((*itorXHigh) < ix)
					{
						itorXHigh++;

						if (xPointValue.end() == itorXHigh)
						{
							itorXHigh--;
							break;
						}
					}
					itorXLow = itorXHigh;
					itorXLow--;

					while ((*itorYHigh) < iy)
					{
						itorYHigh++;

						if (yPointValue.end() == itorYHigh)
						{
							itorYHigh--;
							break;
						}
					}
					itorYLow = itorYHigh;
					itorYLow--;

					while ((*itorZHigh) < iz)
					{
						itorZHigh++;

						if (zPointValue.end() == itorZHigh)
						{
							itorZHigh--;
							break;
						}
					}
					itorZLow = itorZHigh;
					itorZLow--;

					long double xLyLzLValue = 0.0;
					long double xLyHzLValue = 0.0;
					long double xHyLzLValue = 0.0;
					long double xHyHzLValue = 0.0;
					long double xLyLzHValue = 0.0;
					long double xLyHzHValue = 0.0;
					long double xHyLzHValue = 0.0;
					long double xHyHzHValue = 0.0;

					xLow = (*itorXLow);
					xHigh = (*itorXHigh);
					yLow = (*itorYLow);
					yHigh = (*itorYHigh);
					zLow = (*itorZLow);
					zHigh = (*itorZHigh);

					for (unsigned int i = 0; i < m_resultPointArray->size(); i++)
					{
						if (fabs(xLow - (*m_resultPointArray)[i].x()) < 0.00001 && fabs(yLow - ((*m_resultPointArray)[i].y())) < 0.00001 && fabs(zLow - ((*m_resultPointArray)[i].z())) < 0.00001)
						{
							xLyLzLValue = (*m_resultPointArray)[i].w();
						}

						if (fabs(xLow - (*m_resultPointArray)[i].x()) < 0.00001 && fabs(yHigh - ((*m_resultPointArray)[i].y())) < 0.00001 && fabs(zLow - ((*m_resultPointArray)[i].z())) < 0.00001)
						{
							xLyHzLValue = (*m_resultPointArray)[i].w();
						}

						if (fabs(xHigh - (*m_resultPointArray)[i].x()) < 0.00001 && fabs(yLow - ((*m_resultPointArray)[i].y())) < 0.00001 && fabs(zLow - ((*m_resultPointArray)[i].z())) < 0.00001)
						{
							xHyLzLValue = (*m_resultPointArray)[i].w();
						}

						if (fabs(xHigh - (*m_resultPointArray)[i].x()) < 0.00001 && fabs(yHigh - ((*m_resultPointArray)[i].y())) < 0.00001 && fabs(zLow - ((*m_resultPointArray)[i].z())) < 0.00001)
						{
							xHyHzLValue = (*m_resultPointArray)[i].w();
						}

						if (fabs(xLow - (*m_resultPointArray)[i].x()) < 0.00001 && fabs(yLow - ((*m_resultPointArray)[i].y())) < 0.00001 && fabs(zHigh - ((*m_resultPointArray)[i].z())) < 0.00001)
						{
							xLyLzHValue = (*m_resultPointArray)[i].w();
						}

						if (fabs(xLow - (*m_resultPointArray)[i].x()) < 0.00001 && fabs(yHigh - ((*m_resultPointArray)[i].y())) < 0.00001 && fabs(zHigh - ((*m_resultPointArray)[i].z())) < 0.00001)
						{
							xLyHzHValue = (*m_resultPointArray)[i].w();
						}

						if (fabs(xHigh - (*m_resultPointArray)[i].x()) < 0.00001 && fabs(yLow - ((*m_resultPointArray)[i].y())) < 0.00001 && fabs(zHigh - ((*m_resultPointArray)[i].z())) < 0.00001)
						{
							xHyLzHValue = (*m_resultPointArray)[i].w();
						}

						if (fabs(xHigh - (*m_resultPointArray)[i].x()) < 0.00001 && fabs(yHigh - ((*m_resultPointArray)[i].y())) < 0.00001 && fabs(zHigh - ((*m_resultPointArray)[i].z())) < 0.00001)
						{
							xHyHzHValue = (*m_resultPointArray)[i].w();
						}
						if (xLyLzLValue > 0 && xLyHzLValue > 0 && xHyLzLValue > 0 && xHyHzLValue > 0 && xLyLzHValue > 0 && xLyHzHValue > 0 && xHyLzHValue > 0 && xHyHzHValue > 0)
						{
							break;
						}
					}
					//反距离加权法
					long double xLyLzLDis = 1000000.0;
					long double xLyHzLDis = 1000000.0;
					long double xHyLzLDis = 1000000.0;
					long double xHyHzLDis = 1000000.0;
					long double xLyLzHDis = 1000000.0;
					long double xLyHzHDis = 1000000.0;
					long double xHyLzHDis = 1000000.0;
					long double xHyHzHDis = 1000000.0;
					long double totalDisR = 0.0;

					if (sqrt(pow(ix - xLow, 2) + pow(iy - yLow, 2) + pow(iz - zLow, 2)) != 0)
					{
						xLyLzLDis = 1 / sqrt(pow(ix - xLow, 2) + pow(iy - yLow, 2) + pow(iz - zLow, 2));
						totalDisR += xLyLzLDis;
					}
					else
						totalDisR += xLyLzLDis;

					if (sqrt(pow(ix - xLow, 2) + pow(iy - yHigh, 2) + pow(iz - zLow, 2)) != 0)
					{
						xLyHzLDis = 1 / sqrt(pow(ix - xLow, 2) + pow(iy - yHigh, 2) + pow(iz - zLow, 2));
						totalDisR += xLyHzLDis;
					}
					else
						totalDisR += xLyHzLDis;

					if (sqrt(pow(ix - xHigh, 2) + pow(iy - yLow, 2) + pow(iz - zLow, 2)) != 0)
					{
						xHyLzLDis = 1 / sqrt(pow(ix - xHigh, 2) + pow(iy - yLow, 2) + pow(iz - zLow, 2));
						totalDisR += xHyLzLDis;
					}
					else
						totalDisR += xHyLzLDis;

					if (sqrt(pow(ix - xHigh, 2) + pow(iy - yHigh, 2) + pow(iz - zLow, 2)) != 0)
					{
						xHyHzLDis = 1 / sqrt(pow(ix - xHigh, 2) + pow(iy - yHigh, 2) + pow(iz - zLow, 2));
						totalDisR += xHyHzLDis;
					}
					else
						totalDisR += xHyHzLDis;

					if (sqrt(pow(ix - xLow, 2) + pow(iy - yLow, 2) + pow(iz - zHigh, 2)) != 0)
					{
						xLyLzHDis = 1 / sqrt(pow(ix - xLow, 2) + pow(iy - yLow, 2) + pow(iz - zHigh, 2));
						totalDisR += xLyLzHDis;
					}
					else
						totalDisR += xLyLzHDis;

					if (sqrt(pow(ix - xLow, 2) + pow(iy - yHigh, 2) + pow(iz - zHigh, 2)) != 0)
					{
						xLyHzHDis = 1 / sqrt(pow(ix - xLow, 2) + pow(iy - yHigh, 2) + pow(iz - zHigh, 2));
						totalDisR += xLyHzHDis;
					}
					else
						totalDisR += xLyHzHDis;

					if (sqrt(pow(ix - xHigh, 2) + pow(iy - yLow, 2) + pow(iz - zHigh, 2)) != 0)
					{
						xHyLzHDis = 1 / sqrt(pow(ix - xHigh, 2) + pow(iy - yLow, 2) + pow(iz - zHigh, 2));
						totalDisR += xHyLzHDis;
					}
					else
						totalDisR += xHyLzHDis;

					if (sqrt(pow(ix - xHigh, 2) + pow(iy - yHigh, 2) + pow(iz - zHigh, 2)) != 0)
					{
						xHyHzHDis = 1 / sqrt(pow(ix - xHigh, 2) + pow(iy - yHigh, 2) + pow(iz - zHigh, 2));
						totalDisR += xHyHzHDis;
					}
					else
						totalDisR += xHyHzHDis;

					long double resultValue = xLyLzLDis / totalDisR * xLyLzLValue + xLyHzLDis / totalDisR * xLyHzLValue +
						xHyLzLDis / totalDisR * xHyLzLValue + xHyHzLDis / totalDisR * xHyHzLValue + xLyLzHDis / totalDisR * xLyLzHValue + xLyHzHDis / totalDisR * xLyHzHValue + xHyLzHDis / totalDisR * xHyLzHValue + xHyHzHDis / totalDisR * xHyHzHValue;
					pTmpPointArray->push_back(osg::Vec4d(ix, iy, iz, resultValue));
				}
			}
		}

        float invertX = GlobalParam::instance()->getModeling().inversionAreaRangeX;
        float invertY = GlobalParam::instance()->getModeling().inversionAreaRangeY;
        float invertZ = GlobalParam::instance()->getModeling().forecastLength;
        DataManager::instance()->setInversionData(pTmpPointArray, invertX, invertY, invertZ);
        emit onInvertCompleted();
        emit creatInversionResult();
		QLog("正在进行反演数据结果的数据密度插值完成.");
    }
	
    setProcessBarValue(100);
    m_currentProgress = 0.0f;

    //     if (!LogSystem::instance()->getProgressBar()->isHidden())
    //     {
    //         LogSystem::instance()->getProgressBar()->hide();
    //     }

    // 	if (!m_progressBar->isHidden())
    // 	{
    // 		m_progressBar->hide();
    // 	}
}

/**********************************************************************************************************/
//function:自动化正演
void ForwardAndInverseProcess::autoGenForward()
{
    if (NULL == m_pModelSubdivison)
        return;

    if (m_firstInitData == false)
        return;

    m_currentOperationType = ProcessType::auto_gen_forward;
    //进度条的初始化

    unsigned int X1 = m_pModelSubdivison->getInvertionXBeg();
    unsigned int X2 = m_pModelSubdivison->getInvertionXEnd();
    unsigned int Y1 = m_pModelSubdivison->getInvertionYBeg();
    unsigned int Y2 = m_pModelSubdivison->getInvertionYEnd();
    unsigned int Z1 = m_pModelSubdivison->getTunnelForZBeg();
    unsigned int Z2 = m_pModelSubdivison->getTunnelForZEnd();

    unsigned int ner = (X2 - X1 + 1) * (Y2 - Y1 + 1) * (Z2 - Z1 + 1);

    QLog("自动化正演流程开始:\n");

    GlobalParam::InversionMethodSelection inverSwitch;
    if (inverSwitch == GlobalParam::InversionMethodSelection::GA)
    {
        QLog("待定\n");
    }

    unsigned int INV_NUM = 0;

    if (NULL == DAT)
    {
        DAT = new long double[DATA_NUM * L_NUM]; // !用于存储理论数据与实际数据的差向量
        memset(DAT, 0.0, sizeof(long double) * (DATA_NUM * L_NUM));
    }
    long double RES, RMS, EPS_RMS; //计算实测值与理论值之间的均方差，相对拟合差以及相对拟合差的收敛判据

    //下面判断反演次数是否达到上限，若达到上限是继续还是终止？
    GlobalParam::InversionParaSetting &inversionParam = GlobalParam::instance()->getInversionParaSetting();
    INVMAX                                            = inversionParam.INVMAX;
    unsigned int FLAG                                 = 0;

    //下面定义各单元的电阻率值
    for (unsigned int i = 0; i < NZ; i++)
    {
        for (unsigned int j = 0; j < NY; j++)
        {
            for (unsigned int k = 0; k < NX; k++)
            {
                BoundU1[i][j][k] = 1550;
                NRO[i][j][k]     = 1000.0;
            }
        }
    }

    //以下定义隧道空腔
    unsigned int xCavityBeg = m_pModelSubdivison->getTunnelCavityXBegin();
    unsigned int xCavityEnd = m_pModelSubdivison->getTunnelCavityXEnd();
    unsigned int yCavityBeg = m_pModelSubdivison->getTunnelCavityYBegin();
    unsigned int yCavityEnd = m_pModelSubdivison->getTunnelCavityYEnd();

    for (unsigned int k = 0; k < Z1; k++)
    {
        for (unsigned int j = yCavityBeg; j <= yCavityEnd; j++)
        {
            for (unsigned int i = xCavityBeg; i <= xCavityEnd; i++)
            {
                NRO[k][j][i] = 10000000.00;
            }
        }
    }

    //建立模型，形成节点坐标，单元编号、节点编号等
    int **tmpI4    = m_pModelSubdivison->getTotalGridIndex();
    double **tmpXY = m_pModelSubdivison->getTotalNodePos();
    for (unsigned int i = 0; i < NE; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            I4[i][j] = tmpI4[i][j];
        }
    }

    for (unsigned int i = 0; i < ND; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            XY[i][j] = tmpXY[i][j];
        }
    }

    setProcessBarValue(0);

    long double *DELTA_D = new long double[DATA_NUM * L_NUM]; // !用于存储理论数据与实际数据的差向量
    memset(DELTA_D, 0.0, sizeof(long double) * (DATA_NUM * L_NUM));

    INVMAX = inversionParam.INVMAX;

    m_forwardTimeProportion = 1.0f;
    INVMAX                  = 1;

    doForwardProcess();

    m_currentOperationType = ProcessType::auto_gen_invert;
    m_preOperationType     = ProcessType::auto_gen_forward;

    setProcessBarValue(100);
    m_currentProgress = 0.0f;
	setForwardProcessSuccess(true);
    //     if (!LogSystem::instance()->getProgressBar()->isHidden())
    //     {
    //         LogSystem::instance()->getProgressBar()->hide();
    //     }

    emit autoGenForwardProcessFinished(true);
}

/**********************************************************************************************************/
//function:自动化反演
void ForwardAndInverseProcess::autoGenInversion()
{
    if (NULL == m_pModelSubdivison)
        return;

    if (m_firstInitData == false)
        return;

    m_currentOperationType = ProcessType::invert;

    //进度条的初始化
    //initProcessBar();

    unsigned int X1 = m_pModelSubdivison->getInvertionXBeg();
    unsigned int X2 = m_pModelSubdivison->getInvertionXEnd();
    unsigned int Y1 = m_pModelSubdivison->getInvertionYBeg();
    unsigned int Y2 = m_pModelSubdivison->getInvertionYEnd();
    unsigned int Z1 = m_pModelSubdivison->getTunnelForZBeg();
    unsigned int Z2 = m_pModelSubdivison->getTunnelForZEnd();

    unsigned int ner = (X2 - X1 + 1) * (Y2 - Y1 + 1) * (Z2 - Z1 + 1);

    QLog("自动化反演流程开始:\n");

    GlobalParam::InversionMethodSelection inverSwitch;
    if (inverSwitch == GlobalParam::InversionMethodSelection::GA)
    {
        QLog("待定\n");
    }

    unsigned int INV_NUM = 0;

    if (NULL == DAT)
    {
        DAT = new long double[DATA_NUM * L_NUM]; // !用于存储理论数据与实际数据的差向量
        memset(DAT, 0.0, sizeof(long double) * (DATA_NUM * L_NUM));
    }
    long double RES, RMS, EPS_RMS; //计算实测值与理论值之间的均方差，相对拟合差以及相对拟合差的收敛判据

    //下面判断反演次数是否达到上限，若达到上限是继续还是终止？
    GlobalParam::InversionParaSetting &inversionParam = GlobalParam::instance()->getInversionParaSetting();

    INV_METHOD  = (int)inversionParam.selectionSwitch;
    DATA_WEIGHT = (int)inversionParam.dataWeighting;

    switch (inversionParam.dataWeighting)
    {
    case GlobalParam::linear:
        QLog("当前数据加权方式: 线性");
        break;
    case GlobalParam::index:
        QLog("当前数据加权方式: 指数");
        break;
    case GlobalParam::secondary:
        QLog("当前数据加权方式: 二次");
        break;
    case GlobalParam::noWeighting:
        QLog("当前数据加权方式: 无加权");
        break;
    default:
        break;
    }

    switch (inversionParam.selectionSwitch)
    {
    case GlobalParam::GA:
    {
        QLog("反演方法：GA反演");
        QLog("未实现");
    }
    break;
    case GlobalParam::antColony:
    {
        QLog("反演方法：蚁群反演");
        QLog("未实现");
    }
    break;
    case GlobalParam::united:
    {
        QLog("反演方法：联合反演");
        QLog("未实现");
    }
    break;
    case GlobalParam::leastSquare:
    {
        QLog("反演方法：光滑约束的最小二乘反演");
    }
    break;
    default:
        break;
    }

    INVMAX            = inversionParam.INVMAX;
    unsigned int FLAG = 0;

    //下面定义各单元的电阻率值
    for (unsigned int i = 0; i < NZ; i++)
    {
        for (unsigned int j = 0; j < NY; j++)
        {
            for (unsigned int k = 0; k < NX; k++)
            {
                BoundU1[i][j][k] = 1550;
                NRO[i][j][k]     = 1000.0;
            }
        }
    }

    //以下定义隧道空腔
    unsigned int xCavityBeg = m_pModelSubdivison->getTunnelCavityXBegin();
    unsigned int xCavityEnd = m_pModelSubdivison->getTunnelCavityXEnd();
    unsigned int yCavityBeg = m_pModelSubdivison->getTunnelCavityYBegin();
    unsigned int yCavityEnd = m_pModelSubdivison->getTunnelCavityYEnd();

    for (unsigned int k = 0; k < Z1; k++)
    {
        for (unsigned int j = yCavityBeg; j <= yCavityEnd; j++)
        {
            for (unsigned int i = xCavityBeg; i <= xCavityEnd; i++)
            {
                NRO[k][j][i] = 10000000.00;
            }
        }
    }

    //建立模型，形成节点坐标，单元编号、节点编号等
    int **tmpI4    = m_pModelSubdivison->getTotalGridIndex();
    double **tmpXY = m_pModelSubdivison->getTotalNodePos();
    for (unsigned int i = 0; i < NE; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            I4[i][j] = tmpI4[i][j];
        }
    }

    for (unsigned int i = 0; i < ND; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            XY[i][j] = tmpXY[i][j];
        }
    }

    if (ProcessType::invert == m_currentOperationType)
    {
        setProcessBarValue(0);
    }
    else
    {
        setProcessBarValue(0);
    }

    long double *DELTA_D = new long double[DATA_NUM * L_NUM]; // !用于存储理论数据与实际数据的差向量
    memset(DELTA_D, 0.0, sizeof(long double) * (DATA_NUM * L_NUM));

    INVMAX = inversionParam.INVMAX;

    m_forwardTimeProportion = 0.6f;
    m_increaseDensity       = 0.3f;

    if (INVMAX == 0)
    {
        INVMAX = 1;
    }

    if (INV_NUM > INVMAX)
    {
        QLog("反演次数达到设定的上限\n");
        QLog("此时反演次数为%d,均方差为%f\n", INV_NUM, RES);
    }

    {
        QLog("计算目的:数值反演\n");
        INV_NUM = 0;

        EPS     = inversionParam.EPS;
        EPS_RSM = inversionParam.EPSRMS;

        float everytimeProgressValue = (100.0f) / float(INVMAX) * (1.0f - m_increaseDensity);

        if (NULL == DELTA_D)
        {
            DELTA_D = new long double[DATA_NUM * L_NUM]; // !用于存储理论数据与实际数据的差向量
            memset(DELTA_D, 0.0, sizeof(long double) * (DATA_NUM * L_NUM));
        }

		long double *delta_m = new long double[ner];
		memset(delta_m, 0, sizeof(long double) * ner);
		
        do
        {
            if (INV_NUM >= INVMAX)
            {
                //TODO 重新录入反演迭代次数
                //FLAG为
                if (FLAG == 0)
                {
                    QLog("本次反演结束\n");
                    break;
                }
                else if (FLAG > 0)
                {
                    INVMAX += FLAG;
                }
            }

            doForwardProcess();

            //检验反演是否收敛
            for (unsigned int i = 0; i < DATA_NUM * L_NUM; i++)
            {
                DELTA_D[i] = DAT[i] - M_RESULT[i][3];
            }

            RES = 0.0;
            RMS = 0.0;
            for (unsigned int i = 0; i < DATA_NUM * L_NUM; i++)
            {
                RES = RES + DELTA_D[i] * DELTA_D[i];
                if (fabs(DAT[i]) > 1e-15)
                    RMS = RMS + pow((DELTA_D[i] / DAT[i]), 2.0);
            }
            RES = sqrt(RES / (long double)(DATA_NUM * L_NUM)); //计算均方差
            RMS = sqrt(RMS / (long double)(DATA_NUM * L_NUM)); //计算相对拟合差

            //计算实测数据与理论数据的对数值的差向量，使反演计算更加稳定
            for (unsigned int i = 0; i < DATA_NUM * L_NUM; i++)
            {
                if (fabs(M_RESULT[i][3]) > 1e-15)
                    DELTA_D[i] = log((DAT[i] / M_RESULT[i][3]));
            }

            //下面判断均方差是否小于容许公差
            if (RES < EPS || RMS < EPS_RSM)
            {
                QLog("均方差或相对拟合差达到收敛判据，是否继续反演?");
                QLog("此时反演次数为:%d，均方差为:%f,拟合差为:%f\n", INV_NUM, RES, RMS);

                //TODO 需要弹出对话窗口控制决定
                //如果继续请输入1，再定义RES或RMS，如果终止反演请输入0
                if (FLAG == 0)
                {
                    QLog("反演结束\n"); //反演结束
                    break;
                }
                else if (FLAG == 1)
                {
                    QLog("请重新定义收敛判据RES和RMS\n");
                    //TODO : 录入 RES 和 RMS
                }
            }

            QLog("敏感度矩阵开始求解");

            setProcessBarValue(m_currentProgress + (10.0f * (1.0f - m_forwardTimeProportion) + 100.0f * m_forwardTimeProportion) / (float)INVMAX);

            //下面计算形成雅克比（敏感度）矩阵
            JA_generator(ner, Z1, Z2, X1, X2, Y1, Y2, ARRAY_TYPE);

            setProcessBarValue(m_currentProgress + (30.0f * (1.0f - m_forwardTimeProportion) + 100.0f * m_forwardTimeProportion) / (float)INVMAX);

            QLog("敏感度矩阵求解完毕");

            //下面计算形成光滑度矩阵
            long double MIU = 0.005;

            //LAMDA = (1 / ((IZ - Z1 + 1) + 1.0) + 0.1) / 2;
            long double M_lamda = 0.01;
            long double lamda_x = 0.05;
            long double lamda_y = 0.05;
            long double lamda_z = 0.05;

            if (NULL == W_A)
            {
                W_A = new long double[DATA_NUM * L_NUM]; //偏导数矩阵的权重
                for (int i = 0; i < DATA_NUM * L_NUM; i++)
                {
                    W_A[i] = 1.0;
                }
            }

            SM_TYPE = inversionParam.computingMethod; //从界面读入
            NUMOFSM = 0;
            //光滑度矩阵求解
            QLog("光滑度矩阵求解开始");
            SM_OPERATOR(ner, Z1, Z2, X1, X2, Y1, Y2, SM_TYPE);
            QLog("光滑度矩阵求解完毕");
            //光滑度矩阵求解完毕
            if (NULL == SHM)
            {
                SHM = new long double[14 * ner];
                memset(SHM, 0.0, sizeof(long double) * (14 * ner));
            }

            NUMOFSHM = 0;
            if (NULL == IDOFSHM)
            {
                IDOFSHM = new int *[14 * ner];
                for (unsigned int i = 0; i < 14 * ner; i++)
                {
                    IDOFSHM[i] = new int[4];
                    memset(IDOFSHM[i], 0, sizeof(int) * (4));
                }
            }

            QLog("形状约束矩阵求解开始");
            SHM_OP(ner, Z1, Z2, X1, X2, Y1, Y2, MIU, SHM, IDOFSHM);
            setProcessBarValue(m_currentProgress + (40.0f * (1.0f - m_forwardTimeProportion) + 100.0f * m_forwardTimeProportion) / (float)INVMAX);
            QLog("形状约束矩阵求解完毕");

			////计算方程的右端项
			int IPATH1 = 1;
			int IPATH2 = 2;
			long double *diag1, *diag2, *diag3;
			diag1 = new long double[ner];
			memset(diag1, 0.0, sizeof(long double) * ner);
			diag2 = new long double[ner];
			memset(diag2, 0.0, sizeof(long double) * ner);
			diag3 = new long double[ner];
			memset(diag3, 0.0, sizeof(long double) * ner);

			for (int i = 0; i < m_ner; i++)
			{
				for (int j = 0; j < DATA_NUM*L_NUM; j++)
				{
					diag1[i] = diag1[i] + W_A[j] * JA[j][i] * W_A[j] * JA[j][i];
				}
			}

			//计算TRANS(SM)*SM的对角矩阵,下列的计算方法很巧妙的运用了一维压缩存储模式的特点
			for (unsigned int i = 0; i <= NUMOFSM; i++)
			{
				diag2[IDOFSM[i][1] - 1] = diag2[IDOFSM[i][1] - 1] + SM[i] * SM[i];
				//QLog("diag2 Index, Value: %d,%d,%lf\n", i, IDOFSM[i][1] - 1, diag2[IDOFSM[i][1] - 1]);
			}

			for (unsigned int i = 0; i < m_ner; i++)
			{
				diag3[i] = diag1[i] + diag2[i];
				//QLog("diag3 Index, Value: %d,%lf\n", i, diag3[i]);
			}

			for (int iii = 0; iii < DATA_NUM * L_NUM; iii++)
			{
				DELTA_D[iii] = DELTA_D[iii] * W_A[iii] * W_A[iii];
			}

			if (NULL == BINV)
			{
				BINV = new long double[ner];
				memset(BINV, 0, sizeof(long double) * ner);
			}

			if (NULL == PINV)
			{
				PINV = new long double[ner];
				memset(PINV, 0, sizeof(long double) * ner);
			}

			if (NULL == RINV)
			{
				RINV = new long double[ner];
				memset(RINV, 0, sizeof(long double) * ner);
			}

			if (NULL == ZZINV)
			{
				ZZINV = new long double[ner];
				memset(ZZINV, 0, sizeof(long double) * ner);
			}

			if (NULL == YINV1)
			{
				YINV1 = new long double[DATA_NUM];
				memset(YINV1, 0, sizeof(long double) * DATA_NUM);
			}

			if (NULL == ZZINV1)
			{
				ZZINV1 = new long double[ner];
				memset(ZZINV1, 0, sizeof(long double) * ner);
			}

			if (NULL == YINV2)
			{
				YINV2 = new long double[ner];
				memset(YINV2, 0, sizeof(long double) * ner);
			}

			if (NULL == ZZINV2)
			{
				ZZINV2 = new long double[ner];
				memset(ZZINV2, 0, sizeof(long double) * ner);
			}

			for (int zi = 0; zi < ner; zi++)
			{
				BINV[zi] = 0.0;
				PINV[zi] = 0.0;
				ZZINV1[zi] = 0.0;
				YINV2[zi] = 0.0;
				ZZINV2[zi] = 0.0;
				RINV[zi] = 0.0;
				ZZINV[zi] = 0.0;
			}

			for (int ii = 0; ii < DATA_NUM; ii++)
			{
				YINV1[ii] = 0.0;
			}

			DMURRv1(DATA_NUM, ner, JA, DATA_NUM, DELTA_D, ner, BINV, IPATH2);

			int IDO = 0;
			int ITER_NUM = 0;

			JPCG_ITMAX = inversionParam.PCGITMAX;  //PCG法解方程时的迭代次数上限
			JPCG_RELERR = inversionParam.PCGRELERR; //PCG法解方程时的收敛容许误差
			JPCG_EPS = inversionParam.PCGEPS;

			BoundL = inversionParam.BoundL;
			BoundU = inversionParam.BoundU;

			//设置解向量U的初值为0，则初始R=B
			for (unsigned int i = 0; i < ner; i++)
			{
				RINV[i] = BINV[i];
				delta_m[i] = BINV[i];
				//QLog("BINV Index, Value: %d,%lf\n", i, BINV[i]);
			}

			QString jpcgString = "";

			do
			{
				m_funcDPCGRC(&IDO, &m_ner, delta_m, PINV, RINV, ZZINV, &JPCG_RELERR, &JPCG_ITMAX);
				ITER_NUM = ITER_NUM + 1;
				//QLog("PCG法求解电阻率反演方程的迭代次数 : %d\n", ITER_NUM);

				long double JPCG_RES = 0.0;
				for (int i = 0; i < m_ner; i++)
				{
					JPCG_RES = JPCG_RES + RINV[i] * RINV[i];
				}
				JPCG_RES = sqrt(JPCG_RES);

				QString numStr = QString::number(JPCG_RES, 'f', 10);

				jpcgString += QString::fromUtf8("PCG收敛值 : ") + numStr + "\n";

				if (IDO == 1)
				{
					DMURRv1(DATA_NUM, ner, JA, ner, PINV, DATA_NUM, YINV1, IPATH1);
					/*for (int jj = 0; jj < DATA_NUM*L_NUM; jj ++)
					{
					YINV1[jj] = YINV1[jj] * W_A[jj] * W_A[jj];
					}*/
					DMURRv1(DATA_NUM, ner, JA, DATA_NUM, YINV1, ner, ZZINV1, IPATH2);
					//计算TRANS(SM)*SM*P   光滑约束项
					MultiplySM(ner, SM, PINV, YINV2, IDOFSM, NUMOFSM, IPATH1);
					MultiplySM(ner, SM, YINV2, ZZINV2, IDOFSM, NUMOFSM, IPATH2);

					for (int jj = 0; jj < ner; jj++)
					{
						//这两行选择形状约束
						ZZINV[jj] = ZZINV1[jj] + ZZINV2[jj];
					}
				}
				else if (IDO == 2)
				{
					for (int ii = 0; ii < ner; ii++)
					{
						ZZINV[ii] = RINV[ii] / diag3[ii];
					}
				}
				else if (IDO == 3)
				{
					break;
				}
			} while (true);

			QStrDPCGRC(jpcgString);

			/************下面是PCG法的自检验程序，也就是将计算结果代入原方程，看左端项与右端项是否一致**************/
			QLog("JPCG求解结果自检查开始\n");
			DMURRv1(DATA_NUM, ner, JA, ner, PINV, DATA_NUM, YINV1, IPATH1);
			DMURRv1(DATA_NUM, ner, JA, DATA_NUM, YINV1, ner, ZZINV1, IPATH2);

			//计算TRANS(SM)*SM*P
			MultiplySM(ner, SM, delta_m, YINV2, IDOFSM, NUMOFSM, IPATH1);
			MultiplySM(ner, SM, YINV2, ZZINV2, IDOFSM, NUMOFSM, IPATH2);

			for (int ii = 0; ii < ner; ii++)
			{
				//将左端项的计算结果方法ZZINV数组
				ZZINV[ii] = ZZINV1[ii] + ZZINV2[ii];
			}

			bool PCG_FLAG2 = 1;
			for (int ii = 0; ii < ner; ii++)
			{
				if (fabs(ZZINV[ii] - BINV[ii]) > 0.00001)
				{
					//QLog("第%d个数据存在异常:\n",ii);
					//QLog("分别为%f,%f:\n",ZZINV[ii], BINV[ii]);
					PCG_FLAG2 = 0;
				}
			}
			if (PCG_FLAG2 == 1)
			{
				QLog("反演方程求解结果满足要求");
			}
			else if (PCG_FLAG2 == 0)
			{
				QLog("反演方程求解结果不能满足要求");
			}

			BoundL = inversionParam.BoundL;
			BoundU = inversionParam.BoundU;
            setProcessBarValue(m_currentProgress + (80.0f * (1.0f - m_forwardTimeProportion) + 100.0f * m_forwardTimeProportion) / (float)INVMAX);

            QLog("本次迭代得到的新的电阻率值模型参数如下:");
            QLog("IX   IY   IZ  网格电阻率值");

            int I = -1;
            for (unsigned int IZ = Z1; IZ <= Z2; IZ++)
            {
                for (unsigned int IX = X1; IX <= X2; IX++)
                {
                    for (unsigned int IY = Y1; IY <= Y2; IY++)
                    {
                        I = I + 1;
                        //对数型计算方式
                        NRO[IZ][IY][IX] = NRO[IZ][IY][IX] * exp(delta_m[I]);

                        if (NRO[IZ][IY][IX] - BoundU1[IZ][IY][IX] > 0.00000001)
                        {
                            NRO[IZ][IY][IX] = BoundU1[IZ][IY][IX] - 1.000;
                        }

                        if (10.0 - NRO[IZ][IY][IX] > 0.00000001)
                        {
                            NRO[IZ][IY][IX] = 10.0;
                        }
                    }
                }
            }
            setProcessBarValue(m_currentProgress + (100.0f * (1.0f - m_forwardTimeProportion) + 100.0f * m_forwardTimeProportion) / (float)INVMAX);
            QLog("第%d反演迭代结束", INV_NUM + 1);

            //反演计数器工作
            INV_NUM = INV_NUM + 1;

            m_currentProgress += everytimeProgressValue;

            //显示或记录计算过程
            QLog("此时反演次数为:%d\n", INV_NUM);
            QLog("本次反演正演数据与实测数据的均方差为:%f", RES);
            QLog("本次反演正演数据与实测数据的拟合精度为:%f", RMS);

            setProcessBarValue(m_currentProgress);
        } while (true);

        if (NULL == m_resultPointArray)
            m_resultPointArray = new osg::Vec4dArray;

        std::set<long double> xPointValue; //x方向的分布值
        std::set<long double> yPointValue; //y方向的分布值
        std::set<long double> zPointValue; //z方向的分布值

        DataManager::instance()->setInversionNROData(NRO, X1, X2, Y1, Y2, Z1, Z2);

        for (unsigned int IZ = Z1; IZ <= Z2 + 1; IZ++)
        {
            for (unsigned int IX = X1; IX <= X2 + 1; IX++)
            {
                for (unsigned int IY = Y1; IY <= Y2 + 1; IY++)
                {
                    unsigned int N      = (IZ) * (NX + 1) * (NY + 1) + (IX) * (NY + 1) + IY;
                    unsigned int startN = (Z1) * (NX + 1) * (NY + 1) + (X1) * (NY + 1) + Y1;

                    long double xValue = (XY[N][0] - XY[startN][0]);
                    long double yValue = (XY[startN][1] - XY[N][1]);
                    long double zValue = (XY[N][2] - XY[startN][2]);

                    if (IZ > Z1)
                    {
                        unsigned int NBefore = (IZ - 1) * (NX + 1) * (NY + 1) + (IX) * (NY + 1) + IY;
                        long double zBeforeValue  = (XY[NBefore][2] - XY[startN][2]);
                        long double zMiddleIndex  = (zBeforeValue + zValue) / 2;
                        long double zMiddleValue = (NRO[IZ - 1][IY][IX] + NRO[IZ][IY][IX]) / 2;
                        m_resultPointArray->push_back(osg::Vec4d(xValue, yValue, zMiddleIndex, zMiddleValue));
                        zPointValue.insert(zMiddleIndex); //z方向的分布值
                    }

                    xPointValue.insert(xValue); //x方向的分布值
                    yPointValue.insert(yValue); //y方向的分布值
                    zPointValue.insert(zValue); //z方向的分布值

                    m_resultPointArray->push_back(osg::Vec4d(xValue, yValue, zValue, NRO[IZ][IY][IX]));
                }
            }
        }

        osg::ref_ptr<osg::Vec4dArray> pTmpPointArray = new osg::Vec4dArray;
        for (unsigned int iz = 1; iz < 30; iz++)
        {
            for (unsigned int iy = 1; iy < 30; iy++)
            {
                for (unsigned int ix = 1; ix < 30; ix++)
                {
                    long double xLow  = 0.0;
                    long double xHigh = 0.0;
                    long double yLow  = 0.0;
                    long double yHigh = 0.0;
                    long double zLow  = 0.0;
                    long double zHigh = 0.0;

                    std::set<long double>::iterator itorXLow = xPointValue.begin();
                    std::set<long double>::iterator itorYLow = yPointValue.begin();
                    std::set<long double>::iterator itorZLow = zPointValue.begin();

                    std::set<long double>::iterator itorXHigh = xPointValue.begin();
                    std::set<long double>::iterator itorYHigh = yPointValue.begin();
                    std::set<long double>::iterator itorZHigh = zPointValue.begin();

                    while ((*itorXHigh) < ix)
                    {
                        itorXHigh++;
                    }
                    itorXLow = itorXHigh;
                    itorXLow--;

                    while ((*itorYHigh) < iy)
                    {
                        itorYHigh++;
                    }
                    itorYLow = itorYHigh;
                    itorYLow--;

                    while ((*itorZHigh) < iz)
                    {
                        itorZHigh++;
                    }
                    itorZLow = itorZHigh;
                    itorZLow--;

                    long double xLyLzLValue = 0.0;
                    long double xLyHzLValue = 0.0;
                    long double xHyLzLValue = 0.0;
                    long double xHyHzLValue = 0.0;
                    long double xLyLzHValue = 0.0;
                    long double xLyHzHValue = 0.0;
                    long double xHyLzHValue = 0.0;
                    long double xHyHzHValue = 0.0;

                    xLow  = (*itorXLow);
                    xHigh = (*itorXHigh);
                    yLow  = (*itorYLow);
                    yHigh = (*itorYHigh);
                    zLow  = (*itorZLow);
                    zHigh = (*itorZHigh);

                    for (unsigned int i = 0; i < m_resultPointArray->size(); i++)
                    {
                        if (fabs(xLow - (*m_resultPointArray)[i].x()) < 0.00001 && fabs(yLow - ((*m_resultPointArray)[i].y())) < 0.00001 && fabs(zLow - ((*m_resultPointArray)[i].z())) < 0.00001)
                        {
                            xLyLzLValue = (*m_resultPointArray)[i].w();
                        }

                        if (fabs(xLow - (*m_resultPointArray)[i].x()) < 0.00001 && fabs(yHigh - ((*m_resultPointArray)[i].y())) < 0.00001 && fabs(zLow - ((*m_resultPointArray)[i].z())) < 0.00001)
                        {
                            xLyHzLValue = (*m_resultPointArray)[i].w();
                        }

                        if (fabs(xHigh - (*m_resultPointArray)[i].x()) < 0.00001 && fabs(yLow - ((*m_resultPointArray)[i].y())) < 0.00001 && fabs(zLow - ((*m_resultPointArray)[i].z())) < 0.00001)
                        {
                            xHyLzLValue = (*m_resultPointArray)[i].w();
                        }

                        if (fabs(xHigh - (*m_resultPointArray)[i].x()) < 0.00001 && fabs(yHigh - ((*m_resultPointArray)[i].y())) < 0.00001 && fabs(zLow - ((*m_resultPointArray)[i].z())) < 0.00001)
                        {
                            xHyHzLValue = (*m_resultPointArray)[i].w();
                        }

                        if (fabs(xLow - (*m_resultPointArray)[i].x()) < 0.00001 && fabs(yLow - ((*m_resultPointArray)[i].y())) < 0.00001 && fabs(zHigh - ((*m_resultPointArray)[i].z())) < 0.00001)
                        {
                            xLyLzHValue = (*m_resultPointArray)[i].w();
                        }

                        if (fabs(xLow - (*m_resultPointArray)[i].x()) < 0.00001 && fabs(yHigh - ((*m_resultPointArray)[i].y())) < 0.00001 && fabs(zHigh - ((*m_resultPointArray)[i].z())) < 0.00001)
                        {
                            xLyHzHValue = (*m_resultPointArray)[i].w();
                        }

                        if (fabs(xHigh - (*m_resultPointArray)[i].x()) < 0.00001 && fabs(yLow - ((*m_resultPointArray)[i].y())) < 0.00001 && fabs(zHigh - ((*m_resultPointArray)[i].z())) < 0.00001)
                        {
                            xHyLzHValue = (*m_resultPointArray)[i].w();
                        }

                        if (fabs(xHigh - (*m_resultPointArray)[i].x()) < 0.00001 && fabs(yHigh - ((*m_resultPointArray)[i].y())) < 0.00001 && fabs(zHigh - ((*m_resultPointArray)[i].z())) < 0.00001)
                        {
                            xHyHzHValue = (*m_resultPointArray)[i].w();
                        }
                    }
                    //反距离加权法
                    long double xLyLzLDis = 1 / sqrt(pow(ix - xLow, 2) + pow(iy - yLow, 2) + pow(iz - zLow, 2));
                    long double xLyHzLDis = 1 / sqrt(pow(ix - xLow, 2) + pow(iy - yHigh, 2) + pow(iz - zLow, 2));
                    long double xHyLzLDis = 1 / sqrt(pow(ix - xHigh, 2) + pow(iy - yLow, 2) + pow(iz - zLow, 2));
                    long double xHyHzLDis = 1 / sqrt(pow(ix - xHigh, 2) + pow(iy - yHigh, 2) + pow(iz - zLow, 2));
                    long double xLyLzHDis = 1 / sqrt(pow(ix - xLow, 2) + pow(iy - yLow, 2) + pow(iz - zHigh, 2));
                    long double xLyHzHDis = 1 / sqrt(pow(ix - xLow, 2) + pow(iy - yHigh, 2) + pow(iz - zHigh, 2));
                    long double xHyLzHDis = 1 / sqrt(pow(ix - xHigh, 2) + pow(iy - yLow, 2) + pow(iz - zHigh, 2));
                    long double xHyHzHDis = 1 / sqrt(pow(ix - xHigh, 2) + pow(iy - yHigh, 2) + pow(iz - zHigh, 2));

                    long double totalDisR = xLyLzLDis + xLyHzLDis + xHyLzLDis + xHyHzLDis + xLyLzHDis + xLyHzHDis + xHyLzHDis + xHyHzHDis;

                    long double resultValue = xLyLzLDis / totalDisR * xLyLzLValue + xLyHzLDis / totalDisR * xLyHzLValue +
                                         xHyLzLDis / totalDisR * xHyLzLValue + xHyHzLDis / totalDisR * xHyHzLValue + xLyLzHDis / totalDisR * xLyLzHValue + xLyHzHDis / totalDisR * xLyHzHValue + xHyLzHDis / totalDisR * xHyLzHValue + xHyHzHDis / totalDisR * xHyHzHValue;
                    pTmpPointArray->push_back(osg::Vec4d(ix, iy, iz, resultValue));
                }
            }
        }
        //DataManager::instance()->setInversionData((const long double ***)NRO, NX, NY, NZ);
        DataManager::instance()->setInversionData(pTmpPointArray, 30, 30, 30);
        // emit onInvertCompleted(pTmpPointArray, (Z2 - Z1 + 1), (Y2 - Y1 + 1), (X2 - X1 + 1));
        emit onInvertCompleted();
    }
    setProcessBarValue(100);
    m_currentProgress = 0.0f;

    //     if (!LogSystem::instance()->getProgressBar()->isHidden())
    //     {
    //         LogSystem::instance()->getProgressBar()->hide();
    //     }
}

void ForwardAndInverseProcess::inducedPolariAutoGenProcess()
{
    start(QThread::NormalPriority);
}

void ForwardAndInverseProcess::doForwardProcess()
{
    potentialDeviceType = (int)GlobalParam::instance()->getForwardModelingParaSetting().potentialDeviceSelectionSwitch;

    switch (GlobalParam::instance()->getForwardModelingParaSetting().potentialDeviceSelectionSwitch)
    {
    case GlobalParam::Schlumberger:
        QLog("当前电位装置选择开关： Schlumberger");
        break;
    case GlobalParam::AMNB:
        QLog("当前电位装置选择开关： AMNB");
        break;
    default:
        break;
    }

    MN = 0.0;

    std::vector<osg::Vec2> list = m_pModelSubdivison->getMeasXYIndexVec();
    std::vector<double> YList   = m_pModelSubdivison->getYLVector();

    MN = YList[int(list[0].y())];

    QLog("最小电极间距为:    %f\n", MN);
    QLog("电极间的距离为:    %d\n", P_DIST);
    QLog("每条测线间的距离为(每条测线隔了几个边长?):  %d", L_DIST);
    QLog("电阻率正演采用的是异常电位法\n");
    QLog("电极附近的电阻率为:   %f", SGM0);
    QLog("模型中电阻率取值范围的下限为:   %f", BoundL);
    QLog("模型中电阻率取值的上限为:    %f", BoundU);
    QLog("供电电源点的节点编号的X‘坐标’为:   %d", I_NUMX);
    QLog("供电电源点的节点编号的Y‘坐标’为:   %d", I_NUMY);
    QLog("供电电源点的节点编号的Z‘坐标’为:   %d", I_NUMZ);

    long double R_DIST, R_DIST1, R_DIST2, R_DIST0;    //视电阻率K的距离
    ND         = (NX + 1) * (NY + 1) * (NZ + 1); //单元节点总数
    int *idofa = new int[ND];
    memset(idofa, 0, sizeof(int) * ND);

    long double *a = new long double[NUM * 45];
    memset(a, 0, sizeof(long double) * (NUM * 45));
    long double *U0 = new long double[ND];
    memset(U0, 0, sizeof(long double) * ND);
    long double *b = new long double[ND];
    memset(b, 0, sizeof(long double) * ND);

	_lock.lockForWrite();
	m_localIntVars.push_back(idofa);
	m_localVars.push_back(a);
	m_localVars.push_back(U0);
	m_localVars.push_back(b);
	_lock.unlock();

    m_forwardResult.clear();

    if (I_NUMZ <= 0 || I_NUMX <= 0 || I_NUMY <= 0)
        return;

    I_num = (I_NUMZ - 1) * (NX + 1) * (NY + 1) + (I_NUMX) * (NY + 1) + I_NUMY;
    Kzong();
    if (NULL == D)
    {
        D = new long double *[d_num * L_NUM + dc_num + 1];
        for (unsigned int i = 0; i < (d_num * L_NUM + dc_num + 1); i++)
        {
            D[i] = new long double[ND];
            memset(D[i], 0.0, sizeof(long double) * (ND));
        }
    }
    else
    {
        for (unsigned int i = 0; i < (d_num * L_NUM + dc_num + 1); i++)
        {
            for (unsigned int j = 0; j < ND; j++)
            {
                D[i][j] = 0.000000;
            }
        }
    }

    for (unsigned int j = 0; j < d_num * L_NUM; j++)
    {
        memset(U0, 0.00000000, sizeof(long double) * (ND));
        memset(b, 0.00000000, sizeof(long double) * (ND));

        UU0(D_POINT[j], U0);           //得到U0
        MULTIPLY(ND, GA1, U0, b, NUM); //得到b

        for (unsigned int i = 0; i < ND; i++)
        {
            D[j][i] = b[i];
        }
    }

    for (unsigned int j = d_num * L_NUM; j < d_num * L_NUM + dc_num; j++)
    {
        memset(U0, 0.000000, sizeof(long double) * (ND));
        UU0(D_POINT[j], U0);           //得到U0
        MULTIPLY(ND, GA1, U0, b, NUM); //得到b

        for (unsigned int i = 0; i < ND; i++)
        {
            D[j][i] = b[i];
        }
    }

    //!下面利用CHOLESKY法求解多点电源电场
    QLog("右端向量D计算完毕");
    QLog("形成半带宽一维存储数组A");

    setProcessBarValue(m_currentProgress + 6.0f * m_forwardTimeProportion / (float)INVMAX);

    //形成半带宽一维存储数组
    A_GENERATE(a, idofa); //得到out参数a和idofa

    setProcessBarValue(m_currentProgress + 10.0f * m_forwardTimeProportion / (float)INVMAX);

    QLog("开始进入CHOLESKY法多电源数值正演");

    //求解多点电源电场
    CHOLESKY(a, ND, d_num * L_NUM + dc_num + 1, idofa); //得到out参数a

    QLog("CHOLESKY法多电源数值正演结束");
    QLog("开始计算各个节点的总电位值");

    for (unsigned int j = 0; j < d_num * L_NUM; j++)
    {
		memset(U0, 0.00000000, sizeof(long double) * (ND));
        UU0(D_POINT[j], U0);
        for (unsigned int i = 0; i < ND; i++)
        {
            D[j][i] = D[j][i] + U0[i];
        }
    }

    for (unsigned int j = d_num * L_NUM; j < d_num * L_NUM + dc_num; j++)
    {
		memset(U0, 0.00000000, sizeof(long double) * (ND));
        UU0(D_POINT[j], U0);
        for (unsigned int i = 0; i < ND; i++)
        {
            D[j][i] = D[j][i] + U0[i];
        }
    }

    setProcessBarValue(m_currentProgress + (98.0f) * m_forwardTimeProportion / (float)INVMAX);

    QLog("各个节点的总电位值计算完毕!");
    QLog("正演结束");

    int ROW = -1;
    long double VM, VN;
    ARRAY_TYPE = 12;

    int circleNum = dc_num / 4;

    QLog("下面输出正演得到的视电阻率观测数据");
    if (ARRAY_TYPE == 12)
    {
        QLog("测线坐标,  横坐标值  ,纵坐标值  , 视电阻率值");
        QString valueString = "";
        //a1-a4的圈数
        for (unsigned int i = 0; i < circleNum; i++)
        {
            for (unsigned int k = 0; k < L_NUM; k++)
            {
                for (unsigned int j = 0; j < d_num; j++)
                {
                    ROW              = ROW + 1;
                    M_RESULT[ROW][0] = i + 1;
                    M_RESULT[ROW][1] = k + 1;
                    M_RESULT[ROW][2] = j + 1;

                    VM = 0.00;

                    /******************************目前只支持一条侧线的情况*************************/
                    VM = D[d_num * L_NUM + i][D_POINT[k * 10 + j]] +
                         D[d_num * L_NUM + circleNum + i][D_POINT[k * 10 + j]] +
                         D[d_num * L_NUM + 2 * circleNum + i][D_POINT[k * 10 + j]] +
                         D[d_num * L_NUM + 3 * circleNum + i][D_POINT[k * 10 + j]];

					M_RESULT[ROW][3] = VM;

					QString value = QString::number(M_RESULT[ROW][3], 'f', 10);

                    valueString += QString("%1   %2   %3   %4\n").arg(M_RESULT[ROW][0]).arg(M_RESULT[ROW][1]).arg(M_RESULT[ROW][2]).arg(value);
                    m_forwardResult.push_back(VM);
                }
            }
        }

        QStrLog(valueString);
    }

    if (ProcessType::invert == m_currentOperationType)
    {
        setProcessBarValue(m_currentProgress + (100.0f) * m_forwardTimeProportion / (float)INVMAX);
    }
    else
    {
        setProcessBarValue(100);

        //         if (!LogSystem::instance()->getProgressBar()->isHidden())
        //         {
        //             LogSystem::instance()->getProgressBar()->hide();
        //         }

        // 		if (!m_progressBar->isHidden())
        // 		{
        // 			m_progressBar->hide();
        // 		}
    }

	_lock.lockForWrite();

	vector<long double*>::iterator it = find(m_localVars.begin(), m_localVars.end(), a);

	if (m_localVars.end() != it)
	{
		m_localVars.erase(it);
	}

	SAFE_DELETE_ARRAY(a);

	it = find(m_localVars.begin(), m_localVars.end(), b);

	if (m_localVars.end() != it)
	{
		m_localVars.erase(it);
	}

	SAFE_DELETE_ARRAY(b);

	it = find(m_localVars.begin(), m_localVars.end(), U0);

	if (m_localVars.end() != it)
	{
		m_localVars.erase(it);
	}

	SAFE_DELETE_ARRAY(U0);

	vector<int*>::iterator it_int = find(m_localIntVars.begin(), m_localIntVars.end(), idofa);

	if (m_localIntVars.end() != it_int)
	{
		m_localIntVars.erase(it_int);
	}

	SAFE_DELETE_ARRAY(idofa);

	_lock.unlock();

    return;
}

void ForwardAndInverseProcess::Kzong()
{
    unsigned int L = 0;
    unsigned int NJ, NK, KK, FLAG;
    long double a, b, c;
    long double KEB1[8][8], KEB2[8][8], H, R, L1, L2, L3, XY1, XY2, XY3;
    long double SGM1, SGM2;

	int tmpI_NUM = (I_NUMZ - 1)*(NX + 1)*(NY + 1) + I_NUMX*(NY + 1) + I_NUMY;

    if (nullptr == GA1)
    {
        GA1 = new long double[NUM];
    }

    if (nullptr == GA)
    {
        GA = new long double[NUM];
    }

    memset(GA1, 0.0, sizeof(long double) * NUM);
    memset(GA, 0.0, sizeof(long double) * NUM);

    //下面将体内单元系数写入一维压缩数组GA和GA1
    for (unsigned int IZ = 0; IZ < NZ; IZ++)
    {
        for (unsigned int IX = 0; IX < NX; IX++)
        {
            for (unsigned int IY = 0; IY < NY; IY++)
            {
                L = (IZ)*NX * NY + (IX)*NY + IY;
                //X方向上的边长
                a = XY[I4[L][3]][0] - XY[I4[L][0]][0];
                //Y方向上的边长
                b = XY[I4[L][0]][1] - XY[I4[L][1]][1];
                //Z方向上的边长
                c = XY[I4[L][4]][2] - XY[I4[L][0]][2];

                //第(IX,IY,IZ)个单元的电阻率值
                SGM1 = 1.0 / NRO[IZ][IY][IX];
                SGM2 = 1.0 / NRO[IZ][IY][IX] - 1.0 / SGM0;
                /////////
                kE_1(a, b, c, SGM1, SGM2);
                for (unsigned int i = 0; i < 8; i++)
                {
                    //第L个单元中的第j个节点的编号
                    NJ = I4[L][i];
                    for (unsigned int j = 0; j < 8; j++)
                    {
                        NK = I4[L][j];
                        for (unsigned int k = IDID[NJ]; k < IDID[NJ + 1]; k++)
                        {
                            int aa         = IDID[NJ];
                            int bb         = IDID[NJ + 1];
                            unsigned int a = IDID[NJ];
                            unsigned int b = IDID[NJ + 1];

                            if (ID_vector[k].first == NJ && ID_vector[k].two == NK)
                            {
                                GA[k]  = GA[k] + KE1[j][i];  //形成左端总刚矩阵的一维存储数组GA
                                GA1[k] = GA1[k] + KE2[j][i]; //形成右端总刚矩阵的一维存储数组GA1
                            }
                        }
                    }
                }
            }
        }
    }

    //下面将IZ=1的边界上的边界单元系数写入一维压缩数组GA和GA1
    unsigned int IZ = 0;
    for (unsigned int IX = 0; IX < NX; IX++)
    {
        for (unsigned int IY = 0; IY < NY; IY++)
        {
            L = (IX)*NY + IY;
            //X方向上的边长
            a = XY[I4[L][3]][0] - XY[I4[L][0]][0];
            //Y方向上的边长
            b = XY[I4[L][0]][1] - XY[I4[L][1]][1];
            //Z方向上的边长
            c = XY[I4[L][4]][2] - XY[I4[L][0]][2];

            XY1 = XY[I4[L][0]][0] + XY[I4[L][1]][0] + XY[I4[L][2]][0] + XY[I4[L][3]][0];
            //节点与电源点在X方向上的距离
            L1 = XY1 / 4.0 - XY[tmpI_NUM - 1][0];

            XY2 = XY[I4[L][0]][1] + XY[I4[L][1]][1] + XY[I4[L][2]][1] + XY[I4[L][3]][1];
            //节点与电源点在Y方向上的距离
            L2 = XY2 / 4.0 - XY[tmpI_NUM - 1][1];

            XY3 = XY[I4[L][0]][2] + XY[I4[L][1]][2] + XY[I4[L][2]][2] + XY[I4[L][3]][2];
            //节点与电源点在Z方向上的距离
            L3 = XY3 / 4.0 - XY[tmpI_NUM - 1][2];

            R = sqrt(L1 * L1 + L2 * L2 + L3 * L3);
            H = fabs(L3);

            //第(IX,IY,IZ)个单元的电阻率值
            SGM1 = 1.0 / NRO[IZ][IY][IX];
            //第(IX,IY,IZ)个单元的异常电阻率值
            SGM2 = 1.0 / NRO[IZ][IY][IX] - 1.0 / SGM0;

            FLAG = 1;
            kE_2(a, b, c, SGM1, SGM2, KEB1, KEB2, FLAG, H, R);

            for (unsigned i = 0; i < 8; i++)
            {
                //第L个单元中的第i个节点的编号
                NJ = I4[L][i];
                for (unsigned int j = 0; j < 8; j++)
                {
                    //第L个单元中的第j个节点的编号
                    NK = I4[L][j];
                    for (unsigned int k = IDID[NJ]; k < IDID[NJ + 1]; k++)
                    {
                        if (ID_vector[k].two == NK)
                        {
                            GA[k]  = GA[k] + KEB1[j][i];
                            GA1[k] = GA1[k] + KEB2[j][i];
                        }
                    }
                }
            }
        }
    }

    //下面将IZ=NZ的边界上的边界单元系数写入一维压缩数组GA和GA1
    IZ = NZ - 1;
    for (unsigned int IX = 0; IX < NX; IX++)
    {
        for (unsigned int IY = 0; IY < NY; IY++)
        {
            L = (IZ)*NX * NY + (IX)*NY + IY; //IZ = NZ时的单元的编号
                                             //X方向上的边长
            a = XY[I4[L][3]][0] - XY[I4[L][0]][0];
            //Y方向上的边长
            b = XY[I4[L][0]][1] - XY[I4[L][1]][1];
            //Z方向上的边长
            c = XY[I4[L][4]][2] - XY[I4[L][0]][2];

            XY1 = XY[I4[L][4]][0] + XY[I4[L][5]][0] + XY[I4[L][6]][0] + XY[I4[L][7]][0];
            //节点与电源点在X方向上的距离
            L1 = XY1 / 4.0 - XY[tmpI_NUM - 1][0];

            XY2 = XY[I4[L][4]][1] + XY[I4[L][5]][1] + XY[I4[L][6]][1] + XY[I4[L][7]][1];
            //节点与电源点在Y方向上的距离
            L2 = XY2 / 4.0 - XY[tmpI_NUM - 1][1];

            XY3 = XY[I4[L][4]][2] + XY[I4[L][5]][2] + XY[I4[L][6]][2] + XY[I4[L][7]][2];
            //节点与电源点在Z方向上的距离
            L3 = XY3 / 4.0 - XY[tmpI_NUM - 1][2];

            R = sqrt(L1 * L1 + L2 * L2 + L3 * L3);
            H = fabs(L3);

            //第(IX,IY,IZ)个单元的电阻率值
            SGM1 = 1.0 / NRO[IZ][IY][IX];
            //第(IX,IY,IZ)个单元的异常电阻率值
            SGM2 = 1.0 / NRO[IZ][IY][IX] - 1.0 / SGM0;

            FLAG = 2;
            kE_2(a, b, c, SGM1, SGM2, KEB1, KEB2, FLAG, H, R);
            for (unsigned i = 0; i < 8; i++)
            {
                //第L个单元中的第i个节点的编号
                NJ = I4[L][i];
                for (unsigned int j = 0; j < 8; j++)
                {
                    //第L个单元中的第j个节点的编号
                    NK = I4[L][j];
                    for (unsigned int k = IDID[NJ]; k < IDID[NJ + 1]; k++)
                    {
                        if (ID_vector[k].two == NK)
                        {
                            GA[k]  = GA[k] + KEB1[j][i];
                            GA1[k] = GA1[k] + KEB2[j][i];
                        }
                    }
                }
            }
        }
    }

    //下面将IX = 1的边界上的边界单元系数写入一维压缩数组GA和GA1
    unsigned int IX = 0;
    for (unsigned int IZ = 0; IZ < NZ; IZ++)
    {
        for (unsigned int IY = 0; IY < NY; IY++)
        {
            L = (IZ)*NX * NY + (IX)*NY + IY; //IX = 1时的单元的编号

            //X方向上的边长
            a = XY[I4[L][3]][0] - XY[I4[L][0]][0];
            //Y方向上的边长
            b = XY[I4[L][0]][1] - XY[I4[L][1]][1];
            //Z方向上的边长
            c = XY[I4[L][4]][2] - XY[I4[L][0]][2];

            XY1 = XY[I4[L][0]][0] + XY[I4[L][1]][0] + XY[I4[L][5]][0] + XY[I4[L][4]][0];
            //节点与电源点在X方向上的距离
            L1 = XY1 / 4.0 - XY[tmpI_NUM - 1][0];

            XY2 = XY[I4[L][0]][1] + XY[I4[L][1]][1] + XY[I4[L][5]][1] + XY[I4[L][4]][1];
            //节点与电源点在Y方向上的距离
            L2 = XY2 / 4.0 - XY[tmpI_NUM - 1][1];

            XY3 = XY[I4[L][0]][2] + XY[I4[L][1]][2] + XY[I4[L][5]][2] + XY[I4[L][4]][2];
            //节点与电源点在Z方向上的距离
            L3 = XY3 / 4.0 - XY[tmpI_NUM - 1][2];

            //节点与电源点在Z方向上的距离
            R = sqrt(L1 * L1 + L2 * L2 + L3 * L3);
            H = fabs(L1);

            //第(IX,IY,IZ)个单元的电阻率值
            SGM1 = 1.0 / NRO[IZ][IY][IX];
            //第(IX,IY,IZ)个单元的异常电阻率值
            SGM2 = 1.0 / NRO[IZ][IY][IX] - 1.0 / SGM0;

            FLAG = 3;
            kE_2(a, b, c, SGM1, SGM2, KEB1, KEB2, FLAG, H, R);
            for (unsigned i = 0; i < 8; i++)
            {
                //第L个单元中的第i个节点的编号
                NJ = I4[L][i];
                for (unsigned int j = 0; j < 8; j++)
                {
                    //第L个单元中的第j个节点的编号
                    NK = I4[L][j];
                    for (unsigned int k = IDID[NJ]; k < IDID[NJ + 1]; k++)
                    {
                        if (ID_vector[k].two == NK)
                        {
                            GA[k]  = GA[k] + KEB1[j][i];
                            GA1[k] = GA1[k] + KEB2[j][i];
                        }
                    }
                }
            }
        }
    }

    //下面将IX = NX的边界上的边界单元系数写入一维压缩数组GA和GA1
    IX = NX - 1;
    for (unsigned int IZ = 0; IZ < NZ; IZ++)
    {
        for (unsigned int IY = 0; IY < NY; IY++)
        {
            L = (IZ)*NX * NY + (IX)*NY + IY; //IX = 1时的单元的编号
                                             //X方向上的边长
            a = XY[I4[L][3]][0] - XY[I4[L][0]][0];
            //Y方向上的边长
            b = XY[I4[L][0]][1] - XY[I4[L][1]][1];
            //Z方向上的边长
            c = XY[I4[L][4]][2] - XY[I4[L][0]][2];

            XY1 = XY[I4[L][2]][0] + XY[I4[L][3]][0] + XY[I4[L][6]][0] + XY[I4[L][7]][0];
            //节点与电源点在X方向上的距离
            L1 = XY1 / 4.0 - XY[tmpI_NUM - 1][0];

            XY2 = XY[I4[L][2]][1] + XY[I4[L][3]][1] + XY[I4[L][6]][1] + XY[I4[L][7]][1];
            //节点与电源点在Y方向上的距离
            L2 = XY2 / 4.0 - XY[tmpI_NUM - 1][1];

            XY3 = XY[I4[L][2]][2] + XY[I4[L][3]][2] + XY[I4[L][6]][2] + XY[I4[L][7]][2];
            //节点与电源点在Z方向上的距离
            L3 = XY3 / 4.0 - XY[tmpI_NUM - 1][2];

            //节点与电源点在Z方向上的距离
            R = sqrt(L1 * L1 + L2 * L2 + L3 * L3);
            H = fabs(L1);

            //第(IX,IY,IZ)个单元的电阻率值
            SGM1 = 1.0 / NRO[IZ][IY][IX];
            //第(IX,IY,IZ)个单元的异常电阻率值
            SGM2 = 1.0 / NRO[IZ][IY][IX] - 1.0 / SGM0;

            FLAG = 4;
            kE_2(a, b, c, SGM1, SGM2, KEB1, KEB2, FLAG, H, R);

            for (unsigned i = 0; i < 8; i++)
            {
                //第L个单元中的第i个节点的编号
                NJ = I4[L][i];
                for (unsigned int j = 0; j < 8; j++)
                {
                    //第L个单元中的第j个节点的编号
                    NK = I4[L][j];
                    for (unsigned int k = IDID[NJ]; k < IDID[NJ + 1]; k++)
                    {
                        if (ID_vector[k].two == NK)
                        {
                            GA[k]  = GA[k] + KEB1[j][i];
                            GA1[k] = GA1[k] + KEB2[j][i];
                        }
                    }
                }
            }
        }
    }

    //下面将IY=NY的边界上的边界单元系数写入一维压缩数组GA和GA1
    unsigned int IY = NY - 1;
    for (unsigned int IZ = 0; IZ < NZ; IZ++)
    {
        for (unsigned int IX = 0; IX < NX; IX++)
        {
            L = (IZ)*NX * NY + (IX)*NY + IY; //IX = 1时的单元的编号
                                             //X方向上的边长
            a = XY[I4[L][3]][0] - XY[I4[L][0]][0];
            //Y方向上的边长
            b = XY[I4[L][0]][1] - XY[I4[L][1]][1];
            //Z方向上的边长
            c = XY[I4[L][4]][2] - XY[I4[L][0]][2];

            XY1 = XY[I4[L][1]][0] + XY[I4[L][2]][0] + XY[I4[L][6]][0] + XY[I4[L][5]][0];
            //节点与电源点在X方向上的距离
            L1 = XY1 / 4.0 - XY[tmpI_NUM - 1][0];

            XY2 = XY[I4[L][1]][1] + XY[I4[L][2]][1] + XY[I4[L][6]][1] + XY[I4[L][5]][1];
            //节点与电源点在Y方向上的距离
            L2 = XY2 / 4.0 - XY[tmpI_NUM - 1][1];

            XY3 = XY[I4[L][1]][2] + XY[I4[L][2]][2] + XY[I4[L][6]][2] + XY[I4[L][5]][2];
            //节点与电源点在Z方向上的距离
            L3 = XY3 / 4.0 - XY[tmpI_NUM - 1][2];

            //节点与电源点在Z方向上的距离
            R = sqrt(L1 * L1 + L2 * L2 + L3 * L3);
            H = fabs(L2);

            //第(IX,IY,IZ)个单元的电阻率值
            SGM1 = 1.0 / NRO[IZ][IY][IX];
            //第(IX,IY,IZ)个单元的异常电阻率值
            SGM2 = 1.0 / NRO[IZ][IY][IX] - 1.0 / SGM0;

            FLAG = 5;
            kE_2(a, b, c, SGM1, SGM2, KEB1, KEB2, FLAG, H, R);

            for (unsigned i = 0; i < 8; i++)
            {
                //第L个单元中的第i个节点的编号
                NJ = I4[L][i];
                for (unsigned int j = 0; j < 8; j++)
                {
                    //第L个单元中的第j个节点的编号
                    NK = I4[L][j];
                    for (unsigned int k = IDID[NJ]; k < IDID[NJ + 1]; k++)
                    {
                        if (ID_vector[k].two == NK)
                        {
                            GA[k]  = GA[k] + KEB1[j][i];
                            GA1[k] = GA1[k] + KEB2[j][i];
                        }
                    }
                }
            }
        }
    }

    //下面将IY=1的边界上的边界单元系数写入一维压缩数组GA和GA1
    IY = 0;
    for (unsigned int IZ = 0; IZ < NZ; IZ++)
    {
        for (unsigned int IX = 0; IX < NX; IX++)
        {
            L = (IZ)*NX * NY + (IX)*NY + IY; //IY = 1时的单元的编号
                                             //X方向上的边长
            a = XY[I4[L][3]][0] - XY[I4[L][0]][0];
            //Y方向上的边长
            b = XY[I4[L][0]][1] - XY[I4[L][1]][1];
            //Z方向上的边长
            c = XY[I4[L][4]][2] - XY[I4[L][0]][2];

            XY1 = XY[I4[L][0]][0] + XY[I4[L][4]][0] + XY[I4[L][3]][0] + XY[I4[L][7]][0];
            //节点与电源点在X方向上的距离
            L1 = XY1 / 4.0 - XY[tmpI_NUM - 1][0];

            XY2 = XY[I4[L][0]][1] + XY[I4[L][4]][1] + XY[I4[L][3]][1] + XY[I4[L][7]][1];
            //节点与电源点在Y方向上的距离
            L2 = XY2 / 4.0 - XY[tmpI_NUM - 1][1];

            XY3 = XY[I4[L][0]][2] + XY[I4[L][4]][2] + XY[I4[L][3]][2] + XY[I4[L][7]][2];
            //节点与电源点在Z方向上的距离
            L3 = XY3 / 4.0 - XY[tmpI_NUM - 1][2];

            //节点与电源点在Z方向上的距离
            R = sqrt(L1 * L1 + L2 * L2 + L3 * L3);
            H = fabs(L2);

            //第(IX,IY,IZ)个单元的电阻率值
            SGM1 = 1.0 / NRO[IZ][IY][IX];
            //第(IX,IY,IZ)个单元的异常电阻率值
            SGM2 = 1.0 / NRO[IZ][IY][IX] - 1.0 / SGM0;

            FLAG = 6;
            kE_2(a, b, c, SGM1, SGM2, KEB1, KEB2, FLAG, H, R);

            for (unsigned i = 0; i < 8; i++)
            {
                //第L个单元中的第i个节点的编号
                NJ = I4[L][i];
                for (unsigned int j = 0; j < 8; j++)
                {
                    //第L个单元中的第j个节点的编号
                    NK = I4[L][j];
                    for (unsigned int k = IDID[NJ]; k < IDID[NJ + 1]; k++)
                    {
                        if (ID_vector[k].two == NK)
                        {
                            GA[k]  = GA[k] + KEB1[j][i];
                            GA1[k] = GA1[k] + KEB2[j][i];
                        }
                    }
                }
            }
        }
    }

    //下面将右端项总体系数矩阵GA1取负值
    for (unsigned int i = 0; i < NUM; i++)
    {
        GA1[i] = -GA1[i];
    }
}

void ForwardAndInverseProcess::kE_2(long double a, long double b, long double c, long double SGM1, long double SGM2, long double KEB1[8][8], long double KEB2[8][8], int FLAG, long double H, long double L)
{
    //面1234
    long double K1[8][8] =
        {
            {4.0, 2.0, 1.0, 2.0, 0.0, 0.0, 0.0, 0.0},
            {2.0, 4.0, 2.0, 1.0, 0.0, 0.0, 0.0, 0.0},
            {1.0, 2.0, 4.0, 2.0, 0.0, 0.0, 0.0, 0.0},
            {2.0, 1.0, 2.0, 4.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
            /*4.0,2.0,1.0,2.0,0.0,0.0,0.0,0.0,2.0,4.0,2.0,1.0,0.0,0.0,
		*0.0,0.0,1.0,2.0,4.0,2.0,0.0,0.0,0.0,0.0,2.0,1.0,2.0,4.0,
		*0.0,0.0,0.0,0.0,32 * 0.0*/
        };

    //面5678
    long double K2[8][8] =
        {
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 4.0, 2.0, 1.0, 2.0},
            {0.0, 0.0, 0.0, 0.0, 2.0, 4.0, 2.0, 1.0},
            {0.0, 0.0, 0.0, 0.0, 1.0, 2.0, 4.0, 2.0},
            {0.0, 0.0, 0.0, 0.0, 2.0, 1.0, 2.0, 4.0}
            /*32*0.0,4*0.0,4.0,2.0,1.0,2.0,4*0.0,2.0,4.0,2.0,1.0,
		4*0.0,1.0,2.0,4.0,2.0,4*0.0,2.0,1.0,2.0,4.0*/
        };

    //面1265
    long double K3[8][8] =
        {
            {4.0, 2.0, 0.0, 0.0, 2.0, 1.0, 0.0, 0.0},
            {2.0, 4.0, 0.0, 0.0, 1.0, 2.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {2.0, 1.0, 0.0, 0.0, 4.0, 2.0, 0.0, 0.0},
            {1.0, 2.0, 0.0, 0.0, 2.0, 4.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
            /*4.0,2.0,2*0.0,2.0,1.0,0.0,0.0,2.0,4.0,0.0,0.0,1.0,2.0,
		0.0,0.0,16*0.0,2.0,1.0,0.0,0.0,4.0,2.0,0.0,0.0,1.0,2.0,0.0,
		0.0,2.0,4.0,18*0.0*/
        };

    //面3487
    long double K4[8][8] =
        {
			{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
			{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
			{ 0.0, 0.0, 4.0, 2.0, 0.0, 0.0, 2.0, 1.0 },
			{ 0.0, 0.0, 2.0, 4.0, 0.0, 0.0, 1.0, 2.0 },
			{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
			{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
			{ 0.0, 0.0, 2.0, 1.0, 0.0, 0.0, 4.0, 2.0 },
			{ 0.0, 0.0, 1.0, 2.0, 0.0, 0.0, 2.0, 4.0 }
            /*18*0.0,4.0,2.0,0.0,0.0,2.0,1.0,0.0,0.0,2.0,4.0,0.0,0.0,
		1.0,2.0,18*0.0,2.0,1.0,0.0,0.0,4.0,2.0,0.0,0.0,1.0,2.0,
		0.0,0.0,2.0,4.0*/
        };

    //面2376
    long double K5[8][8] =
        {
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 4.0, 2.0, 0.0, 0.0, 2.0, 1.0, 0.0},
            {0.0, 2.0, 4.0, 0.0, 0.0, 1.0, 2.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 2.0, 1.0, 0.0, 0.0, 4.0, 2.0, 0.0},
            {0.0, 1.0, 2.0, 0.0, 0.0, 2.0, 4.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
            /*9*0.0,4.0,2.0,0.0,0.0,2.0,1.0,0.0,0.0,2.0,4.0,0.0,0.0,
		1.0,2.0,18*0.0,2.0,1.0,0.0,0.0,4.0,2.0,0.0,0.0,1.0,2.0,
		0.0,0.0,2.0,4.0,9*0.0*/
        };

    //面2376
    long double K6[8][8] =
        {
            {4.0, 0.0, 0.0, 2.0, 2.0, 0.0, 0.0, 1.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {2.0, 0.0, 0.0, 4.0, 1.0, 0.0, 0.0, 2.0},
            {2.0, 0.0, 0.0, 1.0, 4.0, 0.0, 0.0, 2.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {1.0, 0.0, 0.0, 2.0, 2.0, 0.0, 0.0, 4.0}
            /*4.0,2*0.0,2.0,2.0,2*0.0,1.0,16*0.0,2.0,2*0.0,4.0,1.0,
		2*0.0,2.0,2.0,2*0.0,1.0,4.0,2*0.0,2.0,16*0.0,1.0,2*0.0,
		2.0,2.0,2*0.0,4.0*/
        };

    if (FLAG == 1)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                KEB1[j][i] = (a * b / 36.00) * SGM1 * (H / L) * (1.00 / L) * K1[j][i];
                KEB2[j][i] = (a * b / 36.00) * SGM2 * (H / L) * (1.00 / L) * K1[j][i];
            }
        }
    }
    else if (FLAG == 2)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                KEB1[j][i] = (a * b / 36.00) * SGM1 * (H / L) * (1.00 / L) * K2[j][i];
                KEB2[j][i] = (a * b / 36.00) * SGM2 * (H / L) * (1.00 / L) * K2[j][i];
            }
        }
    }
    else if (FLAG == 3)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                KEB1[j][i] = (c * b / 36.00) * SGM1 * (H / L) * (1.00 / L) * K3[j][i];
                KEB2[j][i] = (c * b / 36.00) * SGM2 * (H / L) * (1.00 / L) * K3[j][i];
            }
        }
    }
    else if (FLAG == 4)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                KEB1[j][i] = (c * b / 36.00) * SGM1 * (H / L) * (1.00 / L) * K4[j][i];
                KEB2[j][i] = (c * b / 36.00) * SGM2 * (H / L) * (1.00 / L) * K4[j][i];
            }
        }
    }
    else if (FLAG == 5)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                KEB1[j][i] = (a * c / 36.00) * SGM1 * (H / L) * (1.00 / L) * K5[j][i];
                KEB2[j][i] = (a * c / 36.00) * SGM2 * (H / L) * (1.00 / L) * K5[j][i];
            }
        }
    }
    else if (FLAG == 6)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                KEB1[j][i] = (a * c / 36.00) * SGM1 * (H / L) * (1.00 / L) * K6[j][i];
                KEB2[j][i] = (a * c / 36.00) * SGM2 * (H / L) * (1.00 / L) * K6[j][i];
            }
        }
    }
}

void ForwardAndInverseProcess::ID_GENERATOR(unsigned int NX, unsigned int NY, unsigned int NZ, unsigned int ND, unsigned int NE, int *IDID, unsigned int &NUM)
{
    if (false)
    {
        NUM   = 0;
        int N = 1;
        ID_vector.clear();
        for (unsigned int i = 0; i < (NZ + 1); i++)
        {
            for (unsigned int j = 0; j < (NX + 1); j++)
            {
                for (unsigned int k = 0; k < (NY + 1); k++)
                {

                    int I = i * (NX + 1) * (NY + 1) + j * (NY + 1) + k;
                    //arrayIndex tmpValidIndexSet(I);

                    N = (I - 1) - ((NX + 1) * (NY + 1)) - (NY + 1);
                    if (N >= 0 /*&& k != 0 && i != 0 && j != 0*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I) - ((NX + 1) * (NY + 1)) - (NY + 1);
                    if (N >= 0 /*&& i != 0 && j != 0*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I + 1) - ((NX + 1) * (NY + 1)) - (NY + 1);
                    if (N >= 0 /*&& k < NY && i != 0 && j != 0*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I - 1) - ((NX + 1) * (NY + 1));
                    if (N >= 0 /*&& k != 0 && i != 0*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I) - ((NX + 1) * (NY + 1));
                    if (N >= 0 /*&& i != 0*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }
                    N = (I + 1) - ((NX + 1) * (NY + 1));
                    if (N >= 0 /*&& k < NY && i != 0*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I - 1) - ((NX + 1) * (NY + 1)) + (NY + 1);
                    if (N >= 0 /*&& k != 0 && i != 0 && j < NX*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I) - ((NX + 1) * (NY + 1)) + (NY + 1);
                    if (N >= 0 /*&& i != 0 && j < NX*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I + 1) - ((NX + 1) * (NY + 1)) + (NY + 1);
                    if (N >= 0 /*&& k < NY && i != 0 && j < NX*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I - 1) - (NY + 1);
                    if (N >= 0 /*&& k != 0 && j != 0*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I) - (NY + 1);
                    if (N >= 0 /*&& j != 0*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }
                    N = (I + 1) - (NY + 1);
                    if (N >= 1 /*&& k < NY && j != 0*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = I - 1;
                    if (N >= 0 /*&& k != 0*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = I;
                    if (N >= 0)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = I + 1;
                    if (N >= 0 /*&& k < NY*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    //TODOOOOOOOOOOO 这个点fortran程序未屏蔽掉
                    N = (I - 1) + (NY + 1);
                    if (N >= 0 /* && k != 0 && j < NX*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I) + (NY + 1);
                    if (N >= 0 /* && j < NX*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I + 1) + (NY + 1);
                    if (N >= 0 /*&& k < NY && j < NX*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I - 1) + ((NX + 1) * (NY + 1)) - (NY + 1);
                    if (N >= 0 /*&& k != 0 && j != 0 && i < NZ*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I) + ((NX + 1) * (NY + 1)) - (NY + 1);
                    if (N >= 0 /*&& i < NZ && j != 0*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I + 1) + ((NX + 1) * (NY + 1)) - (NY + 1);
                    if (N >= 0 /*&& k < NY && i < NZ && j != 0*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I - 1) + ((NX + 1) * (NY + 1));
                    if (N >= 0 /*&& k != 0 && i < NZ*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I) + ((NX + 1) * (NY + 1));
                    if (N >= 0 /*&& i < NZ*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I + 1) + ((NX + 1) * (NY + 1));
                    if (N >= 0 /*&& k < NY && i < NZ*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I - 1) + ((NX + 1) * (NY + 1)) + (NY + 1);
                    if (N >= 0 /*&& k != 0 && i < NZ && j < NX*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I) + ((NX + 1) * (NY + 1)) + (NY + 1);
                    if (N >= 0 /*&& i < NZ && j < NX*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I + 1) + ((NX + 1) * (NY + 1)) + (NY + 1);
                    if (N >= 0 /*&& k < NY && i < NZ && j < NX*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }
                    //ID_vector.push_back(tmpValidIndexSet);
                }
            }
        }

        NUM = ID_vector.size();
        ////test
        //for (size_t i = 0; i < ID_vector.size(); i++)
        //{
        //	arrayIndex tmpIndex = ID_vector[i];

        //	int l = tmpIndex.first;
        //	int m = tmpIndex.two;
        //}
        IDID[0] = 0;
        //IDID[1] = 8;//0号节点所对应的立方体的节点个数
        //IDID[2] = 8+12; //0号节点所对应的立方体的节点个数 + 1号节点所对应的所有立方体的节点个数
        //IDID[3] = 8 + 12 + 12; //0号节点所对应的立方体的节点个数 + 1号节点所对应的所有立方体的节点个数
        int MM = 0;

        for (unsigned int i = 1; i < NUM; i++)
        {
            if (ID_vector[i].first != (MM))
            {
                MM       = MM + 1;
                IDID[MM] = i;
            }
        }
        IDID[MM + 1] = NUM;
    }
    else
    {
        NUM   = 0;
        int N = 1;
        ID_vector.clear();
        for (unsigned int i = 0; i < (NZ + 1); i++)
        {
            for (unsigned int j = 0; j < (NX + 1); j++)
            {
                for (unsigned int k = 0; k < (NY + 1); k++)
                {

                    int I = i * (NX + 1) * (NY + 1) + j * (NY + 1) + k;
                    //arrayIndex tmpValidIndexSet(I);

                    N = (I - 1) - ((NX + 1) * (NY + 1)) - (NY + 1);
                    if (N >= 0 && N < ND /*&& k != 1 && i != 0 && j != 0*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I) - ((NX + 1) * (NY + 1)) - (NY + 1);
                    if (N >= 0 && N < ND /*&& i != 0 && j != 0*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I + 1) - ((NX + 1) * (NY + 1)) - (NY + 1);
                    if (N >= 0 && N < ND /* && k < NY + 1 && i != 0 && j != 0*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I - 1) - ((NX + 1) * (NY + 1));
                    if (N >= 0 && N < ND /*&& k != 1 && i != 0*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I) - ((NX + 1) * (NY + 1));
                    if (N >= 0 && N < ND /*&& i != 0*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }
                    N = (I + 1) - ((NX + 1) * (NY + 1));
                    if (N >= 0 && N < ND /*&& k < NY + 1 && i != 0*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I - 1) - ((NX + 1) * (NY + 1)) + (NY + 1);
                    if (N >= 0 && N < ND /*&& k != 1 && i != 0 && j < NX*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I) - ((NX + 1) * (NY + 1)) + (NY + 1);
                    if (N >= 0 && N < ND /*&& i != 0 && j < NX*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I + 1) - ((NX + 1) * (NY + 1)) + (NY + 1);
                    if (N >= 0 && N < ND /*&& k < NY + 1 && i != 0 && j < NX*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I - 1) - (NY + 1);
                    if (N >= 0 && N < ND /*&& k != 1 && j != 0*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I) - (NY + 1);
                    if (N >= 0 && N < ND /*&& j != 0*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }
                    N = (I + 1) - (NY + 1);
                    if (N >= 0 && N < ND /*&& k < NY + 1 && j != 0*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = I - 1;
                    if (N >= 0 && N < ND /*&& k != 1*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = I;
                    if (N >= 0 && N < ND)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = I + 1;
                    if (N >= 0 && N < ND /*&& k < NY + 1*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    //TODOOOOOOOOOOO 这个点fortran程序未屏蔽掉
                    N = (I - 1) + (NY + 1);
                    if (N >= 0 && N < ND /*&& k != 1 && j < NX*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I) + (NY + 1);
                    if (N >= 0 && N < ND /*&& j < NX*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I + 1) + (NY + 1);
                    if (N >= 0 && N < ND /*&& k < NY + 1 && j < NX*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I - 1) + ((NX + 1) * (NY + 1)) - (NY + 1);
                    if (N >= 0 && N < ND /*&& k != 1 && j != 0 && i < NZ*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I) + ((NX + 1) * (NY + 1)) - (NY + 1);
                    if (N >= 0 && N < ND /*&& i < NZ && j != 0*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I + 1) + ((NX + 1) * (NY + 1)) - (NY + 1);
                    if (N >= 0 && N < ND /*&& k < NY + 1 && i < NZ && j != 0*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I - 1) + ((NX + 1) * (NY + 1));
                    if (N >= 0 && N < ND /*&& k != 1 && i < NZ*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I) + ((NX + 1) * (NY + 1));
                    if (N >= 0 && N < ND /*&& i < NZ*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I + 1) + ((NX + 1) * (NY + 1));
                    if (N >= 0 && N < ND /*&& k < NY + 1 && i < NZ*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I - 1) + ((NX + 1) * (NY + 1)) + (NY + 1);
                    if (N >= 0 && N < ND /*&& k != 1 && i <NZ && j < NX*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I) + ((NX + 1) * (NY + 1)) + (NY + 1);
                    if (N >= 0 && N < ND /*&& i < NZ && j < NX*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }

                    N = (I + 1) + ((NX + 1) * (NY + 1)) + (NY + 1);
                    if (N >= 0 && N < ND /*&& k < NY + 1 && i < NZ && j < NX*/)
                    {
                        ID_vector.push_back(ArrayIndex(I, N));
                        //tmpValidIndexSet.validIndexSet.insert(N - 1);
                    }
                    //ID_vector.push_back(tmpValidIndexSet);
                }
            }
        }

        NUM = ID_vector.size();
        ////test
        //for (size_t i = 0; i < ID_vector.size(); i++)
        //{
        //	arrayIndex tmpIndex = ID_vector[i];

        //	int l = tmpIndex.first;
        //	int m = tmpIndex.two;
        //}
        IDID[0] = 0;
        //IDID[1] = 8;//0号节点所对应的立方体的节点个数
        //IDID[2] = 8+12; //0号节点所对应的立方体的节点个数 + 1号节点所对应的所有立方体的节点个数
        //IDID[3] = 8 + 12 + 12; //0号节点所对应的立方体的节点个数 + 1号节点所对应的所有立方体的节点个数
        int MM = 0;

        for (unsigned int i = 1; i < NUM; i++)
        {
            if (ID_vector[i].first != (MM))
            {
                MM       = MM + 1;
                IDID[MM] = i;
            }
        }
        IDID[MM + 1] = NUM;
    }
}

void ForwardAndInverseProcess::UU0(int I_NUM, long double *U0)
{
    long double PIValue = 3.14159274101257;
    long double L1, L2, L3, L;
	long double tmpValue = 4.000000000;
    for (int IZ = 0; IZ < NZ + 1; IZ++)
    {
        for (int IX = 0; IX < NX + 1; IX++)
        {
            for (int IY = 0; IY < NY + 1; IY++)
            {
                int N = (IZ) * (NX + 1) * (NY + 1) + (IX) * (NY + 1) + IY;

                if (N != (I_NUM))
                {
                    L1     = XY[N][0] - XY[I_NUM][0];
                    int aa = XY[N][0];
                    int bb = XY[I_NUM][0];
                    L2     = XY[N][1] - XY[I_NUM][1];
                    L3     = XY[N][2] - XY[I_NUM][2];
                    L      = sqrt(L1 * L1 + L2 * L2 + L3 * L3); //求平方根
                    U0[N]  = (SGM0 * II) / (tmpValue * PIValue * L);
                }
            }
        }
    }

    U0[I_NUM] = SGM0 * II / (tmpValue * PIValue);
}

void ForwardAndInverseProcess::MULTIPLY(int ND, long double *GA, long double *X, long double *Y, int NUM)
{
    memset(Y, 0.0000000, sizeof(long double) * ND);
    for (unsigned int I = 0; I < NUM; I++)
    {
        int first = ID_vector[I].first;
        int two   = ID_vector[I].two;
        Y[first]  = Y[first] + GA[I] * X[two];
    }
}

void ForwardAndInverseProcess::kE_1(long double a, long double b, long double c, long double SGM1, long double SGM2)
{
    long double KK1[3];
    long double AA, BB, CC;

    long double K1[9][3] =
        {
            {4.0, 4.0, 4.0},
            {2.0, -4.0, 2.0},
            {-2.0, -2.0, 1.0},
            {-4.0, 2.0, 2.0},
            {2.0, 2.0, -4.0},
            {1.0, -2.0, -2.0},
            {-1.0, -1.0, -1.0},
            {-2.0, 1.0, -2.0},
            {4.0, 4.0, 4.0}
            /*{ 4.0, 2.0, -2.0,-4.0, 2.0, 1.0, -1.0, -2.0, 4.0 },
		{ 4.0, -4.0,-2.0, 2.0, 2.0, -2.0,-1.0, 1.0,  4.0 },
		{ 4.0, 2.0, 1.0,  2.0, -4.0,-2.0,-1.0, -2.0, 4.0 }*/
        };

    long double K2[9][3] =
        {
            {-4.0, 2.0, 2.0},
            {-2.0, -2.0, 1.0},
            {1.0, -2.0, -2.0},
            {2.0, 2.0, -4.0},
            {-2.0, 1.0, -2.0},
            {-1.0, -1.0, -1.0},
            {4.0, 4.0, 4.0},
            {2.0, -4.0, 2.0},
            {-1.0, -1.0, -1.0}
            /*{ -4.0,-2.0,1.0,2.0,-2.0,-1.0,4.0,2.0,-1.0},
		{ 2.0,   -2.0,-2.0,2.0,1.0,-1.0,4.0,-4.0,-1.0},
		{ 2.0,    1.0,-2.0,-4.0,-2.0,-1.0,4.0,2.0,-1.0}*/
        };

    long double K3[9][3] =
        {
            {-2.0, 1.0, -2.0},
            {2.0, 2.0, -4.0},
            {1.0, -2.0, -2.0},
            {4.0, 4.0, 4.0},
            {-2.0, 1.0, -2.0},
            {-1.0, -1.0, -1.0},
            {1.0, -2.0, -2.0},
            {2.0, 2.0, -4.0},
            {4.0, 4.0, 4.0}
            /*{ -2.0,2.0,1.0, 4.0,-2.0,-1.0,1.0,2.0,4.0 },
		{   1.0, 2.0,-2.0,4.0,1.0,-1.0,-2.0,2.0,4.0 },
		{   -2.0,-4.0,-2.0,4.0,-2.0,-1.0,-2.0,-4.0,4.0}*/
        };

    long double K4[9][3] =
        {
            {2.0, -4.0, 2.0},
            {-2.0, -2.0, 1.0},
            {-4.0, 2.0, 2.0},
            {4.0, 4.0, 4.0},
            {-4.0, 2.0, 2.0},
            {-2.0, -2.0, 1.0},
            {4.0, 4.0, 4.0},
            {2.0, -4.0, 2.0},
            {4.0, 4.0, 4.0}
            /*{ 2.0, -2.0,-4.0,4.0,-4.0,-2.0,4.0, 2.0,4.0 },
		{   -4.0,-2.0,2.0, 4.0, 2.0,-2.0,4.0,-4.0,4.0 },
		{   2.0, 1.0, 2.0, 4.0, 2.0,1.0, 4.0, 2.0,4.0 }*/
        };

    AA = b * c / ((long double)36.0 * a);
    BB = a * c / ((long double)36.0 * b);
    CC = a * b / ((long double)36.0 * c);

    KK1[0] = AA;
    KK1[1] = BB;
    KK1[2] = CC;

    long double *kValue = MatmulOne(K1, 3, 9, KK1, 3);

	_lock.lockForWrite();
	m_localVars.push_back(kValue);
	_lock.unlock();

    for (unsigned int i = 0; i < 8; i++)
    {
        KE1[0][i] = kValue[i];
    }
    KE1[1][1] = kValue[8];

    long double *kTwoValue = MatmulOne(K2, 3, 9, KK1, 3);

	_lock.lockForWrite();
	m_localVars.push_back(kTwoValue);
	_lock.unlock();

    KE1[1][2]         = kTwoValue[0];
    KE1[1][3]         = kTwoValue[1];
    KE1[1][4]         = kTwoValue[2];
    KE1[1][5]         = kTwoValue[3];
    KE1[1][6]         = kTwoValue[4];
    KE1[1][7]         = kTwoValue[5];
    KE1[2][2]         = kTwoValue[6];
    KE1[2][3]         = kTwoValue[7];
    KE1[2][4]         = kTwoValue[8];

    long double *kThreeValue = MatmulOne(K3, 3, 9, KK1, 3);

	_lock.lockForWrite();
	m_localVars.push_back(kThreeValue);
	_lock.unlock();
    KE1[2][5]           = kThreeValue[0];
    KE1[2][6]           = kThreeValue[1];
    KE1[2][7]           = kThreeValue[2];
    KE1[3][3]           = kThreeValue[3];
    KE1[3][4]           = kThreeValue[4];
    KE1[3][5]           = kThreeValue[5];
    KE1[3][6]           = kThreeValue[6];
    KE1[3][7]           = kThreeValue[7];
    KE1[4][4]           = kThreeValue[8];

    long double *kFourValue = MatmulOne(K4, 3, 9, KK1, 3);

	_lock.lockForWrite();
	m_localVars.push_back(kFourValue);
	_lock.unlock();

    KE1[4][5]          = kFourValue[0];
    KE1[4][6]          = kFourValue[1];
    KE1[4][7]          = kFourValue[2];
    KE1[5][5]          = kFourValue[3];
    KE1[5][6]          = kFourValue[4];
    KE1[5][7]          = kFourValue[5];
    KE1[6][6]          = kFourValue[6];
    KE1[6][7]          = kFourValue[7];
    KE1[7][7]          = kFourValue[8];

    for (int i = 1; i < 8; i++)
    {
        KE1[i][0] = KE1[0][i];
    }

    for (int i = 2; i < 8; i++)
    {
        KE1[i][1] = KE1[1][i];
    }

    for (int i = 3; i < 8; i++)
    {
        KE1[i][2] = KE1[2][i];
    }

    for (int i = 4; i < 8; i++)
    {
        KE1[i][3] = KE1[3][i];
    }

    for (int i = 5; i < 8; i++)
    {
        KE1[i][4] = KE1[4][i];
    }

    for (int i = 6; i < 8; i++)
    {
        KE1[i][5] = KE1[5][i];
    }

    KE1[7][6] = KE1[6][7];

    for (unsigned int i = 0; i < 8; i++)
    {
        for (unsigned j = 0; j < 8; j++)
        {
            KE2[i][j] = KE1[i][j] * SGM2;
            KE1[i][j] = KE1[i][j] * SGM1;
        }
    }

	_lock.lockForWrite();

	vector<long double*>::iterator it = find(m_localVars.begin(), m_localVars.end(), kValue);

	if (m_localVars.end() != it)
	{
		m_localVars.erase(it);
	}

	SAFE_DELETE_ARRAY(kValue);

	it = find(m_localVars.begin(), m_localVars.end(), kTwoValue);

	if (m_localVars.end() != it)
	{
		m_localVars.erase(it);
	}

	SAFE_DELETE_ARRAY(kTwoValue);

	it = find(m_localVars.begin(), m_localVars.end(), kThreeValue);

	if (m_localVars.end() != it)
	{
		m_localVars.erase(it);
	}

	SAFE_DELETE_ARRAY(kThreeValue);

	it = find(m_localVars.begin(), m_localVars.end(), kFourValue);

	if (m_localVars.end() != it)
	{
		m_localVars.erase(it);
	}

	SAFE_DELETE_ARRAY(kFourValue);

	_lock.unlock();
}

void ForwardAndInverseProcess::CHOLESKY(long double *A, int N, int M, int *IDOFA)
{
    QLog("CHOLESKY法求解方程开始");

    int L = 1;

    //等于0的场合
    if (fabs(A[0]) < 1e-15)
    {
        L = 0;
    }
    //对系数矩阵的第一行、第一列的元素进行处理
    A[0] = sqrt(A[0]);

    //对系数阵的第一行数据进行处理
    for (int j = IDOFA[0] + 1; j <= IDOFA[1] - 1; j++)
    {
        float progressValue = float(j - IDOFA[0] + 1) / float(IDOFA[1] - 1 - IDOFA[0] + 1) * 6.0f;

        setProcessBarValue(m_currentProgress + (10.0f + progressValue) * m_forwardTimeProportion / (float)INVMAX);

        if (fabs(A[0]) > 0)
            A[j] = A[j] / A[0];
    }

    //下面的大循环25100是对系数阵的其它元素进行处理
    for (int i = 1; i < N; i++)
    {
        float progressValue = float(i) / float(N) * 60.0f;

        setProcessBarValue(m_currentProgress + (16.0f + progressValue) * m_forwardTimeProportion / (float)INVMAX);

        if (i == 10000)
        {
            //QLog(i);
        }
        else if (i == 20000)
        {
            //QLog(i);
        }
        else if (i == 30000)
        {
            //QLog(i);
        }
        else if (i == 40000)
        {
            //QLog(i);
        }

        if (i < band + 50)
        {
            //该循环是对每行的对角元素进行处理
            for (int j = 0; j < i; j++)
            {
                if (IDOFA[j] + i - j <= IDOFA[j + 1] - 1)
                {
                    A[IDOFA[i]] = A[IDOFA[i]] - A[IDOFA[j] + i - j] * A[IDOFA[j] + i - j];
                }
            }
        }
        else
        {
            for (int j = i - (band + 50); j < i; j++)
            {
                if (IDOFA[j] + i - j <= IDOFA[j + 1] - 1)
                {
                    A[IDOFA[i]] = A[IDOFA[i]] - A[IDOFA[j] + i - j] * A[IDOFA[j] + i - j];
                }
            }
        }

        //下面是验证系数矩阵的正定性
        if (fabs(A[IDOFA[i]]) < 1e-15)
        {
            L = 0;
            //WRITE(*, FORMAT(1X, 'FAIL'))
            return;
        }

        A[IDOFA[i]] = sqrt(A[IDOFA[i]]); //对角元素的变换
                                         //下面是对非对角元素进行处理
        if (i != N - 1 && i < band + 50)
        {
            for (unsigned int j = IDOFA[i] + 1; j <= IDOFA[i + 1] - 1; j++)
            {
                for (unsigned int kk = 0; kk < i; kk++)
                {
                    if ((IDOFA[kk] + i - kk <= IDOFA[kk + 1] - 1) && (IDOFA[kk] + j - IDOFA[i] + i - kk <= IDOFA[kk + 1] - 1))
                    {
                        A[j] = A[j] - A[IDOFA[kk] + i - kk] * A[IDOFA[kk] + j - IDOFA[i] + i - kk];
                    }
                }
                A[j] = A[j] / A[IDOFA[i]];
            }
        }

        if (i != N - 1 && i >= (band + 50))
        {
            for (unsigned int j = IDOFA[i] + 1; j <= IDOFA[i + 1] - 1; j++)
            {
                for (unsigned int kk = i - (band + 50); kk < i; kk++)
                {
                    if ((IDOFA[kk] + i - kk <= IDOFA[kk + 1] - 1) && (IDOFA[kk] + j - IDOFA[i] + i - kk <= IDOFA[kk + 1] - 1))
                    {
                        A[j] = A[j] - A[IDOFA[kk] + i - kk] * A[IDOFA[kk] + j - IDOFA[i] + i - kk];
                    }
                }
                A[j] = A[j] / A[IDOFA[i]];
            }
        }
    }

    QLog("CHOLESKY子程序对角化结束");

	//ofstream outFile;
	
	//outFile.open("test.txt", ios::out);

    //下面是求解Y向量，在此右端向量为多组向量的组合
    for (unsigned int j = 0; j < M; j++)
    {
        float progressValue = float(j) / float(M) * 13.0f;
        setProcessBarValue(m_currentProgress + (76.0f + progressValue) * m_forwardTimeProportion / (float)INVMAX);
		if (fabs(A[0]) > 1e-15)
		{
			D[j][0] = D[j][0] / A[0];
		}
		else
		{
			D[j][0] = 0.0;
		}
        for (unsigned int i = 1; i < N; i++)
        {
            if (i < band + 50)
            {
                for (unsigned int kk = 1; kk <= i; kk++)
                {
                    if (IDOFA[kk - 1] + i - kk + 1 <= IDOFA[kk] - 1)
                    {
						if (fabs(A[IDOFA[kk - 1]]) > 0.00000000001 && fabs(D[j][kk - 1])>0.0000000001)
						{
							//outFile << "J Value: " << j << endl;
							//outFile << "I Value : " << i << endl;
							//outFile << "KK Value :" << kk << endl;
							//outFile << "idofa(kk-1)+I-KK+1 : " << IDOFA[kk - 1] + i - kk + 1 << endl;
							//outFile << "IDOFA(KK)-1: " << IDOFA[kk] - 1 << endl;
							int indexValue = IDOFA[kk - 1] + i - kk + 1;
							long double AValue = A[indexValue];
							long double DValue = D[j][kk - 1];
							
							D[j][i] = D[j][i] - AValue * DValue;
							//outFile << "D(I,J),A(idofa(kk-1)+I-kk+1),D(kk-1,J):" << D[j][i] << " : " << A[IDOFA[kk - 1] + i - kk + 1] << " : " << D[j][kk - 1] << endl;
							//outFile << "D[j][i] : " << D[j][i] << endl;
						}
                    }
                }
				//outFile << "D[j][i] : " << D[j][i] << endl;
				if (fabs(A[IDOFA[i]]) > 1e-15)
				{
					D[j][i] = D[j][i] / A[IDOFA[i]];
				}
				//outFile << "IDOFA(I):" << IDOFA[i] << endl;
				//outFile << "D(I,J),A(IDOFA(I)):" << D[j][i] << " : "  << A[IDOFA[i]] << endl;
            }
            else
            {
                for (unsigned int kk = i - (band + 50) + 1; kk <= i; kk++)
                {
                    if (IDOFA[kk - 1] + i - kk + 1 <= IDOFA[kk] - 1)
                    {
						//outFile << "idofa(kk-1)+I-KK+1,IDOFA(KK)-1):" << IDOFA[kk - 1] + i - kk + 1 << " : " << A[IDOFA[kk - 1] + i - kk + 1] << " : " << IDOFA[kk] - 1 << endl;
						
                        D[j][i] = D[j][i] - A[IDOFA[kk - 1] + i - kk + 1] * D[j][kk - 1];
						//outFile << "D(I,J),A(idofa(kk-1)+I-kk+1),D(kk-1,J):" << D[j][i] << " : " << A[IDOFA[kk - 1] + i - kk + 1] << " : " << D[j][kk - 1] << endl;
						//outFile << "D[j][i]: " << D[j][i] << endl;
                    }
                }
				//outFile << "D[j][i] : " << D[j][i] << endl;
				if (fabs(A[IDOFA[i]]) > 1e-15)
				{
					D[j][i] = D[j][i] / A[IDOFA[i]];
				}
				else
				{
					D[j][i] = 0.0;
				}
				//outFile << "IDOFA(I): " << IDOFA[i] << endl;
				//outFile << "D(I,J),A(IDOFA(I)): " << D[j][i] << " : " << A[IDOFA[i]] << endl;
            }
        }
    }

	//outFile.close();

    /*下面是求解X向量，在此右端向量为多组向量的组合*/
    N = N - 1;
    for (unsigned int j = 0; j < M; j++)
    {
        float progressValue = float(j) / float(M) * 7.0f;

        setProcessBarValue(m_currentProgress + (89.0f + progressValue) * m_forwardTimeProportion / (float)INVMAX);

        D[j][N] = D[j][N] / A[IDOFA[N]];
        for (int kk = N - 1; kk >= 0; kk--)
        {
            for (unsigned int i = kk + 1; i <= N; i++)
            {
                if (IDOFA[kk] + i - kk >= IDOFA[kk + 1])
                {
                    break;
                }
                else
                {
                    D[j][kk] = D[j][kk] - A[IDOFA[kk] + i - kk] * D[j][i];
                }
            }
            if (fabs(A[IDOFA[kk]]) > 1e-15)
                D[j][kk] = D[j][kk] / A[IDOFA[kk]];
        }
    }

    QLog("CHOLESKY子程序X向量求解结束");
}

void ForwardAndInverseProcess::A_GENERATE(long double *A, int *IDOFA)
{
    numofa    = 0;
    IDOFA[0]  = 0;
    int flag1 = 1;

    //band用来存储半带宽
    band = ID_vector[IDID[1] - 1].two - ID_vector[IDID[0]].two + 1;
    //第一行最后一个元素的位置 - 第一行第一个元素的位置，两个列号相减
    //write(*, *) band

    for (int i = 0; i < ND; i++)
    {
        float progressValue = ((float)i / (float)ND) * 2.0f;

        if (ProcessType::invert == m_currentOperationType)
        {
            setProcessBarValue(m_currentProgress + (float)(3 + (int)progressValue) / (float)INVMAX);
        }
        else
        {
            setProcessBarValue(6 + (int)progressValue * 2);
        }

        if (i < ND - band + 1)
        {
            for (int KK = i; KK <= ID_vector[IDID[i + 1] - 1].two; KK++)
            {
                int aa = IDID[i + 1];
                int bb = ID_vector[IDID[i + 1] - 1].two;

                for (int j = IDID[i]; j <= IDID[i + 1]-1; j++)
                {
                    if (KK == ID_vector[j].two)
                    {
                        A[numofa] = GA[j];
                        numofa    = numofa + 1;
                        flag1     = 1;
                        break;
                    }
                    else
                    {
                        flag1 = 0;
                    }
                }

                if (flag1 == 0)
                {
                    A[numofa] = 0.000;
                    numofa    = numofa + 1;
                }
            }

            if (i + 1 < ND)
            {
                IDOFA[i + 1] = numofa;
            }
        }
        else if (i >= (ND - band + 1))
        {
            //下面的循环是遍历GA中是否存在该元素，若存在即调用该元素，若不存在则定义为零
            for (int kk = i; kk < ND; kk++)
            {
                for (int j = IDID[i]; j <= IDID[i + 1]-1; j++)
                {
                    if (kk == ID_vector[j].two)
                    {
                        A[numofa] = GA[j];
                        numofa    = numofa + 1;
                        flag1     = 1;
                        break;
                    }
                    else
                    {
                        flag1 = 0;
                    }
                }

                if (flag1 == 0)
                {
                    A[numofa] = 0.000;
                    numofa    = numofa + 1;
                }
            }

            if (i + 1 < ND)
            {
                IDOFA[i + 1] = numofa;
            }
        }
    }
    numofa = numofa - 1;
}

/**********************************************************************************************************************/
//function:生成进度条，正演和反演进度条掌控
void ForwardAndInverseProcess::createProcessBar()
{
}

void ForwardAndInverseProcess::initProcessBar()
{
    LogSystem::instance()->getProgressBar()->show();

    //     if (m_progressBar)
    //     {
    //         m_progressBar->setGeometry(QRect(0, 0, m_parent->width() / 3, 30));
    //         m_progressBar->setRange(0, 100);
    //         m_progressBar->move(m_parent->width() / 3, m_parent->height() / 2);
    //         setProcessBarValue(0);
    //         //m_progressBar->show();
    //         LogSystem::instance()->getProgressBar()->show();
    //     }
}

void ForwardAndInverseProcess::setProcessBarValue(int value)
{
    //QString preStr = "";

    //if (ProcessType::invert == m_currentOperationType)
    //{
    //    preStr = QString::fromLocal8Bit("执行反演中请稍后...");
    //}
    //else if (ProcessType::forward == m_currentOperationType)
    //{
    //    preStr = QString::fromLocal8Bit("执行正演中请稍后...");
    //}
    //else if (ProcessType::simuforward == m_currentOperationType)
    //{
    //    preStr = QString::fromLocal8Bit("执行模拟正演中请稍后...");
    //}

    /*if (100 <= value)
    {
                 if (!LogSystem::instance()->getProgressBar()->isHidden())
                 {
                     LogSystem::instance()->getProgressBar()->hide();
                     return;
                 }
    }*/

    emit setProgressValue(value);

    // 	m_progressBar->setFormat(preStr + QString::fromLocal8Bit("当前进度为：%1%").arg(QString::number(value)));
    // 	m_progressBar->setValue(value);
    QCoreApplication::processEvents();
}

void ForwardAndInverseProcess::JA_generator(int ner, int z1, int z2, int x1, int x2, int y1, int y2, int ArrayType)
{
    int col = -1, ROW = 0; //偏导数矩阵的列号计数器
    int L              = 0;
    int circleTotalNum = dc_num / 4;
    long double a, b, c;

    long double PARTIAL_VM, PARTIAL_VN; //PARTIAL_VM, PARTIAL_VN !存放M和N点电位对某网格电阻率的偏导数
    long double *UA1 = nullptr, *UA2 = nullptr, *UA3 = nullptr, *UA4 = nullptr;
    
    if (nullptr == UA1)
    {
        UA1 = new long double[ND];
		_lock.lockForWrite();
		m_localVars.push_back(UA1);
		_lock.unlock();
        memset(UA1, 0, sizeof(long double) * ND);
    }

    if (nullptr == UA2)
    {
        UA2 = new long double[ND];
		_lock.lockForWrite();
		m_localVars.push_back(UA2);
		_lock.unlock();
        memset(UA2, 0, sizeof(long double) * ND);
    }

    if (nullptr == UA3)
    {
        UA3 = new long double[ND];
		_lock.lockForWrite();
		m_localVars.push_back(UA3);
		_lock.unlock();
        memset(UA3, 0, sizeof(long double) * ND);
    }

    if (nullptr == UA4)
    {
        UA4 = new long double[ND];
		_lock.lockForWrite();
		m_localVars.push_back(UA4);
		_lock.unlock();

        memset(UA4, 0, sizeof(long double) * ND);
    }

    //初始化DA
    if (NULL == DA)
    {
        DA = new long double *[8];
        for (unsigned int i = 0; i < 8; i++)
        {
            DA[i] = new long double[8];
            memset(DA[i], 0, sizeof(long double) * 8);
        }
    }

    if (nullptr == JA)
    {
        JA = new long double *[DATA_NUM * L_NUM];
		
        for (unsigned int i = 0; i < DATA_NUM * L_NUM; i++)
        {
            JA[i] = new long double[ner];
            memset(JA[i], 0.0, sizeof(long double) * ner);
        }
    }

    if (NULL == D)
    {
        D = new long double *[d_num * L_NUM + dc_num + 1];
        for (unsigned int i = 0; i < d_num * L_NUM + dc_num + 1; i++)
        {
            D[i] = new long double[ND];
            memset(D[i], 0.0, sizeof(long double) * ND);
        }
    }
    //forwardProTest();
    //z1,z2分别为反演区域的Z方向的起始和终止节点索引
    for (unsigned int IZ = z1; IZ <= z2; IZ++)
    {
        for (unsigned int IX = x1; IX <= x2; IX++)
        {
            for (unsigned int IY = y1; IY <= y2; IY++)
            {
                col = col + 1;
                //第(IX, IY, IZ)个单元的编号
                L = (IZ)*NX * NY + (IX)*NY + IY;
                //X方向上的边长
                a = fabs(XY[I4[L][3]][0] - XY[I4[L][0]][0]);
                b = fabs(XY[I4[L][0]][1] - XY[I4[L][1]][1]);
                c = fabs(XY[I4[L][4]][2] - XY[I4[L][0]][2]);

                //diriv0fA函数为形成某一个单元的单元刚度矩阵
                diriv0fA(a, b, c);
                //由数值正演得到下列合成观测数据M_RESULT
                //偏导数矩阵的行数计数器
                ROW = -1;

                if (ArrayType == 1)
                {
                }
                else if (ArrayType == 2)
                {
                }
                else if (ArrayType == 11)
                {
                }
                else if (ArrayType == 12)
                {
                    //circleNum为供电电极圈数
                    for (unsigned int circleNum = 0; circleNum < circleTotalNum; circleNum++)
                    {
                        for (unsigned int j = 0; j < ND; j++)
                        {
                            UA1[j] = 0.0;
                            UA2[j] = 0.0;
                            UA3[j] = 0.0;
                            UA4[j] = 0.0;
                        }

                        for (unsigned int i = 0; i < 8; i++)
                        {
                            for (unsigned int j = 0; j < 8; j++)
                            {
                                //计算A1点供电时的解向量与系数的偏导矩阵的 乘积 dc_num个供电点
                                long double dda = DA[j][i];

                                int UALIIndex   = I4[L][i];
                                int I4LJIndex   = I4[L][j];
                                long double UA1Value = UA1[UALIIndex];
                                long double UA2Value = UA2[UALIIndex];
                                long double UA3Value = UA3[UALIIndex];
                                long double UA4Value = UA4[UALIIndex];

                                long double powValue  = -pow((NRO[IZ][IY][IX]), 2);
                                long double DI4Value1 = D[d_num * L_NUM + circleNum][I4LJIndex];
                                long double DI4Value2 = D[d_num * L_NUM + circleTotalNum + circleNum][I4LJIndex];
                                long double DI4Value3 = D[d_num * L_NUM + 2 * circleTotalNum + circleNum][I4LJIndex];
                                long double DI4Value4 = D[d_num * L_NUM + 3 * circleTotalNum + circleNum][I4LJIndex];

                                UA1[UALIIndex] = UA1[UALIIndex] +
                                                 (DA[j][i] / (powValue)) * D[d_num * L_NUM + circleNum][I4LJIndex];

                                UA2[UALIIndex] = UA2[UALIIndex] +
                                                 (DA[j][i] / (powValue)) * D[d_num * L_NUM + circleTotalNum + circleNum][I4LJIndex];

                                UA3[UALIIndex] = UA3[UALIIndex] +
                                                 (DA[j][i] / (powValue)) * D[d_num * L_NUM + 2 * circleTotalNum + circleNum][I4LJIndex];

                                UA4[UALIIndex] = UA4[UALIIndex] +
                                                 (DA[j][i] / (powValue)) * D[d_num * L_NUM + 3 * circleTotalNum + circleNum][I4LJIndex];
                            }
                        }

                        for (unsigned int j = 0; j < ND; j++)
                        {
                            UA1[j] = -UA1[j];
                            UA2[j] = -UA2[j];
                            UA3[j] = -UA3[j];
                            UA4[j] = -UA4[j];
                        }

                        //k为测线数
                        for (unsigned int k = 0; k < 1; k++)
                        {
                            //j为测量点的个数
                            for (unsigned int j = 0; j < d_num; j++)
                            {
                                ROW        = ROW + 1;
                                PARTIAL_VM = 0.0;

                                for (unsigned int n = 0; n < 8; n++)
                                {
                                    long double he  = (UA1[I4[L][n]] + UA2[I4[L][n]] + UA3[I4[L][n]] + UA4[I4[L][n]]);
                                    long double ha  = D[k * 10 + j][I4[L][n]];
                                    PARTIAL_VM = PARTIAL_VM + (UA1[I4[L][n]] + UA2[I4[L][n]] + UA3[I4[L][n]] + UA4[I4[L][n]]) * D[k * 10 + j][I4[L][n]];
                                    long double a1  = UA1[I4[L][n]];
                                    long double a2  = UA2[I4[L][n]];
                                    long double a3  = UA3[I4[L][n]];
                                    long double a4  = UA4[I4[L][n]];
                                    int index  = I4[L][n];
                                    long double a5  = D[k * 10 + j][I4[L][n]];
                                }
                                if (fabs(M_RESULT[ROW][3]) > 1e-15)
                                    JA[ROW][col] = PARTIAL_VM * NRO[IZ][IY][IX] / M_RESULT[ROW][3];
                            }
                        }
                    }
                }
            }
        }
    }

	_lock.lockForWrite();

	vector<long double*>::iterator it = find(m_localVars.begin(), m_localVars.end(), UA1);

	if (m_localVars.end() != it)
	{
		m_localVars.erase(it);
	}

	SAFE_DELETE_ARRAY(UA1);

	it = find(m_localVars.begin(), m_localVars.end(), UA2);

	if (m_localVars.end() != it)
	{
		m_localVars.erase(it);
	}

	SAFE_DELETE_ARRAY(UA2);

	it = find(m_localVars.begin(), m_localVars.end(), UA3);

	if (m_localVars.end() != it)
	{
		m_localVars.erase(it);
	}

	SAFE_DELETE_ARRAY(UA3);

	it = find(m_localVars.begin(), m_localVars.end(), UA4);

	if (m_localVars.end() != it)
	{
		m_localVars.erase(it);
	}

	SAFE_DELETE_ARRAY(UA4);

	_lock.unlock();
}

void ForwardAndInverseProcess::SHM_OP(unsigned int NER, unsigned int Z1, unsigned int Z2, unsigned int X1, unsigned int X2, unsigned int Y1, unsigned int Y2, long double MIU, long double *SHM, int **IDOFSHM)
{
    ///< 定义需要形状约束的单元
    unsigned int SHAPE_NUM1 = 0;
    int SHAPE_NER[100];
    memset(SHAPE_NER, 0, sizeof(int) * 100);
    int COL = -1;

    int SX1  = 9;
    int SX2  = 10;
    int SY1  = 14;
    int SY2  = 19;
    int SZ1  = 12;
    int SZ2  = 13;
    int SX11 = 9;
    int SX22 = 10;
    int SY11 = 14;
    int SY22 = 19;
    int SZ11 = 17;
    int SZ22 = 18;

    ///< 在反演区域的编号为
    for (int IZ = SZ1; IZ <= SZ2; IZ++)
    {
        for (int IX = SX1; IX <= SX2; IX++)
        {
            for (int IY = SY1; IY <= SY2; IY++)
            {
                SHAPE_NER[SHAPE_NUM1] = (IZ - Z1) * (X2 - X1 + 1) * (Y2 - Y1 + 1) + (IX - X1) * (Y2 - Y1 + 1) + IY - Y1;
                SHAPE_NUM1++;
            }
        }
    }

    for (int IZ = SZ11; IZ <= SZ22; IZ++)
    {
        for (int IX = SX11; IX <= SX22; IX++)
        {
            for (int IY = SY11; IY <= SY22; IY++)
            {
                SHAPE_NER[SHAPE_NUM1] = (IZ - Z1) * (X2 - X1 + 1) * (Y2 - Y1 + 1) + (IX - X1) * (Y2 - Y1 + 1) + IY - Y1;
                SHAPE_NUM1++;
            }
        }
    }
    SHAPE_NUM1--;
    NUMOFSHM = 0; //光滑度矩阵的一维存储模式的计数器
    for (int IZ = Z1; IZ <= Z2; IZ++)
    {
        for (int IX = X1; IX <= X2; IX++)
        {
            for (int IY = Y1; IY <= Y2; IY++)
            {
                COL++;
                if (IZ >= SZ1 && IZ <= SZ2)
                {
                    if (IX >= SX1 && IX <= SX2)
                    {
                        if (IY >= SY1 && IY <= SY2)
                        {
                            for (int I = 0; I <= SHAPE_NUM1; I++)
                            {
                                IDOFSHM[NUMOFSHM][0] = COL;
                                IDOFSHM[NUMOFSHM][1] = SHAPE_NER[I];

                                if (SHAPE_NER[I] == COL)
                                {
                                    SHM[NUMOFSHM] = MIU * 100;
                                }
                                else
                                {
                                    SHM[NUMOFSHM] = -100 * MIU / (SHAPE_NUM1 + 1);
                                }
                                NUMOFSHM++;
                            }
                        }
                    }
                }

                if (IZ >= SZ11 && IZ <= SZ22)
                {
                    if (IX >= SX11 && IX <= SX22)
                    {
                        if (IY >= SY11 && IY <= SY22)
                        {
                            for (int I = 0; I <= SHAPE_NUM1; I++)
                            {
                                IDOFSHM[NUMOFSHM][0] = COL;
                                IDOFSHM[NUMOFSHM][1] = SHAPE_NER[I];
                                if (SHAPE_NER[I] == COL)
                                {
                                    SHM[NUMOFSHM] = MIU * 20;
                                }
                                else
                                {
                                    SHM[NUMOFSHM] = -20 * MIU / (SHAPE_NUM1 + 1);
                                }

                                NUMOFSHM++;
                            }
                        }
                    }
                }
            }
        }
    }
    NUMOFSHM--;
}

void ForwardAndInverseProcess::SM_OPERATOR(unsigned int ner, int z1, int z2, int x1, int x2, int y1, int y2, int SM_TYPE)
{
    unsigned int col = 0; //光滑度矩阵的计数器
    unsigned int L   = 0;
    int *IDIDOFSM    = NULL;
    IDIDOFSM         = new int[ner];

	_lock.lockForWrite();
	m_localIntVars.push_back(IDIDOFSM);
	_lock.unlock();

    NUMOFSM          = 0; //光滑度矩阵的一维存储模式的计数器
    long double ADD;
    if (SM_TYPE == 1)
    {
        ADD = 0.00;
        for (int IZ = z1; IZ < z2; IZ++)
        {
            for (int IX = x1; IX < x2; IX++)
            {
                for (int IY = y1; IY < y2; IY++)
                {
                    col = col + 1;
                    L   = (IZ - 1) * NX * NY + (IX - 1) * NY + IY;
                    //SM数组的二级索引数组,将每行的第一个元素的列号作为二级索引值
                    IDIDOFSM[col] = NUMOFSM;

                    //下面将第COL个反演网格与前后左右上下的网格的距离作为光滑度因子放入光滑度矩阵中
                    if (IY - 1 >= y1)
                    {
                        SM[NUMOFSM]        = LAMDA / sqrt(YL[NY + 1 - IY] / 2.0 + YL[NY + 1 - (IY - 1)] / 2.0);
                        IDOFSM[NUMOFSM][0] = col;
                        IDOFSM[NUMOFSM][1] = col;
                    }

                    if (IY + 1 <= y2)
                    {
                        SM[NUMOFSM]        = LAMDA / sqrt(YL[NY + 1 - IY] / 2.0 + YL[NY + 1 - (IY + 1)] / 2.0);
                        IDOFSM[NUMOFSM][0] = col;
                        IDOFSM[NUMOFSM][1] = col;
                    }

                    if (IX - 1 >= x1)
                    {
                        SM[NUMOFSM]        = LAMDA / sqrt(XL[IX] / 2.0 + XL[(IX - 1)] / 2.0);
                        IDOFSM[NUMOFSM][0] = col;
                        IDOFSM[NUMOFSM][1] = col - ((y2 - y1) + 1);
                    }

                    if (IX + 1 <= x2)
                    {
                        SM[NUMOFSM]        = LAMDA / sqrt(XL[IX] / 2.0 + XL[(IX + 1)] / 2.0);
                        IDOFSM[NUMOFSM][0] = col;
                        IDOFSM[NUMOFSM][1] = col - ((y2 - y1) + 1);
                    }

                    if (IZ - 1 >= z1)
                    {
                        SM[NUMOFSM]        = LAMDA / sqrt(ZL[IZ] / 2.0 + ZL[(IZ - 1)] / 2.0);
                        IDOFSM[NUMOFSM][0] = col;
                        IDOFSM[NUMOFSM][1] = col - ((y2 - y1) + 1);
                    }

                    if (IZ + 1 <= z2)
                    {
                        SM[NUMOFSM]        = LAMDA / sqrt(ZL[IZ] / 2.0 + ZL[(IZ + 1)] / 2.0);
                        IDOFSM[NUMOFSM][0] = col;
                        IDOFSM[NUMOFSM][1] = col - ((x2 - x1) + 1) * (y2 - y1 + 1);
                    }
                    ADD     = ADD + SM[NUMOFSM];
                    NUMOFSM = NUMOFSM + 1;

                    SM[NUMOFSM]        = -ADD;
                    IDOFSM[NUMOFSM][0] = col;
                    IDOFSM[NUMOFSM][1] = col;
                    NUMOFSM            = NUMOFSM + 1;
                    ADD                = 0.0;
                }
            }
        }
        NUMOFSM = NUMOFSM + 1;
    }
    else if (SM_TYPE == 2)
    {
        col       = 0;
        NUMOFSM   = 0;
        long double XX = 0;
        long double YY = 0;
        for (int IZ = z1; IZ <= z2; IZ++)
        {
            for (int IX = x1; IX <= x2; IX++)
            {
                for (int IY = y1; IY <= y2; IY++)
                {
                    col = col + 1;
                    XX  = fabs(IX - (x2 + x1) / 2);
                    YY  = fabs(IY - (y2 + y1) / 2);

                    if (GlobalParam::instance()->getInversionParaSetting().UseLamda)
                    {
                        LAMDA = GlobalParam::instance()->getInversionParaSetting().Lamda;
                    }
                    else
                    {
                        LAMDA = 1 / ((IZ - z1 + 1) + 1.0) + 0.2;
                    }

                    //MAMDA = ((1/((IZ-z1+1)+1.0)+1/(XX+1.0)+1/(YY+1.0))/3)+0.9;

                    //圈定一个范围然后变小lamda
                    L = (IZ)*NX * NY + (IX)*NY + IY;

                    //下面将第COL个反演网格与前后左右上下的网格的距离作为光滑度因子放入光滑度矩阵中
                    if (IY - 1 >= y1)
                    {
                        SM[NUMOFSM]        = LAMDA / 6.0;
                        IDOFSM[NUMOFSM][0] = col;
                        IDOFSM[NUMOFSM][1] = col - 1;
                        NUMOFSM            = NUMOFSM + 1;
                    }
                    if (IY + 1 <= y2)
                    {
                        SM[NUMOFSM]        = LAMDA / 6.0;
                        IDOFSM[NUMOFSM][0] = col;
                        IDOFSM[NUMOFSM][1] = col + 1;
                        NUMOFSM            = NUMOFSM + 1;
                    }

                    if (IX - 1 >= x1)
                    {
                        SM[NUMOFSM]        = LAMDA / 6.0;
                        IDOFSM[NUMOFSM][0] = col;
                        IDOFSM[NUMOFSM][1] = col - ((y2 - y1) + 1);
                        NUMOFSM            = NUMOFSM + 1;
                    }
                    if (IX + 1 <= x2)
                    {
                        SM[NUMOFSM]        = LAMDA / 6.0;
                        IDOFSM[NUMOFSM][0] = col;
                        IDOFSM[NUMOFSM][1] = col + ((y2 - y1) + 1);
                        NUMOFSM            = NUMOFSM + 1;
                    }

                    if (IZ - 1 >= z1)
                    {
                        SM[NUMOFSM]        = LAMDA / 6.0;
                        IDOFSM[NUMOFSM][0] = col;
                        IDOFSM[NUMOFSM][1] = col - ((x2 - x1) + 1) * (y2 - y1 + 1);
                        NUMOFSM            = NUMOFSM + 1;
                    }
                    if (IZ + 1 <= z2)
                    {
                        SM[NUMOFSM]        = LAMDA / 6.0;
                        IDOFSM[NUMOFSM][0] = col;
                        IDOFSM[NUMOFSM][1] = col + ((x2 - x1) + 1) * (y2 - y1 + 1);
                        NUMOFSM            = NUMOFSM + 1;
                    }

                    SM[NUMOFSM]        = -1.0 * LAMDA;
                    IDOFSM[NUMOFSM][0] = col;
                    IDOFSM[NUMOFSM][1] = col;
                    NUMOFSM            = NUMOFSM + 1;
                }
            }
        }
        NUMOFSM = NUMOFSM - 1;
    }

	_lock.lockForWrite();
	vector<int*>::iterator it_int = find(m_localIntVars.begin(), m_localIntVars.end(), IDIDOFSM);

	if (m_localIntVars.end() != it_int)
	{
		m_localIntVars.erase(it_int);
	}
	_lock.unlock();

	SAFE_DELETE_ARRAY(IDIDOFSM);
}

void ForwardAndInverseProcess::diriv0fA(long double a, long double b, long double c)
{
    long double KK1[3];
    memset(KK1, 0.0, sizeof(long double) * 3);

    long double AA = 0.0, BB = 0.0, CC = 0.0;

    long double K1[9][3] =
        {
            {4.0, 4.0, 4.0},
            {2.0, -4.0, 2.0},
            {-2.0, -2.0, 1.0},
            {-4.0, 2.0, 2.0},
            {2.0, 2.0, -4.0},
            {1.0, -2.0, -2.0},
            {-1.0, -1.0, -1.0},
            {-2.0, 1.0, -2.0},
            {4.0, 4.0, 4.0}
            /*{ 4.0, 2.0, -2.0,-4.0, 2.0, 1.0, -1.0, -2.0, 4.0 },
		{ 4.0, -4.0,-2.0, 2.0, 2.0, -2.0,-1.0, 1.0,  4.0 },
		{ 4.0, 2.0, 1.0,  2.0, -4.0,-2.0,-1.0, -2.0, 4.0 }*/
        };

    long double K2[9][3] =
        {
            {-4.0, 2.0, 2.0},
            {-2.0, -2.0, 1.0},
            {1.0, -2.0, -2.0},
            {2.0, 2.0, -4.0},
            {-2.0, 1.0, -2.0},
            {-1.0, -1.0, -1.0},
            {4.0, 4.0, 4.0},
            {2.0, -4.0, 2.0},
            {-1.0, -1.0, -1.0}
            /*{ -4.0,-2.0,1.0,2.0,-2.0,-1.0,4.0,2.0,-1.0},
		{ 2.0,   -2.0,-2.0,2.0,1.0,-1.0,4.0,-4.0,-1.0},
		{ 2.0,    1.0,-2.0,-4.0,-2.0,-1.0,4.0,2.0,-1.0}*/
        };

    long double K3[9][3] =
        {
            {-2.0, 1.0, -2.0},
            {2.0, 2.0, -4.0},
            {1.0, -2.0, -2.0},
            {4.0, 4.0, 4.0},
            {-2.0, 1.0, -2.0},
            {-1.0, -1.0, -1.0},
            {1.0, -2.0, -2.0},
            {2.0, 2.0, -4.0},
            {4.0, 4.0, 4.0}
            /*{ -2.0,2.0,1.0, 4.0,-2.0,-1.0,1.0,2.0,4.0 },
		{   1.0, 2.0,-2.0,4.0,1.0,-1.0,-2.0,2.0,4.0 },
		{   -2.0,-4.0,-2.0,4.0,-2.0,-1.0,-2.0,-4.0,4.0}*/
        };

    long double K4[9][3] =
        {
            {2.0, -4.0, 2.0},
            {-2.0, -2.0, 1.0},
            {-4.0, 2.0, 2.0},
            {4.0, 4.0, 4.0},
            {-4.0, 2.0, 2.0},
            {-2.0, -2.0, 1.0},
            {4.0, 4.0, 4.0},
            {2.0, -4.0, 2.0},
            {4.0, 4.0, 4.0}
            /*{ 2.0, -2.0,-4.0,4.0,-4.0,-2.0,4.0, 2.0,4.0 },
		{   -4.0,-2.0,2.0, 4.0, 2.0,-2.0,4.0,-4.0,4.0 },
		{   2.0, 1.0, 2.0, 4.0, 2.0,1.0, 4.0, 2.0,4.0 }*/
        };

    if (fabs(a) > 1e-15)
        AA = b * c / (36.0 * a);
    if (fabs(b) > 1e-15)
        BB = a * c / (36.0 * b);
    if (fabs(c) > 1e-15)
        CC = a * b / (36.0 * c);

    KK1[0] = AA;
    KK1[1] = BB;
    KK1[2] = CC;

    long double *kValue = MatmulOne(K1, 3, 9, KK1, 3);
	_lock.lockForWrite();
	m_localVars.push_back(kValue);
	_lock.unlock();
    for (unsigned int i = 0; i < 8; i++)
    {
        DA[0][i] = kValue[i];
    }
    DA[1][1] = kValue[8];

    long double *kTwoValue = MatmulOne(K2, 3, 9, KK1, 3);

	_lock.lockForWrite();
	m_localVars.push_back(kTwoValue);
	_lock.unlock();
    DA[1][2]          = kTwoValue[0];
    DA[1][3]          = kTwoValue[1];
    DA[1][4]          = kTwoValue[2];
    DA[1][5]          = kTwoValue[3];
    DA[1][6]          = kTwoValue[4];
    DA[1][7]          = kTwoValue[5];
    DA[2][2]          = kTwoValue[6];
    DA[2][3]          = kTwoValue[7];
    DA[2][4]          = kTwoValue[8];

    long double *kThreeValue = MatmulOne(K3, 3, 9, KK1, 3);
	_lock.lockForWrite();
	m_localVars.push_back(kThreeValue);
	_lock.unlock();
    DA[2][5]            = kThreeValue[0];
    DA[2][6]            = kThreeValue[1];
    DA[2][7]            = kThreeValue[2];
    DA[3][3]            = kThreeValue[3];
    DA[3][4]            = kThreeValue[4];
    DA[3][5]            = kThreeValue[5];
    DA[3][6]            = kThreeValue[6];
    DA[3][7]            = kThreeValue[7];
    DA[4][4]            = kThreeValue[8];

    long double *kFourValue = MatmulOne(K4, 3, 9, KK1, 3);
	_lock.lockForWrite();
	m_localVars.push_back(kFourValue);
	_lock.unlock();
    DA[4][5]           = kFourValue[0];
    DA[4][6]           = kFourValue[1];
    DA[4][7]           = kFourValue[2];
    DA[5][5]           = kFourValue[3];
    DA[5][6]           = kFourValue[4];
    DA[5][7]           = kFourValue[5];
    DA[6][6]           = kFourValue[6];
    DA[6][7]           = kFourValue[7];
    DA[7][7]           = kFourValue[8];

    for (int i = 1; i < 8; i++)
    {
        DA[i][0] = DA[0][i];
    }

    for (int i = 2; i < 8; i++)
    {
        DA[i][1] = DA[1][i];
    }

    for (int i = 3; i < 8; i++)
    {
        DA[i][2] = DA[2][i];
    }

    for (int i = 4; i < 8; i++)
    {
        DA[i][3] = DA[3][i];
    }

    for (int i = 5; i < 8; i++)
    {
        DA[i][4] = DA[4][i];
    }

    for (int i = 6; i < 8; i++)
    {
        DA[i][5] = DA[5][i];
    }

    DA[7][6] = DA[6][7];

	_lock.lockForWrite();

	vector<long double*>::iterator it = find(m_localVars.begin(), m_localVars.end(), kValue);

	if (m_localVars.end() != it)
	{
		m_localVars.erase(it);
	}

	SAFE_DELETE_ARRAY(kValue);

	it = find(m_localVars.begin(), m_localVars.end(), kTwoValue);

	if (m_localVars.end() != it)
	{
		m_localVars.erase(it);
	}

	SAFE_DELETE_ARRAY(kTwoValue);

	it = find(m_localVars.begin(), m_localVars.end(), kThreeValue);

	if (m_localVars.end() != it)
	{
		m_localVars.erase(it);
	}

	SAFE_DELETE_ARRAY(kThreeValue);

	it = find(m_localVars.begin(), m_localVars.end(), kFourValue);

	if (m_localVars.end() != it)
	{
		m_localVars.erase(it);
	}

	SAFE_DELETE_ARRAY(kFourValue);

	_lock.unlock();
}

void ForwardAndInverseProcess::MultiplySM(int NER, long double *SM, long double *X, long double *Y, int **IDOFSM, int NUMOFSM, int IPATH)
{
    for (int i = 0; i < NER; i++)
    {
        Y[i] = 0.0;
    }
    //下面计算Y=SM*X
    if (IPATH == 1)
    {
        for (int i = 0; i <= NUMOFSM; i++)
        {
            int IDOFSMValue0 = IDOFSM[i][0];
            int IDOFSMValue1 = IDOFSM[i][1];

            long double smValue = SM[i];
            long double xValue  = X[IDOFSMValue1 - 1];

            Y[IDOFSM[i][0] - 1] = Y[IDOFSM[i][0] - 1] + SM[i] * X[IDOFSM[i][1] - 1];
        }
    }
    //下面计算Y = TRANS(SM)*X
    else if (IPATH == 2)
    {
        for (int i = 0; i <= NUMOFSM; i++)
        {
            Y[IDOFSM[i][1] - 1] = Y[IDOFSM[i][1] - 1] + SM[i] * X[IDOFSM[i][0] - 1];
        }
    }
}

void ForwardAndInverseProcess::DMURRv1(int nra, int nca, long double **a, int nx, long double *x, int nz, long double *z, int ipath)
{
    for (int i = 0; i < nz; i++)
    {
        z[i] = 0.0;
    }

    if (ipath == 1)
    {
        for (int i = 0; i < nra; i++)
        {
            for (int j = 0; j < nca; j++)
            {
                z[i] = z[i] + a[i][j] * x[j];
            }
        }
    }
    else if (ipath == 2)
    {
        for (int j = 0; j < nca; j++)
        {
            for (int i = 0; i < nra; i++)
            {
                z[j] = z[j] + a[i][j] * x[i];
            }
        }
    }
}

void ForwardAndInverseProcess::onResize()
{
}

void ForwardAndInverseProcess::autoGenForwardMulti()
{
    if (this->isRunning())
        this->stopThread();

    m_currentOperationType = ProcessType::auto_gen_forward;

    initProcessBar();

    start(QThread::NormalPriority);
}

void ForwardAndInverseProcess::autoGenInvertMulti()
{
    if (this->isRunning())
        this->stopThread();

    m_currentOperationType = ProcessType::auto_gen_invert;

    initProcessBar();
    start(QThread::NormalPriority);
}

void ForwardAndInverseProcess::initialization()
{
    createProcessBar();
    m_preOperationType     = ProcessType::none;
    m_pModelSubdivison     = NULL; //模型剖分类
    m_resultPointArray     = NULL;
    m_isReselectDialogOver = false;
	m_forwardProcessSuccess = false;
    m_currentOperationType = ProcessType::none;

    m_firstInitData = false;
    SM_TYPE         = 0;
    INVMAX          = 0;
    MN              = 0.5;
    P_DIST          = 1;
    L_DIST          = 2;
    BoundL          = 0.0;
    BoundU          = 0.0;
    EPS             = 0.0;
    JPCG_ITMAX      = 0.0;
    JPCG_RELERR     = 0.0;
    ITER_NUM        = 0;

    RINV     = NULL;
    RINV2    = NULL;
    BINV     = NULL;
    PINV     = NULL;
    YINV1    = NULL;
    YINV2    = NULL;
    ZINV     = NULL;
    ZINV2    = NULL;
    ZZINV    = NULL;
    ZZINV1   = NULL;
    ZZINV2   = NULL;
    SM       = NULL;
    DA       = NULL;
    SHM      = NULL;
    IDID     = NULL;
    D_POINT  = NULL;
    DAT      = NULL;
    GA       = NULL;
    GA1      = NULL;
    KE1      = NULL;
    KE2      = NULL;
    DA       = NULL;
    BoundU1  = NULL;
    IDOFSHM  = NULL;
    W_A      = NULL;
    X        = NULL;
    Y        = NULL;
    Z        = NULL;
    XL       = NULL;
    YL       = NULL;
    ZL       = NULL;
    M_RESULT = NULL;
    M_RESULT = NULL;
    IDOFSM   = NULL;
    D        = NULL;
    I4       = NULL;
    JA       = NULL;
    XY       = NULL;
    NRO      = NULL;

    loadDPCGRCLibrary();
}

void ForwardAndInverseProcess::reset()
{
    m_currentOperationType = ProcessType::none;
}

void ForwardAndInverseProcess::releaseMemory()
{
    SAFE_DELETE_ARRAY(RINV);
    SAFE_DELETE_ARRAY(RINV2);
    SAFE_DELETE_ARRAY(BINV);
    SAFE_DELETE_ARRAY(PINV);
    SAFE_DELETE_ARRAY(YINV1);
    SAFE_DELETE_ARRAY(YINV2);
    SAFE_DELETE_ARRAY(ZINV);
    SAFE_DELETE_ARRAY(ZINV2);
    SAFE_DELETE_ARRAY(ZZINV);
    SAFE_DELETE_ARRAY(ZZINV1);
    SAFE_DELETE_ARRAY(ZZINV2);
    SAFE_DELETE_ARRAY(SM);
    SAFE_DELETE_ARRAY(SHM);
    SAFE_DELETE_ARRAY(IDID);
    SAFE_DELETE_ARRAY(D_POINT);
    SAFE_DELETE_ARRAY(DAT);
    SAFE_DELETE_ARRAY(GA);
    SAFE_DELETE_ARRAY(GA1);

	//释放内存
	if (NULL != delta_m)
	{
		delete[] delta_m;
		delta_m = NULL;
	}

	if (NULL != DELTA_D)
	{
		delete[] DELTA_D;
		DELTA_D = NULL;
	}

    if (NULL != KE1)
    {
        for (unsigned int i = 0; i < 8; i++)
        {
            SAFE_DELETE_ARRAY(KE1[i]);
        }
        SAFE_DELETE_ARRAY(KE1);
    }

    if (NULL != KE2)
    {
        for (unsigned int i = 0; i < 8; i++)
        {
            SAFE_DELETE_ARRAY(KE2[i]);
        }
        SAFE_DELETE_ARRAY(KE2);
    }

    if (NULL != DA)
    {
        for (unsigned int i = 0; i < 8; i++)
        {
            SAFE_DELETE_ARRAY(DA[i]);
        }
        SAFE_DELETE_ARRAY(DA);
    }

    if (NULL != BoundU1)
    {
        for (unsigned int i = 0; i < NZ; i++)
        {
            for (unsigned int j = 0; j < NY; j++)
            {
                SAFE_DELETE_ARRAY(BoundU1[i][j]);
            }
            SAFE_DELETE_ARRAY(BoundU1[i]);
        }
        SAFE_DELETE_ARRAY(BoundU1);
    }

    //删除动态内存
    if (NULL != IDOFSHM)
    {
        for (unsigned int i = 0; i < 14 * m_ner; i++)
        {
            SAFE_DELETE_ARRAY(IDOFSHM[i]);
        }
        SAFE_DELETE_ARRAY(IDOFSHM);
    }

    //////删除父类内存
    SAFE_DELETE_ARRAY(W_A);
    SAFE_DELETE_ARRAY(X);
    SAFE_DELETE_ARRAY(Y);
    SAFE_DELETE_ARRAY(Z);
    SAFE_DELETE_ARRAY(XL);
    SAFE_DELETE_ARRAY(YL);
    SAFE_DELETE_ARRAY(ZL);

    if (NULL != M_RESULT)
    {
        for (unsigned int i = 0; i < DATA_NUM * L_NUM; i++)
        {
            SAFE_DELETE_ARRAY(M_RESULT[i]);
        }
        SAFE_DELETE_ARRAY(M_RESULT);
    }

    if (NULL != IDOFSM)
    {
        for (unsigned int i = 0; i < 7 * m_ner; i++)
        {
            SAFE_DELETE_ARRAY(IDOFSM[i]);
        }
        SAFE_DELETE_ARRAY(IDOFSM);
    }

    if (NULL != D)
    {
        for (unsigned int i = 0; i < (d_num * L_NUM + dc_num + 1); i++)
        {
            SAFE_DELETE_ARRAY(D[i]);
        }
        SAFE_DELETE_ARRAY(D);
    }

    if (NULL != I4)
    {
        for (unsigned int i = 0; i < NE; i++)
        {
            SAFE_DELETE_ARRAY(I4[i]);
        }
        SAFE_DELETE_ARRAY(I4);
    }

    if (NULL != JA)
    {
        for (unsigned int i = 0; i < DATA_NUM * L_NUM; i++)
        {
            SAFE_DELETE_ARRAY(JA[i]);
        }
        SAFE_DELETE_ARRAY(JA);
    }

    if (NULL != XY)
    {
        for (unsigned int i = 0; i < ND; i++)
        {
            SAFE_DELETE_ARRAY(XY[i]);
        }
        SAFE_DELETE_ARRAY(XY);
    }

    if (NULL != NRO)
    {
        for (unsigned int i = 0; i < NZ; i++)
        {
            for (unsigned int j = 0; j < NY; j++)
            {
                SAFE_DELETE_ARRAY(NRO[i][j]);
            }
            SAFE_DELETE_ARRAY(NRO[i]);
        }
        SAFE_DELETE_ARRAY(NRO);
    }
}
}