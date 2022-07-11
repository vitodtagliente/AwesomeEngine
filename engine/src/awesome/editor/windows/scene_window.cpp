#include "scene_window.h"

#include <imgui.h>

#include <awesome/application/input.h>
#include <awesome/core/string_util.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/state.h>
#include <awesome/editor/text_icon.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

namespace editor
{
	void SceneWindow::render()
	{
		State& state = State::instance();
		Entity* const selectedEntity = state.selection.entity;

		const bool hasActiveFocus = Layout::isWindowFocused();
		if (hasActiveFocus && selectedEntity != nullptr)
		{
			processInput(selectedEntity);
		}

		ImGui::BeginChild("Header", ImVec2(0.f, 26.f), false, ImGuiWindowFlags_NoDecoration);
		if (Layout::button(TextIcon::plus()))
		{
			addEntity();
		}

		Layout::sameLine();

		const std::string previousFilter = m_filter;
		Layout::input(TextIcon::search(), m_filter);
		if (previousFilter != m_filter || !hasActiveFocus)
		{
			m_state = NavigationState::Navigating;
		}
		ImGui::EndChild();

		Layout::separator();

		ImGui::BeginChild("Content", ImVec2(0.f, 0.f), false, ImGuiWindowFlags_AlwaysUseWindowPadding);
		int i = 0;
		for (const auto& entity : World::instance().getEntities())
		{
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

				if (Layout::selectable((entity->getPrefab() != uuid::Invalid ? TextIcon::cube(" " + entity->name) : entity->name) + "##entity" + std::to_string(i), isSelected))
				{
					m_state = NavigationState::Navigating;
					m_tempRename = entity->name;
					selectEntity(entity.get());
				}
			}
			++i;
		}
		ImGui::EndChild();
	}

	void SceneWindow::processInput(Entity* const entity)
	{
		Input& input = Input::instance();
		if (m_state == NavigationState::Renaming)
		{
			if (input.isKeyPressed(KeyCode::Enter) || input.isKeyPressed(KeyCode::Escape))
			{
				m_state = NavigationState::Navigating;
				renameEntity(entity, m_tempRename);
			}
		}
		else
		{
			if (input.isKeyPressed(KeyCode::F2))
			{
				m_state = NavigationState::Renaming;
			}
			else if (input.isKeyPressed(KeyCode::Delete))
			{
				deleteEntity(entity);
			}
		}
	}

	void SceneWindow::addEntity()
	{
		World& world = World::instance();
		Entity* const newEntity = world.spawn();
		newEntity->name = std::string("Entity ") + std::to_string(world.getEntities().size() + 1);
		State::instance().select(newEntity);
		Layout::scrollToBottom();
	}

	void SceneWindow::deleteEntity(Entity* const entity)
	{
		const uuid id = entity->getId();
		World& world = World::instance();
		world.destroy(entity);
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
	}

	void SceneWindow::selectEntity(Entity* const entity)
	{
		State::instance().select(entity);
	}

	void SceneWindow::renameEntity(Entity* const entity, const std::string& name)
	{
		entity->name = name;
	}

	REFLECT_WINDOW(SceneWindow)
}