/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/prefab_asset.h>
#include <awesome/asset/sprite_asset.h>
#include <awesome/entity/component.h>
#include <awesome/math/transform.h>

#include "pawn/pawn.h"

REFLECT_ENUM(CombatType,
	Meele,
	Ranged
)

namespace graphics
{
	class Renderer;
}

class CombatController : public Component
{
public:
	typedef CombatType Type;

	CombatController() = default;
	virtual ~CombatController() = default;

	virtual void init() override;
	virtual void render(graphics::Renderer* const renderer) override;
	virtual void update(double deltaTime) override;

	void attack();

	virtual void inspect() override;
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;

	REFLECT()

private:
	PrefabAssetPtr m_bulletPrefab{ nullptr };
	SpriteAssetPtr m_crosshair{ nullptr };
	float m_crosshairRadius{ 1.0f };
	math::transform m_crosshairTransform;
	math::vec3 m_direction{ math::vec3::right };
	Pawn* m_pawn{ nullptr };
	Type m_type{ Type::Meele };
};