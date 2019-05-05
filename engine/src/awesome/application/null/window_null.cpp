#include "window_null.h"

namespace awesome
{
	void WindowNULL::setTitle(const std::string& t_title)
	{
	}

	void WindowNULL::resize(const uint32 t_width, const uint32 t_height)
	{
	}

	bool WindowNULL::open(const Settings& t_settings)
	{
		return true;
	}

	bool WindowNULL::close_implementation()
	{
		return true;
	}

	void WindowNULL::update_implementation()
	{
	}
}