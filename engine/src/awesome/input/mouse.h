#pragma once

#include <awesome/math/vector2.h>
#include "input_device.h"

namespace awesome
{
	class Mouse : public InputDevice
	{
	public:

		enum class Button
		{
			Unknown,
			Left,
			Right,
			Middle, // wheel button
			Extra1,
			Extra2,
			Count
		};

		Mouse(Input& t_input);

		bool isButtonDown(const Button t_button) const;
		bool isButtonClicked(const Button t_button) const;
		bool isButtonReleased(const Button t_button) const;

		inline const vec2& getPosition() const;
		inline const vec2& getDeltaPosition() const;
		inline bool hasValidPosition() const;
	};
}