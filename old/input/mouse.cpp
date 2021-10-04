#include "mouse.h"

#include "input.h"

namespace awesome
{
	Mouse::Mouse(Input& t_input)
		: InputDevice(t_input, Type::Mouse)
	{
	}

	bool Mouse::isButtonDown(const Button t_button) const
	{
		return false;
	}

	bool Mouse::isButtonClicked(const Button t_button) const
	{
		return false;
	}

	bool Mouse::isButtonReleased(const Button t_button) const
	{
		return false;
	}

	inline const vec2& Mouse::getPosition() const
	{
		return m_input.getMousePosition();
	}

	inline const vec2& Mouse::getDeltaPosition() const
	{
		return m_input.getDeltaMousePosition();
	}

	inline bool Mouse::hasValidPosition() const
	{
		return m_input.isMousePositionValid();
	}
}