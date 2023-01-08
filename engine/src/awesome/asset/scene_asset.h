/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/encoding/json.h>

#include "base_asset.h"

struct SceneAsset : public BaseAsset<Asset::Type::Scene, json::value>
{
	SceneAsset() = default;

	virtual void load(const std::filesystem::path& path) override;
};
typedef std::shared_ptr<SceneAsset> SceneAssetPtr;