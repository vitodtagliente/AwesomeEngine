/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "asset.h"
#include "data/scene.h"

struct SceneAsset : public Asset
{
	SceneAsset();

	virtual bool load(const std::filesystem::path& path) override;
	virtual bool save(const std::filesystem::path& path) const override;

	Scene data;
};

typedef std::shared_ptr<SceneAsset> SceneAssetPtr;