/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/asset_handler.h>

#include "image_asset_handler_generated.h"

CLASS(Type = AssetHandler)
struct ImageAssetHandler : public AssetHandler
{
	ImageAssetHandler();

	GENERATED_BODY()
};