/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/scene/component.h>

#include "lifetime_component_generated.h"

CLASS(Type = Component)
class LifetimeComponent : public Component
{
public:
	virtual void init() override;
	virtual void update(double deltaTime) override;
	
	PROPERTY() double lifetime{ 1.0 };

	GENERATED_BODY()
private:
	double m_timer{ 0 };
};