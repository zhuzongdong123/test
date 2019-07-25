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
    //��ʼ�����ݽ����������
    void initForwardData();
	void releaseMemory();

    bool initProcessData(); //��ʼ�����ݷ���ģ������
    void setINVMAX(int value);

    void Model(unsigned int NX, unsigned int NY, unsigned int NZ, long double *X, long double *Y, long double *Z, unsigned int ND, unsigned int NE, long double **XY, int **I4);

    std::vector<double> &getForwardResult() { return m_forwardResult; };

    void setDat(std::vector<double> result);

    void process(ProcessType vType);
    void onResize();

    void autoGenForwardMulti();
    void autoGenInvertMulti();
    void autoGenForward();   //�Զ�������
    void autoGenInversion(); //�Զ�������

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
    //function:���ݺ���
    void doForwardProcess(); //��ʼ����

    void Kzong();

    /**************************************************************************************************/
    //function:
    //SGM1:���������ʣ�SGM2�쳣������
    void kE_2(long double a, long double b, long double c, long double SGM1, long double SGM2, long double KEB1[8][8], long double KEB2[8][8], int FLAG, long double H, long double L);

    void UU0(int I_NUM, long double *U0);

    /**
	  * @brief ������GA������X��ˣ��õ�����Y
	  *
	  * @param [in] ND ÿ����Ԫ�ĵ�����ֵ
	  * @param [in] X ����Ԫ����x����߳�
	  * @param [out] Y ����Ԫ����y����߳�
	  * @param [in] ID ����Ԫ����y����߳�
	  * @param [in] NUM x����
	  */
    void MULTIPLY(int ND, long double *GA, long double *X, long double *Y, int NUM);

    /**************************************************************************************************/
    //function:
    //SGM1:���������ʣ�SGM2�쳣������
    void kE_1(long double a, long double b, long double c, long double SGM1, long double SGM2);

    //������CHOLESKY����������ӳ���
    //���ӳ���Ϊ����˹�������Գ�����������洢����Խ�С���ҿ�һ���������Ҷ������ķ���
    void CHOLESKY(long double *A, int N, int M, int *IDOFA);
    void ID_GENERATOR(unsigned int NX, unsigned int NY, unsigned int NZ, unsigned int ND, unsigned int NE, int *IDID, unsigned int &NUM);
    void A_GENERATE(long double *A, int *IDOFA);
    /////////////////////////////////////
    void JA_generator(int ner, int z1, int z2, int x1, int x2, int y1, int y2, int ArrayType);
    /**
	  * @brief ��С���˷��ݷ�����״Լ����������ӳ���
	  *
	  * @param [in] NRO ÿ����Ԫ�ĵ�����ֵ
	  * @param [in] NX ����Ԫ����x����߳�
	  * @param [in] NY ����Ԫ����y����߳�
	  * @param [in] NZ ����Ԫ����y����߳�
	  * @param [in] X1 x����
	  * @param [in] Y1 y����
	  * @param [in] Z1 z����
	  * @param [in] X2 x����
	  * @param [in] Y2 y����
	  * @param [in] Z2 z����
	  * @param [in] MIU ��֪��
	  * @param [in] SHM ��֪��
	  * @param [out] IDOFSHM ��֪��
	  * @param [out] NUMOFSHM ��֪��
	  */
    void SHM_OP(unsigned int NER, unsigned int Z1, unsigned int Z2, unsigned int X1, unsigned int X2, unsigned int Y1, unsigned int Y2,
                long double MIU, long double *SHM, int **IDOFSHM);

    /*******************************************************************************************/
    //function:
    //PARAMETER:ner:Ϊ���ݵ�����Ԫ����
    //long double PRECISION SM(7 * NER), SM_X(7 * NER), SM_Y(7 * NER), SM_Z(7 * NER)!�⻬�Ⱦ���
    //long double PRECISION SFM(7 * NER)!��ʽԼ������
    //INTEGER IDOFSFM(2, 7 * NER), NUMOFSFM !��ʽԼ����������
    void SM_OPERATOR(unsigned int ner, int z1, int z2, int x1, int x2, int y1, int y2, int SM_TYPE);
    void diriv0fA(long double a, long double b, long double c);

    //����˵��:һά����Ԫ��ѹ���⻬�Ⱦ���SM���������ĳ˵��ӳ���
    //NERӦ����y�����ĸ���
    //SM��һ����֪��һά����
    //X��һ����֪��һά����
    //Y��һ����֪��һά����,�����ڴ˺����б����³�ʼ���󣬸�ֵ��
    //IDOFSM��һ����֪�Ķ�ά���飬Ӧ����ȫ�ֱ���
    //NUMOFSM����⻬�Ⱦ����һά�洢ģʽ�ļ�����
    //IPATH������㷽�̵��Ҷ���
    void MultiplySM(int NER, long double *SM, long double *X, long double *Y, int **IDOFSM, int NUMOFSM, int IPATH);

    //����˵����ax=z!!!!!!�����������
    //nra�Ǿ��������
    //nca�Ǿ��������
    //a��һ����֪����(nra��nca��������)
    //nx������x�ĸ���������С
    //x��һ����֪����
    //nz������ֵ����z�ĸ���
    //z������ֵ�������ŵ��ǳ˵Ľ�����������ڲ�new��
    //ipath������㷽�̵��Ҷ���
    void DMURRv1(int nra, int nca, long double **a, int nx, long double *x, int nz, long double *z, int ipath);

  private:
    void createProcessBar();
    void initProcessBar();
    void setProcessBarValue(int value);
    void initialization();
    void reset();

  private:
    bool m_isReselectDialogOver;
    bool m_firstInitData; //�����������Ƿ��ʼ��
	bool m_forwardProcessSuccess; //���ݳɹ���ǣ������Ƿ���з���

    ProcessType m_currentOperationType;
    ProcessType m_preOperationType;

    double **M_RESULT; //(4, DATA_NUM*L_NUM)!ʵ���ӵ��������ݺ�װ��ϵ������
    double ***NRO;     //ÿ����Ԫ�ĵ�����ֵ
    int **IDOFSM;      //INTEGER IDOFSFM(2, 7 * NER), NUMOFSFM !��ʽԼ����������
    long double **D;  //��cholesky����������ʱΪ���鷽�̵��Ҷ���, ���ʱΪ���̵Ľ�
    int **I4;    //���е�Ԫ���õĶ�������
    long double **JA; // JA(DATA_NUM*L_NUM, NER)!�ֱ�洢�ӵ����ʺ͹۲��λ��ģ�ε�ƫ����

    long double *W_A; //ƫ���������Ȩ��
    long double **XY; //ÿ���ڵ����������
    long double *X;   //x�������нڵ�����
    long double *Y;   //y�������нڵ�����
    long double *Z;   //z�������нڵ�����
    long double *XL;  //ģ����X�������е�Ԫ�ı߳�
    long double *YL;  //ģ����Y�������е�Ԫ�ı߳�
    long double *ZL;  //�洢ģ����Z�������е�Ԫ�ı߳�

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

    long double ***BoundU1; //ÿ����Ԫ�ĵ�����ֵ
    long double *SM;
    long double **KE1 = NULL; //����
    long double **KE2 = NULL; //����
    long double **DA  = NULL; //����
    long double *SHM;
    int **IDOFSHM;

    unsigned int P_DIST; //�����缫֮��ļ�ࣨ���˶��ٸ��߳���
    unsigned int L_DIST; //�����缫֮��ļ�ࣨ���˶��ٸ��߳���
    unsigned int I_NUMX; //�����Դ��ġ�X���ꡯ
    unsigned int I_NUMY; //�����Դ��ġ�Y���ꡯ
    unsigned int I_NUMZ; //�����Դ��ġ�Z���ꡯ
    unsigned int NUM;    //GA�����ʵ�ʴ�С��A�����ʵ�ʴ�С
    unsigned int INVMAX;
    unsigned int ND;       //�ڵ�����
    unsigned int NX;       //����Ԫ����x����߳�
    unsigned int NY;       //����Ԫ����y����߳�
    unsigned int NZ;       //����Ԫ����z����߳�
    unsigned int NE;       //��Ԫ����
    unsigned int dc_num;   //�������ε缫(Ȧ���缫��)
    unsigned int d_num;    //���ܶȵ編�ĵ缫����
    int DATA_NUM; //�Ը��ܶȵ編���ݵ�������Ĺ���
    int L_NUM;    //������

    int *IDID;      //GA��GA1�Ķ�����������
    int *D_POINT;   //�洢������͹۲��Ľڵ��
    int ARRAY_TYPE; //װ�����ͱ��
    int m_ner;
    int I_num;  //�����Դ��Ľڵ��ż���ŵġ����ꡯ
    int band;   //�����洢�����
    int numofa; //A�����ʵ�ʴ�С
    int NUMOFSM;
    int JPCG_ITMAX; //PCG���ⷽ��ʱ�ĵ�����������
    int SM_TYPE;
    int ITER_NUM;
    int NUMOFSHM;
    int INV_METHOD;
    int DATA_WEIGHT;         //���ݼ�Ȩ
    int potentialDeviceType; ///< ��λװ��ѡ�񿪹�

    float m_forwardTimeProportion;
    float m_increaseDensity;
    float m_currentProgress;
    long double LAMDA;       //��������
    long double BoundU;      ///< ����ȡֵ������
    long double BoundL;      ///< ����ȡֵ������
    long double II;          //�����Ĵ�С
    long double C_II;        //�����Ĵ�С
    long double JPCG_RELERR; //PCG���ⷽ��ʱ�������������
    long double JPCG_EPS;    //PCG���ⷽ��ʱ�ľ�����
    long double EPS;         //��С���˷����е������������
    long double EPS_RSM;     //��С�������������������
    long double SGM0;        //����缫�����ĵ�����ֵ
    long double MN;          //�洢��С�缫���

    long double *DAT; //����ʵ��������ģ�����ݵĲ�ֵ
    long double *GA;  //����ϵ����һά����Ԫ�ش洢����GA
    long double *GA1; //����ϵ����һά����Ԫ�ش洢����GA

	long double* DELTA_D;
	long double* delta_m;

    ModelingSubdivision *m_pModelSubdivison; //ģ���ʷ���
    QWidget *m_parent;

    std::vector<double> m_forwardResult;
    vector<ArrayIndex> ID_vector;
    osg::ref_ptr<osg::Vec4dArray> m_resultPointArray; //���淴�ݽ���ķ�������ֵ

    HINSTANCE m_DPCGRCInstance;
    DPCGRC m_funcDPCGRC;

	vector<long double*> m_localVars;
	vector<int*> m_localIntVars;

	QReadWriteLock _lock;
};
}

#endif