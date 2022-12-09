#include "weapon_component.h"

#include <awesome/core/logger.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>

#include <data/game_settings.h>

void WeaponComponent::init()
{
	Component::init();

	const GameSettings& settings = GameSettings::instance();
	const auto& it = settings.weapons.find(getTypeName());
	if (it != settings.weapons.end())
	{
		m_data = it->second.get();
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

int WeaponComponent::getLevels() const
{
	return static_cast<int>(m_data->levels.size());
}

void WeaponComponent::applyLevel(const int level)
{
	if (level < getLevels())
	{
		WeaponLevel* const data = m_data->levels[level].get();
		duration = data->duration;
		efficacy = data->efficacy;
		frequency = data->frequency;
		quantity = data->quantity;
		range = data->range;
		speed = data->speed;
	}
}
