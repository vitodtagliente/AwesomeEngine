#include "menu.h"

#include <filesystem>

#include <awesome/application/application.h>
#include <awesome/data/archive.h>
#include <awesome/data/asset_importer.h>
#include <awesome/data/sprite.h>
#include <awesome/data/sprite_animation.h>
#include <awesome/editor/private/menu_layout.h>
#include <awesome/entity/world.h>

namespace editor
{
	void Menu::render()
	{
		if (MenuLayout::beginMainMenu())
		{
			menuFile();
			menuAssets();
			MenuLayout::endMainMenu();
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
			if (MenuLayout::item("Sprite"))
			{
				m_saveFileDialog.open("Save Sprite...", Asset::getExtensionByType(Asset::Type::Sprite), [](const std::filesystem::path& filename) -> void
					{
						if (!filename.string().empty())
						{
							Sprite sprite(nullptr, graphics::TextureRect());
							sprite.save(filename);

							AssetImporter importer;
							importer.import(filename);
						}
					}
				);
			}

			if (MenuLayout::item("Sprite Animation"))
			{
				m_saveFileDialog.open("Save Sprite Animation...", Asset::getExtensionByType(Asset::Type::SpriteAnimation), [](const std::filesystem::path& filename) -> void
					{
						if (!filename.string().empty())
						{
							SpriteAnimation animation;
							animation.save(filename);

							AssetImporter importer;
							importer.import(filename);
						}
					}
				);
			}

			MenuLayout::endMenu();
		}
	}
}