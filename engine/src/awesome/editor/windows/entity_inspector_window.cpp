#include <awesome/editor/windows/entity_inspector_window.h>

#include <awesome/asset/asset_importer.h>
#include <awesome/data/archive.h>
#include <awesome/editor/dialog.h>
#include <awesome/editor/editor.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/private/entity_layout.h>
#include <awesome/entity/world.h>

void EntityInspectorWindow::render()
{
	Editor::State& state = Editor::instance().state;
	Entity* const entity = state.selection.entity;
	if (entity == nullptr)
	{
		return;
	}

	if (entity->getState() != Entity::State::Alive)
	{
		state.select();
		return;
	}

	EntityLayout::input(entity);

	Layout::separator();

	if (Layout::button(TextIcon::save(" Save Prefab")))
	{
		const uuid entityId = entity->getId();
		Dialog::instance().save("Save Prefab...", Asset::getExtensionByType(Asset::Type::Prefab), [entityId](const std::filesystem::path& path) -> void
			{
				if (!path.string().empty())
				{
					World& world = World::instance();
					Entity* const entity = world.findEntityById(entityId);
					if (entity == nullptr) return;

					Archive archive(path, Archive::Mode::Write);
					archive << json::Serializer::to_string(entity->serialize());

					AssetImporter importer;
					importer.import(path);
				}
			}
		);
	}
}