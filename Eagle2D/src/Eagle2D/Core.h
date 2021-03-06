#pragma once
#ifdef EAGLE_BUILD_DLL
#define EAGLE_API __declspec(dllexport)
#else
#define EAGLE_API __declspec(dllimport)
#endif