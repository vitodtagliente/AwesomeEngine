/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>

#include "rotator_component_generated.h"

CLASS(Category = Component)
class RotatorComponent : public Component
{
public:
	RotatorComponent();

	virtual void update(double deltaTime) override;

	PROPERTY() float speed;

	GENERATED_BODY()
};