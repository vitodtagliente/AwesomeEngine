/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>

#include "base_asset.h"
#include "data/sprite_animation.h"

typedef BaseAsset<Asset::Type::SpriteAnimation, SpriteAnimation> SpriteAnimationAsset;
typedef std::shared_ptr<SpriteAnimationAsset> SpriteAnimationAssetPtr;
ASSETTYPEINFO(SpriteAnimationAsset, Asset::Type::SpriteAnimation)