/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/scene/component.h>
#include <awesome/graphics/texture_rect.h>

namespace graphics
{
	class Renderer;
	class Texture;
}

class SpriteRenderer : public Component
{
public:
	SpriteRenderer();

	class graphics::Texture* texture;
	graphics::TextureRect rect;

	void render(graphics::Renderer& renderer) override;
	void inspect() override;
};