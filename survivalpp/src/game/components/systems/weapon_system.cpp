#include "weapon_system.h"

void WeaponSystem::process(const double delta_time, Weapon& weapon)
{
	weapon.update(delta_time);
}
