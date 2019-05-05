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

	void WindowNULL::close_implementation()
	{
		
	}

	void WindowNULL::update_implementation()
	{
	}
}