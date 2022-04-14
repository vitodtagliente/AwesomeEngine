#include "menu.h"

#include <imgui.h>

#include <awesome/application/application.h>

namespace editor
{
	void Menu::render()
	{
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New"))
                {

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
	}
}