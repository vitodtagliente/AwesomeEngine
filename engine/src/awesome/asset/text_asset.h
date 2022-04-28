/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>

#include "base_asset.h"

typedef BaseAsset<Asset::Type::Text, std::string> TextAsset;
typedef std::shared_ptr<TextAsset> TextAssetPtr;
ASSETTYPE(TextAsset, Asset::Type::Text)