/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

#include <awesome/asset/sprite_asset.h>
#include <awesome/entity/component.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/graphics_component.h>

#include "sprite_renderer_component_generated.h"

CLASS(Category = Component)
class SpriteRendererComponent : public graphics::IGraphicsComponent, public Component
{
public:
	SpriteRendererComponent() = default;
	virtual ~SpriteRendererComponent() = default;

	SpriteAssetPtr sprite;
	PROPERTY() graphics::Color color{ graphics::Color::White };
	PROPERTY() bool flipX{ false };
	PROPERTY() bool flipY{ false };

	virtual void render(graphics::Renderer2D* const renderer) override;
	virtual void update(double deltaTime) override;

	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;

	GENERATED_BODY()
};