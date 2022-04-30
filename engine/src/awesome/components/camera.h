/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>
#include <awesome/graphics/color.h>

namespace graphics
{
	class Renderer;
}

class Camera : public Component
{
public:
	Camera() = default;
	virtual ~Camera() = default;

	void render(graphics::Renderer* const renderer) override;

	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;
	virtual void inspect() override;

	REFLECT()

	graphics::Color color;
};