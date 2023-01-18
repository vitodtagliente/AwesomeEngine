/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "asset.h"

#include <awesome/encoding/json.h>

#include "prefab_asset_generated.h"

CLASS(Type = Asset, Extension = .prefab, CreateInEditor = false)
struct PrefabAsset : public Asset
{
	virtual bool load(const std::filesystem::path& path) override;
	virtual bool save(const std::filesystem::path& path) const override;

	json::value data;

	GENERATED_BODY()
};

typedef std::shared_ptr<PrefabAsset> PrefabAssetPtr;