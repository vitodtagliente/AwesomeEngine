/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/image_asset.h>
#include <awesome/entity/component.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/texture_rect.h>

#include "sprite_renderer_component_generated.h"

namespace graphics
{
	class Renderer2D;
}

CLASS(Type = Component)
class SpriteRendererComponent : public Component
{
public:
	SpriteRendererComponent() = default;
	virtual ~SpriteRendererComponent() = default;

	PROPERTY() graphics::Color color{ graphics::Color::White };
	PROPERTY() bool flipX{ false };
	PROPERTY() bool flipY{ false };
	PROPERTY() ImageAssetPtr image;
	PROPERTY() graphics::TextureRect rect;

	virtual void render(graphics::Renderer2D* const renderer) override;
	virtual void update(double deltaTime) override;

	GENERATED_BODY()
};