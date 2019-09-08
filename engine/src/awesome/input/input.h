#pragma once

#include <map>
#include <vector>
#include <awesome/core/singleton.h>
#include <awesome/math/vector2.h>
#include "keycode.h"
#include "input_module.h"
#include "input_device.h"

namespace awesome
{
	class Input final : public Singleton<Input>
	{
	public:

		Input(InputModule::API& t_api);

		// update the input state
		void update();
		
		bool isKeyDown(const keycode_t t_key) const;
		bool isKeyPressed(const keycode_t t_key) const;
		bool isKeyReleased(const keycode_t t_key) const;
		bool hasKeyState(const keycode_t t_key, const KeyState t_state) const;

		void setKeyState(const keycode_t t_key, const KeyState t_state);
		void setMousePosition(const float t_x, const float t_y);
		void setMousePosition(const vector2& t_position);
		void setMousePositionValid(const bool t_valid);

		const vec2& getMousePosition() const;
		const vec2& getDeltaMousePosition() const;
		bool isMousePositionValid() const;

		// reset the input state
		void clear();

	private:

		// input api
		InputModule::API& m_api;
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
		bool m_isMousePositionValid;
		// input devices
		std::vector<std::unique_ptr<InputDevice>> m_devices;
		
	};
}