/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "asset_identifier.h"

#include "common_asset_identifier_generated.h"

CLASS(Type = AssetIdentifier)
struct CommonAssetIdentifier : public AssetIdentifier
{
	virtual bool identify(const std::filesystem::path& path) const override;
	virtual AssetPtr instatiate(const std::filesystem::path& path) const override;

	GENERATED_BODY()
};