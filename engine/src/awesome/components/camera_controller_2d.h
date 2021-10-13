/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <optional>
#include <vdtmath/vector2.h>

#include <awesome/entity/component.h>

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

	void update(class World& world, double deltaTime) override;
	void render(graphics::Renderer& renderer) override;
	void inspect(editor::Context& context) override;

	float speed;

private:
	std::optional<math::vec2> m_dragPosition;
};