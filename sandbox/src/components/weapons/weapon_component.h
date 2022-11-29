/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>

#include <data/game_settings.h>

#include "weapon_component_generated.h"

CLASS()
class WeaponComponent : public Component
{
public:
	WeaponComponent() = default;
	virtual ~WeaponComponent() = default;

	virtual void init() override;
	virtual void inspect() override;

	virtual bool upgrade();

	inline int getLevel() const { return m_level; }
	inline int getLevels() const { return static_cast<int>(m_data.levels.size()); }

	PROPERTY() float efficacy{ 1.f };
	PROPERTY() float frequency{ 1.f };
	PROPERTY() int power{ 1 };
	PROPERTY() int quantity{ 1 };
	PROPERTY() float range{ 1.f };
	PROPERTY() float speed{ 1.f };

protected:
	void applyLevel(int level);

	WeaponItem m_data;
	int m_level{ 1 };

	GENERATED_BODY()
};