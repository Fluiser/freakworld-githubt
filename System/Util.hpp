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