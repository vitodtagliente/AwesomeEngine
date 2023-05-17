/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/image_asset.h>
#include <awesome/graphics/texture_rect.h>
#include <awesome/math/vector3.h>
#include <awesome/scene/component.h>

#include "aim_component_generated.h"

namespace graphics
{
	class Renderer;
}

CLASS(Type = Component)
class AimComponent : public Component
{
public:
	virtual void render(graphics::Renderer& renderer) override;
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
	PROPERTY() ImageAsset m_image;
	PROPERTY() graphics::TextureRect m_rect;
	bool m_visible{ true };
};