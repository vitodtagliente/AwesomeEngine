/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

#include "base_asset.h"

struct TextAsset : public BaseAsset<Asset::Type::Text, std::string>
{
	TextAsset(const Asset::Descriptor& descriptor)
		: BaseAsset(descriptor)
	{

	}
};
typedef std::shared_ptr<TextAsset> TextAssetPtr;