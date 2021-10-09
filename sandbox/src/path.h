/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>
#include <awesome/graphics/color.h>
#include <awesome/scene/component.h>
#include <vdtmath/vector3.h>

class Path : public Component
{
public:
	Path();

	void render(class Renderer& renderer) override;

	std::vector<math::vec3> steps;
	Color color;
};