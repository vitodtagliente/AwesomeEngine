#include "game.h"

#include <iostream>

#include <awesome/components/camera_controller_2d.h>
#include <awesome/components/gizmos_renderer.h>
#include <awesome/components/orthographic_camera_component.h>
#include <awesome/components/sprite_animator.h>
#include <awesome/components/sprite_renderer.h>
#include <awesome/data/archive.h>
#include <awesome/asset/asset_library.h>
#include <awesome/asset/sprite_asset.h>
#include <awesome/editor/layout.h>
#include <awesome/encoding/json.h>
#include <awesome/graphics/texture.h>
#include <awesome/graphics/texture_library.h>
#include <awesome/graphics/texture_rect.h>
#include <awesome/entity/component.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

#include "pawn/bullet.h"
#include "pawn/camera_follow_2d.h"
#include "pawn/combat_controller.h"
#include "pawn/health.h"
#include "pawn/lifetime.h"
#include "pawn/patrol.h"
#include "pawn/pawn.h"
#include "pawn/pawn_controller.h"

class Rotator : public Component
{
public:
	Rotator()
		: speed(math::random(5.0f, 40.0f))
	{

	}

	void update(double deltaTime) override
	{
		math::transform& transform = getOwner()->transform;
		transform.rotation.z = getOwner()->transform.rotation.z;
		transform.rotation.z += speed * static_cast<float>(deltaTime);
		if (transform.rotation.z >= 360.f)
		{
			transform.rotation.z = 0;
		}
	}

	void inspect() override
	{
		Component::inspect();
		editor::Layout::input("Speed", speed);
	}

	float speed;

	REFLECT()
};

REFLECT_COMPONENT(Rotator)

void Game::startup()
{
	TypeFactory::load<Bullet>();
	TypeFactory::load<CameraFollow2d>();
	TypeFactory::load<CombatController>();
	TypeFactory::load<Health>();
	TypeFactory::load<Lifetime>();
	TypeFactory::load<Patrol>();
	TypeFactory::load<Pawn>();
	TypeFactory::load<PawnController>();
	TypeFactory::load<Rotator>();

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