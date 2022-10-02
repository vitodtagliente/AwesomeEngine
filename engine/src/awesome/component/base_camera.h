/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/camera.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>

#include "base_camera_generated.h"

CLASS()
class BaseCamera : public Component
{
public:
	BaseCamera();
	virtual ~BaseCamera() = default;

	virtual void update(double) override;

	virtual math::vec3 screenToWorldCoords(const math::vec2& point);

	static BaseCamera* const main();

	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;
	virtual void inspect() override;

	PROPERTY() graphics::Color color;

	GENERATED_BODY()

protected:
	std::unique_ptr<graphics::Camera> m_data;
};