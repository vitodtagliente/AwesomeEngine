/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/image_asset.h>
#include <awesome/entity/component.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/texture_rect.h>
#include <awesome/ui/ui_component.h>

#include "image_component_generated.h"

CLASS(Type = Component, Category = UI)
class ImageComponent : public IUIComponent, public Component
{
public:
	ImageComponent() = default;
	virtual ~ImageComponent() = default;

	PROPERTY() graphics::Color color{ graphics::Color::White };
	PROPERTY() ImageAssetPtr image;
	PROPERTY() graphics::TextureRect rect;

	virtual void render(graphics::Renderer2D* const renderer) override;
	virtual void update(double deltaTime) override;

	GENERATED_BODY()
};