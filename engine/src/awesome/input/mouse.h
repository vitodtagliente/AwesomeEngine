#pragma once

#include <awesome/math/vector2.h>
#include "input_device.h"

namespace awesome
{
	class Mouse : public InputDevice
	{
	public:

		inline const vec2& getPosition() const { return m_position; }
		inline const vec2& getDeltaPosition() const { return m_deltaPosition; }
		inline bool hasValidPosition() const { return m_hasValidPosition; }

	private:

		// last position
		vec2 m_lastPosition;
		// position
		vec2 m_position;
		// delta position
		vec2 m_deltaPosition;
		// is mouse over window?
		bool m_hasValidPosition;

	};
}