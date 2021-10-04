/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>
#include <vector>
#include <GLFW/glfw3.h>
#include <vdtmath/vector2.h>

#include <awesome/core/singleton.h>
#include "keycode.h"

class Input : public Singleton<Input>
{
public:
	Input();

	// update the input state
	void update();

	bool isKeyDown(const keycode_t key) const;
	bool isKeyPressed(const keycode_t key) const;
	bool isKeyReleased(const keycode_t key) const;
	bool hasKeyState(const keycode_t key, const KeyState state) const;

	void setKeyState(const keycode_t key, const KeyState state);
	void setMousePosition(const float x, const float y);
	void setMousePosition(const math::vec2& position);
	void setMousePositionValid(const bool valid);

	const math::vec2& getMousePosition() const;
	const math::vec2& getDeltaMousePosition() const;
	bool isMousePositionValid() const;

	// reset the input state
	void clear();

private:

	// last keys states
	std::map<keycode_t, KeyState> m_lastKeysState;
	// keys states
	std::map<keycode_t, KeyState> m_keysState;
	// last mouse position
	math::vec2 m_lastMousePosition;
	// mouse position
	math::vec2 m_mousePosition;
	// delta mouse position
	math::vec2 m_deltaMousePosition;
	// is mouse over window?
	bool m_isMousePositionValid;
};