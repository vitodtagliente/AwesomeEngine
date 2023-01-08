/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "base_asset.h"
#include "data/image.h"

struct ImageAsset : public BaseAsset<Asset::Type::Image, Image>
{
	virtual void load(const std::filesystem::path& path) override;
};
typedef std::shared_ptr<ImageAsset> ImageAssetPtr;