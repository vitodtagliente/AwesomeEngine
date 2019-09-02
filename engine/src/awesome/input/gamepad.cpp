#include "gamepad.h"

namespace awesome
{
	Gamepad::Gamepad(InputSystem* const t_inputSystem, const unsigned int t_index)
		: InputDevice(t_inputSystem, Type::Gamepad)
		, m_index(t_index)
	{

	}
}