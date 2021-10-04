#pragma once

/*
 * Vito Domenico Tagliente
 * Generic InputDevice interface
 */

namespace awesome
{
	class Input;

	class InputDevice
	{
	public:

		enum class Type
		{
			Unknown,
			Gamepad,
			Keyboard,
			Mouse,
			Touchpad
		};

		// dependency injection
		InputDevice(Input& t_input, const Type t_type = Type::Unknown)
			: m_input(t_input)
			, m_type(t_type)
		{

		}

		virtual ~InputDevice() = default;

		InputDevice(const InputDevice&) = delete;
		InputDevice& operator=(const InputDevice&) = delete;
		InputDevice(InputDevice&&) = delete;
		InputDevice& operator=(InputDevice&&) = delete;

		// return the device type
		inline Type getType() const { return m_type; }
		// return true if the device is properly running on the current system
		virtual bool isValid() const { return true; }

	protected:

		// input system
		Input& m_input;
		// device type
		Type m_type;
		
	};
}