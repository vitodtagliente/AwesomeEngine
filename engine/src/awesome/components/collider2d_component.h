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
enum class Collision2DShapeType : int
{
	Circle = 0,
	Rect
};

CLASS(Type = Component)
class Collider2dComponent : public Component
{
public:
	friend class Collider2dComponentInspector;

	Collider2dComponent();

	const Collision2DShapeType type() const { return m_type; }

	virtual void init() override;
	virtual void render(graphics::Renderer& renderer) override;
	virtual void uninit() override;
	virtual void update(double) override;

	bool collide(const Collider2dComponent& other);

	PROPERTY() math::vec2 bounds{ 1.0f, 1.0f };
	PROPERTY() bool isTrigger{ false };

	static const std::vector<Collider2dComponent*>& components() { return s_components; }

	GENERATED_BODY()

private:
	void update_aabb();

	std::variant<math::circle, math::rect> m_aabb;
	bool m_isColliding{ false };
	const RendererSettings& m_renderSettings;
	PROPERTY() Collision2DShapeType m_type{ Collision2DShapeType::Rect };

	static inline std::vector<Collider2dComponent*> s_components;
};