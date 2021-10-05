/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>
#include <vdtmath/vector2.h>
#include "color.h"

class Context
{
public:

	void clear(const Color& color);
	void viewport(int width, int height);
	void drawLines(const std::vector<std::pair<math::vec2, Color>>& lines);
};