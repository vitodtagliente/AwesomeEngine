/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/prefab_asset.h>
#include <awesome/asset/sprite_asset.h>
#include <awesome/graphics/graphics_component.h>
#include <awesome/entity/component.h>
#include <awesome/math/transform.h>

#include "pawn.h"
#include "combat_type.h"

namespace graphics
{
	class Renderer2D;
}

class CombatController : public Component, public graphics::IGraphicsComponent
{
public:
	typedef CombatType Type;

	CombatController() = default;
	virtual ~CombatController() = default;

	virtual void init() override;
	virtual void render(graphics::Renderer2D* const renderer) override;
	virtual void update(double deltaTime) override;

	void attack();

	virtual void inspect() override;
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;

	PROTO()

private:
	PrefabAssetPtr m_bulletPrefab{ nullptr };
	SpriteAssetPtr m_crosshair{ nullptr };
	float m_crosshairRadius{ 1.0f };
	math::transform m_crosshairTransform;
	math::vec3 m_direction{ math::vec3::right };
	Pawn* m_pawn{ nullptr };
	Type m_type{ Type::Meele };
};