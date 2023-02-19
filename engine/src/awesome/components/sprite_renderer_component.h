/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/image_asset.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/texture_rect.h>
#include <awesome/scene/component.h>

class SpriteRendererComponent : public Component
{
public:
	SpriteRendererComponent() = default;
	virtual ~SpriteRendererComponent() = default;

	graphics::Color color{ graphics::Color::White };
	bool flipX{ false };
	bool flipY{ false };
	ImageAssetPtr image;
	graphics::TextureRect rect;

	virtual void update(double deltaTime) override;

	virtual void inspect();
	virtual json::value serialize() const override;

	static constexpr char* const id = "SpriteRenderer";
};