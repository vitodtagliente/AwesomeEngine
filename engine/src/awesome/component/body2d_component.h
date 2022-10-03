/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>

#include "body2d_component_generated.h"

CLASS()
class Body2dComponent : public Component
{
public:
	Body2dComponent() = default;
	virtual ~Body2dComponent() = default;

	virtual void init() override;

	void move(const math::vec2& amount);
	void move(const math::vec3& amount);

	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;
	virtual void inspect() override;

	GENERATED_BODY()

private:
	class Collider2dComponent* m_collider{ nullptr };
};