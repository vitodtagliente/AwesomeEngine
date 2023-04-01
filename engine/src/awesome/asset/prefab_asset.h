/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "asset.h"
#include "data/prefab.h"

#include "prefab_asset_generated.h"

CLASS()
struct PrefabAsset : public Asset
{
	PrefabAsset();

	virtual bool load(const std::filesystem::path& path) override;
	virtual bool save(const std::filesystem::path& path) const override;

	Prefab data;

	GENERATED_BODY()
};