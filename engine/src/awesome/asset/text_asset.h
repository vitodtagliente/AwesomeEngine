/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

#include "asset.h"

#include "text_asset_generated.h"

CLASS(Type = Asset, Extension = .txt|.md|.shader|.ini|.cfg, CreateInEditor = false)
struct TextAsset : public Asset
{
	virtual bool load(const std::filesystem::path& path) override;
	virtual bool save(const std::filesystem::path& path) const override;

	std::string data;

	GENERATED_BODY()
};

typedef std::shared_ptr<TextAsset> TextAssetPtr;