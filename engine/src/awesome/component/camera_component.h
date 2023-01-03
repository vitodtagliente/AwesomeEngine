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

	const graphics::Camera& getData() const { return *m_data; }
	virtual math::vec3 screenToWorldCoords(const math::vec2& point);

	virtual void update(double) override;

	static CameraComponent* const main();

	PROPERTY() graphics::Color color;

	GENERATED_BODY()

protected:
	std::unique_ptr<graphics::Camera> m_data;
};