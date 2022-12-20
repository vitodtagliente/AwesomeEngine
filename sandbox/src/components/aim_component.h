/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/sprite_asset.h>
#include <awesome/entity/component.h>
#include <awesome/graphics/graphics_component.h>
#include <awesome/math/vector3.h>

#include "aim_component_generated.h"

namespace graphics
{
	class Renderer2D;
}

CLASS(Category = Component)
class AimComponent : public graphics::IGraphicsComponent, public Component
{
public:
	AimComponent() = default;
	virtual ~AimComponent() = default;

	virtual void render(graphics::Renderer2D* const renderer) override;
	virtual void update(double deltaTime) override;

	const math::vec3& getDirection() const { return m_direction; }
	const math::vec3& getPosition() const { return m_position; }

	GENERATED_BODY()

private:
	math::vec3 m_direction{ math::vec3::right };
	PROPERTY() float m_maxRange{ 3.f };
	PROPERTY() float m_maxSize{ .8f };
	PROPERTY() float m_minRange{ 1.5f };
	PROPERTY() float m_minSize{ .4f };
	math::vec3 m_position{ math::vec3::zero };
	float m_range{ 0.0f };
	bool m_reduceSize{ true };
	PROPERTY() float m_resizeSpeed{ .1f };
	float m_size{ 0.0f };
	PROPERTY() SpriteAssetPtr m_sprite;
	bool m_visible{ true };
};