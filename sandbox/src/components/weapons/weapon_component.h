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

	virtual void init() override;
	virtual void inspect() override;

	virtual bool upgrade();

	inline int getLevel() const { return m_level; }
	int getLevels() const;

	PROPERTY() float efficacy{ 1.f };
	PROPERTY() float frequency{ 1.f };
	PROPERTY() int power{ 1 };
	PROPERTY() int quantity{ 1 };
	PROPERTY() float range{ 1.f };
	PROPERTY() float speed{ 1.f };

protected:
	void applyLevel(int level);

	class WeaponItem* m_data{ nullptr };
	int m_level{ 1 };

	GENERATED_BODY()
};