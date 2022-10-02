#include <awesome/editor/windows/entity_inspector_window.h>

#include <awesome/asset/asset_importer.h>
#include <awesome/data/archive.h>
#include <awesome/editor/dialog.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/private/entity_layout.h>
#include <awesome/editor/state.h>

void EntityInspectorWindow::render()
{
	State& state = State::instance();
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
		Dialog::instance().save("Save Prefab...", Asset::getExtensionByType(Asset::Type::Prefab), [&entity](const std::filesystem::path& path) -> void
			{
				if (!path.string().empty())
				{
					Archive archive(path, Archive::Mode::Write);
					archive << json::Serializer::to_string(entity->serialize());

					AssetImporter importer;
					importer.import(path);
				}
			}
		);
	}
}