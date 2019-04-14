#include "input.h"

namespace awesome
{
	Input::Input()
		: m_lastKeysState()
		, m_keysState()
		, m_lastMousePosition()
		, m_mousePosition()
		, m_deltaMousePosition()
		, m_isMouseOverWindow(true) 
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
	
	void Input::init(void * const t_windowHandler)
	{
		platformInit(t_windowHandler);
	}

	void Input::update()
	{
		platformUpdate();

		auto temp_lastKeysState = std::move(m_lastKeysState);
		m_lastKeysState = std::move(m_keysState);
		m_keysState.clear();

		// handle mouse buttons keystate
		
	}

	void Input::uninit()
	{
		platformUinit();
	}

	void Input::handleKeyCallback(const keycode_t t_key, const KeyState t_state)
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

	void Input::handleMousePositionCallback(const float t_x, const float t_y)
	{
		m_lastMousePosition = m_mousePosition;
		m_mousePosition = { t_x, t_y };
		m_deltaMousePosition = m_mousePosition - m_lastMousePosition;
	}

	void Input::handleMouseEnterCallback(const bool t_inside)
	{
		m_isMouseOverWindow = t_inside;
	}
}