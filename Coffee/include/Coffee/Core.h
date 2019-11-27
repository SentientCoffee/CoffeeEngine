#pragma once

#ifdef CF_PLATFORM_WINDOWS
	#ifdef CF_BUILD_DLL
		#define COFFEE_API __declspec(dllexport)
	#else
		#define COFFEE_API __declspec(dllimport)
	#endif
#else
	#error CoffeeEngine only supports Windows!
#endif

#define BIT_SHIFT(x) (1 << (x))
