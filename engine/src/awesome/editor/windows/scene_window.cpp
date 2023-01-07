#include "scene_window.h"

#include <awesome/core/string_util.h>
#include <awesome/editor/editor.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/text_icon.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

std::string SceneWindow::getTitle() const
{
	return "Scene";
}

void SceneWindow::render()
{
	Entity* const selectedEntity = Editor::instance()->state.selection.entity;

	const bool hasActiveFocus = hasFocus();
	if (hasActiveFocus && selectedEntity != nullptr)
	{
		processInput(selectedEntity);
	}

	Layout::beginChild("Header", 0.f, 46.f);
	if (Layout::beginCombo(TextIcon::plus(" Add Entity"), ""))
	{
		const std::vector<std::string>& types = TypeFactory::list("Type", "Entity");
		for (const std::string& type : types)
		{
			if (Layout::selectable(type.c_str(), false))
			{
				addEntity(type);
				break;
			}
		}
		Layout::endCombo();
	}

	const std::string previousFilter = m_filter;
	Layout::input(TextIcon::search(), m_filter);
	if (previousFilter != m_filter || !hasActiveFocus)
	{
		m_state = NavigationState::Navigating;
	}
	Layout::endChild();

	Layout::separator();

	Layout::beginChild("Content");
	World& world = World::instance();
	for (int i = 0; i < world.getEntities().size(); ++i)
	{
		const auto& entity = world.getEntities()[i];
		const bool isSelected = selectedEntity != nullptr && entity->getId() == selectedEntity->getId();
		if (isSelected && m_state == NavigationState::Renaming)
		{
			Layout::rename(m_tempRename);
		}
		else
		{
			if (!m_filter.empty() && !StringUtil::contains(entity->name, m_filter, StringUtil::CompareMode::IgnoreCase))
			{
				continue;
			}

			if (Layout::selectable((entity->getPrefab() != nullptr ? TextIcon::cube(" " + entity->name) : entity->name) + "##entity" + std::to_string(i), isSelected))
			{
				m_state = NavigationState::Navigating;
				selectEntity(entity.get());
			}

			// Layout::beginDrag("ENTITY_REPARENT", entity->name, (void*)(&entity->getId()), sizeof(uuid));
			// Layout::endDrag("ENTITY_REPARENT", [this, &entity](void* const data, const size_t) -> void
			// 	{
			// 		const uuid id = *(const uuid*)data;
			// 		if (id == entity->getId()) return;
			// 
			// 		Entity* const inEntity = World::instance().findEntityById(id);
			// 		if (inEntity != nullptr)
			// 		{
			// 			inEntity->setParent(entity.get());
			// 		}
			// 	}
			// );
		}
	}
	Layout::endChild();
}

void SceneWindow::processInput(Entity* const entity)
{
	if (m_state == NavigationState::Renaming)
	{
		if (Layout::isKeyPressed(KeyCode::Enter) || Layout::isKeyPressed(KeyCode::Escape))
		{
			m_state = NavigationState::Navigating;
			renameEntity(entity, m_tempRename);
			m_tempRename.clear();
		}
	}
	else
	{
		if (Layout::isKeyPressed(KeyCode::F2))
		{
			m_state = NavigationState::Renaming;
			m_tempRename = entity->name;
		}
		else if (Layout::isKeyPressed(KeyCode::Delete))
		{
			deleteEntity(entity);
		}
		else if (isHovered() && Layout::isMouseClicked())
		{
			Editor::instance()->state.unselectEntity();
		}
	}
}

void SceneWindow::addEntity(const std::string& type)
{
	World& world = World::instance();
	Entity* const entity = world.instantiate(TypeFactory::instantiate<Entity>(type));
	if (entity != nullptr)
	{
		entity->name = std::string("Entity ") + std::to_string(world.getEntities().size() + 1);
		Editor::instance()->state.select(entity);
		Layout::scrollToBottom();
	}
}

void SceneWindow::deleteEntity(Entity* const entity)
{
	const uuid id = entity->getId();
	entity->queue_destroy();
	const auto& entities = World::instance().getEntities();
	if (!entities.empty())
	{
		if (entities[0]->getId() == id)
		{
			if (entities.size() > 1)
			{
				Editor::instance()->state.select(entities[1].get());
			}
			else
			{
				Editor::instance()->state.unselectEntity();
			}
		}
		else
		{
			Editor::instance()->state.select(entities[0].get());
		}
	}
	else
	{
		Editor::instance()->state.unselectEntity();
	}
}

void SceneWindow::selectEntity(Entity* const entity)
{
	Editor::instance()->state.select(entity);
}

void SceneWindow::renameEntity(Entity* const entity, const std::string& name)
{
	entity->name = name;
}