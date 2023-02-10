/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/prefab_asset.h>
#include <awesome/entity/component.h>

#include "shoot_component_generated.h"

CLASS(Type = Component)
class ShootComponent : public Component
{
public:
	ShootComponent() = default;
	virtual ~ShootComponent() = default;

	virtual void init() override;
	virtual void update(double deltaTime) override;

	GENERATED_BODY()

private:
	double m_activationTimer{ 0 };
	class AimComponent* m_aim;
	PROPERTY() PrefabAssetPtr m_bulletPrefab;
	PROPERTY() int m_damage{ 1 };
	PROPERTY() double m_frequency{ 1.0 };

	void shoot();
};