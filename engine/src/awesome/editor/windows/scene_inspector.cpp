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

		if (Layout::button("Add"))
		{
			EntityPtr newEntity = world->spawn();
			newEntity->name = std::string("Entity-") + std::to_string(world->getEntities().size() + 1);
			getState()->select(newEntity.get());
			Layout::scrollToBottom();
		}

		if (selectedEntity != nullptr)
		{
			Layout::sameLine();
			if (Layout::button("Delete"))
			{
				// world->destroy(selectedEntity);
				getState()->select();
			}
		}

		if (!world->getEntities().empty())
		{
			Layout::sameLine();
			if (Layout::button("Clear"))
			{
				world->clear();
				getState()->select();
			}
		}

		Layout::separator();

		for (const auto& entity : world->getEntities())
		{
			if (Layout::selectable(entity->name, selectedEntity != nullptr && entity.get() == selectedEntity))
			{
				getState()->select(entity.get());
			}
		}
	}

	REFLECT_EDITOR(SceneInspector)
}