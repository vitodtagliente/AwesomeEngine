/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "base_asset.h"
#include "data/sprite_animation_data.h"

struct SpriteAnimationAsset : public BaseAsset<Asset::Type::SpriteAnimation, SpriteAnimationData>
{
	SpriteAnimationAsset(const Asset::Descriptor& descriptor)
		: BaseAsset(descriptor)
	{

	}
};
typedef std::shared_ptr<SpriteAnimationAsset> SpriteAnimationAssetPtr;