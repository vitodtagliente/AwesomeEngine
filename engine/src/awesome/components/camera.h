/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>
#include <awesome/graphics/color.h>
#include <awesome/math/matrix4.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>

class Camera : public Component
{
public:
	Camera() = default;
	virtual ~Camera() = default;

	virtual void update(double) override;

	math::vec3 screenToWorldCoords(const math::vec2& point);

	static Camera* const main();

	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;
	virtual void inspect() override;

	REFLECT()

	graphics::Color color;

protected:
	virtual math::matrix4 computeProjectionMatrix();
};