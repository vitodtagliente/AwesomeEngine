/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/sprite_asset.h>
#include <awesome/entity/component.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/graphics_component.h>

#include "image_component_generated.h"

CLASS(Type = Component, Category = UI)
class ImageComponent : public graphics::IGraphicsComponent, public Component
{
public:
	ImageComponent() = default;
	virtual ~ImageComponent() = default;

	PROPERTY() SpriteAssetPtr sprite;
	PROPERTY() graphics::Color color{ graphics::Color::White };

	virtual void render(graphics::Renderer2D* const renderer) override;
	virtual void update(double deltaTime) override;

	GENERATED_BODY()
};