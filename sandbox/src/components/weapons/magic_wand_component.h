/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/prefab_asset.h>

#include "weapon_component.h"

#include "magic_wand_component_generated.h"

CLASS(Category = Component)
class MagicWandComponent : public WeaponComponent
{
public:
	MagicWandComponent() = default;
	virtual ~MagicWandComponent() = default;

	virtual void init() override;
	virtual void update(double deltaTime) override;

	GENERATED_BODY()

private:
	PROPERTY() PrefabAssetPtr m_bulletPrefab;
	double m_activationTimer{ 0 };

	void activate();
};