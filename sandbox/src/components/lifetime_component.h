/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>

#include "lifetime_component_generated.h"

CLASS()
class LifetimeComponent : public Component
{
public:
	LifetimeComponent() = default;
	virtual ~LifetimeComponent() = default;

	virtual void update(double deltaTime) override;

	virtual void inspect() override;
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;

	GENERATED_BODY()

private:
	double m_lifetime{ 1.0 };
	double m_timer{ 0.0 };
};