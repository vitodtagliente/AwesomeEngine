/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>

#include "asset.h"

#include "asset_identifier_generated.h"

CLASS()
struct AssetIdentifier : public Type
{
	virtual bool identify(const std::filesystem::path&) const { return false; }
	virtual AssetPtr instatiate(const std::filesystem::path&) const { return nullptr; }

	GENERATED_BODY()
};