#include "mouse.h"

namespace awesome
{

	Mouse::Mouse(InputSystem* const t_inputSystem)
		: InputDevice(t_inputSystem, Type::Mouse)
	{

	}

	bool Mouse::isButtonDown(const Button t_button) const
	{
		return false;
	}

	bool Mouse::isButtonClicked(const Button t_button) const
	{
		return false;
	}

	bool Mouse::isButtonReleased(const Button t_button) const
	{
		return false;
	}
}