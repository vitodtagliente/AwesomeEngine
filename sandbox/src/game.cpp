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

#include "minion.h"
#include "path.h"
#include "tower.h"
#include "wave_manager.h"

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

	std::shared_ptr<Asset> image = AssetLibrary::instance()->find(Asset::Type::Image, "../assets/spritesheet.png");

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
			if (SpriteRenderer* component = entity->addComponent<SpriteRenderer>())
			{
				const float spriteSize = 1.0f / 11;
				component->texture = graphics::TextureLibrary::instance()->find(image->id);
				component->rect = graphics::TextureRect(spriteSize * 9, spriteSize * 6, spriteSize, spriteSize);
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
		// path setup
		{
			Entity* const entity = world->spawn(math::vec3::zero, math::quaternion::identity);
			entity->name = std::string("path");
			entity->tag = "path";
			if (Path* const component = entity->addComponent<Path>())
			{
				for (int i = 0; i < 10; ++i)
				{
					component->steps.push_back(math::vec3(
						static_cast<float>(i) * 2.f, -2.f, 0.f
					));
				}
			}

			{
				std::cout << json::Serializer::to_string(entity->toJson());
			}
		}
		// minion setup
		{
			Entity* const entity = world->spawn(math::vec3::zero, math::quaternion::identity);
			entity->name = std::string("minion");
			entity->tag = "minion";
			entity->addComponent<Minion>();
			if (SpriteRenderer* component = entity->addComponent<SpriteRenderer>())
			{
				const float spriteSize = 1.0f / 11;
				component->texture = graphics::TextureLibrary::instance()->find(image->id);
				component->rect = graphics::TextureRect(spriteSize * 9, spriteSize * 6, spriteSize, spriteSize);
			}
			if (GizmosRenderer* component = entity->addComponent<GizmosRenderer>())
			{
				component->type = GizmosRenderer::Type::Rect;
			}
		}
		// towers setup
		{
			Entity* const entity = world->spawn(math::vec3(8.f, 1.f, 0.f), math::quaternion::identity);
			entity->name = std::string("tower");
			entity->tag = "tower";
			entity->addComponent<Tower>();
			if (GizmosRenderer* component = entity->addComponent<GizmosRenderer>())
			{
				component->type = GizmosRenderer::Type::Rect;
				component->color = graphics::Color::Blue;
			}
		}
		// wave manager
		{
			Entity* const entity = world->spawn(math::vec3::zero, math::quaternion::identity);
			entity->name = std::string("wave manager");
			entity->tag = "wave manager";
			if (WaveManager* const component = entity->addComponent<WaveManager>())
			{
				Wave wave;
				wave.duration = 10.f;
				wave.numOfMinions = 4;
				wave.perMinionSpawnDelay = 1.f;

				component->push(wave);
				component->push(wave);
				component->push(wave);

				component->start();
			}
		}
	}
}

void Game::shutdown()
{
}