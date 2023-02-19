/// Copyright (c) Vito Domenico Tagliente
#pragma once

struct WindowLayout final
{
	WindowLayout() = delete;

	static void begin(char* const name);
	static void end();
	static bool isFocused();
	static bool isHovered();
};