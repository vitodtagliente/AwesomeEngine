#include "keyboard.h"

namespace awesome
{
	Keyboard::Keyboard(InputSystem * const t_inputSystem)
		: InputDevice(t_inputSystem, Type::Keyboard)
	{

	}
}