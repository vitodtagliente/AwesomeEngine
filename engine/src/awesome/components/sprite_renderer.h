/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>
#include <awesome/graphics/texture_rect.h>

namespace editor
{
	class Context;
}

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

	void render(graphics::Renderer* const renderer) override;
	void inspect(editor::Context& context) override;
};