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

	PROPERTY() float efficacy{ 0.f };
	PROPERTY() float frequency{ 0.f };
	PROPERTY() int quantity{ 0 };
	PROPERTY() float range{ 0.f };
	PROPERTY() float speed{ 0.f };

protected:
	void applyLevel(int level);

	class WeaponItem* m_data{ nullptr };
	int m_level{ 1 };

	GENERATED_BODY()
};