#include "menu.h"

#include <filesystem>

#include <awesome/application/application.h>
#include <awesome/asset/asset_importer.h>
#include <awesome/asset/asset_library.h>
#include <awesome/asset/sprite_animation_asset.h>
#include <awesome/asset/sprite_asset.h>
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
		if (MenuLayout::item("Sprite"))
		{
			Dialog::instance().save("Save Sprite...", Asset::getExtensionByType(Asset::Type::Sprite), [](const std::filesystem::path& filename) -> void
				{
					if (!filename.string().empty())
					{
						SpriteAsset::data_t sprite(nullptr, graphics::TextureRect());
						sprite.save(filename);

						AssetImporter importer;
						importer.import(filename);
					}
				}
			);
		}
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
			Editor::instance().state.select();
			World::instance().clear();
		}
		MenuLayout::separator();
		if (MenuLayout::item("Save Scene"))
		{
			World& world = World::instance();
			if (world.getLoadedSceneId() != uuid::Invalid)
			{
				SceneAssetPtr asset = AssetLibrary::instance().find<SceneAsset>(world.getLoadedSceneId());
				if (asset)
				{
					world.save(asset->descriptor.getDataPath());
				}
				else
				{
					Dialog::instance().save("Save Scene", Asset::getExtensionByType(Asset::Type::Scene), [](const std::filesystem::path& path) -> void
						{
							if (!path.string().empty())
							{
								World::instance().save(path);
							}
						}
					);
				}
			}
		}
		if (MenuLayout::item("Save Scene as..."))
		{
			Dialog::instance().save("Save Scene as...", Asset::getExtensionByType(Asset::Type::Scene), [](const std::filesystem::path& path) -> void
				{
					if (!path.string().empty())
					{
						World::instance().save(path);
					}
				}
			);
		}
		MenuLayout::endMenu();
	}
}

void Menu::menuView()
{
	if (MenuLayout::beginMenu("View"))
	{
		EditorSettings& settings = Editor::instance().settings;
		if (MenuLayout::item(settings.renderWindows ? "Hide windows" : "Show windows"))
		{
			settings.renderWindows = !settings.renderWindows;
		}
		MenuLayout::endMenu();
	}
}