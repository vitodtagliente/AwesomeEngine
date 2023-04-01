/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "asset.h"
#include "data/image.h"

#include "image_asset_generated.h"

CLASS()
struct ImageAsset : public Asset
{
	ImageAsset();

	virtual bool load(const std::filesystem::path& path) override;
	virtual bool save(const std::filesystem::path& path) const override;

	Image data;

	GENERATED_BODY()
};