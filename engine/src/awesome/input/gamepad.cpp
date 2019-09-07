#include "gamepad.h"

#include "input.h"

namespace awesome
{
	Gamepad::Gamepad(Input& t_input, const unsigned int t_index)
		: InputDevice(t_input, Type::Gamepad)
		, m_index(t_index)
	{

	}
}