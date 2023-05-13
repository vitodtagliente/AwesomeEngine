/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <optional>

#include <awesome/math/vector2.h>
#include <awesome/scene/component.h>

#include "camera_controller2d_component_generated.h"

CLASS(Type = Component)
class CameraController2DComponent : public Component
{
public:
	void update(double deltaTime) override;

	PROPERTY() float speed{ 0.05f };
	PROPERTY() float zoomSpeed{ 1.0f };

	GENERATED_BODY()

private:
	std::optional<math::vec2> m_dragPosition;
};