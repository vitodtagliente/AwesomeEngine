/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/data/type_file.h>

#include "asset.h"
#include "data/widget.h"

#include "widget_asset_generated.h"

template <>
struct ResourceReader<Widget>
{
	using result_type = std::shared_ptr<Widget>;

	template <typename... Args>
	static result_type read(const std::filesystem::path& path, Args&&... args)
	{
		result_type result = std::make_shared<Widget>();
		if (TypeFile::load(path, *result))
		{
			return result;
		}
		return nullptr;
	};
};

template <>
struct ResourcerWriter<Widget>
{
	static bool write(const Widget& data, const std::filesystem::path& path)
	{
		return TypeFile::save(data, path), true;
	}
};

constexpr int AssetType_Widget = 6;

CLASS(Type = Asset)
struct WidgetAsset : public Asset
{
	WidgetAsset()
		: Asset(AssetType_Widget)
	{}

	WidgetAsset(const uuid& _id)
		: Asset(_id, AssetType_Widget)
	{}

	ASSET_GENERATED_BODY(AssetType_Widget, Widget)
	GENERATED_BODY()
};

CLASS(Type = AssetLoader)
struct WidgetAssetLoader : public AssetLoader
{
	WidgetAssetLoader()
		: AssetLoader()
	{
		extensions = { ".widget" };
		type = AssetType_Widget;
	}

	virtual void load(const std::filesystem::path& path) override
	{
		Resource<Widget>::load(path);
	}

	GENERATED_BODY()
};