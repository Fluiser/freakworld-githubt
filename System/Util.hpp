#pragma once

#define M_PI 3.14159265358979323846f

#ifdef DEBUG
#include <iostream>

#define DEB_LOG(x) std::cout << x

#if defined(_MSVC_LANG)
#define BREAK_POINT DebugBreak()
#else
#define BREAK_POINT __builtin_trap()
#endif

#define BREAK_POINT_IF(x)                                                      \
  if (x)                                                                       \
  BREAK_POINT

#else
#define DEB_LOG(x)
#define BREAK_POINT
#define BREAK_POINT_IF(x)
#endif

#include <boost/stacktrace.hpp>
#include <stdlib.h>
#include <string>

#ifdef WIN32
#include <Windows.h>
#define CRITICAL_ERROR(message)                                                \
  {                                                                            \
    std::string msg = message;                                                 \
    msg += '\n';                                                               \
    msg += boost::stacktrace::to_string(boost::stacktrace::stacktrace());      \
    MessageBox(0, msg.c_str(), "CRITICAL ERROR", MB_ICONERROR);                \
    exit(0xff);                                                                \
  }
#else
#define CRITICAL_ERROR(message)                                                \
  {                                                                            \
    std::string msg = message;                                                 \
    msg += '\n';                                                               \
    msg += boost::stacktrace::to_string(boost::stacktrace::stacktrace());      \
    std::cout << msg << "\n";                                                  \
    exit(0xff);                                                                \
  }
#endif
#include <math.h>
#include <stdint.h>

namespace Math {
template <class T> class vec2 {
public:
  typedef vec2<T> vt;

  T x;
  T y;
  vec2(const T &_x, const T &_y) : x(_x), y(_y) {}
  vec2(T &&_x, T &&_y) : x(_x), y(_y) {}
  vec2() : x(0), y(0) {}

  void operator=(const vt &vec) {
    x = vec.x;
    y = vec.y;
  }

  void operator+=(const vt &vec) {
    x += vec.x;
    y += vec.y;
  }
  void operator-=(const vt &vec) {
    x -= vec.x;
    y -= vec.y;
  }
  void operator*=(const T &v) {
    x *= v;
    y *= v;
  }

  inline friend vt operator+(vt left, const vt &right) {
    return vt{left.x + right.x, right.x + right.y};
  }
  inline friend vt operator*(const vt &left, const vt &right) {
    return vt{left.x * right.x, right.x * right.y};
  }
  inline friend vt operator/(const vt &left, const vt &right) {
    return vt{left.x / right.x, right.x / right.y};
  }
  inline friend vt operator-(const vt &left, const vt &right) {
    return vt{left.x - right.x, right.x - right.y};
  }
};

typedef vec2<float> vec2f;
typedef vec2<uint32_t> vec2u;
typedef vec2<int32_t> vec2i;
} // namespace Math

#include <iostream>

template <typename T> void ZeroMem(T &v) { memset((void *)&v, 0, sizeof(v)); }
#ifdef WIN32
#define CHECK_VULKAN_CALLBACK(CB)                                              \
  {                                                                            \
    auto result = CB;                                                          \
                                                                               \
    {                                                                          \
      HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);                       \
      SetConsoleTextAttribute(hConsole, 14);                                   \
      std::cout << "Normal:   ";                                               \
      SetConsoleTextAttribute(hConsole, 7);                                    \
      std::cout << "[" << __LINE__ << "] " << #CB ": ";                                                   \
      SetConsoleTextAttribute(hConsole, (result == VK_SUCCESS ? 10 : 4));      \
      std::cout << (result == VK_SUCCESS ? "OK (" : "ERR ") << (int)result     \
                << ")\n";                                                      \
      SetConsoleTextAttribute(hConsole, 7);                                    \
    }                                                                          \
  }
#define CRITICAL_VULKAN_CALLBACK(CB)                                           \
  {                                                                            \
    auto res = CB;                                                             \
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);                         \
    if (res != VK_SUCCESS) {                                                   \
      std::string str = #CB " return :";                                       \
      str += std::to_string((int)res);                                         \
      CRITICAL_ERROR(str.c_str())                                              \
    } else {                                                                   \
      SetConsoleTextAttribute(hConsole, 10);                                   \
      std::cout << "CRITICAL: ";                                               \
      SetConsoleTextAttribute(hConsole, 7);                                    \
      std::cout << "[" << __LINE__ << "] " << #CB ": ";                                                   \
      SetConsoleTextAttribute(hConsole, (res == VK_SUCCESS ? 10 : 4));         \
      std::cout << (res == VK_SUCCESS ? "OK (" : "ERR ") << (int)res << ")\n"; \
      SetConsoleTextAttribute(hConsole, 7);                                    \
    }                                                                          \
  }
#else
#define CHECK_VULKAN_CALLBACK(CB)                         \
    {                                                     \
        auto result = CB;                                 \
        if (result != VK_SUCCESS)                         \
        {                                                 \
            std::cout << #CB ": " << (int)result << "\n"; \
        }                                                 \
    }
#define CRITICAL_VULKAN_CALLBACK(CB)                                           \
    {                                                                          \
        auto res = CB;                                                         \
        if (res != VK_SUCCESS)                                                 \
        {                                                                      \
            std::string str = #CB " return :"; str += std::to_string((int)res); \
            CRITICAL_ERROR(str.c_str())                                        \
        }                                                                      \
    }
#endif