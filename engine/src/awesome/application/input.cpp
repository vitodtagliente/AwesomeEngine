#include "input.h"

Input::Input()
	: m_lastKeysState()
	, m_keysState()
	, m_lastMousePosition()
	, m_mousePosition()
	, m_deltaMousePosition()
	, m_isMousePositionValid(true)
{

}

void Input::update()
{
	auto temp_lastKeysState = std::move(m_lastKeysState);
	m_lastKeysState = std::move(m_keysState);
	m_keysState.clear();

	// handle mouse buttons keystate
	for (auto key_code : { KeyCode::MouseLeftButton, KeyCode::MouseRightButton, KeyCode::MouseWheelButton })
	{
		auto key_code_it = temp_lastKeysState.find(key_code);
		if (key_code_it != temp_lastKeysState.end())
		{
			if (key_code_it->second == KeyState::Pressed || key_code_it->second == KeyState::Down)
			{
				auto it = m_lastKeysState.find(key_code);
				if (it != m_lastKeysState.end())
				{
					if (it->second != KeyState::Released)
					{
						it->second = KeyState::Down;
					}
				}
				else
				{
					m_lastKeysState.insert({ key_code, KeyState::Down });
				}
			}
		}
	}
}

bool Input::isKeyDown(const keycode_t key) const
{
	return hasKeyState(key, KeyState::Down);
}

bool Input::isKeyPressed(const keycode_t key) const
{
	return hasKeyState(key, KeyState::Pressed);
}

bool Input::isKeyReleased(const keycode_t key) const
{
	return hasKeyState(key, KeyState::Released);
}

bool Input::hasKeyState(const keycode_t key, const KeyState state) const
{
	const auto it = m_lastKeysState.find(key);
	if (it != m_lastKeysState.end())
		return it->second == state;
	return false;
}

void Input::setKeyState(const keycode_t key, const KeyState state)
{
	const auto it = m_keysState.find(key);
	if (it != m_keysState.end())
	{
		m_keysState[key] = state;
	}
	else
	{
		m_keysState.insert({ key, state });
	}
}

void Input::setMousePosition(const float x, const float y)
{
	m_lastMousePosition = m_mousePosition;
	m_mousePosition = { x, y };
	m_deltaMousePosition = m_mousePosition - m_lastMousePosition;
}

void Input::setMousePosition(const math::vec2& position)
{
	m_lastMousePosition = m_mousePosition;
	m_mousePosition = { position.x, position.y };
	m_deltaMousePosition = m_mousePosition - m_lastMousePosition;
}

void Input::setMousePositionValid(const bool valid)
{
	m_isMousePositionValid = valid;
}

const math::vec2& Input::getMousePosition() const
{
	return m_mousePosition;
}

const math::vec2& Input::getDeltaMousePosition() const
{
	return m_deltaMousePosition;
}

bool Input::isMousePositionValid() const
{
	return m_isMousePositionValid;
}

void Input::clear()
{
	m_lastKeysState.clear();
	m_keysState.clear();
}