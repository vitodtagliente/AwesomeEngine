#include "game.h"

#include <awesome/components/gizmos_renderer.h>
#include <awesome/components/sprite_renderer.h>
#include <awesome/graphics/texture.h>
#include <awesome/graphics/texture_library.h>
#include <awesome/graphics/texture_rect.h>
#include <awesome/scene/entity.h>
#include <awesome/scene/world.h>

#include "minion.h"
#include "path.h"

void Game::startup()
{
	if (World* const world = World::instance())
	{
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
				component->texture = graphics::TextureLibrary::instance()->get("sheet");
				component->rect = graphics::TextureRect(spriteSize * 9, spriteSize * 6, spriteSize, spriteSize);
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