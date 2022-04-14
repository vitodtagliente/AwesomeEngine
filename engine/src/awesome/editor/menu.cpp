#include "menu.h"

#include <filesystem>

#include <imgui.h>

#include <awesome/application/application.h>
#include <awesome/data/archive.h>
#include <awesome/data/asset_importer.h>
#include <awesome/editor/file_dialog.h>
#include <awesome/entity/world.h>

namespace editor
{
	void Menu::render()
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

		if (ImGui::BeginMainMenuBar())
		{
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
					m_fileDialog.open(saveScene);
				}

				if (ImGui::MenuItem("Save Scene as..."))
				{
					m_fileDialog.open(saveScene);
				}

				ImGui::Separator();

				if (ImGui::MenuItem("Exit"))
				{
					Application::instance().exit();
				}

				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		m_fileDialog.render();
	}
}