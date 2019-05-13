#pragma once

#include <map>
#include "keycode.h"
#include "../core/singleton.h"
#include "../core/types.h"
#include "../math/vector.h"

namespace awesome
{
	class Input : public Singleton<Input>
	{
	public:

		Input();

		// initialize the input system
		virtual bool initialize(class Window* const t_window) = 0;
		// update the input state
		void update();

		bool isKeyDown(const keycode_t t_key) const;
		bool isKeyPressed(const keycode_t t_key) const;
		bool isKeyReleased(const keycode_t t_key) const;
		bool hasKeyState(const keycode_t t_key, const KeyState t_state) const;

		const vec2& getMousePosition() const;
		const vec2& getDeltaMousePosition() const;
		bool isMouseOverWindow() const;

		// reset the input state
		void clear();

	protected:

		// callbacks, derived modules should use these callbacks
		// to update the input states
		void handleKeyCallback(const keycode_t t_key, const KeyState t_state);
		void handleMousePositionCallback(const float t_x, const float t_y);
		void handleMouseEnterCallback(const bool t_inside);

		// update implementation
		virtual void update_implementation() = 0;

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