/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

#include <awesome/entity/component.h>
#include <awesome/graphics/texture.h>
#include <awesome/graphics/texture_rect.h>

namespace graphics
{
	class Renderer;
}

class SpriteRenderer : public Component
{
public:
	SpriteRenderer();

	std::shared_ptr<graphics::Texture> texture;
	graphics::TextureRect rect;

	void render(graphics::Renderer* const renderer) override;
};