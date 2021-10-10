#include "scene_tree_window.h"

#include <awesome/scene/entity.h>
#include <awesome/scene/world.h>

#include "context.h"

namespace editor
{
	SceneTreeWindow::SceneTreeWindow()
		: Window()
		, m_selectedEntity()
	{
	}

	std::string SceneTreeWindow::getTitle() const
	{
		return "SceneTree";
	}

	void SceneTreeWindow::render(Context& context)
	{
		World* const world = World::instance();
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