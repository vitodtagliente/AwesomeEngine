/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>
#include <awesome/math/vector3.h>

class Crosshair : public Component
{
public:
	Crosshair() = default;
	virtual ~Crosshair() = default;

	virtual void init() override;
	virtual void update(double deltaTime) override;

	virtual void inspect() override;
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;

	PROTO()

private:
	math::vec3 _minScale{ .4f, .4f, 1.f };
	math::vec3 _maxScale{ .8f, .8f, 1.f };
	float _scaleSpeed = 1.f;
	bool _scaleUp{ false };
};