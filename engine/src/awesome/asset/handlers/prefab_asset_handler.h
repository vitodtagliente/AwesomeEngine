/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/asset_handler.h>

#include "prefab_asset_handler_generated.h"

CLASS(Type = AssetHandler)
struct PrefabAssetHandler : public AssetHandler
{
	PrefabAssetHandler();

	GENERATED_BODY()
};