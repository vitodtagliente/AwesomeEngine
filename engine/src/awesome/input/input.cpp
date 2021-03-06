#include "input.h"

#include "input_module.h"
#include "input_device.h"

namespace awesome
{
	Input::Input(InputModule::API& t_api)
		: Singleton<Input>()
		, m_api(t_api)
		, m_lastKeysState()
		, m_keysState()
		, m_lastMousePosition()
		, m_mousePosition()
		, m_deltaMousePosition()
		, m_isMousePositionValid(true)
		, m_devices()
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

	void Input::setKeyState(const keycode_t t_key, const KeyState t_state)
	{
		const auto it = m_keysState.find(t_key);
		if (it != m_keysState.end())
		{
			m_keysState[t_key] = t_state;
		}
		else
		{
			m_keysState.insert({ t_key, t_state });
		}
	}

	void Input::setMousePosition(const float t_x, const float t_y)
	{
		m_lastMousePosition = m_mousePosition;
		m_mousePosition = { t_x, t_y };
		m_deltaMousePosition = m_mousePosition - m_lastMousePosition;
	}

	void Input::setMousePosition(const vector2& t_position)
	{
		m_lastMousePosition = m_mousePosition;
		m_mousePosition = { t_position.x, t_position.y };
		m_deltaMousePosition = m_mousePosition - m_lastMousePosition;
	}

	void Input::setMousePositionValid(const bool t_valid)
	{
		m_isMousePositionValid = t_valid;
	}

	const vec2& Input::getMousePosition() const
	{
		return m_mousePosition;
	}

	const vec2& Input::getDeltaMousePosition() const
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
}