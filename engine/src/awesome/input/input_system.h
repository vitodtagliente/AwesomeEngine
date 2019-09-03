#pragma once

#include <memory>
#include <vector>
#include "input_device.h"

namespace awesome
{
	class InputSystem
	{
	public:



	private:

		// list of input devices
		std::vector<std::unique_ptr<InputDevice>> m_devices;
	};
}