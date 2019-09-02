#pragma once

#include "input_device.h"

namespace awesome
{
	class Gamepad : public InputDevice
	{
	public:

		Gamepad(InputSystem* const t_inputSystem, const unsigned int t_index);

	private:

		// pad index
		unsigned int m_index;

	};
}