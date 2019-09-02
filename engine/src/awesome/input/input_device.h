#pragma once

/*
 * Vito Domenico Tagliente
 * Generic InputDevice interface
 */

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
		InputDevice(InputSystem* const t_inputSystem, const Type t_type = Type::Unknown)
			: m_inputSystem(t_inputSystem)
			, m_type(t_type)
		{

		}

		virtual ~InputDevice() = default;

		// return the device type
		inline Type getType() const { return m_type; }
		// return true if the device is properly running on the current system
		virtual bool isValid() const { return true; }

	private:

		// input system
		InputSystem* m_inputSystem;
		// device type
		Type m_type;
		
	};
}