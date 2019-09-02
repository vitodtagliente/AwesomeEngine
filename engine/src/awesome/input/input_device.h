#pragma once

#include "keycode.h"

namespace awesome
{
	class InputSystem;

	class InputDevice
	{
	public:

		enum class Type
		{
			Unknown,
			Gamepad,
			Keyboard,
			Mouse
		};

		// dependency injection
		InputDevice(InputSystem* const t_inputSystem);

		inline Type getType() const { return m_type; }

	private:

		// device type
		Type m_type;
		
	};
}