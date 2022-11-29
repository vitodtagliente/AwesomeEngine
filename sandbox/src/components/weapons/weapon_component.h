/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>

#include "weapon_component_generated.h"

CLASS()
class WeaponComponent : public Component
{
public:
	WeaponComponent() = default;
	virtual ~WeaponComponent() = default;

	virtual bool upgrade() { return false; }

	PROPERTY() float efficacy{ 1.f };
	PROPERTY() float frequency{ 1.f };
	PROPERTY() int power{ 1 };
	PROPERTY() int quantity{ 1 };
	PROPERTY() float range{ 1.f };
	PROPERTY() float speed{ 1.f };

	GENERATED_BODY()
};