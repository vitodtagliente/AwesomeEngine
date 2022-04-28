#include "entity_inspector.h"

#include <awesome/asset/asset_importer.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/private/entity_layout.h>
#include <awesome/editor/state.h>
#include <awesome/editor/text_icon.h>

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
			m_saveFileDialog.open("Save Prefab...", Asset::getExtensionByType(Asset::Type::Prefab), [&entity](const std::filesystem::path& filename) -> void
				{
					if (!filename.string().empty())
					{
						// Prefab prefab(entity);
						// prefab.save(filename);
						// 
						// AssetImporter importer;
						// importer.import(filename);
					}
				}
			);
		}

		m_saveFileDialog.render();
	}
}