/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/engine/keycode.h>

struct InteractionLayout final
{
	InteractionLayout() = delete;

	static bool isKeyDown(keycode_t keycode);
	static bool isKeyPressed(keycode_t keycode);
	static bool isKeyReleased(keycode_t keycode);
	static bool isItemHovered();
	static bool isMouseClicked();
	static void scroll(float position);
	static void scrollToBottom();
};