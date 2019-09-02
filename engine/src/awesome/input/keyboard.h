#pragma once

#include "input_device.h"

namespace awesome
{
	class Keyboard : public InputDevice
	{
	public:

		Keyboard(InputSystem * const t_inputSystem);
	};
}