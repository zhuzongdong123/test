#include "DataManager.h"
#include <QDir>
#include <queue>
#include <sstream>

shared_ptr<DataManager> DataManager::_instance = nullptr;

struct CompareA
{
    QString a;
    CompareA(const QString &aa) { a = aa; }
    bool operator<(const CompareA &b) const
    {
        // 		QFileInfo fileA(a);
        // 		QFileInfo fileB(b.a);

        QString aName = "A10";
        QString bName = "A16";

        int aNum = aName.section("A", 1, 1).toInt();
        int bNum = bName.section("A", 1, 1).toInt();

        return aNum > bNum;
    }
};

DataManager::DataManager()
{
    _fileCols             = 4;
    m_defaultResultName   = "result.txt";
    _inversionProcessData = nullptr;
	_inversionProcessNROData = nullptr;
	_inversionDataXLen = 0;
	_inversionDataYLen = 0;
	_inversionDataZLen = 0;
	_inversionNRODataXBegLen = 0;
	_inversionNRODataYBegLen = 0;
	_inversionNRODataZBegLen = 0;

	_inversionNRODataXEndLen = 0;
	_inversionNRODataYEndLen = 0;
	_inversionNRODataZEndLen = 0;

	_halfLifeCurveDataList = new osg::Vec2dArray;;
}

DataManager::~DataManager()
{
	clearInversionData();
}

shared_ptr<DataManager> DataManager::instance()
{
    if (0 == _instance)
    {
        _instance = shared_ptr<DataManager>(new DataManager);
    }

    return _instance;
}

void DataManager::clearInversionData()
{
    if (_inversionProcessData)
    {
        for (unsigned int z = 0; z < _inversionDataZLen; z++)
        {
            for (unsigned int y = 0; y < _inversionDataYLen; y++)
            {
                if (_inversionProcessData[z][y])
                {
                    delete[] _inversionProcessData[z][y];
                    _inversionProcessData[z][y] = nullptr;
                }
            }

            if (_inversionProcessData[z])
            {
                delete[] _inversionProcessData[z];
                _inversionProcessData[z] = nullptr;
            }
        }

		delete [] _inversionProcessData;
        _inversionProcessData = nullptr;
    }
}

void DataManager::setInversionNROData(double ***data, int xBeg, int xEnd, int yBeg, int yEnd, int zBeg, int zEnd)
{
	//clearInversionNROData();
	if (0 == xEnd || 0 == yEnd || 0 == zEnd)
	{
		return;
	}

	_inversionNRODataXBegLen = xBeg;
	_inversionNRODataYBegLen = yBeg;
	_inversionNRODataZBegLen = zBeg;

	_inversionNRODataXEndLen = xEnd;
	_inversionNRODataYEndLen = yEnd;
	_inversionNRODataZEndLen = zEnd;

	_inversionProcessNROData = data;
}

void DataManager::setInversionData(osg::ref_ptr<osg::Vec4dArray> vPointArray, int xLen, int yLen, int zLen)
{
	clearInversionData();
	if (0 == xLen || 0 == yLen || 0 == zLen)
	{
		return;
	}

	_inversionDataXLen = xLen;
	_inversionDataYLen = yLen;
	_inversionDataZLen = zLen;

	_inversionProcessData = new double **[zLen];
	memset(_inversionProcessData, 0, sizeof(double **) * zLen);

	for (unsigned int i = 0; i < zLen; i++)
	{
		_inversionProcessData[i] = new double *[yLen];
		memset(_inversionProcessData[i], 0, sizeof(double *) * yLen);
		for (unsigned int j = 0; j < yLen; j++)
		{
			_inversionProcessData[i][j] = new double[xLen];
			memset(_inversionProcessData[i][j], 0, sizeof(double) * xLen);
		}
	}

	for (int i = 0; i < vPointArray->size(); i++)
	{
		int xPos = (*vPointArray)[i].x();
		int yPos = (*vPointArray)[i].y();
		int zPos = (*vPointArray)[i].z();
		if (xPos >= xLen || yPos >= yLen || zPos >= zLen)
			continue;
		_inversionProcessData[xPos][yPos][zPos] = (*vPointArray)[i].w();
	}

	emit onInvertDataLoadCompleted(_inversionProcessData, zLen, yLen, xLen);
}

void DataManager::setInversionData(const shared_ptr<double> &data, unsigned int x, unsigned int y, unsigned int z)
{
	clearInversionData();
    if (0 == x || 0 == y || 0 == z)
    {
        return;
    }

    _inversionDataXLen = x;
    _inversionDataYLen = y;
    _inversionDataZLen = z;

    _inversionProcessData = new double **[z];
    memset(_inversionProcessData, 0, sizeof(double **) * z);

    for (unsigned int i = 0; i < z; i++)
    {
        _inversionProcessData[i] = new double *[y];
        memset(_inversionProcessData[i], 0, sizeof(double *) * y);

        for (unsigned int j = 0; j < y; j++)
        {
            _inversionProcessData[i][j] = new double[x];
            memset(_inversionProcessData[i][j], 0, sizeof(double) * x);

            for (unsigned int k = 0; k < x; k++)
            {
                _inversionProcessData[i][j][k] = data.get()[i * y * x + j * x + k];
            }
        }
    }

    emit onInvertDataLoadCompleted(_inversionProcessData, z, y, x);
}

