/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

struct WindowLayout final
{
	WindowLayout() = delete;

	static void begin(const std::string& name);
	static void end();
	static bool isFocused();
	static bool isHovered();
};