/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/image_asset.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/texture_rect.h>
#include <awesome/scene/component.h>

#include "sprite_renderer_component_generated.h"

CLASS(Type = Component, Category = Graphics)
class SpriteRendererComponent : public Component
{
public:
	SpriteRendererComponent() = default;
	virtual ~SpriteRendererComponent() = default;

	PROPERTY() graphics::Color color{ graphics::Color::White };
	PROPERTY() bool flipX{ false };
	PROPERTY() bool flipY{ false };
	PROPERTY() std::shared_ptr<ImageAsset> image;
	PROPERTY() graphics::TextureRect rect;

	virtual void update(double deltaTime) override;

	GENERATED_BODY()
};