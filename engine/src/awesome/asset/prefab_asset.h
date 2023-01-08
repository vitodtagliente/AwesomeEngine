/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/encoding/json.h>

#include "base_asset.h"

struct PrefabAsset : public BaseAsset<Asset::Type::Prefab, json::value>
{
	PrefabAsset(const Asset::Descriptor& descriptor)
		: BaseAsset(descriptor)
	{

	}
};
typedef std::shared_ptr<PrefabAsset> PrefabAssetPtr;
