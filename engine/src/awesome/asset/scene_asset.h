/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>

#include <awesome/encoding/json.h>

#include "base_asset.h"

typedef BaseAsset<Asset::Type::Scene, json::value> SceneAsset;
typedef std::shared_ptr<SceneAsset> SceneAssetPtr;
ASSETTYPE(SceneAsset, Asset::Type::Scene)