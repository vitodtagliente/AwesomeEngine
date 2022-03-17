#include "game.h"

#include <iostream>

#include <awesome/components/camera_controller_2d.h>
#include <awesome/components/gizmos_renderer.h>
#include <awesome/components/orthographic_camera.h>
#include <awesome/components/sprite_animator.h>
#include <awesome/components/sprite_renderer.h>
#include <awesome/data/archive.h>
#include <awesome/data/asset_library.h>
#include <awesome/encoding/json.h>
#include <awesome/graphics/texture.h>
#include <awesome/graphics/texture_library.h>
#include <awesome/graphics/texture_rect.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

void Game::startup()
{
	{
		Archive ar("archive.txt", Archive::Mode::Write);
		ar << 1 << "Hello" << true;
	}

	{
		Archive ar("archive.txt", Archive::Mode::Read);
		int one; std::string hello; bool value;
		ar >> one >> hello >> value;
	}

	std::shared_ptr<ImageAsset> image = AssetLibrary::instance()->find<ImageAsset>(Asset::Type::Image, "../assets/spritesheet.png");

	if (World* const world = World::instance())
	{
		// camera setup
		{
			Entity* const entity = world->spawn(math::vec3::zero, math::quaternion::identity);
			entity->name = std::string("camera");
			entity->tag = "camera";
			entity->addComponent<OrthographicCamera>();
			entity->addComponent<CameraController2d>();
		}
		// animated entity
		{
			Entity* const entity = world->spawn(math::vec3::zero, math::quaternion::identity);
			entity->name = std::string("animated guy");
			entity->tag = "animated guy";

			const float spriteSize = 1.0f / 11;
			Sprite sprite(image, graphics::TextureRect(spriteSize * 9, spriteSize * 6, spriteSize, spriteSize));

			if (SpriteRenderer* component = entity->addComponent<SpriteRenderer>())
			{
				const float spriteSize = 1.0f / 11;
				component->sprite = sprite;
			}

			if (SpriteAnimator* component = entity->addComponent<SpriteAnimator>())
			{
				const float spriteSize = 1.0f / 11;
				SpriteAnimator::Animation idle;
				idle.frames.push_back(SpriteAnimator::Animation::Frame(graphics::TextureRect(spriteSize * 9, spriteSize * 3, spriteSize, spriteSize), 1.0f));
				idle.frames.push_back(SpriteAnimator::Animation::Frame(graphics::TextureRect(spriteSize * 9, spriteSize * 4, spriteSize, spriteSize), 1.0f));
				idle.frames.push_back(SpriteAnimator::Animation::Frame(graphics::TextureRect(spriteSize * 9, spriteSize * 5, spriteSize, spriteSize), 1.0f));
				idle.frames.push_back(SpriteAnimator::Animation::Frame(graphics::TextureRect(spriteSize * 9, spriteSize * 6, spriteSize, spriteSize), 1.0f));
				component->animations.insert(std::make_pair("idle", idle));
				component->autoplay = true;
			}

			if (GizmosRenderer* component = entity->addComponent<GizmosRenderer>())
			{
				component->type = GizmosRenderer::Type::Rect;
			}
		}
	}
}

void Game::shutdown()
{
}