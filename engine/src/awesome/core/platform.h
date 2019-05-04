#pragma once

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(__MINGW32__)
#define PLATFORM_WINDOWS 1
#elif defined( __linux__ )
#define PLATFORM_LINUX 1
#elif defined( __APPLE__ )
#define PLATFORM_OSX 1
#endif

#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX) || defined(PLATFORM_OSX)
#define PLATFORM_DESKTOP 1
#else
#define PLATFORM_MOBILE 1
#endif
