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

constexpr int AssetType_Prefab = 3;

typedef AssetHandle<AssetType_Prefab, Prefab> PrefabAsset;

NATIVE_CLASS(PrefabAsset, typedef AssetHandle<3, Prefab> PrefabAsset;)
struct native_PrefabAsset
{
	PROPERTY() uuid id;
};