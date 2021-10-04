#include "keyboard.h"

#include "input.h"

namespace awesome
{
	Keyboard::Keyboard(Input& t_input)
		: InputDevice(t_input, Type::Keyboard)
	{

	}
}