void DataManager::setInversionNROData(const shared_ptr<double> &data, int xBeg, int xEnd, int yBeg, int yEnd, int zBeg, int zEnd)
{
	if (0 == xEnd || 0 == yEnd || 0 == zEnd)
	{
		return;
	}

	_inversionNRODataXBegLen = xBeg;
	_inversionNRODataYBegLen = yBeg;
	_inversionNRODataZBegLen = zBeg;

	_inversionNRODataXEndLen = xEnd;
	_inversionNRODataYEndLen = yEnd;
	_inversionNRODataZEndLen = zEnd;

	int zDataLen = zEnd - zBeg + 1;
	int yDataLen = yEnd - yBeg + 1;
	int xDataLen = xEnd - xBeg + 1;
	_inversionProcessNROData = new double **[zDataLen];
	memset(_inversionProcessNROData, 0, sizeof(double **) * zDataLen);

	for (unsigned int i = 0; i < zDataLen; i++)
	{
		_inversionProcessNROData[i] = new double *[yDataLen];
		memset(_inversionProcessNROData[i], 0, sizeof(double *) * yDataLen);

		for (unsigned int j = 0; j < yDataLen; j++)
		{
			_inversionProcessNROData[i][j] = new double[xDataLen];
			memset(_inversionProcessNROData[i][j], 0, sizeof(double) * xDataLen);

			for (unsigned int k = 0; k < xDataLen; k++)
			{
				_inversionProcessNROData[i][j][k] = data.get()[i * yDataLen * xDataLen + j * xDataLen + k];
			}
		}
	}
}

bool DataManager::initialize(const QString &path)
{
    QDir dir(path);
	_dataList.clear();

    if (!dir.exists())
    {
        return false;
    }

	vector<double> observeDataListTemp = _observeDataList;
    cleanData();
	_observeDataList = observeDataListTemp;

    QStringList list;

    priority_queue<CompareA> f;

    foreach (QFileInfo mfi, dir.entryInfoList(QDir::Dirs, QDir::Name))
    {
        if (mfi.isDir())
        {
            if ("." == mfi.fileName())
            {
                continue;
            }

            if (".." == mfi.fileName())
            {
                continue;
            }

            QString s = mfi.absoluteFilePath();

            CompareA ca(s);

            f.push(ca);
        }
    }

    unsigned int readFileCount    = 0;
    shared_ptr<DataInfo> dataInfo = nullptr;

    DataInfo dInfo = {0};

    while (!f.empty())
    {
        QString fileName = f.top().a;
        f.pop();

        if (0 == readFileCount % _fileCols)
        {
            dataInfo = shared_ptr<DataInfo>(new DataInfo, [](DataInfo *ptr)
			{
				for (unsigned int i = 0; i < ptr->row; i++)
				{
					if (ptr->data[i])
					{
						delete[] ptr->data[i];
					}
				}

				if (ptr->data)
				{
					delete[] ptr->data;
				}

				ptr->data = nullptr;
			});

            memset(dataInfo.get(), 0, sizeof(DataInfo));
            QFile file(fileName + "/" + m_defaultResultName);

            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                file.close();
                return false;
            }

            QByteArray a;
            unsigned int lineCount = 0;

            while (0 < (a = file.readLine()).size())
            {
                lineCount++;
            }

            dataInfo->row = lineCount;
            dataInfo->col = _fileCols;

            dataInfo->data = new double *[dataInfo->row];
            memset(dataInfo->data, 0, sizeof(double *) * dataInfo->row);

            for (unsigned int i = 0; i < dataInfo->row; i++)
            {
                dataInfo->data[i] = new double[dataInfo->col];
                memset(dataInfo->data[i], 0, sizeof(double) * dataInfo->col);
            }

            _dataList.push_back(dataInfo);
            file.close();
        }

        QFile file(fileName + "/" + m_defaultResultName);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            file.close();
            return false;
        }

        QByteArray a;

        unsigned int dataRow = 0;

        while (0 < (a = file.readLine()).size())
        {
            QString str(a);

            stringstream ss(str.toStdString());
            string element = "";

            unsigned int lineCol = 0;

            while (ss >> element)
            {
                if (5 != lineCol)
                {
                    lineCol++;
                    continue;
                }

                lineCol++;

                QString str(element.c_str());

                double value = str.toDouble();

                unsigned int cols = readFileCount % _fileCols;

                dataInfo->data[dataRow][cols] = value;
            }

            dataRow++;
        }

        readFileCount++;
        file.close();
    }

	emit onObserverDataLoaded();

    return true;
}

void DataManager::cleanData()
{
	_observeDataList.clear();
	_adjustmentDataVec.clear();
    _dataList.clear();
	_halfLifeCurveDataList->clear();
	_inversionDataXLen = 0;
	_inversionDataYLen = 0;
	_inversionDataZLen = 0;
}