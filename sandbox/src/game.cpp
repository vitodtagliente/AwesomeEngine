#include "game.h"

#include <iostream>

#include <awesome/asset/asset_library.h>
#include <awesome/asset/prefab_asset.h>
#include <awesome/editor/layout.h>

void Game::startup()
{
	PrefabAssetPtr prefab = AssetLibrary::instance().find<PrefabAsset>(uuid("146999684233600"));
	prefab->onLoad = [prefab]()
	{
		// World& world = World::instance();
		// for (int i = 0; i < 0; ++i)
		// {
		// 	world.spawn(prefab, math::vec3(math::random(-10.f, 10.f), math::random(-10.f, 10.f), 0.0f));
		// }
	};
}

void Game::shutdown()
{
}