/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/data/type_file.h>

#include "asset.h"
#include "data/prefab.h"

#include "prefab_asset_generated.h"

template <>
struct ResourceLoader<Prefab>
{
	using result_type = std::shared_ptr<Prefab>;

	template <typename... Args>
	result_type operator()(const std::filesystem::path& path, Args&&... args)
	{
		result_type result = std::shared_ptr<Prefab>();
		return TypeFile::load(path, *result);
	};
};

constexpr int AssetType_Prefab = 4;

typedef AssetHandle<AssetType_Prefab, Prefab, ResourceLoader<Prefab>> PrefabAsset;

NATIVE_CLASS(PrefabAsset, typedef AssetHandle<4, Prefab, ResourceLoader<Prefab>> PrefabAsset;)
struct native_PrefabAsset
{
	PROPERTY() uuid id;
};