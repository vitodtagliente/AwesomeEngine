#include "game.h"

#include <iostream>

#include <awesome/asset/asset_library.h>
#include <awesome/editor/layout.h>

#include "pawn/bullet.h"
#include "pawn/camera_follow_2d.h"
#include "pawn/combat_controller.h"
#include "pawn/health.h"
#include "pawn/lifetime.h"
#include "pawn/pawn.h"
#include "pawn/pawn_controller.h"
#include "pawn/rotator.h"

#include <awesome/application/application_settings.h>

void Game::startup()
{
	Bullet::autoload();
	CameraFollow2d::autoload();
	CombatController::autoload();
	Health::autoload();
	Lifetime::autoload();
	Pawn::autoload();
	PawnController::autoload();
	Rotator::autoload();

	Serializer::instance().load();

	ApplicationSettings settings;
	json::value value = Serializer::instance().serialize(&settings);

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