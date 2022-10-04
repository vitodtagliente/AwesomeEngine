/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>

#include "rotator_component_generated.h"

CLASS()
class RotatorComponent : public Component
{
public:
	RotatorComponent();

	void update(double deltaTime) override;
	void inspect() override;

	PROPERTY()
	float speed;

	GENERATED_BODY()
};