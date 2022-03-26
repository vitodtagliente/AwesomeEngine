#include "window.h"

namespace editor
{
	Window::Window()
		: m_state()
	{
	}

	std::string Window::getTitle() const
	{
		return getTypeDescriptor().name;
	}

	void Window::init()
	{
	}

	void Window::update(const double /*deltaTime*/)
	{
	}

	void Window::render()
	{
	}

	REFLECT_IMP(Window)
}