/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/asset_handler.h>

#include "scene_asset_handler_generated.h"

CLASS(Type = AssetHandler)
struct SceneAssetHandler : public AssetHandler
{
	SceneAssetHandler();

	GENERATED_BODY()
};