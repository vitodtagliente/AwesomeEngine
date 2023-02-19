#include "scene_window.h"

#include <awesome/core/string_util.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/editor_state.h>
#include <awesome/editor/text_icon.h>
#include <awesome/scene/entity.h>
#include <awesome/scene/scene_graph.h>

SceneWindow::SceneWindow()
	: m_editorState(EditorState::instance())
{
}

char* const SceneWindow::getTitle() const
{
	return "Scene";
}

void SceneWindow::render()
{
	Entity* const selectedEntity = m_editorState->selection.entity;
	
	Layout::beginChild("Header", 0.f, 46.f);
	if (Layout::button(TextIcon::plus(" Add Entity")))
	{
		addEntity(selectedEntity);
	}

	const std::string previousFilter = m_filter;
	Layout::input(TextIcon::search(), m_filter);
	if (previousFilter != m_filter || !hasFocus())
	{
		m_state = NavigationState::Navigating;
	}
	Layout::endChild();

	Layout::separator();

	Layout::beginChild("Content");
	for (const auto& entity : SceneGraph::instance().root()->children())
	{
		const bool isSelected = selectedEntity != nullptr && entity->id() == selectedEntity->id();
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

			renderEntity(entity.get(), selectedEntity);

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

	// reset the entity selection once clicked in the entities area
	if (Layout::isItemHovered() && Layout::isMouseClicked())
	{
		m_editorState->unselectEntity();
	}
}

void SceneWindow::update(double)
{
	if (!hasFocus()) return;

	Entity* const selectedEntity = m_editorState->selection.entity;

	if (m_state == NavigationState::Renaming)
	{
		if (Layout::isKeyPressed(KeyCode::Enter) || Layout::isKeyPressed(KeyCode::Escape))
		{
			m_state = NavigationState::Navigating;
			renameEntity(selectedEntity, m_tempRename);
			m_tempRename.clear();
		}
	}
	else
	{
		if (selectedEntity != nullptr)
		{
			if (Layout::isKeyPressed(KeyCode::F2))
			{
				m_state = NavigationState::Renaming;
				m_tempRename = selectedEntity->name;
			}
			else if (Layout::isKeyPressed(KeyCode::Delete))
			{
				deleteEntity(selectedEntity);
			}
		}		
	}
}

void SceneWindow::addEntity(Entity* const parent)
{
	Entity* const entity = parent ? parent->addChild() : SceneGraph::instance().root()->addChild();
	entity->name = static_cast<std::string>(entity->id());
	if (parent == nullptr)
	{
		m_editorState->select(entity);
		Layout::scrollToBottom();
	}
}

void SceneWindow::deleteEntity(Entity* const entity)
{
	const uuid id = entity->id();
	entity->queue_destroy();
	const auto& entities = SceneGraph::instance().root()->children();
	if (!entities.empty())
	{
		if (entities[0]->id() == id)
		{
			if (entities.size() > 1)
			{
				m_editorState->select(entities[1].get());
			}
			else
			{
				m_editorState->unselectEntity();
			}
		}
		else
		{
			m_editorState->select(entities[0].get());
		}
	}
	else
	{
		m_editorState->unselectEntity();
	}
}

void SceneWindow::renderEntity(Entity* const entity, Entity* const selectedEntity)
{
	const std::string name = entity->name + "##entity" + static_cast<std::string>(entity->id());
	const bool open = Layout::beginTreeNode(name, entity == selectedEntity);
	if (Layout::isTreeNodeClicked())
	{
		m_state = NavigationState::Navigating;
		selectEntity(entity);
	}

	if(open)
	{
		for (const auto& child : entity->children())
		{
			renderEntity(child.get(), selectedEntity);
		}
		Layout::endTreeNode();
	}
}

void SceneWindow::selectEntity(Entity* const entity)
{
	m_editorState->select(entity);
}

void SceneWindow::renameEntity(Entity* const entity, const std::string& name)
{
	entity->name = name;
}