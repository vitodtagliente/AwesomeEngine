/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <optional>
#include <awesome/scene/component.h>
#include <vdtmath/vector2.h>

class CameraController2d : public Component
{
public:
	CameraController2d();

	void update(class World& world, double deltaTime) override;
	void render(class Renderer& renderer) override;
	void inspect() override;

	float speed;

private:
	std::optional<math::vec2> m_dragPosition;
};