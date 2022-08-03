/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>

class Rotator : public Component
{
public:
	Rotator();

	void update(double deltaTime) override;
	void inspect() override;

	float speed;

	PROTO()
};