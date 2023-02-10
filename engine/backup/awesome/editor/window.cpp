#include "window.h"

std::string Window::getTitle() const
{
	return getTypeName();
}

void Window::setFocus(const bool focus)
{
	if (m_hasFocus != focus)
	{
		m_hasFocus = focus;
		onFocusChange(m_hasFocus);
	}
}

void Window::setIsHovered(bool isHovered)
{
	m_isHovered = isHovered;
}