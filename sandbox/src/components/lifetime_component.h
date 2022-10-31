/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>

#include "lifetime_component_generated.h"

CLASS(Category = Component)
class LifetimeComponent : public Component
{
public:
	LifetimeComponent() = default;
	virtual ~LifetimeComponent() = default;

	virtual void init() override;
	virtual void update(double deltaTime) override;

	PROPERTY() double value{ 1.0 };

	GENERATED_BODY()

private:
	double m_timer{ 0.0 };
};