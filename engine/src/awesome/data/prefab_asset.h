/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>

#include <awesome/encoding/json.h>

#include "base_asset.h"

typedef BaseAsset<Asset::Type::Prefab, json::value> PrefabAsset;
typedef std::shared_ptr<PrefabAsset> PrefabAssetPtr;
ASSETTYPE(PrefabAsset, Asset::Type::Prefab)
