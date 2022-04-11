#include "window.h"

namespace editor
{
	std::string Window::getTitle() const
	{
		return getTypeDescriptor().name;
	}

	REFLECT_IMP(Window)
}