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

void reparentEntity(const uuid& id, Entity* parent)
{
	if (id == parent->id()) return;

	Entity* const draggingEntity = SceneGraph::instance().root()->findChildById(id);
	if (draggingEntity == nullptr
		|| parent->findChildById(id, false) != nullptr)
		return;

	draggingEntity->parent()->moveChild(parent, id);
}

void SceneWindow::render()
{
	Entity* const selectedEntity = m_editorState->selection.entity;
	Entity* const root = SceneGraph::instance().root();

	if (EditorUI::button(EditorUI::Icon::plus.c_str()))
	{
		Entity* const entity = root->addChild();
		entity->name = entity->id().value;
	}

	EditorUI::sameLine();
	EditorUI::search(m_filter);

	EditorUI::Child::begin("SceneContent");

	const bool open = EditorUI::Tree::begin("root", false);
	EditorUI::DragDrop::end("Entity::ChangeParent", [this, root](void* const data, const size_t) -> void { reparentEntity(*(const uuid*)data, root); });

	if (open)
	{
		for (auto it = root->children().begin(); it != root->children().end(); ++it)
		{
			const auto& entity = *it;
			if (!m_filter.empty() && !StringUtil::contains(entity->name, m_filter, StringUtil::CompareMode::IgnoreCase))
			{
				continue;
			}

			renderEntity(entity.get(), selectedEntity);
		}
		EditorUI::Tree::end();
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
	if (selectedEntity != nullptr && EditorUI::Input::isKeyPressed(KeyCode::Delete))
	{
		deleteEntity(selectedEntity);
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
			m_editorState->select(entity);
		}

		EditorUI::DragDrop::begin("Entity::ChangeParent", entity->name.c_str(), (void*)(&entity->id()), sizeof(uuid));
		EditorUI::DragDrop::end("Entity::ChangeParent", [this, entity](void* const data, const size_t) -> void { reparentEntity(*(const uuid*)data, entity); });

		if (open)
		{
			for (const auto& child : entity->children())
			{
				if (!m_filter.empty() && !StringUtil::contains(child->name, m_filter, StringUtil::CompareMode::IgnoreCase))
				{
					continue;
				}

				renderEntity(child.get(), selectedEntity);
			}
			EditorUI::Tree::end();
		}
	}
	else
	{
		if (EditorUI::selectable(name.c_str(), entity == selectedEntity))
		{
			m_editorState->select(entity);
		}

		EditorUI::DragDrop::begin("Entity::ChangeParent", entity->name.c_str(), (void*)(&entity->id()), sizeof(uuid));
		EditorUI::DragDrop::end("Entity::ChangeParent", [this, entity](void* const data, const size_t) -> void { reparentEntity(*(const uuid*)data, entity); });
	}
}