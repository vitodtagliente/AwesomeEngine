#include "game.h"

#include <iostream>

#include <awesome/components/camera_controller_2d.h>
#include <awesome/components/gizmos_renderer.h>
#include <awesome/components/orthographic_camera.h>
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
#include "pawn/combat_controller.h"
#include "pawn/health.h"
#include "pawn/lifetime.h"
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
	TypeFactory::load<CombatController>();
	TypeFactory::load<Health>();
	TypeFactory::load<Lifetime>();
	TypeFactory::load<Pawn>();
	TypeFactory::load<PawnController>();
	TypeFactory::load<Rotator>();
}

void Game::shutdown()
{
}