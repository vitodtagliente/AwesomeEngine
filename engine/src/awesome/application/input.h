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
		~Input();

		Input& operator=(Input&& t_input) = delete;
		Input(const Input& t_input) = delete;
		Input(Input&& t_input) = delete;
		Input& operator= (const Input& t_input) = delete;

		virtual void update() override;

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