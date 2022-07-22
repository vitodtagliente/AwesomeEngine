/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

#include <awesome/asset/sprite_asset.h>
#include <awesome/entity/component.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/graphics_component.h>

namespace graphics
{
	class Renderer2D;
}

namespace component
{
	class SpriteRenderer : public Component, public graphics::IGraphicsComponent
	{
	public:
		SpriteRenderer() = default;
		virtual ~SpriteRenderer() = default;

		SpriteAssetPtr sprite;
		graphics::Color color{ graphics::Color::White };
		bool flipX{ false };
		bool flipY{ false };

		virtual void render(graphics::Renderer2D* const renderer) override;
		virtual void update(double deltaTime) override;

		virtual json::value serialize() const override;
		virtual void deserialize(const json::value& value) override;
		virtual void inspect() override;

		REFLECT()
	};
}