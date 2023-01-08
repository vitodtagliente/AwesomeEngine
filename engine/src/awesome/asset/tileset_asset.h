/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>

#include "base_asset.h"
#include "data/tileset.h"

typedef BaseAsset<Asset::Type::Text, Tileset> TilesetAsset;
typedef std::shared_ptr<TilesetAsset> TilesetAssetPtr;