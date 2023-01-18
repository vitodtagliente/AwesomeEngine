/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "asset.h"
#include "data/image.h"

#include "image_asset_generated.h"

CLASS(Type = Asset, Extension = .png|.jpg|.jpeg|.bmp, CreateInEditor = false)
struct ImageAsset : public Asset
{
	virtual bool load(const std::filesystem::path& path) override;
	virtual bool save(const std::filesystem::path& path) const override;

	Image data;

	GENERATED_BODY()
};

typedef std::shared_ptr<ImageAsset> ImageAssetPtr;