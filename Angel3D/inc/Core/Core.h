#pragma once

#ifdef ANGEL3D_PLATFORM_WINDOWS
	#ifdef ANGEL3D_BUILD_DLL
		#define ANGEL3D_API __declspec(dllexport)
	#else
		#define ANGEL3D_API __declspec(dllimport)
	#endif
#else
	#error Angel3D only supports Windows!
#endif // ANGEL_PLATFORM_WINDOWS

#ifdef ANGEL3D_ENABLE_ASSERTS
	#define ANGEL3D_ASSERT(x, ...) {if(!(x)) { ANGEL3D_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define ANGEL3D_CORE_ASSERT(x, ...) {if(!(x)) { ANGEL3D_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define ANGEL3D_ASSERT(x, ...)
	#define ANGEL3D_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)