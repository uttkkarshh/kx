#pragma once
#include <memory>
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



#ifdef kx_DEBUG
#define kx_ENABLE_ASSERTS
#endif

#ifdef kx_ENABLE_ASSERTS
#define kx_ASSERT(x, ...) { if(!(x)) { kx_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define kx_CORE_ASSERT(x, ...) { if(!(x)) { kx_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define kx_ASSERT(x, ...)
#define kx_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

#define kx_ASSERT(x) if(x){}

#define KX_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace kx {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}