/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>

#include "base_asset.h"

typedef BaseAsset<Asset::Type::Scene, std::string> SceneAsset;
typedef std::shared_ptr<SceneAsset> SceneAssetPtr;
ASSETTYPE(SceneAsset, Asset::Type::Scene)