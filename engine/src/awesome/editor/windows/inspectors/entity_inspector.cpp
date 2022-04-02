#include "entity_inspector.h"

#include <awesome/data/archive.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>

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

		Layout::input("Name", &entity->name, 100);
		Layout::input("Tag", &entity->tag, 100);
		Layout::input("Position", entity->transform.position);
		Layout::input("Rotation", entity->transform.rotation);
		Layout::input("Scale", entity->transform.scale);
		Layout::input("Static", entity->transform.isStatic);
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
			if (Layout::collapsingHeader(component->getTypeDescriptor().name))
			{
				component->inspect();
				if (Layout::button("Remove"))
				{
					entity->removeComponent(component);
					return; // force the refresh of the inspector
				}
			}
		}

		Layout::separator();

		// Layout::input("Filename", &m_filename, 300);
		// if (Layout::button("Save Prefab"))
		// {
		// 	const std::string name = m_filename.c_str();
		// 	if (!name.empty())
		// 	{
		// 		const std::string filename = (getState()->workPath / name).string() + ".prefab";
		// 		Archive archive(filename, Archive::Mode::Write);
		// 		archive << json::Serializer::to_string(entity->serialize());
		// 
		// 		AssetImporter importer;
		// 		importer.import(filename);
		// 	}
		// 	m_filename.clear();
		// }
	}
}