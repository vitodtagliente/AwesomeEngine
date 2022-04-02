#include "entity_inspector.h"

#include <awesome/data/archive.h>
#include <awesome/editor/asset_importer.h>
#include <awesome/editor/layout.h>
#include <awesome/encoding/json.h>
#include <awesome/entity/entity.h>

namespace editor
{
	EntityInspector::EntityInspector()
		: m_previousSelecytedEntity()
		, m_filename()
	{
		m_filename.reserve(300);
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

		Layout::beginContext("entity");
		Layout::input("Name", &entity->name, 100);
		Layout::input("Tag", &entity->tag, 100);
		Layout::input("Position", entity->transform.position);
		Layout::input("Rotation", entity->transform.rotation);
		Layout::input("Scale", entity->transform.scale);
		Layout::input("Static", entity->transform.isStatic);
		Layout::endContext();

		Layout::separator();

		if (Layout::beginCombo("Add component", ""))
		{
			static std::set<std::string> types = TypeFactory::listByCategory("Component");
			for (const std::string& type : types)
			{
				if (Layout::selectable(type.c_str(), false))
				{
					Component* const component = TypeFactory::instantiate<Component>(type);
					if (component)
					{
						entity->addComponent(component);
						Layout::endCombo();
						return; // force the refresh of the inspector
					}
				}
			}
			Layout::endCombo();
		}

		const auto& components = entity->getComponents();
		for (auto it = components.begin(); it != components.end(); ++it)
		{
			Component* const component = *it;
			const std::string& componentName = component->getTypeDescriptor().name;
			Layout::beginContext(componentName);
			if (Layout::collapsingHeader(componentName))
			{
				component->inspect();
				if (Layout::button("Remove"))
				{
					entity->removeComponent(component);
					return; // force the refresh of the inspector
				}
			}
			Layout::endContext();
		}

		Layout::separator();

		if (hasChanged)
		{
			m_filename = entity->name;
		}

		Layout::beginContext("prefab");
		Layout::input("Filename", &m_filename, 300);
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