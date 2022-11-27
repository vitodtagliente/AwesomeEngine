/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>

class WeaponComponent : public Component
{
public:
	WeaponComponent() = default;
	virtual ~WeaponComponent() = default;

	virtual bool upgrade() { return false; };
};