#include "prefab_asset_handler.h"

#include <awesome/asset/prefab_asset.h>

PrefabAssetHandler::PrefabAssetHandler()
	: AssetHandler()
{
	create = []() ->AssetPtr { return std::make_shared<PrefabAsset>(); };
	extensions = { ".prefab" };
	name = "PrefabAsset";
	type = AssetType_Prefab;
}
