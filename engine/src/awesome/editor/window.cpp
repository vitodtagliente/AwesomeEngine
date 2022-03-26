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

	void Window::update(const double /*deltaTime*/)
	{
	}

	void Window::render(Context&)
	{
	}

	REFLECT_IMP(Window)
}