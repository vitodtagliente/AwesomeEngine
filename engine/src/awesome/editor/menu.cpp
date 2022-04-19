#include "menu.h"

#include <filesystem>

#include <imgui.h>

#include <awesome/application/application.h>
#include <awesome/data/archive.h>
#include <awesome/data/asset_importer.h>
#include <awesome/data/sprite.h>
#include <awesome/data/sprite_animation.h>
#include <awesome/entity/world.h>

namespace editor
{
	void Menu::render()
	{
		if (ImGui::BeginMainMenuBar())
		{
			menuFile();
			menuAssets();
			ImGui::EndMainMenuBar();
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

		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New"))
			{

			}

			ImGui::Separator();

			if (ImGui::MenuItem("New Scene"))
			{
				World::instance().clear();
			}

			if (ImGui::MenuItem("Save Scene"))
			{
				m_saveFileDialog.open("Save Scene...", Asset::getExtensionByType(Asset::Type::Scene), saveScene);
			}

			if (ImGui::MenuItem("Save Scene as..."))
			{
				m_saveFileDialog.open("Save Scene...", Asset::getExtensionByType(Asset::Type::Scene), saveScene);
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Exit"))
			{
				Application::instance().exit();
			}

			ImGui::EndMenu();
		}
	}

	void Menu::menuAssets()
	{
		if (ImGui::BeginMenu("Assets"))
		{
			if (ImGui::MenuItem("Sprite"))
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

			if (ImGui::MenuItem("Sprite Animation"))
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

			ImGui::EndMenu();
		}
	}
}