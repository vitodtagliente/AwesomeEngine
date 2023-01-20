#include "menu.h"

#include <filesystem>

#include <awesome/application/application.h>
#include <awesome/asset/asset_importer.h>
#include <awesome/core/string_util.h>
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
		const auto& asset_types = TypeFactory::list("Type", "Asset");
		for (const TypeDefinition& type : asset_types)
		{
			const auto& it = type.meta.find("CreateInEditor");
			if (it == type.meta.end() || it->second == "false") continue;

			const auto& extIt = type.meta.find("Extension");
			if (extIt == type.meta.end()) continue;

			const std::vector<std::string> extensions = StringUtil::split(extIt->second, '|');
			if (extensions.empty()) continue;

			const std::string label = StringUtil::replace(type.name, "Asset", "");
			if (MenuLayout::item(label))
			{
				Dialog::instance().save(label, extensions.front(), [type](const std::filesystem::path& path) -> void
					{
						AssetPtr asset = std::shared_ptr<Asset>(TypeFactory::instantiate<Asset>(type));
						if (asset != nullptr)
						{
							asset->save(path);

							AssetImporter importer;
							importer.import(path);
						}
					}
				);
			}
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
			Editor::instance()->state.unselectEntity();
			World::instance().clear();
		}
		MenuLayout::separator();
		bool save_as = false;
		if (MenuLayout::item("Save Scene"))
		{
			SceneAssetPtr scene = World::instance().getScene();
			if (scene != nullptr)
			{
				scene->save(scene->path);
			}
			else
			{
				save_as = true;
			}
		}
		if (MenuLayout::item("Save Scene as..."))
		{
			save_as = true;
		}

		if (save_as)
		{
			Dialog::instance().save("Save Scene as...", SceneAsset::staticTypeMeta().at("Extension"), [](const std::filesystem::path& path) -> void
				{
					World::instance().save(path);

					AssetImporter importer;
					importer.import(path);
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