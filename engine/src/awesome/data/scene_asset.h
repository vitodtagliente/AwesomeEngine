/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>

#include "base_asset.h"
#include "scene.h"

typedef BaseAsset<Asset::Type::Scene, Scene> SceneAsset;
typedef std::shared_ptr<SceneAsset> SceneAssetPtr;
ASSETTYPE(SceneAsset, Asset::Type::Scene)