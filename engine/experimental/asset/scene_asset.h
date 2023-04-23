/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/data/type_file.h>

#include "asset.h"
#include "data/scene.h"

#include "scene_asset_generated.h"

template <>
struct ResourceLoader<Scene>
{
	using result_type = std::shared_ptr<Scene>;

	template <typename... Args>
	result_type operator()(const std::filesystem::path& path, Args&&... args)
	{
		result_type result = std::shared_ptr<Scene>();
		return TypeFile::load(path, *result);
	};
};

constexpr int AssetType_Scene = 8;

typedef AssetHandle<AssetType_Scene, Scene, ResourceLoader<Scene>> SceneAsset;

NATIVE_CLASS(SceneAsset, typedef AssetHandle<8, Scene, ResourceLoader<Scene>> SceneAsset;)
struct native_SceneAsset
{
	PROPERTY() uuid id;
};