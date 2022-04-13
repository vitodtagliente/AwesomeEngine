#include "window.h"

namespace editor
{
	std::string Window::getTitle() const
	{
		return getTypeDescriptor().name;
	}

	void Window::setFocus(bool focus)
	{
		if (m_hasFocus != focus)
		{
			m_hasFocus = focus;
			onFocusChange(m_hasFocus);
		}
	}

	REFLECT_IMP(Window)
}