/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/camera.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>

#include "camera_component_generated.h"

CLASS()
class CameraComponent : public Component
{
public:
	CameraComponent();
	virtual ~CameraComponent() = default;

	virtual void update(double) override;

	virtual math::vec3 screenToWorldCoords(const math::vec2& point);

	static CameraComponent* const main();

	virtual void inspect() override;

	PROPERTY() graphics::Color color;

	GENERATED_BODY()

protected:
	std::unique_ptr<graphics::Camera> m_data;
};