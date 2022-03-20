#include "scene_inspector.h"

#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

#include "../context.h"
#include "../selection_system.h"

namespace editor
{
	SceneInspector::SceneInspector()
		: Window()
	{
	}

	std::string SceneInspector::getTitle() const
	{
		return "Scene";
	}

	void SceneInspector::render(Context& context)
	{
		SelectionSystem* selectionSystem = SelectionSystem::instance();
		const auto& selection = selectionSystem->getSelection();

		if (World* const world = World::instance())
		{
			for (auto it = world->getEntities().begin(); it != world->getEntities().end(); ++it)
			{
				Entity* const entity = *it;
				if (context.selectable(entity->name, 
					selection.has_value() && 
					selection->type == SelectionSystem::Selection::Type::Entity && std::get<Entity*>(selection->data) == entity))
				{
					selectionSystem->select(entity);
				}
			}
		}
	}
}