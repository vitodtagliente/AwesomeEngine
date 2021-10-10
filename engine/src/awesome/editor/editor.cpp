#include "editor.h"

#include <imgui.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD 
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "window.h"

namespace editor
{
	Editor::Editor()
		: m_context()
		, m_windows()
	{
	}

	void Editor::startup()
	{
	}

	void Editor::shutdown()
	{
	}

	void Editor::preRendering()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void Editor::render(graphics::Renderer& renderer)
	{
		for (auto it = m_windows.begin(); it != m_windows.end(); ++it)
		{
			Window* const window = *it;
			window->render(m_context);
		}
	}

	void Editor::postRendering()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}