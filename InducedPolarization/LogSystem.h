/*
*
*/

#ifndef LOGSYSTEM_H
#define LOGSYSTEM_H

#include <memory>
#include <QString>
#include "QtCore\QThread"
#include "QtCore\QReadWriteLock"
#include "DialogProgress.h"
#include <list>
#include "QObject"
#pragma execution_character_set("utf-8")
using namespace std;

class LogSystem : public QThread
{
    Q_OBJECT
  public:
    struct MessageInfo
    {
        QtMsgType type;
        QString file;
        int line;
        QString msg;
    };

    enum LogType
    {
        DebugInfo = 0,
        DPCGRCInfo,
        NROInfo
    };

    ~LogSystem();

    static shared_ptr<LogSystem> instance();

    bool init(const QString &path, bool isUsingMultiThread = false, QWidget *parent = nullptr);
    bool isInit() const { return _isInit; }
    void setPath(const QString &path) { _path = path; }

    /**
	* @brief 文件输出消息
	*
	* @param [in] type 消息类型，4种:调试信息(QtWarningMsg)，警告(warning)，严重(QtCriticalMsg)，致命(QtFatalMsg)
	* @param [in] context 日志消息的上下文
	* @param [in] msg 消息内容
	*/
    bool write(QtMsgType type, const QMessageLogContext &context, const QString &msg);
	void writeQString(LogType logType,const QString str);

    void writeToDialog(LogType logType, char *msg, ...);

    shared_ptr<DialogProgress> getProgressBar() { return _progressBar; }

    void stopThreadLog();
    void startThreadLog();

  signals:
    void writeToDialog(QString);

  public slots:
    void onWriteToDialog(QString value);

  protected:
    LogSystem();

    static shared_ptr<LogSystem> _instance;

    virtual void run() override;

  private:
    QString _path;
    QString _currentFileName;
    bool _isInit;
    bool _isUsingMultiThread;
    QReadWriteLock _lock;

    shared_ptr<DialogProgress> _progressBar;

    list<QString> _messages;
};

#define OUT_DATA 1

//#define QLog(...)
#define QLog(...) LogSystem::instance()->writeToDialog(LogSystem::DebugInfo, __VA_ARGS__)
#define QDPCGRC(...) LogSystem::instance()->writeToDialog(LogSystem::DPCGRCInfo, __VA_ARGS__)
#define QNRO(...) LogSystem::instance()->writeToDialog(LogSystem::NROInfo, __VA_ARGS__)

#define QStrLog(x) LogSystem::instance()->writeQString(LogSystem::DebugInfo, x)
#define QStrDPCGRC(x) LogSystem::instance()->writeQString(LogSystem::DPCGRCInfo, x)
#define QStrNRO(x) LogSystem::instance()->writeQString(LogSystem::NROInfo, x)

#if OUT_DATA
#define QDataLog(...) LogSystem::instance()->write(__VA_ARGS__)
#else
#define QDataLog
#endif

#endif