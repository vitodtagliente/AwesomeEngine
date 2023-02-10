#include <awesome/editor/windows/entity_inspector_window.h>

#include <awesome/asset/asset_importer.h>
#include <awesome/core/serialization.h>
#include <awesome/data/json_file.h>
#include <awesome/editor/dialog.h>
#include <awesome/editor/editor.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/private/entity_layout.h>
#include <awesome/entity/world.h>

std::string EntityInspectorWindow::getTitle() const
{
	return "Entity Inspector";
}

void EntityInspectorWindow::render()
{
	Editor::State& state = Editor::instance()->state;
	Entity* const entity = state.selection.entity;
	if (entity == nullptr)
	{
		return;
	}

	if (entity->getState() != Entity::State::Alive)
	{
		state.unselectEntity();
		return;
	}

	EntityLayout::input(entity);

	Layout::separator();

	if (Layout::button(TextIcon::save(" Save Prefab")))
	{
		const uuid entityId = entity->getId();
		Dialog::instance().save("Save Prefab...", PrefabAsset::staticTypeMeta().at("Extension"), [entityId](const std::filesystem::path& path) -> void
			{
				World& world = World::instance();
				Entity* const entity = world.findEntityById(entityId);
				if (entity == nullptr) return;

				PrefabData data;
				data.entity = Serializer::serialize(*entity);
				JsonFile::save(data, path);

				AssetImporter importer;
				importer.import(path);
			}
		);
	}
}