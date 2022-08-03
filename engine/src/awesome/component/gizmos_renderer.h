/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vdtproto/runtime.h>

#include <awesome/graphics/color.h>
#include <awesome/graphics/graphics_component.h>
#include <awesome/graphics/texture_rect.h>
#include <awesome/entity/component.h>

namespace graphics
{
	class Renderer2D;
}

namespace component
{
	class GizmosRenderer : public Component, public graphics::IGraphicsComponent
	{
	public:
		GizmosRenderer() = default;

		enum class Type : int
		{
			None,
			Rect,
			Circle
		};

		Type type{ Type::None };
		graphics::Color color{ graphics::Color::White };

		void render(class graphics::Renderer2D* const renderer) override;

		virtual json::value serialize() const override;
		virtual void deserialize(const json::value& value) override;
		virtual void inspect() override;

		PROTO()
	};
}