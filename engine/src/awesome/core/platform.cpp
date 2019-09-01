#include "platform.h"

namespace awesome
{
	Platform::Type Platform::type()
	{
#ifdef PLATFORM_WINDOWS
		return Type::Windows;
#elif PLATFORM_LINUX

#elif PLATFORM_OSX

#endif 

		return Type::Null;
	}

	Platform::Category Platform::category()
	{
		return Category::Desktop;
	}
}