#include "window.h"

namespace editor
{
	std::string Window::getTitle() const
	{
		return get_descriptor().name;
	}

	void Window::setFocus(const bool focus)
	{
		if (m_hasFocus != focus)
		{
			m_hasFocus = focus;
			onFocusChange(m_hasFocus);
		}
	}
}