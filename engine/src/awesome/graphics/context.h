/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>
#include <vdtmath/vector3.h>
#include "color.h"

class Context
{
public:

	void clear(const Color& color);
	void viewport(int width, int height);
	void drawLines(const std::vector<std::pair<math::vec3, Color>>& lines);
};