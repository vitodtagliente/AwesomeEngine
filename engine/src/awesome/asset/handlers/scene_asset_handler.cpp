#include "scene_asset_handler.h"

#include <awesome/asset/scene_asset.h>

SceneAssetHandler::SceneAssetHandler()
	: AssetHandler()
{
	create = []() ->AssetPtr { return std::make_shared<SceneAsset>(); };
	extensions = { ".scene" };
	name = "SceneAsset";
	type = AssetType_Scene;
}
