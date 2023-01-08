/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/encoding/json.h>

#include "base_asset.h"

struct PrefabAsset : public BaseAsset<Asset::Type::Prefab, json::value>
{
	virtual void load(const std::filesystem::path& path) override;
};
typedef std::shared_ptr<PrefabAsset> PrefabAssetPtr;
