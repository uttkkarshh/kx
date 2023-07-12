
#ifdef kx_PLATFORM_WINDOW
#if kx_DYNAMIC_LINK
  #ifdef kx_BUILD_DLL
     #define kx_API _declspec(dllexport)
  #else
     #define kx_API _declspec(dllimport)
  #endif
#else
 #define kx_API
#endif
#else
    #error kx ONLY SUPPORT WINDOWS
#endif
#define BIT(x) (1 << x)

#define kx_ASSERT(x) if(x){}

#define KX_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)