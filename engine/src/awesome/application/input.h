/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>

#include <awesome/core/singleton.h>
#include <vdtmath/vector2.h>

#include "keycode.h"

class Input final : public Singleton<Input>
{
public:
	// update the input state
	void update();

	bool isKeyDown(keycode_t key) const;
	bool isKeyPressed(keycode_t key) const;
	bool isKeyReleased(keycode_t key) const;
	bool hasKeyState(keycode_t key, const KeyState state) const;

	float getAxis(keycode_t key1, keycode_t key2) const;

	void setKeyState(keycode_t key, KeyState state);
	void setMousePosition(float x, float y);
	void setMousePosition(const math::vec2& position);
	void setMouseWheelPosition(float x, float y);
	void setMouseWheelPosition(const math::vec2& position);
	void setMousePositionValid(bool valid);

	const math::vec2& getMousePosition() const;
	const math::vec2& getDeltaMousePosition() const;
	const math::vec2& getMouseWheelPosition() const;
	const math::vec2& getDeltaMouseWheelPosition() const;
	bool isMousePositionValid() const;

	// reset the input state
	void clear();

	bool preventKeyEvents{ false };
	bool preventMouseEvents{ false };

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
	bool m_isMousePositionValid{ true };
};