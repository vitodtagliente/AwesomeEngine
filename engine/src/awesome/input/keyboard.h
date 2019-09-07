#pragma once

#include "input_device.h"

namespace awesome
{
	class Keyboard : public InputDevice
	{
	public:

		Keyboard(Input& t_input);
	};
}