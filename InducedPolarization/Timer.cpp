#include "Timer.h"
#include "qDebug.h"

namespace MatlabAnaly
{
Timer *Timer::_instance = 0;

Timer::Timer()
{
    reset();
}

Timer::~Timer()
{
}

Timer *Timer::instance()
{
    if (0 == _instance)
    {
        _instance = new Timer;
    }

    return _instance;
}

void Timer::BeginTimer()
{
    reset();
    QueryPerformanceFrequency(&_tc);
    QueryPerformanceCounter(&_t1);
}

void Timer::EndTimer()
{
    QueryPerformanceCounter(&_t2);
}

float Timer::getCostSeconds()
{
    return (_t2.QuadPart - _t1.QuadPart) * 1.0 / _tc.QuadPart;
}

void Timer::writeLog(const char *text)
{
	float timeCost = getCostSeconds();

    qWarning() << text << " cost time:" << timeCost << " seconds." << endl;
}

void Timer::reset()
{
    memset(&_t1, 0, sizeof(LARGE_INTEGER));
    memset(&_t2, 0, sizeof(LARGE_INTEGER));
    memset(&_tc, 0, sizeof(LARGE_INTEGER));
}
}