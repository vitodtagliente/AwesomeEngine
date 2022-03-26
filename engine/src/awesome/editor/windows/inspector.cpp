#include "inspector.h"

#include <fstream>
#include <memory>
#include <set>
#include <vector>

#include <awesome/core/reflection.h>
#include <awesome/data/archive.h>
#include <awesome/data/asset.h>
#include <awesome/editor/asset_importer.h>
#include <awesome/editor/context.h>
#include <awesome/editor/selection_system.h>
#include <awesome/encoding/json.h>

namespace editor
{
	Inspector::Inspector()
		: Window()
		, m_prefabFilename()
	{
		m_prefabFilename.reserve(100);
	}

	void Inspector::render(Context& context)
	{
		const auto& selection = SelectionSystem::instance()->getSelection();
		if (selection.has_value())
		{
			if (selection->type == SelectionSystem::Selection::Type::Entity)
			{
				Entity* const entity = selection->asEntity();
				if (entity != nullptr)
				{
					inspect(context, entity);
				}
			}
			else if (selection->type == SelectionSystem::Selection::Type::Asset)
			{
				std::shared_ptr<Asset> asset = selection->asAsset();
				if (asset)
				{
					inspect(context, asset);
				}
			}
		}
	}

	void Inspector::inspect(Context& context, Entity* const entity)
	{
		context.input("Name", &entity->name, 100);
		context.input("Tag", &entity->tag, 100);
		context.input("Position", &entity->transform.position);
		context.input("Rotation", &entity->transform.rotation);
		context.input("Scale", &entity->transform.scale);
		context.input("Static", &entity->transform.isStatic);

		context.separator();

		if (context.beginCombo("Add component"))
		{
			static std::set<std::string> types = TypeFactory::listByCategory("Component");
			for (const std::string& type : types)
			{
				if (context.selectable(type.c_str(), false))
				{
					Component* const component = TypeFactory::instantiate<Component>(type);
					if (component)
					{
						entity->addComponent(component);
						context.endCombo();
						return; // force the refresh of the inspector
					}
				}

			}
			context.endCombo();
		}

		const auto& components = entity->getComponents();
		for (auto it = components.begin(); it != components.end(); ++it)
		{
			Component* const component = *it;
			if (context.collapsingHeader(component->getTypeDescriptor().name))
			{
				component->inspect(context);
				if (context.button("Remove"))
				{
					entity->removeComponent(component);
					return; // force the refresh of the inspector
				}
			}
		}

		context.separator();

		context.input("Filename", &m_prefabFilename, 300);
		if (context.button("Save Prefab"))
		{
			const std::string name = m_prefabFilename.c_str();
			if (!name.empty())
			{
				const std::string filename = (SelectionSystem::instance()->getPath() / name).string() + ".prefab";
				Archive archive(filename, Archive::Mode::Write);
				archive << json::Serializer::to_string(entity->serialize());
				
				AssetImporter importer;
				importer.import(filename);
			}
			m_prefabFilename.clear();
		}
	}

	void Inspector::inspect(Context& context, std::shared_ptr<Asset> asset)
	{
		switch (asset->type)
		{
		case Asset::Type::Image:
		{
			std::shared_ptr<ImageAsset> image = std::static_pointer_cast<ImageAsset>(asset);
			if (image)
			{
				context.image(image);
			}
			break;
		}
		case Asset::Type::Prefab:
		{
			std::shared_ptr<PrefabAsset> prefab = std::static_pointer_cast<PrefabAsset>(asset);
			if (prefab)
			{
				context.textWrapped(prefab->data);
			}
			break;
		}
		case Asset::Type::Text:
		{
			std::shared_ptr<TextAsset> text = std::static_pointer_cast<TextAsset>(asset);
			if (text)
			{
				context.textWrapped(text->data);
			}
			break;
		}
		default: break;
		}
	}

	REFLECT_IMP(Inspector)
}