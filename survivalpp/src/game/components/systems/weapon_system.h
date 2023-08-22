#pragma once

#include "ecs/ecs.h"

#include "game/components/weapon.h"

class WeaponSystem : public System<Weapon>
{
protected:
	virtual void process(double delta_time, Weapon& weapon);
};