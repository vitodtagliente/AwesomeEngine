/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <optional>

#include <awesome/entity/component.h>
#include <awesome/math/vector2.h>

#include "camera_controller_2d_component_generated.h"

CLASS(Type = Component)
class CameraController2dComponent : public Component
{
public:
	CameraController2dComponent();

	void update(double deltaTime) override;

	PROPERTY() float speed;
	PROPERTY() float zoomSpeed;

	GENERATED_BODY()

private:
	std::optional<math::vec2> m_dragPosition;
};