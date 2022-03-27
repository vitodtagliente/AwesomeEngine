#include "inspector.h"

#include <fstream>
#include <memory>
#include <set>
#include <vector>

#include <awesome/core/reflection.h>
#include <awesome/data/archive.h>
#include <awesome/data/asset.h>
#include <awesome/editor/asset_importer.h>
#include <awesome/editor/layout.h>
#include <awesome/encoding/json.h>

namespace editor
{
	Inspector::Inspector()
		: Window()
		, m_prefabFilename()
	{
		m_prefabFilename.reserve(100);
	}

	void Inspector::render()
	{
		const auto& selection = getState()->selection;
		if (selection.has_value())
		{
			if (selection->type == State::Selection::Type::Entity)
			{
				Entity* const entity = selection->asEntity();
				if (entity != nullptr)
				{
					inspect(entity);
				}
			}
			else if (selection->type == State::Selection::Type::Asset)
			{
				std::shared_ptr<Asset> asset = selection->asAsset();
				if (asset)
				{
					inspect(asset);
				}
			}
		}
	}

	void Inspector::inspect(Entity* const entity)
	{
		Layout::input("Name", &entity->name, 100);
		Layout::input("Tag", &entity->tag, 100);
		Layout::input("Position", &entity->transform.position);
		Layout::input("Rotation", &entity->transform.rotation);
		Layout::input("Scale", &entity->transform.scale);
		Layout::input("Static", &entity->transform.isStatic);
		Layout::separator();

		if (Layout::beginCombo("Add component"))
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

		Layout::input("Filename", &m_prefabFilename, 300);
		if (Layout::button("Save Prefab"))
		{
			const std::string name = m_prefabFilename.c_str();
			if (!name.empty())
			{
				const std::string filename = (getState()->workPath / name).string() + ".prefab";
				Archive archive(filename, Archive::Mode::Write);
				archive << json::Serializer::to_string(entity->serialize());
				
				AssetImporter importer;
				importer.import(filename);
			}
			m_prefabFilename.clear();
		}
	}

	void Inspector::inspect(std::shared_ptr<Asset> asset)
	{
		switch (asset->type)
		{
		case Asset::Type::Image:
		{
			std::shared_ptr<ImageAsset> image = std::static_pointer_cast<ImageAsset>(asset);
			if (image)
			{
				Layout::image(image);
			}
			break;
		}
		case Asset::Type::Prefab:
		{
			std::shared_ptr<PrefabAsset> prefab = std::static_pointer_cast<PrefabAsset>(asset);
			if (prefab)
			{
				if (Layout::button("Import"))
				{

				}
				Layout::textWrapped(prefab->data);
			}
			break;
		}
		case Asset::Type::Text:
		{
			std::shared_ptr<TextAsset> text = std::static_pointer_cast<TextAsset>(asset);
			if (text)
			{
				Layout::textWrapped(text->data);
			}
			break;
		}
		default: break;
		}
	}

	REFLECT_EDITOR(Inspector)
}