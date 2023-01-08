/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/reflection.h>

#include "base_asset.h"

typedef BaseAsset<Asset::Type::Custom, std::unique_ptr<Type>> CustomAsset;
typedef std::shared_ptr<CustomAsset> CustomAssetPtr;