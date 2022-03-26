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
		Entity* const selectedEntity = selection.has_value() && selection->type == SelectionSystem::Selection::Type::Entity
			? selection->asEntity() 
			: nullptr;

		World* const world = World::instance();

		if (context.button("+", 24, 20))
		{
			Entity* const newEntity = world->spawn();
			newEntity->name = std::string("Entity-") + std::to_string(world->getEntities().size() + 1);
			selectionSystem->select(newEntity);
		}
		
		context.sameLine();

		if (context.button("X", 24, 20) && selectedEntity != nullptr)
		{
			world->destroy(selectedEntity);
			selectionSystem->unselect();
		}

		for (auto it = world->getEntities().begin(); it != world->getEntities().end(); ++it)
		{
			Entity* const entity = *it;
			if (context.selectable(entity->name, selectedEntity != nullptr && entity == selectedEntity))
			{
				selectionSystem->select(entity);
			}
		}
	}
}