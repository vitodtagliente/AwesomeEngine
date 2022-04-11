#include "scene_window.h"

#include <awesome/data/archive.h>
#include <awesome/data/asset_importer.h>
#include <awesome/editor/layout.h>
#include <awesome/encoding/json.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

namespace editor
{
	void SceneWindow::render()
	{
		const auto& selection = getState()->selection;
		Entity* const selectedEntity = selection.has_value() && selection->type == State::Selection::Type::Entity
			? selection->asEntity()
			: nullptr;

		World* const world = World::instance();

		if (Layout::button("Add"))
		{
			Entity* const newEntity = world->spawn();
			newEntity->name = std::string("Entity-") + std::to_string(world->getEntities().size() + 1);
			getState()->select(newEntity);
			Layout::scrollToBottom();
		}

		if (selectedEntity != nullptr)
		{
			Layout::sameLine();
			if (Layout::button("Delete"))
			{
				world->destroy(selectedEntity);
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

		if (!world->getEntities().empty())
		{
			Layout::separator();
		}

		for (const auto& entity : world->getEntities())
		{
			if (Layout::selectable(entity->name, selectedEntity != nullptr && entity == selectedEntity))
			{
				getState()->select(entity);
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
				const std::string filename = (getState()->path / name).string() + ".scene";
				Archive archive(filename, Archive::Mode::Write);
				archive << json::Serializer::to_string(world->serialize());

				AssetImporter importer;
				importer.import(filename);
			}
			m_filename.clear();
		}
		Layout::endContext();
	}

	REFLECT_EDITOR(SceneWindow)
}