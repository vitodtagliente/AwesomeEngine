/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>
#include <awesome/math/vector3.h>

#include "crosshair_component_generated.h"

CLASS()
class CrosshairComponent : public Component
{
public:
	CrosshairComponent() = default;
	virtual ~CrosshairComponent() = default;

	virtual void init() override;
	virtual void update(double deltaTime) override;

	virtual void inspect() override;
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;

	GENERATED_BODY()

private:
	math::vec3 _minScale{ .4f, .4f, 1.f };
	math::vec3 _maxScale{ .8f, .8f, 1.f };
	float _scaleSpeed = 1.f;
	bool _scaleUp{ false };
};