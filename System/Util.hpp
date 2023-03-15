#pragma once
#ifdef DEBUG

#define DEB_LOG(x) std::cout << x

#if defined( _MSVC_LANG )
#define BREAK_POINT DebugBreak()
#else 
#define BREAK_POINT __builtin_trap()
#endif

#define BREAK_POINT_IF(x) if(x) BREAK_POINT

#else 
#define DEB_LOG(x)
#define BREAK_POINT
#define BREAK_POINT_IF(x)
#endif

#include <math.h>
#include <stdint.h>

namespace Math {
	template<class T>
	class vec2 {
	public:
		typedef vec2<T> vt;

		T x;
		T y;
		vec2(const T& _x, const T& _y) :
			x(_x), y(_y)
		{}
		vec2(T&& _x, T&& _y) :
			x(_x), y(_y)
		{}
		vec2(): x(0), y(0) {}

		void operator+=(const vt& vec)
		{
			x += vec.x;
			y += vec.y;
		}
		void operator-=(const vt& vec)
		{
			x -= vec.x;
			y -= vec.y;
		}
		void operator*=(const T& v)
		{
			x *= v;
			y *= v;
		}

		inline friend vt operator+(vt left, const vt& right)
		{
			return vt{
				left.x + right.x,
				right.x + right.y
			};
		}
		inline friend vt operator*(const vt& left, const vt& right)
		{
			return vt{
				left.x * right.x,
				right.x * right.y
			};
		}
		inline friend vt operator/(const vt& left, const vt& right)
		{
			return vt{
				left.x / right.x,
				right.x / right.y
			};
		}
		inline friend vt operator-(const vt& left, const vt& right)
		{
			return vt{
				left.x - right.x,
				right.x - right.y
			};
		}
	
	
	};

	typedef vec2<float>		vec2f;
	typedef vec2<uint32_t>	vec2u;
	typedef vec2<int32_t>	vec2i;
}