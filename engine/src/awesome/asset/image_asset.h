/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/reflection.h>

#include "asset.h"
#include "data/image.h"

#include "resource.h"

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

template <>
struct ResourceLoader<Image>
{
	using result_type = std::shared_ptr<Image>;

	template <typename... Args>
	result_type operator()(const std::filesystem::path& path, Args&&... args)
	{
		return std::make_shared<T>(Image::load(path));
	};
};

typedef FAsset<Image, ResourceLoader<Image>> FImageAsset;

NATIVE_CLASS(FImageAsset, typedef FAsset<Image, ResourceLoader<Image>> FImageAsset;)
struct native_FImageAsset
{
	PROPERTY() uuid m_id;
};