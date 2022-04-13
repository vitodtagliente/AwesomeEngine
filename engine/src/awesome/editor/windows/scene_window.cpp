#include "scene_window.h"

#include <awesome/application/input.h>
#include <awesome/data/archive.h>
#include <awesome/data/asset_importer.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/state.h>
#include <awesome/encoding/json.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

namespace editor
{
	void SceneWindow::update(const double deltaTime)
	{
		Input& input = Input::instance();
		if (input.isKeyPressed(KeyCode::F2))
		{
			m_renaming = true;
		}
		else if (m_renaming && input.isKeyPressed(KeyCode::Enter))
		{
			m_renaming = false;
		}
	}

	void SceneWindow::render()
	{
		const auto& selection = State::instance().selection;
		Entity* const selectedEntity = selection.has_value() && selection->type == State::Selection::Type::Entity
			? selection->asEntity()
			: nullptr;

		World& world = World::instance();

		if (Layout::button("Add"))
		{
			Entity* const newEntity = world.spawn();
			newEntity->name = std::string("Entity-") + std::to_string(world.getEntities().size() + 1);
			State::instance().select(newEntity);
			Layout::scrollToBottom();
		}

		if (selectedEntity != nullptr)
		{
			Layout::sameLine();
			if (Layout::button("Delete"))
			{
				world.destroy(selectedEntity);
				State::instance().select();
			}
		}

		if (!world.getEntities().empty())
		{
			Layout::sameLine();
			if (Layout::button("Clear"))
			{
				world.clear();
				State::instance().select();
			}
		}

		if (!world.getEntities().empty())
		{
			Layout::separator();
		}

		for (const auto& entity : world.getEntities())
		{
			const bool isSelected = selectedEntity != nullptr && entity.get() == selectedEntity;
			if (isSelected && m_renaming)
			{
				Layout::rename(entity->name);
			}
			else
			{
				if (Layout::selectable(entity->name, isSelected))
				{
					State::instance().select(entity.get());
				}
			}
		}

		Layout::separator();

		Layout::beginContext("scene");
		Layout::input("Filename", m_filename);
		if (Layout::button("Save Scene"))
		{
			const std::string name = m_filename.c_str();
			if (!name.empty())
			{
				const std::string filename = (State::instance().path / name).string() + ".scene";
				Archive archive(filename, Archive::Mode::Write);
				archive << json::Serializer::to_string(world.serialize());

				AssetImporter importer;
				importer.import(filename);
			}
			m_filename.clear();
		}
		Layout::endContext();
	}

	REFLECT_WINDOW(SceneWindow)
}