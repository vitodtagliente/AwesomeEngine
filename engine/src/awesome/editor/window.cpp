#include "window.h"

namespace editor
{
	void Window::setFocus(bool focus)
	{
		if (m_hasFocus != focus)
		{
			m_hasFocus = focus;
			onFocusChange(m_hasFocus);
		}
	}
}