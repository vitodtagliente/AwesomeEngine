#include "scene_window.h"

#include <awesome/application/input.h>
#include <awesome/core/string_util.h>
#include <awesome/data/archive.h>
#include <awesome/data/asset_importer.h>
#include <awesome/editor/icons.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/state.h>
#include <awesome/encoding/json.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

namespace editor
{
	void SceneWindow::update(const double /*deltaTime*/)
	{
		if (hasFocus() == false)
		{
			return;
		}

		Input& input = Input::instance();

		if (m_isRenaming)
		{
			if (input.isKeyPressed(KeyCode::Enter) || input.isKeyPressed(KeyCode::Escape))
			{
				m_isRenaming = false;
			}
		}
		else
		{
			if (input.isKeyPressed(KeyCode::F2))
			{
				m_isRenaming = true;
			}
			else if (input.isKeyPressed(KeyCode::Delete))
			{
				State& state = State::instance();
				const auto& selection = state.selection;
				Entity* const selectedEntity = selection.has_value() && selection->type == State::Selection::Type::Entity
					? selection->asEntity()
					: nullptr;

				if (selectedEntity)
				{
					World& world = World::instance();
					world.destroy(selectedEntity);
					const auto& entities = world.getEntities();
					if (!entities.empty())
					{
						if (entities[0]->getId() == selectedEntity->getId())
						{
							if (entities.size() > 1)
							{
								state.select(entities[1].get());
							}
							else
							{
								state.select();
							}
						}
						else
						{
							state.select(entities[0].get());
						}
					}
					else
					{
						state.select();
					}
				}
			}
		}
	}

	void SceneWindow::render()
	{
		State& state = State::instance();
		const auto& selection = state.selection;
		Entity* const selectedEntity = selection.has_value() && selection->type == State::Selection::Type::Entity
			? selection->asEntity()
			: nullptr;

		World& world = World::instance();

		if (Layout::button(ICON_FA_PLUS))
		{
			Entity* const newEntity = world.spawn();
			newEntity->name = std::string("Entity-") + std::to_string(world.getEntities().size() + 1);
			state.select(newEntity);
			Layout::scrollToBottom();
		}

		Layout::sameLine();

		const std::string previousFilter = m_filter;
		Layout::input(ICON_FA_SEARCH, m_filter);
		if (previousFilter != m_filter)
		{
			state.select();
			m_isRenaming = false;
		}

		Layout::separator();

		for (const auto& entity : world.getEntities())
		{
			const bool isSelected = selectedEntity != nullptr && entity.get() == selectedEntity;
			if (isSelected && m_isRenaming)
			{
				Layout::rename(entity->name);
			}
			else
			{
				if (!m_filter.empty() && !StringUtil::contains(entity->name, m_filter, StringUtil::CompareMode::IgnoreCase))
				{
					continue;
				}

				if (Layout::selectable(entity->name, isSelected))
				{
					state.select(entity.get());
					m_isRenaming = false;
				}
			}
		}
	}

	void SceneWindow::onFocusChange(const bool focus)
	{
		if (!focus)
		{
			m_isRenaming = false;
		}
	}

	REFLECT_WINDOW(SceneWindow)
}