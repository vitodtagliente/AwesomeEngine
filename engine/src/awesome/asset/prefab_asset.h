/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "asset.h"
#include "data/prefab.h"

struct PrefabAsset : public Asset
{
	virtual bool load(const std::filesystem::path& path) override;
	virtual bool save(const std::filesystem::path& path) const override;

	Prefab data;
};

typedef std::shared_ptr<PrefabAsset> PrefabAssetPtr;