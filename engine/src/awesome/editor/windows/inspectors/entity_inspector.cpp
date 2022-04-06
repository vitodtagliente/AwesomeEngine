#include "entity_inspector.h"

#include <awesome/data/archive.h>
#include <awesome/editor/asset_importer.h>
#include <awesome/editor/layout.h>
#include <awesome/encoding/json.h>

#include "entity_layout.h"

namespace editor
{
	EntityInspector::EntityInspector()
		: m_previousSelecytedEntity()
		, m_filename()
	{

	}

	bool EntityInspector::canInspect(const State::Selection& selection)
	{
		return selection.type == State::Selection::Type::Entity;
	}

	void EntityInspector::inspect(const State::Selection& selection, const std::filesystem::path& path)
	{
		Entity* const entity = selection.asEntity();
		
		const bool hasChanged = entity != m_previousSelecytedEntity;
		m_previousSelecytedEntity = entity;

		if (entity == nullptr)
		{
			return;
		}

		EntityLayout::input(*entity);

		Layout::separator();

		if (hasChanged)
		{
			m_filename = entity->name;
		}

		Layout::beginContext("prefab");
		Layout::input("Filename", m_filename);
		if (Layout::button("Save Prefab"))
		{
			const std::string name = m_filename.c_str();
			if (!name.empty())
			{
				const std::string filename = (path / name).string() + ".prefab";
				Archive archive(filename, Archive::Mode::Write);
				archive << json::Serializer::to_string(entity->serialize());
		
				AssetImporter importer;
				importer.import(filename);
			}
			m_filename.clear();
		}
		Layout::endContext();
	}
}