#include "window.h"

namespace editor
{
	Window::Window()
	{
	}

	std::string Window::getTitle() const
	{
		return getTypeDescriptor().name;
	}

	void Window::render(Context&)
	{
	}

	REFLECT_IMP(Window)
}