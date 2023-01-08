/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "base_asset.h"
#include "data/tileset.h"

struct TilesetAsset : public BaseAsset<Asset::Type::Tileset, Tileset>
{
	TilesetAsset() = default;

	virtual void load(const std::filesystem::path& path) override;
};
typedef std::shared_ptr<TilesetAsset> TilesetAssetPtr;