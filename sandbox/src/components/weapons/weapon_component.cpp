#include "weapon_component.h"

#include <awesome/core/logger.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>

void WeaponComponent::init()
{
	Component::init();

	const GameSettings& settings = GameSettings::instance();
	const auto& it = settings.weapons.find(getTypeName());
	if (it != settings.weapons.end())
	{
		m_data = it->second;
		applyLevel(0);
	}
	else
	{
		ERR_LOG("WeaponComponent", std::string("Cannot find the ") + getTypeName() + " weapon...");
		getOwner()->removeComponent(this);
	}
}

void WeaponComponent::inspect()
{
	Component::inspect();
	Layout::separator();

	if (Layout::button("Upgrade"))
	{
		upgrade();
	}
}

bool WeaponComponent::upgrade()
{
	if (m_level < getLevels())
	{
		applyLevel(m_level++);
		return true;
	}
	return false;
}

void WeaponComponent::applyLevel(const int level)
{
	if (level < getLevels())
	{
		const WeaponLevel& data = m_data.levels[level];
		efficacy = data.efficacy;
		frequency = data.frequency;
		power = data.power;
		quantity = data.quantity;
		range = data.range;
		speed = data.speed;
	}
}
