/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>
#include <vector>
#include <vdtmath/vector3.h>

#include <awesome/graphics/color.h>
#include <awesome/scene/component.h>

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

	void init() override;
	void render(graphics::Renderer& renderer) override;
	void inspect(editor::Context& context) override;

	static Path* const findOrRandom(class World& world, const std::string& name);

	std::vector<math::vec3> steps;
	graphics::Color color;
};