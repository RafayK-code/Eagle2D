#pragma once

#ifdef EAGLE_PLATFORM_WINDOWS
	#ifdef EAGLE_BUILD_DLL
		#define EAGLE_API __declspec(dllexport)
	#else 
		#define EAGLE_API __declspec(dllimport)
	#endif
#endif