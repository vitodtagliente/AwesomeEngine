/// Copyright (c) Vito Domenico Tagliente
#pragma once

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

	virtual void inspect() override;
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;

	REFLECT()

private:
	SpriteAssetPtr m_crosshair;
	float m_crosshairRadius{ 1.0f };
	math::transform m_crosshairTransform;
	Pawn* m_pawn;
	Type m_type{ Type::Meele };
};