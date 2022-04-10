#include "game.h"

#include <iostream>

#include <awesome/components/camera_controller_2d.h>
#include <awesome/components/gizmos_renderer.h>
#include <awesome/components/orthographic_camera.h>
#include <awesome/components/sprite_animator.h>
#include <awesome/components/sprite_renderer.h>
#include <awesome/data/archive.h>
#include <awesome/data/asset_library.h>
#include <awesome/data/sprite_asset.h>
#include <awesome/editor/layout.h>
#include <awesome/encoding/json.h>
#include <awesome/graphics/texture.h>
#include <awesome/graphics/texture_library.h>
#include <awesome/graphics/texture_rect.h>
#include <awesome/entity/component.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

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
	SpriteAssetPtr sprite = AssetLibrary::instance()->find<SpriteAsset>(uuid("357240685689300"));
	SpriteAnimationAssetPtr animation = AssetLibrary::instance()->find<SpriteAnimationAsset>(uuid("546811582152200"));

	if (World* const world = World::instance())
	{
		// camera setup
		{
			EntityPtr entity = world->spawn(math::vec3::zero, math::quaternion::identity);
			entity->name = std::string("Camera");
			entity->tag = "Main Camera";
			entity->addComponent<OrthographicCamera>();
			entity->addComponent<CameraController2d>();
		}

		// animated entity
		for (int i = 0; i < 1000; ++i)
		{
			static float magic = 35.f;
			EntityPtr entity = world->spawn(math::vec3(math::random(-magic, magic), math::random(-magic, magic), 0.0f), math::quaternion::identity);
			entity->transform.rotation.z = math::random(0.0f, 360.0f);
			entity->transform.scale.x = entity->transform.scale.y = math::random(0.6f, 2.4f);
			entity->name = std::string("Animated Guy-") + std::to_string(i + 1);
			entity->tag = "Player";

			if (SpriteRenderer* component = entity->addComponent<SpriteRenderer>())
			{
				component->sprite = sprite;
			}

			if (SpriteAnimator* component = entity->addComponent<SpriteAnimator>())
			{
				component->animations.insert(std::make_pair("idle", animation));
				component->autoplay = true;
				component->enabled = math::random(0.0f, 1.0f) >= 0.4f;
			}

			if (GizmosRenderer* component = entity->addComponent<GizmosRenderer>())
			{
				component->type = GizmosRenderer::Type::Rect;
				component->enabled = math::random(0.0f, 1.0f) >= 0.7f;
			}

			if (Rotator* component = entity->addComponent<Rotator>())
			{
				component->enabled = math::random(0.0f, 1.0f) >= 0.6f;
			}
		}
	}
}

void Game::shutdown()
{
}