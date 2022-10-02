/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <optional>

#include <awesome/entity/component.h>
#include <awesome/math/vector2.h>

#include "camera_controller_2d_generated.h"

CLASS()
class CameraController2d : public Component
{
public:
	CameraController2d();

	void update(double deltaTime) override;

	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;
	virtual void inspect() override;

	PROPERTY() float speed;
	PROPERTY() float zoomSpeed;

	GENERATED_BODY()

private:
	std::optional<math::vec2> m_dragPosition;
};