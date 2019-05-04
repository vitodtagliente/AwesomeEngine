#pragma once

#include <map>
#include "singleton.h"
#include "keycode.h"
#include "../math/vec2.h"

namespace awesome
{
	class Input final : public Singleton<Input>
	{
	public:

		friend class Engine;

		Input& operator=(Input&& t_input) = delete;
		Input(const Input& t_input) = delete;
		Input(Input&& t_input) = delete;
		Input& operator= (const Input& t_input) = delete;

		bool isKeyDown(const keycode_t t_key) const;
		bool isKeyPressed(const keycode_t t_key) const;
		bool isKeyReleased(const keycode_t t_key) const;
		bool hasKeyState(const keycode_t t_key, const KeyState t_state) const;

		const vec2& getMousePosition() const;
		const vec2& getDeltaMousePosition() const;
		inline bool isMouseOverWindow() const { return m_isMouseOverWindow; }

		// reset the input state
		void clear();

	private:
		
		Input();
		~Input();

		void init(void* const t_windowHandler);
		void platformInit(void* const t_windowHandler);
		void update();
		void platformUpdate();
		void uninit();
		void platformUinit();

		// events callbacks
		void handleKeyCallback(const keycode_t t_key, const KeyState t_state);
		void handleMousePositionCallback(const float t_x, const float t_y);
		void handleMouseEnterCallback(const bool t_inside);

		// last keys states
		std::map<keycode_t, KeyState> m_lastKeysState;
		// keys states
		std::map<keycode_t, KeyState> m_keysState;
		// last mouse position
		vec2 m_lastMousePosition;
		// mouse position
		vec2 m_mousePosition;
		// delta mouse position
		vec2 m_deltaMousePosition;
		// is mouse over window?
		bool m_isMouseOverWindow;
	};
}