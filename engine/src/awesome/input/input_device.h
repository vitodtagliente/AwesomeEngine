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
		InputDevice(InputSystem* const t_inputSystem, const Type t_type = Type::Unknown);

		inline Type getType() const { return m_type; }

	private:

		// input system
		InputSystem* m_inputSystem;
		// device type
		Type m_type;
		
	};
}