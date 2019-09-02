#include "gamepad.h"

namespace awesome
{
	Gamepad::Gamepad(InputSystem* const t_inputSystem)
		: InputDevice(t_inputSystem, Type::Gamepad)
	{

	}
}