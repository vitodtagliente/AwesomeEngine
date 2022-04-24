/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>

#include "base_asset.h"

typedef BaseAsset<Asset::Type::Prefab, std::string> PrefabAsset;
typedef std::shared_ptr<PrefabAsset> PrefabAssetPtr;
ASSETTYPE(PrefabAsset, Asset::Type::Prefab)
