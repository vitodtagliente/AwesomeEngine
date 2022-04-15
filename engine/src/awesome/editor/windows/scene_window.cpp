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

		m_list.onItemSelection = [](const std::string& item) -> void
		{
			if (item.empty())
			{
				State::instance().select();
			}
			else
			{
				State::instance().select(World::instance().findEntityByName(item));
			}
		};

		m_list.onRemoveItem = [](const std::string& item) -> void
		{
			World& world = World::instance();
			world.destroy(world.findEntityByName(item));
			const auto& entities = world.getEntities();
			if (!entities.empty())
			{
				if (entities[0]->name == item)
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

		m_list.onRenameItem = [](const std::string& item, const std::string& name) -> void
		{
			Entity* const entity = World::instance().findEntityByName(item);
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

		std::vector<std::string> items;
		const auto& entities = World::instance().getEntities();
		std::transform(entities.begin(), entities.end(), std::back_inserter(items), [](const std::unique_ptr<Entity>& entity) -> std::string
			{
				return entity->name;
			}
		);
		m_list.render(items, selectedEntity ? selectedEntity->name : "");
	}

	REFLECT_WINDOW(SceneWindow)
}