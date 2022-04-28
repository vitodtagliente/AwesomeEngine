/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>

#include "base_asset.h"
#include "data/sprite.h"

typedef BaseAsset<Asset::Type::Sprite, Sprite> SpriteAsset;
typedef std::shared_ptr<SpriteAsset> SpriteAssetPtr;
ASSETTYPE(SpriteAsset, Asset::Type::Sprite)