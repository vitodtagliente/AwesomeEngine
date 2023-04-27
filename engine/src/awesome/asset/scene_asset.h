/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/data/type_file.h>

#include "asset.h"
#include "data/scene.h"

#include "scene_asset_generated.h"

template <>
struct ResourceReader<Scene>
{
	using result_type = std::shared_ptr<Scene>;

	template <typename... Args>
	static result_type read(const std::filesystem::path& path, Args&&... args)
	{
		result_type result = std::make_shared<Scene>();
		if (TypeFile::load(path, *result))
		{
			return result;
		}
		return nullptr;
	};
};

template <>
struct ResourcerWriter<Scene>
{
	static bool write(const Scene& data, const std::filesystem::path& path)
	{
		return TypeFile::save(data, path), true;
	}
};

constexpr int AssetType_Scene = 4;

typedef AssetHandle<AssetType_Scene, Scene> SceneAsset;

NATIVE_CLASS(SceneAsset, typedef AssetHandle<4, Scene> SceneAsset;)
struct native_SceneAsset
{
	PROPERTY() uuid id;
};