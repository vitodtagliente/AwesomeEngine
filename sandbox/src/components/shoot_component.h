/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/prefab_asset.h>
#include <awesome/scene/component.h>

#include "shoot_component_generated.h"

CLASS(Type = Component)
class ShootComponent : public Component
{
public:
	virtual void init() override;
	virtual void update(double deltaTime) override;

	GENERATED_BODY()

private:
	void shoot();
	
	double m_activationTimer{ 0 };
	class AimComponent* m_aim{ nullptr };
	PROPERTY() PrefabAsset m_bullet;
	PROPERTY() int m_damage{ 1 };
	PROPERTY() double m_frequency{ 1.0 };
};