/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/scene/component.h>
#include <awesome/graphics/texture_rect.h>

class SpriteRenderer : public Component
{
public:
	SpriteRenderer();

	class Texture* texture;
	TextureRect rect;

	void render(class Renderer& renderer) override;
	void inspect() override;
};