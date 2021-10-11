#include "window.h"

#include <typeinfo>

namespace editor
{
	Window::Window()
	{
	}
	
	std::string Window::getTitle() const
	{
		return typeid(*this).name();
	}
}