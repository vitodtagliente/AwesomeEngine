/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "asset.h"
#include "data/scene.h"

#include "scene_asset_generated.h"

CLASS()
struct SceneAsset : public Asset
{
	SceneAsset();

	virtual bool load(const std::filesystem::path& path) override;
	virtual bool save(const std::filesystem::path& path) const override;

	Scene data;

	GENERATED_BODY()
};