/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/prefab_asset.h>

#include "weapon_component.h"

#include "rotating_shields_component_generated.h"

CLASS(Category = Component)
class RotatingShieldsComponent : public WeaponComponent
{
public:
	RotatingShieldsComponent() = default;
	virtual ~RotatingShieldsComponent() = default;

	virtual void init() override;
	virtual void update(double deltaTime) override;

	GENERATED_BODY()

private:
	void activate();
	
	PROPERTY() PrefabAssetPtr m_bulletPrefab;
	double m_activationTimer{ 0 };
	double m_deactivationTimer{ 0 };
	std::vector<std::pair<Entity*, float>> m_bullets;
};