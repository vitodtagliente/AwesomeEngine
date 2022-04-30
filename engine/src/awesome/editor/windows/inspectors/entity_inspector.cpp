#include "entity_inspector.h"

#include <awesome/asset/asset_importer.h>
#include <awesome/asset/prefab_asset.h>
#include <awesome/data/archive.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/private/entity_layout.h>
#include <awesome/editor/state.h>
#include <awesome/editor/text_icon.h>
#include <awesome/encoding/json.h>

namespace editor
{
	bool EntityInspector::canInspect(const State::Selection& selection)
	{
		return selection.type == State::Selection::Type::Entity;
	}

	void EntityInspector::inspect(const State::Selection& selection)
	{
		Entity* const entity = selection.asEntity();
		if (entity == nullptr)
		{
			return;
		}

		EntityLayout::input(*entity);

		Layout::separator();

		if (Layout::button(TextIcon::save(" Save Prefab")))
		{
			m_saveFileDialog.open("Save Prefab...", Asset::getExtensionByType(Asset::Type::Prefab), [&entity](const std::filesystem::path& path) -> void
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

		m_saveFileDialog.render();
	}
}