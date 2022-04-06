/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

#include "base_asset.h"
#include "prefab.h"

typedef BaseAsset<Asset::Type::Prefab, Prefab> PrefabAsset;
typedef std::shared_ptr<PrefabAsset> PrefabAssetPtr;
ASSETTYPE(PrefabAsset, Asset::Type::Prefab)
