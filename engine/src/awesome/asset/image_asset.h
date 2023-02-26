/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "asset.h"
#include "data/image.h"

struct ImageAsset : public Asset
{
	ImageAsset();

	virtual bool load(const std::filesystem::path& path) override;
	virtual bool save(const std::filesystem::path& path) const override;

	Image data;
};

typedef std::shared_ptr<ImageAsset> ImageAssetPtr;