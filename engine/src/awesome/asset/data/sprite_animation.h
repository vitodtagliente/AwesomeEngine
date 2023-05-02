/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/asset/image_asset.h>
#include <awesome/core/reflection.h>
#include <awesome/graphics/texture_rect.h>

#include "sprite_animation_generated.h"

struct SpriteAnimationFrame : public IType
{
	PROPERTY() graphics::TextureRect rect;
	PROPERTY() double duration{ 1.0f };

	GENERATED_BODY()
};

CLASS()
struct SpriteAnimation : public IType
{
	PROPERTY() ImageAsset image;
	PROPERTY() int startingFrame{ 0 };
	PROPERTY() std::vector<SpriteAnimationFrame> frames;

	GENERATED_BODY()
};