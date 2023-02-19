/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <functional>

struct DialogLayout final
{
	DialogLayout() = delete;

	static bool saveFile(const char* const name, const char* const extension);
};