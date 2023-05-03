#include "scene_window.h"

#include <awesome/core/string_util.h>
#include <awesome/editor/editor_state.h>
#include <awesome/editor/editor_ui.h>
#include <awesome/scene/entity.h>
#include <awesome/scene/scene_graph.h>

SceneWindow::SceneWindow()
	: Window()
	, m_editorState(EditorState::instance())
{
}

char* const SceneWindow::getTitle() const
{
	return "Scene";
}

void SceneWindow::render()
{
	Entity* const selectedEntity = m_editorState->selection.entity;
	
	EditorUI::DragDrop::end("ENTITY_REPARENT", [this](void* const data, const size_t) -> void
		{
			const uuid id = *(const uuid*)data;

			Entity* const draggingEntity = SceneGraph::instance().root()->findChildById(id);
			if (draggingEntity != nullptr)
			{
				draggingEntity->parent()->moveChild(SceneGraph::instance().root(), id);
				m_editorState->unselectEntity();
			}
		}
	);

	if (EditorUI::button(EditorUI::Icon::plus.c_str()))
	{
		addEntity(nullptr);
	}

	EditorUI::sameLine();
	EditorUI::search(m_filter);

	EditorUI::Child::begin("Content");
	const auto& children = SceneGraph::instance().root()->children();
	for (auto it = children.begin(); it != children.end(); ++it)
	{
		const auto& entity = *it;
		const bool isSelected = selectedEntity != nullptr && entity->id() == selectedEntity->id();
		if (isSelected && m_state == NavigationState::Renaming)
		{
			EditorUI::rename(m_tempRename);
		}
		else
		{
			if (!m_filter.empty() && !StringUtil::contains(entity->name, m_filter, StringUtil::CompareMode::IgnoreCase))
			{
				continue;
			}

			renderEntity(entity.get(), selectedEntity);

			bool dragCompleted{ false };
			EditorUI::DragDrop::end("ENTITY_REPARENT", [this, &entity, &dragCompleted](void* const data, const size_t) -> void
				{
					const uuid id = *(const uuid*)data;
					if (id == entity->id()) return;
			
					Entity* const draggingEntity = SceneGraph::instance().root()->findChildById(id);
					if (draggingEntity != nullptr)
					{
						draggingEntity->parent()->moveChild(entity.get(), id);
						m_editorState->unselectEntity();
						dragCompleted = true;
					}
				}
			);

			if (dragCompleted)
			{
				break;
			}
		}
	}
	EditorUI::Child::end();

	// reset the entity selection once clicked in the entities area
	if (EditorUI::Input::isItemHovered() && EditorUI::Input::isMouseClicked())
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
		if (EditorUI::Input::isKeyPressed(KeyCode::Enter) || EditorUI::Input::isKeyPressed(KeyCode::Escape))
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
			if (EditorUI::Input::isKeyPressed(KeyCode::F2))
			{
				m_state = NavigationState::Renaming;
				m_tempRename = selectedEntity->name;
			}
			else if (EditorUI::Input::isKeyPressed(KeyCode::Delete))
			{
				deleteEntity(selectedEntity);
			}
		}		
	}
}

void SceneWindow::addEntity(Entity* const parent)
{
	Entity* const entity = parent ? parent->addChild() : SceneGraph::instance().root()->addChild();
	entity->name = entity->id().value;
	if (parent == nullptr)
	{
		m_editorState->select(entity);
		EditorUI::Input::scrollToBottom();
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
	const std::string name = entity->name + "##entity" + entity->id().value;
	if (entity->hasChildren())
	{
		const bool open = EditorUI::Tree::begin(name.c_str(), entity == selectedEntity);
		if (EditorUI::Tree::isClicked())
		{
			m_state = NavigationState::Navigating;
			selectEntity(entity);
		}

		EditorUI::DragDrop::begin("ENTITY_REPARENT", entity->name.c_str(), (void*)(&entity->id()), sizeof(uuid));

		if (open)
		{
			for (const auto& child : entity->children())
			{
				renderEntity(child.get(), selectedEntity);
			}
			EditorUI::Tree::end();
		}
	}
	else
	{
		if (EditorUI::selectable(name.c_str(), entity == selectedEntity))
		{
			m_state = NavigationState::Navigating;
			selectEntity(entity);
		}

		EditorUI::DragDrop::begin("ENTITY_REPARENT", entity->name.c_str(), (void*)(&entity->id()), sizeof(uuid));
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