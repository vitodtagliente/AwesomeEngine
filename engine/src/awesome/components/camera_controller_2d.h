/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <optional>

#include <awesome/entity/component.h>
#include <awesome/math/vector2.h>

namespace editor
{
	class Context;
}

namespace graphics
{
	class Renderer;
}

class CameraController2d : public Component
{
public:
	CameraController2d();

	void update(double deltaTime) override;
	void render(graphics::Renderer* const renderer) override;
	void inspect(editor::Context& context) override;

	float speed;

private:
	std::optional<vec2> m_dragPosition;
};