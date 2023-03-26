/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <functional>
#include <string>
#include <vector>

#include <awesome/core/reflection.h>

#include "asset.h"

#include "asset_handler_generated.h"

CLASS()
struct AssetHandler : public IType
{
	std::function<AssetPtr()> create;
	std::vector<std::string> extensions;
	std::string name;
	int type{ AssetType_Invalid };

	GENERATED_BODY()
};