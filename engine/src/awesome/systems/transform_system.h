/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/ecs.h>
#include <awesome/core/reflection.h>
#include <awesome/math/transform.h>

class TransformSystem : public ecs::System<TransformSystem, math::transform>
{
public:
	virtual void update(const double deltaTime) override;

	REFLECT()
};