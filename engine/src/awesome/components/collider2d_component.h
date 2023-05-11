/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/engine/engine_settings.h>
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
	Collider2dComponent();

	virtual void init() override;
	virtual void render(graphics::Renderer& renderer) override;
	virtual void uninit() override;

	bool collide(const Collider2dComponent& other);

	PROPERTY() bool isTrigger{ false };

	static const std::vector<Collider2dComponent*>& components() { return s_components; }

	GENERATED_BODY()

private:
	PROPERTY() Collision2DShapeType m_type{ Collision2DShapeType::Rect };
	PROPERTY() math::vec2 m_bounds{ 1.0f, 1.0f };
	bool m_isColliding{ false };
	const RendererSettings& m_renderSettings;

	static inline std::vector<Collider2dComponent*> s_components;
};