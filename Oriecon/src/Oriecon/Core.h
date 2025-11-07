#pragma once

#define BIT(x) (1<<x)

#ifdef ORIECON_PLATFORM_WINDOWS

#ifdef ORIECON_BUILD_DLL
#define ORIECON_API __declspec(dllexport)
#else
#define ORIECON_API __declspec(dllimport)
#endif

#else
#error Oriecon only support Windows
#endif

#ifdef ORIECON_ENABLE_ASSERT
#define ORIECON_ASSERT(expr, ...) if(!(expr)) { ORIECON_LOG_FATAL(__VA_ARGS__); __debugbreak(); } 
#else
#define ORIECON_ASSERT(expr, ...)
#endif
