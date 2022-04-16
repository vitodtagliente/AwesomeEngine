#include "scene_window.h"

#include <awesome/editor/layout.h>
#include <awesome/editor/state.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

namespace editor
{
	SceneWindow::SceneWindow()
		: m_list()
	{
		m_list.onAddItem = []() -> void
		{
			World& world = World::instance();
			Entity* const newEntity = world.spawn();
			newEntity->name = std::string("Entity ") + std::to_string(world.getEntities().size() + 1);
			State::instance().select(newEntity);
			Layout::scrollToBottom();
		};

		m_list.onItemSelection = [](const uuid& id) -> void
		{
			State::instance().select(World::instance().findEntityById(id));
		};

		m_list.onRemoveItem = [](const uuid& id) -> void
		{
			World& world = World::instance();
			world.destroy(world.findEntityById(id));
			const auto& entities = world.getEntities();
			if (!entities.empty())
			{
				if (entities[0]->getId() == id)
				{
					if (entities.size() > 1)
					{
						State::instance().select(entities[1].get());
					}
					else
					{
						State::instance().select();
					}
				}
				else
				{
					State::instance().select(entities[0].get());
				}
			}
			else
			{
				State::instance().select();
			}
		};

		m_list.onRenameItem = [](const uuid& id, const std::string& name) -> void
		{
			Entity* const entity = World::instance().findEntityById(id);
			if (entity)
			{
				entity->name = name;
			}
		};
	}

	void SceneWindow::render()
	{
		State& state = State::instance();
		const auto& selection = state.selection;
		Entity* const selectedEntity = selection.has_value() && selection->type == State::Selection::Type::Entity
			? selection->asEntity()
			: nullptr;

		std::map<uuid, std::string> items;
		for (const auto& entity : World::instance().getEntities())
		{
			items.insert(std::make_pair(entity->getId(), entity->name));
		}
		m_list.render(items, selectedEntity ? std::optional<uuid>(selectedEntity->getId()) : std::nullopt);
	}

	REFLECT_WINDOW(SceneWindow)
}