#include "menu.h"

#include <filesystem>

#include <awesome/application/application.h>
#include <awesome/asset/asset_importer.h>
#include <awesome/asset/asset_library.h>
#include <awesome/asset/sprite_animation_asset.h>
#include <awesome/asset/tileset_asset.h>
#include <awesome/data/json_file.h>
#include <awesome/editor/dialog.h>
#include <awesome/editor/editor.h>
#include <awesome/editor/private/menu_layout.h>
#include <awesome/entity/world.h>

void Menu::init()
{

}

void Menu::render()
{
	if (MenuLayout::beginMainMenu())
	{
		menuFile();
		menuScene();
		menuAssets();
		menuView();

		MenuLayout::endMainMenu();
	}
}

void Menu::menuAssets()
{
	if (MenuLayout::beginMenu("Assets"))
	{
		/*
		if (MenuLayout::item("SpriteAnimation"))
		{
			Dialog::instance().save("Save Sprite Animation...", Asset::getExtensionByType(Asset::Type::SpriteAnimation), [](const std::filesystem::path& filename) -> void
				{
					if (!filename.string().empty())
					{
						SpriteAnimationAsset::data_t tileset;
						JsonFile::save(tileset, filename);

						AssetImporter importer;
						importer.import(filename);
					}
				}
			);
		}
		if (MenuLayout::item("Tileset"))
		{
			Dialog::instance().save("Save Tileset...", Asset::getExtensionByType(Asset::Type::Tileset), [](const std::filesystem::path& filename) -> void
				{
					if (!filename.string().empty())
					{
						TilesetAsset::data_t tileset;
						JsonFile::save(tileset, filename);

						AssetImporter importer;
						importer.import(filename);
					}
				}
			);
		}
		*/
		MenuLayout::endMenu();
	}
}

void Menu::menuFile()
{
	if (MenuLayout::beginMenu("File"))
	{
		if (MenuLayout::item("Exit"))
		{
			Application::instance().exit();
		}

		MenuLayout::endMenu();
	}
}

void Menu::menuScene()
{
	if (MenuLayout::beginMenu("Scene"))
	{
		if (MenuLayout::item("New Scene..."))
		{
			Editor::instance()->state.unselectEntity();
			World::instance().clear();
		}
		MenuLayout::separator();
		// if (MenuLayout::item("Save Scene"))
		// {
		// 	World& world = World::instance();
		// 	if (world.getScene() != nullptr)
		// 	{
		// 		const std::filesystem::path& path = world.getScene()->descriptor.getDataPath();
		// 		world.save(path);
		// 
		// 		AssetImporter importer;
		// 		importer.import(path);
		// 	}
		// 	else
		// 	{
		// 		Dialog::instance().save("Save Scene as...", Asset::getExtensionByType(Asset::Type::Scene), [](const std::filesystem::path& path) -> void
		// 			{
		// 				if (!path.string().empty())
		// 				{
		// 					World::instance().save(path);
		// 
		// 					AssetImporter importer;
		// 					importer.import(path);
		// 				}
		// 			}
		// 		);
		// 	}
		// }
		// if (MenuLayout::item("Save Scene as..."))
		// {
		// 	Dialog::instance().save("Save Scene as...", Asset::getExtensionByType(Asset::Type::Scene), [](const std::filesystem::path& path) -> void
		// 		{
		// 			if (!path.string().empty())
		// 			{
		// 				World::instance().save(path);
		// 			}
		// 		}
		// 	);
		// }
		MenuLayout::endMenu();
	}
}

void Menu::menuView()
{
	if (MenuLayout::beginMenu("View"))
	{
		const auto& windows = Editor::instance()->getWindows();
		for (auto& window : windows)
		{
			MenuLayout::item(window->getTitle(), window->visible);
		}

		if (!windows.empty())
		{
			MenuLayout::separator();
		}

		EditorSettings& settings = Editor::instance()->settings;
		MenuLayout::item("Show windows (F5)", settings.renderWindows);
		MenuLayout::endMenu();
	}
}