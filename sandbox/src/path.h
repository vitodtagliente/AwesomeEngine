/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>
#include <awesome/graphics/color.h>
#include <awesome/scene/component.h>
#include <vdtmath/vector3.h>

namespace editor
{
	class Context;
}

namespace graphics
{
	class Renderer;
}

class Path : public Component
{
public:
	Path();

	void render(graphics::Renderer& renderer) override;
	void inspect(editor::Context& context) override;

	std::vector<math::vec3> steps;
	graphics::Color color;
};