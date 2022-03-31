#include "inspector.h"

#include <fstream>
#include <memory>
#include <set>
#include <vector>

#include <awesome/core/reflection.h>
#include <awesome/data/archive.h>
#include <awesome/data/image_asset.h>
#include <awesome/data/prefab_asset.h>
#include <awesome/data/sprite_asset.h>
#include <awesome/data/sprite_animation_asset.h>
#include <awesome/data/text_asset.h>
#include <awesome/editor/asset_importer.h>
#include <awesome/editor/layout.h>
#include <awesome/encoding/json.h>

namespace editor
{
	Inspector::Inspector()
		: Window()
		, m_filename()
		, m_rect()
	{
		m_filename.reserve(100);
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

		Layout::input("Filename", &m_filename, 300);
		if (Layout::button("Save Prefab"))
		{
			const std::string name = m_filename.c_str();
			if (!name.empty())
			{
				const std::string filename = (getState()->workPath / name).string() + ".prefab";
				Archive archive(filename, Archive::Mode::Write);
				archive << json::Serializer::to_string(entity->serialize());
				
				AssetImporter importer;
				importer.import(filename);
			}
			m_filename.clear();
		}
	}

	void Inspector::inspect(AssetPtr asset)
	{
		switch (asset->type)
		{
		case Asset::Type::Image:
		{
			ImageAssetPtr image = std::static_pointer_cast<ImageAsset>(asset);
			if (image)
			{
				Layout::image(image);
				if (Layout::collapsingHeader("Sprite Editor"))
				{
					Layout::input("Filename", &m_filename, 300);
					Layout::input("Rect", m_rect);
					if (Layout::button("Save Sprite"))
					{
						const std::string name = m_filename.c_str();
						if (!name.empty())
						{
							const std::string filename = (getState()->workPath / name).string() + ".sprite";
							Sprite sprite(image, m_rect);
							sprite.save(filename);

							AssetImporter importer;
							importer.import(filename);
						}
						m_filename.clear();
						m_rect = graphics::TextureRect();
					}
				}
				if (Layout::collapsingHeader("Sprite Animation"))
				{
					Layout::input("Filename", &m_filename, 300);
					if (Layout::button("Save Animation"))
					{
						const std::string name = m_filename.c_str();
						if (!name.empty())
						{
							const std::string filename = (getState()->workPath / name).string() + ".spriteanim";
							SpriteAnimation animation;
							animation.save(filename);

							AssetImporter importer;
							importer.import(filename);
						}
						m_filename.clear();
					}
				}
			}
			break;
		}
		case Asset::Type::Prefab:
		{
			PrefabAssetPtr prefab = std::static_pointer_cast<PrefabAsset>(asset);
			if (prefab)
			{
				if (Layout::button("Import"))
				{

				}
				Layout::textWrapped(prefab->data);
			}
			break;
		}
		case Asset::Type::Sprite:
		{
			SpriteAssetPtr sprite = std::static_pointer_cast<SpriteAsset>(asset);
			if (sprite)
			{
				Layout::image(sprite->data.image, sprite->data.rect);
				Layout::input("Rect", sprite->data.rect);
			}
			break;
		}
		case Asset::Type::Text:
		{
			TextAssetPtr text = std::static_pointer_cast<TextAsset>(asset);
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