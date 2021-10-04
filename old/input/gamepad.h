#pragma once

#include "input_device.h"

namespace awesome
{
	class Gamepad : public InputDevice
	{
	public:

		Gamepad(Input& t_input, const unsigned int t_index);

		inline unsigned int getIndex() const { return m_index; }

	private:

		// pad index
		unsigned int m_index;

	};
}