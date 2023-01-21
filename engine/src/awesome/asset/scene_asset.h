/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "asset.h"

#include "data/scene_data.h"

#include "scene_asset_generated.h"

CLASS(Type = Asset, Extension = .scene, CreateInEditor = false)
struct SceneAsset : public Asset
{
	virtual bool load(const std::filesystem::path& path) override;
	virtual bool save(const std::filesystem::path& path) const override;

	json::value data;

	GENERATED_BODY()
};

typedef std::shared_ptr<SceneAsset> SceneAssetPtr;