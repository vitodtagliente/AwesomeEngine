/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/reflection.h>

#include "asset.h"
#include "data/image.h"

#include "image_asset_generated.h"

template <>
struct ResourceLoader<Image>
{
	using result_type = std::shared_ptr<Image>;

	template <typename... Args>
	result_type operator()(const std::filesystem::path& path, Args&&... args)
	{
		return std::make_shared<Image>(Image::load(path));
	};
};

constexpr int AssetType_Image = 2;

typedef AssetHandle<AssetType_Image, Image, ResourceLoader<Image>> ImageAsset;

NATIVE_CLASS(ImageAsset, typedef AssetHandle<2, Image, ResourceLoader<Image>> ImageAsset;)
struct native_ImageAsset
{
	PROPERTY() uuid id;
};