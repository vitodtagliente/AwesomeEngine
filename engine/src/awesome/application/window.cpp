#include "window.h"

namespace awesome
{
	// default configuration
	Window::Settings::Settings()
		: title("Awesome")
		, width(640)
		, height(480)
		, fullscreen(false)
		, vsync(false)
	{

	}

	bool Window::startup_imp()
	{
		// #todo: get default app size by config
		return open({});
	}
}