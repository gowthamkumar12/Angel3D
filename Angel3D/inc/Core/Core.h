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
