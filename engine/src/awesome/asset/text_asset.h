/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

#include "base_asset.h"

struct TextAsset : public BaseAsset<Asset::Type::Text, std::string>
{
	TextAsset() = default;

	virtual void load(const std::filesystem::path& path) override;
};
typedef std::shared_ptr<TextAsset> TextAssetPtr;