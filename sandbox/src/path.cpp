#include "path.h"

#include <vdtmath/algorithm.h>

#include <awesome/editor/context.h>
#include <awesome/graphics/gizmos.h>
#include <awesome/graphics/renderer.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

Path::Path()
	: steps()
	, color(graphics::Color::Green)
{
}

void Path::init()
{
	getOwner()->tag = "path";
}

void Path::render(graphics::Renderer& renderer)
{
	for (size_t i = 0; i < steps.size() - 1; ++i)
	{
		renderer.getGizmos().line(steps[i], steps[i + 1], color);
	}
}

void Path::inspect(editor::Context& context)
{
	context.input("color", &color);
}

Path* const Path::findOrRandom(World& world, const std::string& name)
{
	std::vector<Path*> paths;
	std::vector<Entity*> entities = world.findEntitiesByTag("path");
	for (auto it = entities.begin(); it != entities.end(); ++it)
	{
		Entity* const entity = *it;
		Path* const path = entity->findComponent<Path>();
		if (path == nullptr)
		{
			continue;
		}

		if (entity->name == name)
		{
			return path;
		}
		else
		{
			paths.push_back(path);
		}
	}
	
	if (paths.empty())
	{
		return nullptr;
	}

	return paths.at(math::random(0, paths.size() - 1));
}