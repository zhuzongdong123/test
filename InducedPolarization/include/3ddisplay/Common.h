#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <memory>

using namespace std;

#if (defined WIN32 || defined _WIN32 || defined WINCE) && \
    defined TSP_MANAGER_EXPORTS
#define TSP_MANAGER_EXPORTS __declspec(dllexport)
#else
#define TSP_MANAGER_EXPORTS
#endif


#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "Dbghelp.lib")

/**
* @brief 定义PI * 2
*/
#define PI_2 1.57079632679489661923f

/**
* @brief 安全删除指针
*/
#ifndef SAFE_DELETE
#define SAFE_DELETE(x) \
    do                 \
    \
{               \
        if (x != 0)    \
        {              \
            delete x;  \
            x = 0;     \
        }              \
    \
} while (false)
#endif

/**
* @brief 安全删除指针数组
*/
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) \
    do                       \
    \
{                     \
        if (x != NULL)       \
        {                    \
            delete[] x;      \
            x = NULL;        \
        }                    \
    \
} while (false)
#endif

template <typename T>
shared_ptr<T> make_shared_array(size_t size)
{
    return shared_ptr<T>(new T[size], default_delete<T[]>());
}