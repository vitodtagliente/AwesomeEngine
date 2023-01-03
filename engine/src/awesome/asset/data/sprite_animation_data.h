/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <vector>

#include <awesome/asset/image_asset.h>
#include <awesome/core/reflection.h>
#include <awesome/graphics/texture_rect.h>

#include "sprite_animation_data_generated.h"

CLASS(Type = Data)
struct SpriteAnimationFrame : public Type
{
	PROPERTY() graphics::TextureRect rect;
	PROPERTY() double duration;

	GENERATED_BODY()
};

CLASS(Type = Data, AssetType = SpriteAnimation)
struct SpriteAnimationData : public Type
{
	PROPERTY() ImageAssetPtr image;
	PROPERTY() int startingFrame;
	PROPERTY() std::vector<std::unique_ptr<SpriteAnimationFrame>> frames;

	GENERATED_BODY()
};