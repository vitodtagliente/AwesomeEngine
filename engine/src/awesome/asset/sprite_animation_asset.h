/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "asset.h"
#include "data/sprite_animation_data.h"

#include "sprite_animation_asset_generated.h"

CLASS()
struct SpriteAnimationAsset : public Asset
{
	virtual bool load(const std::filesystem::path& path) override;
	virtual bool save(const std::filesystem::path& path) const override;

	SpriteAnimationData data;

	GENERATED_BODY()
};

typedef std::shared_ptr<SpriteAnimationAsset> SpriteAnimationAssetPtr;