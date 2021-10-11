#include "game.h"

#include <awesome/scene/entity.h>
#include <awesome/scene/world.h>

#include "path.h"

void Game::startup()
{
	if (World* const world = World::instance())
	{
		// path setup
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
}

void Game::shutdown()
{
}