#include "scene_inspector.h"

#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

#include "../context.h"

namespace editor
{
	SceneInspector::SceneInspector()
		: Window()
		, m_selectedEntity()
	{
	}

	std::string SceneInspector::getTitle() const
	{
		return "Scene";
	}

	void SceneInspector::render(Context& context)
	{
		if (World* const world = World::instance())
		{
			for (auto it = world->getEntities().begin(); it != world->getEntities().end(); ++it)
			{
				Entity* const entity = *it;
				if (context.selectable(entity->name, entity == m_selectedEntity))
				{
					m_selectedEntity = entity;
				}
			}
		}
	}
}