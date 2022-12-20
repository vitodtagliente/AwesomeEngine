/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <functional>
#include <memory>
#include <vector>

#include <awesome/asset/scene_asset.h>
#include <awesome/entity/entity.h>

struct SceneLoader final
{
	SceneLoader() = delete;

	static void load(const SceneAssetPtr& asset, const std::function<void(std::vector<std::unique_ptr<Entity>>&)>& callback);
};