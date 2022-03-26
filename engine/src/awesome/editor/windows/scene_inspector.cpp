#include "scene_inspector.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

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

	void SceneInspector::render()
	{
		const auto& selection = getState()->selection;
		Entity* const selectedEntity = selection.has_value() && selection->type == State::Selection::Type::Entity
			? selection->asEntity()
			: nullptr;

		World* const world = World::instance();

		if (Layout::button("+"))
		{
			Entity* const newEntity = world->spawn();
			newEntity->name = std::string("Entity-") + std::to_string(world->getEntities().size() + 1);
			getState()->select(newEntity);
		}

		if (selectedEntity != nullptr)
		{
			Layout::sameLine();
			if (Layout::button("X"))
			{
				world->destroy(selectedEntity);
				getState()->select();
			}
		}

		for (auto it = world->getEntities().begin(); it != world->getEntities().end(); ++it)
		{
			Entity* const entity = *it;
			if (Layout::selectable(entity->name, selectedEntity != nullptr && entity == selectedEntity))
			{
				getState()->select(entity);
			}
		}
	}

	REFLECT_EDITOR(SceneInspector)
}