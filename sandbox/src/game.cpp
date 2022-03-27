#include "game.h"

#include <iostream>

#include <awesome/components/camera_controller_2d.h>
#include <awesome/components/gizmos_renderer.h>
#include <awesome/components/orthographic_camera.h>
#include <awesome/components/sprite_animator.h>
#include <awesome/components/sprite_renderer.h>
#include <awesome/data/archive.h>
#include <awesome/data/asset_library.h>
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
		transform.rotation.z += speed * deltaTime;
		if (transform.rotation.z >= 360.f)
		{
			transform.rotation.z = 0;
		}
	}

	void inspect() override
	{
		Component::inspect();
		editor::Layout::input("Speed", &speed);
	}

	float speed;

	REFLECT()
};

REFLECT_COMPONENT(Rotator)

void Game::startup()
{
	std::shared_ptr<ImageAsset> image = AssetLibrary::instance()->find<ImageAsset>(uuid("222601788947200"));

	if (World* const world = World::instance())
	{
		// camera setup
		{
			Entity* const entity = world->spawn(math::vec3::zero, math::quaternion::identity);
			entity->name = std::string("Camera");
			entity->tag = "Main Camera";
			entity->addComponent<OrthographicCamera>();
			entity->addComponent<CameraController2d>();
		}

		// animated entity
		for (int i = 0; i < 1000; ++i)
		{
			static float magic = 35.f;
			Entity* const entity = world->spawn(math::vec3(math::random(-magic, magic), math::random(-magic, magic), 0.0f), math::quaternion::identity);
			entity->transform.rotation.z = math::random(0.0f, 360.0f);
			entity->transform.scale.x = entity->transform.scale.y = math::random(0.6f, 2.4f);
			entity->name = std::string("Animated Guy-") + std::to_string(i + 1);
			entity->tag = "Player";

			const float spriteSize = 1.0f / 11;
			Sprite sprite(image, graphics::TextureRect(spriteSize * 9, spriteSize * 6, spriteSize, spriteSize));

			if (SpriteRenderer* component = entity->addComponent<SpriteRenderer>())
			{
				component->sprite = sprite;
			}

			if (SpriteAnimator* component = entity->addComponent<SpriteAnimator>())
			{
				SpriteAnimator::Animation idle;
				idle.frames.push_back(SpriteAnimator::Animation::Frame(Sprite(image, graphics::TextureRect(spriteSize * 9, spriteSize * 3, spriteSize, spriteSize)), 1.0f));
				idle.frames.push_back(SpriteAnimator::Animation::Frame(Sprite(image, graphics::TextureRect(spriteSize * 9, spriteSize * 4, spriteSize, spriteSize)), 1.0f));
				idle.frames.push_back(SpriteAnimator::Animation::Frame(Sprite(image, graphics::TextureRect(spriteSize * 9, spriteSize * 5, spriteSize, spriteSize)), 1.0f));
				idle.frames.push_back(SpriteAnimator::Animation::Frame(Sprite(image, graphics::TextureRect(spriteSize * 9, spriteSize * 6, spriteSize, spriteSize)), 1.0f));
				idle.startingFrame = math::random(0, idle.frames.size());
				component->animations.insert(std::make_pair("idle", idle));
				component->autoplay = true;
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