/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>
#include <vector>

#include <awesome/core/singleton.h>
#include <vdtmath/vector2.h>

#include "keycode.h"

class Input final : public Singleton<Input>
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
	void setMouseWheelPosition(const float x, const float y);
	void setMouseWheelPosition(const math::vec2& position);
	void setMousePositionValid(const bool valid);

	const math::vec2& getMousePosition() const;
	const math::vec2& getDeltaMousePosition() const;
	const math::vec2& getMouseWheelPosition() const;
	const math::vec2& getDeltaMouseWheelPosition() const;
	bool isMousePositionValid() const;

	// reset the input state
	void clear();

	bool preventMouseEvents;

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
	// last mouse wheel position
	math::vec2 m_lastMouseWheelPosition;
	// mouse wheel position
	math::vec2 m_mouseWheelPosition;
	// delta mouse wheel position
	math::vec2 m_deltaMouseWheelPosition;
	// is mouse over window?
	bool m_isMousePositionValid;
};