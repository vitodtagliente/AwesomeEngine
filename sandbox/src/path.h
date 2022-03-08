/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>
#include <vector>
#include <vdtmath/vector3.h>

#include <awesome/core/typename.h>
#include <awesome/graphics/color.h>
#include <awesome/entity/component.h>

namespace graphics
{
	class Renderer;
}

class Path : public Component
{
public:
	Path();

	void init() override;
	void render(graphics::Renderer* const renderer) override;

	static Path* const findOrRandom(class World& world, const std::string& name);

	virtual json::value toJson() const override;

	std::vector<math::vec3> steps;
	graphics::Color color;
};

TYPENAME(Path)