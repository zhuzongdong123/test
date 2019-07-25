#include "LogSystem.h"
#include <QFile>
#include "QtCore\QTextStream"
#include "QtCore\QDateTime"
#include "QtCore\QMutex"
#include "QtCore\QTextCodec"
#include <stdarg.h>
#include "GlobalClass\GlobalParam.h"
#include "QColor"

shared_ptr<LogSystem> LogSystem::_instance = nullptr;

void LogSystem::run()
{
    while (true)
    {
        if (0 < _messages.size())
        {
            QString logPrePath = _path;

            _lock.lockForRead();
            QString message = _messages.back();
            _lock.unlock();

            _lock.lockForWrite();
            _messages.pop_back();
            _lock.unlock();

            if (GlobalParam::instance()->getCommonSetting().writeFile)
            {
                QFile file(logPrePath + "/" + _currentFileName);

                if (file.open(QIODevice::WriteOnly | QIODevice::Append))
                {
                    QTextStream text_stream(&file);
                    text_stream << message << "\r\n";
                }

                file.flush();
                file.close();
            }

            emit writeToDialog(message);
        }

        msleep(80);
    }
}

LogSystem::LogSystem()
{
    _isUsingMultiThread = false;

    _isInit = false;
}

LogSystem::~LogSystem()
{
    terminate();
    wait();
}

std::shared_ptr<LogSystem> LogSystem::instance()
{
    if (nullptr == _instance)
    {
        _instance = shared_ptr<LogSystem>(new LogSystem);
    }

    return _instance;
}

bool LogSystem::init(const QString &path, bool isUsingMultiThread, QWidget *parent)
{
    if (0 >= path.length())
    {
        return false;
    }

    _currentFileName = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh_mm_ss") + ".log";
    _path            = path;
    _isInit          = true;

    _isUsingMultiThread = isUsingMultiThread;

    if (_isUsingMultiThread)
    {
        start(QThread::LowPriority);
    }

    _progressBar = shared_ptr<DialogProgress>(new DialogProgress(parent));

    return true;
}

bool LogSystem::write(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if (0 >= msg.length())
    {
        return false;
    }

    //QTextCodec *code = QTextCodec::codecForName("GB2312");//解决中文路径问题

    if (_isUsingMultiThread)
    {
        _lock.lockForRead();
        _messages.push_front(msg);
        _lock.unlock();

        return true;
    }

    static QMutex mutex;

    mutex.lock();

    QString text;

    QString logPrePath = _path;

    switch (type)
    {
    case QtDebugMsg:
        text = QString("Debug:");
        break;
    case QtWarningMsg:
        text = QString("Warning:");
        break;
    case QtCriticalMsg:
        text = QString("Critical:");
        break;
    case QtFatalMsg:
        text = QString("Fatal:");
    }

    QString context_info      = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh_mm_ss");
    QString current_date      = QString("(%1)").arg(current_date_time);

    //	std::string convertMsg = code->fromUnicode(msg).data();

    QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);

    QFile file(logPrePath + "/" + _currentFileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream text_stream(&file);
        text_stream << message << "\r\n";
    }

    file.flush();
    file.close();
    mutex.unlock();

    return true;
}

void LogSystem::writeQString(LogType logType,const QString str)
{
	if (_isUsingMultiThread)
	{
		//emit writeToDialog(QString::fromUtf8(p));

		if (LogType::DebugInfo == logType && GlobalParam::instance()->getCommonSetting().debugLog)
		{
			_lock.lockForWrite();
			_messages.push_front(str);
			_lock.unlock();
		}

		if (LogType::DPCGRCInfo == logType && GlobalParam::instance()->getCommonSetting().DPCGRCLog)
		{
			_lock.lockForWrite();
			//	QString m = formatHtml(QString::fromUtf8(p), QColor(255, 0, 0));
			_messages.push_front(str);
			_lock.unlock();
		}

		if (LogType::NROInfo == logType && GlobalParam::instance()->getCommonSetting().NROLog)
		{
			_lock.lockForWrite();
			_messages.push_front(str);
			_lock.unlock();
		}
	}
}

void LogSystem::writeToDialog(LogType logType, char *msg, ...)
{
    //write(msg);

    if (!_progressBar)
    {
        return;
    }

    va_list argList;
    char p[1024] = {0};

    va_start(argList, msg);
    int byteWrite = vfprintf(stdout, msg, argList);

    _vsnprintf(p, 1024, msg, argList);

    va_end(argList);

    if (_isUsingMultiThread)
    {
        //emit writeToDialog(QString::fromUtf8(p));

        if (LogType::DebugInfo == logType && GlobalParam::instance()->getCommonSetting().debugLog)
        {
            _lock.lockForWrite();
            _messages.push_front(QString::fromUtf8(p));
            _lock.unlock();
        }

        if (LogType::DPCGRCInfo == logType && GlobalParam::instance()->getCommonSetting().DPCGRCLog)
        {
            _lock.lockForWrite();
            //	QString m = formatHtml(QString::fromUtf8(p), QColor(255, 0, 0));
            _messages.push_front(QString::fromUtf8(p));
            _lock.unlock();
        }

        if (LogType::NROInfo == logType && GlobalParam::instance()->getCommonSetting().NROLog)
        {
            _lock.lockForWrite();
            _messages.push_front(QString::fromUtf8(p));
            _lock.unlock();
        }
    }
}

void LogSystem::stopThreadLog()
{
    //_progressBar = nullptr;

    disconnect(this, SIGNAL(writeToDialog(QString)), this, SLOT(onWriteToDialog(QString)));
}

void LogSystem::startThreadLog()
{
    connect(this, SIGNAL(writeToDialog(QString)), this, SLOT(onWriteToDialog(QString)), Qt::UniqueConnection);
}

void LogSystem::onWriteToDialog(QString value)
{
    if (!_progressBar)
    {
        return;
    }

    _progressBar->writeMessage(0, value);
}