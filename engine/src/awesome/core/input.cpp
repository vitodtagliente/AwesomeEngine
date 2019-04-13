#include "input.h"

namespace awesome
{
	Input::Input()
		: m_lastKeysState()
		, m_keysState()
		, m_lastMousePosition()
		, m_mousePosition()
		, m_deltaMousePosition()
	{
	}

	Input::~Input()
	{
	}

	bool Input::isKeyDown(const keycode_t t_key) const
	{
		return hasKeyState(t_key, KeyState::Down);
	}

	bool Input::isKeyPressed(const keycode_t t_key) const
	{
		return hasKeyState(t_key, KeyState::Pressed);
	}

	bool Input::isKeyReleased(const keycode_t t_key) const
	{
		return hasKeyState(t_key, KeyState::Released);
	}

	bool Input::hasKeyState(const keycode_t t_key, const KeyState t_state) const
	{
		const auto it = m_lastKeysState.find(t_key);
		if (it != m_lastKeysState.end())
			return it->second == t_state;
		return false;
	}

	const vec2 & Input::getMousePosition() const
	{
		return m_mousePosition;
	}

	const vec2 & Input::getDeltaMousePosition() const
	{
		return m_deltaMousePosition;
	}

	void Input::clear()
	{
		m_lastKeysState.clear();
		m_keysState.clear();
	}

	void Input::init()
	{

	}

	void Input::update()
	{
		platformUpdate();

		// #todo: mouse implementation
	}
}