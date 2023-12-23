#pragma once

#ifdef NEUROCYN_SHARED
	#if defined(_WIN32) && !defined(__MINGW32__)
		#ifdef NEUROCYN_BUILD
			#define NEUROCYN_API __declspec(dllexport)
		#else
			#define NEUROCYN_API __declspec(dllimport)
		#endif
	#else
		#define NEUROCYN_API __attribute__((visibility("default")))
	#endif
#else
#define NEUROCYN_API
#endif

/*********************************************************************************/

#ifdef __GNUC__
	#define NEUROCYN_DEPRECATED(func, hint) func __attribute__((deprecated(hint)))
#elif defined(_MSC_VER)
	#define NEUROCYN_DEPRECATED(func, hint) __declspec(deprecated(hint)) func
#else
	#define NEUROCYN_DEPRECATED(func, hint) func
#endif

/*********************************************************************************/

#ifndef __GNUC__
	#define NEUROCYN_ATTRIBUTE_FORMAT(...)
#elif defined(__MINGW32__)
	#define NEUROCYN_ATTRIBUTE_FORMAT(...) __attribute__((format(gnu_printf, __VA_ARGS__)))
#else
	#define NEUROCYN_ATTRIBUTE_FORMAT(...) __attribute__((format(printf, __VA_ARGS__)))
#endif

/*********************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __cplusplus
}
#endif
