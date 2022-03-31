/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

#include <awesome/data/sprite_asset.h>
#include <awesome/graphics/color.h>
#include <awesome/entity/component.h>

namespace graphics
{
	class Renderer;
}

class SpriteRenderer : public Component
{
public:
	SpriteRenderer();

	SpriteAssetPtr sprite;
	graphics::Color color;

	void render(graphics::Renderer* const renderer) override;

	virtual json::value serialize() const override;
	virtual void inspect() override;

	REFLECT()
};