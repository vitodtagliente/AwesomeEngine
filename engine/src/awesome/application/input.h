#pragma once

#include <map>
#include "keycode.h"
#include "../core/types.h"
#include "../engine/module.h"
#include "../math/vec2.h"

namespace awesome
{
	class Input : public Module<Input>
	{
	public:

		Input();

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

		// module update
		virtual void update_imp() override;

		// callbacks
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