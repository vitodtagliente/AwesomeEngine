/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <functional>

struct DragLayout final
{
	DragLayout() = delete;

	static void begin(const char* const name, const char* const item, void* const data, size_t size);
	static void end(const char* const name, const std::function<void(void*, size_t)>& handler);
};