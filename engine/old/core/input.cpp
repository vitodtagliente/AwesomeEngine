#include <awesome/core/input.h>
#include <awesome/core/application.h>

namespace awesome
{
	void InputManager::clear() {
		m_LastKeysState.clear();
		m_KeysState.clear();
	}

	void InputManager::init(void* const window_handler) {
		platformInit(window_handler);
	}

	void InputManager::update() 
	{
		platformUpdate();
		
		// update keys cache system
		auto temp_last_keys_state = m_LastKeysState; // mouse button down implementation
		m_LastKeysState = m_KeysState;
		m_KeysState.clear();
				
		// implements mouse button down state
		for (auto key_code : { KeyCode::MouseButtonLeft, KeyCode::MouseButtonRight, KeyCode::MouseButtonWheel }) {
			auto it = temp_last_keys_state.find(key_code);
			if (it != temp_last_keys_state.end())
			{
				if (it->second == KeyState::Pressed || it->second == KeyState::Down)
				{
					// search in m_LastKeys 
					auto it1 = m_LastKeysState.find(key_code);
					if (it1 != m_LastKeysState.end())
					{
						if (it1->second != KeyState::Released)
							it1->second = KeyState::Down;
					}
					else
					{
						m_LastKeysState.insert(std::pair<uint, KeyState>(key_code, KeyState::Down));
					}
				}
			}
		}
	}

	void InputManager::onKeyCallback(const uint key_code, const KeyState key_state)
	{
		const auto it = m_KeysState.find(key_code);
		if (it != m_KeysState.end())
		{
			m_KeysState[key_code] = key_state;
		}
		else 
		{
			m_KeysState.insert(std::pair<uint, KeyState>(key_code, key_state));
		}
	}

	void InputManager::onMousePositionCallback(const float x, const float y)
	{
		m_LastMousePosition = m_MousePosition;
		m_MousePosition = vec2{ x, y };
		m_MouseDeltaPosition = m_MousePosition - m_LastMousePosition;
	}

	void InputManager::onMouseEnterCallback(const bool entered) {
		m_IsMousePositionValid = entered;
	}

	bool InputManager::isKeyDown(const uint key_code) const
	{
		const auto it = m_LastKeysState.find(key_code);
		if (it != m_LastKeysState.end())
			return it->second == KeyState::Down;
		return false;
	}

	bool InputManager::isKeyPressed(const uint key_code) const
	{
		const auto it = m_LastKeysState.find(key_code);
		if (it != m_LastKeysState.end())
			return it->second == KeyState::Pressed;
		return false;
	}

	bool InputManager::isKeyReleased(const uint key_code) const
	{
		const auto it = m_LastKeysState.find(key_code);
		if (it != m_LastKeysState.end())
			return it->second == KeyState::Released;
		return false;
	}

	InputManager* Input::m_MainInputManager = nullptr;

	InputManager* Input::mainInputManager() {
		if (m_MainInputManager == nullptr)
		{
			const auto application = Application::instance();
			if (application) {
				const auto window = application->getWindow();
				if (window) {
					m_MainInputManager = window->getInputManager();
				}
			}
		}
		return m_MainInputManager;
	}
}