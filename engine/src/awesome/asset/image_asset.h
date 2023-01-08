/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "base_asset.h"
#include "data/image.h"

struct ImageAsset : public BaseAsset<Asset::Type::Image, Image>
{
	ImageAsset(const Asset::Descriptor& descriptor)
		: BaseAsset(descriptor)
	{

	}
};
typedef std::shared_ptr<ImageAsset> ImageAssetPtr;