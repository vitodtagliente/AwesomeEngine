/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/data/type_file.h>

#include "asset.h"
#include "data/prefab.h"

#include "prefab_asset_generated.h"

template <>
struct ResourceReader<Prefab>
{
	using result_type = std::shared_ptr<Prefab>;

	template <typename... Args>
	static result_type read(const std::filesystem::path& path, Args&&... args)
	{
		result_type result = std::make_shared<Prefab>();
		if (TypeFile::load(path, *result))
		{
			return result;
		}
		return nullptr;
	};
};

template <>
struct ResourcerWriter<Prefab>
{
	static bool write(const Prefab& data, const std::filesystem::path& path)
	{
		return TypeFile::save(data, path), true;
	}
};

constexpr int AssetType_Prefab = 3;

CLASS(Type = Asset)
struct PrefabAsset : public Asset
{
	PrefabAsset()
		: Asset(AssetType_Prefab)
	{}

	PrefabAsset(const uuid& _id)
		: Asset(_id, AssetType_Prefab)
	{}

	ASSET_GENERATED_BODY(AssetType_Prefab, Prefab)
	GENERATED_BODY()
};

CLASS(Type = AssetLoader)
struct PrefabAssetLoader : public AssetLoader
{
	PrefabAssetLoader()
		: AssetLoader()
	{
		extensions = { ".prefab" };
		type = AssetType_Prefab;
	}

	virtual void load(const std::filesystem::path& path) override
	{
		Resource<Prefab>::load(path);
	}

	GENERATED_BODY()
};