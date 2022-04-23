#include "menu.h"

#include <filesystem>

#include <awesome/application/application.h>
#include <awesome/data/archive.h>
#include <awesome/data/asset_importer.h>
#include <awesome/editor/private/menu_layout.h>
#include <awesome/entity/world.h>

#include <awesome/editor/menu_items/sprite_animation_menu_item.h>
#include <awesome/editor/menu_items/sprite_menu_item.h>

namespace editor
{
	void Menu::init()
	{
		TypeFactory::load<SpriteAnimationMenuItem>();
		TypeFactory::load<SpriteMenuItem>();

		static std::set<std::string> types = TypeFactory::list("MenuItem");
		for (const std::string& type : types)
		{
			MenuItem* const item = TypeFactory::instantiate<MenuItem>(type);
			if (item)
			{
				m_menuItems.push_back(std::unique_ptr<MenuItem>(item));
			}
		}
	}

	void Menu::render()
	{
		if (MenuLayout::beginMainMenu())
		{
			menuFile();
			menuAssets();
			MenuLayout::endMainMenu();
		}

		for (const auto& item : m_menuItems)
		{
			item->render();
		}
		m_saveFileDialog.render();
	}

	void Menu::menuFile()
	{
		static const auto& saveScene = [](const std::filesystem::path& filename) -> void
		{
			if (!filename.string().empty())
			{
				Archive archive(filename, Archive::Mode::Write);
				archive << json::Serializer::to_string(World::instance().serialize());

				AssetImporter importer;
				importer.import(filename);
			}
		};

		if (MenuLayout::beginMenu("File"))
		{
			if (MenuLayout::item("New"))
			{

			}

			MenuLayout::separator();

			if (MenuLayout::item("New Scene"))
			{
				World::instance().clear();
			}

			if (MenuLayout::item("Save Scene"))
			{
				m_saveFileDialog.open("Save Scene...", Asset::getExtensionByType(Asset::Type::Scene), saveScene);
			}

			if (MenuLayout::item("Save Scene as..."))
			{
				m_saveFileDialog.open("Save Scene...", Asset::getExtensionByType(Asset::Type::Scene), saveScene);
			}

			MenuLayout::separator();

			if (MenuLayout::item("Exit"))
			{
				Application::instance().exit();
			}

			MenuLayout::endMenu();
		}
	}

	void Menu::menuAssets()
	{
		if (MenuLayout::beginMenu("Assets"))
		{
			for (const auto& item : m_menuItems)
			{
				if (item->getCategory() == "Assets" && MenuLayout::item(item->getName()))
				{
					item->execute();
				}
			}
			MenuLayout::endMenu();
		}
	}
}