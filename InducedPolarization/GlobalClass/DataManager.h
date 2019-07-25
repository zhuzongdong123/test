#pragma once
//单实例类，只存放中间处理数据
#include <QtCore/QObject>
#include <memory>
#include "../osg/Array"

using namespace std;

class DataManager : public QObject
{
    Q_OBJECT

  public:
    typedef struct __DataInfo
    {
        double **data;
        unsigned short row;
        unsigned short col;
    } DataInfo, *PDataInfo;

    typedef vector<shared_ptr<DataInfo>> DataList;

    ~DataManager();

    static shared_ptr<DataManager> instance();

    template <typename T>
    shared_ptr<T> makeData(size_t size)
    {
        auto r = shared_ptr<T>(new T[size], default_delete<T[]>());
        memset(r.get(), 0, sizeof(T) * size);

        return r;
    }

    void clearInversionData();
	
    void setInversionNROData(double ***data, int xBeg, int xEnd, int yBeg, int yEnd, int zBeg, int zEnd);
	void setInversionNROData(const shared_ptr<double> &data, int xBeg, int xEnd, int yBeg, int yEnd, int zBeg, int zEnd);
    void setInversionData(const shared_ptr<double> &data, unsigned int x, unsigned int y, unsigned int z);
	void setInversionData(osg::ref_ptr<osg::Vec4dArray> vPointArray, int xLen, int yLen, int zLen);

    const DataList &getDataList() const { return _dataList; }
    DataList &getDataListRef() { return _dataList; }

    const vector<double> &getObserveDataList() const { return _observeDataList; }
    vector<double> &getObserveDataListRef() { return _observeDataList; }
	void setObserveDataList(vector<double> list) { _observeDataList = list; }

    const vector<double> &getAdjustmentDataVec() const { return _adjustmentDataVec; }
    vector<double> &getAdjustmentDataVecRef() { return _adjustmentDataVec; }

    unsigned int getInversionProcessDataXLen() { return _inversionDataXLen; }
    unsigned int getInversionProcessDataYLen() { return _inversionDataYLen; }
    unsigned int getInversionProcessDataZLen() { return _inversionDataZLen; }
    double ***getInversionProcessData() { return _inversionProcessData; }

	unsigned int getInversionProcessNRODataXBegLen() { return _inversionNRODataXBegLen;}
	unsigned int getInversionProcessNRODataYBegLen() { return _inversionNRODataYBegLen; }
	unsigned int getInversionProcessNRODataZBegLen() { return _inversionNRODataZBegLen; }

	unsigned int getInversionProcessNRODataXEndLen() { return _inversionNRODataXEndLen; }
	unsigned int getInversionProcessNRODataYEndLen() { return _inversionNRODataYEndLen; }
	unsigned int getInversionProcessNRODataZEndLen() { return _inversionNRODataZEndLen; }

	double ***getInversionProcessNROData() { return _inversionProcessNROData; }

	osg::ref_ptr<osg::Vec2dArray> getHalfLifeCurveDataList() { return _halfLifeCurveDataList; }

    bool initialize(const QString &path);
    void cleanData();

  signals:

    void onInvertDataLoadCompleted(double ***vData, unsigned int vZLen, unsigned int vYLen, unsigned int vXLen);
	void onObserverDataLoaded();

  private:
    DataManager();

    static shared_ptr<DataManager> _instance;

    QString m_path;
    QString m_defaultResultName;

    unsigned int _fileCols;
    DataList _dataList;						//坏点剔除
    vector<double> _observeDataList;		//观测数据提取
    vector<double> _adjustmentDataVec;		//调整数据
    //shared_ptr<double> _inversionProcessData;
    double ***_inversionProcessData;
	double ***_inversionProcessNROData;
    unsigned int _inversionDataXLen;
    unsigned int _inversionDataYLen;
    unsigned int _inversionDataZLen;
	
	int _inversionNRODataXBegLen;
	int _inversionNRODataYBegLen;
	int _inversionNRODataZBegLen;

	int _inversionNRODataXEndLen;
	int _inversionNRODataYEndLen;
	int _inversionNRODataZEndLen;
	osg::ref_ptr<osg::Vec2dArray> _halfLifeCurveDataList;

  private:
};