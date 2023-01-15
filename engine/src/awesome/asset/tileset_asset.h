/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "asset.h"
#include "data/tileset.h"

#include "tileset_asset_generated.h"

CLASS()
struct TilesetAsset : public Asset
{
	virtual bool load(const std::filesystem::path& path) override;
	virtual bool save(const std::filesystem::path& path) const override;

	Tileset data;

	GENERATED_BODY()
};

typedef std::shared_ptr<TilesetAsset> TilesetAssetPtr;