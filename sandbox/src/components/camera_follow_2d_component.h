/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>
#include <awesome/entity/entity.h>

#include "camera_follow_2d_component_generated.h"

CLASS()
class CameraFollow2dComponent : public Component
{
public:
	CameraFollow2dComponent() = default;
	virtual ~CameraFollow2dComponent() = default;

	virtual void update(double deltaTime) override;

	virtual void inspect() override;
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;

	GENERATED_BODY()

private:
	float m_speed{ 3.0f };
	Entity* m_target{ nullptr };
};