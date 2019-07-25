/*****************************************************************************
*  计时器类																	 *
*  Copyright (C) 山东大学岩土与结构工程研究中心                              *
*                                                                            *
*  这个文件是计时器类功能的一部分	     									 *
*                                                                            *
*                                                                            *
*  @file     Timer.h													     *
*  @brief    是Timer类的头文件											     *
*                                                                            *
*  @author   郭浩                                                            *
*  @email    korman@qq.com                                                   *
*  @version  1.0.0                                                           *
*  @date     2019/03/04                                                      *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*----------------------------------------------------------------------------*
*  2019/03/04 | 1.0.0   | 郭浩  | 创建文件                                   *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#ifndef TIMER_H
#define TIMER_H

#include <windows.h>

/**
* @brief 应用核心命名空间
* 为方便跟他人混乱而建立的命名空间
*/
namespace MatlabAnaly
{

/**
* @brief 计时器单例类
* 负责对一些操作进行计时
* @code
* BEGIN_TIMER;
* xxxProecess(); // 需要计时的操作
* END_TIMER;
* TIMER_LOG("xx操作");
* @endcode
*/
class Timer
{
  public:
    /**
      * @brief 实例获得
      *
      * @return 返回实例指针
      */
    static Timer *instance();

    /**
	* @brief 开始计时
	*/
    void BeginTimer();

    /**
	* @brief 结束计时
	*/
    void EndTimer();

    /**
	* @brief 获得操作的花费时间
	*
	* @return 获得花费时间
	*/
    float getCostSeconds();

    /**
	* @brief 写log
	*
	* @param [in] text 要写的操作名
	* @warning 只需要写操作名就好了，会自动补上cost xxx seconds这种。
	*/
    void writeLog(const char *text);

  protected:
    /**
	  * @brief 重置
	  */
    void reset();

    static Timer *_instance; ///< 管理类的实例

    LARGE_INTEGER _t1; ///< 计时变量1
    LARGE_INTEGER _t2; ///< 计时变量2
    LARGE_INTEGER _tc; ///< 计时变量3

  private:
    /**
      * @brief 构造函数
      */
    Timer();

    /**
	* @brief 析构函数
	*/
    ~Timer();
};
}

#define BEGIN_TIMER                                   \
    do                                                \
    {                                                 \
        MatlabAnaly::Timer::instance()->BeginTimer(); \
    } while (false)
#define END_TIMER                                   \
    do                                              \
    {                                               \
        MatlabAnaly::Timer::instance()->EndTimer(); \
    } while (false)
#define TIMER_LOG(x)                                 \
    do                                               \
    {                                                \
        MatlabAnaly::Timer::instance()->writeLog(x); \
    } while (false)

#endif