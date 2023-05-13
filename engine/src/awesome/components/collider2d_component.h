/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>
#include <variant>

#include <awesome/engine/engine_settings.h>
#include <awesome/math/circle.h>
#include <awesome/math/rectangle.h>
#include <awesome/math/vector2.h>
#include <awesome/scene/component.h>

#include "collider2d_component_generated.h"

namespace graphics
{
	class Renderer;
}

ENUM()
enum class ColliderType2D : int
{
	Circle = 0,
	Rect
};

CLASS(Type = Component)
class Collider2DComponent : public Component
{
public:
	friend class Collider2DComponentInspector;

	Collider2DComponent();

	const ColliderType2D type() const { return m_type; }

	virtual void init() override;
	virtual void render(graphics::Renderer& renderer) override;
	virtual void update(double) override;

	bool collide(const Collider2DComponent& other);

	PROPERTY() math::vec2 bounds{ 1.0f, 1.0f };
	PROPERTY() bool isTrigger{ false };

	GENERATED_BODY()

private:
	void update_aabb();

	std::variant<math::circle, math::rect> m_aabb;
	bool m_isColliding{ false };
	const RendererSettings& m_renderSettings;
	PROPERTY() ColliderType2D m_type{ ColliderType2D::Rect };
};