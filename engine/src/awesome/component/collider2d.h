/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <functional>

#include <vdtproto/runtime.h>

#include <awesome/entity/component.h>
#include <awesome/graphics/graphics_component.h>
#include <awesome/math/vector2.h>

#include "shape_type.h"

namespace graphics
{
	class Renderer2D;
}

namespace component
{
	class Collider2d : public Component, public graphics::IGraphicsComponent
	{
	public:
		typedef ShapeType Type;

		Collider2d() = default;
		virtual ~Collider2d() = default;

		void render(graphics::Renderer2D* const renderer) override;

		bool collide(const Collider2d& other) const;

		std::function<void(const Collider2d&)> onTrigger;

		virtual json::value serialize() const override;
		virtual void deserialize(const json::value& value) override;
		virtual void inspect() override;

		bool isTrigger{ false };

		PROTO()

	private:
		Type m_type{ Type::Rect };
		math::vec2 m_rectSize{ 1.0f, 1.0f };
		float m_circleSize{ 1.0f };
	};
}