
#ifdef kx_PLATFORM_WINDOW
#ifdef HZ_BUILD_DLL
#define kx_API _declspec(dllexport)
#else
#define kx_API _declspec(dllimport)
#endif
#else
    #error kx ONLY SUPPORT WINDOWS
#endif