/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "weapon_component.h"

#include "healer_component_generated.h"

CLASS(Category = Component)
class HealerComponent : public WeaponComponent
{
public:
	HealerComponent() = default;
	virtual ~HealerComponent() = default;

	virtual void init() override;
	virtual void update(double deltaTime) override;

	PROPERTY() int efficacy{ 1 };
	PROPERTY() double frequency{ 1 };

	GENERATED_BODY()

private:
	class HealthComponent* m_health;
	double m_activationTimer{ 0 };
};