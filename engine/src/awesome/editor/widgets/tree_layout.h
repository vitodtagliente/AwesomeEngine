/// Copyright (c) Vito Domenico Tagliente
#pragma once

struct TreeLayout final
{
	TreeLayout() = delete;

	static bool begin(const char* const name, bool selected);
	static void end();
};