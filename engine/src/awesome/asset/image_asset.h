/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>

#include "base_asset.h"
#include "data/image.h"

typedef BaseAsset<Asset::Type::Image, Image> ImageAsset;
typedef std::shared_ptr<ImageAsset> ImageAssetPtr;
ASSETTYPE(ImageAsset, Asset::Type::Image)