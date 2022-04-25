/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <functional>
#include <memory>
#include <vector>

#include <awesome/data/scene_asset.h>
#include <awesome/entity/entity.h>

class SceneLoader final
{
public:
	SceneLoader() = default;
	~SceneLoader() = default;

	void load(const SceneAssetPtr& asset, const std::function<void(std::vector<std::unique_ptr<Entity>>&)>& handler);
	void update(double deltaTime);

	bool isLoading() const;
	size_t getProgress() const;

private:
	SceneAssetPtr m_asset;
	std::vector<std::unique_ptr<Entity>> m_entities;
	std::function<void(std::vector<std::unique_ptr<Entity>>&)> m_handler;
	bool m_isLoading{ false };
	size_t m_progress{ 0 };
	size_t m_totalProgress{ 0 };
};