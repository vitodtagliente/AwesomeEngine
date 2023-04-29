/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/reflection.h>

#include "asset.h"
#include "data/image.h"

#include "image_asset_generated.h"

template <>
struct ResourceReader<Image>
{
	using result_type = std::shared_ptr<Image>;

	template <typename... Args>
	static result_type read(const std::filesystem::path& path, Args&&... args)
	{
		return std::make_shared<Image>(Image::load(path));
	};
};

constexpr int AssetType_Image = 2;

CLASS(Type = Asset)
struct ImageAsset : public Asset
{
	ImageAsset()
		: Asset(AssetType_Image)
	{}

	ImageAsset(const uuid& _id)
		: Asset(_id, AssetType_Image)
	{}

	ASSET_GENERATED_BODY(AssetType_Image, Image)
	GENERATED_BODY()
};

CLASS(Type = AssetLoader)
struct ImageAssetLoader : public AssetLoader
{
	ImageAssetLoader()
		: AssetLoader()
	{
		extensions = { ".png", ".bmp", ".jpg", ".jpeg" };
		type = AssetType_Image;
	}

	virtual void load(const std::filesystem::path& path) override
	{
		Resource<Image>::load(path);
	}

	GENERATED_BODY()
};