/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>

#include "shoot_component_generated.h"

CLASS(Category = Component)
class ShootComponent : public Component
{
public:
	ShootComponent() = default;
	virtual ~ShootComponent() = default;

	virtual void init() override;
	virtual void update(double deltaTime) override;

	GENERATED_BODY()

private:
	class AimComponent* m_aim;
};