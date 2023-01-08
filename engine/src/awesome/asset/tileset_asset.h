/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "base_asset.h"
#include "data/tileset.h"

struct TilesetAsset : public BaseAsset<Asset::Type::Tileset, Tileset>
{
	TilesetAsset(const Asset::Descriptor& descriptor)
		: BaseAsset(descriptor)
	{

	}
};
typedef std::shared_ptr<TilesetAsset> TilesetAssetPtr;